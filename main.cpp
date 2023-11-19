#include "lexer.h"


int main() {
//    std::string a = "func #HelloWorld(){\r\n print('Hell#o world#!#');\r\nif(1.23 t#o int==1){\r\n       for   in (  0,   11   #)    }\n\r";
//    std::string a = "123.12312312132896128736127836178256367125476235647812346578934265897623453142389748923748923423.1.23.123.12.31.23.12";
    std::string a = "1.2'3 to int; \n\r\r \n\n \n\r vv a;  \r\n\r\n\rvv";
//    a += EOF;
    std::stringbuf ss(a);
    ErrorHandler eh = ErrorHandler();
    Lexer * l = new Lexer(ss, eh, 1024);
    std::optional<Token> tkn;
    while(tkn = l->nextToken() ){
        printToken(*tkn);
        if(tkn->getTokenType() == EOF_TYPE) {
            break;
        }
    }
    return 0;
}
