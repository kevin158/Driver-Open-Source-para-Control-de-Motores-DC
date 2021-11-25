#!/bin/bash
make -C /usr/src/linux-headers-$(uname -r) M=$(pwd modules)
cp customusb.ko /lib/modules/5.11.0-40-generic/kernel/drivers/usb/serial
insmod /lib/modules/5.11.0-40-generic/kernel/drivers/usb/serial/usbserial.ko
insmod /lib/modules/5.11.0-40-generic/kernel/drivers/usb/serial/customusb.ko
