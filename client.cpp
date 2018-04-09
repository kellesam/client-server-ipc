#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

int main() {
    int socket_FD;
    struct sockaddr_in server_address;
    struct hostent* server_host_info;
    char buffer[600];
    
    memset((char*)&server_address, '\0', sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(26578);      //randomly chosen port number
	server_host_info = gethostbyname("localhost");
	memcpy((char*)&server_address.sin_addr.s_addr, (char*)server_host_info->h_addr, server_host_info->h_length);

	socket_FD = socket(AF_INET, SOCK_STREAM, 0);
	connect(socket_FD, (struct sockaddr*)&server_address, sizeof(server_address));
	
	memset(buffer, '\0', sizeof(buffer));
    fgets(buffer, 501, stdin);              //read in 500 chars
    buffer[strcspn(buffer, "\n")] = '\0';   //trim newline
    
	send(socket_FD, buffer, strlen(buffer), 0);
	memset(buffer, '\0', sizeof(buffer));
	read(socket_FD, buffer, sizeof(buffer) - 1);
	std::cout << buffer << std::endl;
    
    return 0;
}
