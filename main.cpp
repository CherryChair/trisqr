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

    std::unique_ptr<ErrorHandler> eh = std::make_unique<ErrorHandler>();

    std::unique_ptr<Lexer> l = std::make_unique<Lexer>(ss, eh.get(), 1024, 1000, 1111, 1111);

    std::unique_ptr<Parser> parser = std::make_unique<Parser>(l.get(), eh.get());

    std::unique_ptr<Program> program;
    try {
        program = parser->parse();
    } catch (ErrorHandler e) {

    }

    ss.close();
    //zamykanie pliku w lexerze albo parserze
    //zwalnianie parsera, errorHandlera unique_ptr

    //try catche
    VisitorSemantic vs = VisitorSemantic(eh.get());
    program->accept(vs);

    VisitorInterpreter vi = VisitorInterpreter(eh.get());
    program->accept(vi);

    return 0;
}
