#ifndef __TPOSTFIX_H__
#define __TPOSTFIX_H__

#include "TStack.h"
#include "TQueue.h"
#include "Token.h"
#include "TSyntaxCheck.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

class TArithmeticExpression {
	string infix;
	string postfix;
	vector<string> postfixTokens;
	map<string, int> priority;
	map<char, double> operands;
public:
	void ToPostfix(TQueue<Token>& tokens) {
		TVectorStack<Token> st;

		while (!tokens.isEmpty()) {
			Token token = tokens.pop();

			if (token.isNumber) {
				postfixTokens.push_back(token.val);
				postfix += token.val;
			}
			else if (token.val == "(") {
				st.Push(token);
			}
			else if (token.val == ")") {
				while (!st.IsEmpty() && st.Top().val != "(") {
					postfixTokens.push_back(st.Top().val);
					postfix += st.Top().val;
					st.Pop();
				}
				if (!st.IsEmpty() && st.Top().val == "(") {
					st.Pop();
				}
			}
			else {
				while (!st.IsEmpty() &&
					st.Top().val != "(" &&
					priority[st.Top().val] >= priority[token.val]) {
					postfixTokens.push_back(st.Top().val);
					postfix += st.Top().val;
					st.Pop();
				}
				st.Push(token);
			}
		}
		while (!st.IsEmpty()) {
			if (st.Top().val != "(") {
				postfixTokens.push_back(st.Top().val);
				postfix += st.Top().val;
			}
			st.Pop();
		}
	}

	TArithmeticExpression(string infx) : infix(infx) {
		priority["+"] = 1; priority["-"] = 1; priority["*"] = 2; priority["/"] = 2;
		try {

			MakeTokens tokensMaker(infix);
			TQueue<Token> tokens = tokensMaker.getTokens();

			SyntaxCheck checker;
			TQueue<Token> correctTokens = checker.Check(tokens);

			ToPostfix(correctTokens);

		}catch(const exception& e) {
			throw runtime_error("Ошибка в выражении");
		}
	}

	TArithmeticExpression() {
		priority["+"] = 1; priority["-"] = 1; priority["*"] = 2; priority["/"] = 2;
	}

	string GetInfix() const {
		return infix;
	}

	string GetPostfix() const {
		return postfix;
	}

	vector<string> GetPostfixTokens() const {
		return postfixTokens;
	}

	double Calculate() {
		TVectorStack<double> st;
		
		for (const string& token : postfixTokens) {
			bool isNumber = true;
			for (char c : token) {
				if (!isdigit(c) && c != '.') {
					isNumber = false;
					break;
				}
			}
			if (isNumber) {
				st.Push(stod(token));
			}
			else if (token == "+" || token == "-" || token == "*" || token == "/") {
				if (st.size() < 2) {
					throw runtime_error("Недостаточно операндов");
				}

				double rightOperand = st.Top(); st.Pop();
				double leftOperand = st.Top(); st.Pop();

				double result = 0;
				if (token == "+") {
					result = leftOperand + rightOperand;
				}
				else if (token == "-") {
					result = leftOperand - rightOperand;
				}
				else if (token == "*") {
					result = leftOperand * rightOperand;
				}
				else if (token == "/") {
					if (rightOperand == 0) {
						throw runtime_error("Деление на ноль");
					}
					result = leftOperand / rightOperand;
				}

				st.Push(result);
			}
		}
		return st.Top();
	}
};

#endif