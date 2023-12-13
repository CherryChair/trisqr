////
//// Created by mpkow on 15.05.2023.
////

#include "Parser.h"

//program             :== {func_declaration | figure_declaration};
Program Parser::parse() {
    std::unordered_map<std::wstring, FuncDeclaration> * functions = {};
    std::unordered_map<std::wstring, FigureDeclaration> * figures = {};
    token = lexer->nextToken();
    Position pos = token->getPos();
    FuncDeclaration * funcDecl;
    FigureDeclaration * figureDecl;
    bool foundFunc = true;
    bool foundFigure = true;
    while((foundFunc || foundFigure) && !this->syntax_error){
        foundFunc = false;
        foundFigure = false;
        if (funcDecl = this->parseFuncDecl()){
            std::wstring fName = funcDecl->getName();
            if(functions->find(fName) != functions->end()){
                (*functions)[fName] = *funcDecl;
            } else {
                errorHandler->onSemanticError(pos, L"Redeclaration of function " + fName);
            }
            foundFunc = true;
        } else if (figureDecl = this->parseFigureDecl()){
            std::wstring fName = figureDecl->getName();
            if(figures->find(fName) != figures->end()){
                (*figures)[fName] = *figureDecl;
            } else {
                errorHandler->onSemanticError(pos, L"Redeclaration of figure " + fName);
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

nullptr_t Parser::handleSyntaxError(const Position & position, const std::wstring & message) {
    errorHandler->onSyntaxError(position, message);
    this->syntax_error = true;
    return nullptr;
}

//figure_declaration  :== "figure ", identifier, "{", point_list, "}";
FigureDeclaration * Parser::parseFigureDecl() {
    //IMPLEMENTACJA
    if (!this->consumeIf(FIGURE_TYPE)){
        return nullptr;
    }

    if(!this->consumeIf(IDENTIFIER_TYPE)){
        //error
    }

    if (!this->consumeIf(L_CURL_BRACKET_TYPE)){
        //error missing l_bracket
    }

    std::wstring name = std::get<std::wstring>(token->getValue());

    return nullptr;
}

//func_declaration    :== "func ", identifier, "(", decl_argument_list, ")", code_block;
FuncDeclaration * Parser::parseFuncDecl() {
    Position position = token->getPos();
    if (!this->consumeIf(FUNC_TYPE)){
        return nullptr;
    }
    if(!this->consumeIf(IDENTIFIER_TYPE)){
        return this->handleSyntaxError(position, L"Missing identifer in function declaration.");
    }
    std::wstring name = std::get<std::wstring>(token->getValue());
    if (!this->consumeIf(L_BRACKET_TYPE)){
        return this->handleSyntaxError(position, L"Missing left bracket in function declaration.");
    }
    std::vector<Parameter *> params = parseParams();
    if (!this->consumeIf(R_BRACKET_TYPE)){
        return this->handleSyntaxError(position, L"Missing right bracket in function declaration.");
    }
    CodeBlock * block = parseCodeBlock();
    if (!block) {
        return this->handleSyntaxError(position, L"Missing block after function declaration.");
    }
    return new FuncDeclaration(name, params, block, position);
}

std::vector<Parameter *> Parser::parseParams() {
    std::vector<Parameter *> params;
    std::unordered_map<std::wstring, bool> paramsMap;
    Parameter * param = parseParam();
    if (param) {
        params.push_back(param);
        paramsMap[param->getName()] = true;
        while (this->consumeIf(COMMA_TYPE)){
            Position position = this->token->getPos();
            param = parseParam();
            if(!param){
                this->handleSyntaxError(position, L"Missing block after function declaration.");
                return params;
            } else if (paramsMap.find(param->getName()) != paramsMap.end()) {
                errorHandler->onSemanticError(position, L"Duplicate param " + param->getName());
            } else {
                params.push_back(param);
                paramsMap[param->getName()] = true;
            }
        }
    }

    return params;
}

Parameter * Parser::parseParam() {
    if(this->consumeIf(IDENTIFIER_TYPE)){
        return new Parameter(std::get<std::wstring>(token->getValue()));
    }
    return nullptr;
}

CodeBlock * Parser::parseCodeBlock() {
    Position position = this->token->getPos();
    if (!this->consumeIf(L_CURL_BRACKET_TYPE)){
        return nullptr;
    }
    std::vector<Statement*> statements;
    Statement * statement;
    while (statement = parseStatement()){
        statements.push_back(statement);
    }
    if (!this->consumeIf(R_CURL_BRACKET_TYPE)){
        return this->handleSyntaxError(position, L"Missing right bracket in code block.");
    }

    return new CodeBlock(statements);
}

Statement * Parser::parseStatement() {
    Statement * statement;
    if((statement = parseWhileStatement()) ||
        (statement = parseIfStatement()) ||
        (statement = parseForStatement()) ||
        (statement = parseDeclarationStatement()) ||
        (statement = parseReturnStatement()))
        return statement;
    return nullptr;
}

Statement * Parser::parseWhileStatement() {
    Position position = this->token->getPos();
    if(!this->consumeIf(IF_TYPE)){
        return nullptr;
    }
    if(!this->consumeIf(L_BRACKET_TYPE)){
        return this->handleSyntaxError(position, L"Missing left bracket in while statement.");
    }
    return dynamic_cast<Statement*>(new WhileStatement());
}

Statement * Parser::parseIfStatement() {
    Position position = this->token->getPos();
    if(!this->consumeIf(IF_TYPE)){
        return nullptr;
    }
    if(!this->consumeIf(L_BRACKET_TYPE)){
        return this->handleSyntaxError(position, L"Missing left bracket in if statement.");
    }
    return dynamic_cast<Statement*>(new IfStatement());
}

Statement * Parser::parseForStatement() {
    Position position = this->token->getPos();
    if(!this->consumeIf(FOR_TYPE)){
        return nullptr;
    }
    if(!this->consumeIf(L_BRACKET_TYPE)){
        return this->handleSyntaxError(position, L"Missing left bracket in for statement.");
    }
    return dynamic_cast<Statement*>(new ForStatement());
}


Statement * Parser::parseDeclarationStatement() {
    Position position = this->token->getPos();
    if(!this->consumeIf(VV_TYPE)){
        return nullptr;
    }
    if(!this->consumeIf(IDENTIFIER_TYPE)){
        return this->handleSyntaxError(position, L"Missing identifier in declaration statement.");
    }
    return dynamic_cast<Statement*>(new DeclarationStatement());
}

Statement * Parser::parseReturnStatement() {
    Position position = this->token->getPos();
    if(!this->consumeIf(IF_TYPE)){
        return nullptr;
    }
    return dynamic_cast<Statement*>(new ReturnStatement());
}
