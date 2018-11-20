#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h> 

#define PRINT_INT(x) printf("\n"#x" : %d\n", x);
#define PRINT_CHAR(x) printf("\n"#x" : %c\n", x);
#define PRINT_STRING(x) printf("\n"#x" : %s\n", x);

/////////////////////////////////출력 관련 매크로

#define SCAN_INT(x) scanf("%d", &x);
#define SCAN_CHAR(x) scanf("%c", &x);
#define SCAN_STRING(x) scanf("%s", x);

/////////////////////////////////입력 관련 매크로

#define PATH_CLIENT "client.txt"
#define PATH_BOOK "book.txt"
#define PATH_BORROW "borrow.txt"

#define READ_MOD "rt"
#define WRITE_MOD "wt"

/////////////////////////////////파일 관련 매크로

#define MALLOC_CHAR(x, y) (x) -> y = (char *) malloc(strlen(y) * sizeof(char))
#define REALLOC_CHAR(x, y) (x) -> y = (char *) realloc((x) -> y, strlen(y) * sizeof(char))
#define MALLOC_STRUCT(x,y) y = (x *) malloc(sizeof(x))

/////////////////////////////////동적 메모리 할당 관련 매크로

#define SWAP_CHAR(x, y) {char temp; temp = x; x = y; y = temp;}
#define SWAP_INT(x, y) {int temp; temp = x; x = y; y = temp;}
#define SWAP_UNSIGNED(x, y) {unsigned temp; temp = x; x = y; y = temp;}
#define SWAP_UNSIGNED_LONG(x, y) {unsigned long temp; temp = x; x = y; y = temp;}
#define SWAP_STRING(x, y) {char temp[100]; strcpy(temp, x); strcpy(x, y); strcpy(y, temp);}
#define SWAP_CLIENT(x, y) {CLIENT *temp; temp = x; x = y; y = temp;}
#define SWAP_BOOK(x, y) {BOOK *temp; temp = x; x = y; y = temp;}

						  
/////////////////////////////////SWAP 관련 매크로
						  
#define CLEAR_BUFFER while(getchar() != '\n')
#define true 1
#define false 0

/////////////////////////////////기타 매크로

typedef struct client { //client 파일의 정보를 저장하기 위한 구조체
   char *id; //학번 (정수 8자리)
   char *password; //비밀번호
   char *name; //이름
   char *address; //주소
   char *phone_number; //전화번호
   struct client *next; //자기 참조 구조체 구현
} CLIENT;

typedef struct book { //book 파일의 정보를 저장하기 위한 구조체
   unsigned number; //도서번호 (정수 7자리)
   char *name; //도서명
   char *publisher; //출판사
   char *writer; //저자명
   char *ISBN; //ISBN(정수 13자리)
   char *location; //소장처
   char borrow; //대여가능 여부
   struct book *next; //자기 참조 구조체 구현
} BOOK;

typedef struct borrow { //borrow 파일의 정보를 저장하기 위한 구조체
   unsigned client_id; //학번 (정수 8자리)
   unsigned book_number; //도서번호 (정수 7자리)
   time_t borrow_date; //대여일자
   time_t return_date; //반납일자
   struct borrow *next; //자기 참조 구조체 구현
} BORROW;

/////////////////////////////////구조체 선언

CLIENT *client_read(void); //파일 정보 받아서 링크드 리스트 만들고 정렬하여 파일에 저장하는 함수

CLIENT *create_client(char id[], char password[], char name[], char address[], char
   phone_number[]); //client의 멤버들에 동적 메모리 할당을 해준 뒤 리턴하는 함수
   
void add_client(CLIENT *new_client, CLIENT **head); //새로운 구조체를 링크드 리스트에 연결해주는 함수

CLIENT *sort_client(CLIENT *head); //client 링크드 리스트를 학번순으로 정렬

int compare_client(const void *p, const void *q); //qsort에 사용할 compare 함수

void print_all_client(CLIENT *head); //client 링크드 리스트의 내용을 전부 출력

void print_one_client(CLIENT *head, int location); //clinet 링크드 리스트의 내용을 하나만 출력

