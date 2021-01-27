#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char data[16];
	char mean1[31];
	char mean2[31];
	char mean3[31];
} Linklist;

int speed;
char file;
int pr;
Linklist list[31];

int main(){
	setbuf(stdout, NULL);

	printf("속도(초) : ");
	scanf("%d", &speed);
	getchar();
	printf("파일명(일차) : ");
	scanf("%c", &file);
	getchar();
	printf("출력 방식(알파벳 순서대로 : 1, 무작위로 : 2) : ");
	scanf("%d", &pr);
	getchar();
	system("clear");

	Linklist list[31];
	//fopen 및 fgets 또는 fscanf
	FILE* fp_out;
	memset(list, 0, sizeof(list));

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
		if(fgets(buffer, sizeof(buffer), fp_out) == NULL) break;

		char* n = strchr(buffer, '\n');
		if(*n == '\n') *n = '\0';

		token = strtok(buffer, " ");
	//단어들을 linkedlist형태로 저장했다고 가정
		while(token != NULL) {
			if(sep == 0) {
				strcpy(list[i].data, token);
			}
			else if (sep == 1) {
				strcpy(list[i].mean1, token);
			}
			else if (sep == 2) {
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
	
	fclose(fp_out);
	// 파일 내용 읽는 부분 끝

	//pr = 2; //임의로 지정
	if(pr == 1) {
		//sort 진행
		for(int j = 0; j<i; j++){
			for(int dest = j+1; dest<=j; dest++){
				Linklist tmp = list[j];
				list[j] = list[dest];
				list[dest] = tmp;
			}
		}
		//printf("정렬 완료");
	}
	else if (pr == 2){
		//그냥 넘어가기
	}
/*
	for(int k = 0; k<i; k++){
		printf("%s %s %s %s\n", list[k].data, list[k].mean1, list[k].mean2, list[k].mean3);
	}
*/

	//puts(">>영어 단어 암기 프로그램 : 플래쉬카드 <<");
	for(int start = 0; start<i; start++){ //list[1]부터 작성된 점 반영해야함..
		if(list[start].data == NULL){
			break;
			//메뉴(초기) 화면으로 돌아가려면 return을 해야할까 또는 해당 메뉴 파일을 열어야할까?
		}
		puts(">>영어 단어 암기 프로그램 : 플래쉬카드 <<\n");
		printf("%s", list[start].data);
		sleep(speed); // speed 대신 2을 임의로 넣음
		system("clear");

		puts(">>영어 단어 암기 프로그램 : 플래쉬카드 <<\n");
		printf("%s %s %s", list[start].mean1, list[start].mean2, list[start].mean3); // 뜻은 한 번에 세 개 다 보여주기
		sleep(speed); // speed 대신 2을 임의로 넣음
		system("clear");
	
	}
	
	system("clear"); //하고 메뉴 창 오픈
	return 0;

}
