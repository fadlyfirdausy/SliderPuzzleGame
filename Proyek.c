#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#define NROWS     4
#define NCOLLUMNS 4
//COLOR DEFINITION
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define LLBLUE 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define LGREY 7
#define GREY 8
#define LBLUE 9
#define LGREEN 10
#define LLLBLUE 11
#define PINK 12
#define LPURPLE 13
#define LYELLOW 14
#define WHITE 15

enum Move { MOVE_UP = 0, MOVE_DOWN = 1, MOVE_LEFT = 2, MOVE_RIGHT = 3 };
int holeRow;       
int holeCollumn;   
int cells[NROWS][NCOLLUMNS];
const int nShuffles = 100; //untuk nge shuffle 100x
void arrow(int posisiAsli,int posisiArrow);
void keluar();
void fullscreen();
void setTimeout(int milliseconds);
int pencet = 0;
void GameOver();
void setRes(const int pX, const int pY);
COORD setc(int x, int y);
typedef struct boxID_struct {
	COORD curs;
	int sizeX;
	int sizeY;
	int type;
	int color;
} boxID;


#define COLORFORG 1
#define COLORBACK 2
int getconsolecolor(int colortype);
COORD c(int x, int y);
#define PNULL -1
void printSuper(COORD cursor, int ForgC, int BackC, const char* val, ...);
#define BOX_LINES 1
#define BOX_FILL 2
boxID makebox(COORD curs, int sizeX, int sizeY, int color, int type) ;
#define DRAW 1
#define ERASE 0
#define UPDATE 2
boxID loopForBox(int state, boxID box_ID) ;
#define BOX_SETCOLOR 1
#define BOX_SETSIZEX 2
#define BOX_SETSIZEY 3
#define BOX_SETCURSOR 4
#define BOX_SETTYPE 5
boxID box(int state, boxID box_ID,...) ;

int main(){
	
	
	int i;
	int position = 1;
	int keyPressed = 0;
	setRes(1366, 768);
	fullscreen();
	system ("cls");
	system ("Color 8B");
	int x = 60;
	int y = 20;
	setc(x,y-1);
	for(i=0;i<45;i++)
	{
		printf("=");
		Sleep(25);
	}	
	setc(x,y); printf("|\t\tSlider Puzzle Game\t\t|");
	setc(x,y+1); printf("|\t\t\tv1.0\t\t\t|");
	setc(x,y+2);
	for(i=0;i<45;i++)
	{
		printf("=");
		Sleep(25);
	}
	
	while (keyPressed != 13){
	system ("cls");
	system ("Color 8B");
	setc(x,y-1);
	for(i=0;i<45;i++)
	{
		printf("=");
	}	
	setc(x,y); printf("|\t\tSlider Puzzle Game\t\t|");
	setc(x,y+1); printf("|\t\t\tv1.0\t\t\t|");
	setc(x,y+2);
	for(i=0;i<45;i++)
	{
		printf("=");
	}
	
	setc(x,y+3);printf("Select");
	setc(x,y+4);arrow(1,position); printf("1. New Game");
	setc(x,y+5);arrow(2,position); printf("2. Exit");
	
	keyPressed = getch();
	if(keyPressed == 80 && position != 2){
		position++;
		
	} else if (keyPressed == 72 && position != 1){
		position--;
	}else{
		position = position;
	}
}

	switch(position){
		case 1:
			position == '1';
			play();
			break;
		case 2:
			position == '2';
			keluar();
			break;
	}
getch();
}

void arrow(int posisiAsli,int posisiArrow){		//menampilkan arrow di main menu
	if(posisiAsli == posisiArrow){
		printf("--> -");
	} else{
		printf("     ");
	}
}
void keluar(){
	int i;
	int x = 60;
	int y = 20;
	system ("cls");
	setc(x,y+2);
	for(i=0;i<32;i++)
	{
		printf("=");
		Sleep(25);
	}
	
	setc(x,y+3);printf("THANK YOU FOR USING THIS PROGRAM");
	setc(x,y+4);
		for(i=0;i<32;i++)
	{
		printf("=");
		Sleep(25);
	}

}
 
