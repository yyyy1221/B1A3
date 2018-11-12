#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h> 

#define PRINT_INT(x) printf("\n"#x" : %d\n", x);
#define PRINT_CHAR(x) printf("\n"#x" : %c\n", x);
#define PRINT_STRING(x) printf("\n"#x" : %s\n", x);

#define SCAN_INT(x) scanf("%d", &x);
#define SCAN_CHAR(x) scanf("%c", &x);
#define SCAN_STRING(x) scanf("%s", s);

struct client{ //client 파일의 정보를 저장하기 위한 구조체
	unsigned id; //학번 (정수 8자리)
	char *password; //비밀번호
	char *name; //이름
	char *address; //주소
	char *phone_number; //전화번호
	struct client *next; //자기 참조 구조체 구현
};

struct book{ //book 파일의 정보를 저장하기 위한 구조체
	unsigned number; //도서번호 (정수 7자리)
	char *name; //도서명
	char *publisher; //출판사
	char *writer; //저자명
 	unsigned long ISBN; //ISBN(정수 13자리)
	char *location; //소장처
	char borrow; //대여가능 여부
	struct book *next; //자기 참조 구조체 구현
};

struct borrow{ //borrow 파일의 정보를 저장하기 위한 구조체
	unsigned client_id; //학번 (정수 8자리)
	unsigned book_number; //도서번호 (정수 7자리)
	time_t borrow_date; //대여일자
	time_t return_date; //반납일자
	struct borrow *next; //자기 참조 구조체 구현
};



//함수 선언 

int main(void){
	FILE *client_ifp, *book_ifp, *borrow_ifp; //파일 입력을 위한 전역 변수 선언
	FILE *client_ofp, *book_ofp, *borrow_ofp; //파일 출력을 위한 전역 변수 선언
	
	struct client *client = (struct client *) malloc(sizeof(client));
	struct book *book = (struct book *) malloc(sizeof(book));
	struct borrow *borrow = (struct borrow *) malloc(sizeof(borrow));
	
	client -> next = NULL;
	book -> next = NULL;
	borrow -> next = NULL;
	
	char tmp[4][30] = {0};
	
	if ((client_ifp = fopen("client.txt", "r")) == NULL){
		printf("client.txt 파일이 존재하지 않습니다.\n");
		exit(1);
	}
	if ((book_ifp = fopen("book.txt", "r")) == NULL){
		printf("book.txt 파일이 존재하지 않습니다.\n");
		exit(1);
	}
	if ((borrow_ifp = fopen("borrow.txt", "r")) == NULL){
		printf("borrow.txt 파일이 존재하지 않습니다.\n");
		exit(1);
	}
	//id | password | name | address | phone_number 
	fscanf(client_ifp, "%d | %s | %s | %s | %s", &client -> id, tmp[0],
	tmp[1], tmp[2], tmp[3]);
	
	client -> password = (char *) malloc(strlen(tmp[0]) * sizeof(char));
	client -> name = (char *) malloc(strlen(tmp[1]) * sizeof(char));
	client -> address = (char *) malloc(strlen(tmp[2]) * sizeof(char));
	client -> phone_number = (char *) malloc(strlen(tmp[3]) * sizeof(char));
	
	strcpy(client -> password, tmp[0]);
	strcpy(client -> name, tmp[1]);
	strcpy(client -> address, tmp[2]);
	strcpy(client -> phone_number, tmp[3]);
	
	printf("%d %s %s %s %s", client -> id, client -> password, client -> name, client -> address, client -> phone_number);
	
	
	fclose(client_ifp);
	fclose(book_ifp);
	fclose(borrow_ifp);
}

	
	
	
	
	
	
	