#include <conio.h>
#include <stdio.h>
#include <malloc.h>
#include <windows.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int PX,PY,GameOver,score,bot1x,bot1y,bot2x,bot2y,bot3x,bot3y,bot4x,bot4y,bot5x,bot5y,bot6x,bot6y,bot7x,bot7y,bot8x,bot8y,bot9x,bot9y;
enum eDir {STOP,UP,DOWN,LEFT,RIGHT};
int AllowWays[4];
int PriorityWay1[4];
int PriorityWay2[4];
eDir bot1dir;
eDir bot2dir;
eDir bot3dir;
eDir bot4dir;
eDir bot5dir;
eDir bot6dir;
eDir bot7dir;
eDir bot8dir;
eDir bot9dir;
eDir dir;

char map[][41]    =  {{" ###################################### "},
					  		 {" #.................##.................# "},
					  		 {" #.#####.########..##..########.#####.# "},
					  		 {" #....................................# "},
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
					  		 {" #....................................# "},
					  		 {" ###################################### "}};

char bonus[][41] =   {{" ###################################### "},
					  		 {" #.................##.................# "},
					  		 {" #.#####.########..##..########.#####.# "},
					  		 {" #....................................# "},
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
					  		 {" #....................................# "},
					  		 {" ###################################### "}};
					  		 
char botmap[][41] =  {{" ###################################### "},
					  		 {" #%.....%.........%##%.........%.....%# "},
					  		 {" #.#####.########..##..########.#####.# "},
					  		 {" #%.....%..%......%..%......%..%.....%# "},
					  		 {" #.#####.##.################.##.#####.# "},
					  		 {" #%.....%##%......%##%......%##%.....%# "},
					  		 {" #######.######### ## #########.####### "},
					  		 {"      ##.##%......%%%%......%##.##      "},
					  		 {"########.##.#######  #######.##.########"},
					  		 {"       #.  .##    #  #    ##.  .#       "},
					  		 {"       #%  %##    #  #    ##%  %#       "},
					  		 {"########.##.#######  #######.##.########"},
					  		 {"      ##.##%.......%%.......%##.##      "},
					  		 {" #######.## ################ ##.####### "},
					  		 {" #%.....%..%......%##%......%..%.....%# "},
					  		 {" #.#####.#########.##.#########.#####.# "},
					  		 {" #%..%##%......%..%..%..%......%##%..%# "},
					  		 {" #.##.##.######.########.######.##.##.# "},
					  		 {" #%..%..%......%........%......%..%..%# "},
					  		 {" ###################################### "}};

	

void setting(){
	srand(time(NULL));
	//system("LineSelection - 0");
	//system("mode con cols=40 lines=22");
	setlocale(LC_ALL, "");
	system("color 1B");
	GameOver = 1;
	score = 0;
	PX = 19;
	PY = 16;
	dir = STOP;
	bot1x = 2;
	bot1y = 18;
	bot2x = 37;
	bot2y = 3;
	bot3x = 11;
	bot3y = 12;
	bot4x = 19;
	bot4y = 9;
   bot5x = 20;
	bot5y = 10;
	bot6x = 19;
	bot6y = 10;
	bot7x = 20;
	bot7y = 9;
	bot8y = 1;
	bot8x = 37;
	bot9y = 1;
	bot9x = 2;
	
	bot1dir = RIGHT;
	bot2dir = LEFT;
	bot3dir = LEFT;
	bot4dir = UP;
	bot5dir = UP;
	bot6dir = DOWN;
	bot7dir = DOWN;
	bot8dir = LEFT;
	bot9dir = DOWN;

}

float Distance(int botx,int boty){
	float a = botx - PX;
	float b = boty - PY;
	float dis;
	return dis = sqrt((pow(a,2))+(pow(b,2)));
}
int Max(int a,int b){
	int y;
	int x;
	if(a < 0){
		x = -a;	
	}else{
		x = a;	
	}
	if(b < 0){
		y = -b;	
	}else{
		y = b;	
	}
	if(x >= y){
		return a;	
	}else{
		return b;	
	}
}


