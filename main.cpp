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

//    std::wfilebuf ss;
//    ss.open("../parser_condition_tests.trisqr", std::ios_base::in);

    ErrorHandler* eh = new ErrorHandler();

    Lexer * l = new Lexer(ss, eh, 1024, 1000, 1111, 1111);

    Parser * parser = new Parser(l, eh);
    auto program = parser->parse();

    VisitorInterpreter vi = VisitorInterpreter(eh);
    program->accept(vi);

    return 0;
}
