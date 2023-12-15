#include "lexer.h"
#include "parser.h"
#include <fstream>
#include "Program/VisitorTree.h"


int main() {
//    std::wstring a = L"func a(m) {\nvv test = 1.23 to int; #aoskdopiaskdp \n test = 3.22;\n \n\n a(12, test, pi)['apple'][test][32.1].b = test.b; if ( a<= 5.0) {\n";
//    a += L"vv g = 1;\n}elsif(apple) {\nmain();\n} elsif(apple || true || false && true && a + 5 || true && a*5.0 to int == 12) {\nmain();\n} else {\ntest.a(true).b[none][(4,4)].next();}\n";
//    a += L"while(a != false) {\nreturn a[2].b;\n}";
//    a += L"while(!a *10+2-2 /2 +test != false) {\nreturn a[2].b;\n}";
//    a += L"vv sajdposaj = -23.0;";
//    a += L"for j in [12832921, 232, a.next(), lp >= 90, pa] {for i in range(123, a() >=209 && 22 *2){return;}}\n";
//    a += L"s = [123, a.a(a(), a(12))[23][ '213.'], [1,[2,[3,4]]]];";
//    a += L"r = (sps, [1293, 921, 'saijodasjda']);";
//    a += L"}\n";
//    a += L"figure Triangle {\n";
//    a += L"a: fun([1,2,3,4]),\n";
//    a += L"b: 12 && 23 *2+2-1 || 123.2 == a(),\n";
//    a += L"c: (12.4, 45335)\n";
//    a += L"}";
//    std::string a = "123.12312312132896128736127836178256367125476235647812346578934265897623453142389748923748923423.1.23.123.12.31.23.12";
//    std::wstring a = L"\n\rvv a  = 3.3 ;   \n\r  \n\r   if ( a != 5.4) { \n\rfigure && ||   \n\r}";
//    std::wstringbuf ss(a);
//    std::wistream ss(&is);
    std::wfilebuf ss;
    ss.open("../parser_test.trisqr", std::ios_base::in);
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
