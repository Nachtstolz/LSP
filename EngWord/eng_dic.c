#include "function.h"

Filelist f_list[100];

Linklist* GetNode(){
	Linklist* tmp;
	tmp = (Linklist*)malloc(sizeof(Linklist));
	tmp->link = NULL;
	return tmp;
}

Word* GetWord(){
	Word* tmp;
	tmp = (Word*)malloc(sizeof(Word));
	tmp->eng[0] = '\0';
	tmp->means[0][0] = tmp->means[1][0] = tmp->means[2][0] = '\0';
	return tmp;
}

Word* InsertWord(char eng[], char mean[][31]){
	Word* tmp;
	tmp = GetWord();
	//Linklist* tmp2 = GetNode();
	//tmp->eng = eng;
	strcpy(tmp->eng, eng);
	//tmp->means[0] = mean[0];
	strcpy(tmp->means[0], mean[0]);
	//tmp->means[1] = mean[1];
	strcpy(tmp->means[1], mean[1]);
	//tmp->means[2] = mean[2];
	strcpy(tmp->means[2], mean[2]);

	return tmp;

}
void ConnectNode(Linklist** head, Word* new){

	//Word* new;
	//new = InsertWord(new, eng, means);

	if((*head) == NULL) {		
		//Linklist* tmp = GetNode();
		//tmp->link = new;
		*head = GetNode();
		(*head)->dic = new;
		return;
	}
	ConnectNode(&(*head)->link, new);
}

void ConnectFile(Linklist** head, int num) {
	f_list[num].link = *head;
	return;
}

void FileProcessing(Linklist** head,char name[]){

	//Linklist* list[31] = {'\0'}; //Linklist 를 저장할 배열. 마지막에 리
	f_list[atoi(name)].file_num = atoi(name);
	char buffer[128]; //한 줄씩 입력받을 버퍼
	char *token; //공백을 단위로 나누기 위한 token
	int sep; //공백을 단위로 나누기 위해 필요한 separator
	int count = 0; //총 단어 개수 알기 위한 변수
	char new_eng[16] = {0};
	char new_mean[3][31] = {0};
	FILE* fp_out;

	char way1[8] = "./";
	char way2[8];
	strcpy(way2, name); //10 이후부터도 생각
	char way3[8] = ".dic";

	strcat(way1, way2);
	strcat(way1, way3);
	fp_out = fopen(way1, "r"); // open file

	if(fp_out == NULL){
		puts("Fail to open file");
		return;
	}

	while(!feof(fp_out)){
		sep = 0; //separator턴
		if(fgets(buffer, sizeof(buffer), fp_out) == NULL) break; //읽은 내용 없으면 break
		buffer[strlen(buffer)-1] = '\0'; //맨 마지막에 저장되는 '\n'을 문장을 끝내는 의미로 변경
		token = strtok(buffer," ");
		while(token != NULL){
			if(sep == 0){
				//new_eng = {token};
				strcpy(new_eng, token);
			}
			else if(sep == 1){
				//new_mean[0] = {token};
				strcpy(new_mean[0], token);
			}
			else if(sep == 2){
				//new_mean[1] = {token};
				strcpy(new_mean[1], token);
			}
			else{
				//new_mean[2] = {token};
				strcpy(new_mean[2], token);
			}
			sep++;
			token = strtok(NULL, " ");
		}
		//printf("출력"); //디버깅
		Word* new = InsertWord(new_eng, new_mean);

		//printf("인서트 완료 %s %s", new_eng, new_mean[]); //디버깅
		//printf("new의 값들 %s %s %s %s", new->eng, new->means[0], new->means[1], new->means[2]); //디버깅
		ConnectNode(head, new);
		if(count == 0) ConnectFile(head, atoi(name));
		count++;
	}

	fclose(fp_out);
	return;

}

void Output(Linklist** head){
	if(*head){
		printf("%s %s\n", (*head)->dic->eng, (*head)->dic->means[0]);
		Output(&(*head)->link);
	}
}

