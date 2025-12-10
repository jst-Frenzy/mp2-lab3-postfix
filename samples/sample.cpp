#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "TPostfix.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    string exprStr;
    while (true) {
        cout << "Enter expression: ";
        getline(cin, exprStr);
        try {
            TArithmeticExpression expr(exprStr);
            cout << expr.GetInfix() << endl;
            cout << expr.GetPostfix() << endl;
            double result = expr.Calculate();
            cout << result << endl;
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
}