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
void NewBookDataWiter(char * *Bookdata, char* PrintMessage,int* WiterNum){
	char temp[1024];
	printf("%s", PrintMessage);
	for (int i = 0; i < 5; i++){
		gets(temp);
		fflush(stdin);
		if(strstr(temp, "\n")!=NULL)break;
		*(Bookdata+i) = (char*)malloc(strlen(temp) + 1);
		strcpy(*(Bookdata + i), temp);
		WiterNum++;
	}
}void NewBookDataTable(char * *Bookdata, char* PrintMessage, int* TableNum){
	char temp[1024];
	printf("%s", PrintMessage);
	for (int i = 0; i < 20; i++){
		gets(temp);
		fflush(stdin);
		if (*temp == '\n')
			break;
		*(Bookdata + i) = (char*)malloc(strlen(temp) + 1);
		strcpy(*(Bookdata + i), temp);
		TableNum++;
	}
}
void InputBookData(ISBN* BookArray,int *WiterNum,int *TableNum){
	NewBookData(&BookArray->Title, "제목");
	NewBookDataWiter(BookArray->Writer, "저자",WiterNum);
	NewBookData(&BookArray->Company, "출판사");
	NewBookData(&BookArray->Price, "가격");
	NewBookDataTable(&BookArray->Title, "목차",TableNum);
}
void AddBook(ISBN * BookArray, int* BookNum, int * WiterNum, int *TableNum){
	InputBookData(&BookArray[*BookNum],WiterNum,TableNum);
	(*BookNum)++;
}
void Print(ISBN * BookArray, int WiterNum, int Tablenum){
	printf("%s", BookArray->Title);
	for (int j = 0; j < WiterNum; j++){
		printf("%s", BookArray->Writer[j]);
	}
	printf("%s", BookArray->Company);
	printf("%s", BookArray->Price);
	for (int j = 0; j < Tablenum; j++){
		printf("%s", BookArray->Table[Tablenum]);
	}
}
void PrintBookList(ISBN * BookArray, int BookNum, int WiterNum, int Tablenum){
	if (BookNum == 0)
		printf("저장된 도서가 없습니다.");
	else{
		for (int i = 0; i < BookNum; i++){
			Print(BookArray, WiterNum, Tablenum);
		}
	}
}
int SSearch(ISBN* BookArray,int BookNum,char* SearchBookdata,int * SearchBookindex){
	if (BookNum == 0){
		return 1;
	}
	else{
		for (int i = 0; i < BookNum; i++){
			if (strcmp(SearchBookdata, BookArray[i].Title) == 0){
				*SearchBookindex = i;
				return 0;
			}
		}
		return 2;
	}
}
int MSearch(ISBN* BookArray, int BookNum,int Bookdata, char* SearchBookdata, int * SearchBookArray){
	int index = 0;
	if (BookNum == 0){
		return 1;
	}
	else{
		for (int i = 0; i < BookNum; i++){
			if (strcmp(SearchBookdata, BookArray[i].Writer[Bookdata]) == 0){
				SearchBookArray[index] = i;
				index++;
			}
		}
		SearchBookArray[index] = -1;
		if (SearchBookArray[0] == -1){
			return 2;
		}
		else{
			return 0;
		}
	}
}
void SearchBook(ISBN * BookArray,int WiterNum,int TableNum , int BookNum){
	char Searchtype = '1';
	char SearchBookdata[128] = { ' ' };
	int SearchBookindex = 0;
	int * flag = (int *)malloc(sizeof(int)*BookNum);
	printf("검색 방법 선택(1.제목검색 , 2.저자검색, 3.목차검색, 0.검색취소: ");
	Searchtype = getchar();
	while (Searchtype != '0'){
		switch (Searchtype)
		{
		case '1':	
			printf("1. 제목검색\n 검색하고 싶은 도서 명 :");
			gets(SearchBookdata);
			fflush(stdin);
			if (SSearch(BookArray, BookNum,SearchBookdata,&SearchBookindex) == 0){
				Print(BookArray + SearchBookindex,WiterNum,TableNum);
			}
			Searchtype = '0';
			break;
		case '2':
			printf("2. 저자검색\n 검색하고 싶은 저자 :");
			gets(SearchBookdata);
			fflush(stdin);
			if (MSearch(BookArray, BookNum, WiterNum, SearchBookdata, flag) == 0){
				Print(BookArray + SearchBookindex, WiterNum, TableNum);
			}
			Searchtype = '0';
			break;
		case '3':
			printf("3. 목차검색\n 검색하고 싶은 목차 :");
			gets(SearchBookdata);
			fflush(stdin);
			if (MSearch(BookArray, BookNum, WiterNum, SearchBookdata, flag) == 0){
				Print(BookArray + SearchBookindex, WiterNum, TableNum);
			}
			Searchtype = '0';
			break;
		default:
			break;
		}
	}
	//메시지 출력(성공 실패)
	free(flag);
}
void main(){
	ISBN * BookArray = {};
	int TotalBook=10;
	int	BookNum = 0;
	int WiterNum = 0;
	int TableNum = 0;
	
	BookArray = (ISBN *)malloc(sizeof(ISBN)* 1);
	AddBook(BookArray, &BookNum,&WiterNum,&TableNum);
	PrintBookList(BookArray, BookNum,  WiterNum, TableNum);
	SearchBook(BookArray, WiterNum, TableNum,BookNum);
}