Linklist* Sort(Linklist* head){
	/*Linklist* n_head;
	  Linklist* tmp = NULL;
	  n_head = head;

	  while(n_head->link != NULL){
	  if(strcmp(n_head->dic->eng, n_head->link->dic->eng) > 0){
	  tmp = n_head->link;
	  n_head->link = n_head->link->link;
	  tmp->link = n_head;
	  continue;
	  }
	  n_head = n_head->link;
	  }

	  return n_head;
	 */

	Linklist* n_head;
	Linklist* tmp = NULL;
	n_head = head;

	while(n_head->link != NULL){
		if(strcmp(n_head->dic->eng, n_head->link->dic->eng) > 0){
			tmp = n_head->link;
			n_head->link = n_head->link->link;
			tmp->link = n_head;
		}
		n_head = n_head->link;
	}

	return head;

}

int first_output(Linklist** head){
	int end = 1;

	if(*head == NULL){
		end = 0;
		return end;
	}
	
	printf("%s ", (*head)->dic->means[0]);
	if(strcmp((*head)->dic->means[1], "") != 0){
		printf("%s ", (*head)->dic->means[1]);
		if(strcmp((*head)->dic->means[2], "") != 0){
			printf("%s ", (*head)->dic->means[2]);
		}
	}

	printf("-> ");
	return end;
}

void first_func(Linklist* head, int file){
	int end = 1;
	char ans[16];
	int corr = 0;
	int total = 0;
	puts(">> 영어 단어 암기 프로그램 : 영어 단어 맞추기 <<");
	while(end){
		end = first_output(&head);
		scanf("%s", ans);
		if(strcmp(ans, ".quit") == 0) break;
		int cmp = strcmp(head->dic->eng, ans);
		if(cmp == 0){
			puts("correct!");
			corr++;
			total++;
		}
		else {
			puts("incorrect!");
			total++;
		}
		head = head->link;
	}

	double score = (double)corr/(double)total * 100;
	printf("당신의 점수는 %.2lf 점입니다.\n", score);
	getchar();

	while(1) {
		char enter = getchar();
		if(enter == '\n') break;
	}
	system("clear");

	return;
}

void first_main(Linklist* head){

	char file[4];
	int pr;
	printf("파일명(일차) : ");
	scanf("%s", file);
	printf("출력 방식(알파벳 순서대로 : 1, 무작위 : 2) : ");
	scanf("%d", &pr);

	FileProcessing(&head, file); //헤드 부분 밑에처럼 바꿀거 생각

	if(pr == 1){
		head = Sort(f_list[atoi(file)].link);
	}
	else if (pr == 2){
		//Random();
		//무작위이기 때문에 어떻게 처리할지 생각중
	}

	system("clear");
	first_func(head, atoi(file));

	return;
}

void second_func(Linklist* head, int second){
	//system("clear");

	while(head != NULL){
		puts(">> 영어 단어 암기 프로그램 : 플래쉬카드 <<");
		printf("\n\t\t%s", head->dic->eng);
		sleep(second);
		system("clear");

		puts(">> 영어 단어 암기 프로그램 : 플래쉬카드 <<");
		printf("\n\t\t%s", head->dic->means[0]);
		if(strcmp(head->dic->means[1], "" )!= 0){
			printf(" %s", head->dic->means[1]);
			if(strcmp(head->dic->means[2], "") != 0){
				printf(" %s", head->dic->means[2]);
			}
		}
		sleep(second);
		system("clear");

		head = head->link;
	}
	return;
}

void second_main(Linklist* head){

	int second;
	char file[4];
	int pr;

	//Linklist* head = NULL;
	printf("속도(초) : "); scanf("%d", &second);
	printf("파일명(일차) : "); scanf("%s", file);
	printf("출력 방식(알파벳 순서대로 : 1, 무작위 : 2) : ");
	scanf("%d", &pr);

	FileProcessing(&head, file); //헤드 부분 밑에처럼 바꿀 거 생각

	if(pr == 1){
		head = Sort(f_list[atoi(file)].link); 
	}
	else if(pr == 2){
		//Random()
	}
	//printf("%s 첫번째 영단어", head->dic->eng);
	system("clear");
	second_func(head, second);
	//second_func(, second);
}

