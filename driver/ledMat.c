/*
 *
 * HT16K33 driver for an 8x8 LED Matrix
 *
 */
#define DEBUG 1

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/mutex.h>
#include <linux/err.h>
#include <linux/sysfs.h>
#include <linux/device.h>
#include <linux/fs.h>



#define DRIVER_NAME			"ledMat"

// Registers
#define REG_BLINK_SETUP 0x81  
#define REG_LED 0x00  



//This is used to define the addresses to scan
static const unsigned short normal_i2c[] = { 0x69, 0x70, I2C_CLIENT_END };

//Driver id table
static const struct i2c_device_id ledMat_i2c_id[] = {
    { "ledMat", 0 },
    {}
};

MODULE_DEVICE_TABLE(i2c, ledMat_i2c_id);

//Data to be stored by the client
struct ledMat_data {
	struct mutex update_lock;
    int someValue;
};

//Variables used by the exposed fileops (write, open, close)
static struct class * ledMat_i2c_class = NULL;
static struct device * ledMat_i2c_device = NULL;
static int ledMat_i2c_major;

//Define global i2c_client structure. This is used for fileops.
static struct i2c_client * ledMat_i2c_client = NULL;

//Mutex to ensure only one process accessing the ledMatrix
static DEFINE_MUTEX(ledMat_i2c_mutex);


// IO function to write data on the i2c bus.
 
int ledMat_write_value(struct i2c_client *client, u8 reg, u16 value)
{
    struct ledMat_data *data = i2c_get_clientdata(client);
    int ret = 0;
 
    dev_info(&client->dev, "%s\n", __FUNCTION__);
 
    mutex_lock(&data->update_lock);
    ret =  i2c_smbus_write_byte_data(client, reg, value);
    mutex_unlock(&data->update_lock);
 
    dev_info(&client->dev, "%s : write reg [%02x] with val [%02x] returned [%d]\n", 
            __FUNCTION__, reg, value, ret);
 
    return ret;
}

//Functions used by the driver to provide a char device interface.
static int ledMat_i2c_open(struct inode * inode, struct file *fp)
{
   printk("%s: Attempt to open our device\n", __FUNCTION__);
   /* Our driver only allows writing to our LED's */
   if ((fp->f_flags & O_ACCMODE) != O_WRONLY)
       return -EACCES;
 
   // Only one process can access the file at one time.
   if (!mutex_trylock(&ledMat_i2c_mutex))
   {
       printk("%s: Device currently in use!\n", __FUNCTION__);
       return -EBUSY;
   }
 
   /* Check if the client is already loaded
    */
   if (ledMat_i2c_client == NULL)
       return -ENODEV;
 
   return 0;
}

static int ledMat_i2c_close(struct inode * inode, struct file * fp)
{
   printk("%s: Freeing /dev resource\n", __FUNCTION__);
 
   mutex_unlock(&ledMat_i2c_mutex);
   return 0;
}


//File op function to write
static ssize_t ledMat_i2c_write(struct file * fp, const char __user * buf,
        size_t count, loff_t * offset)
{
    int x, numwrite = 0;
    char * tmp;
 
    /* We'll limit the number of bytes written out */
    if (count > 512)
        count = 512;
 
    tmp = memdup_user(buf, count);
    if (IS_ERR(tmp))
        return PTR_ERR(tmp);
 
    printk("%s: Write operation with [%d] bytes\n", __FUNCTION__, count);
    for (x = 0; x < count; x++)
        if (ledMat_write_value(ledMat_i2c_client, REG_LED, (u16) tmp[x]) == 0)
            numwrite++;
 
    return numwrite;
}

//The file operations table used by the initialization code.
static const struct file_operations ledMat_i2c_fops = {
    .owner = THIS_MODULE,
    .llseek = no_llseek,
    .write = ledMat_i2c_write,
    .open = ledMat_i2c_open,
    .release = ledMat_i2c_close
};

//attribute exported via sysfs. 
static ssize_t set_mat_led(struct device *dev, 
    struct device_attribute * devattr,
    const char * buf, 
    size_t count)
{
    struct i2c_client * client = to_i2c_client(dev);
    int value, err;
 
    dev_dbg(&client->dev, "%s\n", __FUNCTION__);
 
    err = kstrtoint(buf, 10, &value);
    if (err < 0)
        return err;
 
    dev_dbg(&client->dev, "%s: write to i2c with val %d\n", 
        __FUNCTION__,
        value);
 
    ledMat_write_value(client, REG_LED, (u16) value);
 
    return count;
}

// mat led is write only
static DEVICE_ATTR(mat_led, 0660, NULL, set_mat_led);


//Init function to initialize the driver
static void ledMat_init_client(struct i2c_client *client)
{
    dev_info(&client->dev, "%s\n", __FUNCTION__);
 
    ledMat_write_value(client, REG_BLINK_SETUP, 0xFF);
}

