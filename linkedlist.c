#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int value;
	struct node *previous;
	struct node *next;
} node;

// Possible solutions to maybe implement in future:
// store list size and an end pointer so we can iterate
// faster through the list for bigger and bigger list sizes.
node * start = NULL;

void create(int value) {
	start = malloc(sizeof(node));
	*start = (node) {value, 0, 0};
}

// Θ(1) time complexity function since the start address is already mapped.
void insert_start(int value) {
	if (NULL == start) return;

	// Allocate memory for the new node
	node *new_head = malloc(sizeof(node));
	*new_head = (node) {value, 0, start};
	
	// Substitutes the head with the new head by pointing the old
	// value previous pointer to the new value.
	start->previous = new_head;
	start = new_head;
}

// This insertion has always Θ(n) time complexity since it needs
// to run through all list to find its last node. It is recommended
// to use the insert_start function if running time is important.
void insert_end(int value) {
	if (NULL == start) return;

	node * current_node = start;
	while (NULL != current_node->next) {
		current_node = current_node->next;
	}
	current_node->next = malloc(sizeof(node));
	*current_node->next = (node) {value, current_node, NULL};
}

// This insertion has a worst running time of Θ(n) cycles and best of Θ(1),
// but the average still is Θ(n).
void insert_pos(int value, int index) {
	if (NULL == start) return;
	if (index == 0) {
		insert_start(value);
		return;
	}

	node * current_node = start;
	for (int i = 0; i < index; i++) {
		if (NULL != current_node->next) current_node = current_node->next;
		else {
			insert_end(value);
			return;
		};
	}
	node * new_node = malloc(sizeof(node));
	*new_node = (node) {value, current_node->previous, current_node};

	current_node->previous->next = new_node;
	current_node->previous = new_node;
}

// The find function has time complexity of Θ(n) at average.
node * find(int index) {
	if (NULL == start) return NULL;

	node* current_node = start;
	for (int i = 0; i < index; i++) {
		if (NULL != current_node->next) current_node = current_node->next;
		else return NULL;
	}
	return current_node;
}

void display() {
	if (NULL == start) return;

	printf("\n//-----------------------\n// Values: ");

	node* current_node = start;
	printf(" %d ", current_node->value);
	while (NULL != current_node->next) {
		current_node = current_node->next;
		printf(" %d ", current_node->value);
	}

	printf("\n//-----------------------\n");
}

// The delete functions follow the same time complexity from
// the insert ones.

void delete_pos(int index) {
	if (NULL == start) return;

	// Find the node for the given index
	node *current_node = start;
	for (int i = 0; i < index; i++) {
		if (NULL != current_node->next) current_node = current_node->next;
		else return;
	}

	// Disconnects current node from list by linking its previous
	// with its next, making itself unavailable for iteration.
	if (NULL != current_node->previous) {
		current_node->previous->next = current_node->next;
	}
	if (NULL != current_node->next) {
		current_node->next->previous = current_node->previous;
	}
	// free the memory allocation in append function.
	free(current_node);
}

void delete_start() {
	if (NULL == start) return;

	start->next->previous = NULL;
	free(start);
}

void delete_end() {
	if (NULL == start) return;

	node * current_node = start;
	while (NULL != current_node->next) {
		current_node = current_node->next;
	}

	current_node->previous->next = NULL;
	free(current_node);
}

int main() {
	int choice;
	int value;
	int position;
	while(1){
		printf("Choose: \n");
		printf("1.Create\n");
		printf("2.Find\n");
		printf("3.Display\n");
		printf("4.Insert at the beginning\n");
		printf("5.Insert at the end \n");
		printf("6.Insert at specified position\n");
		printf("7.Delete from beginning\n");
		printf("8.Delete from the end\n");
		printf("9.Delete from specified position\n");
		printf("10.Exit\n");
		printf("Enter your choice: ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				printf("Enter the value: ");
				scanf("%d", &value);
				create(value);
				break;
			case 2:
				printf("Enter the position: ");
				scanf("%d", &position);
				node * found_node = find(position);
				if (NULL != found_node) printf("\n//-----------------------\n// Value: %d\n//-----------------------\n", found_node->value);
				else printf("\n//-----------------------\n// Value not found in position!\n//-----------------------\n");
				break;
			case 3:
				display();
				break;
			case 4: 
				printf("Enter the value: ");
				scanf("%d", &value);
				insert_start(value);
				break;
			case 5:
				printf("Enter the value: ");
				scanf("%d", &value);
				insert_end(value);
				break;
			case 6:
				printf("Enter the value: ");
				scanf("%d", &value);
				printf("Enter the position: ");
				scanf("%d", &position);
				insert_pos(value, position);
				break;
			case 7:
				delete_start();
				break;
			case 8:
				delete_end();
				break;
			case 9:
				printf("Enter the position: ");
				scanf("%d", &position);
				delete_pos(position);
				break;
			case 10:
				exit(0);
				break;
			default:
				printf("Wrong Choice");
				break;
		}
	}

	return 0;
}
