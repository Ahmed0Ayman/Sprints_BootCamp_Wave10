
#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "Terminal.h"
#include <winsock2.h>

#define __DEBUG__ 0



#define MAX_CLIENT_MESSAGE_LEN              100u
#define   LISTEN_PORT_NUM                   2021u
#define MAX_CLIENT_MESSAGE_LEN              100u
#define   MAX_LISTEN_NUM                    10u

extern SOCKET ServerHSocket_Id  , ClientHSocket_Id  ;
extern uint8_t  ClientMassage[MAX_CLIENT_MESSAGE_LEN+1] ;



typedef enum { UTILITY_OK , UTILITY_ERROR }UtilitySataus_t;





/* 
 * brief            : this fuction used to set some of delay (blocking mode )   
 * param [input]    : NumOfSecond number of seconds   
 * Return TernimalStatus_t : return the TERMINAL_OK if every thing is ok 
 */
void Delay(uint32_t NumOfSecond);






/* 
 * brief            : this fuction used to set some of delay (blocking mode )   
 * param [input]    : Message  pointer to message that you want to send   
 * param [input]    : Socket_Id  socket Id number  
 * Return UtilitySataus_t : return the UTILITY_OK if every thing is ok 
 */
UtilitySataus_t SocketSend(uint8_t * Message , SOCKET Socket_Id);





/* 
 * brief            : this fuction used to set some of delay (blocking mode )   
 * param [input]    : Message  pointer to buffer  that you want to receive the message    
 * param [input]    : Socket_Id  socket Id number  
 * Return UtilitySataus_t : return the UTILITY_OK if every thing is ok 
 */
UtilitySataus_t SocketReceive(uint8_t * BufferRecv ,uint32_t BufferLen , SOCKET Socket_Id);






/* 
 * brief            : this fuction used to initialize all sock configuration functions    
 * param           : void   
 * Return          : void
 */
void Socket_Init(void );





#endif 