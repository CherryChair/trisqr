////
//// Created by mpkow on 15.05.2023.
////

#include "Parser.h"

//program             :== {func_declaration | figure_declaration};
Program Parser::parse() {
    std::unordered_map<std::wstring, FuncDeclaration> * functions = {};
    std::unordered_map<std::wstring, FigureDeclaration> * figures = {};
    token = lexer->nextToken();
    std::optional<FuncDeclaration> funcDecl;
    std::optional<FigureDeclaration> figureDecl;
    bool foundFunc = true;
    bool foundFigure = true;
    while(foundFunc || foundFigure){
        foundFunc = false;
        foundFigure = false;
        if (funcDecl = this->parseFuncDecl()){
            std::wstring fName = funcDecl->getName();
            if(functions->find(fName) != functions->end()){
                (*functions)[fName] = *funcDecl;
            } else {
    //            error
            }
            foundFunc = true;
        } else if (figureDecl = this->parseFigureDecl()){
            std::wstring fName = figureDecl->getName();
            if(figures->find(fName) != figures->end()){
                (*figures)[fName] = *figureDecl;
            } else {
                //            error
            }
            foundFigure = true;
        }
    }
    return Program(*functions, *figures);
}

bool Parser::consumeIf(unsigned int token_type) {
    if(token->getTokenType() == token_type) {
        token = lexer->nextToken();
        return true;
    }
    return false;
}

//figure_declaration  :== "figure ", identifier, "{", point_list, "}";
std::optional<FigureDeclaration> Parser::parseFigureDecl() {
    //IMPLEMENTACJA
    if (!this->consumeIf(FIGURE_TYPE)){
        return std::nullopt;
    }

    if(!this->consumeIf(IDENTIFIER_TYPE)){
        //error
    }

    if (!this->consumeIf(L_CURL_BRACKET_TYPE)){
        //error missing l_bracket
    }

    std::wstring name = std::get<std::wstring>(token->getValue());

    return std::nullopt;
}

//func_declaration    :== "func ", identifier, "(", decl_argument_list, ")", code_block;
std::optional<FuncDeclaration> Parser::parseFuncDecl() {
    Position position = token->getPos();
    if (!this->consumeIf(FUNC_TYPE)){
        return std::nullopt;
    }
    if(!this->consumeIf(IDENTIFIER_TYPE)){
        //error
    }
    std::wstring name = std::get<std::wstring>(token->getValue());
    if (!this->consumeIf(L_BRACKET_TYPE)){
        //error missing l_bracket
    }
    std::vector<Parameter> params = parseParams();
    if (!this->consumeIf(R_BRACKET_TYPE)){
        //error missing r_bracket
    }
    std::optional<CodeBlock> block = parseCodeBlock();
    if (!block) {
        //error missing code block
    }
    return FuncDeclaration(name, params, block.value(), position);
}

std::vector<Parameter> Parser::parseParams() {
    std::vector<Parameter> params;
    std::unordered_map<std::wstring, bool> paramsMap;
    std::optional<Parameter> param = parseParam();
    if (param) {
        params.push_back(*param);
        paramsMap[param->getName()] = true;
        while (this->consumeIf(COMMA_TYPE)){
            param = parseParam();
            if(!param){
                //error missing param
            } else if (paramsMap.find(param->getName()) != paramsMap.end()) {
                //error duplicate param
            } else {
                params.push_back(*param);
                paramsMap[param->getName()] = true;
            }
        }
    }

    return params;
}

std::optional<Parameter> Parser::parseParam() {
    if(this->consumeIf(IDENTIFIER_TYPE)){
        return Parameter(std::get<std::wstring>(token->getValue()));
    }
    return std::nullopt;
}

std::optional<CodeBlock> Parser::parseCodeBlock() {
    if (!this->consumeIf(L_CURL_BRACKET_TYPE)){
        //error missing l_curl_bracket
        return std::nullopt;
    }
    std::vector<Statement*> statements;
    Statement * statement;
    while (statement = parseStatement()){
        statements.push_back(statement);
    }
    if (!this->consumeIf(R_CURL_BRACKET_TYPE)){
        //error missing l_curl_bracket
    }

    return CodeBlock(statements);
}

Statement * Parser::parseStatement() {
    Statement * statement;
    if((statement = parseWhileStatement()) ||
        (statement = parseIfStatement()) ||
        (statement = parseForStatement()) ||
        (statement = parseDeclarationStatement()) ||
        (statement = parseReturnStatement()))
        return statement;

}

Statement * Parser::parseWhileStatement() {
    if(!this->consumeIf(IF_TYPE)){
        return NULL;
    }
    if(!this->consumeIf(L_BRACKET_TYPE)){
        //error missing bracket
    }
    return dynamic_cast<Statement*>(new WhileStatement());
}

Statement * Parser::parseIfStatement() {
    if(!this->consumeIf(IF_TYPE)){
        return NULL;
    }
    if(!this->consumeIf(L_BRACKET_TYPE)){
        //error missing bracket
    }
    return dynamic_cast<Statement*>(new IfStatement());
}

Statement * Parser::parseForStatement() {
    if(!this->consumeIf(FOR_TYPE)){
        return NULL;
    }
    if(!this->consumeIf(L_BRACKET_TYPE)){
        //error missing bracket
    }
    return dynamic_cast<Statement*>(new ForStatement());
}


Statement * Parser::parseDeclarationStatement() {
    if(!this->consumeIf(VV_TYPE)){
        return NULL;
    }
    if(!this->consumeIf(IDENTIFIER_TYPE)){
        //error missing bracket
    }
    return dynamic_cast<Statement*>(new DeclarationStatement());
}

Statement * Parser::parseReturnStatement() {
    if(!this->consumeIf(IF_TYPE)){
        return NULL;
    }
    if(!this->consumeIf(L_BRACKET_TYPE)){
        //error missing bracket
    }
    return dynamic_cast<Statement*>(new ReturnStatement());
}
