/*
 *
 * HT16K33 driver for an 8x8 LED Matrix
 *
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/fs.h> /* everything... */
#include <linux/errno.h> /* error codes */
#include <linux/types.h> /* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h> /* O_ACCMODE */
#include <asm/uaccess.h> /* copy_from/to_user */
#include <linux/i2c.h>
MODULE_LICENSE("Dual BSD/GPL");/* License */

#define DRIVER_NAME			"ledMat"

// Registers

#define REG_BLINK_SETUP 0x81  //Register address




static int ledMat_probe(struct i2c_client *client,
				  const struct i2c_device_id *id)
{
	int err;
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev, "i2c_check_functionality error\n");
		return -EIO;
	}
	//Set blink mode OFF
	err = i2c_smbus_write_byte_data(client, REG_BLINK_SETUP, 0xFF);
	//Set LED on
	err = i2c_smbus_write_byte_data(client, 0x01, 0xFF);

	printk("Detected LED Matrix!!!");
	return err;
}


static int ledMat_remove(struct i2c_client *client)
{
	return 0;
}


static const struct i2c_device_id ledMat_i2c_match[] = {
	{ "ht16k33", 0 },
	{ }
};

MODULE_DEVICE_TABLE(i2c, ledMat_i2c_match);

static const struct of_device_id ledMat_of_match[] = {
	{ .compatible = "holtek,ht16k33", },
	{ }
};
MODULE_DEVICE_TABLE(of, ledMat_of_match);

static struct i2c_driver ledMat_driver = {
	.probe		= ledMat_probe,
	.remove		= ledMat_remove,
	.driver		= {
		.name		= DRIVER_NAME,
		.of_match_table	= of_match_ptr(ledMat_of_match),
	},
	.id_table = ledMat_i2c_match,
};
module_i2c_driver(ledMat_driver);