int Perbarui(enum Move move){		//untuk menampilkan array setelah angka 0 dipindahkan
    const int dx[] = {  0,  0, -1, +1 };
    const int dy[] = { -1, +1,  0,  0 };
    int i = holeRow     + dy[move];
    int j = holeCollumn + dx[move];    
    if ( i >= 0 && i < NROWS && j >= 0 && j < NCOLLUMNS ){
        cells[holeRow][holeCollumn] = cells[i][j];
        cells[i][j] = 0; holeRow = i; holeCollumn = j;
        return 1;
    }
    return 0;
}
 
void Setup(void){		//mengisi array dan di random sebanyak 100x
    int i,j,k;
    for ( i = 0; i < NROWS; i++ )
        for ( j = 0; j < NCOLLUMNS; j++ )
            cells[i][j] = i * NCOLLUMNS + j + 1;
    cells[NROWS-1][NCOLLUMNS-1] = 0;
    holeRow = NROWS - 1;
    holeCollumn = NCOLLUMNS - 1;
    k = 0;
    while ( k < nShuffles )
        k += Perbarui((enum Move)(rand() % 4));
}
 
int Selesai(void){		//mendeteksi apakah array sudah sesuai berurutan atau belum
    int i,j; int k = 1;
    for ( i = 0; i < NROWS; i++ )
        for ( j = 0; j < NCOLLUMNS; j++ ) 
            if ( (k < NROWS*NCOLLUMNS) && (cells[i][j] != k++ ) )
                return 0;
    return 1;        
}
 
void View_showBoard(){		//menampilkan array (angka 1-15)
    int i,j;
    int x = 70;
	int y = 20;
    setc(x,y);
    box(DRAW,(makebox(c(69,19),20,5,BLUE,BOX_LINES)));
    for ( i = 0; i < NROWS; i++ )
        for ( j = 0; j < NCOLLUMNS; j++ ){
        	setc(x+4*j,y+i);
            if ( cells[i][j] )
                printf(j != NCOLLUMNS-1 ? "%d" : "%d", cells[i][j]);
            else
                printf(j != NCOLLUMNS-1 ? "%s" : "%s", "  ");  
        }
}
 
void View_displayMessage(char* text){
	int x = 60;
	int y = 20;
    setc(x,y+4);printf("%s", text);
}

int getch_nonblock() {
	if (_kbhit()) return _getch();
	else return -1;
}
 
enum Move Controller_getMove(void){			//input untuk memindahkan nilai 0
    int c;
    int x = 60;
    int y = 25;
       setc(x,y); printf("Press w/a/s/d To Move : ");
        switch ( getch() ){
            case 's' : pencet = pencet + 1; return MOVE_UP;   
            case 'w' : pencet = pencet + 1; return MOVE_DOWN;
            case 'd' : pencet = pencet + 1; return MOVE_LEFT;
            case 'a' : pencet = pencet + 1; return MOVE_RIGHT;
            case 27 : exit (0);
        }
}

int play(void){
 	system ("cls");
    srand((unsigned)time(NULL));
 	
    do Setup(); while ( Selesai() );
    View_showBoard();
    int time = 120;
    int score = 0;
    bool state[4] = {0};
    clock_t gameclock;
    gameclock = clock();
    clock_t dump_clock = gameclock;
    while( !Selesai() ){ 
    	gameclock = clock();
    	if(gameclock >= (dump_clock + (int)1000)){
    		time--;
    		dump_clock = gameclock;
    		setc(50,15); printf("TIME LEFT %2d:%2d ",(int)(time/60),time%60);
		}
        Perbarui( Controller_getMove() );
        setc(50,16); printf("MOVE LEFT %2d ",150-pencet);
        setc(50,17); printf("SCORE	   %2d ",score*100);
       	if (pencet == 150 || time <= 0){ // ganti step
       		GameOver();
       		return 0;
		   }
		int a;
		for(a=0;a<4;a++){
			if(state[a] == FALSE){
				if(cells[a][0+a] == a+1
				&& cells[a][1+a] == a+2
				&& cells[a][2+a] == a+3
				&& cells[a][3+a] == a+4){
					score++;
					time+=30;
					state[a] = TRUE;
				}
			}else if(state[a]==TRUE){
				if(cells[a][0+a] != a+1
				&& cells[a][1+a] != a+2
				&& cells[a][2+a] != a+3
				&& cells[a][3+a] != a+4){
					score--;
					state[a] = FALSE;
				}
			}
		}
        View_showBoard();
    }
    score += time;
    View_displayMessage("Congratulation!!! You win!");
    printf(" SCORE : %d",score*100);
 	getchar();
    return 0;
}

