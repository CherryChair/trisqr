////
//// Created by mpkow on 15.05.2023.
////

#include "Parser.h"

//program             :== {func_declaration | figure_declaration};
Program * Parser::parse() {
    std::unordered_map<std::wstring, FuncDeclaration *> functions = {};
    std::unordered_map<std::wstring, FigureDeclaration *> figures = {};
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
            auto fName = funcDecl->getName();
            if(functions.find(fName) == functions.end()){
                functions[fName] = funcDecl;
            } else {
                this->handleSemanticError(pos, L"Redeclaration of function " + fName);
            }
            foundFunc = true;
        } else if (figureDecl = this->parseFigureDecl()){
            std::wstring fName = figureDecl->getName();
            if(figures.find(fName) == figures.end()){
                figures[fName] = figureDecl;
            } else {
                errorHandler->onSemanticError(pos, L"Redeclaration of figure " + fName);
            }
            foundFigure = true;
        }
    }
    return new Program(functions, figures);
}

bool Parser::consumeIf(unsigned int token_type) {
    while(token->getTokenType() == COMMENT_TYPE) {
        token = lexer->nextToken();
    }
    if(token->getTokenType() == token_type) {
        token = lexer->nextToken();
        return true;
    }
    return false;
}


nullptr_t Parser::handleSyntaxError(const Position & position, const std::wstring & message) {
    errorHandler->onSyntaxError(position, message);
    this->blocking_syntax_error = true;
    throw;
    return nullptr;
}

void Parser::handleSemanticError(const Position &position, const std::wstring &message) {
    errorHandler->onSemanticError(position, message);
    this->semantic_error = true;
}

// figure_declaration  :== "figure ", identifier, "{", point_list, "}";
// point_list          :== point_declaration, {",", point_declaration}, "," "color", ":",
FigureDeclaration * Parser::parseFigureDecl() {
    Position position = token->getPos();
    if (!this->consumeIf(FUNC_TYPE)){
        return nullptr;
    }
    auto name = (token->getValue());
    if(!this->consumeIf(IDENTIFIER_TYPE)){
        this->handleSyntaxError(position, L"Missing identifer in function declaration.");
    }
    if (!this->consumeIf(L_CURL_BRACKET_TYPE)){
        this->handleSyntaxError(position, L"Missing left bracket in function declaration.");
    }
    std::vector<Parameter *> params = parseFigureParams();
    if (!this->consumeIf(R_CURL_BRACKET_TYPE)){
        this->handleSyntaxError(position, L"Missing right bracket in function declaration.");
    }
    return new FigureDeclaration(std::get<std::wstring>(name), params, position);
}

// point_list          :== point_declaration, {",", point_declaration}
std::vector<Parameter *> Parser::parseFigureParams() {
    std::vector<Parameter *> params;
    std::unordered_map<std::wstring, bool> paramsMap;
    Position position = this->token->getPos();
    Parameter * param = parseFigureParam();
    if (param) {
        params.push_back(param);
        paramsMap[param->getName()] = true;
        while (this->consumeIf(COMMA_TYPE)){
            Position position = this->token->getPos();
            param = parseFigureParam();
            if(!param){
                this->handleSyntaxError(position, L"Missing param after comma.");
                return params;
            } else if (paramsMap.find(param->getName()) != paramsMap.end()) {
                this->handleSemanticError(position, L"Duplicate param " + param->getName());
            } else {
                params.push_back(param);
                paramsMap[param->getName()] = true;
            }
        }
    }

    if (params.empty()) {
        this->handleSemanticError(position, L"No params in figure declaration.");
    }

    return params;
}

//point_declaration   :== identifier, ":", expression;
Parameter * Parser::parseFigureParam() {
    Position position = this->token->getPos();
    auto name = token->getValue();
    if(!this->consumeIf(IDENTIFIER_TYPE)){
        return nullptr;
    }

    if(!this->consumeIf(COLON_TYPE)){
        this->handleSemanticError(position, L"Missing identifier in figure param");
    }

    Expression * expression;
    if (!(expression = this->parseExpression())) {
        this->handleSemanticError(position, L"Missing expression in figure param");
    }
    return new FigureParameter(std::get<std::wstring>(name), expression);
}

