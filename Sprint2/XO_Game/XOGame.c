#include "XOGame.h"



uint32_t gau32_WinCases[8] = {  7,56,448,          /* first Row */
                                73,146,292,        /* Second Row */
                                273,84      };     /* Two Diagonals conditions */

uint32_t User_WinCond[2] ;




/*
 * brief  : this function used to update the game board 
 * param. : pu32_Game pointer to the game board
 * param. : User_Num hold player number that made the change 
 * param. : NewLoc the new location that need to be nodified by the player 
 * return : UpdateGameRetEvents enum that indicate the current status of the game board 
 */
int32_t GameUpdate (uint32_t * pu32_Game , uint32_t User_Num, uint8_t NewLoc)
{
    uint32_t  GameCurrentCondition = 0 ;

    if ((*pu32_Game >> ((NewLoc - 1) * 2))& (0x3))	/* try again you are trying to set already set location */
    {
      printf ("this location is already set try again\n");
      return LOC_ALREADY_SET;
    }
    else
    {

	  *pu32_Game |= User_Num << ((NewLoc - 1) * USER_LOC_BIT_SIZE);
	  User_WinCond[User_Num-1] |= 1 << (NewLoc - 1);

    }

        DrawPattern (pu32_Game);
        GameCurrentCondition = CheckWinCondition(pu32_Game,User_WinCond[User_Num-1]);
        if(GameCurrentCondition == USER_EQUAL)
        {
            return GAME_END_EQUAL ;
        }
        
        
    return GameCurrentCondition;
    
    
    
}/* END_OF_FUN GameUpdat() */







/*
 * brief  : this function used to check the current condition of the game board 
 * param. : pu32_Game pointer to the game board
 * param. : CondVar varibale hold all bits of each player to simplify win check 
 * param. : NewLoc the new location that need to be nodified by the player 
 * return : UpdateGameRetEvents enum that indicate the current status of the game board 
 */
uint32_t CheckWinCondition(uint32_t * pu32_Game , uint32_t CondVar)
{
    uint32_t u32_WinFlag = USER_NOT_YET ;       /* WinFlag used to hold the status of game */ 

    for(uint32_t counter =0 ;counter < sizeof(gau32_WinCases)/sizeof(uint32_t) ; counter++)
    {
        if((gau32_WinCases[counter] & CondVar) == gau32_WinCases[counter])
        {
            u32_WinFlag = USER_WIN ;
            break ; 
        }
    }

        if (u32_WinFlag != USER_WIN)
        {
            for(uint32_t Counter= 0 ; Counter<9; Counter++)
            {
                if((* pu32_Game >> (Counter  * 2))& (0x3))
                 {
                     u32_WinFlag = USER_EQUAL ;
                 }
                 else{
                    u32_WinFlag = USER_NOT_YET ;
                    break ;
                 }
            }
        }
        
        
    return u32_WinFlag ;
    
    
}/* END_OF_FUN CheckWinCondition() */







/*
 * brief  : this function used to draw pattern on screen 
 * param. : pu32_Game pointer to the game board 
 * return : void 
 */
void DrawPattern (uint32_t * pu32_Game)
{
  char Shap = ' ';
  uint8_t   u8_UserNumber = 0 ,         /* hold user number USER_1_NUM or USER_1_NUM */
            u8_GameLineNum = 0;         /* hold the current line index */
	system("clear");	/* clear terminal with each player turn */
    for (int interCounter = 0; interCounter < 3; interCounter++)    /* used to draw the most upper line */
    {
      printf (" -- ");
    }
    printf ("\n");
    
    
    for (int Counter = 0; Counter < 3; Counter++, u8_GameLineNum += 3 )  /* draw current status of the game */
    {

        for (int interCounter = 0; interCounter < 3; interCounter++)
    	{
    	    u8_UserNumber = (*pu32_Game  >> ((interCounter  + u8_GameLineNum)* USER_LOC_BIT_SIZE ) & 0x3);  /* here we hold the owner for the location*/
    	    if (u8_UserNumber == USER_1_NUM)
    	    {
    	      Shap = 'X';
    	    }
    	    else if (u8_UserNumber == USER_2_NUM)
    	    {
    	      Shap = 'O';
    	    }
    	    else
    	    {
    	      Shap = ' ';       /* empty location */
    	    }
    
    	    printf ("| %c ", Shap);
    	}
    	
        printf ("|\n");
        for (int interCounter = 0; interCounter < 3; interCounter++)     /* used to drow the most down line */
    	{
    	  printf (" -- ");
    	}
    	
    	
        printf ("\n");
    }



}/* END_OF_FUN DrawPattern() */

