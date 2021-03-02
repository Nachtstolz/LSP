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
/*
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
*/
void Addlog2(char file[], int start){ //스레드 함수 내에 쓰일 add로그
	time_t tt;
	tm* td;

	FILE* fp;
	fp = fopen("./logfile", "a+");
	
	time(&tt);
	td = localtime(&tt);
	int td_year = td->tm_year%100;
	int td_mon = td->tm_mon+1;
	int td_day = td->tm_mday;
	int td_hour = td->tm_hour;
	int td_min = td->tm_min;
	int td_sec = td->tm_sec;

	char log[512];
	char edit_file[32];
	if(start == 1){
		sprintf(log, "[%d%d%d %d%d%d] %s %s", td_year, td_mon, td_day, td_hour, td_min, td_sec, file, "added");
	}
	else{
		sprintf(edit_file, "%d%d%d%d%d%d", td_year, td_mon, td_day, td_hour, td_min, td_sec);
		sprintf(log, "[%d%d%d %d%d%d] %s_%s %s", td_year, td_mon, td_day, td_hour, td_min, td_sec, file, edit_file, "generated");
	}

	return;
}

/*
void Editlog(LogDetail* lhead){ //로그파일에 recover명령어로 인한 로그
	if(lhead == NULL){
		lhead = GetLog();
		int tmp_time[16];
		sprintf(tmp_time, "%d%d%d%d%d%d", td->tm_year%100, td->tm_mon+1, td->tm_mday, td->tm_hour, td->tm_min, td->tm_sec);
		lhead->time = tmp_time;
		strcat(file, lhead->time);
		lhead->name = file;
		lhead->descript = "generated";
		return;
	}
	Editlog(lhead->link, file);
}
*/

/*
void Removelog(LogDetail* lhead, char file[]){ //로그파일에 로그 삭제
	
	if(lhead == NULL){
		lhead = GetLog();
		int tmp_time[16];
		sprintf(tmp_time, "%d%d%d%d%d%d", td->tm_year%100, td->tm_mon+1, td->tm_mday, td->tm_hour, td->tm_min, td->tm_sec);
		lhead->time = tmp_time;
		lhead->name = file;
		lhead->descript = "deleted";
		return;
	}
	Removelog(lhead->link, file);
}
*/

void Removelog2(char file[]){
	FILE* fp;
	fopen("./logfile", "a+");

	time_t tt;
	tm* td;

	time(&tt);
	td = localtime(&tt);
	
	int td_year = td->tm_year%100;
	int td_mon = td->tm_mon+1;
	int td_day = td->tm_mday;
	int td_hour = td->tm_hour;
	int td_min = td->tm_min;
	int td_sec = td->tm_sec;

	char log[512];
	sprintf(log, "[%d%d%d %d%d%d] %s %s", td_year, td_mon, td_day, td_hour, td_min, td_sec, file, "deleted");

	return;
}
/*		
void Insertlog(LogDetail* lhead){
	if(lhead == NULL){
		return;
	}*/
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
/*
	fprintf(logfile, "[%s] %s %s", lhead->time, lhead->name, lhead->descript);

	//fputs(new, logfile);
	
	Insertlog(lhead->link);
}
*/
int CheckFile(Linklist* head, char cm_file[]){
	if(head == NULL){
		return 1;
	}
	if(strcmp(head->route, cm_file) == 0) { return 0; }
	CheckFile(head->link, cm_file);
}

