//
// Created by mpkow on 15.05.2023.
//

#include <vector>
#include <variant>
#include <unordered_map>
#include <string>
#include <optional>
#include <functional>
#include "lexer.h"
#include "Program/Program.h"

#ifndef LEXER_PARSER_H
#define LEXER_PARSER_H

static const std::unordered_map<unsigned short, std::function<Expression*(Expression *, Expression *, const Position &)>> lhs_rhs_expression_constructor_map= {
        {LESS_TYPE, [](Expression * leftConditionExpression, Expression * rightConditionExpression, const Position & factorPos)
                    {
                        return new ExpressionCompLess(leftConditionExpression, rightConditionExpression, factorPos);
                    }
        },
        {GREATER_TYPE, [](Expression * leftConditionExpression, Expression * rightConditionExpression, const Position & factorPos)
                    {
                        return new ExpressionCompGreater(leftConditionExpression, rightConditionExpression, factorPos);
                    }
        },
        {LEQ_TYPE, [](Expression * leftConditionExpression, Expression * rightConditionExpression, const Position & factorPos)
                    {
                        return new ExpressionCompLeq(leftConditionExpression, rightConditionExpression, factorPos);
                    }
        },
        {GEQ_TYPE, [](Expression * leftConditionExpression, Expression * rightConditionExpression, const Position & factorPos)
                    {
                        return new ExpressionCompGeq(leftConditionExpression, rightConditionExpression, factorPos);
                    }
        },
        {EQ_TYPE, [](Expression * leftConditionExpression, Expression * rightConditionExpression, const Position & factorPos)
                    {
                        return new ExpressionCompEq(leftConditionExpression, rightConditionExpression, factorPos);
                    }
        },
        {NEQ_TYPE, [](Expression * leftConditionExpression, Expression * rightConditionExpression, const Position & factorPos)
                    {
                        return new ExpressionCompNeq(leftConditionExpression, rightConditionExpression, factorPos);
                    }
        },
        {MULTIPLY_TYPE, [](Expression * leftConditionExpression, Expression * rightConditionExpression, const Position & factorPos)
                  {
                      return new ExpressionMul(leftConditionExpression, rightConditionExpression, factorPos);
                  }
        },
        {DIVIDE_TYPE, [](Expression * leftConditionExpression, Expression * rightConditionExpression, const Position & factorPos)
                  {
                      return new ExpressionDiv(leftConditionExpression, rightConditionExpression, factorPos);
                  }
        },
        {PLUS_TYPE, [](Expression * leftConditionExpression, Expression * rightConditionExpression, const Position & factorPos)
                        {
                            return new ExpressionAdd(leftConditionExpression, rightConditionExpression, factorPos);
                        }
        },
        {MINUS_TYPE, [](Expression * leftConditionExpression, Expression * rightConditionExpression, const Position & factorPos)
                        {
                            return new ExpressionSub(leftConditionExpression, rightConditionExpression, factorPos);
                        }
        },
};

class Parser {
public:
    Parser(Lexer *pLexer, ErrorHandler *pHandler) : lexer(pLexer), errorHandler(pHandler) {};

    Program * parse();
    bool getSemanticError() {return this->semantic_error;};
    bool getSyntaxError() {return this->blocking_syntax_error;};
private:
    bool blocking_syntax_error = false;
    bool semantic_error = false;
    Lexer * lexer;
    ErrorHandler * errorHandler;
    std::optional<Token> token;

    bool consumeIf(unsigned int token_type);
    std::variant<int, double, std::wstring> mustBe(unsigned int token_type, std::wstring message);

    FuncDeclaration * parseFuncDecl();
    FigureDeclaration * parseFigureDecl();
    std::vector<Parameter *> parseFigureParams();
    Parameter * parseFigureParam();
    std::vector<Parameter *> parseFunctionParams();
    Parameter * parseParam();
    CodeBlock * parseCodeBlock();
    Statement * parseStatement();
    Statement * parseWhileStatement();
    Statement * parseIfStatement();
    Statement * parseForStatement();
    Statement * parseDeclarationStatement();
    Statement * parseIdentifierAssignmentStatement();
    Statement * parseIdentifierExpressionStatement();
    Expression * parseObjectAccessExpression();
    Expression * parseIdentifierListIndexExpression();
    Expression * parseIdentifierFunctionCallExpression();
    Expression * parseIdentifierExpression();
    Statement * parseReturnStatement();
    ConditionAndBlock * parseConditionAndBlock(const std::wstring & statement_type, token_type tokenType);
    Expression * parseExpression();
    Expression * parseExpressionAnd();
    Expression * parseExpressionComp();
    Expression * parseExpressionIs();
    Expression * parseExpressionAdd();
    Expression * parseExpressionMul();
    Expression * parseExpressionTo();
    Expression * parseExpressionNeg();
    Expression * parseAccessedValue();
    Expression * parseExpressionValueList();
    Expression * parseExpressionValueLiteral();

    nullptr_t handleSyntaxError(const Position &position, const std::wstring &message);
    void handleSemanticError(const Position &position, const std::wstring &message);

};


#endif //LEXER_PARSER_H