void setTimeout(int milliseconds)
{
    if (milliseconds <= 0) {
        fprintf(stderr, "Count milliseconds for timeout is less or equal to 0\n");
        return;
    }

    int milliseconds_since = clock() * 1000 / CLOCKS_PER_SEC;
    int end = milliseconds_since + milliseconds;

    do {
        milliseconds_since = clock() * 1000 / CLOCKS_PER_SEC;
    } while (milliseconds_since <= end);
}

void fullscreen()
{
keybd_event(VK_MENU,0x38,0,0);
keybd_event(VK_RETURN,0x1c,0,0);
keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}

void GameOver(){
	setc(60,25);printf("Step anda sudah habis! ");
}

int getconsolecolor(int colortype) {
	CONSOLE_SCREEN_BUFFER_INFO psBI;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &psBI);
	if (colortype == COLORFORG) {
		WORD dump = psBI.wAttributes >> 4 << 4;
		dump = psBI.wAttributes - dump;
		return (int)dump;
	}
	else if (colortype == COLORBACK) {
		return (int)psBI.wAttributes >> 4;
	}
}

void setRes(const int pX, const int pY) {
	DEVMODE devmode;
	devmode.dmPelsWidth = pX;
	devmode.dmPelsHeight = pY;
	devmode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
	devmode.dmSize = sizeof(DEVMODE);
	ChangeDisplaySettings(&devmode, 0);
	
}

COORD setc(int x, int y) {
	COORD cursor;
	cursor.X = x;
	cursor.Y = y;
	CONSOLE_SCREEN_BUFFER_INFO psBI;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &psBI);
	COORD pos;
	pos.X = cursor.X; pos.Y = cursor.Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	return pos;
}

COORD c(int x, int y){
	COORD curs;
	curs.X = x;
	curs.Y = y;
	return curs;
}

void printSuper(COORD cursor, int ForgC, int BackC, const char* val, ...) {
	CONSOLE_SCREEN_BUFFER_INFO psBI;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &psBI);
	if (cursor.X == -1) {
		cursor.X = psBI.dwCursorPosition.X;
	}
	if (cursor.Y == -1) {
		cursor.Y = psBI.dwCursorPosition.Y;
	}
	setc(cursor.X,cursor.Y);
	va_list arg_list;
	int my_arg;
	va_start(arg_list, val);
	int charlen = strlen(val);
	WORD wOldColorAttrs;
	wOldColorAttrs = psBI.wAttributes;
	if (ForgC == PNULL && BackC != PNULL) {
		WORD dump = wOldColorAttrs >> 4 << 4;
		dump = wOldColorAttrs - dump;
		WORD wColor = ((BackC & 0x0F) << 4 + dump);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
	}
	else if (BackC == PNULL && ForgC != PNULL) {
		WORD wColor = ((wOldColorAttrs >> 4) << 4 + (ForgC & 0x0F));
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
	}
	else if (ForgC != PNULL && BackC != PNULL) {
		WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
	}
	for (my_arg = 0; my_arg < charlen; my_arg++) {
		if (val[my_arg] == '%') {
			int r = 0;
			char value[16];
			while (my_arg < charlen) {
				value[r] = val[my_arg];
				value[r + 1] = 0;
				if (val[my_arg] == 'd' || val[my_arg] == 'c' || val[my_arg] == 's') {
					printf(value, va_arg(arg_list, int));
					break;
				}
				else if (val[my_arg] == 'f') {
					printf(value, va_arg(arg_list, double));
					break;
				}
				my_arg++; r++;
			}
		}
		else if (val[my_arg] != '%')printf("%c", val[my_arg]);
	}
	va_end(arg_list);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wOldColorAttrs);
}

