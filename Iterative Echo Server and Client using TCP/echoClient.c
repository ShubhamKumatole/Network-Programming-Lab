#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#define handle_error(msg) do{perror(msg);exit(1);}while(0)
#define status(msg) printf("%s\n",msg)

void str_cli(FILE *fp, int sockfd)
{
   int bufsize = 1024, cont;
   char *buffer = malloc(bufsize);

while(fgets(buffer,bufsize,fp)!=NULL)
{
	send(sockfd, buffer, sizeof(buffer), 0);  

  if((cont=recv(sockfd, buffer, bufsize, 0))>0) {
    fputs(buffer,stdout);
  }}
  printf("\nEOF\n");
}
int main(int argc,char* argv[]){
	if(argc<2){
		printf("usage <%s> <IP>",argv[0]);
		exit(0);
	}
	int sockfd ;
	struct sockaddr_in myaddr;
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1)
		handle_error("socket");
	memset(&myaddr,0,sizeof(myaddr));
	//memset(&peeraddr,0,sizeof(peeraddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(15001);
	inet_pton(AF_INET,argv[1],&myaddr.sin_addr);
	status("socket created");
	int connfd;
	if((connfd=connect(sockfd,(struct sockaddr*)&myaddr,sizeof(myaddr)))<0)
		handle_error("connect");
	str_cli(stdin,sockfd);
	close(connfd);
	close(sockfd);
	return 0;
}
	
