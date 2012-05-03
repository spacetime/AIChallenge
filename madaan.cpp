	//sg
#include<stdio.h>
#include<iostream>
#include"parameter.h"
using namespace std;
class sampleplayer
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
	sampleplayer(char id)
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

int sampleplayer::count=-1;
int sampleplayer::spiral_safe=1;
int sampleplayer::spiral_wont_work()
{
    spiral_safe=0;
}
int sampleplayer::getcount()
{
    return ++count;
}

int sampleplayer::SNM(char board[BOARD_LENGHT][BOARD_BREADTH],int head_positiony,int head_positionx ,int acc_direction,int life_left)
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
bool sampleplayer::checkvoid(char board[BOARD_LENGHT][BOARD_BREADTH],int heady,int headx,int dir)
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

/*#include<stdio.h>
#include<iostream>
#include"parameter.h"

class sampleplayer
{
    private:
        char playerid;
     public:   
        sampleplayer(char id)
        {
            playerid=id;
        } 
        
        int getmove(char board[BOARD_LENGHT][BOARD_BREADTH],int head_positiony,int head_positionx, int acc_direction,int life_left)// Funtion which will return the move by the player
        {
            //Return moves as #define UP ,DOWN ,RIGHT ,LEFT  
            //here just for stimulation a random move is returned
            char ch;
			std::cout<<"Player A's move? ";
			ch=getchar();
            switch(ch)
            {
                case 'w': return UP;
                case 's': return DOWN;
                case 'a': return LEFT;
                case 'd': return RIGHT;
            }    
        }    
};    */
