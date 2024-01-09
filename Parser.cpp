////
//// Created by mpkow on 15.05.2023.
////

#include "Parser.h"

//program             :== {func_declaration | figure_declaration};
std::unique_ptr<Program> Parser::parse() {//TODO unique_ptr optionale i varianty
    //TODO statement to variant typów statementów
    std::unordered_map<std::wstring, std::unique_ptr<FuncDeclaration>> functions = {};
    std::unordered_map<std::wstring, std::unique_ptr<FigureDeclaration>> figures = {};
    token = lexer->nextToken();
    Position pos = token->getPos();
    bool foundFunc = true;
    bool foundFigure = true;
    while((foundFunc || foundFigure) && !this->blocking_syntax_error){
        foundFunc = false;
        foundFigure = false;
        if (auto funcDecl = std::move(this->parseFuncDecl())){
            auto fName = funcDecl->name;
            if(functions.find(fName) == functions.end()){
                functions[fName] = std::move(funcDecl);//TODO * przy opt
            } else {
                this->handleSemanticError(pos, L"Redeclaration of function " + fName);
            }
            foundFunc = true;
        } else if (auto figureDecl = std::move(this->parseFigureDecl())){
            std::wstring fName = figureDecl->name;
            if(figures.find(fName) == figures.end()){
                figures[fName] = std::move(figureDecl);
            } else {
                errorHandler->onSemanticError(pos, L"Redeclaration of figure " + fName);
            }
            foundFigure = true;
        }
    }
    return std::make_unique<Program>(std::move(functions), std::move(figures));
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
std::unique_ptr<FigureDeclaration> Parser::parseFigureDecl() {
    Position position = token->getPos();
    if (!this->consumeIf(FIGURE_TYPE)){
        return nullptr;
    }
    auto name = this->mustBe(IDENTIFIER_TYPE, L"Missing identifer in figure declaration.");
    this->mustBe(L_CURL_BRACKET_TYPE, L"Missing left bracket in figure declaration.");
    std::vector<std::unique_ptr<Parameter>> params = std::move(parseFigureParams());
    this->mustBe(R_CURL_BRACKET_TYPE, L"Missing right bracket in figure declaration.");

    return std::make_unique<FigureDeclaration>(std::get<std::wstring>(name), std::move(params), position);
}

// point_list          :== point_declaration, {",", point_declaration}
std::vector<std::unique_ptr<Parameter>> Parser::parseFigureParams() {
    std::vector<std::unique_ptr<Parameter>> params;
    Position position = this->token->getPos();
    std::unique_ptr<Parameter> param = std::move(parseFigureParam());
    if (param) {
        params.push_back(std::move(param));
        while (this->consumeIf(COMMA_TYPE)){
            Position position = this->token->getPos();
            param = std::move(parseFigureParam());
            if(!param){
                this->errorHandler->onSyntaxError(position, L"Missing param after comma.");
                return params;
            } else if (std::find_if(params.begin(), params.end(), [&param](std::unique_ptr<Parameter> & p) {return p.get()->name == param->name;}) != params.end()) {
                this->handleSemanticError(position, L"Duplicate param " + param->getName());
            } else {
                params.push_back(std::move(param));
            }
        }
    }

    if (params.empty()) {
        this->handleSemanticError(position, L"No params in figure declaration.");
    }

    return params;
}

//point_declaration   :== leftExpression, ":", expression;
std::unique_ptr<Parameter> Parser::parseFigureParam() {
    Position position = this->token->getPos();
    auto name = token->getValue();
    if(!this->consumeIf(IDENTIFIER_TYPE)){
        return nullptr;
    }

    this->mustBe(COLON_TYPE, L"Missing colon in figure param.");


    std::unique_ptr<Expression> expression;
    if (!(expression = std::move(this->parseExpression()))) {
        this->handleSemanticError(position, L"Missing expression in figure param");
    }
    return std::make_unique<FigureParameter>(std::get<std::wstring>(name), std::move(expression), position);
}

//func_declaration    :== "func ", leftExpression, "(", decl_argument_list, ")", code_block;
std::unique_ptr<FuncDeclaration> Parser::parseFuncDecl() {
    Position position = token->getPos();
    if (!this->consumeIf(FUNC_TYPE)){
        return nullptr;
    }
    auto name =  this->mustBe(IDENTIFIER_TYPE, L"Missing identifier in function declaration.");

    this->mustBe(L_BRACKET_TYPE, L"Missing left bracket in function declaration.");
    std::vector<std::unique_ptr<Parameter>> params = std::move(parseFunctionParams());
    this->mustBe(R_BRACKET_TYPE, L"Missing right bracket in function declaration.");
    std::unique_ptr<CodeBlock> block = std::move(parseCodeBlock());
    if (!block) {
        this->handleSyntaxError(position, L"Missing block after function declaration.");
    }
    return std::make_unique<FuncDeclaration>(std::get<std::wstring>(name), std::move(params), std::move(block), position);
}

//decl_argument_list  :== [leftExpression, {", ", leftExpression}];
std::vector<std::unique_ptr<Parameter>> Parser::parseFunctionParams() {
    std::vector<std::unique_ptr<Parameter>> params;
    std::unique_ptr<Parameter> param = std::move(parseParam());
    if (param) {
        params.push_back(std::move(param));

        while (this->consumeIf(COMMA_TYPE)){
            Position position = this->token->getPos();
            param = std::move(parseParam());
            if(!param){
                this->handleSyntaxError(position, L"Missing param after comma.");
                return params;
            } else if (std::find_if(params.begin(), params.end(), [&param](std::unique_ptr<Parameter> & p) {return p.get()->name == param->name;}) != params.end()) {
                this->handleSemanticError(position, L"Duplicate param " + param->getName());
            } else {
                params.push_back(std::move(param));
            }
        }
    }

    return params;
}

std::unique_ptr<Parameter> Parser::parseParam() {
    Position position = token->getPos();
    auto name = token->getValue();
    if(this->consumeIf(IDENTIFIER_TYPE)){
        return std::make_unique<Parameter>(std::get<std::wstring>(name), position);
    }
    return nullptr;
}

//code_block          :== "{", {statement}, "}";
std::unique_ptr<CodeBlock> Parser::parseCodeBlock() {
    Position position = this->token->getPos();
    if (!this->consumeIf(L_CURL_BRACKET_TYPE)){
        return nullptr;
    }
    std::vector<std::unique_ptr<Statement>> statements;//TODO tu zrobić variant
    std::unique_ptr<Statement> statement;
    while (statement = std::move(parseStatement())){
        statements.push_back(std::move(statement));
    }
    this->mustBe(R_CURL_BRACKET_TYPE, L"Missing right bracket in code block.");

    return std::make_unique<CodeBlock>(std::move(statements), position);
}

//statement           :== while_stmnt
//                        | for_stmnt
//                        | if_stmnt
//                        | declaration
//                        | identifier_stmnt, ["=", expression], ";"
//                        | return;
std::unique_ptr<Statement> Parser::parseStatement() {
    std::unique_ptr<Statement> statement;
    if((statement = std::move(parseWhileStatement())) ||
        (statement = std::move(parseIfStatement())) ||
        (statement = std::move(parseForStatement())) ||
        (statement = std::move(parseDeclarationStatement())) ||
        (statement = std::move(parseIdentifierAssignmentStatement())) ||
        (statement = std::move(parseReturnStatement())))
        return statement;
    return nullptr;
}


std::unique_ptr<ConditionAndBlock> Parser::parseConditionAndBlock(const std::wstring & statement_type, token_type tokenType) {
    Position position = this->token->getPos();
    if(!this->consumeIf(tokenType)){
        return nullptr;
    }
    this->mustBe(L_BRACKET_TYPE, L"Missing left bracket in " + statement_type + L" statement.");

    std::unique_ptr<Expression> expression = std::move(this->parseExpression());

    if(!expression) {
        this->handleSyntaxError(position, L"Missing expression in " + statement_type + L" statement.");
    }
    this->mustBe(R_BRACKET_TYPE, L"Missing right bracket in " + statement_type + L" statement.");


    std::unique_ptr<CodeBlock> block = std::move(parseCodeBlock());
    if (!block) {
        this->handleSyntaxError(position, L"Missing block after " + statement_type + L" statement.");
    }
    return std::make_unique<ConditionAndBlock>(std::move(expression), std::move(block));
}

//while_stmnt         :== "while", "(",  std::move(expression), ")", code_block;
std::unique_ptr<Statement> Parser::parseWhileStatement() {
    Position position = token->getPos();
    std::unique_ptr<ConditionAndBlock> conditionAndBlock = std::move(this->parseConditionAndBlock(L"while", WHILE_TYPE));
    if (!conditionAndBlock) {
        return nullptr;
    }
    return std::make_unique<WhileStatement>(std::move(conditionAndBlock), position);
}

//if_stmnt            :== "if", "(",  std::move(expression), ")", code_std::move(block), {"elsif", "(",  std::move(expression), ")", code_block }, ["else", code_block];
std::unique_ptr<Statement> Parser::parseIfStatement() {
    Position position = token->getPos();
    std::unique_ptr<ConditionAndBlock> ifConditionAndBlock = std::move(this->parseConditionAndBlock(L"if", IF_TYPE));
    if (!ifConditionAndBlock) {
        return nullptr;
    }
    std::vector<std::unique_ptr<ConditionAndBlock>> elsifConditionsAndBlocks;
    while(std::unique_ptr<ConditionAndBlock> elsifConditionAndBlock = std::move(this->parseConditionAndBlock(L"elsif", ELSIF_TYPE))){
        elsifConditionsAndBlocks.push_back(std::move(elsifConditionAndBlock));
    }
    std::unique_ptr<CodeBlock> elseCodeBlock = nullptr;
    Position elsePosition = this->token->getPos();
    if (this->consumeIf(ELSE_TYPE)) {
        elseCodeBlock = std::move(parseCodeBlock());
        if (!elseCodeBlock) {
            this->handleSyntaxError(elsePosition, L"Missing block after else statement.");
        }
    }
    return std::make_unique<IfStatement>(std::move(ifConditionAndBlock), std::move(elsifConditionsAndBlocks), std::move(elseCodeBlock), position);
}

//for_stmnt           :== "for", leftExpression, "in", expression_or_range, code_block;
std::unique_ptr<Statement> Parser::parseForStatement() {
    Position position = this->token->getPos();
    if(!this->consumeIf(FOR_TYPE)){
        return nullptr;
    }
    auto name = this->mustBe(IDENTIFIER_TYPE, L"Missing identifier in for statement");

    this->mustBe(IN_TYPE, L"Missing 'in' keyword in for statement");


    Position expressionPosition = this->token->getPos();
    std::unique_ptr<Expression> expression;
    if(this->consumeIf(RANGE_TYPE)){ //TODO przenieść do osobnej funkcji
        this->mustBe(L_BRACKET_TYPE, L"Missing left bracket in range expression.");

        expressionPosition = this->token->getPos();
        std::unique_ptr<Expression> leftExpression;
        if (!(leftExpression = std::move(this->parseExpression()))) {
            this->handleSyntaxError(expressionPosition, L"Missing expression in range.");
        }
        this->mustBe(COMMA_TYPE, L"Missing comma in range.");

        expressionPosition = this->token->getPos();
        std::unique_ptr<Expression> rightExpression;
        if (!(rightExpression = std::move(this->parseExpression()))) {
            this->handleSyntaxError(expressionPosition, L"Missing expression in range.");
        }
        this->mustBe(R_BRACKET_TYPE, L"Missing right bracket in range expression.");

        std::unique_ptr<CodeBlock> block = std::move(this->parseCodeBlock());
        if(!block) {
            return this->handleSyntaxError(expressionPosition, L"Missing code block after for statement.");
        }
        return std::make_unique<ForRangeStatement>(std::get<std::wstring>(name), std::move(leftExpression), std::move(rightExpression), std::move(block), position);
    } else if (!(expression = std::move(this->parseExpression()))) {
        this->handleSyntaxError(expressionPosition, L"Missing expression or range in for statement.");
    }
    std::unique_ptr<CodeBlock> block = std::move(this->parseCodeBlock());
    if(!block) {
        return this->handleSyntaxError(expressionPosition, L"Missing code block after for statement.");
    }
    return std::make_unique<ForStatement>(std::get<std::wstring>(name), std::move(expression), std::move(block), position);
}

// declaration         :== "vv ", leftExpression, ["=", expression], ";";
std::unique_ptr<Statement> Parser::parseDeclarationStatement() {
    Position position = this->token->getPos();
    if(!this->consumeIf(VV_TYPE)){
        return nullptr;
    }
    auto name = this->mustBe(IDENTIFIER_TYPE, L"Missing leftExpression in declaration statement.");

    std::unique_ptr<Expression> expression = nullptr;
    if(this->consumeIf(ASSIGN_TYPE)){
        if(!(expression = std::move(this->parseExpression()))) {
            this->handleSyntaxError(position, L"Missing expression after assignment.");
        }
    }

    this->mustBe(SEMICOLON_TYPE, L"Missing semicolon on end of declaration.");

    return std::make_unique<DeclarationStatement>(std::get<std::wstring>(name), std::move(expression), position); // osobny byt assign tak jak niżej
}


//identifier_stmnt, ["=", expression], ";"
std::unique_ptr<Statement> Parser::parseIdentifierAssignmentStatement() {
    Position position = this->token->getPos();

    std::unique_ptr<Statement> identifierStatement;
    if (!(identifierStatement = std::move(this->parseIdentifierExpressionStatement()))) {
        return nullptr;
    }

    std::unique_ptr<Expression> expression = nullptr;
    if(this->consumeIf(ASSIGN_TYPE)){
        expression = std::move(this->parseExpression());
        if (!expression) {
            this->handleSyntaxError(position, L"Missing expression after assignement.");
        }
    }

    position = this->token->getPos();

    this->mustBe(SEMICOLON_TYPE, L"Missing semicolon.");

    if(expression == nullptr) {
        return identifierStatement;
    }

    return std::make_unique<IdentifierStatementAssign>(std::move(identifierStatement), std::move(expression), position);
}

std::unique_ptr<Statement> Parser::parseIdentifierExpressionStatement() {
    Position position = this->token->getPos();

    std::unique_ptr<Expression> identifierExpression;
    if (!(identifierExpression = std::move(this->parseObjectAccessExpression()))) {
        return nullptr;
    }

    return std::make_unique<IdentifierExpressionStatement>(std::move(identifierExpression), position);
}

//identifier_stmnt    :== part, {".", part};
std::unique_ptr<Expression> Parser::parseObjectAccessExpression() {
    Position position = this->token->getPos();
    std::unique_ptr<Expression> leftIdentifierListCallExpression;
    if (!(leftIdentifierListCallExpression = std::move(this->parseIdentifierListIndexExpression()))) {
        return nullptr;
    }
    while (this->consumeIf(DOT_TYPE)) {
        Position identifierPos = this->token->getPos();
        std::unique_ptr<Expression> rightIdentifierListCallExpression;
        if (!(rightIdentifierListCallExpression = std::move(this->parseIdentifierListIndexExpression()))) {
            this->handleSyntaxError(identifierPos, L"No identifier after dot.");
            break;
        }
        leftIdentifierListCallExpression = std::make_unique<ObjectAccessExpression>(std::move(leftIdentifierListCallExpression), std::move(rightIdentifierListCallExpression), identifierPos);
    }

    return leftIdentifierListCallExpression;
}

//part                :== part_call, {"[", std::move(expression), "]"};
std::unique_ptr<Expression> Parser::parseIdentifierListIndexExpression() {
    Position position = this->token->getPos();
    std::unique_ptr<Expression> leftExpression;
    if (!(leftExpression = std::move(this->parseIdentifierFunctionCallExpression()))) {
        return nullptr;
    }
    while(this->consumeIf(L_SQR_BRACKET_TYPE)) {
        Position expressionPosition = this->token->getPos();
        if(std::unique_ptr<Expression> expression = std::move(this->parseExpression())) {
            leftExpression = std::make_unique<IdentifierListIndexExpression>(std::move(leftExpression), std::move(expression), position);
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
std::unique_ptr<Expression> Parser::parseIdentifierFunctionCallExpression() {
    Position position = this->token->getPos();
    bool isFunctionCall = false;

    std::unique_ptr<Expression> identifierExpression = std::move(this->parseIdentifierExpression());
    if(!identifierExpression) {
        return nullptr;
    }

    std::vector<std::unique_ptr<Expression>> expressions;

    //- argument_list       :== [std::move(expression), {",", expression}];
    if(this->consumeIf(L_BRACKET_TYPE)){
        Position expressionPos = this->token->getPos();
        if (std::unique_ptr<Expression> expression = std::move(parseExpression())) {
            expressions.push_back(std::move(expression));
            while(consumeIf(COMMA_TYPE)) {
                expressionPos = this->token->getPos();
                if(expression = std::move(parseExpression())) {
                    expressions.push_back(std::move(expression));
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

    return std::make_unique<IdentifierFunctionCallExpression>(std::move(identifierExpression), std::move(expressions), position);
}

std::unique_ptr<Expression> Parser::parseIdentifierExpression() {
    Position position = this->token->getPos();
    auto name = this->token->getValue();
    if(!this->consumeIf(IDENTIFIER_TYPE)){
        return nullptr;
    }
    return std::make_unique<IdentifierExpression>(std::get<std::wstring>(name), position);
}

//return              :== "return ", [expression], ";"
std::unique_ptr<Statement> Parser::parseReturnStatement() {
    Position position = this->token->getPos();
    if(!this->consumeIf(RETURN_TYPE)){
        return nullptr;
    }

    std::unique_ptr<Expression> expression = std::move(this->parseExpression());

    this->mustBe(SEMICOLON_TYPE, L"Missing semicolon after return statement");

    return std::make_unique<ReturnStatement>(std::move(expression), position);
}

//expression          :== bool_and, {"||",  bool_and};
std::unique_ptr<Expression> Parser::parseExpression() {
    Position position = this->token->getPos();
    std::unique_ptr<Expression> leftConditionExpression;
    if (!(leftConditionExpression = std::move(this->parseExpressionAnd()))) {
        return nullptr;
    }
    while (this->consumeIf(OR_TYPE)) {
        Position factorPos = this->token->getPos();
        std::unique_ptr<Expression> rightConditionExpression;
        if (!(rightConditionExpression = std::move(this->parseExpressionAnd()))) {
            this->handleSyntaxError(factorPos, L"No expression after ||.");
            break;
        }
        leftConditionExpression = std::make_unique<ExpressionOr>(std::move(leftConditionExpression), std::move(rightConditionExpression), factorPos);
    }

    return leftConditionExpression;
}

//bool_and            :== bool_comp , {"&&",  bool_comp};
std::unique_ptr<Expression>Parser::parseExpressionAnd() {
    Position position = this->token->getPos();
    std::unique_ptr<Expression> leftConditionExpression;
    if (!(leftConditionExpression = std::move(this->parseExpressionComp()))) {
        return nullptr;
    }
    while (this->consumeIf(AND_TYPE)) {
        Position factorPos = this->token->getPos();
        std::unique_ptr<Expression> rightConditionExpression;
        if (!(rightConditionExpression = std::move(this->parseExpressionComp()))) {
            this->handleSyntaxError(factorPos, L"No expression after &&.");
            break;
        }
        leftConditionExpression = std::make_unique<ExpressionAnd>(std::move(leftConditionExpression), std::move(rightConditionExpression), factorPos);
    }

    return leftConditionExpression;
}

//bool_comp           :== expression_is, [comp_operator, expression_is];
std::unique_ptr<Expression>Parser::parseExpressionComp() {
    Position position = this->token->getPos();
    std::unique_ptr<Expression> leftConditionExpression;
    if (!(leftConditionExpression = std::move(this->parseExpressionIs()))) {
        return nullptr;
    }

    unsigned short tokenType = this->token->getTokenType();
    if (this->consumeIf(LESS_TYPE) || this->consumeIf(LEQ_TYPE) || this->consumeIf(EQ_TYPE) ||
        this->consumeIf(GREATER_TYPE) || this->consumeIf(GEQ_TYPE) || this->consumeIf(NEQ_TYPE)) {
        Position factorPos = this->token->getPos();
        std::unique_ptr<Expression>rightConditionExpression;
        if (!(rightConditionExpression = std::move(this->parseExpressionIs()))) {
            this->handleSyntaxError(factorPos, L"No expression after comparison operator.");
        }
        leftConditionExpression = std::move(lhs_rhs_expression_constructor_map.at(tokenType)(std::move(leftConditionExpression), std::move(rightConditionExpression), factorPos));
    }

    return leftConditionExpression;
}


//expression_is       :== expression_add, [" is ",  type];
std::unique_ptr<Expression>Parser::parseExpressionIs() {
    Position position = this->token->getPos();
    std::unique_ptr<Expression> leftConditionExpression;
    if (!(leftConditionExpression = std::move(this->parseExpressionAdd()))) {
        return nullptr;
    }

    if (this->consumeIf(IS_TYPE)) {
        Position factorPos = this->token->getPos();
        std::unique_ptr<Expression>rightConditionExpression;
        if(this->consumeIf(STRING_KEYWORD_TYPE)){
            leftConditionExpression = std::make_unique<ExpressionIs>(std::move(leftConditionExpression), STRING_VARIABLE, factorPos);
        } else if(this->consumeIf(INT_KEYWORD_TYPE)){
            leftConditionExpression = std::make_unique<ExpressionIs>(std::move(leftConditionExpression), INT_VARIABLE, factorPos);
        } else if(this->consumeIf(DOUBLE_KEYWORD_TYPE)) {
            leftConditionExpression = std::make_unique<ExpressionIs>(std::move(leftConditionExpression), DOUBLE_VARIABLE, factorPos);
        } else if(this->consumeIf(BOOL_KEYWORD_TYPE)){
            leftConditionExpression = std::make_unique<ExpressionIs>(std::move(leftConditionExpression), BOOL_VARIABLE, factorPos);
        } else if(this->consumeIf(NONE_KEYWORD_TYPE)){
            leftConditionExpression = std::make_unique<ExpressionIs>(std::move(leftConditionExpression), NONE_VARIABLE, factorPos);
        } else if(this->consumeIf(POINT_KEYWORD_TYPE)) {
            leftConditionExpression = std::make_unique<ExpressionIs>(std::move(leftConditionExpression), POINT_VARIABLE, factorPos);
        } else if(this->consumeIf(FIGURE_TYPE)) {
            leftConditionExpression = std::make_unique<ExpressionIs>(std::move(leftConditionExpression), FIGURE_VARIABLE, factorPos);
        } else {
            this->handleSyntaxError(factorPos, L"No type after is keyword.");
        }
    }

    return leftConditionExpression;
}


//expression_add      :== expression_mul, {add_operator, expression_mul};
std::unique_ptr<Expression>Parser::parseExpressionAdd() {
    Position position = this->token->getPos();
    std::unique_ptr<Expression> leftConditionExpression;
    if (!(leftConditionExpression = std::move(this->parseExpressionMul()))) {
        return nullptr;
    }

    unsigned short tokenType = this->token->getTokenType();
    while (this->consumeIf(PLUS_TYPE) || this->consumeIf(MINUS_TYPE)) {
        Position factorPos = this->token->getPos();
        std::unique_ptr<Expression> rightConditionExpression;
        if (!(rightConditionExpression = std::move(this->parseExpressionMul()))) {
            this->handleSyntaxError(factorPos, L"No expression after addition operator.");
            break;
        }
        leftConditionExpression = std::move(lhs_rhs_expression_constructor_map.at(tokenType)(std::move(leftConditionExpression), std::move(rightConditionExpression), factorPos));
        tokenType = this->token->getTokenType();
    }

    return leftConditionExpression;
}

//expression_mul      :== expression_to, {mul_operator, expression_to};
std::unique_ptr<Expression>Parser::parseExpressionMul() {
    Position position = this->token->getPos();
    std::unique_ptr<Expression> leftConditionExpression;
    if (!(leftConditionExpression = std::move(this->parseExpressionTo()))) {
        return nullptr;
    }

    unsigned short tokenType = this->token->getTokenType();
    while (this->consumeIf(MULTIPLY_TYPE) || this->consumeIf(DIVIDE_TYPE)) {
        Position factorPos = this->token->getPos();
        std::unique_ptr<Expression> rightConditionExpression;
        if (!(rightConditionExpression = std::move(this->parseExpressionTo()))) {
            this->handleSyntaxError(factorPos, L"No expression after multiplication operator.");
            break;
        }
        leftConditionExpression = std::move(lhs_rhs_expression_constructor_map.at(tokenType)(std::move(leftConditionExpression), std::move(rightConditionExpression), factorPos));
        tokenType = this->token->getTokenType();
    }

    return leftConditionExpression;
}

//expression_to       :== nagated_value, [" to ",  type];
std::unique_ptr<Expression>Parser::parseExpressionTo() {
    Position position = this->token->getPos();
    std::unique_ptr<Expression> leftConditionExpression;
    if (!(leftConditionExpression = std::move(this->parseExpressionNeg()))) {
        return nullptr;
    }

    if (this->consumeIf(TO_TYPE)) {
        Position factorPos = this->token->getPos();
        std::unique_ptr<Expression>rightConditionExpression;
        if(this->consumeIf(STRING_KEYWORD_TYPE)){
            leftConditionExpression = std::make_unique<ExpressionTo>(std::move(leftConditionExpression), STRING_VARIABLE, factorPos);
        } else if(this->consumeIf(INT_KEYWORD_TYPE)){
            leftConditionExpression = std::make_unique<ExpressionTo>(std::move(leftConditionExpression), INT_VARIABLE, factorPos);
        } else if(this->consumeIf(DOUBLE_KEYWORD_TYPE)) {
            leftConditionExpression = std::make_unique<ExpressionTo>(std::move(leftConditionExpression), DOUBLE_VARIABLE, factorPos);
        } else if(this->consumeIf(BOOL_KEYWORD_TYPE)){
            leftConditionExpression = std::make_unique<ExpressionTo>(std::move(leftConditionExpression), BOOL_VARIABLE, factorPos);
        } else if(this->consumeIf(NONE_KEYWORD_TYPE)){
            leftConditionExpression = std::make_unique<ExpressionTo>(std::move(leftConditionExpression), NONE_VARIABLE, factorPos);
        } else if(this->consumeIf(POINT_KEYWORD_TYPE)) {
            leftConditionExpression = std::make_unique<ExpressionTo>(std::move(leftConditionExpression), POINT_VARIABLE, factorPos);
        } else if(this->consumeIf(FIGURE_TYPE)) {
            leftConditionExpression = std::make_unique<ExpressionTo>(std::move(leftConditionExpression), FIGURE_VARIABLE, factorPos);
        } else {
            this->handleSyntaxError(factorPos, L"No expression after is keyword.");
        }
    }

    return leftConditionExpression;
}

//negated_value       :== [negation_operator], accessed_value;
std::unique_ptr<Expression>Parser::parseExpressionNeg() {
    Position position = this->token->getPos();
    std::unique_ptr<Expression> expression;
    unsigned short tokenType = this->token->getTokenType();
    bool negated = false;
    if (this->consumeIf(NEGATION_TYPE) || this->consumeIf(MINUS_TYPE)) {
        negated = true;
    }

    if (!(expression = std::move(this->parseAccessedValue()))) {
        if (negated) {
            this->handleSyntaxError(position, L"No expression after negation operator.");
        }
        return nullptr;
    }

    if (negated) {
        if (tokenType == NEGATION_TYPE) {
            expression = std::make_unique<ExpressionNeg>(std::move(expression), position);
        } else {
            expression = std::make_unique<ExpressionNegMinus>(std::move(expression), position);
        }
    }

    return expression;
}

//accessed_value        :== value
//                        | list
//                        | point
//                        | identifier_stmnt
//                        | "(", std::move(expression), ")";
std::unique_ptr<Expression>Parser::parseAccessedValue() {
    std::unique_ptr<Expression> expression;
    if (expression = std::move(this->parseExpressionValueList())) {
    } else if (expression = std::move(this->parseExpressionValueLiteral())) {
    } else if (expression = std::move(this->parseObjectAccessExpression())){
    } else {//osobna metoda
        //"(", std::move(expression), ")";
        if(!consumeIf(L_BRACKET_TYPE)) {
            return nullptr;
        }
        Position insideExpressionPosition = this->token->getPos();
        std::unique_ptr<Expression> insideExpression = std::move(parseExpression());
        if (!insideExpression) {
            this->handleSyntaxError(insideExpressionPosition, L"No expression inside brackets");
        }
        //point               :== "(", std::move(expression), ",", std::move(expression), ")";
        if(this->consumeIf(COMMA_TYPE)) {
            std::unique_ptr<Expression> xCoordExpression = std::move(insideExpression);
            std::unique_ptr<Expression> yCoordExpression;
            Position yCoordExprPos = this->token->getPos();
            if(yCoordExpression = std::move(parseExpression())) {
            } else {
                this->handleSyntaxError(yCoordExprPos, L"Missing expression after comma in point value.");
            }
            this->mustBe(R_BRACKET_TYPE, L"No right bracket in point");

            expression = std::make_unique<ExpressionValuePoint>(std::move(xCoordExpression), std::move(yCoordExpression), insideExpressionPosition);
        } else {
            this->mustBe(R_BRACKET_TYPE, L"No right bracket.");
            expression = std::make_unique<ExpressionValueBrackets>(std::move(insideExpression), insideExpressionPosition);
        }

    }
    return expression;
}

//list                :== "[", std::move(expression), {", ", expression} "]";
std::unique_ptr<Expression>Parser::parseExpressionValueList() {
    Position position = this->token->getPos();
    if(!consumeIf(L_SQR_BRACKET_TYPE)) {
        return nullptr;
    }
    std::vector<std::unique_ptr<Expression>> expressions;
    Position expressionPos = this->token->getPos();
    if (std::unique_ptr<Expression> expression = std::move(parseExpression())) {
        expressions.push_back(std::move(expression));
        while(consumeIf(COMMA_TYPE)) {
            expressionPos = this->token->getPos();
            if(expression = std::move(parseExpression())) {
                expressions.push_back(std::move(expression));
            } else {
                this->handleSyntaxError(expressionPos, L"Missing expression after comma in list");
            }
        }
    }
    this->mustBe(R_SQR_BRACKET_TYPE, L"Missing right bracket closing list");
    return std::make_unique<ExpressionValueList>(std::move(expressions), position);
}

// value                :== int_val
//                        | bool_val
//                        | double_val
//                        | string_val
//                        | "none";
std::unique_ptr<Expression>Parser::parseExpressionValueLiteral() {
    //get value i type
    auto value = this->token->getValue();
    auto position = this->token->getPos();
    if (this->consumeIf(INTEGER_TYPE)) {
        return std::make_unique<ExpressionValueLiteral>(std::get<int>(value), position);
    }
    if (this->consumeIf(DOUBLE_TYPE)){
        return std::make_unique<ExpressionValueLiteral>(std::get<double>(value), position);
    }
    if (this->consumeIf(NONE_KEYWORD_TYPE)){
        return std::make_unique<ExpressionValueLiteral>(std::monostate(), position);
    }
    if(this->consumeIf(TRUE_TYPE)){
        return std::make_unique<ExpressionValueLiteral>(true, position);
    }
    if (this->consumeIf(FALSE_TYPE)){
        return std::make_unique<ExpressionValueLiteral>(false, position);
    }
    if (this->consumeIf(STRING_TYPE)){
        return std::make_unique<ExpressionValueLiteral>(std::get<std::wstring>(value), position);
    }
    return nullptr;
}
