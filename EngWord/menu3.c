#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct node {
	char data[16];
	char mean1[31];
	char mean2[31];
	char mean3[31];
	//struct node* link;
} Linklist;
/*
Linklist* GetNode(){
	Linklist* tmp;
	tmp = (Linklist*)malloc(sizeof(Linklist));
	tmp->link = NULL;
	return tmp;
}
*/
int pr;
Linklist list[31];

int main(void){
	
	Linklist list[31];
	FILE* fp_out;
	memset(list, 0, sizeof(list));
	
	//int file = 1;
	//char buffer [50000] = {0}; // 15(영단어) * (30*3)(한글뜻) * 30(단어 총 갯수)

	fp_out = fopen("./1.dic", "r");
	
	if(fp_out == NULL){
		printf("Fail to open file");
		return 0;
	}
	char buffer[1351];
	char *token;
	int sep = 0;
	int i = 0;

	while(!feof(fp_out)) {
		sep = 0;
		//char buffer[1351];
		if(fgets(buffer, sizeof(buffer), fp_out)== NULL) break;
		
		char* n = strchr(buffer, '\n');
		if(*n == '\n') *n = '\0';

		token = strtok(buffer, " ");
		while(token != NULL) {
			if (sep == 0){
				strcpy(list[i].data, token);
			}
			else if (sep == 1){
				strcpy(list[i].mean1, token);
			}
			else if (sep == 2){
				strcpy(list[i].mean2, token);
			}
			else {
				strcpy(list[i].mean3, token);
			}
			sep++;
			token = strtok(NULL, " ");
		}
		i++;
	}

/*	
	for (int j = 0; j<i; j++){
		printf("%s %s %s %s\n", list[j].data, list[j].mean1, list[j].mean2, list[j].mean3);
	}
*/
	fclose(fp_out);
	
	//여기부터는 3번 메뉴를 위한 코드
	//랜덤 진행 -> rand써줘야하는 것 잊지 말기. srand든 뭐든
	srand((int)time(NULL));
	puts(">>영어 단어 암기 프로그램 : 행맨  <<");
	int rnd = rand();
	int num = rnd%i;
	printf("(힌트) %s %s %s\n", list[num].mean1, list[num].mean2, list[num].mean3);
	int length = strlen(list[num].data);
	char empty[16];
	for (int line = 0; line<length; line++){
		empty[line] = "_";
	}
	puts("-----------------------+");
	// 그림이 추가되는 부분 필요. 이 공간을 임의로 비웠다가 바꿀 수 있을까?

	printf("%s", empty);
	for(){
		printf("%d번째 시도 : ");
	}

	return 0;

}
