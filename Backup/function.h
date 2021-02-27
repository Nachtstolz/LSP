#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/stat.h>
#include <ctype.h>
#include <time.h>

typedef struct logDetail{
	char time[16]; //일단 시간을 문자열로 저장하고자 했음
	char name[256]; //백업해야할 파일 이름
	char descript[32]; //수행 내용
	struct logDetail* link;
}LogDetail;

typedef struct node {
	char route[256];
	int period;
	int t_id;
	struct node* link;
}Linklist;

typedef struct array {
	char dir[256];
	struct node* link;
}Diclist;

typedef struct tm tm;

typedef struct thr_factor{
	Linklist* head;
	char path[256];
	char file[256];
	int period;
}Factor;
//Linkedlist 함수

