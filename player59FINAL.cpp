	//sg
#include<stdio.h>
#include<iostream>
#include"parameter.h"
#define VRBS 1

namespace killerBot{
	int movecount=0;	
	int deathoverride=0;
	int phase=0;
	int flag1=0;
	int algoID=0;
}

using namespace killerBot;

class superkilla
{
private:
	char playerid;
	int x;
	int sequence[16];
	int spiral[100];
public:   
	static  int count;
	static int spiral_safe;        
		//______________________________________________________
	int getcount();
	int spiral_wont_work();
	int SNM(char board[BOARD_LENGHT][BOARD_BREADTH],int head_positiony,int head_positionx ,int acc_direction,int life_left);
	bool checkvoid(char board[BOARD_LENGHT][BOARD_BREADTH],int heady,int headx,int dir);
	
		//______________________________________________________
	superkilla(char id)
	{
		playerid=id;
	}
        // STORING PATTERN IN AN ARRAY,ONLY IF SPIRAL IS STILL A POSSIBILITY
	void initspiral()
	{
		int cnt=0;
		
		
		for(int i=0,j=1;i<16;i+=2,j++)
		{
			sequence[i]=j;
			sequence[i+1]=j;
		}
		for(int i=0;i<16;i++)
		{
			
			for(int j=1;j<=sequence[i];j++)
			{
				switch(i%4)
				{
					case 0:
						spiral[cnt]=RIGHT;
						break;
					case 1:
						spiral[cnt]=UP;
						break;
					case 2:
						spiral[cnt]= LEFT;
						break;
					case 3:
						spiral[cnt]= DOWN;
						break;
				}
				cnt++;
			} //end for j
		} //end for i
		
	} //end initspiral
	
	int getmove(char board[BOARD_LENGHT][BOARD_BREADTH],int head_positiony,int head_positionx ,int acc_direction,int life_left)// Funtion which will return the move by the player
	{
		
		int x;
		if(spiral_safe)
		{
			initspiral();
			x=getcount();
			switch(spiral[x])
			{
				case UP:
					if(board[head_positiony+1][head_positionx]!=BLANK)
					{
						spiral_wont_work();
					}
					break;
				case DOWN:
					if(board[head_positiony-1][head_positionx]!=BLANK)
					{
						spiral_wont_work();
					}
					break;
				case LEFT:
					if(board[head_positiony][head_positionx-1]!=BLANK)
					{
						spiral_wont_work();
					}
					break;
				case RIGHT:
					if(board[head_positiony][head_positionx+1]!=BLANK)
					{
						spiral_wont_work();
					}
					break;
			}
			
			if (spiral_safe)
			{
				
				return spiral[x];
			}
			else 
				x=SNM(board ,head_positiony, head_positionx , acc_direction, life_left);
		}
		else
		{
			x=SNM(board ,head_positiony, head_positionx , acc_direction, life_left);
		} 
		return x;
	}//end func
	
};    

int superkilla::count=-1;
int superkilla::spiral_safe=1;
int superkilla::spiral_wont_work()
{
    spiral_safe=0;
}
int superkilla::getcount()
{
    return ++count;
}

