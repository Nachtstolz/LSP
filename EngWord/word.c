#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	int data;
	struct node* link;
}Linklist;

Linklist* GetNode(){
	Linklist* tmp;
	tmp = (Linklist*)malloc(sizeof(Linklist));
	tmp->link = NULL;
	return tmp;
}

int num;
int file;
int pr;
int speed;

int main(void){

	//int num;

	puts(">>영어 단어 암기 프로그램<<");
	puts("1. 영어 단어 맞추기\t2. 플래쉬카드");
	puts("3. 행맨(hangman)\t4. 단어장 관리");
	puts("5. 프로그램 종료\n");
	printf("번호를 선택하세요: "); scanf("%d", &num);
	if(num == 1){
		//int file;
		//int pr;
		printf("파일명(일차) : "); scanf("%d",&file);
		printf("출력 방식(알파벳 순서대로 : 1, 무작위 : 2) : ");
		scanf("%d",&pr);
		fopen("./menu1.c", "r");
	}
	else if (num == 2){
		//int speed;
		//int file;
		//int pr;
		printf("속도(초) : "); scanf("%d", &speed);
		printf("파일명(일차) : "); scanf("%d", &file);
		printf("출력 방식(알파벳 순서대로 : 1, 무작위 : 2) : ");
		scanf("%d",&pr);
	}
	else if (num == 3){

	}
	else if (num == 4){

	}
	else if (num == 5){ return 0; }

	return 0;
}
