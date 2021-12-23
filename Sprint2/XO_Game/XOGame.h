#ifndef __XO_GAME__
#define __XO_GAME__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

#define Total_Name_LEN          10u
#define USER_LOC_BIT_SIZE       2u
#define USER_1_NUM              1u
#define USER_2_NUM              2u



enum _UserStatus
{ LOC_SET_OK = 0, LOC_ALREADY_SET , GAME_END_EQUAL , USER_WIN , USER_EQUAL , USER_NOT_YET } UpdateGameRetEvents;



/*
 * brief  : this function used to draw pattern on screen 
 * param. : pu32_Game pointer to the game board 
 * return : void 
 */
void DrawPattern (uint32_t * pu32_Game );






/*
 * brief  : this function used to update the game board 
 * param. : pu32_Game pointer to the game board
 * param. : User_Num hold player number that made the change 
 * param. : NewLoc the new location that need to be nodified by the player 
 * return : UpdateGameRetEvents enum that indicate the current status of the game board 
 */
int32_t GameUpdat (uint32_t * pu32_Game , uint32_t User_Num, uint8_t NewLoc);





/*
 * brief  : this function used to check the current condition of the game board 
 * param. : pu32_Game pointer to the game board
 * param. : CondVar varibale hold all bits of each player to simplify win check 
 * param. : NewLoc the new location that need to be nodified by the player 
 * return : UpdateGameRetEvents enum that indicate the current status of the game board 
 */
uint32_t CheckWinCondition(uint32_t * pu32_Game , uint32_t CondVar);



# endif /* __XO_GAME__ */