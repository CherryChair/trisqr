#include "lexer.h"


int main() {
    std::string a = "if(a<=b) {\n\r     apple.method(1.233, 3.22);\n\r\n} \n\r";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * l = new Lexer(ss);
    Token * tkn;
    while(tkn = l->nextToken()){
        printToken(tkn);
    }
    return 0;
}
