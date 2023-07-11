#include <stdio.h>
#include <stdlib.h>

#define CALL_STACK_HEIGHT 256
#define CELL_START_OFFSET 15000
#define CELL_COUNT 30000

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: %s [SOURCE]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  FILE* fp = fopen(argv[1], "r");
  if (!fp) {
    fprintf(stderr, "ERR: Could not load file %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  // quick n' dirty filesize
  fseek(fp, 0L, SEEK_END);
  unsigned long sz = ftell(fp);
  rewind(fp);

  // loading it as string for easier access
  char* bf_code = (char*)calloc(sz + 1, 1); // calloc initializes to 0, avoiding need for memset; +1 for nullterminator
  fread((void*) bf_code, 1, sz, fp);
  fclose(fp);

  char* cell = (char*) calloc(CELL_COUNT, 1); // guidelines say that total cell-count should be 30k
  unsigned short cell_ptr = CELL_START_OFFSET;
  unsigned short call_stack_ptr = 0;
  unsigned long call_stack[256] = {0};
  unsigned long instruction_ptr = 0;

  printf("PROGRAM START\n");
  while (bf_code[instruction_ptr] != 0) {
    switch (bf_code[instruction_ptr]) {
      case '+':
        ++cell[cell_ptr];
        ++instruction_ptr;
        break;
      case '-':
        --cell[cell_ptr];
        ++instruction_ptr;
        break;
      case '<':
        if (cell_ptr == 0) {
          fprintf(stderr, "ERR: Cell index out of bounds @ %lu\n", instruction_ptr);
          free(cell);
          exit(EXIT_FAILURE);
        }
        --cell_ptr;
        ++instruction_ptr;
        break;
      case '>':
        if (cell_ptr == CELL_COUNT - 1) {
          fprintf(stderr, "ERR: Cell index out of bounds @ %lu\n", instruction_ptr);
          free(cell);
          exit(EXIT_FAILURE);
        }
        ++cell_ptr;
        ++instruction_ptr;
        break;
      case '.':
        putchar(cell[cell_ptr]);
        ++instruction_ptr;
        break;
      case '[':
        if (cell[cell_ptr] == 0) {
          unsigned short brace_depth = 1;
          ++instruction_ptr;
          while (brace_depth) {
            switch (bf_code[instruction_ptr]) {
              case '[':
                ++brace_depth;
                break;
              case ']':
                --brace_depth;
                break;
            }
            ++instruction_ptr;
          }
        } else if (call_stack_ptr == 0xFFFF) {
          fprintf(stderr, "ERR: Maximum nested loop depth reached.\n");
          free(cell);
          exit(EXIT_FAILURE);
        } else {
          call_stack[call_stack_ptr++] = instruction_ptr++;
        }
        break;
      case ']':
        if (call_stack_ptr == 0) {
          fprintf(stderr, "ERR: Mismatched [ ] @ %lu\n", instruction_ptr);
          free(cell);
          exit(EXIT_FAILURE);
        }
        instruction_ptr = call_stack[--call_stack_ptr];
        break;
      default:
        ++instruction_ptr;
    }
  }
  printf("\nPROGRAM END\n");
  free(cell);

  return 0;
}