int PriorityWays(int x,int y){
	int xbias = x - PX;
	int ybias = y - PY;
	
	int Maxbias = Max(xbias,ybias);
	//printf("xb %i\n",xbias);
	//printf("yb %i\n",ybias);
	//printf("mb %i\n",Maxbias);
	for(int i = 0;i < 4;i++){
		PriorityWay1[i] = 0;
	}
	for(int i = 0;i < 4;i++){
		PriorityWay2[i] = 0;
	}
		if(x <= PX && y >= PY){
			if(Maxbias == ybias || Maxbias == -ybias){
				PriorityWay1[0]  = 1;
				PriorityWay2[3] = 1;
			}
			if(Maxbias == xbias || Maxbias == - xbias){
				PriorityWay1[3]  = 1;
				PriorityWay2[0] = 1;
			}
		}
		if(x <= PX && y <= PY){
			if(Maxbias == ybias || Maxbias == -ybias){
				PriorityWay1[1]  = 1;
				PriorityWay2[3] = 1;
			}
			if(Maxbias == xbias || Maxbias == - xbias){
				PriorityWay1[3]  = 1;
				PriorityWay2[1] = 1;
			}
		}
		if(x >= PX && y <= PY){
			if(Maxbias == ybias || Maxbias == -ybias){
				PriorityWay1[1]  = 1;
				PriorityWay2[2] = 1;
			}
			if(Maxbias == xbias || Maxbias == - xbias){
				PriorityWay1[2]  = 1;
				PriorityWay2[1] = 1;
			}
		}
		if(x >= PX && y >= PY){
			if(Maxbias == ybias || Maxbias == -ybias){
				PriorityWay1[0]  = 1;
				PriorityWay2[2] = 1;
			}
			if(Maxbias == xbias || Maxbias == - xbias){
				PriorityWay1[2]  = 1;
				PriorityWay2[0] = 1;
			}
		}
		
		
		
		
		
		

		
		//printf("mb %i\n",Maxbias);
	
		//for(int i = 0;i < 4;i++){
		//	printf("%i\t",AllowWays[i]);
		//}
		//printf("\n");
		//for(int i = 0;i < 4;i++){
		//	printf("%i\t",PriorityWay1[i]);
		//}
		//printf("\n");
		//for(int i = 0;i < 4;i++){
		//	printf("%i\t",PriorityWay2[i]);
		//}
		
}

int matches(){
	int nextstep = 4;;
	for(int i = 0;i < 4;i++){
		if(AllowWays[i] == PriorityWay1[i] && AllowWays[i] == 1 ){
			nextstep	= i;
		}
	}	
	if(nextstep == 4){
		for(int i = 0;i < 4;i++){
			if(AllowWays[i] == PriorityWay2[i] && AllowWays[i] == 1 ){
				nextstep	= i;
			}
		}
	}
	//printf("%i\n",nextstep);
		
	
	return nextstep;
}



void DeathCheckPlayer(eDir Nextd,int x,int y){
	int nextx = x;
	int nexty = y;
	switch (Nextd){
		case LEFT :
			nextx--;
			if(map[nexty][nextx] == '@'){
				GameOver = 0;	
			}
			break;	
		case RIGHT :
			nextx++;
			if(map[nexty][nextx] == '@'){
				GameOver = 0;	
			}
			break;
		case UP :
			nexty--;
			if(map[nexty][nextx] == '@'){
				GameOver = 0;	
			}
			break;
		case DOWN :
			nexty++;
			if(map[nexty][nextx] == '@'){
				GameOver = 0;	
			}
			break;
	}
}
void DeathCheck(eDir Nextd,int x,int y){
	int nextx = x;
	int nexty = y;
	switch (Nextd){
		case LEFT :
			nextx--;
			if(map[nexty][nextx] == '0'){
				GameOver = 0;	
			}
			break;	
		case RIGHT :
			nextx++;
			if(map[nexty][nextx] == '0'){
				GameOver = 0;	
			}
			break;
		case UP :
			nexty--;
			if(map[nexty][nextx] == '0'){
				GameOver = 0;	
			}
			break;
		case DOWN :
			nexty++;
			if(map[nexty][nextx] == '0'){
				GameOver = 0;	
			}
			break;
	}
}
void PossibleWays(int x,int y){

   for(int i = 0;i < 4;i++){
		AllowWays[i] = 0;
	}
   
	int tempx = x;
	int tempy = y;
	if(botmap[tempy-1][tempx] != '#' ){
		AllowWays[0] = 1;
	}
	if(botmap[tempy+1][tempx] != '#' ){
		AllowWays[1] = 1;
	}
	if(botmap[tempy][tempx-1] != '#' ){
		AllowWays[2] = 1;
	}
	if(botmap[tempy][tempx+1] != '#' ){
		AllowWays[3] = 1;
	}
	
}