int superkilla::SNM(char board[BOARD_LENGHT][BOARD_BREADTH],int head_positiony,int head_positionx ,int acc_direction,int life_left)
{
    switch(acc_direction)
    {
		case LEFT:  
			if((checkvoid(board,head_positiony,head_positionx,LEFT))&&((board[head_positiony][head_positionx-1]==BLANK)||((board[head_positiony][head_positionx-1]==POWER_UP)&&(board[head_positiony][head_positionx-2]==BLANK))))
				return LEFT;
			else if(head_positiony>=10)  //i am in upper half
			{
				if((board[head_positiony-1][head_positionx]==BLANK)||((board[head_positiony-1][head_positionx]==POWER_UP)&&(board[head_positiony-2][head_positionx]==BLANK)))
					return DOWN;
				else
					return UP;
			}
			else 
			{
				if((board[head_positiony+1][head_positionx]==BLANK)||((board[head_positiony+1][head_positionx]==POWER_UP)&&(board[head_positiony+2][head_positionx]==BLANK)))
					return UP;
				else 
					return DOWN;
			}
			
			break;
		case RIGHT:
			
			if((checkvoid(board,head_positiony,head_positionx,RIGHT))&&((board[head_positiony][head_positionx+1]==BLANK)||((board[head_positiony][head_positionx+1]==POWER_UP)&&(board[head_positiony][head_positionx+2]==BLANK))))
			{
				return RIGHT;
			}
			else if(head_positiony>10)  //i am in upper half
			{
				if((board[head_positiony-1][head_positionx]==BLANK)||((board[head_positiony-1][head_positionx]==POWER_UP)&&(board[head_positiony-2][head_positionx]==BLANK)))
					return DOWN;
				else 
					return UP;
			}
			else 
			{
				if((board[head_positiony+1][head_positionx]==BLANK)||((board[head_positiony+1][head_positionx]==POWER_UP)&&(board[head_positiony+2][head_positionx]==BLANK)))
					return UP;
				else 
					return DOWN;
			}
			
			break;
		case UP:
			if(head_positionx>=10)  //i am in right half
			{
				if((board[head_positiony][head_positionx-1]==BLANK)||((board[head_positiony][head_positionx-1]==POWER_UP)&&(board[head_positiony][head_positionx-2]==BLANK)))
					return LEFT;
				else if((board[head_positiony][head_positionx+1]==BLANK)||((board[head_positiony][head_positionx+1]==POWER_UP)&&(board[head_positiony][head_positionx+2]==BLANK)))
					
					return RIGHT;
				
				else 
					return UP;
			}
			else 
				
			{
				if((board[head_positiony][head_positionx+1]==BLANK)||((board[head_positiony][head_positionx+1]==POWER_UP)&&(board[head_positiony][head_positionx+2]==BLANK)))
					return RIGHT;
				else  if((board[head_positiony][head_positionx-1]==BLANK)||((board[head_positiony][head_positionx-1]==POWER_UP)&&(board[head_positiony][head_positionx-2]==BLANK)))
					return LEFT;
				
				else //if((board[head_positiony+1][head_positionx]==BLANK)||((board[head_positiony+1][head_positionx]==POWER_UP)&&(board[head_positiony+2][head_positionx]==BLANK)))
					return UP;
			}   
			break;
		case DOWN:
			if((board[head_positiony-1][head_positionx]==BLANK)||((board[head_positiony-1][head_positionx]==POWER_UP)&&(board[head_positiony-2][head_positionx]==BLANK)))
				return DOWN;
			else     if(head_positionx>=10)  //i am in right half
			{
				if((board[head_positiony][head_positionx-1]==BLANK)||((board[head_positiony][head_positionx-1]==POWER_UP)&&(board[head_positiony][head_positionx-2]==BLANK)))
					return LEFT;
				else 
					return RIGHT;
			}
			else 
			{
				if((board[head_positiony][head_positionx+1]==BLANK)||((board[head_positiony][head_positionx+1]==POWER_UP)&&(board[head_positiony][head_positionx+2]==BLANK)))
					return RIGHT;
				else 
					return LEFT;
			}
			break;
		default:
			
			switch(rand()%4)
		{
			case 0: return UP;
			case 1: return DOWN;
			case 2: return LEFT;
			case 3: return RIGHT;
		}  
	}  //end switch
}
bool superkilla::checkvoid(char board[BOARD_LENGHT][BOARD_BREADTH],int heady,int headx,int dir)
{
	int up,down;
	if(dir==LEFT)
	{
		up=board[heady+1][headx-1];
		down=board[heady-1][headx-1];
	}
	else if(dir==RIGHT)
	{
		up=board[heady+1][headx-+1];
		down=board[heady-1][headx+1];
	}
	if((up==down)&&(up!=BLANK))
		return false ;
	else 
		return true;
}     



class player59
{
private:
	char playerid;
	char newboard[BOARD_LENGHT][BOARD_BREADTH];
	int enemyx, enemyy;
	
	
	
public:   
	player59(char id)
	{
		playerid=id;
	}
	