void save_client(CLIENT *head); //client 파일에 메모리에 있는 client 링크드 리스트를 저장

void signup_client(CLIENT *head); //회원가입용 함수

int checkname_client(CLIENT *head, char name[]); //client 파일 같은 이름이 몇번째에 있는지 리턴

int checkid_client(CLIENT *head, char id[]); //client 파일에 매개 인자로 받은 학번과 중복 학번이 없으면 -1을 리턴, 있으면
 // head에서 몇번 움직여야 중복인게 나오는지 숫자를 리턴하는 함수
 
int checkpw_client(CLIENT *head, char password[]); //id 말고 password 리턴하는 함수
 
void login_client(CLIENT *head); //로그인 한 뒤 head에서 몇번 움직여야 내 정보로 갈 수 있는지 my_account에 저장하는 함수

void edit_client(CLIENT **head_p); //내 회원 정보를 수정하는 함수

void remove_client(CLIENT **head_p); //회원 탈퇴 함수

void logout_client(void); //로그아웃 함수

void cal_time();

/////////////////////////////////client 관련 함수 선언

BOOK *book_read(void);

BOOK *create_book(unsigned number, char name[], char publisher[], char writer[], char
	ISBN[], char location[], char borrow);

void add_book(BOOK *new_book, BOOK **head_p);

BOOK *sort_book(BOOK *head);

int book_number_check(BOOK *head);

void bookname_search(BOOK *head);

void publisher_search(BOOK *head);

void ISBN_search(BOOK *head);

void writer_search(BOOK *head);

void total_search(BOOK *head);

/////////////////////////////////book 관련 함수 선언

void main_menu_print(void);

void main_menu(CLIENT *client_head, BOOK *book_head, BORROW *borrow_head);

void client_menu_print(void);

void client_menu(CLIENT *client_head, BOOK *book_head, BORROW *borrow_head);

void admin_menu_print(void);

void admin_menu(CLIENT *client_head, BOOK *book_head, BORROW *borrow_head);

void search_menu_print(void);

void search_menu(CLIENT *client_head);

void booksearch_menu_print(void);

/////////////////////////////////메뉴 함수 선언 

int my_account = 0; //로그인 정보를 저장할 전역 변수

int main(void) {
	CLIENT *client_head = client_read();
	BOOK *book_head = book_read();
	BORROW *borrow_head;

	// total_search(book_head);
	// print_all_client(client_head);

	main_menu(client_head, book_head, borrow_head);

	return 0;
}

CLIENT *client_read(void) { //함수 안에서 client 파일 내용 받아와서 CLIENT 구조체에 내용 넣는 함수 (만드는 중)
	FILE *client_ifp; //client 파일 내용 받아오는 포인터 변수

	if ((client_ifp = fopen(PATH_CLIENT, READ_MOD)) == NULL) { //client 파일 읽어오기
	  printf("client.txt 파일이 존재하지 않습니다.\n"); //파일 없으면 오류 메시지 출력
	  exit(1); //프로그램 종료
	}


	CLIENT *head; //client 구조체 포인터 변수

	char id[10]; //학번 (정수 8자리)
	char password[20]; //비밀번호
	char name[25]; //이름
	char address[100]; //주소
	char phone_number[30]; //전화번호   

	MALLOC_STRUCT(CLIENT, head); //client 구조체 포인터변수에 메모리 할당

	head -> next = NULL; //시작 부분

	// id | password | name | address | phone_number : client 파일 데이터 형식
	//client 파일에서 한줄 fscanf로 받아와서 자료형에 넣어주기

	while (fscanf(client_ifp, "%s | %s | %s | %[^|] | %s", id, password, name, address,
	phone_number) != EOF){
		add_client(create_client(id, password, name, address, phone_number), &head);
	}
	fclose(client_ifp);
	
	head = sort_client(head);

	return head;
}

