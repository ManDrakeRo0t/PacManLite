#include <conio.h>
#include <stdio.h>
#include <malloc.h>
#include <windows.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

int PX,PY,GameOver,score,bot1x,bot1y,bot2x,bot2y,bot3x,bot3y,bot4x,bot4y,bot5x,bot5y;
enum eDir {STOP,UP,DOWN,LEFT,RIGHT};
int AllowWays[4];
eDir bot1dir;
eDir bot2dir;
eDir bot3dir;
eDir bot4dir;
eDir bot5dir;

eDir dir;

char map[][41]    =  {{" ###################################### "},
					  		 {" #.................##.................# "},
					  		 {" #.#####.########..##..########.#####.# "},
					  		 {" # .................................. # "},
					  		 {" #.#####.##.################.##.#####.# "},
					  		 {" #.......##........##........##.......# "},
					  		 {" #######.######### ## #########.####### "},
					  		 {"      ##.##..................##.##      "},
					  		 {"########.##.#######  #######.##.########"},
					  		 {"        .  .##            ##.  .        "},
					  		 {"        .  .##            ##.  .        "},
					  		 {"########.##.#######  #######.##.########"},
					  		 {"      ##.##..................##.##      "},
					  		 {" #######.## ################ ##.####### "},
					  		 {" #.................##.................# "},
					  		 {" #.#####.#########.##.#########.#####.# "},
					  		 {" #....##...........0............##....# "},
					  		 {" #.##.##.######.########.######.##.##.# "},
					  		 {" # .................................. # "},
					  		 {" ###################################### "}};

char bonus[][41] =   {{" ###################################### "},
					  		 {" #.................##.................# "},
					  		 {" #.#####.########..##..########.#####.# "},
					  		 {" # .................................. # "},
					  		 {" #.#####.##.################.##.#####.# "},
					  		 {" #.......##........##........##.......# "},
					  		 {" #######.######### ## #########.####### "},
					  		 {"      ##.##..................##.##      "},
					  		 {"########.##.#######  #######.##.########"},
					  		 {"        .  .##            ##.  .        "},
					  		 {"        .  .##            ##.  .        "},
					  		 {"########.##.#######  #######.##.########"},
					  		 {"      ##.##..................##.##      "},
					  		 {" #######.## ################ ##.####### "},
					  		 {" #.................##.................# "},
					  		 {" #.#####.#########.##.#########.#####.# "},
					  		 {" #....##........................##....# "},
					  		 {" #.##.##.######.########.######.##.##.# "},
					  		 {" # .................................. # "},
					  		 {" ###################################### "}};

	

void setting(){
	srand(time(NULL));
	system("mode con cols=40 lines=22");
	setlocale(LC_ALL, "");
	system("color 1B");
	GameOver = 1;
	score = 0;
	PX = 19;
	PY = 16;
	dir = STOP;
	bot1x = 3;
	bot1y = 18;
	bot2x = 37;
	bot2y = 3;
	bot3x = 11;
	bot3y = 12;
	bot4x = 20;
	bot4y = 10;
   bot5x = 19;
	bot5y = 9;
	
	bot1dir = RIGHT;
	bot2dir = LEFT;
	bot3dir = LEFT;
	bot4dir = UP;
	bot5dir = DOWN;

}

void PossibleWays(int x,int y){

   for(int i = 0;i < 4;i++){
		AllowWays[i] = 0;
	}
   
	int tempx = x;
	int tempy = y;
	if(bonus[tempy-1][tempx] != '#' ){
		AllowWays[0] = 1;
	}
	if(bonus[tempy+1][tempx] != '#' ){
		AllowWays[1] = 1;
	}
	if(bonus[tempy][tempx-1] != '#' ){
		AllowWays[2] = 1;
	}
	if(bonus[tempy][tempx+1] != '#' ){
		AllowWays[3] = 1;
	}
	
}

int CheckWall(eDir Nextd,int x,int y){
	int nextx = x;
	int nexty = y;
	switch (Nextd){
		case LEFT :
			nextx--;
			if(map[nexty][nextx] == '#'){
				return 0;	
			}
			break;	
		case RIGHT :
			nextx++;
			if(map[nexty][nextx] == '#'){
				return 0;	
			}
			break;
		case UP :
			nexty--;
			if(map[nexty][nextx] == '#'){
				return 0;	
			}
			break;
		case DOWN :
			nexty++;
			if(map[nexty][nextx] == '#'){
				return 0;	
			}
			break;
		default:
			return 1;
	}
}

int NextStep(eDir botdir,int boty,int botx){
	int tempx = botx;
	int tempy = boty;
	if(bonus[tempy][tempx] == ' '){
		return 0;
	}else if(bonus[tempy][tempx] == '.'){
		return 1;
	}
		
	
}

