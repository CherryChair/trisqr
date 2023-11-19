#include "lexer.h"


int main() {
    std::string a = "123.12312312132896128736127836178256367125476235647812346578934265897623453142389748923748923423.1.23.123.12.31.23.12";
//    std::string a = "1.23 to int; \n\r\nvv \r \r\nvv vv a;  \r\n\n\r\r\nlak";

//    a += EOF;
    std::stringbuf ss(a);
    ErrorHandler eh = ErrorHandler();
    Lexer * l = new Lexer(ss, eh, 5);
    std::optional<Token> tkn;
    while(tkn = l->nextToken() ){
        printToken(*tkn);
        if(tkn->getTokenType() == EOF_TYPE) {
            break;
        }
    }
    return 0;
}
