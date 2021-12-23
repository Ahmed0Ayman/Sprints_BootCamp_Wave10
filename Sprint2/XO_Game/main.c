/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "XOGame.h"





int main ()
{
    uint32_t u32_WinFlag = 0 , Location = 0  , u32_GameBoard = 0 ;
    uint8_t ua8_User1_Name[Total_Name_LEN + 1] = { 0 }, ua8_User2_Name[Total_Name_LEN + 1] = {0};

    printf (" enter the first player name \n");
    fgets (ua8_User1_Name, Total_Name_LEN, stdin);
    ua8_User1_Name[strlen(ua8_User1_Name)-1] = 0 ;  /* scape new line */



    /* set user2 name */
    printf (" enter the second user name MAX 6 characters\n");
    fgets (ua8_User2_Name, Total_Name_LEN, stdin);
    ua8_User2_Name[strlen(ua8_User2_Name)-1] = 0 ;  /* scape new line */

  
  
    while (1)
    {
        do{     /* first Do while for first Player turn */
            printf ("your turn %s enter next turn  \n", ua8_User1_Name);
            do{
                scanf ("%d", &Location);
                if((Location > 9)||(Location < 0))
                {
                    printf("wrong location please enter from 1 to 9 \n");
                }
                else
                {
                    ;
                }
            }while((Location > 9)||(Location < 0));
        u32_WinFlag = GameUpdat(&u32_GameBoard , USER_1_NUM , Location);
        
        }while(u32_WinFlag == LOC_ALREADY_SET);
        
        if(u32_WinFlag == GAME_END_EQUAL )  /* check if the game is ended with quality result */
        {
             printf("both of you are equeal please try again \n");
             return 0 ;
        }else if (u32_WinFlag == USER_WIN)  /* check if the game is ended wtih win for fisrt player */
        {
             printf("congratulation %s , you are win \n" , ua8_User1_Name);
             return 0 ;            
        }
        
        
        do{  /* second Do while for second Player turn */
            printf ("your turn %s enter next turn  \n", ua8_User2_Name);
        
            do{  /* avoid wrong user location */
        
                scanf ("%d", &Location);
                if((Location > 9)||(Location < 0))
                {
                    printf("wrong location please enter from 1 to 9 \n");
                }
                else
                {
                    ;
                }
            }while((Location > 9)||(Location < 0));
            u32_WinFlag = GameUpdat(&u32_GameBoard , USER_2_NUM , Location);
            
        }while(u32_WinFlag == LOC_ALREADY_SET ); 
        
        if(u32_WinFlag == GAME_END_EQUAL)     /* check if the game is ended with quality result */
        {
             printf("both of you are equeal please try again \n");
             return 0 ;
        }else if (u32_WinFlag == USER_WIN ) /* check if the game is ended wtih win for second player */
        {
             printf("congratulation %s , you are win  \n" , ua8_User2_Name);
             return 0 ;            
        }
    

    }

  return 0;
}