void bot4logic(){
	int num = 0;
	if(CheckWall(bot4dir,bot4x,bot4y) == 0){
		bot4dir = STOP;
		PossibleWays(bot4x,bot4y);
		for(int i = 0;i < 4;i++){
			if(AllowWays[i] == 1){
				num++;
			}	
		}
		do{
			int ii = rand();
			int nextway = ii % ++num;
			if(AllowWays[nextway] == 1){
				switch(nextway){
					case 0:
						bot4dir = UP;
						break;
					case 1:
						bot4dir = DOWN;
						break;
					case 2:
						bot4dir = LEFT;
						break;
					case 3:
						bot4dir = RIGHT;
						break;
					default:
						bot4dir = STOP;
				 }
			}
		}while(bot4dir == STOP);
	}
			
	switch (bot4dir){
		case LEFT:
			if(NextStep(bot4dir,bot4y,bot4x) == 0){
				map[bot4y][bot4x] = ' ';	
			}else{
				map[bot4y][bot4x] = '.';	
			}
			bot4x--;
			map[bot4y][bot4x] = '@';
			break;
		case RIGHT:
			if(NextStep(bot4dir,bot4y,bot4x) == 0){
				map[bot4y][bot4x] = ' ';	
			}else{
				map[bot4y][bot4x] = '.';	
			}
			bot4x++;
			map[bot4y][bot4x] = '@';
			break;
		case UP:
			if(NextStep(bot4dir,bot4y,bot4x) == 0){
				map[bot4y][bot4x] = ' ';	
			}else{
				map[bot4y][bot4x] = '.';	
			}
			bot4y--;
			map[bot4y][bot4x] = '@';
			break;
		case DOWN:
			if(NextStep(bot4dir,bot4y,bot4x) == 0){
				map[bot4y][bot4x] = ' ';	
			}else{
				map[bot4y][bot4x] = '.';	
			}
			bot4y++;
			map[bot4y][bot4x] = '@';
			break;
		case STOP:
			map[bot4y][bot4x] = '@';
			break;
		}
	
}

void bot5logic(){
	int num = 0;
	if(CheckWall(bot5dir,bot5x,bot5y) == 0){
		bot5dir = STOP;
		PossibleWays(bot5x,bot5y);
		for(int i = 0;i < 4;i++){
			if(AllowWays[i] == 1){
				num++;
			}	
		}
		do{
			int ii = rand();
			int nextway = ii % ++num;
			if(AllowWays[nextway] == 1){
				switch(nextway){
					case 0:
						bot5dir = UP;
						break;
					case 1:
						bot5dir = DOWN;
						break;
					case 2:
						bot5dir = LEFT;
						break;
					case 3:
						bot5dir = RIGHT;
						break;
					default:
						bot5dir = STOP;
				 }
			}
		}while(bot5dir == STOP);
	}
			
	switch (bot5dir){
		case LEFT:
			if(NextStep(bot5dir,bot5y,bot5x) == 0){
				map[bot5y][bot5x] = ' ';	
			}else{
				map[bot5y][bot5x] = '.';	
			}
			bot5x--;
			map[bot5y][bot5x] = '@';
			break;
		case RIGHT:
			if(NextStep(bot5dir,bot5y,bot5x) == 0){
				map[bot5y][bot5x] = ' ';	
			}else{
				map[bot5y][bot5x] = '.';	
			}
			bot5x++;
			map[bot5y][bot5x] = '@';
			break;
		case UP:
			if(NextStep(bot5dir,bot5y,bot5x) == 0){
				map[bot5y][bot5x] = ' ';	
			}else{
				map[bot5y][bot5x] = '.';	
			}
			bot5y--;
			map[bot5y][bot5x] = '@';
			break;
		case DOWN:
			if(NextStep(bot5dir,bot5y,bot5x) == 0){
				map[bot5y][bot5x] = ' ';	
			}else{
				map[bot5y][bot5x] = '.';	
			}
			bot5y++;
			map[bot5y][bot5x] = '@';
			break;
		case STOP:
			map[bot5y][bot5x] = '@';
			break;
		}
	
}

void bot3logic(){
	if(bot3x == 28 && bot3y == 12){
		bot3dir = UP;
	}else if(bot3x == 28 && bot3y == 7){
		bot3dir = LEFT;
	}else if(bot3x == 11 && bot3y == 7){
		bot3dir = DOWN;
	}else if(bot3x == 11 && bot3y == 12){
		bot3dir = RIGHT;
	}
	switch (bot3dir){
		case LEFT:
			if(NextStep(bot3dir,bot3y,bot3x) == 0){
				map[bot3y][bot3x] = ' ';	
			}else{
				map[bot3y][bot3x] = '.';	
			}
			bot3x--;
			map[bot3y][bot3x] = '@';
			break;
		case RIGHT:
			if(NextStep(bot3dir,bot3y,bot3x) == 0){
				map[bot3y][bot3x] = ' ';	
			}else{
				map[bot3y][bot3x] = '.';	
			}
			bot3x++;
			map[bot3y][bot3x] = '@';
			break;
		case UP:
			if(NextStep(bot3dir,bot3y,bot3x) == 0){
				map[bot3y][bot3x] = ' ';	
			}else{
				map[bot3y][bot3x] = '.';	
			}
			bot3y--;
			map[bot3y][bot3x] = '@';
			break;
		case DOWN:
			if(NextStep(bot3dir,bot3y,bot3x) == 0){
				map[bot3y][bot3x] = ' ';	
			}else{
				map[bot3y][bot3x] = '.';	
			}
			bot3y++;
			map[bot3y][bot3x] = '@';
			break;
		}
}


