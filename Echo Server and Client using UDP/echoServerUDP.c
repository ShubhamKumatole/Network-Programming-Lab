#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#define handleError(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)
#define status(msg) printf("%s\n",msg);

void str_echo(int sockfd,struct sockaddr* peerAddr,int clilen){
	int bufsz = 1024,n;
	char* buf = malloc(bufsz);
	status("in wait for datagrams");
	while(1){
		int addrlen = clilen;
		n=recvfrom(sockfd,buf,bufsz,0,peerAddr,&addrlen);
		status("recieved datagram");
		//status(buf);
		sendto(sockfd,buf,n,0,peerAddr,addrlen);
		perror("sendto");
	}
}
int main(int argc,char* argv[]){
	int sockfd;
	struct sockaddr_in myaddr,peeraddr;
	//memset(&myaddr,0,sizeof(myaddr));
	//memset(&peeraddr,0,sizeof(peeraddr));
	if((sockfd = socket(AF_INET,SOCK_DGRAM,0))<=0)
		handleError("socket");
	status("Socket successfully created");
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = INADDR_ANY;
	myaddr.sin_port = htons(15001);
	printf("The address before bind %s  ...\n",inet_ntoa(myaddr.sin_addr) );
	if(bind(sockfd,(struct sockaddr*)&myaddr,sizeof(myaddr))==-1)
		handleError("bind");
	status("Bind successful");
	str_echo(sockfd,(struct sockaddr*)&peeraddr,sizeof(peeraddr));
	return 0;
}
