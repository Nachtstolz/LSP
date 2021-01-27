#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

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
char file;

int main(void){
	setbuf(stdout, NULL);

	printf("파일명(일차) : ");
	scanf("%c", &file);
	system("clear");

	Linklist list[31];
	FILE* fp_out;
	memset(list, 0, sizeof(list));
	
	//int file = 1;
	//char buffer [50000] = {0}; // 15(영단어) * (30*3)(한글뜻) * 30(단어 총 갯수)

	char way1[10] = "./";
	char way2[10] = {file};
	char way3[10] = ".dic";

	strcat(way1, way2);
	strcat(way1, way3);

	fp_out = fopen(way1, "r");
	
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
		
		buffer[strlen(buffer)-1] = '\0';

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
	int rnd = rand();
	int num = rnd%i;
	int length = strlen(list[num].data);
	char empty[16] = {0};
	for (int line = 0; line<length; line++){
		empty[line] = '_';
	}

	char head[31];
	char body[31];
	char legs[31];
	memset(head, ' ', sizeof(head));
	memset(body, ' ', sizeof(body));
	memset(legs, ' ', sizeof(legs));

	int chance = 1;
	char abc;
	int no = 0;

	while (1) {
		puts(">> 영어 단어 암기 프로그램 : 행맨 <<");
		printf("(힌트) %s %s %s\n", list[num].mean1, list[num].mean2, list[num].mean3);
		puts("-------------------------+");

		int input = 0;
		//printf("%s\n %s\n %s\n", head, body, legs);
		printf("%s\n", head);
		printf("%s\n", body);
		printf("%s\n", legs);

		if(legs[26] == '\\') break; //전체메뉴로 돌아가야
		
		puts("");
		printf("%s\n", empty);
		printf("%d번째 시도 : ", chance); //총 6번 틀리면 끝
		scanf("%c", &abc);
		getchar();

		//fflush(stdout); 버퍼문제 없음
		chance++;
		
		for(int j = 0; j<length; j++) {
			if(list[num].data[j] == abc){
				empty[j] = abc;
				input = 1;
			}
		}

		char* nul = strchr(empty,'_');
		if(nul == NULL) break;

		if(input == 0) {
			no++;
			switch (no) {
				case 1 : 
					head[25] = 'O';
					break;
				case 2 :
					body[23] = '/';
					break;
				case 3 :
					body[25] = '|';
					break;
				case 4 :
					body[27] = '\\'; //출력 잘 될까. 임의로 설정
					break;
				case 5 :
					legs[24] = '/';
					break;
				case 6 :
					legs[26] = '\\';
			}
		}
	//	sleep(2); //확인용
		system("clear");
	}
	
	puts("\t###########################\n");
	puts("\t### Congraturlations!!! ###\n");
	puts("\t###########################\n");

	//끝나면 전체메뉴로 돌아가야

	sleep(3);

	system("clear");

	return 0;

}
