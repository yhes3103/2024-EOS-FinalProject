obj-m := car_driver.o

all: RPI_build
clean: RPI_clean

RPI_build: car_driver.c
	sudo make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -C $(PWD) M=$(shell pwd) modules
 
RPI_clean:
	sudo make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -C $(PWD) M=$(shell pwd) clean
 
.PHONY: 
	all clean RPI_build RPI_clean