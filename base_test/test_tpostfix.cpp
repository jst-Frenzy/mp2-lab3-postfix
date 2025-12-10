#include "TPostfix.h"
#include <gtest/gtest.h>

TEST(TArithmeticExpression, can_create_expression) {
    ASSERT_NO_THROW(TArithmeticExpression expr("1+2"));
}

TEST(TArithmeticExpression, throws_if_incorrect_expression) {
    ASSERT_ANY_THROW(TArithmeticExpression expr("1++2"));
    ASSERT_ANY_THROW(TArithmeticExpression expr("2+"));
    ASSERT_ANY_THROW(TArithmeticExpression expr("(1+2"));
}

TEST(TArithmeticExpression, can_get_correct_infix) {
    TArithmeticExpression expr("2+3*4");
    EXPECT_EQ("2+3*4", expr.GetInfix());
}

TEST(TArithmeticExpression, can_topostfix_simple_example) {
    TArithmeticExpression expr;

    MakeTokens tokensMaker("2+3");
    TQueue<Token> tokens = tokensMaker.getTokens();

    SyntaxCheck checker;
    TQueue<Token> test = checker.Check(tokens);

    expr.ToPostfix(test);
    EXPECT_EQ("23+", expr.GetPostfix());
}

TEST(TArithmeticExpression, can_topostfix_hard_example) {
    TArithmeticExpression expr;

    MakeTokens tokensMaker("-(3*4)+5/-2");
    TQueue<Token> tokens = tokensMaker.getTokens();

    SyntaxCheck checker;
    TQueue<Token> test = checker.Check(tokens);

    expr.ToPostfix(test);
    EXPECT_EQ("034*-502-/+", expr.GetPostfix());
}

TEST(TArithmeticExpression, can_topostfix_with_brackets) {
    TArithmeticExpression expr;

    MakeTokens tokensMaker("(2+3)*4");
    TQueue<Token> tokens = tokensMaker.getTokens();

    SyntaxCheck checker;
    TQueue<Token> test = checker.Check(tokens);

    expr.ToPostfix(test);
    EXPECT_EQ("23+4*", expr.GetPostfix());
}

TEST(TArithmeticExpression, can_topostfix_with_unary_minus) {
    TArithmeticExpression expr;

    MakeTokens tokensMaker("-1+2");
    TQueue<Token> tokens = tokensMaker.getTokens();

    SyntaxCheck checker;
    TQueue<Token> test = checker.Check(tokens);

    expr.ToPostfix(test);
    EXPECT_EQ("01-2+", expr.GetPostfix());
}

TEST(TArithmeticExpression, can_calculate_simple_example) {
    TArithmeticExpression expr("2+3");
    double answ = expr.Calculate();
    EXPECT_EQ(5.0, answ);
}

TEST(TArithmeticExpression, can_calculate_hard_example) {
    TArithmeticExpression expr("-(3*4)+5/-2");
    double answ = expr.Calculate();
    EXPECT_EQ(-14.5, answ);
}

TEST(TArithmeticExpression, can_calculate_multi_digit_nums) {
    TArithmeticExpression expr("123+456");
    double answ = expr.Calculate();
    EXPECT_EQ(579.0, answ);
}

TEST(TArithmeticExpression, can_calculate_example_with_brackets) {
    TArithmeticExpression expr("(2+3)*4");
    double answ = expr.Calculate();
    EXPECT_EQ(20.0, answ);
}

TEST(TArithmeticExpression, can_calculate_with_unary_minus) {
    TArithmeticExpression expr("-1+2");
    double answ = expr.Calculate();
    EXPECT_EQ(1.0, answ);
}