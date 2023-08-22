#invoke make inside following directories and in this order: loader, launch, fib
all:
	cd loader && $(MAKE)
	cd launcher && $(MAKE)
	cd test && $(MAKE)
	make install
	cd launcher
	gcc -o launch -L../bin -l_simpleloader launch.c

#move the lib_simpleloader.so and launch binaries inside bin directory
install:
	mkdir -p bin
	cp loader/loader.o bin/
	cp launcher/launch.o bin/
	gcc -shared -o lib_simpleloader.so ./bin/loader.o ./bin/launch.o

#Provide the command for cleanup
clean:
	rm -rf bin
	cd loader && $(MAKE) clean
	cd launcher && $(MAKE) clean
	cd test && $(MAKE) clean