#include <stdio.h>
#include <stdlib.h>

int click;


int main(void){
	setbuf(stdout, NULL);
	system("clear");

	puts(">> 영어 단어 암기 프로그램 : 단어장 관리 <<");
	printf("1. 새 파일 추가하기\t2. 새 단어 추가하기\n");
	printf("3. 단어장 보기\t4. 단어 파일 목록보기\n");
	printf("5. 단어장 관리 종료\n");

	printf("번호를 입력하세요 : ");
	scanf("%d", &click); 

	if(click == 1){
		//system("./menu4_1");

	}
	else if (click == 2) {
		//system("./menu4_2");
	}
	else if (click == 3){
		//system("./menu4_3");
	}
	else if (click == 4){
		//system("./menu4_4");
	}
	else if (click == 5){
		return 0;
	}

	return 0;

}