void add_client(CLIENT *new_client, CLIENT **head_p) {
	//**head_p로 head 포인터의 주소값을 받아와서 *head_p가 가리키는 구조체의 값을 변경해줘야됨
	//*head로 받아오면 값에 의한 호출이라 안바뀜
	//head는 포인터이므로 **으로 이중포인터 표현 사용
	//add_client를 호출할 때 매개인자에 head의 주소값을 넣어주면 됨
	
	if ((*head_p) -> next == NULL) {      //자료가 첫번째로 입력될 때
		new_client -> next = new_client;
		*head_p = new_client;
	}
	else if ((*head_p) -> next == (*head_p)){ //자료가 두번째로 입력될 때
		(*head_p) -> next = new_client;
		new_client -> next = NULL;
	}
	else {                     //자료가 세번째 이후로 입력될 때
		new_client -> next = (*head_p) -> next;  //이전의 노드가 마지막 노드
		(*head_p) -> next = new_client;  //처음 노드가 새로 추가된 노드를 가리킴
	}

}

CLIENT *create_client(char id[], char password[], char name[], char address[], char
   phone_number[]) {
	CLIENT *new_client;

	MALLOC_STRUCT(CLIENT, new_client); //client 구조체 포인터변수에 메모리 할당

	MALLOC_CHAR(new_client, id);
	MALLOC_CHAR(new_client, password); //new_client -> password에 메모리 할당
	MALLOC_CHAR(new_client, name); //new_client -> name에 메모리 할당
	MALLOC_CHAR(new_client, address);
	MALLOC_CHAR(new_client, phone_number); //new_client -> phone_number에 메모리 할당

	strcpy(new_client -> id, id);
	strcpy(new_client -> password, password);
	strcpy(new_client -> name, name);
	strcpy(new_client -> address, address);
	strcpy(new_client -> phone_number, phone_number);
	new_client -> next = NULL;

	return new_client;
}

CLIENT *sort_client(CLIENT *head){
	CLIENT *temp = head;
	
	int i, j, cnt = 0;
	
	while(temp){
		temp = temp -> next;
		cnt++;
	}
	
	CLIENT **sort = (CLIENT **) malloc(sizeof(CLIENT *) * cnt);
	
	for (i = 0, temp = head; i < cnt; temp = temp -> next)
		sort[i++] = temp;
	
	for (i = 0; i < cnt - 1; i++){
		for (j = i + 1; j < cnt; j++){
			if (atoi(sort[i] -> id) > atoi(sort[j] -> id))
				SWAP_CLIENT(sort[i], sort[j]);
		}
	}
	
	head = sort[0];
	
	for (i = 1, temp = head; i < cnt && temp; temp = temp -> next)
		temp -> next = sort[i++];
	temp -> next = NULL;
	
	free(sort);
	
	return head;
}

void print_all_client(CLIENT *head){
	while (head){
		printf("%s | %s | %s | %s| %s\n", head -> id, head -> password, head -> name, 
		head -> address, head -> phone_number);
		head = head -> next;
	}		
}	

void print_one_client(CLIENT *head, int location){
	for (int i = 0; i < location; i++)
		head = head -> next;
	printf("학번 : %s\n", head -> id);
	printf("비밀번호 : %s\n", head -> password);
	printf("이름 : %s\n", head -> name);
	printf("주소 : %s\n", head -> address);
	printf("전화번호 : %s\n", head -> phone_number);
}	

void save_client(CLIENT *head){
	FILE *client_ofp = fopen(PATH_CLIENT, WRITE_MOD);
	while(head){
		fprintf(client_ofp, "%s | %s | %s | %s| %s\n", head -> id, head -> password, head -> name,
		head -> address, head -> phone_number);
		head = head -> next;
	}
	fclose(client_ofp);
}

