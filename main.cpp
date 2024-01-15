#include "Lexer/lexer.h"
#include "Parser/Parser.h"
#include <fstream>
#include "Visitors/VisitorTree.h"
#include "Visitors/VisitorSemantic.h"
#include "Visitors/VisitorInterpreter.h"


int main(int argc, char *argv[]) {
//    std::wstring a = L"func main() {\n";
//    a += L"\tvv a = 1 + 2;\n";
//    a += L"\ta = '1 + 2';\n";
//    a += L"\tprint(a to str);\n";
//    a += L"}\n";
//    std::wstringbuf ss(a);

    if (argc != 2) {
        std::cout << "Specify file to interpret!" << std::endl;
        return 0;
    }

    std::string filename = argv[1];

    std::wfilebuf ss;
    if (!ss.open(filename, std::ios_base::in)) {
        std::cout << "File " + filename + " can't be read or it doesn't exist." << std::endl;
        return 0;
    }

    ErrorHandler* eh = new ErrorHandler();

    Lexer * l = new Lexer(ss, eh, 1024, 1000, 1111, 1111);

    Parser * parser = new Parser(l, eh);
    auto program = parser->parse();

    VisitorSemantic vs = VisitorSemantic(eh);
    program->accept(vs);

    VisitorInterpreter vi = VisitorInterpreter(eh);
    program->accept(vi);

    return 0;
}