Word* printRandom(Linklist* head){
	srand(time(NULL));
	int rnd = rand();
	//char result[16] = head->dic->eng;
	Word* result = head->dic;

	Linklist* now = head;
	for(int i = 2; now!= NULL; i++){
		if(rnd%i == 0){
			result = now->dic;
			break;
		}
		now = now->link;
	}
	return result;
}

void third_func(Linklist* head){
	Word* res = printRandom(head);
	char hint[3][31] = {0};//res->means;
	char ans[16] = {0};//res->eng;
	int length = strlen(ans);
	char empty[16] = {0};

	for(int i = 0; i<length; i++){
		empty[i] = '_';
	}

	char header[31];
	char bodyer[31];
	char legser[31];

	memset(header, ' ', sizeof(header));
	memset(bodyer, ' ', sizeof(bodyer));
	memset(legser, ' ', sizeof(legser));

	int chance = 1;
	char abc;
	int fail = 0; 
	int input = 0;
	int circle = 1;
	int success = 0;

	while(circle){
		puts(">> 영어 단어 암기 프로그램 : 행맨 <<");
		printf("(힌트) %s", hint[0]);
		if(strcmp(hint[1], "") != 0){
			printf(" %s", hint[1]);
			if(strcmp(hint[2], "") != 0){
				printf(" %s", hint[2]);
			}
		}
		printf("\n");

		puts("-------------------------+");
		printf("%s\n%s\n%s\n", header, bodyer, legser);

		if(legser[26] == '\\') break;

		puts("");
		printf("%s\n", empty);
		printf("%d번째 시도 : ", chance);
		scanf("%c", &abc);

		chance++;
		for(int j = 0; j<length; j++){
			if(ans[j] == abc){
				empty[j] = abc;
				input = 1;
			}
		}

		//정답 맞췄을 경우
		success = 0;

		for(int j = 0; j<length; j++){
			if(empty[j] != '_') success++;
		}
		if(success == length) circle = 0;

		if(input == 0){
			fail++;
			switch(fail) {
				case 1:
					header[25] = 'O';
					break;
				case 2:
					bodyer[25] = '|';
					break;
				case 3 :
					bodyer[23] = '/';
					break;
				case 4 :
					bodyer[27] = '\\';
					break;
				case 5 :
					legser[24] = '/';
					break;
				case 6 :
					legser[26] = '\\';
			}
		}
		system("clear");
	}
	if(legser[26] != '\\'){
		puts("\t##########################");
		puts("\t### Congratulations!!! ###");
		puts("\t##########################");
	}

	sleep(2);
	return;
}

void third_main(Linklist* head){
	char file[4];
	printf("파일명(일차) : "); scanf("%s", file);
	system("clear");

	FileProcessing(&head, file);
	f_list[atoi(file)].link = head;
	third_func(head);

	return;
}

int main(void){
	//Linklist* list[31] = {'\0'};
	//Filelist f_list[100] = '\0';

	char n[4]; //나중에 이 부분 적용해야
	int num;
	Linklist* head = NULL;

	while(1){
		head = NULL;
		puts(">>영어 단어 암기 프로그램<<");
		puts("1. 영어 단어 맞추기\t2. 플래쉬카드");
		puts("3. 행맨(hangman)\t4. 단어장 관리");
		puts("5. 프로그램 종료\n");
		printf("번호를 선택하세요 : "); scanf("%d", &num);
		if(num == 1){
			// 1번 기능 함수로 넘어가기
			first_main(head);
		}
		else if (num == 2){
			// 2번 기능 함수로 넘어가기
			second_main(head);
		}
		else if (num == 3){
			// 3번 기능 함수로 넘어가기
		}
		else if (num == 4){
			// 4번 기능 함수로 넘어가기
		}
		else if (num == 5){ break; }
	}

	//FileProcessing(&head, n);

	//Output(&head);

	return 0;
}