void signup_client(CLIENT *head){	
	char id[10]; //학번 (정수 8자리)
	char password[20]; //비밀번호
	char name[25]; //이름
	char address[100]; //주소
	char phone_number[20]; //전화번호  
		
	printf("\n>> 회원 가입 <<\n");
	printf("학번, 비밀번호, 이름, 주소, 전화번호를 입력하세요.\n\n");
	printf("학번 : ");
	SCAN_STRING(id); //학번 입력받기
	
	while (checkid_client(head, id) != -1){ //학번 중복 체크 하는 부분
		printf("이미 있는 학번입니다. 다시 입력해주세요.\n");
		printf("학번 : ");
		SCAN_STRING(id);
	}
	
	printf("비밀번호 : ");
	SCAN_STRING(password); //비밀번호 입력받기
	printf("이름 : ");
	SCAN_STRING(name); //이름 입력받기
	CLEAR_BUFFER; //버퍼 초기화
	printf("주소 : "); 
	gets(address); //주소 입력받기
	printf("전화번호 : "); 
	SCAN_STRING(phone_number); //전화번호 입력받기
	
	add_client(create_client(id, password, name, address, phone_number), &head);
	head = sort_client(head);
	save_client(head);
}

int checkname_client(CLIENT *head, char name[]){
	int res = -1;
	int cnt = 0;
	
	while (head){
		if (!strcmp(name, head -> name))
			res = cnt;
		head = head -> next;
		cnt++;
	}
	
	return res;
}

int checkid_client(CLIENT *head, char id[]){
	int res = -1;
	int cnt = 0;
	
	while (head){
		if (!strcmp(id, head -> id))
			res = cnt;
		head = head -> next;
		cnt++;
	}
	
	return res;
}

int checkpw_client(CLIENT *head, char password[]){
	int res = -1;
	int cnt = 0;
	
	while (head){
		if (!strcmp(password, head -> password))
			res = cnt;
		head = head -> next;
		cnt++;
	}
	
	return res;
}

void login_client(CLIENT *head){
	char id[10];
	char password[20];
	
	int res;
	
	printf("\n>> 로그인 <<\n");
	printf("학번 : ");
	SCAN_STRING(id);
	printf("비밀번호 : ");
	SCAN_STRING(password);
	
	while ((res = checkid_client(head, id)) != checkpw_client(head, password)
			|| res == -1){
		printf("아이디 혹은 비밀번호가 틀렸습니다.\n");
		printf("다시 입력해주세요.\n\n");
		printf("학번 : ");
		SCAN_STRING(id);
		printf("비밀번호 : ");
		SCAN_STRING(password);
	}
	
	printf("\n>> 로그인 성공 <<\n");
	
	my_account = res;
}

void logout_client(void){
	printf("\n>> 로그아웃 되었습니다.<<\n");
	my_account = 0;
}

void remove_client(CLIENT **head_p){
	CLIENT *previous = *head_p, *after = *head_p, *temp;
	
	if (my_account == 0){
		putchar('A');
		temp = (*head_p) -> next;
		free((*head_p) -> id);
		free((*head_p) -> password);
		free((*head_p) -> name);
		free((*head_p) -> address);
		free((*head_p) -> phone_number);
		free((*head_p));
		(*head_p) = temp;
	}
	else {		
		for (int i = 0; i < my_account - 1; i++){
			previous = previous -> next;
		}
		
		for (int i = 0; i < my_account + 1; i++){
			after = after -> next;
		}
		previous -> next = after;
	}	
	
	logout_client();
	
	printf("탈퇴되었습니다.\n");
}
		
void edit_client(CLIENT **head_p){
	CLIENT *temp = *head_p;

	char password[20]; //비밀번호
	char address[100]; //주소
	char phone_number[20]; //전화번호 

	printf("\n>> 개인정보 수정 <<\n");
	print_one_client((*head_p), my_account);
	printf("\n수정할 정보를 입력해주세요\n");
	printf("비밀번호 : ");	
	SCAN_STRING(password);
	CLEAR_BUFFER;
	printf("주소 : ");
	gets(address);
	printf("전화번호 : ");
	SCAN_STRING(phone_number);


	address[strlen(address)] = ' '; //주소 마지막칸 띄어쓰기 해주기
	address[strlen(address) + 1] = '\0'; //널문자 넣어주기

	for (int i = 0; i < my_account; i++)
		*head_p = (*head_p) -> next;

	// free((*head_p) -> name); //왜 이거 안되는지 이해가 안가 ㅡ.ㅡ
	// free((*head_p) -> address);
	// free((*head_p) -> phone_number);

	MALLOC_CHAR(*head_p, password); //head -> password에 메모리 할당 
	MALLOC_CHAR(*head_p, address); //head -> address에 메모리 할당
	MALLOC_CHAR(*head_p, phone_number); //head -> phone_number에 메모리 할당

	strcpy((*head_p) -> password, password);
	strcpy((*head_p) -> address, address);
	strcpy((*head_p) -> phone_number, phone_number);

	(*head_p) = temp;
}