//Driver callback functions
//This function is called by the kernel when the device is detected.
static int ledMat_i2c_probe(struct i2c_client *client,
    const struct i2c_device_id *id)
{
    int retval = 0;
    struct device * dev = &client->dev;
    struct ledMat_data *data = NULL;
 
    printk("ledMat_i2c: %s\n", __FUNCTION__);
 
    /* Allocate the client's data here */
    data = devm_kzalloc(&client->dev, sizeof(struct ledMat_data), GFP_KERNEL);
    if(!data)
        return -ENOMEM;
 
    /* Initialize client's data to default */
    i2c_set_clientdata(client, data);
    /* Initialize the mutex */
    mutex_init(&data->update_lock);
 
    /* If our driver requires additional data initialization
     * we do it here. For our intents and purposes, we only 
     * set the data->kind which is taken from the i2c_device_id.
     **/
    data->someValue = id->driver_data;
 
    /* initialize our hardware */
    ledMat_init_client(client);
 
    /* In our arbitrary hardware, we only have
     * one instance of this existing on the i2c bus.
     * Therefore we set the global pointer of this
     * client.
     */
    ledMat_i2c_client = client;
 
    /* We now create our character device driver */
    ledMat_i2c_major = register_chrdev(0, DRIVER_NAME,
        &ledMat_i2c_fops);
    if (ledMat_i2c_major < 0)
    {
        retval = ledMat_i2c_major;
        printk("%s: Failed to register char device!\n", __FUNCTION__);
        goto out;
    }
 
    ledMat_i2c_class = class_create(THIS_MODULE, DRIVER_NAME);
    if (IS_ERR(ledMat_i2c_class))
    {
        retval = PTR_ERR(ledMat_i2c_class);
        printk("%s: Failed to create class!\n", __FUNCTION__);
        goto unreg_chrdev;
    }
 
    ledMat_i2c_device = device_create(ledMat_i2c_class, NULL, 
        MKDEV(ledMat_i2c_major, 0),
        NULL,
        DRIVER_NAME "_leds");
    if (IS_ERR(ledMat_i2c_device))
    {
        retval = PTR_ERR(ledMat_i2c_device);
        printk("%s: Failed to create device!\n", __FUNCTION__);
        goto unreg_class;
    }
 
    /* Initialize the mutex for /dev fops clients */
    mutex_init(&ledMat_i2c_mutex);
 
 
    // We now register our sysfs attributs. 
    device_create_file(dev, &dev_attr_mat_led);
 
    return 0;
    /* Cleanup on failed operations */
 
unreg_class:
    class_unregister(ledMat_i2c_class);
    class_destroy(ledMat_i2c_class);
unreg_chrdev:
    unregister_chrdev(ledMat_i2c_major, DRIVER_NAME);
    printk("%s: Driver initialization failed!\n", __FUNCTION__);
out:
    return retval;
}

//Function called when the driver or the device is removed
static int ledMat_i2c_remove(struct i2c_client * client)
{
    struct device * dev = &client->dev;
 
    printk("ledMat_i2c: %s\n", __FUNCTION__);
 
    ledMat_i2c_client = NULL;
 
    device_remove_file(dev, &dev_attr_mat_led);
 
    device_destroy(ledMat_i2c_class, MKDEV(ledMat_i2c_major, 0));
    class_unregister(ledMat_i2c_class);
    class_destroy(ledMat_i2c_class);
    unregister_chrdev(ledMat_i2c_major, DRIVER_NAME);
 
    return 0;
}
 
//function called by the kernel to detect the ledMat at a given address.
static int ledMat_i2c_detect(struct i2c_client * client, 
    struct i2c_board_info * info)
{
    struct i2c_adapter *adapter = client->adapter;
    int address = client->addr;
    const char * name = NULL;
 
    printk("ledMat_i2c: %s!\n", __FUNCTION__);
 
    if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
        return -ENODEV;
 
    // Since our address is hardwired to 0x21
    // we update the name of the driver. This must
    // match the name of the chip_driver struct below
    // in order for this driver to be loaded.
    if (address == 0x70)
    {
        name = DRIVER_NAME;
        dev_info(&adapter->dev,
            "ledMat device found at 0x%02x\n", address);
    }else
        return -ENODEV;
 
    /* Upon successful detection, we coup the name of the
     * driver to the info struct.
     **/
    strlcpy(info->type, name, I2C_NAME_SIZE);
    return 0;
}

//Main driver description table
static struct i2c_driver ledMat_driver = {
    .class      = I2C_CLASS_HWMON,
    .driver = {
            .name = DRIVER_NAME,
    },
    .probe          = ledMat_i2c_probe,
    .remove         = ledMat_i2c_remove,
    .id_table       = ledMat_i2c_id,
    .detect      = ledMat_i2c_detect,
    .address_list   = normal_i2c,
};

module_i2c_driver(ledMat_driver);

MODULE_DESCRIPTION("8x8 LED Matrix I2C Driver");
MODULE_LICENSE("Dual BSD/GPL");/* License */