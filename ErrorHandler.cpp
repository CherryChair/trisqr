//
// Created by mpkow on 15.05.2023.
//

#include "ErrorHandler.h"
#include <iostream>

std::ostream & operator<< (std::ostream& os, Position pos) {
    os << "Line " << std::to_string(pos.line) << ", character " << pos.characterNum;
    return os;
}

void ErrorHandler::onLexerError(int error_type,  Position position, std::string value) {
    if (value.length() > line_max_char_displayed) {
        value.erase(line_max_char_displayed);
        value += "...";
    }
    if (error_type != ERR_NOT_CLOSED_STRING){
        for(int i=0; i<value.length(); i++){
            char current_char = value[i];
            if (escape_sequences.find(current_char) != escape_sequences.end()) {
                value.replace(i, 1, escape_sequences.at(current_char));
            }
        }
    }
    std::cerr << "LEX_ERR: " + error_mesages.at(error_type) << std:: endl;
    std::cerr << position << ": " << value << " << error" << std::endl;
}
