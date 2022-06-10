MODULENAME := hello

ifeq ($(KERNELRELEASE), )
KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)
clean:
	@rm -rf .*.cmd *.ko *.mod *.mod.c *.o Module.symvers modules.order
load:
	@sudo insmod $(MODULENAME).ko
unload:
	@sudo rmmod $(MODULENAME)
else
	obj-m := $(MODULENAME).o
endif