void bot2logic(){
	if(bot2x == 37){
		bot2dir = LEFT;
	}else if(bot2x == 3){
		bot2dir = RIGHT;
	}
	switch (bot2dir){
		case LEFT:
			if(NextStep(bot3dir,bot2y,bot2x) == 0){
				map[bot2y][bot2x] = ' ';	
			}else{
				map[bot2y][bot2x] = '.';	
			}
			bot2x--;
			map[bot2y][bot2x] = '@';
			break;
		case RIGHT:
			if(NextStep(bot3dir,bot2y,bot2x) == 0){
				map[bot2y][bot2x] = ' ';	
			}else{
				map[bot2y][bot2x] = '.';	
			}
			bot2x++;
			map[bot2y][bot2x] = '@';
			break;
		}
}

void bot1logic(){
	if(bot1x == 37){
		bot1dir = LEFT;
	}else if(bot1x == 3){
		bot1dir = RIGHT;
	}
	switch (bot1dir){
		case LEFT:
			if(NextStep(bot1dir,bot1y,bot1x) == 0){
				map[bot1y][bot1x] = ' ';	
			}else{
				map[bot1y][bot1x] = '.';	
			}
			bot1x--;
			map[bot1y][bot1x] = '@';
			break;
		case RIGHT:
			if(NextStep(bot1dir,bot1y,bot1x) == 0){
				map[bot1y][bot1x] = ' ';	
			}else{
				map[bot1y][bot1x] = '.';	
			}
			bot1x++;
			map[bot1y][bot1x] = '@';
			break;
		}
}

int input(){
	if(kbhit()){
		switch (getch()){
			case 'a' :
				dir = LEFT;
				break;
			case 'd' :
				dir = RIGHT;
				break;		
			case 'w' :
				dir = UP;
				break;		
			case 's' :
				dir = DOWN;
				break;	
		}
	}
}


void clear(int x,int y){
	map[y][x] = ' ';
}





void teleport(){
	if(PX == 0 && (PY == 9 || PY == 10)){
		map[PY][PX] = ' ';
		PX = 38;
	}else if(PX == 39){
		map[PY][PX] = ' ';
		PX = 1;
	}
}
	


void logic(){
	int NextX = PX+1;
	int NextY = PY+1;
	if(map[PY][PX] == '@' /*|| map[PY][NextX] == '@' || map[NextY][PX] == '@' || map[NextY][NextX] == '@'*/){
		GameOver = 0;
	}
	if(score == 286){
		GameOver = 0;	
	}
	if(bonus[PY][PX] == '.'){
		score+=1;	
		bonus[PY][PX] = ' ';
	}
}

void move(){
	
	switch (dir){
		case LEFT :
			if(CheckWall(dir,PX,PY)){
				logic();
				clear(PX,PY);
				teleport();
				PX--;
				map[PY][PX] = '0';
				logic();
			}else{
				dir = STOP;	
			}
			break;	
		case RIGHT :
			if(CheckWall(dir,PX,PY)){
				logic();
				teleport();
				clear(PX,PY);
				PX++;
				map[PY][PX] = '0';
				logic();
			}else{
				dir = STOP;	
			}
			break;
		case UP :
			if(CheckWall(dir,PX,PY)){
				logic();
				clear(PX,PY);
				PY--;
				map[PY][PX] = '0';
				logic();
			}else{
				dir = STOP;	
			}
			break;
		case DOWN :
			if(CheckWall(dir,PX,PY)){
				logic();
				clear(PX,PY);
				PY++;
				map[PY][PX] = '0';
				logic();
			}else{
				dir = STOP;	
			}
			break;
	}
}




void Print(){
	for(int i = 0;i < 20;i++){
		puts(map[i]);
		//printf("%s\n",map[i]);
	}	
	printf("счет: %i\n",score);
	printf(" PY %i--PX %i",PY,PX);
	Sleep(250);
	system("cls");
}


int main(){
	setting();
	while(GameOver){
		Print();
		input();
		move();
		bot1logic();
		bot2logic();
		bot3logic();
		bot4logic();
		bot5logic();
		logic();
	}
	
	getch();	
}
