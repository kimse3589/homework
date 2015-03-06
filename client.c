#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>

#include "packet.h"

int main(int argc,char **argv)
{
	int sock;
	int server_addr_size;

	struct sockaddr_in server_addr;

	struct packet pk;
	struct timespec ts_start;
	int packetNumber;
	
	sock = socket(PF_INET,SOCK_DGRAM,0);


	if(-1 == sock)
	{
		printf("socket 생성 실패\n");
		exit(1);
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(4000);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	packetNumber=0;
	while(1)
	{
		pk.packetNumber = packetNumber++;
		clock_gettime(CLOCK_MONOTONIC, &ts_start);
		pk.sendTime = ts_start.tv_sec;

		if(-1 == sendto(sock, &pk, sizeof(pk),0,(struct sockaddr*)&server_addr, sizeof(server_addr)) )
		{
			printf("falied\n");
		}
		
		printf("\"%d %d\n",packetNumber,pk.sendTime);
		usleep(20000);
	}

	return 0;

}
