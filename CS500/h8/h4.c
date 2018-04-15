/* 6 points */
#include <stdio.h>
#include <stdlib.h>

/**
 * Define the struct node structure: (1/2 point)
 */

struct node {
  
  int data;
  struct node * next;
  
} ;

/**
 * Creates a new linked list node storing the data value in the node, it should
 * return the pointer to the allocated node. (1/2pt)
 */
struct node *newnode(int data)
{
  struct node * new = malloc(sizeof(struct node));
  
  new->data = data;
  new->next = NULL;
  
  return new;

}

/**
 * Should allocate and insert a node into the linked list given by the pointer
 * to the head element.  The head pointer is a double pointer so you can modify
 * the original head pointer (i.e. using (*head = x) will change what the head
 * pointer points at.) Insert the new node into the list where it belongs in
 * the list. (2pts)
 */

void insert(struct node **head, int data)
{
  struct node * curr;
  struct node * new = newnode(data);
  if(*head == NULL || (*head)->data >= data){ // if new element should be the new head
    
    new->next = *head;
    *head = new;
  }else{
   
    curr = *head;
    while(curr->next != NULL && curr->next->data < data){ // find the place to be inserted
      
      curr = curr->next;
    }
    
    new->next=curr->next;
    curr->next = new;
    
  }
 
}

/**
 * This should find and delete the node with the same data value. The node
 * should then be freed. (2pts)
 */
void delete(struct node **head, int data)
{
  
  struct node * curr;
  struct node * temp;
  if((*head)->data == data){
    temp = *head;
    *head = temp->next;
    free(temp);
  }else{
   
    curr = *head;
    while(curr->next != NULL && curr->next->data != data){ // find the place to be inserted
      
      curr = curr->next;
    }
    
    temp = curr->next;
    curr->next = temp->next;
    free(temp);
    
  }
}

/**
 * This function is given a head node to the linked list.  Print data value for
 * every element in the list in the order in which they occur in the list.
 * (1pt)
 */
void print(struct node *head)
{
  if(head == NULL) return;
  
  printf("%d\n", head->data);
  print(head->next);

}

// free the list after done
void freeList(struct node **head)
{
  if(*head == NULL) return;
  struct node * temp = * head;
  head = &(*head)->next;
  free(temp);
  freeList(&(*head)); 
}

/**
 * Do not modify main below: Fill in the above functions to make the program 
 * below work. Do not make your own head variable.
 * Expected output for h4:
 * 3
 * 5
 * 11
 * 19
 * 23
 * 41
 * 43
 */
int main(int argc, char *argv[])
{
  int nums[] = {5,23,13,11,2,37,47,3,43,19,29,7,17,31,41,-1};
  int remove[] = {17,2,47,29,31,37,7,13,-1};
  struct node *head = NULL;
  int i;

  for(i=0; nums[i] >= 0; i++) insert(&head, nums[i]);
  for(i=0; remove[i] >= 0; i++) delete(&head, remove[i]);
  print(head);
  
  freeList(&head);
  
  return 0;
}
