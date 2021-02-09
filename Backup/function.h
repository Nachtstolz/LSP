#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <direct.h>
#include <pthread.h>
#include <sys/type.h>
#include <sys/stat.h>

typedef struct node {
	char route[255];
	struct node* link;
}Linklist;

typedef struct array {
	char dir[255];
	char node* link;
}Diclist;

//Linkedlist 함수

