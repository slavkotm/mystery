#WINDOWS



#LINUX 
CUR = $(shell pwd)
VULKAN_SDK = $(VULKAN_SDK)

run: $(CUR)/mystery/src/main.c
	gcc -I$(VULKAN_SDK)/include $< -o main
