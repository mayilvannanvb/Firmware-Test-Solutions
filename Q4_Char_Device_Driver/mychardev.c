/*
 * Question 4: Simple Linux Character Device Driver
 *
 * Device : /dev/mychardev
 * Ops    : open, read, write, release
 *
 * Build  : make
 * Load   : sudo insmod mychardev.ko
 * Test   : echo "Hello Driver" > /dev/mychardev && cat /dev/mychardev
 * Remove : sudo rmmod mychardev
 *
 * Concepts: Kernel Module, file_operations, copy_to_user,
 *           copy_from_user, printk, device registration
 *
 * NOTE: Requires Linux kernel headers.
 *       sudo apt install linux-headers-$(uname -r)
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/init.h>

#define DEVICE_NAME "mychardev"
#define CLASS_NAME  "mychar_class"
#define BUF_SIZE    1024

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mayilvannan VB");
MODULE_DESCRIPTION("Simple Character Device Driver");
MODULE_VERSION("1.0");

static int            major_number;
static char           kernel_buffer[BUF_SIZE] = {0};
static int            buf_len = 0;
static struct class  *mychar_class  = NULL;
static struct device *mychar_device = NULL;

/* open() - called when user opens /dev/mychardev */
static int dev_open(struct inode *inodep, struct file *filep)
{
    printk(KERN_INFO "mychardev: Device Opened\n");
    return 0;
}

/* release() - called when user closes the device */
static int dev_release(struct inode *inodep, struct file *filep)
{
    printk(KERN_INFO "mychardev: Device Closed\n");
    return 0;
}

/* read() - sends kernel_buffer data to user space */
static ssize_t dev_read(struct file *filep, char __user *user_buf,
                         size_t len, loff_t *offset)
{
    int to_read = buf_len - *offset;
    if (to_read <= 0) return 0;
    if (to_read > (int)len) to_read = len;

    if (copy_to_user(user_buf, kernel_buffer + *offset, to_read))
        return -EFAULT;

    *offset += to_read;
    printk(KERN_INFO "mychardev: Data Read - %d bytes\n", to_read);
    return to_read;
}

/* write() - receives data from user space into kernel_buffer */
static ssize_t dev_write(struct file *filep, const char __user *user_buf,
                          size_t len, loff_t *offset)
{
    if (len > BUF_SIZE - 1) len = BUF_SIZE - 1;
    memset(kernel_buffer, 0, BUF_SIZE);

    if (copy_from_user(kernel_buffer, user_buf, len))
        return -EFAULT;

    buf_len = len;
    kernel_buffer[buf_len] = '\0';
    printk(KERN_INFO "mychardev: Data Written - %zu bytes: %s\n", len, kernel_buffer);
    return len;
}

static struct file_operations fops = {
    .open    = dev_open,
    .read    = dev_read,
    .write   = dev_write,
    .release = dev_release,
};

static int __init mychardev_init(void)
{
    /* Step 1: Register char device — kernel assigns major number */
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "mychardev: register failed (%d)\n", major_number);
        return major_number;
    }
    printk(KERN_INFO "mychardev: registered, major = %d\n", major_number);

    /* Step 2: Create /sys/class/mychar_class */
    mychar_class = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(mychar_class)) {
        unregister_chrdev(major_number, DEVICE_NAME);
        return PTR_ERR(mychar_class);
    }

    /* Step 3: Create /dev/mychardev via udev */
    mychar_device = device_create(mychar_class, NULL,
                                   MKDEV(major_number, 0),
                                   NULL, DEVICE_NAME);
    if (IS_ERR(mychar_device)) {
        class_destroy(mychar_class);
        unregister_chrdev(major_number, DEVICE_NAME);
        return PTR_ERR(mychar_device);
    }

    printk(KERN_INFO "mychardev: /dev/%s created\n", DEVICE_NAME);
    return 0;
}

static void __exit mychardev_exit(void)
{
    device_destroy(mychar_class, MKDEV(major_number, 0));
    class_unregister(mychar_class);
    class_destroy(mychar_class);
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "mychardev: Module removed\n");
}

module_init(mychardev_init);
module_exit(mychardev_exit);
