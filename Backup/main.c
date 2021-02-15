#include "function.h"

Diclist* dic = NULL;
FILE* logfile;

Linklist* GetNode(){
	Linklist* tmp;
	tmp = (Linklist*)malloc(sizeof(Linklist));
	tmp->link = NULL;
	return tmp;
}

/*Diclist* GetArray(){
	Diclist* tmp;
	tmp = (Diclist*)malloc(sizeof(Diclist));
	tmp->link = NULL;
	return tmp;
}*/

Linklist* Add(Linkedlist* head, char path[], char file[], char option[][32]){
	int idx = 0;
	FILE* fp;
	struct stat f_info;
	mode_t f_mode;
	LogDetail* put_log;

	if(strcmp(file, "\0") == 0){
		puts("Fail to add command");
		//basic 함수로 넘어가서 return 처리가 바로 될 수 있도록 조건 넣어줄 것
		return head;
	}
	// 백업해야할 파일이 존재하지 않을 때 처리
	if(fopen(file, "r") == NULL){
		puts("Fail to add command");
	}
	// 백업해야할 파일이 일반파일이 아닐 경우 처리
	int f_stat = stat(file, &f_info);
	f_mode = f_info.st_mode;
	if(!S_ISREG(f_mode)){
		puts("Fail to open file");
	}
	// 백업해야할 파일이 백업리스트에 존재하는 지 확인 후 처리
	
	//PERIOD 처리
	if(strcmp(option[0], '\0') == 0){ //PERIOD 입력 없을 시
		puts("Fail to add command");
	}
	if(isdigit(atoi(option[0])) != 0){ //int, float, double 구분해야. 아직 X
		puts("Fail to add command"); //PERIOD가 실수일 때
	do{
		if(dic[idx] == NULL) break; //특정 인덱스의 값이 없다면 break
	}while(idx++)

	dic[idx]->route = path;
	dic[idx]->link = head;
	
	while(head == NULL){
		head = GetNode();
		head->route = file;
		head->period = atoi(option[0]);
		head->link = NULL;
		
		//log 파일 게시 작업은 훗날 따로 함수를 만들어서 지정 가능성도 열어놓기
		put_log->time = 0; //로그 시간 설정
		put_log->name = file;
		put_log->descript = "added";
		//link 부분도 지정해야

		//logfile에 게시하는 작업
		fputs(, logflie);

		break;
	}
	Add(head->link, file, option);
	

	return head;
}

Linklist* Remove(Linklist* head, char path[], char file[], char option[][32]){
	//FILENAME 입력 없을 시
	if(strcmp(file, "\0") == 0){
		puts("Fail to add command");
		//basic 함수로 넘어가서 return 처리가 바로 될 수 있도록 조건 넣어줄 것
		return head;
	}
	//백업을 중단할 파일이 백업 리스트에 존재하지 않을 시(로그 파일)

	



	return head;
}


void base_print(Linklist* head, char path[256]){
	char input[256];
	int sep = 0; //separator. 공백을 단위로 나누기 위함
	char oper[8] = {0};
	char file[256] = {0};
	char option[2][32] = {0};

	print("20193058> "); //기본 프롬프트 모양
	scanf("%s" &input);
	token = strtok(input, " ");

	while(token != NULL){
		if(sep == 0){
			strcpy(oper, token);
		}
		else if(sep == 1){
			strcpy(file, token);
		}
		else if(sep == 2){
			strcpy(option[0], token);
		}
		else {
			strcpy(option[1], token);
		}
		sep++;
		token = strtok(NULL, " ");
	}

	if(strcmp(oper, "add") == 0){
		//add 명령어와 맞는 함수
	}
	else if (strcmp(oper, "remove") == 0){
		//remove 명령어와 맞는 함수
	}
	else if (strcmp(oper, "compare") == 0){
		//compare과 맞는 함수
	}
	else if (strcmp(oper, "recover") == 0){
		//recover과 맞는 함수
	}
	else if (strcmp(oper, "list") == 0){
		//list와 맞는 함수
	}
	else if (strcmp(oper, "ls") == 0){
		//system("ls");
	}
	else if (strcmp(oper, "vi") == 0){
		//system("vi");
	}
	else if (strcmp(oper, "exit") == 0){
		//exit에 맞는 함수
	}
}






int main(char argc, char *argv[]){
	system("clear");
	Linklist* head = NULL;
	Diclist* arr[32] = NULL;
	int re = 0;
	char path[256];
	struct stat dir_info;
	mode_t dir_mode;
	//FILE* logfile;

	if(logfile = fopen("./logfile", "a+") == NULL){ //a+ or ra로 읽기도 동시에 할 수 있는지..
		logfile = fopen("./logfile", "w+");
	}

	if(strchr(argv, '/') == NULL){ //상대 경로의 경우 앞에 ./ 추가
		char way1[8] = "./";
		strcat(path, way1);
		strcat(path, argv);
	}

	int dir_res = mkdir(path);
	if(argc > 2){ //인자가 2개 이상
		printf("Usage : %s", path);
		return 0;
	}

	int re_stat = stat(path, &dir_info);
	dir_mode = dir_info.st_mode;
	if(!S_ISDIR(dir_mode)){ //디렉토리 파일이 아니라면
		printf("Usage : %s", path);
	}
	
	//접근권한
	if(!S_IRWXU(dir_mode)){
		printf("Usage : %s", path);
	}

	if(dir_res != 0){
		printf("Fail to make directory");
		return 0;
	}
	while(re){
		base_print(head,path);
	}

	return 0;
}
