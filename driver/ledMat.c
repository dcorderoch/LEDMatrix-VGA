/*
 *
 * HT16K33 driver for an 8x8 LED Matrix
 * 
 * This driver is intended to be used with an Adafruit Mini 8x8 LED 
   Matrix w/I2C Backpack connected to the I2C port located in the VGA 
   connector.

   It provides an easy interface to turn on and off each LED.


Copyright (C) 2017  David Cordero Chavarría
Copyright (C) 2017  Manuel Zumbado Corrales

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#define DEBUG 1

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
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
#define REG_LED_0 0x00  
#define REG_LED_1 0x02
#define REG_LED_2 0x04
#define REG_LED_3 0x06
#define REG_LED_4 0x08
#define REG_LED_5 0x0a
#define REG_LED_6 0x0c
#define REG_LED_7 0x0d    

void ledMat_exit(void);
int ledMat_init(void);/* Structure that declares the usual file */


//Data to be stored by the client
struct ledMat_data {
	struct mutex update_lock;
    int someValue;
};

//Declaration of the init function
module_init(ledMat_init);
module_exit(ledMat_exit);

//Variables used by the exposed fileops (write, open, close)
static struct class * ledMat_i2c_class = NULL;
static struct device * ledMat_i2c_device = NULL;
static int ledMat_i2c_major;

//Define global i2c_client structure. This is used for fileops.
static struct i2c_client * ledMat_i2c_client = NULL;

static struct i2c_board_info ledMat_board_info  = {
    I2C_BOARD_INFO("ledMat", 0x70),
};

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
   // Only in write mode
   if ((fp->f_flags & O_ACCMODE) != O_WRONLY)
       return -EACCES;
 
   // Only one process can access the file at one time.
   if (!mutex_trylock(&ledMat_i2c_mutex))
   {
       printk("%s: Device currently in use!\n", __FUNCTION__);
       return -EBUSY;
   }
 
   // Check if the client is already loaded
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
 
    //Limit the number of bytes written
    if (count > 512)
        count = 512;
 
    tmp = memdup_user(buf, count);
    if (IS_ERR(tmp))
        return PTR_ERR(tmp);
 
    printk("%s: Write operation with [%d] bytes\n", __FUNCTION__, count);
    for (x = 0; x < count; x++)
        if (ledMat_write_value(ledMat_i2c_client, REG_LED_0, (u16) tmp[x]) == 0)
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

//attributes exported via sysfs. 
static ssize_t set_mat_led0(struct device *dev, 
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
 
    ledMat_write_value(client, REG_LED_0, (u16) value);
 
    return count;
}

static ssize_t set_mat_led1(struct device *dev, 
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
 
    ledMat_write_value(client, REG_LED_1, (u16) value);
 
    return count;
}

static ssize_t set_mat_led2(struct device *dev, 
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
 
    ledMat_write_value(client, REG_LED_2, (u16) value);
 
    return count;
}

static ssize_t set_mat_led3(struct device *dev, 
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
 
    ledMat_write_value(client, REG_LED_3, (u16) value);
 
    return count;
}

static ssize_t set_mat_led4(struct device *dev, 
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
 
    ledMat_write_value(client, REG_LED_4, (u16) value);
 
    return count;
}

static ssize_t set_mat_led5(struct device *dev, 
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
 
    ledMat_write_value(client, REG_LED_5, (u16) value);
 
    return count;
}

static ssize_t set_mat_led6(struct device *dev, 
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
 
    ledMat_write_value(client, REG_LED_6, (u16) value);
 
    return count;
}

static ssize_t set_mat_led7(struct device *dev, 
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
 
    ledMat_write_value(client, REG_LED_7, (u16) value);
 
    return count;
}

// mat led is write only
static DEVICE_ATTR(mat_led0, 0660, NULL, set_mat_led0);
static DEVICE_ATTR(mat_led1, 0660, NULL, set_mat_led1);
static DEVICE_ATTR(mat_led2, 0660, NULL, set_mat_led2);
static DEVICE_ATTR(mat_led3, 0660, NULL, set_mat_led3);
static DEVICE_ATTR(mat_led4, 0660, NULL, set_mat_led4);
static DEVICE_ATTR(mat_led5, 0660, NULL, set_mat_led5);
static DEVICE_ATTR(mat_led6, 0660, NULL, set_mat_led6);
static DEVICE_ATTR(mat_led7, 0660, NULL, set_mat_led7);


//Init function to initialize the driver
static void ledMat_init_client(struct i2c_client *client)
{
    dev_info(&client->dev, "%s\n", __FUNCTION__);
}



int ledMat_init(void) {
	int retval = 0;
	struct i2c_adapter * adapter;
	struct i2c_client * client;
	adapter = i2c_get_adapter(1);

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
        return -ENODEV;

    client = i2c_new_device(adapter, &ledMat_board_info);

    struct device * dev = &client->dev;
    struct ledMat_data *data = NULL;
 
    printk("ledMat_i2c: %s\n", __FUNCTION__);

 
    // Allocate client's data 
    data = devm_kzalloc(&client->dev, sizeof(struct ledMat_data), GFP_KERNEL);
    if(!data)
        return -ENOMEM;
 
    // Initialize client's data to default
    i2c_set_clientdata(client, data);
    // Initialize mutex
    mutex_init(&data->update_lock);
 
    // initialize hardware
    ledMat_init_client(client);
 
    //Global pointer to the client
    ledMat_i2c_client = client;
 
    // We now create our character device driver
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
 
    // Initialize the mutex for /dev fops clients 
    mutex_init(&ledMat_i2c_mutex);
 
 
    // We now register our sysfs attributs. 
    device_create_file(dev, &dev_attr_mat_led0);
    device_create_file(dev, &dev_attr_mat_led1);
    device_create_file(dev, &dev_attr_mat_led2);
    device_create_file(dev, &dev_attr_mat_led3);
    device_create_file(dev, &dev_attr_mat_led4);
    device_create_file(dev, &dev_attr_mat_led5);
    device_create_file(dev, &dev_attr_mat_led6);
    device_create_file(dev, &dev_attr_mat_led7);

    ledMat_write_value(client, REG_BLINK_SETUP, 0xFF);
 
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

//Exit function called when driver stops or the device is removed.
void ledMat_exit(void)
{
	struct device * dev = &ledMat_i2c_client->dev;
    printk("ledMat_i2c: %s\n", __FUNCTION__);
 
    ledMat_i2c_client = NULL;
 
    device_remove_file(dev, &dev_attr_mat_led0);
    device_remove_file(dev, &dev_attr_mat_led1);
    device_remove_file(dev, &dev_attr_mat_led2);
    device_remove_file(dev, &dev_attr_mat_led3);
    device_remove_file(dev, &dev_attr_mat_led4);
    device_remove_file(dev, &dev_attr_mat_led5);
    device_remove_file(dev, &dev_attr_mat_led6);
    device_remove_file(dev, &dev_attr_mat_led7);
 
    device_destroy(ledMat_i2c_class, MKDEV(ledMat_i2c_major, 0));
    class_unregister(ledMat_i2c_class);
    class_destroy(ledMat_i2c_class);
    unregister_chrdev(ledMat_i2c_major, DRIVER_NAME);
}

MODULE_DESCRIPTION("8x8 LED Matrix I2C Driver");
MODULE_LICENSE("GPL2");/* License */