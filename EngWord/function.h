//선언용 파일

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

typedef struct node{
	struct word *dic;
	struct node *link;
}Linklist; //단어별 연결 리스트

// 파일에 대한 배열을 만들고 파일별로 단어들을 연결하는 리스트
typedef struct file{
	int file_num;
	struct node *link;
}Filelist; //파일 하나

typedef struct word{ //Linklist의 data로 들어갈 것
	char eng[16];
	char means[3][31];
} Word; //단어 하나 - 뜻 3개를 가진 구조체

// LinkedList 관련 함수
Word* GetWord(); //연결리스트의 data에 들어갈 Word 구조체 생성
Word* InsertWord(char eng[], char mean[][31]); //Word 구조체에 데이터 삽입하기
Linklist* GetNode(); //연결리스트에 들어갈 노드 생성
void ConnectNode(Linklist** head, Word* new); //노드 다음으로 노드 연결하기
void ConnectFile(Linklist** head, int num);
void FileProcessing(Linklist** head, char name[]); //파일 열기 및 데이터 추출과 저장

// 1번 메뉴


// 2번 메뉴


// 3번 메뉴


// 4번 메뉴



