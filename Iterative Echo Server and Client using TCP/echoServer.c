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
void str_echo(int connfd){
	int bufsz = 1024;
	char* buf;
	int n;
	status("in str_echo");
	buf = malloc(bufsz);
	again : 
	while((n = recv(connfd,buf,bufsz,0))>0){
		status("in while");
		send(connfd,buf,n,0);	
	}
	if(n<0){		
		printf("Waiting for message\n");
		goto again;
	}
	return ;
}
int main(int argc,char* argv[]){
	int sockfd;
	struct sockaddr_in addr,peeraddr;
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1){
		printf("Error\n");
		exit(0);		
	}
	printf("Socket was created successfully\n");
	//addr = (struct sockaddr_in*)malloc(sizeof(struct sockaddr));
	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;// family
	addr.sin_port = htons(15001);//port 15001
	addr.sin_addr.s_addr=INADDR_ANY;///any address
	printf("The address before bind %s  ...\n",inet_ntoa(addr.sin_addr) );
	if(bind(sockfd,(struct sockaddr*)&addr,sizeof(addr))==-1){//bind returns -1 on error
		handle_error("bind");
	}
	printf("The address after bind %s  ...\n",inet_ntoa(addr.sin_addr) ); 
	//printf("Server address : %d\n",addr.sin_addr.s_addr);
	status("bind successul");
	// listen marks the socket as passive i.e making it possible to accept incoming connections
	if(listen(sockfd,10)==-1)
		handle_error("listen");
	// now server can accept incoming connections
	status("passive open");
	int addrlen  = sizeof(peeraddr);
	while(1){
		int connfd = accept(sockfd, (struct sockaddr*)&peeraddr,&addrlen);
		status("Accepted connection");
		if(connfd ==-1)
			handle_error("accept");
		str_echo(connfd);
		close(connfd);
	}
	printf("Death of socket \n"); 
	close(sockfd);
	return 0;
}
	
