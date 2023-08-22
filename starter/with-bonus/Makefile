#invoke make inside following directories and in this order: loader, launch, fib
all:
	mkdir -p bin
	cd loader && $(MAKE)
	cd launcher && $(MAKE)
	cd test && $(MAKE)
	make install

#move the lib_simpleloader.so and launch binaries inside bin directory
install:
	cp loader/loader.o bin/
	cp launcher/launch.o bin/
	cp test/fib bin/
	cd bin
	gcc -shared -o lib_simpleloader.so loader.o launch.o
	gcc -m32 -o fib -L. -l_simpleloader

#Provide the command for cleanup
clean:
	rm -rf bin
	cd loader && $(MAKE) clean
	cd launcher && $(MAKE) clean
	cd test && $(MAKE) clean