#include<stdio.h>
#include<iostream>
#include"parameter.h"

class playerXX
{
    private:
        char playerid;
     public:   
        playerXX(char id)
        {
            playerid=id;
        } 
        
        int getmove(char board[BOARD_LENGHT][BOARD_BREADTH],int head_positiony,int head_positionx ,int acc_direction,int life_left)// Funtion which will return the move by the player
        {
            
            
                if(board[head_positiony+1][head_positionx]==BLANK || (board[head_positiony+1][head_positionx]==POWER_UP && board[head_positiony+2][head_positionx]==BLANK))
                return UP;
                else if(board[head_positiony][head_positionx-1]==BLANK || (board[head_positiony][head_positionx-1]==POWER_UP && board[head_positiony][head_positionx-2]==BLANK))
                return LEFT;
                else if(board[head_positiony-1][head_positionx]==BLANK || (board[head_positiony-1][head_positionx]==POWER_UP && board[head_positiony-2][head_positionx]==BLANK))
                return DOWN;
                else
                return RIGHT;
                         
             //Write your code here
        }    
};    
