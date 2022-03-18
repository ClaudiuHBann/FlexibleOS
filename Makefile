GCCPARAMS = -m32 -IInclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARAMS = --32
LDPARAMS = -melf_i386

OSName = FlexibleOS
Objects = Objects/Common/Console.o \
		  Objects/Common/Converter.o \
		  Objects/Common/Error.o \
		  Objects/Common/Math.o \
		  Objects/Common/Memory.o \
\
		  Objects/Drivers/VideoGraphicsArray.o \
		  Objects/Drivers/Keyboard.o \
		  Objects/Drivers/Mouse.o \
\
		  Objects/HardwareCommunication/InterruptManager.o \
		  Objects/HardwareCommunication/InterruptStubs.o \
		  Objects/HardwareCommunication/Port.o \
\
		  Objects/GlobalDescriptorTable.o \
		  Objects/Kernel.o \
		  Objects/Loader.o \

Objects/%.o: Source/%.cpp
	mkdir -p $(@D)
	gcc $(GCCPARAMS) -c -o $@ $<

Objects/%.o: Source/%.asm
	mkdir -p $(@D)
	as $(ASPARAMS) -o $@ $<

$(OSName).bin: Linker.ld $(Objects)
	ld $(LDPARAMS) -T $< -o $@ $(Objects)

$(OSName).iso: $(OSName).bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $(OSName).bin iso/boot/$(OSName).bin

	echo 'set timeout = 0'                    > iso/boot/grub/grub.cfg
	echo 'set default = 0'                   >> iso/boot/grub/grub.cfg
	echo ''                                  >> iso/boot/grub/grub.cfg
	echo 'menuentry "$(OSName)" {' 			 >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/$(OSName).bin'   >> iso/boot/grub/grub.cfg
	echo '  boot'                            >> iso/boot/grub/grub.cfg
	echo '}'                                 >> iso/boot/grub/grub.cfg

	grub-mkrescue --output=$(OSName).iso iso

clean:
	rm -rf Objects iso
	rm $(OSName).bin

	mv $(OSName).iso Build/

copy:
	cp Build/$(OSName).iso /mnt/hgfs/Desktop

build: $(OSName).iso clean copy

git:
	git add -A .
	git commit -m "$m"
	git push -u origin master