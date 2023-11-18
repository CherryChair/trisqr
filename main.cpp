#include "lexer.h"


int main() {
    std::string a = "if";
//    a += EOF;
    std::stringbuf ss(a);
    ErrorHandler eh = ErrorHandler();
    Lexer * l = new Lexer(ss, eh);
    std::optional<Token> tkn;
    while(tkn = l->nextToken() ){
        printToken(*tkn);
        if(tkn->getTokenType() == EOF_TYPE) {
            break;
        }
    }
    return 0;
}
