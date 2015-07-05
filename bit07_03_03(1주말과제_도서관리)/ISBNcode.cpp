#pragma warning(disable:4996)
#include <stdio.h>
#include <iostream>
#include <malloc.h>
#include <windows.h>
//수정할 내용
//메시지 출력 printf("%s", );
//메모리 관리 free

typedef struct _ISBN
{
	char * Title;
	char * Writer[5];
	char * Company;
	char * Price;
	char * Table[20];
	int WriterNum;
	int TableNum;
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
	for (int iCurrentBookNum = 0; iCurrentBookNum < 5; iCurrentBookNum++){
		gets(temp);
		fflush(stdin);
		if(strstr(temp, "\n")!=NULL)break;
		*(Bookdata + iCurrentBookNum) = (char*)malloc(strlen(temp) + 1);
		strcpy(*(Bookdata + iCurrentBookNum), temp);
		WiterNum++;
	}
}void NewBookDataTable(char * *Bookdata, char* PrintMessage, int* TableNum){
	char temp[1024];
	printf("%s", PrintMessage);
	for (int iCurrentBookNum = 0; iCurrentBookNum < 20; iCurrentBookNum++){
		gets(temp);
		fflush(stdin);
		if (*temp == '\n')
			break;
		*(Bookdata + iCurrentBookNum) = (char*)malloc(strlen(temp) + 1);
		strcpy(*(Bookdata + iCurrentBookNum), temp);
		TableNum++;
	}
}
void NewBookindex(int *Bookindex, int *BookData){
	Bookindex = BookData;
}
void InputBookData(ISBN* BookArray){
	int WiterNum = 0;
	int TableNum = 0;
	NewBookData(&BookArray->Title, "제목");
	NewBookDataWiter(BookArray->Writer, "저자",&WiterNum);
	NewBookData(&BookArray->Company, "출판사");
	NewBookData(&BookArray->Price, "가격");
	NewBookDataTable(&BookArray->Title, "목차",&TableNum);
	NewBookindex(&BookArray->WriterNum, &WiterNum);
	NewBookindex(&BookArray->TableNum, &TableNum);
}
void AddBook(ISBN * BookArray, int* BookNum, int TotalBook ){
	if ((*BookNum) >= TotalBook){
		printf("자리가 없습니다.\n");
		return;
	}
	InputBookData(&BookArray[*BookNum]);
	(*BookNum)++;
}
void Print(ISBN * BookArray){
	printf("%s", BookArray->Title);
	for (int j = 0; j < BookArray->WriterNum; j++){
		printf("%s", BookArray->Writer[j]);
	}
	printf("%s", BookArray->Company);
	printf("%s", BookArray->Price);
	for (int j = 0; j < BookArray->TableNum; j++){
		printf("%s", BookArray->Table[j]);
	}
}
void PrintBookList(ISBN * BookArray, int BookNum){
	if (BookNum == 0)
		printf("저장된 도서가 없습니다.");
	else{
		for (int iCurrentBookNum = 0; iCurrentBookNum < BookNum; iCurrentBookNum++){
			Print(BookArray);
		}
	}
}
int SSearch(ISBN* BookArray, int BookNum, char* SearchBookdata, int * SearchBookIndex){
	if (BookNum == 0){
		return 1;
	}
	else{
		for (int iCurrentBookNum = 0; iCurrentBookNum < BookNum; iCurrentBookNum++){
			if (strcmp(SearchBookdata, BookArray[iCurrentBookNum].Title) == 0){
				*SearchBookIndex = iCurrentBookNum;
				return 0;
			}
		}
		return 2;
	}
}
int MSearchW(ISBN* BookArray, int BookNum, char* SearchBookdata, int * SearchBookArray){
	//Bookdata 저자 수 or 목차 수
	int index = 0;
	if (BookNum == 0){
		return 1;
	}
	else{
		for (int iCurrentBookNum = 0; iCurrentBookNum < BookNum; iCurrentBookNum++){
			for (int j = 0; j < BookArray->WriterNum; j++){
				if (strcmp(SearchBookdata, BookArray[iCurrentBookNum].Writer[j]) == 0){
					SearchBookArray[index] = iCurrentBookNum;
					index++;
				}
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
int MSearchT(ISBN* BookArray, int BookNum, char* SearchBookdata, int * SearchBookArray){
	//Bookdata 저자 수 or 목차 수
	int index = 0;
	if (BookNum == 0){
		return 1;
	}
	else{
		for (int iCurrentBookNum = 0; iCurrentBookNum < BookNum; iCurrentBookNum++){
			for (int j = 0; j < BookArray->TableNum; j++){
				if (strstr(SearchBookdata, BookArray[iCurrentBookNum].Table[j]) == 0){
					SearchBookArray[index] = iCurrentBookNum;
					index++;
				}
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
void SearchBook(ISBN * BookArray, int BookNum){
	char Searchtype = '1';
	char SearchBookdata[128] = { ' ' };
	int SearchBookIndex = 0;
	int * SearchBookArray = (int *)malloc(sizeof(int)*BookNum);
	int ReturnSearch = 0;
	printf("검색 방법 선택(1.제목검색 , 2.저자검색, 3.목차검색, 0.검색취소: ");
	Searchtype = getchar();
	while (Searchtype != '0'){
		switch (Searchtype)
		{
		case '1':	
			printf("1. 제목검색\n 검색하고 싶은 도서 명 :");
			gets(SearchBookdata);
			fflush(stdin);
			ReturnSearch = SSearch(BookArray, BookNum, SearchBookdata, &SearchBookIndex);
			if ( ReturnSearch == 0){
				Print(BookArray + SearchBookIndex);
			}
			Searchtype = '0';
			break;
		case '2':
			printf("2. 저자검색\n 검색하고 싶은 저자 :");
			gets(SearchBookdata);
			fflush(stdin);
			ReturnSearch = MSearchW(BookArray, BookNum, SearchBookdata, SearchBookArray);
			if (ReturnSearch == 0){
				Print(BookArray + SearchBookIndex);
			}
			Searchtype = '0';
			break;
		case '3':
			printf("3. 목차검색\n 검색하고 싶은 목차 :");
			gets(SearchBookdata);
			fflush(stdin);
			ReturnSearch = MSearchT(BookArray, BookNum, SearchBookdata, SearchBookArray);
			if (ReturnSearch == 0){
				Print(BookArray + SearchBookIndex);
			}
			Searchtype = '0';
			break;
		default:
			break;
		}
	}
	//메시지 출력(성공 실패)
	free(SearchBookArray);
}
void ChangeBook(ISBN * BookArray, int BookNum){
	char SearchBookdata[128] = { ' ' };
	int SearchBookIndex = 0;
	printf("수정하고 싶은 도서 명 :");
	gets(SearchBookdata);
	fflush(stdin);
	int ReturnSearch = SSearch(BookArray, BookNum, SearchBookdata, &SearchBookIndex);
	if (ReturnSearch == 0){
		printf("수정할 정보 :");
		//메모리 관리 free
		InputBookData(&BookArray[SearchBookIndex]);
	}
	//메시지 출력 printf("%s", );
}
//void DeleteBook(ISBN * BookArray, int WiterNum, int TableNum, int BookNum){
//	char SearchBookdata[128] = { ' ' };
//	int SearchBookIndex = 0;
//	printf("수정하고 싶은 도서 명 :");
//	gets(SearchBookdata);
//	fflush(stdin);
//	int ReturnSearch = SSearch(BookArray, BookNum, SearchBookdata, &SearchBookIndex);
//	if (ReturnSearch == 0){
//		printf("수정할 정보 :");
//		//메모리 관리 free
//		for (int i = SearchBookIndex; i < BookNum; i++){
//			BookArray[i].Title = BookArray[i + 1].Title;
//			for (int j = WiterNum)
//			BookArray[i].Writer[]
//		}
//	}
//	//메시지 출력 printf("%s", );
//}
void main(){
	ISBN * BookArray = {};
	int TotalBook=10;
	int	BookNum = 0;
	
	BookArray = (ISBN *)malloc(sizeof(ISBN)* 1);
	AddBook(BookArray, &BookNum, TotalBook);
	PrintBookList(BookArray, BookNum);
	SearchBook(BookArray, BookNum);
	ChangeBook(BookArray, BookNum);
	//DeleteBook(BookArray, BookNum);
}


