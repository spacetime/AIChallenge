/* TWISTED TRON
 *
 * Artifical Intelligence Challenge, Innovision 2011.
 *
 * First Read the README PDF/TXT given.
 */

#include<stdio.h>
#include<time.h>
#include<iostream>
#include"parameter.h"
#include"sampleplayer.cpp"
#include"playerXX.cpp"

using namespace std;
struct player
{
    char id;
    int head_positiony;
    int head_positionx;
    int life_left;
    int acc_direction;//stores the player's accelerating direction
    bool status;//dead=false or alive=true
};
    
class stimulator
{
    private:
        char board[BOARD_LENGHT][BOARD_BREADTH];
        player p[NO_OF_PLAYERS];
        int players_alive_on_board;//stores the number of players alive on board
    public:
        stimulator()
        {
            int i,j;
            players_alive_on_board=NO_OF_PLAYERS;
            for( i=0;i<BOARD_LENGHT;i++)
            for( j=0;j<BOARD_BREADTH;j++)
            {
                if(i==0 || j==0 || i==(BOARD_LENGHT-1) || j==(BOARD_BREADTH-1))///for setting up fence on the board
                board[i][j]=FENCE;
                else
                board[i][j]=BLANK;//for initialising blank positions on board
            }   
            //initialising attributes and positions of the players on board
            for(i=0;i<NO_OF_PLAYERS;i++)
            {
                p[i].id=(char)(i+65);//ASCII code of A is 65
                p[i].head_positiony=BOARD_LENGHT /2;
                p[i].head_positionx=(i+1)*BOARD_BREADTH /(NO_OF_PLAYERS+1);
                board[ p[i].head_positiony][p[i].head_positionx]=p[i].id;
                p[i].life_left=NO_OF_LIFE;
                p[i].acc_direction=0;
                p[i].status=true;
            }    
            //initialise power ups on the board
            srand(time(NULL));
            int powerup=0;
            while(powerup<NO_OF_POWERUPS)
            {
                i=rand()% BOARD_LENGHT;
                j=rand()% BOARD_BREADTH ;
                
                if(board[i][j] == BLANK )
                {
                    board[i][j]=POWER_UP;
                    powerup++;
                }
            }
        }
        
         void display_board()//displays the board with the values of their respective columns and rows
        {
            int i,j;printf("\n   ");
            FILE *fp;
            fp=fopen("tron.doc","a+");
            for( i=BOARD_LENGHT;i>=0;i--)
            {     
                for( j=-1;j<BOARD_BREADTH;j++)
                {
                    if(i==BOARD_LENGHT && j==-1) continue;
                    if(i==BOARD_LENGHT) printf("%3d",j);
                    else if(j==-1) printf("%3d",i);
                    else 
                    {
                        printf("%3c",board[i][j]);
                        fprintf(fp,"%c",board[i][j]);
                    }    
                }    
                printf("\n");fprintf(fp,"\n");
            }    
            fprintf(fp,"\n");
            fclose(fp);
        }    
        
