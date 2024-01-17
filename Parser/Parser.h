//
// Created by mpkow on 15.05.2023.
//

#include <vector>
#include <variant>
#include <unordered_map>
#include <string>
#include <memory>
#include <optional>
#include <functional>
#include "../Lexer/lexer.h"
#include "../Program/Program.h"

#ifndef LEXER_PARSER_H
#define LEXER_PARSER_H

static const std::unordered_map<unsigned short, std::function<std::unique_ptr<Expression>(std::unique_ptr<Expression>, std::unique_ptr<Expression>, const Position &)>> lhs_rhs_expression_constructor_map= {
        {LESS_TYPE, [](std::unique_ptr<Expression> leftConditionExpression, std::unique_ptr<Expression> rightConditionExpression, const Position & factorPos)
                    {
                        return std::make_unique<ExpressionCompLess>(std::move(leftConditionExpression), std::move(rightConditionExpression), factorPos);
                    }
        },
        {GREATER_TYPE, [](std::unique_ptr<Expression> leftConditionExpression, std::unique_ptr<Expression> rightConditionExpression, const Position & factorPos)
                    {
                        return std::make_unique<ExpressionCompGreater>(std::move(leftConditionExpression), std::move(rightConditionExpression), factorPos);
                    }
        },
        {LEQ_TYPE, [](std::unique_ptr<Expression> leftConditionExpression, std::unique_ptr<Expression> rightConditionExpression, const Position & factorPos)
                    {
                        return std::make_unique<ExpressionCompLeq>(std::move(leftConditionExpression), std::move(rightConditionExpression), factorPos);
                    }
        },
        {GEQ_TYPE, [](std::unique_ptr<Expression> leftConditionExpression, std::unique_ptr<Expression> rightConditionExpression, const Position & factorPos)
                    {
                        return std::make_unique<ExpressionCompGeq>(std::move(leftConditionExpression), std::move(rightConditionExpression), factorPos);
                    }
        },
        {EQ_TYPE, [](std::unique_ptr<Expression> leftConditionExpression, std::unique_ptr<Expression> rightConditionExpression, const Position & factorPos)
                    {
                        return std::make_unique<ExpressionCompEq>(std::move(leftConditionExpression), std::move(rightConditionExpression), factorPos);
                    }
        },
        {NEQ_TYPE, [](std::unique_ptr<Expression> leftConditionExpression, std::unique_ptr<Expression> rightConditionExpression, const Position & factorPos)
                    {
                        return std::make_unique<ExpressionCompNeq>(std::move(leftConditionExpression), std::move(rightConditionExpression), factorPos);
                    }
        },
        {MULTIPLY_TYPE, [](std::unique_ptr<Expression> leftConditionExpression, std::unique_ptr<Expression> rightConditionExpression, const Position & factorPos)
                  {
                      return std::make_unique<ExpressionMul>(std::move(leftConditionExpression), std::move(rightConditionExpression), factorPos);
                  }
        },
        {DIVIDE_TYPE, [](std::unique_ptr<Expression> leftConditionExpression, std::unique_ptr<Expression> rightConditionExpression, const Position & factorPos)
                  {
                      return std::make_unique<ExpressionDiv>(std::move(leftConditionExpression), std::move(rightConditionExpression), factorPos);
                  }
        },
        {PLUS_TYPE, [](std::unique_ptr<Expression> leftConditionExpression, std::unique_ptr<Expression> rightConditionExpression, const Position & factorPos)
                        {
                            return std::make_unique<ExpressionAdd>(std::move(leftConditionExpression), std::move(rightConditionExpression), factorPos);
                        }
        },
        {MINUS_TYPE, [](std::unique_ptr<Expression> leftConditionExpression, std::unique_ptr<Expression> rightConditionExpression, const Position & factorPos)
                        {
                            return std::make_unique<ExpressionSub>(std::move(leftConditionExpression), std::move(rightConditionExpression), factorPos);
                        }
        },
};

class Parser {
public:
    Parser(Lexer *pLexer, ErrorHandler *pHandler) : lexer(pLexer), errorHandler(pHandler) {};

    std::unique_ptr<Program> parse();
private:
    Lexer * lexer;
    ErrorHandler * errorHandler;
    std::optional<Token> token;

    bool consumeIf(unsigned int token_type);
    std::variant<int, double, std::wstring> mustBe(unsigned int token_type, std::wstring message);

    std::unique_ptr<FuncDeclaration> parseFuncDecl();
    std::unique_ptr<FigureDeclaration> parseFigureDecl();
    std::vector<std::unique_ptr<Parameter>> parseFigureParams();
    std::unique_ptr<Parameter> parseFigureParam();
    std::vector<std::unique_ptr<Parameter>> parseFunctionParams();
    std::unique_ptr<Parameter> parseParam();
    std::unique_ptr<CodeBlock> parseCodeBlock();
    std::unique_ptr<Statement> parseStatement();
    std::unique_ptr<Statement> parseWhileStatement();
    std::unique_ptr<Statement> parseIfStatement();
    std::unique_ptr<Statement> parseForStatement();
    std::unique_ptr<Statement> parseForRangeStatement(const std::wstring & name, const Position & position);
    std::unique_ptr<Statement> parseDeclarationStatement();
    std::unique_ptr<Statement> parseIdentifierAssignmentOrExpressionStatement();
    std::unique_ptr<Expression> parseObjectAccessExpression();
    std::unique_ptr<Expression> parseIdentifierListIndexExpression();
    std::unique_ptr<Expression> parseIdentifierFunctionCallExpression();
    std::unique_ptr<Expression> parseIdentifierExpression();
    std::unique_ptr<Statement> parseReturnStatement();
    std::unique_ptr<ConditionAndBlock> parseConditionAndBlock(const std::wstring & statement_type, token_type tokenType);
    std::unique_ptr<Expression> parseExpression();
    std::unique_ptr<Expression> parseExpressionAnd();
    std::unique_ptr<Expression> parseExpressionComp();
    std::unique_ptr<Expression> parseExpressionIs();
    std::unique_ptr<Expression> parseExpressionAdd();
    std::unique_ptr<Expression> parseExpressionMul();
    std::unique_ptr<Expression> parseExpressionTo();
    std::unique_ptr<Expression> parseExpressionNeg();
    std::unique_ptr<Expression> parseAccessedValue();
    std::unique_ptr<Expression> parseExpressionValueList();
    std::unique_ptr<Expression> parseExpressionValueLiteral();
    std::unique_ptr<Expression> parseExpressionValueBrackets();

    nullptr_t handleSyntaxError(const Position &position, const std::wstring &message);
    void handleSemanticError(const Position &position, const std::wstring &message);

};


#endif //LEXER_PARSER_H
