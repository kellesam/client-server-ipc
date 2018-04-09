#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

const int SCREEN_WIDTH = 80;

void addEndChar(int* char_count, std::string* output) {
    if (*char_count == SCREEN_WIDTH || *char_count == SCREEN_WIDTH-1) {
        *output += '\n';
        *char_count = 0;
    }
    else {
        *output += ' ';
        *char_count += 1;
    }
}

int main() {

    int socket_FD, connection_FD;
    struct sockaddr_in server_address, client_address;
    socklen_t size_of_client_info;
    char buffer[600];
    
    memset((char *)&server_address, '\0', sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(26578);
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	socket_FD = socket(AF_INET, SOCK_STREAM, 0);
	bind(socket_FD, (struct sockaddr *)&server_address, sizeof(server_address));
	listen(socket_FD, 1);

	while(true) {
		size_of_client_info = sizeof(client_address);
		connection_FD = accept(socket_FD, (struct sockaddr *)&client_address, &size_of_client_info);
	
	    memset(buffer, '\0', sizeof(buffer));
	    read(connection_FD, buffer, sizeof(buffer) - 1);
	
	    std::string input_string = buffer;
	    std::string formatted_string = "";
	
	    if (input_string.length() <= SCREEN_WIDTH) {
	        formatted_string += input_string;
	        formatted_string += '\n';
	        std::cout << formatted_string << std::endl;
	        return 0;
	    }
	    
	    std::istringstream ss(input_string);
	    std::string word;
	    int char_count = 0;
	    
	    while(std::getline(ss, word, ' ')) {
	        //word fits on line
	        if (char_count + word.length() <= SCREEN_WIDTH) {
	            formatted_string += word;
	            char_count += word.length();
	            addEndChar(&char_count, &formatted_string);
	        }
	        
	        //word doesn't fit but is less than SCREEN_WIDTH
	        else if (word.length() < SCREEN_WIDTH) {
	            formatted_string += '\n';
	            formatted_string += word;
	            char_count = word.length();
	            addEndChar(&char_count, &formatted_string);
	        }
	        
	        //word too long for own line
	        else {
	            int space_left = SCREEN_WIDTH - char_count;
	            std::cout << space_left << std::endl;
	            formatted_string += word.substr(0, space_left);
	            formatted_string += '\n';
	            char_count = 0;
	            
	            int word_left = word.length() - space_left;
	            while (word_left > SCREEN_WIDTH) {
	                std::string slice = word.substr(word.length() - word_left, SCREEN_WIDTH);
	                formatted_string += slice;
	                formatted_string += '\n';
	                word_left -= SCREEN_WIDTH;
	            }
	            
	            std::string word_leftovers = word.substr(word.length() - word_left, SCREEN_WIDTH);
	            formatted_string += word_leftovers;
	            char_count += word_leftovers.length();
	            
	            addEndChar(&char_count, &formatted_string);
	        }
	    }
	    
		std::cout << formatted_string << std::endl;
	    send(connection_FD, formatted_string.c_str(), formatted_string.length(), 0);
		close(connection_FD);
	}

	close(socket_FD);

    return 0;
}
