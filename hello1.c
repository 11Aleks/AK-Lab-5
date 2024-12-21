// SPDX-License-Identifier: UNLICENSED
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <hello1.h>

MODULE_AUTHOR("Antipov O. <minigameapple@gmail.com>");
MODULE_DESCRIPTION("First part kernel module for printing 'Hello, world!'");
MODULE_LICENSE("Dual BSD/GPL");

struct event_data {
	struct list_head list;
	ktime_t start_Stamp;
	ktime_t end_Stamp;
};

static LIST_HEAD(event_list);

void print_hello(void)
{
	struct event_data *new_event = kmalloc(sizeof(*new_event),
	 	GFP_KERNEL);
	new_event->start_Stamp = ktime_get();
	pr_info("Hello, world!\n");
	new_event->end_Stamp = ktime_get();
	list_add_tail(&new_event->list, &event_list);
}
EXPORT_SYMBOL(print_hello);

static void __exit hello1_exit(void)
{
	struct event_data *event;
	struct list_head *pos,  *q;

	list_for_each_safe(pos, q, &event_list) {
		event = list_entry(pos, struct event_data, list);
		pr_info("Print time: %lld ns\n",
		        ktime_to_ns(event->end_Stamp) - ktime_to_ns(event->start_Stamp));
		list_del(pos);
		kfree(event);
	}
}
module_exit(hello1_exit);