////////////////////////////////////////////////////////////////////////////////////

BOOK *book_read(void) { //함수 안에서 book 파일 내용 받아와서 BOOK 구조체에 내용 넣는 함수
	FILE *book_ifp; //book 파일 내용 받아오는 포인터 변수

	if ((book_ifp = fopen("book.txt", READ_MOD)) == NULL) { //book 파일 읽어오기
		printf("book.txt 파일이 존재하지 않습니다.\n"); //파일 없으면 오류 메시지 출력
		exit(1); //프로그램 종료
	}

	BOOK *head; //book 구조체 포인터 변수

	unsigned number;
	char name[70]; //도서명
	char publisher[40]; //출판사
	char ISBN[20]; //ISBN(정수 13자리)
	char writer[40]; //저자명
	char location[40]; //소장처
	char borrow;

	MALLOC_STRUCT(BOOK, head); //book 구조체 포인터변수에 메모리 할당

	head -> next = NULL; //시작 부분

	// id | password | name | address | phone_number : client 파일 데이터 형식
	//client 파일에서 한줄 fscanf로 받아와서 자료형에 넣어주기

	fseek(book_ifp, 3, SEEK_SET); // 개같은거 넘기기

	while (fscanf(book_ifp, "%u | %[^|] | %[^|] | %[^|] | %s | %[^|] | %c\n", &number, name, publisher, writer, ISBN, location, &borrow) != EOF){
		add_book(create_book(number, name, publisher, writer, ISBN, location, borrow), &head);
	}
	fclose(book_ifp);

	head = sort_book(head);

	return head;
}

BOOK *create_book(unsigned number, char name[], char publisher[], char writer[], char
	ISBN[], char location[], char borrow){
		BOOK *new_book;

		MALLOC_STRUCT(BOOK, new_book);

		MALLOC_CHAR(new_book, name);
		MALLOC_CHAR(new_book, publisher);
		MALLOC_CHAR(new_book, writer);
		MALLOC_CHAR(new_book, ISBN);
		MALLOC_CHAR(new_book, location);

		new_book -> number = number;
		strcpy(new_book -> name, name);
		strcpy(new_book -> publisher, publisher);
		strcpy(new_book -> writer, writer);
		strcpy(new_book -> ISBN, ISBN);
		strcpy(new_book -> location, location);
		new_book -> borrow = borrow;

		return new_book;
	}

void add_book(BOOK *new_book, BOOK **head_p){
	if ((*head_p) -> next == NULL){
		new_book -> next = new_book;
		*head_p = new_book;
	}
	else if ((*head_p) -> next == *head_p){
		(*head_p) -> next = new_book;
		new_book -> next = NULL;
	}
	else {
		new_book -> next = (*head_p) -> next;
		(*head_p) -> next = new_book;
	}
}

BOOK *sort_book(BOOK *head){
	BOOK *temp = head;
	
	int i, j, cnt = 0;
	
	while(temp){
		temp = temp -> next;
		cnt++;
	}
	
	BOOK **sort = (BOOK **) malloc(sizeof(BOOK *) * cnt);
	
	for (i = 0, temp = head; i < cnt; temp = temp -> next)
		sort[i++] = temp;
	
	for (i = 0; i < cnt - 1; i++){
		for (j = i + 1; j < cnt; j++){
			if (atol(sort[i] -> ISBN) > atol(sort[j] -> ISBN)){ 
				//ISBN 숫자가 커서 오버플로가 발생하므로 atol을 사용해야함
				SWAP_BOOK(sort[i], sort[j]);
			}
			else if (atol(sort[i] -> ISBN) == atol(sort[j] -> ISBN)){ 
				//ISBN이 같을 때 도서번호 순으로 정렬
				if (sort[i] -> number > sort[j] -> number)
					SWAP_BOOK(sort[i], sort[j]);
			}
		}
	}

	head = sort[0];
	
	for (i = 1, temp = head; i < cnt && temp; temp = temp -> next)
		temp -> next = sort[i++];
	temp -> next = NULL;
	
	free(sort);
	
	return head;
}

