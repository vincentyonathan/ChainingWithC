#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#define max 26
FILE *input; //mengakses file input
FILE *search; //mengakses file search
FILE *output; //mengakses file output

struct tnode{
	int key;
	char name[100];
	int id;
	struct tnode *next;
};

struct hashPool{
	struct tnode *head;
	struct tnode *tail;
};

struct hashPool hashTable[max];

void init(){
	for(int i = 0; i < max; i++){
		hashTable[i].head = NULL;
		hashTable[i].tail = NULL;
	}
}

int generateKey(char name[]){
	int key = 0;
	key = name[0] - 'A';
	return key;
}

struct tnode *newnode(char name[], int id){
	struct tnode *curr = (struct tnode *) malloc (sizeof(struct tnode));
	
	curr->key = generateKey(name);
	strcpy(curr->name, name);
	curr->next = NULL;
	curr->id = id;
	return curr;
}

void insertChaining(struct tnode *node){
	if(hashTable[node->key].head == NULL){
		hashTable[node->key].head = hashTable[node->key].tail = node;
	}
	else{
		hashTable[node->key].tail->next = node;
		hashTable[node->key].tail = node;
	}
}

void printChaining(){
	for(int i = 0; i < max; i++){
		printf("[%d] : ", i);
		
		struct tnode *temp = hashTable[i].head;
		
		while(temp != NULL){
			printf("%s->", temp->name);
			temp = temp->next;
		}
		puts("");
	}
	puts("");
}

void searchData(){
	char find[200];
	int idtemp;
	search = fopen("search.txt","r");
	output = fopen("output.txt","w");
	clock_t t; 
    double time_taken;
	t = clock(); 
	while(fscanf(search,"%s %d",find,&idtemp)!=EOF)
	{
		int findIdx = generateKey(find);
		struct tnode *curr = hashTable[findIdx].head;
		while(curr != NULL){
			if(strcmp(curr->name, find) == 0){
				if(curr->id == idtemp){
					fprintf(output,"Data is valid in index %d\n", findIdx);
					break;
				}
				else{
					curr = curr->next;
				}
			}
			else{
				curr = curr->next;
			}
		}
		if(curr == NULL){
			fprintf(output,"INVALID : Data not found\n");
		}
	}
	t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("The time for this searching require	: %f seconds\n", time_taken);
    puts("Done.");
	puts("");
}


int main(){
	char name[200];
	int id=1;
	init();	
	
	int command;
	puts("WELCOME TO VY's DATABASE");
	puts("========================");
	
	do{	
		puts("Command List :");
		puts("1. Insert Data");
		puts("2. Search Data");
		puts("3. Print All Data");
		puts("4. Exit");
		printf("Input number : ");
		scanf("%d", &command);
//		printf("%d\n", command);
		getchar();
		
		switch(command){
			case 1:
				input = fopen("input.txt","r");
				while(fscanf(input,"%s", name)!=EOF){
//					printf("%s\n",name);
					insertChaining(newnode(name, id));
					id++;
				}
				puts("Data successfully added");
				puts("");
				break;
			case 2:
				printf("Searching . . .\n");
				searchData();
				break;
			case 3:
				printChaining();
				break;
		}
				
		
	}while(command != 4);
	
	return 0;
}
