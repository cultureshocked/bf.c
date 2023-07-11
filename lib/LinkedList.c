#include <stdlib.h>
#include <stdio.h>

#include "LinkedList.h"

void free_forwards(ListNode* current_node);
void free_backwards(ListNode* current_node);

struct _list_node {
  ListNode* next;
  ListNode* prev;
  char data;
};

ListNode* initialize_list() {
  ListNode* return_node = (ListNode*)malloc(sizeof(ListNode));
  return_node->next = NULL;
  return_node->prev = NULL;
  return_node->data = 0;
  return return_node;
}

void free_entire_list(ListNode* current_node) {
  if (current_node->next) 
    free_forwards(current_node->next);
  
  if (current_node->prev)
    free_backwards(current_node->prev);

  current_node->next = NULL;
  current_node->prev = NULL;

  free(current_node);

  return;
}

void free_backwards(ListNode* current_node) {
  if (current_node->prev)
    free_backwards(current_node->prev);

  current_node->next = NULL;
  current_node->prev = NULL;

  free(current_node);

  return;
}

void free_forwards(ListNode* current_node) {
  if (current_node->next)
    free_forwards(current_node->next);

  current_node->next = NULL;
  current_node->prev = NULL;

  free(current_node);

  return;
}

ListNode* add_next_node(ListNode* current_node) {
  if (current_node->next) {
    fprintf(stderr, "ERR: Attempting to add a new node (forwards) in-place of a current one\n");
    free_entire_list(current_node);
    exit(EXIT_FAILURE);
  }
  ListNode* return_node = (ListNode*)malloc(sizeof(ListNode));
  return_node->next = NULL;
  return_node->prev = current_node;
  return_node->data = 0;
  current_node->next = return_node;
  return return_node;
}

ListNode* add_prev_node(ListNode* current_node) {
  if (current_node->prev) {
    fprintf(stderr, "ERR: Attempting to add a new node in-place of a current one\n");
    free_entire_list(current_node);
    exit(EXIT_FAILURE);
  }
  ListNode* return_node = (ListNode*)malloc(sizeof(ListNode));
  return_node->next = current_node;
  return_node->prev = NULL;
  return_node->data = 0;
  current_node->prev = return_node;
  return return_node;
}

int is_next_empty(ListNode* current_node) {
  return (current_node->next) ? 0 : 1;
}

int is_prev_empty(ListNode* current_node) {
  return (current_node->prev) ? 0 : 1;
}

char get_data(ListNode* current_node) {
  return current_node->data;
}

void increment_node(ListNode* current_node) {
  current_node->data += 1;
}

void decrement_node(ListNode* current_node) {
  current_node->data -= 1;
}

ListNode* get_next_node(ListNode* current_node) {
  return current_node->next;
}

ListNode* get_prev_node(ListNode* current_node) {
  return current_node->prev;
}
