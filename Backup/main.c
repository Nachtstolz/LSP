#include "function.h"

Diclist* dic = NULL;


void base_print(Linklist* head){
	char input[256];

	print("20193058> ");
	scanf("%s" &input);
}





int main(char argc, char *argv[]){
	system("clear");
	Linklist* head = NULL;
	Diclist* arr[32] = NULL;
	int re = 0;
	char path[256];
	struct stat dir_info;
	mode_t dir_mode;
	

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
	
	//여기에 접근권한
	if(dir_res != 0){
		printf("Fail to make directory");
		return 0;
	}
	while(re){
		base_print(head);
	}

	return 0;
}
