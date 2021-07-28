#include <stdio.h>
#include <stdlib.h>

struct AdjacencyList{
	char vertex;
	struct AdjacencyList* next;
};

struct Queue
{
	char* vertex;
	int front;
	int end;
	unsigned size;
};


struct AdjacencyList* newNode(char child){
	struct AdjacencyList* temp = (struct AdjacencyList*)malloc(sizeof(struct AdjacencyList));
	temp->vertex = child;
	temp->next = NULL;

	return temp;
}

void insert(struct AdjacencyList* array[], int index, char child){

	struct AdjacencyList* temp = newNode(child);
	temp->next = array[index];
	array[index] = temp;

}


struct Queue* CreateQueue(int size){

	struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));

	queue->size = size;
	queue->front = -1;
	queue->end = -1;

	queue->vertex = (char*)malloc(queue->size * sizeof(char));

	return queue;
}


int isEmpty(struct Queue* queue){
	return (queue->front == -1);
}

void push(struct Queue* queue,  char value){
	if(isEmpty(queue)){
		queue->front = queue->end =0;
	}

	else queue->end++;

	queue->vertex[queue->end] = value;
}

char pop(struct Queue* queue){
	if(isEmpty(queue)) return '\0';

	char vertex = queue->vertex[queue->front];
	queue->front++;

	if(queue->front >queue->end) queue->front = queue->end = -1;

	return vertex;
}

int sourceToIndex(char character){
	return (character-'A');
}

void BFS(struct AdjacencyList* array[], int size, char source, int* inBFSTree){

	struct Queue* queue = CreateQueue(size);
	
	int index = sourceToIndex(source);
	push(queue, source);

	inBFSTree[index] = 1;

	while(!isEmpty(queue)){
		char parrent = pop(queue);
		index = sourceToIndex(parrent);
		struct AdjacencyList* temp = array[index];


		printf("%c->", parrent);
		while(temp != NULL){
			char child = temp->vertex;
			int tempIndex = sourceToIndex(child);
			if(!inBFSTree[tempIndex]){
				push(queue, child);
				inBFSTree[tempIndex] = 1;
			}

			temp = temp->next;
		}
	}

	printf("NULL\n");
}

int main(int argc, char const *argv[])
{

	int size=9;
	printf("Enter the number of vertices: \n");
	scanf("%d", &size);
	struct AdjacencyList* array[8] = {0};

	printf("Is is a directed Graph? 1/0? \n");
	int isDirected;
	scanf("%d", &isDirected);

	int choice = 1;

	while(choice == 1){
		printf("Enter the parrent and child(in upper Case): \n");
		char parrent, child;
		scanf(" %c %c", &parrent, &child);
		int index1 = parrent - 'A';
		insert(array, index1, child);

		if(!isDirected){
			int index2 = child - 'A';
			insert(array, index2, parrent);
		}
		
		printf("Want to continue:1/0 ? \n");
		scanf("%d", &choice);
	}


	printf("\nThe BFS Tree is: \n");
	int inBFSTree[8] = {0};

	printf("Enter the source: \n");

	char source;
	scanf(" %c", &source);
	BFS(array, size, source, inBFSTree);	


	return 0;
}