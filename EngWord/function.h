//선언용 파일

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

typedef struct node{
	int data;
	struct node *link;
}Linklist; //단어별 연결 리스트
// 파일에 대한 배열을 만들고 파일별로 연결리스트가 있을 예정

typedef struct word{ //Linklist의 data로 들어갈 것
	char eng[16];
	char means[3][31];
} Word; //단어 하나 - 뜻 3개를 가진 구조체

// LinkedList 관련 함수
Word* GetWord(); //연결리스트의 data에 들어갈 Word 구조체 생성
Word* InsertWord(char eng[], char mean[]); //Word 구조체에 데이터 삽입하기
Linklist* GetNode(); //연결리스트에 들어갈 노드 생성
void ConnectNode(Linklist* list, Word* new, int num); //노드 다음으로 노드 연결하기
//void StoreWord(char file, ); //파일 열어서 단어 저장
Linklist* FileProcessing(char name); //파일 열기 및 데이터 추출과 저장

// 1번 메뉴


// 2번 메뉴


// 3번 메뉴


// 4번 메뉴



