#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct _list_node ListNode;

ListNode* initialize_list();
void increment_node(ListNode* current_node);
void decrement_node(ListNode* current_node);
int is_next_empty(ListNode* current_node);
int is_prev_empty(ListNode* current_node);
char get_data(ListNode* current_node);
ListNode* add_next_node(ListNode* current_node);
ListNode* add_prev_node(ListNode* current_node);
ListNode* get_next_node(ListNode* current_node);
ListNode* get_prev_node(ListNode* current_node);
void free_entire_list(ListNode* current_node);

#endif

