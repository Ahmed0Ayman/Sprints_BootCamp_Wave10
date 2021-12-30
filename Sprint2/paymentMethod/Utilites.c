#include "Utilites.h"
#include <winsock2.h>





SOCKET ServerHSocket_Id  , ClientHSocket_Id  ;
uint8_t  ClientMassage[MAX_CLIENT_MESSAGE_LEN+1] ;
struct sockaddr_in str_ServerSocket = {0} , sock_clientaddr ;
uint32_t ServerSocketSize = sizeof(str_ServerSocket) , ClientServerSize = sizeof(str_ServerSocket) ;



/* 
 * brief            : this fuction used to set some of delay (blocking mode )   
 * param [input]    : NumOfSecond number of seconds   
 * Return TernimalStatus_t : return the TERMINAL_OK if every thing is ok 
 */
void Delay(uint32_t NumOfSecond)
{
        int MilSecond  = 1000 * NumOfSecond ;

        clock_t StartTime = clock() ;
        while (clock() < StartTime+MilSecond)
        {
            ;
        }

}






/* 
 * brief            : this fuction used to initialize all sock configuration functions    
 * param           : void   
 * Return          : void
 */
void Socket_Init(void )
{
    
WORD wVersionRequested;

WSADATA wsaData;

int wsaerr;

 

// Using MAKEWORD macro, Winsock version request 2.2

wVersionRequested = MAKEWORD(2, 2);

 

wsaerr = WSAStartup(wVersionRequested, &wsaData);

if (wsaerr != 0)

{
    /* Tell the user that we could not find a usable WinSock DLL.*/
    printf("Server: The Winsock dll not found!\n");
    exit(-1);
}
else

{
       printf("Server: The Winsock dll found!\n");
       printf("Server: The status: %s.\n", wsaData.szSystemStatus);
}



ServerHSocket_Id = socket(AF_INET , SOCK_STREAM , 0) ;
if(ServerHSocket_Id == -1)
{
    printf( "Error Socket Creating  \n");
    WSACleanup();
    #if(__DEBUG__ == 1)
    printf("Error in Socket() function \n");
    #endif
    exit(-1) ;
}else{
    #if(__DEBUG__ == 1)
    printf("Socket Creating Ok \n");
    #endif
}


str_ServerSocket.sin_port   = htons(LISTEN_PORT_NUM);
str_ServerSocket.sin_family = AF_INET ;
str_ServerSocket.sin_addr.s_addr = inet_addr("192.168.0.13");



if (bind(ServerHSocket_Id, (struct sockaddr *)&str_ServerSocket, sizeof(str_ServerSocket)) == SOCKET_ERROR)

{
    #if(__DEBUG__ == 1)
    printf("Error Bind Function \n");
    closesocket(ServerHSocket_Id);
    #endif

    exit(-1) ;
}
else
{
   
    #if(__DEBUG__ == 1)
    printf("Bind function is OK!\n");
    #endif

}


if (listen(ServerHSocket_Id, MAX_LISTEN_NUM ) == SOCKET_ERROR)
{
    #if(__DEBUG__ == 1)
    printf("Server listen fail \n");
    #endif
    exit(-1);
}
else
{
    #if(__DEBUG__ == 1)
    printf(" Listen function , we're waiting New Connection  \n");
    #endif

}


do{
    ClientHSocket_Id = accept(ServerHSocket_Id, (struct sockaddr *)&sock_clientaddr, &ClientServerSize);
}while(ClientHSocket_Id == SOCKET_ERROR);


    #if(__DEBUG__ == 1)
    printf(" Listen function , we're waiting New Connection  \n");
    printf("first client connected \n");    
    #endif

}









/* 
 * brief            : this fuction used to set some of delay (blocking mode )   
 * param [input]    : Message  pointer to message that you want to send   
 * param [input]    : Socket_Id  socket Id number  
 * Return UtilitySataus_t : return the UTILITY_OK if every thing is ok 
 */
UtilitySataus_t SocketSend(uint8_t * Message , SOCKET Socket_Id)
{
    uint8_t SendData[MAX_CLIENT_MESSAGE_LEN+1] ={0} ;   
    if((Message == NULL)||(Socket_Id == -1))
    {
        #if(__DEBUG__ == 1)
        printf("SocketSend() Parameter Error \n");    
        #endif        
        return  UTILITY_ERROR ; 
    }
    else
    {
    
            memset(SendData , 0 , MAX_CLIENT_MESSAGE_LEN +1 );       
            sprintf(SendData ,"%s" , Message );
            if(send(Socket_Id,SendData, strlen(SendData) ,0) == -1)
            {
                #if(__DEBUG__ == 1)
                printf(" Send() socket returned an error \n");
                #endif
                exit(-1);
            }

        
    }

    return UTILITY_OK ;

}






/* 
 * brief            : this fuction used to set some of delay (blocking mode )   
 * param [input]    : Message  pointer to buffer  that you want to receive the message    
 * param [input]    : Socket_Id  socket Id number  
 * Return UtilitySataus_t : return the UTILITY_OK if every thing is ok 
 */
UtilitySataus_t SocketReceive(uint8_t * BufferRecv ,uint32_t BufferLen , SOCKET Socket_Id)
{


    if((BufferRecv == NULL)||(Socket_Id == -1))
    {
        #if(__DEBUG__ == 1)
        printf("SocketReceive() Parameter Error \n");    
        #endif        
        return  UTILITY_ERROR ; 
    }
    else
    {
        if(recv(Socket_Id , BufferRecv , BufferLen ,0) == -1)
        {
            #if(__DEBUG__ == 1)
            printf(" recv() socket returned an error \n");
            #endif
            exit(-1);
        } 


    }



    return UTILITY_OK ;


}