boxID makebox(COORD curs, int sizeX, int sizeY, int color, int type) {
	boxID myBox;
	myBox.curs = curs;
	myBox.sizeX = sizeX;
	myBox.sizeY = sizeY;
	myBox.color = color;
	myBox.type = type;
	return myBox;
}

boxID loopForBox(int state, boxID box_ID) {
	if (box_ID.type == BOX_LINES) {
		int backg = getconsolecolor(GREY);
		int forg;
		if (state == DRAW) {
			forg = box_ID.color;
		}
		else if (state == ERASE) {
			forg = backg;
		}
		printSuper(box_ID.curs, forg, backg, "%c", 218);
		int a; for (a  = box_ID.curs.X; a < box_ID.curs.X + box_ID.sizeX; a++) printSuper(c(PNULL, PNULL), forg, backg, "%c", 196);
		printSuper(c(box_ID.curs.X + box_ID.sizeX, box_ID.curs.Y), forg, backg, "%c", 191);
		for (a  = box_ID.curs.Y + 1; a < box_ID.curs.Y + box_ID.sizeY; a++) {
			printSuper(c(box_ID.curs.X, a), forg, backg, "%c", 179);
			printSuper(c(box_ID.curs.X + box_ID.sizeX, a), forg, backg, "%c", 179);
		}
		printSuper(c(box_ID.curs.X, box_ID.curs.Y + box_ID.sizeY), forg, backg, "%c", 192);
		for (a  = box_ID.curs.X; a < box_ID.curs.X + box_ID.sizeX; a++) printSuper(c(PNULL, PNULL), forg, backg, "%c", 196);
		printSuper(c(box_ID.curs.X + box_ID.sizeX, box_ID.curs.Y + box_ID.sizeY), forg, backg, "%c", 217);
	}
	else if (box_ID.type == BOX_FILL) {
		int backg;
		if (state == DRAW) backg = box_ID.color;
		else backg = getconsolecolor(GREY);
		int i; for ( i  = 0; i < box_ID.sizeY; i++) {
			int j; for ( j = 0; j < box_ID.sizeX; j++) {
				printSuper(c((box_ID.curs.X + j), (box_ID.curs.Y + i)), backg, backg, " ");
			}
		}
	}
	return box_ID;
}

boxID box(int state, boxID box_ID,...) {
	if (state == UPDATE) {
		int eraseState = FALSE;
		boxID box_ID_Old = box_ID;
		va_list xcols;
		va_start(xcols, box_ID);
		int a;
		for (a = 0; a < 5; a++) {
			int Ttype = va_arg(xcols, int);
			if (Ttype < 1 || Ttype > 5) break;
			else if (Ttype == BOX_SETCOLOR) {
				box_ID.color = va_arg(xcols, int);
				if (eraseState != TRUE) eraseState = FALSE;
			}
			else if (Ttype == BOX_SETCURSOR) {
				box_ID.curs = va_arg(xcols, COORD);
				eraseState = TRUE;
			}
			else if (Ttype == BOX_SETSIZEX) {
				box_ID.sizeX = va_arg(xcols, int);
				if ((box_ID.sizeX < box_ID_Old.sizeX) && eraseState == FALSE) {
					eraseState = TRUE;
				}
			}
			else if (Ttype == BOX_SETSIZEY) {
				box_ID.sizeY = va_arg(xcols, int);
				if ((box_ID.sizeY < box_ID_Old.sizeY) && eraseState == FALSE) {
					eraseState = TRUE;
				}
			}
			else if (Ttype == BOX_SETTYPE) {
				box_ID.type = va_arg(xcols, int);
				if ((box_ID.type < box_ID_Old.type) && eraseState == FALSE) {
					eraseState = TRUE;
				}
			}
		}
		va_end(xcols);
		if(eraseState != FALSE) loopForBox(ERASE, box_ID_Old);
		loopForBox(DRAW, box_ID);
	}
	else {
		loopForBox(state, box_ID);
	}
	return box_ID;
}
