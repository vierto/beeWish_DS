#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{

	char name[105];
	int priority;
	Node *next;
	Node *prev;

}*head = NULL, *tail = NULL;

Node *newNode(char name[], int priority){

	Node *temp = (Node*)malloc(sizeof(Node));

	strcpy(temp->name, name);
	temp->priority = priority;
	
	temp->next = NULL;
	temp->prev = NULL;
	
	return temp;
}

void pushHead(char name[], int priority){
		
		Node *temp = newNode(name, priority);
		
		if(!head) head = tail = temp;
		else{
			temp->next = head;
			head->prev = temp;
			head = temp;
		}	
}

void pushTail(char name[], int priority){
	
	Node *temp = newNode(name, priority);
	
	if(!head) head = tail = temp;
	else{
		temp->prev = tail;
		tail->next = temp;
		tail = temp;
	}
}

Node *popHead(){
	if(!head){
		return NULL;
	}
	else if(head == tail){
		Node *temp = head;
		head = tail = NULL;
		
		return temp;
	}
	else{
		Node *curr = head;
		head = curr->next;
		
		head->prev = NULL;
		curr->next = NULL;
		
		return curr;
	}
	
}

Node *popTail(){
	if(!head){
		return NULL;
	}
	else if(head == tail){
		Node *temp = tail;
		head = tail = NULL;

		return temp;		
	}
	else
	{
		Node *curr = tail;
		tail = curr->prev;
		
		tail->next = NULL;
		curr->prev = NULL;
		
		return curr;
	}
}

void pushPriority(char name[], int priority){
	Node *temp = newNode(name, priority);

	if(!head) head = tail = temp;
	else{
		if(temp->priority < head->priority){
			pushHead(name, priority);
		} 
		else if(temp->priority > tail->priority){
			pushTail(name, priority);
		} 
		else{
			Node *curr = head;
			
			while(curr->next != NULL && temp->priority >= curr->priority){
				curr = curr->next;	
			}
			
			temp->next = curr;
			temp->prev = curr->prev;
			
			curr->prev->next = temp;
			curr->prev = temp;
		}
	}
}

Node *popMid(char name[]){
	if(!head){
		return NULL;
	}
	else{
		Node *curr = tail;
		
		while(curr != NULL){
			if(strcmp(curr->name, name) == 0){
				break;
			}
			curr = curr->prev;
		}
		
		if(!curr){
			return NULL;
		}
		else{
			if(curr == tail){
				popTail();
			} 
			else if(curr == head){
				popHead();
			} 
			else{
				curr->prev->next = curr->next;
				curr->next->prev = curr->prev;
				
				curr->next = NULL;
				curr->prev = NULL;
				
				return curr;
			}
		}
	}
}

void print(){
	if(!head){
		printf("Wish list is empty...\n"); getchar();
	}
	else{
		Node *curr = head;
		
		int i=1;
		
		while(curr){
			printf("%.2d. %s #%d\n", i, curr->name, curr->priority);
			i++;
			curr = curr->next;
		}
	}
}

int main(){
	
	int choose = 0;
	
	do{
		system("cls");
		printf("1. Add wish\n");
		printf("2. View wish list\n");
		printf("3. Remove wish\n");
		printf("4. Exit\n");
		printf("Please choose: ");
		scanf("%d", &choose); getchar();
		
		switch(choose){
			
			case 1:
				char name[105];
				int priority;
			
				do{
					printf("Input wish name [2..100]: ");
					scanf("%[^\n]", name); getchar();
				}while(strlen(name)<2 || strlen(name)>100);
				
				do{
					printf("Input wish priority [1..10]: ");
					scanf("%d", &priority); getchar();
				}while(priority<1 || priority>10);
				
				pushPriority(name, priority);
				
				printf("\n");
			break;
			
			case 2:
				print(); getchar();
			break;
			
			case 3:
				char nama[105];
				
				do{
					printf("Input wish name [2..100]: ");
					scanf("%[^\n]", nama); getchar();
				}while(strlen(nama)<2 || strlen(nama)>100);
				
				Node *deleted = popMid(nama);
				
				if(!deleted){
					printf("Wish not found...\n"); getchar();
				}
				else{
					printf("Success to delete wish \"%s #%d\" from download list.", deleted->name, deleted->priority); getchar();
				}
				
				free(deleted);
				deleted = NULL;
			break;
		}
	}while(choose != 4);
	
	while(head){
		popHead();
	}
	return 0;
}
