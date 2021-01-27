#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
/*
void Sort(){

	for(int i = 0; i<30; i++){
		if(strcmp(list[i].data, list[i+1].data) > 0){
			Linklist tmp  = list[i];
			list[i] = list[i+1];
			list[i+1] = tmp;
		}
	}

	return;
}
*/

int main(void){
	
	printf("파일명(일차) : ");
	scanf("%c", &file);
	printf("출력 방식(알파벳 순서대로 : 1, 무작위 : 2) : ");
	scanf("%d", &pr);
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
		
		/*
		char* n = strchr(buffer, '\n');
		if(*n == '\n') *n = '\0';
		*/

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
		printf("%s %s %s %s", list[j].data, list[j].mean1, list[j].mean2, list[j].mean3);
	}
	*/

	fclose(fp_out);
	
	//여기부터는 1번 메뉴를 위한 코드
 	//pr = 1;
	//알파벳 순서대로 / 임의의 순서대로
	if(pr == 1) { //pr은 메인에서 넘어온 값
		for(int j = 0; j < i; j++){ //list[0]에 저장된 값이 없고 밀려남. 왜?
			for(int dest = j+1; dest<=i; dest++){
				if(strcmp(list[j].data,list[dest].data) > 0) {
					Linklist tmp = list[j];
					list[j] = list[dest];
					list[dest] = tmp;
				//	printf("%s\n", tmp.data);
				}
			}

		}
	}
	else if(pr == 2){
		//상관 없음. 나중에 1, 2 이외의 숫자가 들어올 경우 생각해서 만들음
	}
	/*
	for (int m = 0; m<=i; m++){
		printf("%s %s %s %s\n", list[m].data, list[m].mean1, list[m].mean2, list[m].mean3);
	}
	*/

	puts(">>영어 단어 암기 프로그램 : 영어 단어 맞추기 <<");
	int end = 1;
	int start = 1; //일단은 list[0]이 비어있으므로 1부터 진행
	int corr = 0;
	char ans[16];

	while(end){
		printf("%s %s %s -> ",list[start].mean1, list[start].mean2, list[start].mean3); 
		scanf("%s", ans);
		if(strcmp(ans, ".quit") == 0){
			break;
		}
		int cmp = strcmp(list[start].data, ans);
		if(cmp == 0){
			printf("correct!\n");
			corr++;
		}
		else
			printf("incorrect!\n");

		start++;
		if(start == i+1){
			end = 0;
		}
	}

	double score = (double)corr/(double)(start-1) * 100; //start가 1부터 시작하므로 start => start-1로 변경
	printf("당신의 점수는 %.2lf 점입니다.\n", score);
	getchar();

	while(1) {
		char enter = getchar();
		if(enter == '\n') break;
	}
	system("clear");
	//enter 입력하면 초기 메뉴로 넘어가는 부분 필요
	return 0;

}