//func_declaration    :== "func ", identifier, "(", decl_argument_list, ")", code_block;
FuncDeclaration * Parser::parseFuncDecl() {
    Position position = token->getPos();
    if (!this->consumeIf(FUNC_TYPE)){
        return nullptr;
    }
    auto name = (token->getValue());
    if(!this->consumeIf(IDENTIFIER_TYPE)){
        this->handleSyntaxError(position, L"Missing identifer in function declaration.");
    }
    if (!this->consumeIf(L_BRACKET_TYPE)){
        this->handleSyntaxError(position, L"Missing left bracket in function declaration.");
    }
    std::vector<Parameter *> params = parseFunctionParams();
    if (!this->consumeIf(R_BRACKET_TYPE)){
        this->handleSyntaxError(position, L"Missing right bracket in function declaration.");
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
                this->handleSyntaxError(position, L"Missing param after comma.");
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
        this->handleSyntaxError(position, L"Missing left bracket in " + statement_type + L" statement.");
    }
    Expression * expression = this->parseExpression();

    if(!expression) {
        this->handleSyntaxError(position, L"Missing expression in " + statement_type + L" statement.");
    }
    if(!this->consumeIf(R_BRACKET_TYPE)){
        this->handleSyntaxError(position, L"Missing right bracket in " + statement_type + L" statement.");
    }

    CodeBlock * block = parseCodeBlock();
    if (!block) {
        this->handleSyntaxError(position, L"Missing block after " + statement_type + L" statement.");
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
        this->handleSyntaxError(position, L"Missing identifier in for statement.");
    }
    if(!this->consumeIf(IN_TYPE)){
        this->handleSyntaxError(position, L"Missing 'in' keyword in for statement");
    }

    Position expressionPosition = this->token->getPos();
    Expression * expression;
    if(this->consumeIf(RANGE_TYPE)){
        if(!this->consumeIf(L_BRACKET_TYPE)){
            this->handleSyntaxError(expressionPosition, L"Missing left bracket in range expression.");
        }
        expressionPosition = this->token->getPos();
        Expression * leftExpression;
        if (!(leftExpression = this->parseExpression())) {
            this->handleSyntaxError(expressionPosition, L"Missing expression in range.");
        }
        if(!this->consumeIf(COMMA_TYPE)){
            this->handleSyntaxError(expressionPosition, L"Missing comma in range.");
        }
        expressionPosition = this->token->getPos();
        Expression * rightExpression;
        if (!(rightExpression = this->parseExpression())) {
            this->handleSyntaxError(expressionPosition, L"Missing expression in range.");
        }
        if(!this->consumeIf(R_BRACKET_TYPE)){
            this->handleSyntaxError(expressionPosition, L"Missing right bracket in range expression.");
        }
        CodeBlock * block = this->parseCodeBlock();
        if(!block) {
            return this->handleSyntaxError(expressionPosition, L"Missing code block after for statement.");
        }
        return new ForRangeStatement(std::get<std::wstring>(name), leftExpression, rightExpression, block, position);
    } else if (!(expression = this->parseExpression())) {
        this->handleSyntaxError(expressionPosition, L"Missing expression or range in for statement.");
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
        this->handleSyntaxError(position, L"Missing identifier in declaration statement.");
    }

    Expression * expression = nullptr;
    if(this->consumeIf(ASSIGN_TYPE)){
        if(!(expression = this->parseExpression())) {
            this->handleSyntaxError(position, L"Missing expression after assignment.");
        }
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
        if (!expression) {
            this->handleSyntaxError(position, L"Missing expression after assignement.");
        }
    }

    position = this->token->getPos();
    if(!this->consumeIf(SEMICOLON_TYPE)){
        this->handleSyntaxError(position, L"Missing semicolon.");
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
            this->handleSyntaxError(identifierPos, L"No identifier after dot.");
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
            this->handleSyntaxError(expressionPosition, L"Missing expression in list element call.");
        }
        if (!this->consumeIf(R_SQR_BRACKET_TYPE)) {
            this->handleSyntaxError(expressionPosition, L"Missing right square bracket in list element call.");
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
    if(this->consumeIf(L_BRACKET_TYPE)){
        Position expressionPos = this->token->getPos();
        if (Expression * expression = parseExpression()) {
            expressions.push_back(expression);
            while(consumeIf(COMMA_TYPE)) {
                expressionPos = this->token->getPos();
                if(expression = parseExpression()) {
                    expressions.push_back(expression);
                } else {
                    this->handleSyntaxError(expressionPos, L"Missing expression after comma in function call");
                }
            }
        }
        if(!this->consumeIf(R_BRACKET_TYPE)){
            this->handleSyntaxError(expressionPos, L"Missing right bracket closing function call");
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
        this->handleSyntaxError(position, L"Missing semicolon after return statement");
    }

    return new ReturnStatement(expression, position);
}

//expression          :== bool_and, {"||",  bool_and};
Expression * Parser::parseExpression() {
    Position position = this->token->getPos();
    Expression * leftConditionExpression;
    if (!(leftConditionExpression = this->parseExpressionAnd())) {
        return nullptr;
    }
    while (this->consumeIf(OR_TYPE)) {
        Position factorPos = this->token->getPos();
        Expression * rightConditionExpression;
        if (!(rightConditionExpression = this->parseExpressionAdd())) {
            this->handleSyntaxError(factorPos, L"No expression after ||.");
            break;
        }
        leftConditionExpression = new ExpressionOr(leftConditionExpression, rightConditionExpression, factorPos);
    }

    return leftConditionExpression;
}

//bool_and            :== bool_comp , {"&&",  bool_comp};
Expression *Parser::parseExpressionAnd() {
    Position position = this->token->getPos();
    Expression * leftConditionExpression;
    if (!(leftConditionExpression = this->parseExpressionComp())) {
        return nullptr;
    }
    while (this->consumeIf(AND_TYPE)) {
        Position factorPos = this->token->getPos();
        Expression * rightConditionExpression;
        if (!(rightConditionExpression = this->parseExpressionComp())) {
            this->handleSyntaxError(factorPos, L"No expression after &&.");
            break;
        }
        leftConditionExpression = new ExpressionAnd(leftConditionExpression, rightConditionExpression, factorPos);
    }

    return leftConditionExpression;
}

//bool_comp           :== expression_add, [comp_operator, expression_add];
Expression *Parser::parseExpressionComp() {
    Position position = this->token->getPos();
    Expression * leftConditionExpression;
    if (!(leftConditionExpression = this->parseExpressionAdd())) {
        return nullptr;
    }

    unsigned short tokenType = this->token->getTokenType();
    if (this->consumeIf(LESS_TYPE) || this->consumeIf(LEQ_TYPE) || this->consumeIf(EQ_TYPE) ||
        this->consumeIf(GREATER_TYPE) || this->consumeIf(GEQ_TYPE) || this->consumeIf(NEQ_TYPE)) {
        Position factorPos = this->token->getPos();
        Expression *rightConditionExpression;
        if (!(rightConditionExpression = this->parseExpressionAdd())) {
            this->handleSyntaxError(factorPos, L"No expression after comparison operator.");
        }
        if (tokenType == LESS_TYPE) {
            leftConditionExpression = new ExpressionCompLess(leftConditionExpression, rightConditionExpression, factorPos);
        } else if (tokenType == GREATER_TYPE) {
            leftConditionExpression = new ExpressionCompGreater(leftConditionExpression, rightConditionExpression, factorPos);
        } else if (tokenType == LEQ_TYPE) {
            leftConditionExpression = new ExpressionCompLeq(leftConditionExpression, rightConditionExpression, factorPos);
        } else if (tokenType == GEQ_TYPE) {
            leftConditionExpression = new ExpressionCompGeq(leftConditionExpression, rightConditionExpression, factorPos);
        } else if (tokenType == EQ_TYPE) {
            leftConditionExpression = new ExpressionCompEq(leftConditionExpression, rightConditionExpression, factorPos);
        } else {
            leftConditionExpression = new ExpressionCompNeq(leftConditionExpression, rightConditionExpression, factorPos);
        }

    }

    return leftConditionExpression;
}

//expression_add      :== expression_mul, {add_operator, expression_mul};
Expression *Parser::parseExpressionAdd() {
    Position position = this->token->getPos();
    Expression * leftConditionExpression;
    if (!(leftConditionExpression = this->parseExpressionMul())) {
        return nullptr;
    }

    while (true) {
        unsigned short tokenType = this->token->getTokenType();
        if (!this->consumeIf(PLUS_TYPE) && !this->consumeIf(MINUS_TYPE)) {
            break;
        }
        Position factorPos = this->token->getPos();
        Expression * rightConditionExpression;
        if (!(rightConditionExpression = this->parseExpressionMul())) {
            this->handleSyntaxError(factorPos, L"No expression after addition operator.");
            break;
        }
        if (tokenType == PLUS_TYPE) {
            leftConditionExpression = new ExpressionAdd(leftConditionExpression, rightConditionExpression, factorPos);
        } else {
            leftConditionExpression = new ExpressionSub(leftConditionExpression, rightConditionExpression, factorPos);
        }
    }

    return leftConditionExpression;
}

//expression_mul      :== expression_is, {mul_operator, expression_is};
Expression *Parser::parseExpressionMul() {
    Position position = this->token->getPos();
    Expression * leftConditionExpression;
    if (!(leftConditionExpression = this->parseExpressionIs())) {
        return nullptr;
    }

    while (true) {
        unsigned short tokenType = this->token->getTokenType();
        if (!this->consumeIf(MULTIPLY_TYPE) && !this->consumeIf(DIVIDE_TYPE)) {
            break;
        }
        Position factorPos = this->token->getPos();
        Expression * rightConditionExpression;
        if (!(rightConditionExpression = this->parseExpressionIs())) {
            this->handleSyntaxError(factorPos, L"No expression after multiplication operator.");
            break;
        }
        if (tokenType == MULTIPLY_TYPE) {
            leftConditionExpression = new ExpressionMul(leftConditionExpression, rightConditionExpression, factorPos);
        } else {
            leftConditionExpression = new ExpressionDiv(leftConditionExpression, rightConditionExpression, factorPos);
        }
    }

    return leftConditionExpression;
}

//expression_is       :== expression_to, [" is ",  type];
Expression *Parser::parseExpressionIs() {
    Position position = this->token->getPos();
    Expression * leftConditionExpression;
    if (!(leftConditionExpression = this->parseExpressionTo())) {
        return nullptr;
    }

    if (this->consumeIf(IS_TYPE)) {
        Position factorPos = this->token->getPos();
        Expression *rightConditionExpression;
        if(this->consumeIf(STRING_KEYWORD_TYPE)){
            leftConditionExpression = new ExpressionIs(leftConditionExpression, STRING_VARIABLE, factorPos);
        } else if(this->consumeIf(INT_KEYWORD_TYPE)){
            leftConditionExpression = new ExpressionIs(leftConditionExpression, INT_VARIABLE, factorPos);
        } else if(this->consumeIf(DOUBLE_KEYWORD_TYPE)) {
            leftConditionExpression = new ExpressionIs(leftConditionExpression, DOUBLE_VARIABLE, factorPos);
        } else if(this->consumeIf(BOOL_KEYWORD_TYPE)){
            leftConditionExpression = new ExpressionIs(leftConditionExpression, BOOL_VARIABLE, factorPos);
        } else if(this->consumeIf(NONE_KEYWORD_TYPE)){
            leftConditionExpression = new ExpressionIs(leftConditionExpression, NONE_VARIABLE, factorPos);
        } else if(this->consumeIf(POINT_KEYWORD_TYPE)) {
            leftConditionExpression = new ExpressionIs(leftConditionExpression, POINT_VARIABLE, factorPos);
        } else if(this->consumeIf(FIGURE_TYPE)) {
            leftConditionExpression = new ExpressionIs(leftConditionExpression, FIGURE_VARIABLE, factorPos);
        } else {
            this->handleSyntaxError(factorPos, L"No expression after is keyword.");
        }
    }

    return leftConditionExpression;
}

//expression_to       :== nagated_value, [" to ",  type];
Expression *Parser::parseExpressionTo() {
    Position position = this->token->getPos();
    Expression * leftConditionExpression;
    if (!(leftConditionExpression = this->parseExpressionNeg())) {
        return nullptr;
    }

    if (this->consumeIf(TO_TYPE)) {
        Position factorPos = this->token->getPos();
        Expression *rightConditionExpression;
        if(this->consumeIf(STRING_KEYWORD_TYPE)){
            leftConditionExpression = new ExpressionTo(leftConditionExpression, STRING_VARIABLE, factorPos);
        } else if(this->consumeIf(INT_KEYWORD_TYPE)){
            leftConditionExpression = new ExpressionTo(leftConditionExpression, INT_VARIABLE, factorPos);
        } else if(this->consumeIf(DOUBLE_KEYWORD_TYPE)) {
            leftConditionExpression = new ExpressionTo(leftConditionExpression, DOUBLE_VARIABLE, factorPos);
        } else if(this->consumeIf(BOOL_KEYWORD_TYPE)){
            leftConditionExpression = new ExpressionTo(leftConditionExpression, BOOL_VARIABLE, factorPos);
        } else if(this->consumeIf(NONE_KEYWORD_TYPE)){
            leftConditionExpression = new ExpressionTo(leftConditionExpression, NONE_VARIABLE, factorPos);
        } else if(this->consumeIf(POINT_KEYWORD_TYPE)) {
            leftConditionExpression = new ExpressionTo(leftConditionExpression, POINT_VARIABLE, factorPos);
        } else if(this->consumeIf(FIGURE_TYPE)) {
            leftConditionExpression = new ExpressionTo(leftConditionExpression, FIGURE_VARIABLE, factorPos);
        } else {
            this->handleSyntaxError(factorPos, L"No expression after is keyword.");
        }
    }

    return leftConditionExpression;
}

//negated_value       :== [negation_operator], accessed_value;
Expression *Parser::parseExpressionNeg() {
    Position position = this->token->getPos();
    Expression * expression;
    unsigned short tokenType = this->token->getTokenType();
    bool negated = false;
    if (this->consumeIf(NEGATION_TYPE) || this->consumeIf(MINUS_TYPE)) {
        negated = true;
    }

    if (!(expression = this->parseAccessedValue())) {
        if (negated) {
            this->handleSyntaxError(position, L"No expression after negation operator.");
        }
        return nullptr;
    }

    if (negated) {
        if (tokenType == NEGATION_TYPE) {
            expression = new ExpressionNeg(expression, position);
        } else {
            expression = new ExpressionNegMinus(expression, position);
        }
    }

    return expression;
}

//accessed_value        :== value
//                        | list
//                        | point
//                        | identifier_stmnt
//                        | "(", expression, ")";
Expression *Parser::parseAccessedValue() {
    Expression * expression;
    if (expression = this->parseExpressionValueList()) {
    } else if (expression = this->parseExpressionValueLiteral()) {
    } else if (expression = static_cast<IdentifierDotStatement *>(this->parseIdentifierDotStatement())){
    } else {
        //"(", expression, ")";
        if(!consumeIf(L_BRACKET_TYPE)) {
            return nullptr;
        }
        Position insideExpressionPosition = this->token->getPos();
        Expression * insideExpression = parseExpression();
        if (!insideExpression) {
            this->handleSyntaxError(insideExpressionPosition, L"No expression inside brackets");
        }
        //point               :== "(", expression, ",", expression, ")";
        if(this->consumeIf(COMMA_TYPE)) {
            Expression * xCoordExpression = insideExpression;
            Expression * yCoordExpression;
            Position yCoordExprPos = this->token->getPos();
            if(yCoordExpression = parseExpression()) {
            } else {
                this->handleSyntaxError(yCoordExprPos, L"Missing expression after comma in point value.");
            }
            if(!consumeIf(R_BRACKET_TYPE)) {
                this->handleSyntaxError(insideExpressionPosition, L"No right bracket");
            }
            expression = new ExpressionValuePoint(xCoordExpression, yCoordExpression, insideExpressionPosition);
        } else {
            if(!consumeIf(R_BRACKET_TYPE)) {
                this->handleSyntaxError(insideExpressionPosition, L"No right bracket");
            }
            expression = new ExpressionValueBrackets(insideExpression, insideExpressionPosition);
        }

    }
    return expression;
}

//list                :== "[", expression, {", ", expression} "]";
Expression *Parser::parseExpressionValueList() {
    Position position = this->token->getPos();
    if(!consumeIf(L_SQR_BRACKET_TYPE)) {
        return nullptr;
    }
    std::vector<Expression *> expressions;
    Position expressionPos = this->token->getPos();
    if (Expression * expression = parseExpression()) {
        expressions.push_back(expression);
        while(consumeIf(COMMA_TYPE)) {
            expressionPos = this->token->getPos();
            if(expression = parseExpression()) {
                expressions.push_back(expression);
            } else {
                this->handleSyntaxError(expressionPos, L"Missing expression after comma in list");
            }
        }
    }
    if(!this->consumeIf(R_SQR_BRACKET_TYPE)){
        this->handleSyntaxError(expressionPos, L"Missing right bracket closing list");
    }
    return new ExpressionValueList(expressions, position);
}

// value                :== int_val
//                        | bool_val
//                        | double_val
//                        | string_val
//                        | "none";
Expression *Parser::parseExpressionValueLiteral() {
    //get value i type
    auto value = this->token->getValue();
    auto position = this->token->getPos();
    if (this->consumeIf(INTEGER_TYPE)) {
        return new ExpressionValueLiteral(std::get<int>(value), position);
    }
    if (this->consumeIf(DOUBLE_TYPE)){
        return new ExpressionValueLiteral(std::get<double>(value), position);
    }
    if (this->consumeIf(NONE_KEYWORD_TYPE)){
        return new ExpressionValueLiteral(std::monostate(), position);
    }
    if(this->consumeIf(TRUE_TYPE)){
        return new ExpressionValueLiteral(true, position);
    }
    if (this->consumeIf(FALSE_TYPE)){
        return new ExpressionValueLiteral(false, position);
    }
    if (this->consumeIf(STRING_TYPE)){
        return new ExpressionValueLiteral(std::get<std::wstring>(value), position);
    }
    return nullptr;
}