	bool willNotDie(char check_board[BOARD_LENGHT][BOARD_BREADTH] ,int head_positionx,int head_positiony,int dir)
	{
		
		if(dir==DOWN)
		{
			
			while(check_board[head_positiony-1][head_positionx]==POWER_UP){
				head_positiony--;
			};
			switch(check_board[head_positiony-1][head_positionx])
			{
				case 'A':
				case 'a':
				case 'B':
				case 'b': 
				case 'F':   return false;
					break;
			}
			return true;
		}
		if(dir==UP)
		{
			
			while(check_board[head_positiony+1][head_positionx]==POWER_UP){
				head_positiony++;
			};
			switch(check_board[head_positiony+1][head_positionx])
			{
				case 'A':
				case 'a':
				case 'B':
				case 'b': 
				case 'F':   return false;
					break;
			}
			return true;
		}
		if(dir==LEFT)
		{
			
			while(check_board[head_positiony][head_positionx-1]==POWER_UP){
				head_positionx--;
			};
			switch(check_board[head_positiony][head_positionx-1])
			{
				case 'A':
				case 'a':
				case 'B':
				case 'b': 
				case 'F':   return false;
					break;
			}
			return true;
		}
		if(dir==RIGHT)
		{
			
			while(check_board[head_positiony][head_positionx+1]==POWER_UP){
				head_positionx++;
			};
			switch(check_board[head_positiony][head_positionx+1])
			{
				case 'A':
				case 'a':
				case 'B':
				case 'b': 
				case 'F':   return false;
					break;
			}
			return true;
		}
		
	}
	
	
	void findMyEnemy(){
			//Set enemy coordinates with head location
		for (int i=0;i<BOARD_LENGHT;i++)
			for (int j=BOARD_BREADTH-1;j>=0;j--) {
				if (newboard[j][i]=='A') {
					if (VRBS) std::cout<<"\nEnemy location: "<<j<<", "<<i;
					enemyx=i;
					enemyy=j;
				}
			}
		
	}
	
