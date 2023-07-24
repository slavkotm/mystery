#WINDOWS



#LINUX 
CUR = $(shell pwd)
VULKAN_SDK = $(VULKAN_SDK)

run: $(CURDIR)/mystery/src/main.c
	gcc -I$(VULKAN_SDK)/include $< -o main
