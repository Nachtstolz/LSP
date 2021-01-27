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
	while(1) {
		puts(">>영어 단어 암기 프로그램<<");
		puts("1. 영어 단어 맞추기\t2. 플래쉬카드");
		puts("3. 행맨(hangman)\t4. 단어장 관리");
		puts("5. 프로그램 종료\n");
		printf("번호를 선택하세요: "); scanf("%d", &num);
		if(num == 1){
			//int file;
			//int pr;
			system("./menu11");
		}
		else if (num == 2){
			//int speed;
			//int file;
			//int pr;
			system("./menu2");
		}
		else if (num == 3){
			system("./menu3");
		}
		else if (num == 4){	
			system("./menu4");
		}
		else if (num == 5){ break; }
	}

	return 0;
}
