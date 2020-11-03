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

void str_client(int sockfd,FILE* fp,struct sockaddr* servaddr,int addrlen){
	int bfsz = 1024,cont,n;
	char * buf = malloc(bfsz);
	while(fgets(buf,bfsz,fp)!=NULL){
		sendto(sockfd,buf,sizeof(buf),0,servaddr,addrlen);
		if((cont = recvfrom(sockfd,buf,bfsz,0,NULL,NULL))>0)
			fputs(buf,stdout);	
		perror("recvfrom");
	}
}
int main(int argc,char* argv[]){
	int sockfd;
	struct sockaddr_in servaddr;
	if(argc==1)
		handleError("argv[1] cannot be null");
	memset(&servaddr,0,sizeof(servaddr));
	if((sockfd = socket(AF_INET,SOCK_DGRAM,0))==-1)
		handleError("socket");
	status("Socket successfully created");
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(15001);
	inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
	str_client(sockfd,stdin,(struct sockaddr*)&servaddr,sizeof(servaddr));
	return 0;
}
