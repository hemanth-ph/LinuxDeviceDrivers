obj-m:=my_char_dev.o
ARCH=arm
CROSS_COMPILER=arm-linux-gnueabihf-
bbb_src_path=/home/hemanth/hemanth/ldd/source/linux
curr_src_path=/lib/modules/5.15.0-47-generic/build

bbb:
	#make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILER) -C $(bbb_src_path) M=$(pwd) modules
	sudo make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C ~/hemanth/ldd/source/linux/ M=$(pwd) modules
	
current:
	make -C $(curr_src_path) M=$(pwd) modules

clean:
	#make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILER) -C $(bbb_src_path) M=$(pwd) clean
	sudo make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C ~/hemanth/ldd/source/linux/ M=$(pwd) clean
