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

void Addlog(LogDetail* lhead, char file[], tm* td){ //로그파일에 로그 추가
	
	if(lhead == NULL){
		lhead = GetLog();
		int tmp_time[16];
		sprintf(tmp_time, "%d%d%d%d%d%d", td->tm_year%100, td->tm_mon+1, td->tm_mday, td->tm_hour, td->tm_min, td->tm_sec);
		lhead->time = tmp_time; //시간 스레드 이용해야. 임의로 0 설정.
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
		int tmp_time[16];
		sprintf(tmp_time, "%d%d%d%d%d%d", td->tm_year%100, td->tm_mon+1, td->tm_mday, td->tm_hour, td->tm_min, td->tm_sec);
		lhead->time = tmp_time;
		strcat(file, lhead->time);
		lhead->name = file;
		lhead->descript = "getnerated";
		return;
	}
	Editlog(lhead->link, file);
}

void Removelog(LogDetail* lhead, char file[]){ //로그파일에 로그 삭제
	
	if(lhead == NULL){
		lhread = GetLog();
		int tmp_time[16];
		sprintf(tmp_time, "%d%d%d%d%d%d", td->tm_year%100, td->tm_mon+1, td->tm_mday, td->tm_hour, td->tm_min, td->tm_sec);
		lhead->time = tmp_time;
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

void Copy(char path[], char file[]){
	FILE* ft = fopen(file, "r");
	FILE* nf = fopen(); //파일명 지정 방법 찾아
	while(1){
		int c = getc(ft);
		if(!feof(ft)){
			fputc(c, nf);
			fseek(ft, 1, SEEK_CUR);
		}else break;
	}
	fclose(ft);
	fclose(nf);

	return;
}

Linklist* Add(Linkedlist* head, LogDetail* lhead, char path[], char file[], char option[][32]){
	time_t tt;
	tm *td;
	int idx = 0;
	//FILE* fp;
	struct stat f_info;
	mode_t f_mode;
	//LogDetail* put_log;

	td = localtime(&tt);
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
	//lhead -> head로 변경해서 진행해야할 것으로 판
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
야
	do{
		if(dic[idx] == NULL) break; //특정 인덱스의단 값이 없다면 break
	}while(idx++)

	dic[idx]->route = path;
	dic[idx]->link = head;
	
	while(head == NULL){
		head = GetNode();
		head->route = file;
		head->period = atoi(option[0]);
		head->link = NULL;
		
		//백업 진행
		Copy(path, file); //파일을 복사하는 작업을 함수로
		
		//logfile에 게시하는 작업
		//함수로 넘겨서 진행할 것. 함수 명시해야.
		Addlog(lhead, file, td);

		//fputs(lhead, logflie);
		// 연결리스트를 그대로 fputs하는 것이 불가능하기 때문에 넣는 함수를 임의로 만들어주는 방법 생각
		Insertlog(lhead);

		break;
	}
	Add(head->link, lhead, path, file, option);
	

	return head;
}

void Delete(char path[], char file[]){
	// 디렉터리 즉, path 오픈
	DIR *dir = NULL;
	struct dirent *file = NULL;

	dir = opendir(path);
	while((file = readdir(dir)) != NULL){
		if(file->d_name == ){ //file의 경로에 있는 파일명만 활용해서 같은지 확인
			unlink(); //삭제할 대상이 될 파일경로
		}
	}

	return;
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

		//백업 디렉토리에 영향을 미치는 함수
		Delete(path, file);

		//로그에 대한 함수들
		Removelog(lhead, file);
		Insertlog(lhead);
	}

	Remove(head->link, lhead, path, file, option);

	return head;
}

void Compare(Linklist* head, char path[], char file[], char option[][32]){ //compare 명령어에 대한 함수

	int comp1 = 0;
	int comp2 = 0;
	struct stat file1_info;
	struct stat file2_info;
	
	//입력 인자가 2개가 아닌 경우
	if(file == NULL || option == NULL){ //NULL로 안될 것 같아서 나중에 봐야
		puts("Fail to compare command");
	}

	//파일이 존재하지 않을 경우
	if(fopen(file, "r") == NULL){
		puts("Fail to compare command");
	}
	if(fopen(option[0], "r") == NULL){
		puts("Fail to compare command");
	}

	//일반 파일이 아닐 경우
	int f1_stat = stat(file, &file1_info);
	int f2_stat = stat(option[0], &file2_info);
	mode_t f1_mode = file1_info.st_mode;
	mode_t f2_mode = file2_info.st_mode;

	if(!S_ISREG(f1_mode)){
		puts("Fail to compare command");
	}
	if(!S_ISREG(f2_mode)){
		puts("Fail to compare command");
	}

	if(file1_info.st_mtime == file2_info.st_mtime){
		comp1 = 1;
	}

	if(file1_info.st_size == file2_info.st_size){
		comp2 = 1;
	}

	if(comp1 == 1 && comp2 == 1){
		puts("File1 = File2");
	}
	else {
		printf("File1 : mtime : %s, 파일 크기 : %lld bytes", file1_info.st_mtime, file1_info.st_size);
		printf("File2 : mtime : %s, 파일 크기 : %lld bytes", file2_info.st_mtime, file2_info.st_size);
	}

	return;

}

void List(Linklist* head){ //list 명령어에 대한 함수
	if(head == NULL) return;
	
	printf("%s %s", head->route, head->period);
	List(head->link);
}

void Ls(){ //argv를 사용하거나 함수에 들어오기 전 공백을 단위로 나누어서 인자 저장하는 방법으로 진행하기
	DIR* dir = NULL;
	struct dirent *file = NULL;
	
	char path[256];
	gets(path)
	dir = opendir(path);
	
	while(file = readdir(dir) != NULL){
		//readdir 읽혀진 파일명 중 현재 디렉토리를 나타내는 . 도 포함되어있기에 무한 반복에 빠지지 않으려면 .과 ..일 경우 skip 해야한다고 함.
		if(strcmp(file->d_name, "." == 0) || strcmp(file->d_name, ".." == 0)){
			continue;
		}

		printf("%s ", file->d_name);

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
			char tmp[256];
			strcpy(tmp, token);
			if(strchr(tmp, '/') == NULL){
				char *buf;
				char buffer[256];
				getcwd(buffer, sizeof(buffer));
				sprintf(file, "%s%s", buffer, tmp);
			//strcpy(file, token);
			if(strchr(file, '\0') == NULL){
				puts("Fail to input file_name");
				return; //파일명 255 넘었을 경우 에러메세지
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
	int re = 0; //전역으로 선언해야할 듯
	char path[256];
	struct stat dir_info;
	mode_t dir_mode;
	//FILE* logfile;

	if(logfile = fopen("./logfile", "w+") == NULL){ //a+ or ra로 읽기도 동시에 할 수 있는지..
		logfile = fopen("./logfile", "w+");
	}

	if(strchr(argv, '/') == NULL){ //상대 경로의 경우 현재 경로 앞에 추가
		char way1[256];
		getcwd(way1, sizeof(way1);
		sprintf(path, "%s%s", way1, argv);
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
