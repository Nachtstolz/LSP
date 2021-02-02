#include "function.h"

Filelist f_list[100]; //extern

void Sort(){

}

void Random(){

}

int First_output(Linkedlist** head){
	int end = 1;

	if(*head == NULL){
		end = 0;
		return end;
	}

	printf("%s ", *head->dic->means[0]);
	if(*head->dic->means[1] != '\0'){
		printf("%s ", *head->dic->means[1]);
		if(*head->dic->means[2] != '\0'){
			printf("%s ", *head->dic->means[2]);
		}
	}

	printf("-> ");

	return end;

}

void first_func(int file){
	Linkedlist* head = f_list[file].link;
	int end = 1;
	char ans[16];
	int corr = 0;
	int total = 0;
	puts(">> 영어 단어 암기 프로그램 : 영어 단어 맞추기 <<");
	while(end){
		end = First_output(&head);
		scanf("%s", ans);
		if(strcmp(ans, ".quit") == 0) break;
		int cmp = strcmp(&head->dic->eng, ans);
		if(cmp == 0){
			puts("correct!\n");
			corr++;
			total++;
		}
		else if (cmp == 1){
			puts("incorrect!\n");
			total++;
		}
		head = head->link;
	}

	


}

int main(void){

	char file[4];
	int pr;
	printf("파일명(일차) : ");
	scanf("%s", file);
	printf("출력 방식(알파벳 순서대로 : 1, 무작위 : 2) : ");
	scanf("%d", &pr);
	
	//Linkedlist* head = NULL;
	//linkedlist.c 파일 실행

	if(pr == 1){
		Sort();
		//단어들을 따로 배열에 저장한 후에 진행할지
	}
	else if (pr == 2){
		Random();
		//위와 동일
		//무작위니까 random안하고 그냥 출력해도 될까
	}
	
	first_func(atoi(file));



}



