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

LogDetail* GetLog(){
	LogDetail* tmp;
	tmp = (LogDetail*)malloc(sizeof(LogDetail));
	tmp->link = NULL;
	return tmp;
}

void Addlog(LogDetail* lhead, char file[]){ //로그파일에 로그 추가
	
	if(lhead == NULL){
		lhead = GetLog();
		lhead->time = 0; //시간 스레드 이용해야. 임의로 0 설정.
		lhead->name = file;
		lhead->descript = "added";
		return;
	}
	Addlog(lhead->link, file);
	// 로그 파일에 해당 연결리스트를 작성하는 것은 돌아가서 진행하는 걸로.
}

void Editlog(LogDetail* lhead){ //로그파일에 recover명령어로 인한 로그
	if(lhead == NULL){
		lhead = GetLog();
		lhead->time = 0; //시간 스레드 사용해야. 임의로 0 설정.
		lhead->name = file;
		strcat(lhead->name, lhead->time);
		lhead->descript = "getnerated";
		return;
	}
	Editlog(lhead->link, file);
}

void Removelog(LogDetail* lhead, char file[]){ //로그파일에 로그 삭제
	
	if(lhead == NULL){
		lhread = GetLog();
		lhead->time = 0; //시간 스레드 이용해야. 임의로 0 설정.
		lhead->name = file;
		lhead->descript = "deleted";
		return;
	}
	Removelog(lhead->link, file);
}

void Insertlog(LogDetail* lhead){
	if(lhead == NULL){
		return;
	}
	/*
	char new[512];
	char n_time[32];
	n_time[0] = "[";
	strcat(n_time, lhead->time);
	strcat(n_time, "]");
	
	strcat(new, n_time);
	strcat(new, " ");
	strcat(new, lhead->name);
	strcat(new, " ");
	strcat(new, lhead->descript);
	*/
	fprintf(logfile, "[%s] %s %s", lhead->time, lhead->name, lhead->descript);

	//fputs(new, logfile);
	
	Insertlog(lhead->link);
}

int CheckFile(LogDetail* lhead, char cm_file[]){
	if(lhead == NULL){
		return 1;
	}
	if(strcmp(lhead->file, cm_file) == 0) { return 0; }
	CheckFile(lhead->link, cm_file);
}

Linklist* Add(Linkedlist* head, LogDetail* lhead, char path[], char file[], char option[][32]){
	int idx = 0;
	FILE* fp;
	struct stat f_info;
	mode_t f_mode;
	//LogDetail* put_log;

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
	if(CheckFile(lhead, file) == 1){
		puts("Fail to open file");
	}

	//PERIOD 처리
	if(strcmp(option[0], '\0') == 0){ //PERIOD 입력 없을 시
		puts("Fail to add command");
	}
	if(((float)atoi(option[0])) % 1.0 > 0){ 
		puts("Fail to add command"); //PERIOD가 실수일 때
	}

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
		
		//logfile에 게시하는 작업
		//함수로 넘겨서 진행할 것. 함수 명시해야.
		Addlog(lhead, file);

		//fputs(lhead, logflie);
		// 연결리스트를 그대로 fputs하는 것이 불가능하기 때문에 넣는 함수를 임의로 만들어주는 방법 생각
		Insertlog(lhead);

		break;
	}
	Add(head->link, lhead, path, file, option);
	

	return head;
}

Linklist* Remove(Linklist* head, LogDetail* lhead, char path[], char file[], char option[][32]){
	//FILENAME 입력 없을 시
	if(strcmp(file, "\0") == 0){
		puts("Fail to remove command");
		//basic 함수로 넘어가서 return 처리가 바로 될 수 있도록 조건 넣어줄 것
		return head;
	}
	//백업을 중단할 파일이 백업 리스트에 존재하지 않을 시(로그 파일)
	if(CheckFile(lhead, file) == 1){
		puts("Fail to remove command");
	}
	
	if(strcmp(head->link->route, file) == 0){
		//head->link = head->link->link;
		Linklist* tmp = NULL;
		tmp = head->link;
		head = tmp->link;
		free(tmp);
		//잘 작동하는지 확인할 필요 있음.

		Removelog(lhead, file);
		Insertlog(lhead);
	}

	Remove(head->link, lhead, path, file, option);

	return head;
}

void Compare(Linklist* head, char path[], char file[], char option[][32]){ //compare 명령어에 대한 함수

	struct stat file1_info;
	struct stat file2_info;

	file1_info.st_mtime

}

void List(Linklist* head){ //list 명령어에 대한 함수
	if(head == NULL) return;
	
	printf("%s %s", head->route, head->period);
	List(head->link);
}

void base_print(Linklist* head, char path[256], LogDetail* lhead){
	char input[256];
	int sep = 0; //separator. 공백을 단위로 나누기 위함
	char oper[8] = {0};
	char file[256] = {0};
	char option[2][32] = {0};

	print("20193058> "); //기본 프롬프트 모양
	fgets(input, sizeof(input), stdin); //fgets로 받는 것이 더 좋음
	input[strlen(input) - 1] = '\0';
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
	LogDetail* lhead = NULL;
	Diclist* arr[32] = NULL;
	int re = 0;
	char path[256];
	struct stat dir_info;
	mode_t dir_mode;
	//FILE* logfile;

	if(logfile = fopen("./logfile", "w+") == NULL){ //a+ or ra로 읽기도 동시에 할 수 있는지..
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
		base_print(head, path, lhead);
	}

	return 0;
}
