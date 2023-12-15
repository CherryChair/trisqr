#include "lexer.h"
#include "parser.h"
#include <fstream>
#include "Program/VisitorTree.h"


int main() {
    std::wstring a = L"func a(m) {\nvv test = 1.23 to int; #aoskdopiaskdp \n test = 3.22;\n \n\n a(12, test, pi)['apple'][test][32.1].b = test.b; if ( a<= 5.0) {\nvv g = 1;\n}elsif(apple) {\nmain();\n}}"
                     L" elsif(apple || true || false && true && a + 5 || true && a*5.0 to int == 12) {\nmain();\n} else {\ntest.a(true).b[none][(4,4)].next();}\n}";
//                     L"[test][32.1].b = test.b; if ( a<= 5.0) {\nvv g = 1;\n} elsif(apple || true || false && true && a + 5) {\nmain();\n} else {\ntest.a(true).b[none][(4,4)].next();}\n}";
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
    Parser * parser = new Parser(l, eh);
    Program * program = parser->parse();
    VisitorTree * vt = new VisitorTree();
    program->accept(*vt);
    vt->printTree();
//    while(tkn = l->nextToken()){
//        printToken(*tkn);
//        if(tkn->getTokenType() == EOF_TYPE) {
//            break;
//        }
//    }
    return 0;
}