         void check_n_update()
        {
            
            int i,x,y;
            char place_reached;
            for(i=0;i<NO_OF_PLAYERS;i++)
            {
                if(p[i].status==false) continue;
                printf("\nplayer %c move= ",p[i].id);
                switch(p[i].acc_direction)
                {
                    case UP:
                        y=+1;x=0;printf("UP");
                        break;
                    case DOWN:
                        y=-1;x=0;printf("DOWN");
                        break;
                    case LEFT:
                        y=0;x=-1;printf("LEFT");
                        break;
                    case RIGHT:
                        y=0;x=+1;printf("RIGHT");
                        break;
                    default:
                        printf("invalid move");
                        getchar();
                        p[i].status=false;
                        players_alive_on_board--;
                        continue;
                }
                            
                do
                {
                    board[p[i].head_positiony][p[i].head_positionx]=p[i].id+32;//setting the present position of the player on the board to trail
                                                            //ASCII code of capital and small letters differ by 32
                    place_reached=board[p[i].head_positiony+y][p[i].head_positionx+x];//getting the value of the place reached
                    board[p[i].head_positiony+y][p[i].head_positionx+x]=p[i].id;
                    p[i].head_positiony+=y;//updating player
                    p[i].head_positionx+=x;//positions
                    printf(". It moves to %d %d.",p[i].head_positiony,p[i].head_positionx);
                    if(place_reached==POWER_UP) printf("It gets a powerup");
                }while(place_reached==POWER_UP) ;
                
                if(place_reached==BLANK)
                {
                    p[i].status=true;
                }       
                else if(place_reached==FENCE)
                {
                    //hits the fence
                    printf(" It hits the fence.");
                    printf(" It LOSES.");
                    p[i].status= false;players_alive_on_board--;
                    board[p[i].head_positiony][p[i].head_positionx]=FENCE;
                }    
                else if(place_reached>=97 && place_reached<(97+NO_OF_PLAYERS))          
                {
                    t://hits a trail of a player
                    p[i].life_left--;
                    if(place_reached==p[i].id+32)
                    {
                        printf("It hits its own trail.No of lives left=%d. ",p[i].life_left);
                    }
                    else
                    {   
                        printf("It hits player %c's trail.No of lives left=%d. ",place_reached,p[i].life_left);
                    }     
                    if(p[i].life_left==0) 
                    {
                        p[i].status=false;
                        printf(" It LOSES.");
                        players_alive_on_board--;
                        board[p[i].head_positiony][p[i].head_positionx]=p[i].id+32;
                    }    
                    else p[i].status=true;
                }    
                else
                {   
                    // collides with another player's head
                    if(place_reached>p[i].id && place_reached<(97+NO_OF_PLAYERS)) goto t;//when the player collides with the head of a player whose id is greater than his own
                                            //then it is actually colliding with its trail as the other player move will be updated later.
                    else 
                    {
                        
                        //players make head on collision
                        p[i].status=false;
                        p[place_reached-65].status=false;
                        players_alive_on_board-=2;
                        printf(" It collides head-on with player %c.",p[place_reached-65].id);
                        printf(" Both player %c and player %c LOSE.",p[place_reached-65].id,p[i].id);
                        board[p[i].head_positiony][p[i].head_positionx]=p[i].id+32; 
                    } 
                }          
            
            }                   
        }                
        
        void controller()
        {
            char copy_of_board[BOARD_LENGHT][BOARD_BREADTH];
            int acc_direct;//stores the direction of the move returned by the getmove function
            int i,j,k;//looping variables
            while(players_alive_on_board>1)
            {
                
                sampleplayer playerA(p[0].id);
                playerXX playerB(p[1].id);
                getchar();
                //creating a copy of the present state of the board
                for( j=0;j<BOARD_LENGHT;j++)
                for( k=0;k<BOARD_BREADTH;k++)
                copy_of_board[j][k]=board[j][k];
                //getting acc_direction from players
                for(i=0;i<NO_OF_PLAYERS;i++)
                {
                    if(p[i].status==false) continue;
                    //getting acc_direction from players
                    switch(i)
                    {
                        case 0:
                            acc_direct=playerA.getmove(copy_of_board,p[i].head_positiony,p[i].head_positionx,p[i].acc_direction,p[i].life_left);
                            break;
                        case 1:
                            acc_direct=playerB.getmove(copy_of_board,p[i].head_positiony,p[i].head_positionx,p[i].acc_direction,p[i].life_left);
                            break;
                    }
                    /*
                    A player moving in some particular direction cannot change its direction to the opposite direction
                    For example, A player moving UP cannot change its direction to DOWN in the next move
                    */ 
                    if(acc_direct!=-p[i].acc_direction)
                    {
                        p[i].acc_direction=acc_direct;
                    }    
                }             
                check_n_update();//updating the move of the player on the board
                display_board();   
            }
            for(i=0;i<NO_OF_PLAYERS;i++)
            if(p[i].status==true)printf("\n player %c wins.",p[i].id);
                   
        }
} ;   

int main()
{
    stimulator s1;
    s1.display_board();
    s1.controller();
    getchar();
    
}    
   