int book_number_check(BOOK *head){
	
}

// void bookname_search(BOOK *head){
//   int i, N;
//   char bookname[30];
//   printf("도서명을 입력하세요 : ");
//   gets(bookname);
//   N = book_number_check(BOOK *head);
//   char *ptr[N];
//   for(i=0 ; i<N ; i++){
//     ptr[i] = strstr(BOOK->name, bookname);
//     if(ptr[i]!=NULL){
//       printf("도서명: %s\n", BOOK->name);
//       printf("출판사: %s\n", BOOK->publisher);
//       printf("저자명: %s\n", BOOK->writer);
//       printf("ISBN: %s\n", BOOK->ISBN);
//       printf("소장처: %s\n", BOOK->location);
//       printf("대여가능 여부: %s\n", BOOK.borrow); //TODO (n/2)는 borrow기능 만들고 해야함
//       printf("** Y는 대여가능, N은 대여불가를 의미\n");
//       printf("** (x/y) : (대여된 총 권수 / 보유하고 있는 총 권수)\n",);
//     }
//     BOOK = BOOK->next;
//   }
// }

// void publisher_search(BOOK *head){
//   int i, N;
//   char publishername[30];
//   printf("출판사를 입력하세요 : ");
//   gets(publishername);
//   N = book_number_check(BOOK *head);
//   char *ptr[N];
//   for(i=0 ; i<N ; i++){
//     ptr[i] = strstr(BOOK->name, bookname);
//     if(ptr[i]!=NULL){
//       printf("도서명: %s\n", BOOK->name);
//       printf("출판사: %s\n", BOOK->publisher);
//       printf("저자명: %s\n", BOOK->writer);
//       printf("ISBN: %s\n", BOOK->ISBN);
//       printf("소장처: %s\n", BOOK->location);
//       printf("대여가능 여부: %s\n", BOOK.borrow); //TODO (n/2)는 borrow기능 만들고 해야함
//       printf("** Y는 대여가능, N은 대여불가를 의미\n");
//       printf("** (x/y) : (대여된 총 권수 / 보유하고 있는 총 권수)\n",);
//     }
//     BOOK = BOOK->next;
//   }
// }

// void ISBN_search(BOOK *head){
//   int i, N;
//   char ISBN_num[30];
//   printf("ISBN을 입력하세요 : ");
//   gets(ISBN_num);
//   N = book_number_check(BOOK *head);
//   char *ptr[N];
//   for(i=0 ; i<N ; i++){
//     ptr[i] = strstr(BOOK->name, bookname);
//     if(ptr[i]!=NULL){
//       printf("도서명: %s\n", BOOK->name);
//       printf("출판사: %s\n", BOOK->publisher);
//       printf("저자명: %s\n", BOOK->writer);
//       printf("ISBN: %s\n", BOOK->ISBN);
//       printf("소장처: %s\n", BOOK->location);
//       printf("대여가능 여부: %s\n", BOOK.borrow); //TODO (n/2)는 borrow기능 만들고 해야함
//       printf("** Y는 대여가능, N은 대여불가를 의미\n");
//       printf("** (x/y) : (대여된 총 권수 / 보유하고 있는 총 권수)\n",);
//     }
//     BOOK = BOOK->next;
//   }
// }

