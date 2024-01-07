////
//// Created by mpkow on 15.05.2023.
////

#include "Parser.h"

//program             :== {func_declaration | figure_declaration};
Program * Parser::parse() {//unique_ptr optionale i varianty
    //TODO statement to variant typów statementów
    std::unordered_map<std::wstring, FuncDeclaration *> functions = {};
    std::unordered_map<std::wstring, FigureDeclaration *> figures = {};
    token = lexer->nextToken();
    Position pos = token->getPos();
    bool foundFunc = true;
    bool foundFigure = true;
    while((foundFunc || foundFigure) && !this->blocking_syntax_error){
        foundFunc = false;
        foundFigure = false;
        if (auto funcDecl = this->parseFuncDecl()){
            auto fName = funcDecl->getName();
            if(functions.find(fName) == functions.end()){
                functions[fName] = funcDecl;//* przy opt
            } else {
                this->handleSemanticError(pos, L"Redeclaration of function " + fName);
            }
            foundFunc = true;
        } else if (auto figureDecl = this->parseFigureDecl()){
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

std::variant<int, double, std::wstring> Parser::mustBe(unsigned int token_type, std::wstring message) {
    auto value = this->token->getValue();
    auto position = this->token->getPos();
    while(token->getTokenType() != token_type) {
        this->handleSyntaxError(position, message);
    }
    while(token->getTokenType() == COMMENT_TYPE) {
        token = lexer->nextToken();
    }
    token = lexer->nextToken();

    return value;
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

// figure_declaration  :== "figure ", leftExpression, "{", point_list, "}";
// point_list          :== point_declaration, {",", point_declaration}, "," "color", ":",
FigureDeclaration * Parser::parseFigureDecl() {
    Position position = token->getPos();
    if (!this->consumeIf(FIGURE_TYPE)){
        return nullptr;
    }
    auto name = this->mustBe(IDENTIFIER_TYPE, L"Missing identifer in figure declaration.");
    this->mustBe(L_CURL_BRACKET_TYPE, L"Missing left bracket in figure declaration.");
    std::vector<Parameter *> params = parseFigureParams();
    this->mustBe(R_CURL_BRACKET_TYPE, L"Missing right bracket in figure declaration.");

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
                this->errorHandler->onSyntaxError(position, L"Missing param after comma.");
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

//point_declaration   :== leftExpression, ":", expression;
Parameter * Parser::parseFigureParam() {
    Position position = this->token->getPos();
    auto name = token->getValue();
    if(!this->consumeIf(IDENTIFIER_TYPE)){
        return nullptr;
    }

    this->mustBe(COLON_TYPE, L"Missing colon in figure param.");


    Expression * expression;
    if (!(expression = this->parseExpression())) {
        this->handleSemanticError(position, L"Missing expression in figure param");
    }
    return new FigureParameter(std::get<std::wstring>(name), expression, position);
}

//func_declaration    :== "func ", leftExpression, "(", decl_argument_list, ")", code_block;
FuncDeclaration * Parser::parseFuncDecl() {
    Position position = token->getPos();
    if (!this->consumeIf(FUNC_TYPE)){
        return nullptr;
    }
    auto name =  this->mustBe(IDENTIFIER_TYPE, L"Missing identifier in function declaration.");

    this->mustBe(L_BRACKET_TYPE, L"Missing left bracket in function declaration.");
    std::vector<Parameter *> params = parseFunctionParams();
    this->mustBe(R_BRACKET_TYPE, L"Missing right bracket in function declaration.");
    CodeBlock * block = parseCodeBlock();
    if (!block) {
        this->handleSyntaxError(position, L"Missing block after function declaration.");
    }
    return new FuncDeclaration(std::get<std::wstring>(name), params, block, position);
}

//decl_argument_list  :== [leftExpression, {", ", leftExpression}];
std::vector<Parameter *> Parser::parseFunctionParams() {
    std::vector<Parameter *> params;
    std::unordered_map<std::wstring, bool> paramsMap;//TODO można po wektorze wyszukać
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
    Position position = token->getPos();
    auto name = token->getValue();
    if(this->consumeIf(IDENTIFIER_TYPE)){
        return new Parameter(std::get<std::wstring>(name), position);
    }
    return nullptr;
}

//code_block          :== "{", {statement}, "}";
CodeBlock * Parser::parseCodeBlock() {
    Position position = this->token->getPos();
    if (!this->consumeIf(L_CURL_BRACKET_TYPE)){
        return nullptr;
    }
    std::vector<Statement*> statements;//TODO tu zrobić variant
    Statement * statement;
    while (statement = parseStatement()){
        statements.push_back(statement);
    }
    this->mustBe(R_CURL_BRACKET_TYPE, L"Missing right bracket in code block.");

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
        (statement = parseIdentifierAssignmentStatement()) ||
        (statement = parseReturnStatement()))
        return statement;
    return nullptr;
}


ConditionAndBlock * Parser::parseConditionAndBlock(const std::wstring & statement_type, token_type tokenType) {
    Position position = this->token->getPos();
    if(!this->consumeIf(tokenType)){
        return nullptr;
    }
    this->mustBe(L_BRACKET_TYPE, L"Missing left bracket in " + statement_type + L" statement.");

    Expression * expression = this->parseExpression();

    if(!expression) {
        this->handleSyntaxError(position, L"Missing expression in " + statement_type + L" statement.");
    }
    this->mustBe(R_BRACKET_TYPE, L"Missing right bracket in " + statement_type + L" statement.");


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
    CodeBlock * elseCodeBlock = nullptr;
    Position elsePosition = this->token->getPos();
    if (this->consumeIf(ELSE_TYPE)) {
        elseCodeBlock = parseCodeBlock();
        if (!elseCodeBlock) {
            this->handleSyntaxError(elsePosition, L"Missing block after else statement.");
        }
    }
    return new IfStatement(ifConditionAndBlock, elsifConditionsAndBlocks, elseCodeBlock, position);
}

//for_stmnt           :== "for", leftExpression, "in", expression_or_range, code_block;
Statement * Parser::parseForStatement() {
    Position position = this->token->getPos();
    if(!this->consumeIf(FOR_TYPE)){
        return nullptr;
    }
    auto name = this->mustBe(IDENTIFIER_TYPE, L"Missing identifier in for statement");

    this->mustBe(IN_TYPE, L"Missing 'in' keyword in for statement");


    Position expressionPosition = this->token->getPos();
    Expression * expression;
    if(this->consumeIf(RANGE_TYPE)){ // przenieść do osobnej funkcji
        this->mustBe(L_BRACKET_TYPE, L"Missing left bracket in range expression.");

        expressionPosition = this->token->getPos();
        Expression * leftExpression;
        if (!(leftExpression = this->parseExpression())) {
            this->handleSyntaxError(expressionPosition, L"Missing expression in range.");
        }
        this->mustBe(COMMA_TYPE, L"Missing comma in range.");

        expressionPosition = this->token->getPos();
        Expression * rightExpression;
        if (!(rightExpression = this->parseExpression())) {
            this->handleSyntaxError(expressionPosition, L"Missing expression in range.");
        }
        this->mustBe(R_BRACKET_TYPE, L"Missing right bracket in range expression.");

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

// declaration         :== "vv ", leftExpression, ["=", expression], ";";
Statement * Parser::parseDeclarationStatement() {
    Position position = this->token->getPos();
    if(!this->consumeIf(VV_TYPE)){
        return nullptr;
    }
    auto name = this->mustBe(IDENTIFIER_TYPE, L"Missing leftExpression in declaration statement.");

    Expression * expression = nullptr;
    if(this->consumeIf(ASSIGN_TYPE)){
        if(!(expression = this->parseExpression())) {
            this->handleSyntaxError(position, L"Missing expression after assignment.");
        }
    }

    this->mustBe(SEMICOLON_TYPE, L"Missing semicolon on end of declaration.");

    return new DeclarationStatement(std::get<std::wstring>(name), expression, position); // osobny byt assign tak jak niżej
}


//identifier_stmnt, ["=", expression], ";"
Statement * Parser::parseIdentifierAssignmentStatement() {
    Position position = this->token->getPos();

    Statement * identifierStatement;
    if (!(identifierStatement = this->parseIdentifierExpressionStatement())) {
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

    this->mustBe(SEMICOLON_TYPE, L"Missing semicolon.");

    if(expression == nullptr) {
        return identifierStatement;
    }

    return new IdentifierStatementAssign(identifierStatement, expression, position);
}

Statement * Parser::parseIdentifierExpressionStatement() {
    Position position = this->token->getPos();

    Expression * identifierExpression;
    if (!(identifierExpression = this->parseObjectAccessExpression())) {
        return nullptr;
    }

    return new IdentifierExpressionStatement(identifierExpression, position);
}

//identifier_stmnt    :== part, {".", part};
Expression * Parser::parseObjectAccessExpression() {
    Position position = this->token->getPos();
    Expression * leftIdentifierListCallExpression;
    if (!(leftIdentifierListCallExpression = this->parseIdentifierListIndexExpression())) {
        return nullptr;
    }
    while (this->consumeIf(DOT_TYPE)) {
        Position identifierPos = this->token->getPos();
        Expression * rightIdentifierListCallExpression;
        if (!(rightIdentifierListCallExpression = this->parseIdentifierListIndexExpression())) {
            this->handleSyntaxError(identifierPos, L"No identifier after dot.");
            break;
        }
        leftIdentifierListCallExpression = new ObjectAccessExpression(leftIdentifierListCallExpression, rightIdentifierListCallExpression, identifierPos);
    }

    return leftIdentifierListCallExpression;
}

//part                :== part_call, {"[", expression, "]"};
Expression * Parser::parseIdentifierListIndexExpression() {
    Position position = this->token->getPos();
    Expression * leftExpression;
    if (!(leftExpression = this->parseIdentifierFunctionCallExpression())) {
        return nullptr;
    }
    while(this->consumeIf(L_SQR_BRACKET_TYPE)) {
        Position expressionPosition = this->token->getPos();
        if(Expression * expression = this->parseExpression()) {
            leftExpression = new IdentifierListIndexExpression(leftExpression, expression, position);
        } else {
            this->handleSyntaxError(expressionPosition, L"Missing expression in list element call.");
        }
        if (!this->consumeIf(R_SQR_BRACKET_TYPE)) {
            this->handleSyntaxError(expressionPosition, L"Missing right square bracket in list element call.");
            break;
        }
    }

    return leftExpression;
}

//part_call           :== leftExpression, ["(", argument_list, ")"];
Expression * Parser::parseIdentifierFunctionCallExpression() {
    Position position = this->token->getPos();
    bool isFunctionCall = false;

    Expression * identifierExpression = this->parseIdentifierExpression();
    if(!identifierExpression) {
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
        this->mustBe(R_BRACKET_TYPE, L"Missing right bracket closing function call");
        isFunctionCall = true;
    }

    if (!isFunctionCall) {
        return identifierExpression;
    }

    return new IdentifierFunctionCallExpression(identifierExpression, expressions, position);
}

Expression * Parser::parseIdentifierExpression() {
    Position position = this->token->getPos();
    auto name = this->token->getValue();
    if(!this->consumeIf(IDENTIFIER_TYPE)){
        return nullptr;
    }
    return new IdentifierExpression(std::get<std::wstring>(name), position);
}

//return              :== "return ", [expression], ";"
Statement * Parser::parseReturnStatement() {
    Position position = this->token->getPos();
    if(!this->consumeIf(RETURN_TYPE)){
        return nullptr;
    }

    Expression * expression = this->parseExpression();

    this->mustBe(SEMICOLON_TYPE, L"Missing semicolon after return statement");

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
        if (!(rightConditionExpression = this->parseExpressionAnd())) {
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

//bool_comp           :== expression_is, [comp_operator, expression_is];
Expression *Parser::parseExpressionComp() {
    Position position = this->token->getPos();
    Expression * leftConditionExpression;
    if (!(leftConditionExpression = this->parseExpressionIs())) {
        return nullptr;
    }

    unsigned short tokenType = this->token->getTokenType();
    if (this->consumeIf(LESS_TYPE) || this->consumeIf(LEQ_TYPE) || this->consumeIf(EQ_TYPE) ||
        this->consumeIf(GREATER_TYPE) || this->consumeIf(GEQ_TYPE) || this->consumeIf(NEQ_TYPE)) {
        Position factorPos = this->token->getPos();
        Expression *rightConditionExpression;
        if (!(rightConditionExpression = this->parseExpressionIs())) {
            this->handleSyntaxError(factorPos, L"No expression after comparison operator.");
        }
        leftConditionExpression = lhs_rhs_expression_constructor_map.at(tokenType)(leftConditionExpression, rightConditionExpression, factorPos);
    }

    return leftConditionExpression;
}


//expression_is       :== expression_add, [" is ",  type];
Expression *Parser::parseExpressionIs() {
    Position position = this->token->getPos();
    Expression * leftConditionExpression;
    if (!(leftConditionExpression = this->parseExpressionAdd())) {
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
            this->handleSyntaxError(factorPos, L"No type after is keyword.");
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

    unsigned short tokenType = this->token->getTokenType();
    while (this->consumeIf(PLUS_TYPE) || this->consumeIf(MINUS_TYPE)) {
        Position factorPos = this->token->getPos();
        Expression * rightConditionExpression;
        if (!(rightConditionExpression = this->parseExpressionAnd())) {
            this->handleSyntaxError(factorPos, L"No expression after addition operator.");
            break;
        }
        leftConditionExpression = lhs_rhs_expression_constructor_map.at(tokenType)(leftConditionExpression, rightConditionExpression, factorPos);
        tokenType = this->token->getTokenType();
    }

    return leftConditionExpression;
}

//expression_mul      :== expression_to, {mul_operator, expression_to};
Expression *Parser::parseExpressionMul() {
    Position position = this->token->getPos();
    Expression * leftConditionExpression;
    if (!(leftConditionExpression = this->parseExpressionTo())) {
        return nullptr;
    }

    unsigned short tokenType = this->token->getTokenType();
    while (this->consumeIf(MULTIPLY_TYPE) || this->consumeIf(DIVIDE_TYPE)) {
        Position factorPos = this->token->getPos();
        Expression * rightConditionExpression;
        if (!(rightConditionExpression = this->parseExpressionAnd())) {
            this->handleSyntaxError(factorPos, L"No expression after multiplication operator.");
            break;
        }
        leftConditionExpression = lhs_rhs_expression_constructor_map.at(tokenType)(leftConditionExpression, rightConditionExpression, factorPos);
        tokenType = this->token->getTokenType();
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
    } else if (expression = this->parseObjectAccessExpression()){
    } else {//osobna metoda
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
            this->mustBe(R_BRACKET_TYPE, L"No right bracket in point");

            expression = new ExpressionValuePoint(xCoordExpression, yCoordExpression, insideExpressionPosition);
        } else {
            this->mustBe(R_BRACKET_TYPE, L"No right bracket.");
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
    this->mustBe(R_SQR_BRACKET_TYPE, L"Missing right bracket closing list");
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
