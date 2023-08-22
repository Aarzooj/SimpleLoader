#invoke make inside following directories and in this order: loader, launch, fib
all:
	cd loader && $(MAKE)
	cd launcher && $(MAKE)
	cd test && $(MAKE)
	make install

#move the lib_simpleloader.so and launch binaries inside bin directory
install:
	cp loader/loader bin/
	cp launcher/launch bin/

#Provide the command for cleanup
clean:
	rm -rf bin
	cd loader && $(MAKE) clean
	cd launcher && $(MAKE) clean
	cd test && $(MAKE) clean