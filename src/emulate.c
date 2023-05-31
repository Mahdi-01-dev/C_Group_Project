#include <stdio.h>
#include <stdlib.h>

#define WORD_SIZE 32
#define MEMORY_SIZE 2097152


unsigned char getBit(unsigned int, int);
void printByte(unsigned char);

unsigned char *memory;

int main(int argc, char **argv) {
  FILE *file;
  // Make sure that there is a second parameter(binary file)
  if (argc != 2) {
    return EXIT_FAILURE;
  }

  // Memory is given 2MB
  memory = (unsigned char *) malloc(MEMORY_SIZE);
  if (memory == NULL) {
    printf("Memory allocation failed.\n");
    return EXIT_FAILURE;
  }
  // Open file
  file = fopen(argv[1], "rb");
  if (file == NULL) {
    printf("Opening file failed.\n");
    return EXIT_FAILURE;
  }

  // File size
  fseek(file, 0, SEEK_END);
  long fileSize = ftell(file);
  rewind(file);

  // Read file into memory
  size_t bytesRead = fread(memory, 1, fileSize, file);
  if (bytesRead != fileSize) {
    printf("Failed to read file.\n");
    free(memory);
    fclose(file);
    return EXIT_FAILURE;
  }

  // Close file
  fclose(file);



  // no. words
  // int numWords = fileSize / sizeof(unsigned int);

  // // process each word
  // for (int i = 0; i < numWords; i++) {
  //   unsigned int word = *(unsigned int *)(memory + i * sizeof(unsigned int));
  //   unsigned char bitArray[WORD_SIZE];

  //   for (int j = 0; j < WORD_SIZE; j++) {
  //     bitArray[j] = (word >> j) & 1;
  //   }
  // }
  // Print byte in hex
  // for (long i = 0; i < fileSize; i++) {
  //    printf("%08x ", memory[i]);

  free(memory);
  return 0;
}

// @param i - ensure it's between 0 and 31 inclusive.
unsigned char getBit(unsigned int word, int i) {
  return (word >> i) & 1;
}

// @param byte - pass in memory[i].
void printByte(unsigned char byte) {
  for (int j = 7; j >= 0; j--) {
    unsigned char mask = 1 << j;
    unsigned char bit = (byte & mask) ? 1 : 0;
    printf("%d", bit);
  }
}
