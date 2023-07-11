#include <stdio.h>
#include <stdlib.h>

#include "lib/LinkedList.h"

#define CALL_STACK_HEIGHT 256

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: %s [BF SOURCE FILE]", argv[0]);
    exit(0);
  }

  FILE* fp = fopen(argv[1], "r");
  if (!fp) {
    fprintf(stderr, "ERR: Could not open file %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  // quick n' dirty way to get filesize from file pointer
  fseek(fp, 0L, SEEK_END);
  unsigned long sz = ftell(fp);
  rewind(fp);

  // loading file as string for easier access
  char* bf_code = (char*) calloc(sz + 1, 1); //calloc initializes to 0
  if (!bf_code) {
    fprintf(stderr, "ERR: Could not allocate a buffer for the entire source file.\n");
    exit(EXIT_FAILURE);
  }
  fread((void*) bf_code, 1, sz, fp);
  
  fclose(fp);

  // Interpreter
  ListNode* cell = initialize_list();
  unsigned long instruction_pointer = 0;
  unsigned long call_stack[CALL_STACK_HEIGHT];
  unsigned short call_stack_ptr = 0;

  while (bf_code[instruction_pointer] != 0) {
    switch(bf_code[instruction_pointer]) {
      case '+':
        increment_node(cell);
        ++instruction_pointer;
        break;
      case '-':
        decrement_node(cell);
        ++instruction_pointer;
        break;
      case '.':
        putchar(get_data(cell));
        ++instruction_pointer;
        break;
      case '<':
        if (is_prev_empty(cell))
          add_prev_node(cell);
        cell = get_prev_node(cell);
        ++instruction_pointer;
        break;
      case '>':
        if (is_next_empty(cell))
          add_next_node(cell);
        cell = get_next_node(cell);
        ++instruction_pointer;
        break;
      case '[':
        if (get_data(cell) == 0) {
          //Find matched braces
          int brace_depth = 1;
          ++instruction_pointer;
          while (brace_depth) {
            switch (bf_code[instruction_pointer]) {
              case '[':
                ++brace_depth;
                break;
              case ']':
                --brace_depth;
                break;
            }
            ++instruction_pointer;
          }
        } else {
          call_stack[call_stack_ptr++] = instruction_pointer;
          ++instruction_pointer;
        }
        break;
      case ']':
        if (call_stack_ptr == 0) {
          fprintf(stderr, "ERR: MISMATCHED [ ] @ %lu\n", instruction_pointer);
          free_entire_list(cell);
          exit(EXIT_FAILURE);
        }
        instruction_pointer = call_stack[--call_stack_ptr];
        break;
      default:
        ++instruction_pointer;
    }
  }

  free_entire_list(cell);
  return 0;
}
