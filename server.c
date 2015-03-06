#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>

#include "packet.h"

#define  BUFF_SIZE   1024


int main( void)
{
///////////////////////////////////////////////////////////////////
   int   sock;
   int   client_addr_size;
   int   packetNumber;

   struct sockaddr_in   server_addr;
   struct sockaddr_in   client_addr;

   char   buff_rcv[BUFF_SIZE+5];
   char   buff_snd[BUFF_SIZE+5];

	struct timespec ts_start;
	struct packet pk;

   sock  = socket( PF_INET, SOCK_DGRAM, 0);
   
   if( -1 == sock)
   {
      printf( "socket 생성 실패n");
      exit( 1);
   }

   memset( &server_addr, 0, sizeof( server_addr));
   server_addr.sin_family     = AF_INET;
   server_addr.sin_port       = htons( 4000);
   server_addr.sin_addr.s_addr= htonl( INADDR_ANY);

   if( -1 == bind( sock, (struct sockaddr*)&server_addr, sizeof( server_addr) ) )
   {
      printf( "bind() 실행 에러n");
      exit( 1);
   }
	/////////////////////////////////////////////////////////////
	// 일반적인 udp통신 코드
 
	//start
	 packetNumber = 0; // packetNumber initialize

	while(1)
	{
		printf("waiting....");
		recvfrom(sock, &pk,sizeof(pk),0,(struct sockaddr*)&client_addr,&client_addr_size);
		
		clock_gettime(CLOCK_MONOTONIC, &ts_start);
		printf("\"%ld %d\n",pk.packetNumber,ts_start.tv_sec);
	}

	return 0;

}
