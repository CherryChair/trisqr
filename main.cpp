#include "lexer.h"
#include <fstream>


int main() {
    std::wstring a = L"1.23 to int; \n\r\nvv \r \r\nvv vv a;  \r\n\n\r\r\nlak";
//    std::string a = "123.12312312132896128736127836178256367125476235647812346578934265897623453142389748923748923423.1.23.123.12.31.23.12";
//    std::wstring a = L"\n\rvv a  = 3.3 ;   \n\r  \n\r   if ( a != 5.4) { \n\rfigure && ||   \n\r}";
    std::wstringbuf ss(a);
//    std::wistream ss(&is);
//    std::wfilebuf ss;
//    ss.open("../example_program.trsqr", std::ios_base::in);
    ErrorHandler* eh = new ErrorHandler();
    Lexer * l = new Lexer(ss, eh, 1024, 1000, 1111, 1111);
    std::optional<Token> tkn;
    if(nullptr) {
        std::wcout << L"nullptr";
    }
    if(NULL) {
        std::wcout << L"NULL";
    }
//    while(tkn = l->nextToken()){
//        printToken(*tkn);
//        if(tkn->getTokenType() == EOF_TYPE) {
//            break;
//        }
//    }
    return 0;
}