// void writer_search(BOOK *head){
//   int i, N;
//   char writername[30];
//   printf("저자명을 입력하세요 : ");
//   gets(writername);
//   N = book_number_check(BOOK *head);
//   char *ptr[N];
//   for(i=0 ; i<N ; i++){
//     ptr[i] = strstr(BOOK->name, bookname);
//     if(ptr[i]!=NULL){
//       printf("도서명: %s\n", BOOK->name);
//       printf("출판사: %s\n", BOOK->publisher);
//       printf("저자명: %s\n", BOOK->writer);
//       printf("ISBN: %s\n", BOOK->ISBN);
//       printf("소장처: %s\n", BOOK->location);
//       printf("대여가능 여부: %s\n", BOOK.borrow); //TODO (n/2)는 borrow기능 만들고 해야함
//       printf("** Y는 대여가능, N은 대여불가를 의미\n");
//       printf("** (x/y) : (대여된 총 권수 / 보유하고 있는 총 권수)\n",);
//     }
//     BOOK = BOOK->next;
//   }
// }

// void total_search(BOOK *head){
//   int i;
//   N = book_number_check(BOOK *head);
//   char *ptr[N];
//   for(i=0 ; i<N ; i++){
//     if(ptr[i]!=NULL){
//       printf("도서명: %s | ", BOOK->name);
//       printf("출판사: %s | ", BOOK->publisher);
//       printf("저자명: %s | ", BOOK->writer);
//       printf("ISBN: %s | ", BOOK->ISBN);
//       printf("소장처: %s | ", BOOK->location);
//       printf("대여가능 여부: %s | ", BOOK.borrow); //TODO (n/2)는 borrow기능 만들고 해야함
//       printf("** Y는 대여가능, N은 대여불가를 의미\n");
//       printf("** (x/y) : (대여된 총 권수 / 보유하고 있는 총 권수)\n",);
//     }
//     BOOK = BOOK->next;
//   }
// }

void total_search(BOOK *head){
	while(head){
		printf("%u | %s| %s| %s| %s | %s| %c\n", head -> number, head -> name,
		head -> publisher, head -> writer, head -> ISBN, head -> location,
		head -> borrow);
		head = head -> next;
	}
}



////////////////////////////////////////////////////////////////////////////////////

void main_menu_print(void){ // 메뉴 프린트 함수
   printf("\n>> 도서관 서비스 <<\n");
   printf("1. 회원가입   2. 로그인   3. 프로그램 종료\n");
   printf("번호를 선택하세요 : ");
}


void main_menu(CLIENT *client_head, BOOK *book_head, BORROW *borrow_head){ // 초기 메인 메뉴
	int num;
	while(1){
		main_menu_print();
		scanf("%d", &num);
		CLEAR_BUFFER;
		switch(num){
			case 1:
				signup_client(client_head);
				save_client(client_head);
				//회원가입
				break;
			case 2:
				login_client(client_head);
				if (my_account)
					client_menu(client_head, book_head, borrow_head);
				else
					admin_menu(client_head, book_head, borrow_head);
				//로그인
				break;
			case 3:
				exit(0);
				//프로그램 종료
			default :
				printf("잘못된 번호입니다. 다시 입력하세요");
				sleep(2);
				system("clear");
		}
	}
}
   
void client_menu_print(void){ //회원 메뉴 프린트 함수
   printf("\n>> 회원 메뉴 <<\n");
   printf("1. 도서 검색      2. 내 대여 목록\n");
   printf("3. 개인정보 수정      4. 회원 탈퇴\n");
   printf("5. 로그아웃      6. 프로그램 종료\n");
}

void client_menu(CLIENT *client_head, BOOK *book_head, BORROW *borrow_head){ //회원 메뉴 전체
	int num;
	while(1){
		client_menu_print();
		scanf("%d", &num);
		CLEAR_BUFFER;
		switch(num){
			case 1:
				//도서검색
				break;
			case 2:
				//내 대여 목록
				break;
			case 3:
				edit_client(&client_head);
				save_client(client_head);
				//개인정보 수정
				break;
			case 4:
				remove_client(&client_head);
				save_client(client_head);
				//회원 탈퇴
				return;
			case 5:
				logout_client();
				//로그아웃
				return;
			case 6:
				exit(0);
				//프로그램 종료
			default :
				printf("잘못된 번호입니다. 다시 입력하세요");
				sleep(2);
				system("clear");
		}
	}
}
   