void Copy(char path[], char file[]){
	time_t tt;
	tm* td;
	
	time(&tt);
	td = localtime(&tt);
	
	char date[16];
	char n_file[256];
	char n_path[256];
	int td_year = td->tm_year%100;
	int td_mon = td->tm_mon+1;
	int td_day = td->tm_mday;
	int td_hour = td->tm_hour;
	int td_min = td->tm_min;
	int td_sec = td->tm_sec;

	sprintf(date, "%d%d%d%d%d%d", td_year, td_mon, td_day, td_hour, td_min, td_sec);
	sprintf(n_file, "%s_%s", file, date);
	sprintf(n_path, "%s%s", path, n_file);
	FILE* ft = fopen(file, "r");
	FILE* nf = fopen(n_path, "w"); //백업 디렉토리 내 파일명 지정
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

Factor* GetFactor(Linklist* head, char path[], char file[], char option[]){
	Factor *factor;
	factor = (Factor*)malloc(sizeof(Factor));
	factor->head = head;
	strcpy(factor->path, path); //factor->path = path;
	strcpy(factor->file, file); //factor->file = file;
	factor->period = atoi(option);
	
	return factor;
}

pthread_mutex_t mutex;

void *thr_func(void* fac){
	Factor* factor = (Factor *)fac; //(Factor*)fac;
	Linklist* head = factor->head;
	//char path[256] = factor->path;
	//char file[256] = factor->file;
	char path[256]; char file[256];
	strcpy(path, factor->path);
	strcpy(file, factor->file);
	int period = head->period;
	int start = 1;
	Addlog2(file, start);
	//Removelog2(file);

	pthread_mutex_lock(&mutex);

	while(1){
		/*if(){ //스레드 종료 조건 넣어야
			pthread_exit((void*)&result);
			break;
		}*/
		Copy(path, file); //파일을 백업 디렉토리에 복사
		sleep(period);
		start++;
	}
	pthread_mutex_unlock(&mutex);

}


int Add(Linklist** head, LogDetail* lhead, char path[], char file[], char option[][32]){
	time_t tt;
	tm *td;
	int idx = 0;
	//FILE* fp;
	struct stat f_info;
	mode_t f_mode;
	//LogDetail* put_log;
	int result;

	//스레드 관련
	pthread_t p_thread;
	pthread_mutex_init(&mutex,NULL);
	int thr_id;

	//thr_id = pthread_create(&pthread[], NULL, thr_func, 
	td = localtime(&tt);
	if(strcmp(file, "\0") == 0){
		puts("Fail to add command");
		//basic 함수로 넘어가서 return 처리가 바로 될 수 있도록 조건 넣어줄 것
		return 1;
	}
	// 백업해야할 파일이 존재하지 않을 때 처리
	if(fopen(file, "r") == NULL){
		puts("Fail to add command");
		return 1;
	}
	// 백업해야할 파일이 일반파일이 아닐 경우 처리
	int f_stat = stat(file, &f_info);
	f_mode = f_info.st_mode;
	if(!S_ISREG(f_mode)){
		puts("Fail to open file");
		return 1;
	}

	// 백업해야할 파일이 백업리스트에 존재하는 지 확인 후 처리
	//lhead -> head로 변경해서 진행해야할 것으로 판단
	if(CheckFile(*head, file) == 1){
		puts("Fail to open file");
		return 1;
	}

	//PERIOD 처리
	if(option[0][0] == '\0'){ //PERIOD 입력 없을 시
		puts("Fail to add command");
		return 1;
	}
	if(fmod((atof(option[0])), 1.0) > 0.0){
		puts("Fail to add command"); //PERIOD가 실수일 때
		return 1;
	}

	do{
		if(dic[idx].dir[0] == '\0'){
			break; //특정 인덱스의 값이 없다면 break
		}
	}while(idx++);

	//dic[idx]->dir = path;
	strcpy(dic[idx].dir, path);
	dic[idx].link = *head;
	
	while((*head) == NULL){
		(*head) = GetNode();
		strcpy((*head)->route, file);//*head->route = file;
		(*head)->period = atoi(option[0]);
		(*head)->link = NULL;
		
		Factor* fac = GetFactor((*head), path, file, option[0]);
		(*head)->t_id = p_thread;
		pthread_create(&p_thread, NULL, thr_func, (void*)fac);
		pthread_join(p_thread, (void*)&result);

		pthread_mutex_destroy(&mutex);
		//백업 진행
		//Copy(path, file); //파일을 복사하는 작업을 함수로
		
		//logfile에 게시하는 작업
		//함수로 넘겨서 진행할 것. 함수 명시해야.
		//Addlog(lhead, file, td);

		//fputs(lhead, logflie);
		// 연결리스트를 그대로 fputs하는 것이 불가능하기 때문에 넣는 함수를 임의로 만들어주는 방법 생각
		//Insertlog(lhead);
		break;
	}
	Add(&(*head)->link, lhead, path, file, option);
	
	return 1;
}

/*
void Delete(char path[], char file[]){
	// 디렉터리 즉, path 오픈
	DIR *dir = NULL;
	struct dirent *file = NULL;

	char file2[256] = strrchr(file, '/');
	dir = opendir(path);
	while((file = readdir(dir)) != NULL){
		if(strcmp(file->d_name, file2) == 0){ //file의 경로에 있는 파일명만 활용해서 같은지 확인
			//파일 자체를 삭제하는 게 아니라 스레드 종료명령어 쓰기
		}
	}
	
	return;
}
*/

int Remove(Linklist** head, LogDetail* lhead, char path[], char file[], char option[][32]){
	//FILENAME 입력 없을 시
	if(strcmp(file, "\0") == 0){
		puts("Fail to remove command");
		//basic 함수로 넘어가서 return 처리가 바로 될 수 있도록 조건 넣어줄 것
		return 1;
	}
	//백업을 중단할 파일이 백업 리스트에 존재하지 않을 시(로그 파일)
	if(CheckFile((*head), file) == 1){
		puts("Fail to remove command");
		return 1;
	}
	
	if(strcmp((*head)->link->route, file) == 0){
		//head->link = head->link->link;
		Linklist* tmp = NULL;
		tmp = (*head)->link;
		(*head) = tmp->link;
		free(tmp);
		//잘 작동하는지 확인할 필요 있음.

		//스레드에 영향을 미치는 함수
		pthread_cancel((*head)->t_id);
		//Delete(path, file);

		//로그에 대한 함수들
		//Removelog(lhead, file);
		//Insertlog(lhead);
		Removelog2(file);
	}

	//pthread_cancel(head->t_id); //이 부분을 Delete 함수 내에서 진행해보기
	Remove(&(*head)->link, lhead, path, file, option);

	return 1;
}

void Compare(Linklist* head, char path[], char file[], char option[][32]){ //compare 명령어에 대한 함수

	int comp1 = 0;
	int comp2 = 0;
	struct stat file1_info;
	struct stat file2_info;
	
	//입력 인자가 2개가 아닌 경우
	if(file == NULL || option == NULL){ //NULL로 안될 것 같아서 나중에 봐야
		puts("Fail to compare command");
		return;
	}

	//파일이 존재하지 않을 경우
	if(fopen(file, "r") == NULL){
		puts("Fail to compare command");
		return;
	}
	if(fopen(option[0], "r") == NULL){
		puts("Fail to compare command");
		return;
	}

	//일반 파일이 아닐 경우
	int f1_stat = stat(file, &file1_info);
	int f2_stat = stat(option[0], &file2_info);
	mode_t f1_mode = file1_info.st_mode;
	mode_t f2_mode = file2_info.st_mode;

	if(!S_ISREG(f1_mode)){
		puts("Fail to compare command");
		return;
	}
	if(!S_ISREG(f2_mode)){
		puts("Fail to compare command");
		return;
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
		printf("File1 : mtime : %ld, 파일 크기 : %ld bytes", file1_info.st_mtime, file1_info.st_size);
		printf("File2 : mtime : %ld, 파일 크기 : %ld bytes", file2_info.st_mtime, file2_info.st_size);
	}

	return;

}

int Rec_check(Linklist* head, char file[]){
	if(head == NULL){
		return 0; //백업파일이 없다는 것 의미
	}

	if(strcmp(head->route, file) == 0){
		return 1;
	}
	Rec_check(head->link, file);
}

/*
void Pring_log(LogDetail* lhead, char f_name[]){

	int num = 0;
	printf("%d. exit", num);
	while(1){
		if(lhead == NULL){
			return;
		}
		
		if(strcmp(f_name, lhead->name) == 0){
			printf("%d. %s\t%s"); //로그 출력하지 않는 방법으로 찾아보기
		}
	}
	
}
*/

char* Print_number(char path[], char file[]){

	int numbering = 0;
	DIR* dir = NULL;
	struct dirent *dp = NULL;
	struct stat fs;
	char fp[256];
	char ans[4];
	char arr[256][256];

	printf("%d. exit\n", numbering);
	dir = opendir(path);
	while((dp = readdir(dir)) != NULL){
		if(strstr(dp->d_name, file) != NULL){
			numbering++;
			sprintf(fp, "%s%s", path, dp->d_name);
			if(stat(fp, &fs) == -1){continue;}
			//char byte[16] = fs.st_size;
			char byte[16];
			//strcpy(byte, fs.st_size);
			sprintf(byte, "%ld", fs.st_size);
			char* date = strrchr(dp->d_name, '_');
			sprintf(arr[numbering], "%d.%s", numbering, date);
			printf("%d. %s\t%s\n", numbering, date, byte);
		}
	}
	puts("Choose file to recover : ");
	fgets(ans, sizeof(ans), stdin);

	char str[8];
	char* n_date;	//char n_date[16];
	sprintf(str, "%s.", ans);
	for(int i = 0; i<256; i++){
		if(strstr(arr[i], str) != NULL){
			n_date = strrchr(arr[i], '.');
			break;
		}
	}

	return n_date;

}

void R_Copy(char new_name[], char file[], char path[]){ //Recover 명령어를 통해서 파일을 백업하는 함수
	FILE* fp;
	FILE* nf;
	char p[256];
	sprintf(p, "%s%s", path, new_name);
	fp = fopen(file, "w");
	nf = fopen(p, "r");
	while(1){
		int c = getc(nf);
		if(!feof(nf)){
			fputc(c, fp);
			fseek(nf, 1, SEEK_CUR);
		} else break;
	}
	fclose(fp);
	fclose(nf);

	return;
}

int Recover(Linklist** head, LogDetail* lhead, char file[], char path[]){

	int ch = Rec_check((*head), file); //백업 파일이 현재 백업 리스트에 존재하는 경우 확인. 백업 수행 종료를 진행해야 함.
	if(ch == 1){ //변경할 파일이 현재 백업 리스트에 존재하는 경우
		//백업 수행 종료 관련 명령문 작성 예정
		pthread_cancel((*head)->t_id);
	}
	if(fopen(file, "r") == NULL){//변경할 파일이 존재하지 않는 경우
		puts("Fail to recover command");
		return 1; //return 은 나중에 수정
	}
	
	// 변경할 파일에 대한 백업 파일이 존재하지 않는 경우
	DIR* dir = NULL;
	struct dirent *dp = NULL;
	int incl = 0;
	char* f_name = strrchr(file, '/');
	dir = opendir(path);
	while((dp = readdir(dir)) != NULL){
		if(dp->d_ino == 0) continue;
		if(strstr(dp->d_name, f_name) != NULL){
			incl = 1;
			break;
		}
	}
	if(incl == 0){
		puts("Fail to recover command");
		return 1; //return 부분 추후 수정
	}

	//Print_log(lhead, file);

	//char n_date[16]
	char* n_date = Print_number(path, f_name); //리스트를 보여주는 함수. 반환되는 문자열은 파일 뒤에 붙는 시간부분을 의미
	if(strcpy(n_date, "exit") == 0){
		//모든 실행중인 백업 중지 후 프로그램 종료
		while((*head) != NULL){
			pthread_cancel((*head)->t_id);
			(*head) = (*head)->link;
		}
		return 0; //return 부분 수정해야
		//pthread_exit();
	}
	char new_name[256];
	sprintf(new_name, "%s_%s", f_name, n_date);
	if(strcpy(dp->d_name, new_name) == 0){
		R_Copy(new_name, file, path);
	}
	FILE* fp;
	fp = fopen(file, "r");
	if(fp == NULL){
		puts("Error to open file");
		return 1;
	}
	while(1){
		int c = getc(fp);
		if(!feof(fp)){
			printf("%c", c);
			fseek(fp, 1, SEEK_CUR);
		}else break;
	}

	fclose(fp);

	return 1;
}

void List(Linklist* head){ //list 명령어에 대한 함수
	if(head == NULL) return;
	
	printf("%s %d", head->route, head->period);
	List(head->link);
}

void Ls(char file[]){ //argv를 사용하거나 함수에 들어오기 전 공백을 단위로 나누어서 인자 저장하는 방법으로 진행하기
	
	char order[260];
	//char path[256];
	char n_path[256];

	/*
	if(strchr(file, '/') == NULL){
		realpath(".", path); //현재 경로의 절대 경로 추출
		sprintf(n_path, "%s%s", path, file);
	}
	else{
		n_path = file;
	}
	*/
	//n_path = file;
	strcpy(n_path, file);
	sprintf(order, "%s %s", "ls", n_path);

	system(order);
	
	return;
/*
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
*/

}

void Vi(char file[]){
	
	char order[260];
	//char path[256];
	char n_path[256];
	/*
	if(strchr(file, '/') == NULL){
		realpath(".", path);
		sprintf(n_path, "%s%s", path, file); //절대경로로 변환
	}
	else{
		n_path = file;
	}
	*/
	//n_path = file;
	strcpy(n_path, file);
	sprintf(order, "%s %s", "vi", n_path); // vi + 절대경로
	system(order);
	
	return;
}

int Exit(Linklist** head){

	while((*head) != NULL){
		pthread_cancel((*head)->t_id);
		(*head) = (*head)->link;
	}

	return 0; //return 부분 나중에 첨삭
}

//path는 절대경로 상의 백업 딕셔너리 주소
int base_print(Linklist* head, char path[256], LogDetail* lhead){
	char input[256];
	int sep = 0; //separator. 공백을 단위로 나누기 위함
	char oper[8] = {0};
	char file[512] = {0};
	char option[2][32] = {0};

	printf("20193058> "); //기본 프롬프트 모양
	fgets(input, sizeof(input), stdin); //fgets로 받는 것이 더 좋음
	input[strlen(input) - 1] = '\0';
	char* token = strtok(input, " ");

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
			}
			//strcpy(file, token);
			if(strchr(file, '\0') == NULL){
				puts("Fail to input file_name");
				return 1; //파일명 255 넘었을 경우 에러메세지
			}
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

	int re = 1;
	if(strcmp(oper, "add") == 0){
		re = Add(&head, lhead, path, file, option);
		return re;
		//add 명령어와 맞는 함수
	}
	else if (strcmp(oper, "remove") == 0){
		re = Remove(&head, lhead, path, file, option);
		return re;
		//remove 명령어와 맞는 함수
	}
	else if (strcmp(oper, "compare") == 0){
		Compare(head, path, file, option);
		//compare과 맞는 함수
	}
	else if (strcmp(oper, "recover") == 0){
		re = Recover(&head, lhead, file, path);
		return re;
		//recover과 맞는 함수
	}
	else if (strcmp(oper, "list") == 0){
		List(head);
		//list와 맞는 함수
	}
	else if (strcmp(oper, "ls") == 0){
		//oper 를 제외한 값들이 들어갈 것. file
		Ls(file);
		//system("ls");
	}
	else if (strcmp(oper, "vi") == 0 || strcmp(oper, "vim") == 0){
		Vi(file);
		//system("vi");
	}
	else if (strcmp(oper, "exit") == 0){
		re = Exit(&head);
		return re;
		//exit에 맞는 함수
	}
	return re;
}

