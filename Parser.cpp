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
    auto name = (token->getValue());
    if(!this->consumeIf(IDENTIFIER_TYPE)){
        return this->handleSyntaxError(position, L"Missing identifer in function declaration.");
    }
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
    return new FuncDeclaration(std::get<std::wstring>(name), params, block, position);
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
    auto name = token->getValue();
    if(this->consumeIf(IDENTIFIER_TYPE)){
        return new Parameter(std::get<std::wstring>(name));
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
    Position position = token->getPos();
    ConditionAndBlock * conditionAndBlock = this->parseConditionAndBlock(L"while", WHILE_TYPE);
    if (!conditionAndBlock) {
        return nullptr;
    }
    return new WhileStatement(conditionAndBlock, position);
}

//if_stmnt            :== "if", "(",  expression, ")", code_block, {"elsif", "(",  expression, ")", code_block }, ["else", code_block];
Statement * Parser::parseIfStatement() {
    Position position = token->getPos();
    ConditionAndBlock * ifConditionAndBlock = this->parseConditionAndBlock(L"if", IF_TYPE);
    if (!ifConditionAndBlock) {
        return nullptr;
    }
    std::vector<ConditionAndBlock *> elsifConditionsAndBlocks;
    while(ConditionAndBlock * elsifConditionAndBlock = this->parseConditionAndBlock(L"elsif", ELSIF_TYPE)){
        elsifConditionsAndBlocks.push_back(elsifConditionAndBlock);
    }
    ConditionAndBlock * elseConditionAndBlock = this->parseConditionAndBlock(L"else", ELSE_TYPE);
    return new IfStatement(ifConditionAndBlock, elsifConditionsAndBlocks, elseConditionAndBlock, position);
}

//for_stmnt           :== "for", identifier, "in", expression_or_range, code_block;
Statement * Parser::parseForStatement() {
    Position position = this->token->getPos();
    if(!this->consumeIf(FOR_TYPE)){
        return nullptr;
    }
    auto name = token->getValue();
    if(!this->consumeIf(IDENTIFIER_TYPE)){
        return this->handleSyntaxError(position, L"Missing identifier in for statement.");
    }
    if(!this->consumeIf(IN_TYPE)){
        return this->handleSyntaxError(position, L"Missing 'in' keyword in for statement");
    }


    Position expressionPosition = this->token->getPos();
    Expression * expression;
    if(this->consumeIf(RANGE_TYPE)){
        if(!this->consumeIf(L_BRACKET_TYPE)){
            return this->handleSyntaxError(expressionPosition, L"Missing left bracket in range expression.");
        }
    } else if (!(expression = this->parseExpression())) {
        return this->handleSyntaxError(expressionPosition, L"Missing expression or range in for statement.");
    }
    CodeBlock * block = this->parseCodeBlock();
    if(!block) {
        return this->handleSyntaxError(expressionPosition, L"Missing code block after for statement.");
    }
    return new ForStatement(std::get<std::wstring>(name), expression, block, position);
}

// declaration         :== "vv ", identifier, ["=", expression], ";";
Statement * Parser::parseDeclarationStatement() {
    Position position = this->token->getPos();
    if(!this->consumeIf(VV_TYPE)){
        return nullptr;
    }
    auto name = token->getValue();
    if(!this->consumeIf(IDENTIFIER_TYPE)){
        return this->handleSyntaxError(position, L"Missing identifier in declaration statement.");
    }

    Expression * expression = nullptr;
    if(this->consumeIf(ASSIGN_TYPE)){
        expression = this->parseExpression();
    }

    if(!this->consumeIf(SEMICOLON_TYPE)){
        this->handleSyntaxError(position, L"Missing semicolon on end of declaration.");
    }

    return new DeclarationStatement(std::get<std::wstring>(name), expression, position);
}


//identifier_stmnt, ["=", expression], ";"
Statement * Parser::parseIdentifierOrAssignmentStatement() {
    Position position = this->token->getPos();

    Statement * identifierStatement;
    if (!(identifierStatement = this->parseIdentifierDotStatement())) {
        return nullptr;
    }

    Expression * expression = nullptr;
    if(this->consumeIf(ASSIGN_TYPE)){
        expression = this->parseExpression();
    }

    if(!this->consumeIf(SEMICOLON_TYPE)){
        this->handleSyntaxError(position, L"Missing semicolon on end of declaration.");
    }

    if (!expression) {
        return identifierStatement;
    }

    return new IdentifierStatementAssign(identifierStatement, expression, position);
}

