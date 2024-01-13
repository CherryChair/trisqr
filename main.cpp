#include "lexer.h"
#include "parser.h"
#include <fstream>
#include "Program/VisitorTree.h"
#include "Program/VisitorInterpreter.h"


int main() {
    std::wstring a = L"func main() {\n";
    a += L"\tvv a = 1 + 2;\n";
    a += L"\ta = '1 + 2';\n";
    a += L"\tprint(a to str);\n";
    a += L"}\n";
    std::wstringbuf ss(a);
//    std::wistream ss(&is);

//    std::wfilebuf ss;
//    ss.open("../parser_condition_tests.trisqr", std::ios_base::in);
    ErrorHandler* eh = new ErrorHandler();
    Lexer * l = new Lexer(ss, eh, 1024, 1000, 1111, 1111);
    std::optional<Token> tkn;
    if(nullptr) {
        std::wcout << L"nullptr";
    }
    Parser * parser = new Parser(l, eh);
    auto program = parser->parse();

//    VisitorTree * vt = new VisitorTree();
//    program->accept(*vt);
//    vt->printTree(std::wcout);

    VisitorInterpreter vi = VisitorInterpreter(eh);
    program->accept(vi);

//    while(tkn = l->nextToken()){
//        printToken(*tkn);
//        if(tkn->getTokenType() == EOF_TYPE) {
//            break;
//        }
//    }
    return 0;
}
