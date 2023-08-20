#include "loader.h"

Elf32_Ehdr *ehdr;
Elf32_Phdr *phdr;
int fd;

// // typedef int (*StartFunction)();
int (*_start)(void);
// int (*_start)(void){
//     entry_addr = (void*)_start;
//     int(*addr)() = (int(*)())entry_addr;
//     return addr();
// }

/*
 * release memory and other cleanups
 */
void loader_cleanup() {
  
}

/*
 * Load and run the ELF executable file
 */
void load_and_run_elf(char* exe) {
  fd = open(exe, O_RDONLY);

  off_t fd_size = lseek(fd,0,SEEK_END);
  lseek(fd,0,SEEK_SET);
  printf("File size: %lld\n", (long long)fd_size);

  char *heap_mem;
  heap_mem = (char*)malloc(fd_size);
  // printf("Heap Memory Allocated\n");

  ssize_t file_read = read(fd, heap_mem, fd_size);
  // printf("File reading Done\n");
  // printf("Address of heap: %p\n", (void*)heap_mem);

  ehdr = (Elf32_Ehdr *)heap_mem; 
  // printf("Address of ehdr: %p\n", (void*)ehdr);

  phdr = (Elf32_Phdr *)(heap_mem + ehdr->e_phoff);
  // printf("offset: %d\n", ehdr->e_phoff);
  // printf("Address of phdr: %p\n", (void*)phdr);

  unsigned int entry = ehdr->e_entry;
  // printf("Entry Point address is %#x\n",entry);

  // printf("Program Headers: %d\n", ehdr->e_phnum);
  // printf("size of Program Headers: %d\n", ehdr->e_phentsize);
  // printf("Offset of Program Headers: %d\n", ehdr->e_phoff);
  Elf32_Phdr * tmp = phdr;
  while(tmp->p_type != PT_LOAD){
    tmp++;
  }
  tmp++;
  // if(tmp->p_type == PT_LOAD){
  //   printf("FOUND\n");
  //   // printf("%d\n",tmp->p_type);
  // }
  // else{
  //   printf("NOT FOUND\n");
  // }
  void* virtual_mem = mmap(NULL,tmp->p_memsz,PROT_READ|PROT_WRITE|PROT_EXEC, MAP_ANONYMOUS|MAP_PRIVATE, 0,0);
  memcpy(virtual_mem,heap_mem+tmp->p_offset,tmp->p_memsz);

  //  for (ssize_t i = 0; i < tmp->p_memsz; i++) {
  //     printf("%02x ", ((unsigned char*)virtual_mem)[i]);
  //     if ((i + 1) % 16 == 0) {
  //         printf("\n");
  //     }
  // }

  void* entry_addr = virtual_mem + (entry - tmp->p_vaddr);
  printf("Entry Point Address in Memory: %p\n", entry_addr);
  printf("Virtual mem start: %p\n", virtual_mem);
  printf("Virtual mem end: %p\n", virtual_mem + tmp->p_memsz);
  // close(fd);

  // if(entry_addr != NULL) {
  //   _start = (int (*)(void))entry_addr;
  //   // ret = sum(1, 2);
  //   // printf("sum:%d\n", ret);
  //   int result = _start();
  //   printf("User _start return value = %d\n",result);
  // };

  if (entry_addr >= virtual_mem && entry_addr < virtual_mem + tmp->p_memsz) {
    printf("Entry Point Address in Memory: %p\n", entry_addr);

    if (entry_addr != NULL) {
        _start = (int (*)(void))entry_addr;
      // printf("yes\n");
        int result = _start();
        printf("User _start return value = %d\n", result);
    }
} else {
    printf("Entry Point Address is out of bounds.\n");
}

  // 1. Load entire binary content into the memory from the ELF file.
  // 2. Iterate through the PHDR table and find the section of PT_LOAD 
  //    type that contains the address of the entrypoint method in fib.c
  // 3. Allocate memory of the size "p_memsz" using mmap function 
  //    and then copy the segment content
  // 4. Navigate to the entrypoint address into the segment loaded in the memory in above step
  // 5. Typecast the address to that of function pointer matching "_start" method in fib.c.
  // 6. Call the "_start" method and print the value returned from the "_start"

  // int result = _start();
  // printf("User _start return value = %d\n",result);
}

int main(int argc, char** argv) 
{
  if(argc != 2) {
    printf("Usage: %s <ELF Executable> \n",argv[0]);
    exit(1);
  }
  // 1. carry out necessary checks on the input ELF file
  // 2. passing it to the loader for carrying out the loading/execution
  load_and_run_elf(argv[1]);
  // 3. invoke the cleanup routine inside the loader  
  loader_cleanup();
  return 0;
}
