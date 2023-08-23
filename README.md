# Simple Loader
The objective of the assignment is to implement a [SimpleLoader](https://en.wikipedia.org/wiki/Loader_(computing)) for loading an ELF 32-bit executable in plain-C without using any library APIs available for manipulating ELF files. The SimpleLoader should compile to a shared library (lib_simpleloader.so) that can be used to load and execute the executable using a helper program.

## Without-bonus: LOADER
The following steps were followed to implement the loader in plain C:
- The “open” system call was used to get the file descriptor for the input binary and “read” system call was used to read the content of the binary into a heap allocated memory of appropriate size. Malloc was used to allocate space for copying content of the binary.
- Iterate through the PHDR table and find the section of PT_LOAD (p_type) type that contains the address of the entrypoint method in fib.c
- Allocate memory of the size “p_memsz” using mmap function and then copy the segment content.
- Navigate to the entrypoint address (e_entrypoint) into the segment loaded in the memory in above step. 
- After reaching that location, simply typecast the address to that of function pointer matching “_start” method in fib.c. 
- Call the “_start” method and print the value returned from the “_start.

### Running the code
First navigate to the folder containing the files and then run the following command:
```
make
./loader ./fib
```

## With-bonus: SHARED LIBRARY
The implementation for Loader is the same as above.
The shared library was dynamically created.
- `Loader.c` was used to create the shared library `lib_simpleloader.c`
- `Launch.c` used this library to execute the `fib.c` code and display the output by calling functions from `loader.c`

### Running the code
First navigate to the folder containing the files and then run the following command:
```
make
cd bin
./launch ../test/fib
```

## Cleanup
Run `make clean` to clean the folders by deleting the `relocatable` and `executable` files.

## References
Following references were used to implement the above assignment:
- [Linux Manual Pages](https://man7.org/linux/man-pages/man5/elf.5.html)
- [Lseek() documentation](https://www.ibm.com/docs/en/i/7.4?topic=ssw_ibm_i_74/apis/lseek.html)
- [Read() documentation](https://www.ibm.com/docs/en/i/7.4?topic=ssw_ibm_i_74/apis/read.html)
- [Mmap() documentation](https://www.ibm.com/docs/en/i/7.4?topic=ssw_ibm_i_74/apis/mmap.html)
- [ELF Format](https://www.ics.uci.edu/~aburtsev/238P/hw/hw3-elf/hw3-elf.html#7)
- [Typecasting and Function Pointers](https://hackaday.com/2018/05/02/directly-executing-chunks-of-memory-function-pointers-in-c/)
- [Creating Static and Dynamic link libraries on Linux](https://stackoverflow.com/questions/480764/linux-error-while-loading-shared-libraries-cannot-open-shared-object-file-no-s)
- [Shared Libraries with GCC on Linux](https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html)
- [Using a Dynamic Library](https://youtu.be/pkMg_df8gHs)
- [.SO Shared Object Files in Linux](https://youtu.be/CqUuNCZMGJU)
- [Solve Shared-Object-Error](https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html)
- [Error while loading shared libraries](https://stackoverflow.com/questions/480764/linux-error-while-loading-shared-libraries-cannot-open-shared-object-file-no-s)