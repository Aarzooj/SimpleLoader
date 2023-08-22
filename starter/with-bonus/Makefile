#invoke make inside following directories and in this order: loader, launch, fib
all:
	cd loader && $(MAKE)
	cd launcher && $(MAKE)
	cd test && $(MAKE)
	make install
	cd launcher && gcc -m32 -o launch -L../bin -l_simpleloader launch.c
	cp launcher/launch bin/

#move the lib_simpleloader.so and launch binaries inside bin directory
install:
	mkdir -p bin
	cd bin && gcc -m32 -shared -o lib_simpleloader.so ../loader/loader.c

#Provide the command for cleanup
clean:
	rm -rf bin
	cd loader && $(MAKE) clean
	cd launcher && $(MAKE) clean
	cd test && $(MAKE) clean