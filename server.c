#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define BUFF_LEN	100
#define IP_VAL		"127.0.0.1"

int main()
{
	int server_sock_fd;
	int client_sock_fd;
	int ret;
	int client_length;

	char buff[BUFF_LEN];
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;

	printf("\n* * * * * Server Program Running * * * * * \n\n");
/*	1. Socket: Creates a un-named socket and Returns Scoket Descriptor	*/

	server_sock_fd=socket(AF_INET,SOCK_STREAM,0);

	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr(IP_VAL);
	server_addr.sin_port=htons(5555); // Host to Network Short for Network Byte Ordering
	if(server_sock_fd){
		printf("Server Socket Created Socket fd=%d....\n",server_sock_fd);
	}
	else{
		perror("Error in Creating Server Socket:\n");
		goto err;
	}

/*	2. bind():  Names a Socket and assigns an address to the Socket	*/

	ret=bind(server_sock_fd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	if(ret==0){
		printf("Successfull In Naming Server Socket......\n");
	}
	else{
		perror("Error in Binding :\n");
		goto err;
	}
/*	3.Listen(): Creates a Socket Queue for Incoming Pending Requests */

	ret=listen(server_sock_fd,0);
	if(ret==0){
		printf("Server Listens and Creates Socket Queue......\n");
	}
	else{
		perror("Error in Creating Socket Queue:\n");
		goto err;
	}

	printf("Server Waiting.......\n");

/*	4. accept(): Accepting Connections	*/

	client_length=sizeof(struct sockaddr_in);

	client_sock_fd=accept(server_sock_fd,(struct sockaddr *)&client_addr, &client_length);
	if(client_sock_fd){
		printf("Server Accepted Client Connection......\n");
	}
	else{
		perror("Error in accepting connection:\n");
		goto err;
	}

/*	5.Read(): Reading from Client Socket	*/
	int i=10;
	while(i > 0) {
		memset(buff,BUFF_LEN,0);
		ret=read(client_sock_fd,buff,BUFF_LEN);
		if(ret<0){
			perror("Error in Reading from Client:\n");
			goto err;
		}
		else{
			printf("\nClient:%s\n",buff);
		}

/*	6.write(): Writing to Client Socket	*/
		printf("Server Enter Data:");
		scanf("%s",buff);
		ret=write(client_sock_fd,buff,BUFF_LEN);
		if(ret < 0){
			perror("Error in Writing\n");
			goto err;
		}
	i--;
	}//end of while
err:
	close(server_sock_fd);
	close(client_sock_fd);

	return 0;

}
