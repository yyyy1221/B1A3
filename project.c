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

#define PATH_CLIENT "client.txt"
#define PATH_BOOK "book.txt"
#define PATH_BORROW "borrow.txt"
#define READ_MOD "rt"
#define WRITE_MOD "wt"

/////////////////////////////////매크로

typedef struct client{ //client 파일의 정보를 저장하기 위한 구조체
	unsigned id; //학번 (정수 8자리)
	char *password; //비밀번호
	char *name; //이름
	char *address; //주소
	char *phone_number; //전화번호
	struct client *next; //자기 참조 구조체 구현
} CLIENT;

typedef struct book{ //book 파일의 정보를 저장하기 위한 구조체
	unsigned number; //도서번호 (정수 7자리)
	char *name; //도서명
	char *publisher; //출판사
	char *writer; //저자명
 	unsigned long ISBN; //ISBN(정수 13자리)
	char *location; //소장처
	char borrow; //대여가능 여부
	struct book *next; //자기 참조 구조체 구현
} BOOK;

typedef struct borrow{ //borrow 파일의 정보를 저장하기 위한 구조체
	unsigned client_id; //학번 (정수 8자리)
	unsigned book_number; //도서번호 (정수 7자리)
	time_t borrow_date; //대여일자
	time_t return_date; //반납일자
	struct borrow *next; //자기 참조 구조체 구현
} BORROW;

/////////////////////////////////구조체 선언

CLIENT * client_read(void);


/////////////////////////////////링크드 리스트 함수 선언



/////////////////////////////////함수 선언 

int main(void){
	FILE *client_ifp, *book_ifp, *borrow_ifp; //파일 입력을 위한 전역 변수 선언
	FILE *client_ofp, *book_ofp, *borrow_ofp; //파일 출력을 위한 전역 변수 선언
	
	CLIENT *client = (CLIENT *) malloc(sizeof(client)); //client 구조체 포인터변수에 메모리 할당
	BOOK *book = (BOOK *) malloc(sizeof(book)); //client 구조체 포인터변수에 메모리 할당
	BORROW *borrow = (BORROW *) malloc(sizeof(borrow)); //client 구조체 포인터변수에 메모리 할당
	
	client -> next = NULL;
	book -> next = NULL;
	borrow -> next = NULL;
	
	char tmp[4][30] = {0}; //동적 메모리 할당을 위해 임시적으로 사용할 배열
	
	if ((client_ifp = fopen(PATH_CLIENT, READ_MOD)) == NULL){ //client 파일 읽어오기
		printf("client.txt 파일이 존재하지 않습니다.\n"); //파일 없으면 오류 메시지 출력
		exit(1); //프로그램 종료
	}
	
	if ((book_ifp = fopen(PATH_BOOK, READ_MOD)) == NULL){ //book 파일 읽어오기
		printf("book.txt 파일이 존재하지 않습니다.\n"); //파일 없으면 오류 메시지 출력
		exit(1); //프로그램 종료
	}
	if ((borrow_ifp = fopen(PATH_BORROW, READ_MOD)) == NULL){ //borrow 파일 읽어오기
		printf("borrow.txt 파일이 존재하지 않습니다.\n"); //파일 없으면 오류 메시지 출력
		exit(1); //프로그램 종료
	}
	//id | password | name | address | phone_number : client 파일 데이터 형식
	fscanf(client_ifp, "%d | %s | %s | %s | %s", &client -> id, tmp[0], //client 파일에서 한줄 fscanf로 받아와서 tmp배열에 넣어주기
	tmp[1], tmp[2], tmp[3]);
	
	client -> password = (char *) malloc(strlen(tmp[0]) * sizeof(char));
	client -> name = (char *) malloc(strlen(tmp[1]) * sizeof(char));
	client -> address = (char *) malloc(strlen(tmp[2]) * sizeof(char));
	client -> phone_number = (char *) malloc(strlen(tmp[3]) * sizeof(char)); //동적 메모리 할당
	
	strcpy(client -> password, tmp[0]);
	strcpy(client -> name, tmp[1]);
	strcpy(client -> address, tmp[2]);
	strcpy(client -> phone_number, tmp[3]); //메모리 할당한 후 배열의 내용 복사해서 넣어주기
	
	printf("%d %s %s %s %s", client -> id, client -> password, client -> name, client -> address, client -> phone_number);
	// 디버깅 코드	
	
	fclose(client_ifp);
	fclose(book_ifp);
	fclose(borrow_ifp); //파일 닫기
}

CLIENT * client_read(void){ //함수 안에서 client 파일 내용 받아와서 CLIENT 구조체에 내용 넣는 함수 (만드는 중)
	FILE *client_ifp; 
	
	if ((client_ifp = fopen(PATH_CLIENT, READ_MOD)) == NULL){ //client 파일 읽어오기
		printf("client.txt 파일이 존재하지 않습니다.\n"); //파일 없으면 오류 메시지 출력
		exit(1); //프로그램 종료
	}
	
	CLIENT *head = NULL;
}
	


	
	
	
	
	
	
	
