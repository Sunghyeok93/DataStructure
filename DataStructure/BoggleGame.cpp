#include <stdio.h>
#include <assert.h>
#include <string.h>
#define TRUE (1)
#define FALSE (0)
#define MAX_BSIZE 1000

typedef struct _relativeCoordinate
{
	int y;  /* y 상대 좌표 */
	int x;  /* x 상대 좌표 */
}RCoordinate;

int initBoard(FILE *fp); 
int boggleGame(const char *searchWord);
int hasWord(int y, int x, const char * word);
int inRange(int y,int x);

int maxY;   /* y좌표의 최대값 저장 */
int maxX;   /* x좌표의 최대값 저장 */

RCoordinate RCXY[8] = { {-1,-1},{-1,0},{-1,1},{1,-1},{1,0},{1,1},{0,-1},{0,1} }; /* 상대 좌표 목록 배열 */
/* ( 0, 0 )을 기준위치로 볼때의 상대좌표 표기 

(-1,-1) ( 0,-1) ( 1,-1)
(-1, 0) ( 0, 0) ( 1, 0)
(-1, 1) ( 0, 1) ( 1, 1)  
*/
char board[MAX_BSIZE][MAX_BSIZE+2];  /* NULL문자의 크기를 고려해서 column에 +1 */

/*----------------------------------------------------------------------------------------
 함수명 : main() 
----------------------------------------------------------------------------------------*/
int main()
{
	FILE *fp;
	int res;  /* 단어 검색 성공 시 1, 실패 시 0 저장 */
	char *searchWord[] = {"PRETTY", "LGE", "ASDVX"};
	int count=0;  /* 게임 횟수 누적변수 */


	fp=fopen("d:\\data\\boggleGame.txt", "rt");
	assert(fp != NULL);

	while(initBoard(fp))
	{
		res = boggleGame(searchWord[count]); /* 보글 게임 함수 호출 */

		if(res == TRUE)  /* 단어를  찾았으면 */
			printf("+ Existence!!(%s)\n", searchWord[count]);
		else   /* 단어를 못찾았으면 */
			printf("- Nonexistence!!(%s)\n", searchWord[count]);
		++count;
	}

	fclose(fp);

	return 0;
}
/*--------------------------------------------------------------------------------------
  함수명 및 기능: initBoard() - 파일에서 보글 게임의	 board정보를 입력 받아 초기화하는 함수
  전달인자 : fp - board정보를 저장하고 있는 파일의 파일 포인터
  리턴값: board정보를 정상적으로 초기화 하면 1리턴, 실패하면 0 리턴
--------------------------------------------------------------------------------------*/
int initBoard(FILE *fp)
{
	int i; /* iterator */
	fscanf(fp, "%d %d\n", &maxY, &maxX);  /* 문자의 가로 개수와 세로 개수 읽기 */
	if(maxY==0 || maxX==0) return FALSE;  /* 가로 또는 세로 크기가 0이면 초기화 실패 */

	for(i=0; i< maxY; ++i)
	{
		fgets(board[i], maxX+2, fp); /* 개행문자와 널문자의 크기 고려해서 +2 */
		board[i][maxX]='\0';  /* 함께 읽혀들어온 한 줄 뒤의 개행문자 삭제 */
		puts(board[i]);  /* 읽어들인 배열 출력 */
	}
	return TRUE;  /* board 초기화 성공 */
}
/*--------------------------------------------------------------------------------------
  함수명 및 기능: boggleGame() - board에 전달된 문자열이 있는가 검사하는 함수 
  전달인자 : searchWord - 검색할 단어문자열의 시작주소
  리턴값: board에 찾는 문자열이 있으면 1리턴, 없으면 0리턴
--------------------------------------------------------------------------------------*/
int boggleGame(const char *searchWord)
{
	int i,j;  /* iterator */
	int res;  /* 단어 검색 성공여부 저장 */ 
	for(i=0; i<maxY; ++i)
	{
		for(j=0; j<maxX; ++j)
		{
			res = hasWord(i, j, searchWord); /* 배열 전체의 각 방을 단어 검색 시작점으로 설정하여 반복 호출 함 */
			if(res == TRUE)  /* 단어를 찾았으면 바로 TRUE 리턴 */ 
				return TRUE;
		}
	}
	return FALSE;
}
/*--------------------------------------------------------------------------------------
  함수명 및 기능: inRange() - 전달된 y, x 좌표의 유효성 검사 함수
  전달인자 : y - 유효성 검사할 y 좌표
             x - 유효성 검사할 y 좌표
  리턴값: y,x 좌표가 모두 유효하면 1리턴, 한 좌표라도 유효하지 않으면 0 리턴
--------------------------------------------------------------------------------------*/
int inRange(int y,int x)
{
	if(y>=0 && y<maxY && x>=0 && x<maxX) 
		return TRUE;
	else 
		return FALSE;
}
/*--------------------------------------------------------------------------------------
  함수명 및 기능: hasWord() - 전달된 y, x 좌표에 찾는 문자가 존재하는가 검사하는 재귀함수
  전달인자 : y - 검사할 y 좌표
             x - 검사할 x 좌표
			 word - 검사할 문자열의 시작주소
  리턴값: 해당좌표에 찾는 문자 있으면 1리턴, 좌표가 유효하지 않거나 찾는 문자 없으면 0리턴
--------------------------------------------------------------------------------------*/
int hasWord(int y, int x, const char * word)
{
	int i;  /* iterator */
	int nextY; /* 다음에 검사할 Y좌표 저장 */
	int nextX; /* 다음에 검사할 X좌표 저장 */

	if( !inRange(y,x) ) /* 기본 부분(Basis part) 1 : 시작 위치가 범위 밖이면 실패 */
		return FALSE; 

	if(board[y][x] != word[0]) /* 기본 부분(Basis part) 2 : word문자열의 첫 글자가 x, y 좌표의 내용과 일치하지 않으면 실패 */
		return FALSE; 
	
	if(strlen(word)==1)  /* 기본 부분(Basis part) 3 : 단어의 길이가 1이면 성공 <== 기본 부분 2보다 반드시 나중에 검사해야 함 */ 
		return TRUE;

	for(i=0; i<8; ++i){   /* 8방향에 대해 이어지는 스펠링이 존재하는가 검사 */
		nextY = y + RCXY[i].y;
		nextX = x + RCXY[i].x;

		if(hasWord(nextY, nextX, word+1))
			return TRUE;
	}
	return FALSE;
}