//identifier_stmnt    :== part, {".", part};
Statement * Parser::parseIdentifierDotStatement() {
    Position position = this->token->getPos();
    Statement * leftIdentifierListCallStatement;
    if (!(leftIdentifierListCallStatement = this->parseIdentifierListCallStatement())) {
        return nullptr;
    }
    while (this->consumeIf(DOT_TYPE)) {
        Position identifierPos = this->token->getPos();
        Statement * rightIdentifierListCallStatement;
        if (!(rightIdentifierListCallStatement = this->parseIdentifierListCallStatement())) {
            errorHandler->onSyntaxError(identifierPos, L"No identifier after dot.");
            break;
        }
        leftIdentifierListCallStatement = new IdentifierDotStatement(leftIdentifierListCallStatement, rightIdentifierListCallStatement, identifierPos);
    }

    return leftIdentifierListCallStatement;
}

//part                :== part_call, {"[", expression, "]"};
Statement * Parser::parseIdentifierListCallStatement() {
    Position position = this->token->getPos();
    Statement * identifierFunctionCallStatement;
    if (!(identifierFunctionCallStatement = this->parseIdentifierFunctionCallStatement())) {
        return nullptr;
    }
    std::vector<Expression *> expressions;
    while(this->consumeIf(L_SQR_BRACKET_TYPE)) {
        Position expressionPosition = this->token->getPos();
        if(Expression * expression = this->parseExpression()) {
            expressions.push_back(expression);
        } else {
            errorHandler->onSyntaxError(expressionPosition, L"Missing expression in list element call.");
        }
        if (!this->consumeIf(R_SQR_BRACKET_TYPE)) {
            errorHandler->onSyntaxError(expressionPosition, L"Missing right square bracket in list element call.");
            break;
        }
    }
    if (expressions.empty()) {
        return  identifierFunctionCallStatement;
    }
    return new IdentifierStatementListCall(identifierFunctionCallStatement, expressions, position);
}

//part_call           :== identifier, ["(", argument_list, ")"];
Statement * Parser::parseIdentifierFunctionCallStatement() {
    Position position = this->token->getPos();
    bool isFunctionCall = false;

    Statement * identifierStatement = this->parseIdentifierStatement();
    if(!identifierStatement) {
        return nullptr;
    }

    std::vector<Expression *> expressions;

    //- argument_list       :== [expression, {",", expression}];
    if(!this->consumeIf(L_BRACKET_TYPE)){
        Position expressionPos = this->token->getPos();
        if (Expression * expression = parseExpression()) {
            expressions.push_back(expression);
            while(consumeIf(COMMA_TYPE)) {
                expressionPos = this->token->getPos();
                if(expression = parseExpression()) {
                    expressions.push_back(expression);
                } else {
                    errorHandler->onSyntaxError(expressionPos, L"Missing expression after comma in function call");
                }
            }
        }
        if(!this->consumeIf(R_BRACKET_TYPE)){
            errorHandler->onSyntaxError(expressionPos, L"Missing right bracket closing function call");
        }
        isFunctionCall = true;
    }

    if (!isFunctionCall) {
        return identifierStatement;
    }

    return new IdentifierStatementFunctionCall(identifierStatement, expressions, position);
}

Statement * Parser::parseIdentifierStatement() {
    Position position = this->token->getPos();
    auto name = this->token->getValue();
    if(!this->consumeIf(IDENTIFIER_TYPE)){
        return nullptr;
    }
    return new IdentifierStatement(std::get<std::wstring>(name), position);
}

//return              :== "return ", [expression], ";"
Statement * Parser::parseReturnStatement() {
    Position position = this->token->getPos();
    if(!this->consumeIf(RETURN_TYPE)){
        return nullptr;
    }

    Expression * expression = this->parseExpression();

    if(!this->consumeIf(SEMICOLON_TYPE)){
        errorHandler->onSyntaxError(position, L"Missing semicolon after return statement");
    }

    return new ReturnStatement(expression, position);
}

//expression          :== bool_and, {"||",  bool_and};
Expression * Parser::parseExpression() {
    return nullptr;
}
