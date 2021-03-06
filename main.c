#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct t_v2{
  float x, y;
}v2;

typedef struct t_v2Node{
  v2 value;
  struct t_v2Node *next;
  struct t_v2Node *prev;
}v2Node;

v2Node *newNode(v2 value) {
  v2Node *newNode = (v2Node *)malloc(sizeof(v2Node));
  newNode->value = value;
  newNode->next = NULL;
  newNode->prev = NULL;
  return newNode;
}

void insertAtStart(v2Node **head, v2 value) {
  v2Node *new = newNode(value);
  if(head == NULL) {
    *head = new;
    return;
  }
  (*head)->prev = new;
  new->next = *head;
  *head = new;
}

void insertAtEnd(v2Node **head, v2 value) {
  v2Node *new = newNode(value);
  v2Node *temp = *head;
  if(head == NULL) {
    *head = new;
    return;
  }

  while(temp->next != NULL) temp = temp->next;
  temp->next = new;
  new->prev = temp;
}

void deleteAtStart(v2Node **head) {
  if(head == NULL)
    return;

  printf("deleting first element...\n");

  *head = (*head)->next;
  (*head)->prev = NULL;
  free((*head)->prev);
}
void deleteAtEnd(v2Node **head) {
  v2Node *temp = *head;
  if(head == NULL)
    return;

  printf("deleting last element...\n");

  while(temp->next != NULL)
    temp = temp->next;
  temp = temp->prev;
  temp->next = NULL;
  free(temp->next);
}

void freeList(v2Node *head)
{
   while (head)
    {
      v2Node* temp;
      temp = head;
      head = head->next;
      temp = NULL;
      free(temp);
    }
}

void printForward(v2Node *head) {
  v2Node *temp = head;
  printf("Forward:\n");
  while(temp != NULL) {
    printf("(%.2f, %.2f)\n", temp->value.x, temp->value.y);
    temp = temp->next;
  }
  printf("\n");
}

void printReverse(v2Node *head) {
  v2Node *temp = head;
  if(temp == NULL) return;
  while(temp->next != NULL) temp = temp->next;

  printf("Backward:\n");
  while(temp != NULL) {
    printf("(%.2f, %.2f)\n", temp->value.x, temp->value.y);
    temp = temp->prev;
  }
  printf("\n");
}

int main() {
  v2Node *newListHead = (v2Node *)malloc(sizeof(v2Node));
  newListHead = newNode((v2){0.1, 0.1});
  insertAtStart(&newListHead, (v2){0.0, 0.0});
  insertAtEnd(&newListHead, (v2){0.2, 0.2});
  insertAtStart(&newListHead, (v2){-0.1, -0.1});
  insertAtEnd(&newListHead, (v2){0.3, 0.3});

  printForward(newListHead); printReverse(newListHead);

  deleteAtStart(&newListHead);
  printForward(newListHead); printReverse(newListHead);

  deleteAtEnd(&newListHead);
  printForward(newListHead); printReverse(newListHead);

  freeList(newListHead);
  return 0;
}
