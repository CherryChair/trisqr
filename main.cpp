#include "lexer.h"


int main() {
    std::string a = "\r\n \n\r";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * l = new Lexer(ss);
    Token tkn;
    while(l->nextToken() ){
        printToken(tkn);
        if(tkn.token_type == EOF_TYPE) {
            break;
        }
    }
    return 0;
}
