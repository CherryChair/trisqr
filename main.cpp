#include "lexer.h"
#include <fstream>


int main() {
//    std::string a = "func #HelloWorld(){\r\n print('Hell#o world#!#');\r\nif(1.23 t#o int==1){\r\n       for   in (  0,   11   #)    }\n\r";
//    std::string a = "123.12312312132896128736127836178256367125476235647812346578934265897623453142389748923748923423.1.23.123.12.31.23.12";
    std::wstring a = L"a123456789";
    std::wstringbuf ss(a);
//    std::wistream ss(&is);
//    std::wfilebuf ss;
//    ss.open("../example_program.trsqr", std::ios_base::in);
    ErrorHandler eh = ErrorHandler();
    Lexer * l = new Lexer(ss, eh, 5, 5, 0, 0);
    std::optional<Token> tkn;
    while(tkn = l->nextToken()){
        printToken(*tkn);
        if(tkn->getTokenType() == EOF_TYPE) {
            break;
        }
    }
    return 0;
}