	int getnewmove(char board[BOARD_LENGHT][BOARD_BREADTH],int head_positiony,int head_positionx ,int acc_direction,int life_left){
		if (VRBS) std::cout<<"MOVECOUNT: "<<movecount<<"\n";
		if (phase==0){
			if (movecount<3) return LEFT;
			if (movecount==3) {
				phase=1;
				return UP;
				
			}
		} //Phase 0 done
		
		findMyEnemy();
		if (phase==1){
			flag1=0;
			if (enemyy>10) {
					//player also moved up
				phase=2;
			}
			else{	//player moved down instead!
				phase=7; //go left till you reach wall
			}
		}
		
		if (phase==2||phase==7){
			if (VRBS) std::cout<<"!!!!!!!Phase 2 with heady position: "<<head_positiony<<"\n and flag1= "<<flag1<<"\n";
				//ABort if A goes down!
			if (enemyy<=9){
				phase=4;
				deathoverride=1;
				flag1=1;
				return RIGHT;
			}
			
			if (head_positiony==17&&flag1==0) {
				flag1=1;
				
				return RIGHT;
				
			}
			if (willNotDie(newboard, head_positionx, head_positiony, UP)) return UP;
			else {if (head_positiony==18) {
				flag1=0;
				phase=3;
			}
			else return RIGHT;
			}
		}
		
		if (phase==3){
			if (VRBS) std::cout<<"!!!!!!!Phase 3";
			if (flag1==0) {
				flag1=1;
				return RIGHT;
			}
			if (flag1==1) {
				flag1=2;
				return DOWN;
			}
			if (flag1==2){
				if (willNotDie(newboard, head_positionx, head_positiony, LEFT)){
					flag1=3;
					return LEFT;
				}
				return DOWN;
			}
			if (flag1==3) {
				deathoverride=1;
				phase=4;
				flag1=0;
			}
			
		}
		
		if (phase==4){
			if (VRBS) std::cout<<"!!!!!!!Phase 4 deathovveride="<<deathoverride;
			if (willNotDie(newboard, head_positionx, head_positiony, DOWN)) return DOWN;
			else if (deathoverride==1&&willNotDie(newboard, head_positionx, head_positiony-1, DOWN)&&willNotDie(newboard, head_positionx, head_positiony-2, LEFT)&&life_left==2) {
				phase=5;
				flag1=1;
				return DOWN;
					//LOSE A LIFE
				
			}
			else if (life_left==1) return RIGHT;
			else {
				flag1=0;
				phase=99;
			}
			
		}
		
		if (phase==99){
			if (VRBS) std::cout<<"!!!!!!!Phase99 Inc";
				//panic! oscillate between up and down till you leave quadrant, then spiral panic
			if (head_positiony<10){
					//We're Out of our trap
				phase=88;
			}
			if (flag1==0){ //Going right
				if (willNotDie(newboard, head_positionx, head_positiony, UP)&&willNotDie(newboard, head_positionx, head_positiony+1, RIGHT)) return UP;
				else flag1=1;
			}
			if (flag1==1){
				if (willNotDie(newboard, head_positionx, head_positiony, RIGHT)) {
					flag1=2;
					return RIGHT;
				}
			}
			
			if (flag1==2) {
				if (willNotDie(newboard, head_positionx, head_positiony, DOWN)&&willNotDie(newboard, head_positionx, head_positiony-1, RIGHT)) return DOWN;
				else flag1=3;			}
			
			if (flag1==3){
				if (willNotDie(newboard, head_positionx, head_positiony, RIGHT)&&willNotDie(newboard, head_positionx+1, head_positiony, UP)) {
					flag1=0;
					return RIGHT;
				}
			}
		}
		
		
		if (phase==5){
			if (flag1==1) {flag1=0; return DOWN;}
			if (VRBS) std::cout<<"!!!!!!!Phase 5\nOur Y:"<<(head_positiony-1)<<"Their: "<<(enemyy-enemyx-1+head_positionx);
				//if ((head_positionx-enemyx)<3) if (willNotDie(newboard, head_positionx, head_positiony, DOWN)) return DOWN;
			
			
			
			if ((head_positiony-1)<(enemyy-enemyx-1+head_positionx)&&head_positiony!=1) if (willNotDie(newboard, head_positionx, head_positiony, LEFT)) return LEFT;
			if ((head_positiony-1)>=(enemyy-enemyx-1+head_positionx)) {
				if (acc_direction==LEFT) return DOWN;
				if (willNotDie(newboard, head_positionx, head_positiony, RIGHT)) return RIGHT;
				if (!willNotDie(newboard, head_positionx, head_positiony, RIGHT)) {
					phase=69;
					flag1=0;
					return UP;
				}
			}
				//if ((head_positiony-enemyy)>2||(head_positionx-enemyx)>2) if (willNotDie(newboard, head_positionx, head_positiony, LEFT))return LEFT;
			
			else if (willNotDie(newboard, head_positionx, head_positiony, DOWN)) return DOWN;
				//else if (head_positiony>1) return RIGHT;
			else {phase=88;
				flag1=0;
				return RIGHT;
				
			}
			
			
		}
		
		if (phase==88){
			if (VRBS) std::cout<<"!!!!!!!Phase 88";
				//fill along y axis till full. die a slow painful death.
			if (flag1==0){ //Going right
				if (willNotDie(newboard, head_positionx, head_positiony, UP)&&willNotDie(newboard, head_positionx, head_positiony+1, RIGHT)) return UP;
				else if (willNotDie(newboard, head_positionx, head_positiony, UP)&&head_positionx==18) return UP;
				else flag1=1;
			}
			if (flag1==1){
				if (willNotDie(newboard, head_positionx, head_positiony, RIGHT)) {
					flag1=2;
					return RIGHT;
				}
			}
			
			if (flag1==2) {
				if (willNotDie(newboard, head_positionx, head_positiony, DOWN)&&willNotDie(newboard, head_positionx, head_positiony-1, RIGHT)) return DOWN;
				else if (willNotDie(newboard, head_positionx, head_positiony, DOWN)&&head_positionx==18) return DOWN;
				else flag1=3;			
			}
			
			if (flag1==3){
				if (willNotDie(newboard, head_positionx, head_positiony, RIGHT)&&willNotDie(newboard, head_positionx+1, head_positiony, UP)) {
					flag1=0;
					return RIGHT;
				}
			}
		}
		
		if (phase==69){
			if (VRBS) std::cout<<"!!!!!!!Phase 69";
				//fill along x axis till full. die a slow painful death.
			if (flag1==0){ //Going up
				if (willNotDie(newboard, head_positionx, head_positiony, LEFT)&&willNotDie(newboard, head_positionx-1, head_positiony, UP)) return LEFT;
				else flag1=1;
			}
			if (flag1==1){
				if (willNotDie(newboard, head_positionx, head_positiony, UP)) {
					flag1=2;
					return UP;
				}
			}
			
			if (flag1==2) {
				if (willNotDie(newboard, head_positionx, head_positiony, RIGHT)&&willNotDie(newboard, head_positionx+1, head_positiony, UP)) return RIGHT;
				else flag1=3;			
			}
			
			if (flag1==3){
				if (willNotDie(newboard, head_positionx, head_positiony, UP)) {
					flag1=0;
					return UP;
				}
			}
		}
		
		if (VRBS) std::cout<<"All has failed!";
		algoID=1;
		return UP;			
		
	}
	
	
	int getmove(char board[BOARD_LENGHT][BOARD_BREADTH],int head_positiony,int head_positionx ,int acc_direction,int life_left)// Funtion which will return the move by the player
	{
		
		if (algoID==1){
			superkilla s1(playerid);
			return s1.getmove(board, head_positionx, head_positiony, acc_direction, life_left);
		}
		
		
		
			//If player is A then reverse the board.
		char chforboardcorrection;
		if (playerid=='A'){
				//std::cout<<"I'm playing as A";
			for (int i=0;i<BOARD_LENGHT;i++)
				for (int j=0;j<BOARD_BREADTH;j++) {
					chforboardcorrection=board[j][i];
					switch (chforboardcorrection) {
						case 'A':
							chforboardcorrection='B';
							break;
						case 'B':
							chforboardcorrection='A';
							break;
						case 'a':
							chforboardcorrection='b';
							break;
						case 'b':
							chforboardcorrection='a';
							break;
						default:
							break;
					}
					newboard[j][BOARD_BREADTH-1-i]=chforboardcorrection;
					
				}
			head_positionx=BOARD_BREADTH-head_positionx-1;
			if (acc_direction==LEFT) acc_direction=RIGHT;
			else acc_direction=LEFT;
		}
		
		else {
			for (int i=0;i<BOARD_LENGHT;i++)
				for (int j=BOARD_BREADTH-1;j>=0;j--) {
					newboard[j][i]=board[j][i];
				}
		}
			//AFTER THIS POINT, PROGRAM FOR PLAYER AS B
		
		int retval=getnewmove(newboard,head_positiony,head_positionx,acc_direction,life_left);
			//CHECK FOR OBV DEATH HERE
		if (!willNotDie(newboard, head_positionx, head_positiony, retval)&&deathoverride==0) {
			std::cout<<"ETF";
			int rndir=LEFT;
			if (willNotDie(newboard, head_positionx, head_positiony, rndir))	return rndir;
			rndir=UP;
			if (willNotDie(newboard, head_positionx, head_positiony, rndir))	return rndir;
			rndir=RIGHT;
			if (willNotDie(newboard, head_positionx, head_positiony, rndir))	return rndir;
			return DOWN;
			
		}
		else if(deathoverride==1&&!willNotDie(newboard, head_positionx, head_positiony, retval)){
			deathoverride=0;
		}
		movecount++;
			//std::cout << head_positionx<<", "<<head_positiony;
		
		if (playerid=='A'){
			switch (retval) {
				case UP:
					return UP;
					break;
				case DOWN:
					return DOWN;
					break;
				case LEFT:
					return RIGHT;
					break;
				case RIGHT:
					return LEFT;
					break;
				default:
					break;
			}
		}
		
		return retval;
		
	}
	
};    
