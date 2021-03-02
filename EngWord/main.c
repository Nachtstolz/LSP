#include "function.h"

Word* GetWord();
void InsertWord(Word* word, char eng[], char mean[][]);
Linklist* GetNode();
void ConnectNode(Linklist* list, char eng[], char means[][]);
void FileProcessing(char name);

int main(void){
	
	Linklist* list[31];
	list = FileProcessing("1");
	for(int i = 0; i<31; i++){
		printf("%d %s %s %s %s %s", i, list[i]->link->eng, list[i]->link->means[0], list[i]->link->means[1], list[i]->link->means[2]);

}