int ChangeDir(int x,int y){
	if(botmap[y][x] == '%'){
		return 1;
	}else{
		return 0;	
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
int CheckWallforBot(eDir Nextd,int x,int y){
	int nextx = x;
	int nexty = y;
	switch (Nextd){
		case LEFT :
			nextx--;
			if(botmap[nexty][nextx] == '#'){
				return 0;	
			}
			break;	
		case RIGHT :
			nextx++;
			if(botmap[nexty][nextx] == '#'){
				return 0;	
			}
			break;
		case UP :
			nexty--;
			if(botmap[nexty][nextx] == '#'){
				return 0;	
			}
			break;
		case DOWN :
			nexty++;
			if(botmap[nexty][nextx] == '#'){
				return 0;	
			}
			break;
		default:
			return 1;
	}
}

int NextStep(eDir botdir,int tempy,int tempx){
	if(bonus[tempy][tempx] == ' '){
		return 0;
	}else if(bonus[tempy][tempx] == '.'){
		return 1;
	}
		
	
}

void bot4logic(){
	DeathCheck(bot4dir,bot4x,bot4y);
	int num = 0;
	if((((Distance(bot4x,bot4y) > 16)||Distance(bot4x,bot4y) < 6) && ChangeDir(bot5x,bot5y)) || (CheckWallforBot(bot4dir,bot4x,bot4y) == 0)){
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
void bot7logic(){
	DeathCheck(bot7dir,bot7x,bot7y);
	int num = 0;
	if((((Distance(bot7x,bot7y) > 16)||Distance(bot7x,bot7y) < 6) && ChangeDir(bot7x,bot7y)) || (CheckWallforBot(bot7dir,bot7x,bot7y) == 0)){
		bot7dir = STOP;
		PossibleWays(bot7x,bot7y);
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
						bot7dir = UP;
						break;
					case 1:
						bot7dir = DOWN;
						break;
					case 2:
						bot7dir = LEFT;
						break;
					case 3:
						bot7dir = RIGHT;
						break;
					default:
						bot7dir = STOP;
				 }
			}
		}while(bot7dir == STOP);
	}
			
	switch (bot7dir){
		case LEFT:
			if(NextStep(bot7dir,bot7y,bot7x) == 0){
				map[bot7y][bot7x] = ' ';	
			}else{
				map[bot7y][bot7x] = '.';	
			}
			bot7x--;
			map[bot7y][bot7x] = '@';
			break;
		case RIGHT:
			if(NextStep(bot7dir,bot7y,bot7x) == 0){
				map[bot7y][bot7x] = ' ';	
			}else{
				map[bot7y][bot7x] = '.';	
			}
			bot7x++;
			map[bot7y][bot7x] = '@';
			break;
		case UP:
			if(NextStep(bot7dir,bot7y,bot7x) == 0){
				map[bot7y][bot7x] = ' ';	
			}else{
				map[bot7y][bot7x] = '.';	
			}
			bot7y--;
			map[bot7y][bot7x] = '@';
			break;
		case DOWN:
			if(NextStep(bot7dir,bot7y,bot7x) == 0){
				map[bot7y][bot7x] = ' ';	
			}else{
				map[bot7y][bot7x] = '.';	
			}
			bot7y++;
			map[bot7y][bot7x] = '@';
			break;
		case STOP:
			map[bot7y][bot7x] = '@';
			break;
		}
	
}

void bot6logic(){
	DeathCheck(bot6dir,bot6x,bot6y);
	int num = 0;
	if(CheckWallforBot(bot6dir,bot6x,bot6y) == 0){
		bot6dir = STOP;
		PossibleWays(bot6x,bot6y);
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
						bot6dir = UP;
						break;
					case 1:
						bot6dir = DOWN;
						break;
					case 2:
						bot6dir = LEFT;
						break;
					case 3:
						bot6dir = RIGHT;
						break;
					default:
						bot6dir = STOP;
				 }
			}
		}while(bot6dir == STOP);
	}
			
	switch (bot6dir){
		case LEFT:
			if(NextStep(bot6dir,bot6y,bot6x) == 0){
				map[bot6y][bot6x] = ' ';	
			}else{
				map[bot6y][bot6x] = '.';	
			}
			bot6x--;
			map[bot6y][bot6x] = '@';
			break;
		case RIGHT:
			if(NextStep(bot6dir,bot6y,bot6x) == 0){
				map[bot6y][bot6x] = ' ';	
			}else{
				map[bot6y][bot6x] = '.';	
			}
			bot6x++;
			map[bot6y][bot6x] = '@';
			break;
		case UP:
			if(NextStep(bot6dir,bot6y,bot6x) == 0){
				map[bot6y][bot6x] = ' ';	
			}else{
				map[bot6y][bot6x] = '.';	
			}
			bot6y--;
			map[bot6y][bot6x] = '@';
			break;
		case DOWN:
			if(NextStep(bot6dir,bot6y,bot6x) == 0){
				map[bot6y][bot6x] = ' ';	
			}else{
				map[bot6y][bot6x] = '.';	
			}
			bot6y++;
			map[bot6y][bot6x] = '@';
			break;
		case STOP:
			map[bot6y][bot6x] = '@';
			break;
		}
	
}


