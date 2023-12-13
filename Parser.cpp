////
//// Created by mpkow on 15.05.2023.
////

#include "Parser.h"

//program             :== {func_declaration | figure_declaration};
Program * Parser::parse() {
    std::unordered_map<std::wstring, FuncDeclaration> * functions = {};
    std::unordered_map<std::wstring, FigureDeclaration> * figures = {};
    token = lexer->nextToken();
    Position pos = token->getPos();
    FuncDeclaration * funcDecl;
    FigureDeclaration * figureDecl;
    bool foundFunc = true;
    bool foundFigure = true;
    while((foundFunc || foundFigure) && !this->blocking_syntax_error){
        foundFunc = false;
        foundFigure = false;
        if (funcDecl = this->parseFuncDecl()){
            std::wstring fName = funcDecl->getName();
            if(functions->find(fName) != functions->end()){
                (*functions)[fName] = *funcDecl;
            } else {
                this->handleSemanticError(pos, L"Redeclaration of function " + fName);
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
    return new Program(*functions, *figures);
}

bool Parser::consumeIf(unsigned int token_type) {
    if(token->getTokenType() == token_type) {
        token = lexer->nextToken();
        return true;
    }
    return false;
}

std::variant<int, double, std::wstring> Parser::mustBe() {

};


nullptr_t Parser::handleSyntaxError(const Position & position, const std::wstring & message) {
    errorHandler->onSyntaxError(position, message);
    this->blocking_syntax_error = true;
    return nullptr;
}

void Parser::handleSemanticError(const Position &position, const std::wstring &message) {
    errorHandler->onSemanticError(position, message);
    this->semantic_error = true;
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
    std::vector<Parameter *> params = parseFunctionParams();
    if (!this->consumeIf(R_BRACKET_TYPE)){
        return this->handleSyntaxError(position, L"Missing right bracket in function declaration.");
    }
    CodeBlock * block = parseCodeBlock();
    if (!block) {
        this->handleSyntaxError(position, L"Missing block after function declaration.");
    }
    return new FuncDeclaration(name, params, block, position);
}

//decl_argument_list  :== [identifier, {", ", identifier}];
std::vector<Parameter *> Parser::parseFunctionParams() {
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
                errorHandler->onSyntaxError(position, L"Missing param after comma.");
                return params;
            } else if (paramsMap.find(param->getName()) != paramsMap.end()) {
                this->handleSemanticError(position, L"Duplicate param " + param->getName());
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

//code_block          :== "{", {statement}, "}";
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
        this->handleSyntaxError(position, L"Missing right bracket in code block.");
    }

    return new CodeBlock(statements);
}

//statement           :== while_stmnt
//                        | for_stmnt
//                        | if_stmnt
//                        | declaration
//                        | identifier_stmnt, ["=", expression], ";"
//                        | return;
Statement * Parser::parseStatement() {
    Statement * statement;
    if((statement = parseWhileStatement()) ||
        (statement = parseIfStatement()) ||
        (statement = parseForStatement()) ||
        (statement = parseDeclarationStatement()) ||
        (statement = parseIdentifierOrAssignmentStatement()) ||
        (statement = parseReturnStatement()))
        return statement;
    return nullptr;
}


ConditionAndBlock * Parser::parseConditionAndBlock(const std::wstring & statement_type, token_type tokenType) {
    Position position = this->token->getPos();
    if(!this->consumeIf(tokenType)){
        return nullptr;
    }
    if(!this->consumeIf(L_BRACKET_TYPE)){
        return this->handleSyntaxError(position, L"Missing left bracket in " + statement_type + L" statement.");
    }
    Expression * expression = this->parseExpression();

    if(!expression) {
        return this->handleSyntaxError(position, L"Missing expression in " + statement_type + L" statement.");
    }
    if(!this->consumeIf(R_BRACKET_TYPE)){
        return this->handleSyntaxError(position, L"Missing right bracket in " + statement_type + L" statement.");
    }

    CodeBlock * block = parseCodeBlock();
    if (!block) {
        return this->handleSyntaxError(position, L"Missing block after " + statement_type + L" statement.");
    }
    return new ConditionAndBlock(expression, block);
}

//while_stmnt         :== "while", "(",  expression, ")", code_block;
Statement * Parser::parseWhileStatement() {
    ConditionAndBlock * conditionAndBlock = this->parseConditionAndBlock(L"while", WHILE_TYPE);
    if (!conditionAndBlock) {
        return nullptr;
    }
    return new WhileStatement(conditionAndBlock);
}

//if_stmnt            :== "if", "(",  expression, ")", code_block, {"elsif", "(",  expression, ")", code_block }, ["else", code_block];
Statement * Parser::parseIfStatement() {
    ConditionAndBlock * ifConditionAndBlock = this->parseConditionAndBlock(L"if", IF_TYPE);
    if (!ifConditionAndBlock) {
        return nullptr;
    }
    std::vector<ConditionAndBlock *> elsifConditionsAndBlocks;
    while(ConditionAndBlock * elsifConditionAndBlock = this->parseConditionAndBlock(L"elsif", ELSIF_TYPE)){
        elsifConditionsAndBlocks.push_back(elsifConditionAndBlock);
    }
    ConditionAndBlock * elseConditionAndBlock = this->parseConditionAndBlock(L"else", ELSE_TYPE);
    return new IfStatement(ifConditionAndBlock, elsifConditionsAndBlocks, elseConditionAndBlock);
}

//for_stmnt           :== "for", identifier, "in", expression_or_range, code_block;
Statement * Parser::parseForStatement() {
    Position position = this->token->getPos();
    if(!this->consumeIf(FOR_TYPE)){
        return nullptr;
    }
    if(!this->consumeIf(IDENTIFIER_TYPE)){
        return this->handleSyntaxError(position, L"Missing identifier in for statement.");
    }
    std::wstring name = std::get<std::wstring>(token->getValue()); //TODO to jest złe, bierze wartość z następnego tokena
    if(!this->consumeIf(IN_TYPE)){
        return this->handleSyntaxError(position, L"Missing 'in' keyword in for statement");
    }

    position = this->token->getPos();
    Expression * expression;
    if(this->consumeIf(RANGE_TYPE)){
        if(!this->consumeIf(L_BRACKET_TYPE)){
            return this->handleSyntaxError(position, L"Missing left bracket in range expression.");
        }
    } else if (!(expression = this->parseExpression())) {
        return this->handleSyntaxError(position, L"Missing expression or range in for statement.");
    }
    CodeBlock * block = this->parseCodeBlock();
    if(!block) {
        return this->handleSyntaxError(position, L"Missing code block after for statement.");
    }
    return new ForStatement(name, expression, block);

}


Statement * Parser::parseDeclarationStatement() {
    Position position = this->token->getPos();
    if(!this->consumeIf(VV_TYPE)){
        return nullptr;
    }
    if(!this->consumeIf(IDENTIFIER_TYPE)){
        return this->handleSyntaxError(position, L"Missing identifier in declaration statement.");
    }
    return new DeclarationStatement();
}

Statement * Parser::parseIdentifierOrAssignmentStatement() {
    return nullptr;
}

Statement * Parser::parseReturnStatement() {
    Position position = this->token->getPos();
    if(!this->consumeIf(IF_TYPE)){
        return nullptr;
    }
    return new ReturnStatement();
}

Expression * Parser::parseExpression() {
    return nullptr;
}
