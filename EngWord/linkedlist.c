#include "function.h"

Filelist* f_list[100];

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
	f_list[num]->link = head;
	return;
}

void FileProcessing(Linklist** head,char name[]){

	//Linklist* list[31] = {'\0'}; //Linklist 를 저장할 배열. 마지막에 리
	f_list[atoi(name)]->file_num = atoi(name);
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
		printf("출력"); //디버깅
		Word* new = InsertWord(new_eng, new_mean);

		//printf("인서트 완료 %s %s", new_eng, new_mean[]); //디버깅
		printf("new의 값들 %s %s %s %s", new->eng, new->means[0], new->means[1], new->means[2]); //디버깅
		ConnectNode(&head, new);
		if(count == 0) ConnectFile(&head, atoi(name));
		count++;
	}

	fclose(fp_out);
	return;

}

/*void FileArray(){

}*/

int main(void){
	//Linklist* list[31] = {'\0'};
	//Filelist* f_list[100] = '\0';
	char n[4] = "1";
	//Linklist* list = FileProcessing(n);
	Linklist* head = NULL;
	FileProcessing(head, n);
	/*for(int i = 0; i<30; i++){
		printf("%s %s %s %s", list[i].link->eng, list[i].link->means[0], list[i].link->means[1], list[i].link.means[2]);
	}*/
	return 0;
}
