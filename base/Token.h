#ifndef __TOKEN_H__
#define __TOKEN_H__

#include "TQueue.h"
#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>

using namespace std;

struct Token {
    string val;
    bool isNumber;

    Token(string v = "", bool num = false) : val(v), isNumber(num) {}
};

class MakeTokens{
private:
    enum TokenStates {
        start,
        reading_number,
        reading_operator,
        error,
        done
    };

    string enteredString;
    size_t pos;
    TokenStates state;
public:
    MakeTokens(const string& s): enteredString(s), pos(0), state(start) {}

    char top() const {
        if (pos < enteredString.length()) {
            return enteredString[pos];
        }
        return '\0';
    }

    char get() {
        if (pos < enteredString.length()) {
            return enteredString[pos++];
        }
        return '\0';
    }

    bool isOperator(char c) const {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
    }

    bool isDigitOrDot(char c) const {
        return isdigit(c) || c == '.' || c == ',';
    }

    void skipSpaces() {
        while (pos < enteredString.length() && isspace(top())) {
            pos++;
        }
    }

    string readNumber() {
        string num;
        bool hasDot = false;

        while (pos < enteredString.length()) {
            char c = top();

            if (isdigit(c)) {
                num += c;
                pos++;
            }
            else if (c == '.' || c == ',') {
                if (!hasDot) {
                    num += '.';
                    hasDot = true;
                    pos++;
                }
                else {
                    state = error;
                    throw runtime_error("Некорректное число");
                }
            }
            else {
                break;
            }
        }
        if (num.empty()) {
            throw runtime_error("Некорректное число");
        }
        if (num.back() == '.') {
            throw runtime_error("Некорректное число");
        }
        return num;
    }

    TQueue<Token> getTokens() {
        TQueue<Token> tokens(enteredString.length() * 2);
        state = start;

        while (true) {
            skipSpaces();

            if (pos >= enteredString.length()) {
                state = done;
                return tokens;
            }

            char current = top();

            switch (state) {
            case start:
                if (isDigitOrDot(current)) {
                    state = reading_number;
                }
                else if (isOperator(current)) {
                    state = reading_operator;
                }
                else {
                    state = error;
                    throw runtime_error(string("Недопустимый символ: '") + current + "'");
                }
                break;

            case reading_number: {
                string num = readNumber();
                tokens.push(Token(num, true));
                state = start;
                break;
            }

            case reading_operator: {
                string op(1, get());
                tokens.push(Token(op, false));
                state = start;
                break;
            }

            case error:
                throw runtime_error("Ошибка при разборе выражения");

            case done:
                return tokens;
            }
        }

        return tokens;
    }
};

#endif