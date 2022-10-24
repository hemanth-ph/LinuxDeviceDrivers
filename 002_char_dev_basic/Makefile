obj-m:=my_char_dev.o
ARCH=arm
CROSS_COMPILER=arm-linux-gnueabihf-
bbb_src_path=/home/hemanth/hemanth/ldd/source/linux
curr_src_path=/lib/modules/5.15.0-47-generic/build

bbb:
	sudo make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C /home/hemanth/hemanth/ldd/source/linux M=/home/hemanth/hemanth/ldd/custom-drivers/002_char_dev_basic modules
current:
	sudo make -C /lib/modules/5.15.0-47-generic/build M=/home/hemanth/hemanth/ldd/custom-drivers/002_char_dev_basic modules

clean:
	sudo make -C /lib/modules/5.15.0-47-generic/build M=/home/hemanth/hemanth/ldd/custom-drivers/002_char_dev_basic clean
