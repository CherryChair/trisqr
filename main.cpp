#include "lexer.h"


int main() {
    std::string a = "1.1234567891234567891234567890";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * l = new Lexer(ss);
    Token * tkn;
    while(tkn = l->nextToken() ){
        printToken(tkn);
        if(tkn->token_type == EOF_TYPE) {
            break;
        }
    }
    return 0;
}