void bot8logic(){
	DeathCheck(bot8dir,bot8x,bot8y);
	int num = 0;
	if(ChangeDir(bot8x,bot8y) || (CheckWallforBot(bot8dir,bot8x,bot8y) == 0)){
		bot8dir = STOP;
		PossibleWays(bot8x,bot8y);
		PriorityWays(bot8x,bot8y);
		int nextway = matches();
		if(nextway != 4){
			switch(nextway){
					case 0:
						bot8dir = UP;
						break;
					case 1:
						bot8dir = DOWN;
						break;
					case 2:
						bot8dir = LEFT;
						break;
					case 3:
						bot8dir = RIGHT;
						break;
			}
		}else{
			for(int i = 0;i < 4;i++){
				if(AllowWays[i] == 1){
					num++;
				}	
			}
		do{
			int ii = rand();
			nextway = ii % ++num;
			if(AllowWays[nextway] == 1){
				switch(nextway){
					case 0:
						bot8dir = UP;
						break;
					case 1:
						bot8dir = DOWN;
						break;
					case 2:
						bot8dir = LEFT;
						break;
					case 3:
						bot8dir = RIGHT;
						break;
					default:
						bot8dir = STOP;
				 }
			}
		}while(bot8dir == STOP);
	}	
		}
		
			
	switch (bot8dir){
		case LEFT:
			if(NextStep(bot8dir,bot8y,bot8x) == 0){
				map[bot8y][bot8x] = ' ';	
			}else{
				map[bot8y][bot8x] = '.';	
			}
			bot8x--;
			map[bot8y][bot8x] = '@';
			break;
		case RIGHT:
			if(NextStep(bot8dir,bot8y,bot8x) == 0){
				map[bot8y][bot8x] = ' ';	
			}else{
				map[bot8y][bot8x] = '.';	
			}
			bot8x++;
			map[bot8y][bot8x] = '@';
			break;
		case UP:
			if(NextStep(bot8dir,bot8y,bot8x) == 0){
				map[bot8y][bot8x] = ' ';	
			}else{
				map[bot8y][bot8x] = '.';	
			}
			bot8y--;
			map[bot8y][bot8x] = '@';
			break;
		case DOWN:
			if(NextStep(bot8dir,bot8y,bot8x) == 0){
				map[bot8y][bot8x] = ' ';	
			}else{
				map[bot8y][bot8x] = '.';	
			}
			bot8y++;
			map[bot8y][bot8x] = '@';
			break;
		case STOP:
			map[bot8y][bot8x] = '@';
			break;
		}
	
}
void bot9logic(){
	DeathCheck(bot9dir,bot9x,bot9y);
	int num = 0;
	if(ChangeDir(bot9x,bot9y) || (CheckWallforBot(bot9dir,bot9x,bot9y) == 0)){
		bot9dir = STOP;
		PossibleWays(bot9x,bot9y);
		PriorityWays(bot9x,bot9y);
		int nextway = matches();
		if(nextway != 4){
			switch(nextway){
					case 0:
						bot9dir = UP;
						break;
					case 1:
						bot9dir = DOWN;
						break;
					case 2:
						bot9dir = LEFT;
						break;
					case 3:
						bot9dir = RIGHT;
						break;
			}
		}else{
			for(int i = 0;i < 4;i++){
				if(AllowWays[i] == 1){
					num++;
				}	
			}
		do{
			int ii = rand();
			nextway = ii % ++num;
			if(AllowWays[nextway] == 1){
				switch(nextway){
					case 0:
						bot9dir = UP;
						break;
					case 1:
						bot9dir = DOWN;
						break;
					case 2:
						bot9dir = LEFT;
						break;
					case 3:
						bot9dir = RIGHT;
						break;
					default:
						bot9dir = STOP;
				 }
			}
		}while(bot9dir == STOP);
	}	
		}
		
			
	switch (bot9dir){
		case LEFT:
			if(NextStep(bot9dir,bot9y,bot9x) == 0){
				map[bot9y][bot9x] = ' ';	
			}else{
				map[bot9y][bot9x] = '.';	
			}
			bot9x--;
			map[bot9y][bot9x] = '@';
			break;
		case RIGHT:
			if(NextStep(bot9dir,bot9y,bot9x) == 0){
				map[bot9y][bot9x] = ' ';	
			}else{
				map[bot9y][bot9x] = '.';	
			}
			bot9x++;
			map[bot9y][bot9x] = '@';
			break;
		case UP:
			if(NextStep(bot9dir,bot9y,bot9x) == 0){
				map[bot9y][bot9x] = ' ';	
			}else{
				map[bot9y][bot9x] = '.';	
			}
			bot9y--;
			map[bot9y][bot9x] = '@';
			break;
		case DOWN:
			if(NextStep(bot9dir,bot9y,bot9x) == 0){
				map[bot9y][bot9x] = ' ';	
			}else{
				map[bot9y][bot9x] = '.';	
			}
			bot9y++;
			map[bot9y][bot9x] = '@';
			break;
		case STOP:
			map[bot9y][bot9x] = '@';
			break;
		}
	
}
void bot5logic(){
	DeathCheck(bot5dir,bot5x,bot5y);
	int num = 0;
	if(CheckWallforBot(bot5dir,bot5x,bot5y) == 0){
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
	DeathCheck(bot3dir,bot3x,bot3y);
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
	DeathCheck(bot2dir,bot2x,bot2y);
	if(bot2x == 37){
		bot2dir = LEFT;
	}else if(bot2x == 2){
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
	DeathCheck(bot1dir,bot1x,bot1y);
	if(bot1x == 37){
		bot1dir = LEFT;
	}else if(bot1x == 2){
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
	DeathCheckPlayer(dir,PX,PY);
	if(score == 290){
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
	printf("score: %i left: %i\n",score,290 - score);
	printf(" PY %i--PX %i",PY,PX);
	Sleep(150);
	if(GameOver == 1){
		system("cls");
	}else if(GameOver == 0 || score != 290){
		printf("YOU DIED");	
	}else{
		printf("Victory!!!");	
	}
}


int main(){
	setting();
	while(GameOver){
		Print();
		input();
		move();
		bot1logic(); // 0 ii
		bot2logic(); // 0 ii
		bot3logic(); // 0 ii
		bot4logic(); // midl ii 
		bot5logic(); // low ii
		bot6logic(); // low ii
		bot7logic(); // midl ii
		bot8logic(); // smart ii
		bot9logic(); // smart ii
		logic();
	}
	Print();
	getch();	
	getch();
}
