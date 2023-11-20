//
// Created by mpkow on 15.05.2023.
//

#include "ErrorHandler.h"
#include <iostream>

std::wostream & operator<< (std::wostream& wos, Position pos) {
    wos << L"Line " << std::to_wstring(pos.line) << L", character " << pos.characterNum;
    return wos;
}

void ErrorHandler::onLexerError(int error_type,  Position position, std::wstring value) {
    if (value.length() > line_max_char_displayed) {
        value.erase(line_max_char_displayed);
        value += L"...";
    }
    for(int i=0; i<value.length(); i++){
        char current_char = value[i];
        if (escape_sequences.find(current_char) != escape_sequences.end()) {
            value.replace(i, 1, escape_sequences.at(current_char));
            i++;
        }
    }
    std::wcerr << L"LEX_ERR: " + error_mesages.at(error_type) << std:: endl;
    std::wcerr << position << L": " << value << L" << error" << std::endl;
}
