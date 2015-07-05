#pragma warning(disable:4996)
#include <stdio.h>
#include <iostream>
#include <malloc.h>
#include <windows.h>
#include <ctype.h>
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
int NewBookDataWiter(char * *Bookdata, char* PrintMessage){
	char temp[1024];
	for (int iCurrentBookNum = 0; iCurrentBookNum < 5; iCurrentBookNum++){
		printf(" %d. %s",iCurrentBookNum+1, PrintMessage);
		gets(temp);
		fflush(stdin);
		if (temp[0]=='\0'){
			return iCurrentBookNum;
		}
		*(Bookdata + iCurrentBookNum) = (char*)malloc(strlen(temp) + 1);
		strcpy(*(Bookdata + iCurrentBookNum), temp);
		memset(temp,NULL,1024);
	}
	return 5;
}
int NewBookDataTable(char * *Bookdata, char* PrintMessage){
	char temp[1024];
	for (int iCurrentBookNum = 0; iCurrentBookNum < 20; iCurrentBookNum++){
		printf(" %d. %s", iCurrentBookNum+1, PrintMessage);
		gets(temp);
		fflush(stdin);
		if (temp[0] == '\0')
			return iCurrentBookNum;
		*(Bookdata + iCurrentBookNum) = (char*)malloc(strlen(temp) + 1);
		strcpy(*(Bookdata + iCurrentBookNum), temp);
		memset(temp,NULL,1024);
	}
	return 20;
}
void InputBookData(ISBN* BookArray){
	int WiterNum = 0;
	int TableNum = 0;
	NewBookData(&BookArray->Title, "제목 : ");
	BookArray->WriterNum=NewBookDataWiter(BookArray->Writer, "저자 : ");
	NewBookData(&BookArray->Company, "출판사 :");
	NewBookData(&BookArray->Price, "가격 :");
	BookArray->TableNum=NewBookDataTable(BookArray->Table, "목차 :");
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
	printf("도서 명 : %s\n", BookArray->Title);
	printf("저자 :\n");
	for (int i= 0; i < BookArray->WriterNum; i++){
		printf("%d.%s ", i+1, BookArray->Writer[i]);
	}
	printf("\n출판사 : %s\n", BookArray->Company);
	printf("가격 : %s\n", BookArray->Price);
	printf("목차 :\n");
	for (int i = 0; i < BookArray->TableNum; i++){
		printf(" %d. %s\n", i+1, BookArray->Table[i]);
	}
}
void PrintBookList(ISBN * BookArray, int BookNum){
	if (BookNum == 0)
		printf("저장된 도서가 없습니다.");
	else{
		for (int iCurrentBookNum = 0; iCurrentBookNum < BookNum; iCurrentBookNum++){
			Print(BookArray+iCurrentBookNum);
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
			for (int j = 0; j < BookArray[iCurrentBookNum].WriterNum; j++){
				if (strstr(BookArray[iCurrentBookNum].Writer[j],SearchBookdata) != 0){
					SearchBookArray[index] = iCurrentBookNum;
					index++;
					break;
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
			for (int j = 0; j < BookArray[iCurrentBookNum].TableNum; j++){
					if (strcmp(BookArray[iCurrentBookNum].Table[j],SearchBookdata ) == 0){
					SearchBookArray[index] = iCurrentBookNum;
					index++;
					break;
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
	char SearchBookdata[1024] ;
	int SearchBookIndex = 0;
	int * SearchBookArray = (int *)malloc(sizeof(int)*BookNum);
	int ReturnSearch = 0;
	printf("검색 방법 선택(1.제목검색 , 2.저자검색, 3.목차검색, 0.검색취소: )");
	Searchtype = getchar();
	fflush(stdin);
	while (Searchtype != '0'){
		switch (Searchtype)
		{
		case '1':	
			printf("1. 제목검색\n 검색하고 싶은 도서 명 : ");
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
				while (SearchBookArray[SearchBookIndex] != -1){
					Print(&BookArray[SearchBookArray[SearchBookIndex]]);
					SearchBookIndex++;
				}
			}
			Searchtype = '0';
			break;
		case '3':
			printf("3. 목차검색\n 검색하고 싶은 목차 :");
			gets(SearchBookdata);
			fflush(stdin);
			ReturnSearch = MSearchT(BookArray, BookNum, SearchBookdata, SearchBookArray);
			if (ReturnSearch == 0){
				while (SearchBookArray[SearchBookIndex] != -1){
					Print(&BookArray[SearchBookArray[SearchBookIndex]]);
					SearchBookIndex++;
				}
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

void DeleteBook(ISBN * BookArray, int *BookNum){
	char SearchBookdata[128] = { ' ' };
	int SearchBookIndex = 0;
	printf("수정하고 싶은 도서 명 :");
	gets(SearchBookdata);
	fflush(stdin);
	int ReturnSearch = SSearch(BookArray, *BookNum, SearchBookdata, &SearchBookIndex);
	if (ReturnSearch == 0){
		//메모리 관리 free
		for (int i = SearchBookIndex; i < *BookNum; i++){
			BookArray[i].Title = BookArray[i + 1].Title;
			for (int j = 0; j < BookArray[i].WriterNum; j++){
				BookArray[i].Writer[j] = BookArray[i + 1].Writer[j];
			}
			BookArray[i].Company = BookArray[i + 1].Company;
			BookArray[i].Price = BookArray[i + 1].Price;
			for (int j = 0; j < BookArray[i].TableNum; j++){
				BookArray[i].Table[j] = BookArray[i + 1].Table[j];
			}
		}
		*BookNum -= 1;
	}
	//메시지 출력 printf("%s", );
}
void FilePrint(ISBN* BookArray, int TotalBook, int BookNum){
	FILE *fp;
	printf("도서목록을 저장합니다.\n");
	fp = fopen("ISBN.txt", "w");
	fprintf(fp, "%d\n", TotalBook);
	for (int index = 0; index < BookNum; index++)
	{
		int iWriteNum = BookArray[index].WriterNum;
		int iTableNum = BookArray[index].TableNum;
		fprintf(fp, "%s\n", BookArray[index].Title);
		fprintf(fp, "%d\n", iWriteNum);				//3번째 정보는 저자 수
		for (int i = 0; i < iWriteNum; i++){
			fprintf(fp, "%s\n", BookArray[index].Writer[i]);
		}
		fprintf(fp, "%s\n", BookArray[index].Company);
		fprintf(fp, "%s\n", BookArray[index].Price);
		fprintf(fp, "%d\n", iTableNum);				//3+저자수+3번째 정보는 목록 수
		for (int i = 0; i < iTableNum; i++){
			fprintf(fp, "%s\n", BookArray[index].Table[i]);
		}
	}
	fclose(fp);
}
char* FileDataScan(FILE * fp, char **pData){
	char temp[1024] = { " " };
	char* tester;
	tester = fgets(temp, 1024, fp);
	*pData = (char *)malloc(strlen(temp));
	strcpy(*pData, temp);
	(*pData)[strlen(temp) - 1] = NULL;
	return tester;
}
int FileDataIndex(FILE * fp, int *pData){
	fscanf(fp, "%d\n", *pData);
	return *pData;
}
void FileScan(ISBN* BookArray, int *TotalBook, int *BookNum){
	FILE *fp;
	fp = fopen("ISBN.txt", "r");
	if (fp == NULL)
		printf("도서목록이 없습니다.");
	else{
		printf("도서목록을 읽어옵니다.\n");
		fscanf(fp, "%d\n", TotalBook);
		int index = 0;
		BookArray[0].Title = NULL;
		free(BookArray);
		BookArray = (ISBN *)malloc(sizeof(BookArray)* (*TotalBook));
		while (!feof(fp))
		{
			if (FileDataScan(fp, &BookArray[index].Title) == NULL)break;
			fscanf(fp, "%d\n", &BookArray[index].WriterNum);
			for (int i = 0; i < BookArray[index].WriterNum; i++){
				FileDataScan(fp, &BookArray[index].Writer[i]);
			}
			FileDataScan(fp, &BookArray[index].Company);
			FileDataScan(fp, &BookArray[index].Price);
			fscanf(fp, "%d\n", &BookArray[index].TableNum);
			for (int i = 0; i < BookArray[index].TableNum; i++){
				FileDataScan(fp, &BookArray[index].Table[i]);
			}
			index++;

		}
		*BookNum = index;
	}
	fclose(fp);
}
void main(){
	ISBN * BookArray = {};
	char mode = '1';
	int TotalBook=10;
	int	BookNum = 0;
	BookArray = (ISBN *)malloc(sizeof(ISBN)* 1);
	while (mode != '0'){
		printf("\nmode 선택 ( 1 = 입력 , 2 = 출력 , 3 = 단일검색, 4 = 수정(정확한 이름), 5 = 단일삭제(정확한 이름), 6 = 파일저장, 7 = 파일로드 0 = 종료) \n");
		mode = getchar();
		fflush(stdin);

		switch (mode)
		{
		case '1':
			AddBook(BookArray, &BookNum, TotalBook);
			break;
		case '2':
			PrintBookList(BookArray, BookNum);
			break;
		case '3':
			SearchBook(BookArray, BookNum);
			break;
		case '4':
			ChangeBook(BookArray, BookNum);
			break;
		case '5':
			DeleteBook(BookArray, &BookNum);
			break;
		case '6':
			FilePrint(BookArray, TotalBook, BookNum);
			break;
		case '7':
			FileScan(BookArray, &TotalBook, &BookNum);
			break;
		default:
			mode = '0';
			free(BookArray);
			break;
		}
	}
}


