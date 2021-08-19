GCCPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARAMS = --32
LDPARAMS = -melf_i386
OSName = FlexibleOS
Objects = Loader.o Kernel.o Console.o Converter.o Math.o Memory.o GlobalDescriptorTable.o Port.o Error.o

%.o: %.cpp
	gcc $(GCCPARAMS) -c -o $@ $<

%.o: %.asm
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
	rm -rf iso

	mv $(OSName).iso ../Build
	mv $(Objects) ../Build
	mv $(OSName).bin ../Build