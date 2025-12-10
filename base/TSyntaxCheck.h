#ifndef __TSYNTAXCHECK_H__
#define __TSYNTAXCHECK_H__

#include "Token.h"
#include "TQueue.h"
#include <stdexcept>
#include <string>

using namespace std;


class SyntaxCheck {
private:

    enum SyntaxStates {
        start,
        expect_number_or_openBracket,
        expect_operator_or_closeBracket,
        expect_number,
        error,
        done
    };

    SyntaxStates state;
    int bracketsCnt;
    int cntUnaryMinuses;
public:
    SyntaxCheck() : state(start), bracketsCnt(0), cntUnaryMinuses(0){}

    bool isBinaryOp(const string& op) const {
        return op == "+" || op == "-" || op == "*" || op == "/";
    }

    bool isUnaryOp(const Token& curr, const Token* prev) const {
        if (curr.val == "-") {
            if (!prev) {
                return true;
            }
            if (!prev->isNumber &&
                (prev->val == "(" || isBinaryOp(prev->val))) {
                return true;
            }
        }
        return false;
    }

    TQueue<Token> Check(TQueue<Token> inputTokens) {
        TQueue<Token> output(100);
        SyntaxStates currState = start;
        bracketsCnt = 0;
        cntUnaryMinuses = 0;
        Token prevTokenObj;
        const Token* prevToken = nullptr;

        while (!inputTokens.isEmpty()) {
            Token currToken = inputTokens.pop();

            switch (currState) {
            case start:
                if (currToken.isNumber) {
                    output.push(currToken);
                    currState = expect_operator_or_closeBracket;
                }
                else if (currToken.val == "(") {
                    output.push(currToken);
                    bracketsCnt++;
                    currState = expect_number_or_openBracket;
                }
                else if (isUnaryOp(currToken, prevToken)) {
                    output.push(Token("(", false));
                    output.push(Token("0", true));
                    output.push(Token("-", false));
                    bracketsCnt++;
                    cntUnaryMinuses++;
                    currState = expect_number;
                }
                else {
                    throw runtime_error("Ошибка");
                }
                break;
            case expect_number_or_openBracket:
                if (currToken.isNumber) {
                    output.push(currToken);
                    currState = expect_operator_or_closeBracket;
                }
                else if (currToken.val == "(") {
                    output.push(currToken);
                    bracketsCnt++;
                    currState = expect_number_or_openBracket;
                }
                else if (isUnaryOp(currToken, prevToken)) {
                    output.push(Token("(", false));
                    output.push(Token("0", true));
                    output.push(Token("-", false));
                    bracketsCnt++;
                    cntUnaryMinuses++;
                    currState = expect_number;
                }
                else {
                    throw runtime_error("Ошибка");
                }
                break;

            case expect_number:
                if (currToken.isNumber) {
                    output.push(currToken);
                    if (cntUnaryMinuses > 0) {
                        output.push(Token(")", false));
                        bracketsCnt--;
                        csntUnaryMinuses--;
                    }
                    currState = expect_operator_or_closeBracket;
                }
                else if (currToken.val == "(") {
                    output.push(currToken);
                    bracketsCnt++;
                    currState = expect_number_or_openBracket;
                }
                else {
                    throw runtime_error("Ошибка");
                }
                break;

            case expect_operator_or_closeBracket:
                if (isBinaryOp(currToken.val)) {
                    output.push(currToken);
                    currState = expect_number_or_openBracket;
                }
                else if (currToken.val == ")") {
                    output.push(currToken);
                    bracketsCnt--;
                    if (cntUnaryMinuses > 0) {
                        output.push(Token(")", false));
                        bracketsCnt--;
                        cntUnaryMinuses--;
                    }
                    if (bracketsCnt < 0) {
                        throw runtime_error("Ошибка");
                    }
                    currState = expect_operator_or_closeBracket;
                }
                else {
                    throw runtime_error("Ошибка");
                }
                break;
            default:
                throw runtime_error("Неизвестное состояние");
            }
            prevTokenObj = currToken;
            prevToken = &prevTokenObj;
        }

        while (cntUnaryMinuses > 0) {
            output.push(Token(")", false));
            bracketsCnt--;
            cntUnaryMinuses--;
        }

        if (currState != expect_operator_or_closeBracket || bracketsCnt != 0) {
            throw runtime_error("Ошибка");
        }

        state = done;
        return output;
    }
};

#endif