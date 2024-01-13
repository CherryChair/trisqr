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
    this->displayError(L"LEX_ERR", error_type, position, value, true);
}

void ErrorHandler::displayError(std::wstring error_type, int error_subtype,  Position position, std::wstring value, bool escape) {
    if (value.length() > line_max_char_displayed) {
        value.erase(line_max_char_displayed);
        value += L"...";
    }
    if(escape) {
        for(int i=0; i<value.length(); i++){
            char current_char = value[i];
            std::unordered_map<wchar_t, std::wstring>::const_iterator iter = escape_sequences.find(current_char);
            if (iter != escape_sequences.end()) {
                value.replace(i, 1, iter->second);
                i++;
            }
        }
    }
    std::wcerr << error_type + L": " + error_mesages.at(error_subtype) << std:: endl;
    std::wcerr << position << L": " << value << L" << error" << std::endl;
}

void ErrorHandler::onSyntaxError(Position position, std::wstring value) {
    this->displayError(L"SYN_ERR", ERR_INVALID_SYNTAX, position, value, true);
}

void ErrorHandler::onSemanticError(Position position, std::wstring value) {
    this->displayError(L"SEM_ERR", ERR_SEMANTIC, position, value, true);
}

void ErrorHandler::onRuntimeError(Position position, std::wstring value) {
    this->displayError(L"RUN_ERR", ERR_RUNTIME, position, value, true);
}

void ErrorHandler::onInterpreterError(Position position, std::wstring value) {
    this->displayError(L"INT_ERR", ERR_INTERPRETER, position, value, true);
}

void ErrorHandler::onInterpreterError(std::wstring value) {
    std::wcerr << L"INR_ERR: " + error_mesages.at(ERR_INTERPRETER) << std:: endl;
    std::wcerr << value << L" << error" << std::endl;
}