void admin_menu_print(void){
   printf("\n>> 관리자 메뉴 <<\n");
   printf("1. 도서 등록      2. 도서 삭제\n");
   printf("3. 도서 대여      4. 도서 반납\n");
   printf("5. 도서 검색      6. 회원 목록\n");
   printf("7. 로그아웃      8. 프로그램 종료\n");
}

void admin_menu(CLIENT *client_head, BOOK *book_head, BORROW *borrow_head){
	int num;
	while(1){
		admin_menu_print();
		scanf("%d", &num);
		CLEAR_BUFFER;
		switch(num){
			case 1:				
				//도서 등록
				break;
			case 2:
				//도서 삭제
				break;
			case 3:
				//도서 대여
				break;
			case 4:
				//도서 반납
				break;
			case 5:
				//도서 검색
				break;
			case 6:
				search_menu(client_head);
				//회원 목록
				break;
			case 7:
				logout_client();
				//로그아웃
				return;
			case 8:
				exit(0);
				//프로그램 종료
			 default :
				printf("잘못된 번호입니다. 다시 입력하세요");
				sleep(2);
				system("clear");
		}
	}
}

void search_menu_print(void){
	printf("\n>> 회원 목록 << \n");
	printf("1. 이름 검색	2. 학번 검색\n");
	printf("3. 전체 검색	4. 이전 메뉴\n");
}

void search_menu(CLIENT *client_head){
	int num, location;
	char name[25], id[10];
	while(1){
		search_menu_print();
		scanf("%d", &num);
		CLEAR_BUFFER;
		switch(num){
			case 1:		
				printf("검색할 이름 : ");
				SCAN_STRING(name);
				if ((location = checkname_client(client_head, name)) == -1)
					printf("없는 이름입니다.\n");
				else
					print_one_client(client_head, location);
				//이름 검색
				break;
			case 2:
				printf("검색할 학번 : ");
				SCAN_STRING(id);
				if ((location = checkid_client(client_head, id)) == -1)
					printf("없는 학번입니다.\n");
				else
					print_one_client(client_head, location);
				//학번 검색
				break;
			case 3:
				print_all_client(client_head);
				//전체 검색
				break;
			case 4:
				//이전 메뉴
				return;
			 default :
				printf("잘못된 번호입니다. 다시 입력하세요");
				sleep(2);
				system("clear");
		}
	}
}

void booksearch_menu_print(void){
   printf(">> 도서 검색 <<\n");
   printf("1. 도서명 검색 2. 출판사 검색\n");
   printf("3. ISBN 검색 4. 저자명 검색\n");
   printf("5. 전체 검색 6. 이전 메뉴\n");
}

void cal_time(void){
	struct tm *t;
	time_t now;
	time_t RETURN;
	char *day;
	int flag = 0;
	now = time(NULL);
	t = localtime(&now);
	switch(t -> tm_wday){
		case 0:
			day = "일";
			break;
		case 1:
			day = "월";
			break;
		case 2:
			day = "화";
			break;
		case 3:
			day = "수";
			break;
		case 4:
			day = "목";
			break;
		case 5:
			day = "금";
			break;
		case 6:
			day = "토";
			break;
	}
	printf("대여일자 : %d년 %d월 %d일 %s요일\n", 1900 + t -> tm_year, t -> tm_mon + 1, t -> tm_mday, day);
	
	RETURN = time(NULL) + (60 * 60 * 24 * 30);
	t = localtime(&RETURN);
	if ((t -> tm_wday) == 0)
		RETURN = (time(NULL) + ( 60 * 60 * 24 * 29));
	t = localtime(&RETURN);
	switch(t -> tm_wday){
		case 0:
			day = "일";
			break;
		case 1:
			day = "월";
			break;
		case 2:
			day = "화";
			break;
		case 3:
			day = "수";
			break;
		case 4:
			day = "목";
			break;
		case 5:
			day = "금";
			break;
		case 6:
			day = "토";
			break;
	}
	
	printf("반납일자 : %d년 %d월 %d일 %s요일\n", 1900 + t -> tm_year, t -> tm_mon + 1, t -> tm_mday, day);
}
   		
	
	


	
	
	
	

	
