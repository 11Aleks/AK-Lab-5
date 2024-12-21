// SPDX-License-Identifier: UNLICENSED
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <hello1.h>

MODULE_AUTHOR("Antipov O. <minigameapple@gmail.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_PARM_DESC(times, "Time to print 'Hello, world!'");

extern void print_hello(void);

static unsigned int times = 1;
module_param(times, uint, 0444); // Parameter of type uint

static int __init hello2_init(void)
{
	unsigned int i = 0;

	if (times == 0 || (times >= 5 && times <= 10))
		pr_warn("Warning: Continuing...\n");

	if (times > 10) {
		pr_err("Error: Module not loaded!\n");
		return -EINVAL;
	}

	for (i = 0; i < times; i++) {
		print_hello();
	}
	return 0;
}
static void __exit hello2_exit(void)
{
	pr_info("Hello2.ko was removed.\n");
}
module_init(hello2_init);
module_exit(hello2_exit);
