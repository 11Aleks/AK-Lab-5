ifneq ($(KERNELRELEASE),)
obj-m += hello1.o hello2.o
ccflags-y := -I$(PWD)/inc
else
KDIR ?= /home/antypovoleksandr/repos/linux-stable

default:
	$(MAKE) -C $(KDIR) M=$$PWD
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
endif