//pthread_t p_thread[32];
int re = 0;

int main(char argc, char* argv[]){
	system("clear");
	//pthread_t p_thread[32];
	Linklist* head = NULL;
	LogDetail* lhead = NULL;
	Diclist* arr[32];
	//int re = 0; //전역으로 선언해야할 듯
	re = 1;
	char path[256];
	struct stat dir_info;
	mode_t dir_mode;
	//FILE* logfile;

	logfile = fopen("./logfile", "w+");
	/*if(logfile == NULL){ //a+ or ra로 읽기도 동시에 할 수 있는지..
		
	}*/

	if(strchr(argv[0], '/') == NULL){ //상대 경로의 경우 현재 경로 앞에 추가
		//char way1[256];
		//getcwd(way1, sizeof(way1));
		//sprintf(path, "%s%s", way1, argv[0]);
		realpath(argv[0], path);
		printf("%s\n%s\n", argv[0], path);
	}
	printf("%s\n%s\n", path, argv[0]);

	int dir_res = mkdir(path, 0775);
	//printf("%d", dir_res); 체크 용도
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
	if(dir_mode >= 0001){
		printf("Usage : %s", path);
	}

	if(dir_res != 0){
		printf("Fail to make directory");
		return 0;
	}
	while(re){
		re = base_print(head, path, lhead);
	}

	return 0;
}
