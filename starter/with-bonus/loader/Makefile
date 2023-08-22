# Create lib_simpleloader.so from loader.c
all:
	gcc -m32 -o loader loader.c
	mkdir -p ../bin
	gcc -m32 -shared -o ../bin/lib_simpleloader.so loader

# Provide the command for cleanup
clean:
	rm -f loader