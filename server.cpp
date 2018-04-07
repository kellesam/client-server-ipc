#include <iostream>
#include <string>
#include <sstream>

int main() {

    const int SCREEN_WIDTH = 80;

    std::string input_string = "Lorem ipsum dolor abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz sit amet, debet latine eruditi in has, vim no alterum assentior. Sed quas virtute offendit at, nibh equidem eam eu. Mazim saepe tibique an duo, no ius oratio aliquip, an vim indoctum interesset.";
    std::string formatted_string = "";

    std::cout << "String is " << input_string.length() << " chars" << std::endl;

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
            
            if (char_count == SCREEN_WIDTH || char_count == SCREEN_WIDTH-1) {
                formatted_string += '\n';
                char_count = 0;
            }
            else {
                formatted_string += ' ';
                char_count++;
            }
        }
        
        //word doesn't fit but is less than SCREEN_WIDTH
        else if (word.length() < SCREEN_WIDTH) {
            formatted_string += '\n';
            formatted_string += word;
            char_count = word.length();
            
            if (char_count == SCREEN_WIDTH || char_count == SCREEN_WIDTH-1) {
                formatted_string += '\n';
                char_count = 0;
            }
            else {
                formatted_string += ' ';
                char_count++;
            }
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
            
            if (char_count == SCREEN_WIDTH || char_count == SCREEN_WIDTH-1) {
                formatted_string += '\n';
                char_count = 0;
            }
            else {
                formatted_string += ' ';
                char_count++;
            }
        }
    }
    
    std::cout << formatted_string << std::endl;

    return 0;
}