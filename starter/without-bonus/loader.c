#include "loader.h"

Elf32_Ehdr *ehdr;
Elf32_Phdr *phdr;
int fd;

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
  printf("Heap Memory Allocated\n");

  ssize_t file_read = read(fd, heap_mem, fd_size);
  printf("File reading Done\n");

  ehdr = (Elf32_Ehdr *)heap_mem; 
  phdr = (Elf32_Phdr*)(heap_mem + ehdr->e_phoff);
  unsigned int entry = ehdr->e_entry;
  printf("%02x\n",entry);
  // unsigned int entry = ehdr->e_entry;
  // printf("---->%d\n",entry);
  // printf("Program Headers: %d\n", ehdr->e_phnum);
  // printf("size of Program Headers: %d\n", ehdr->e_phentsize);
  // printf("Offset of Program Headers: %d\n", ehdr->e_phoff);
  Elf32_Phdr* tmp = phdr;
  while(tmp->p_type != PT_LOAD){
    tmp++;
  }
  if(tmp->p_type == PT_LOAD){
    printf("FOUND\n");
    // printf("%02x\n",tmp->p_vaddr);
  }
  else{
    printf("NOT FOUND\n");
  }   

  void* virtual_mem = mmap(NULL,tmp->p_memsz,PROT_READ|PROT_WRITE|PROT_EXEC,MAP_ANONYMOUS|MAP_PRIVATE,0,0);
  // printf("%p\n",virtual_mem);

  memcpy(virtual_mem,heap_mem+tmp->p_offset,tmp->p_memsz);

  // for (ssize_t i = 0; i < file_read; i++) {
  // printf("%02x ", heap_mem[i]);
  // if ((i + 1) % 16 == 0) {
  //     printf("\n");
  //   }
  // }
  // for (size_t i = 0; i < tmp->p_memsz; i++) {
  // printf("%02x ", ((unsigned char*)virtual_mem)[i]);
  // if ((i + 1) % 16 == 0) {
  //     printf("\n");
  //   }
  // }

  // Calculate the offset within the segment to the e_entrypoint
  // unsigned int e_entry_offset = entry - tmp->p_vaddr;

  // Navigate to the e_entrypoint address within the virtual memory segment
  // void* e_entry_address = (char*)virtual_mem + e_entry_offset;

  // printf("THIS THIS: %p",e_entry_address);
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
