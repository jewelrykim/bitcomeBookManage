#pragma warning(disable:4996)
#include <stdio.h>
#include <iostream>
#include <malloc.h>
#include <windows.h>

typedef struct _ISBN
{
	char * Title;
	char * Writer[5];
	char * Company;
	char * Price;
	char * Table[20];
}ISBN;
void NewBookData(char * *Bookdata, char* PrintMessage){
	char temp[1024];
	printf("%s",PrintMessage);
	gets(temp);
	fflush(stdin);
	*Bookdata = (char*)malloc(strlen(temp) + 1);
	strcpy(*Bookdata, temp);
}
void NewBookDataWiter(char * *Bookdata, char* PrintMessage){
	char temp[1024];
	printf("%s", PrintMessage);
	for (int i = 0; i < 5; i++){
		gets(temp);
		fflush(stdin);
		if (*temp == '\n')
			break;
		*(Bookdata+i) = (char*)malloc(strlen(temp) + 1);
		strcpy(*(Bookdata + i), temp);
	}
}void NewBookDataTable(char * *Bookdata, char* PrintMessage){
	char temp[1024];
	printf("%s", PrintMessage);
	for (int i = 0; i < 20; i++){
		gets(temp);
		fflush(stdin);
		if (*temp == '\n')
			break;
		*(Bookdata + i) = (char*)malloc(strlen(temp) + 1);
		strcpy(*(Bookdata + i), temp);
	}
}
void InputBookData(ISBN* BookArray){
	NewBookData(&BookArray->Title, "제목");
	NewBookDataWiter(BookArray->Writer, "저자");
	NewBookData(&BookArray->Company, "출판사");
	NewBookData(&BookArray->Price, "가격");
	NewBookDataTable(&BookArray->Title, "제목");
}
void AddBook(ISBN * BookArray, int* Totalbook){
	InputBookData(&BookArray[*Totalbook]);
	(*Totalbook)++;
}

void main(){
	ISBN * BookArray = {};
	int TotalBook=1;
	BookArray = (ISBN *)malloc(sizeof(ISBN)* 1);
	AddBook(BookArray, &TotalBook);

}


