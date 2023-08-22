#include "../loader/loader.h"

int main1(int argc, char** argv) 
{
  if(argc != 2) {
    printf("Usage: %s <ELF Executable> \n",argv[0]);
    exit(1);
  }
  // 1. carry out necessary checks on the input ELF file
  // checking if ELF file exists in the provided path
  FILE *elfFile = fopen(argv[1], "rb");
  if (!elfFile)
  {
    printf("Error: Unable to open ELF file.\n");
    exit(1);
  }
  fclose(elfFile);
  // 2. passing it to the loader for carrying out the loading/execution
  load_and_run_elf(&argv[1]);
  // 3. invoke the cleanup routine inside the loader  
  loader_cleanup();
  return 0;
}
