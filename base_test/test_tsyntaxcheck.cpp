#include "TSyntaxCheck.h"
#include "Token.h"
#include "TQueue.h"
#include <gtest/gtest.h>

TEST(TSyntaxCheck, can_create_syntax_checker) {
	ASSERT_NO_THROW(SyntaxCheck checker);
}

TEST(TSyntaxCheck, returns_true_if_binary_operator) {
	SyntaxCheck checker;
	EXPECT_TRUE(checker.isBinaryOp("+"));
	EXPECT_TRUE(checker.isBinaryOp("-"));
	EXPECT_TRUE(checker.isBinaryOp("*"));
	EXPECT_TRUE(checker.isBinaryOp("/"));
}

TEST(TSyntaxCheck, returns_false_if_not_binary_operator) {
	SyntaxCheck checker;
	EXPECT_FALSE(checker.isBinaryOp("a"));
	EXPECT_FALSE(checker.isBinaryOp("="));
	EXPECT_FALSE(checker.isBinaryOp("5"));
}

TEST(TSyntaxCheck, returns_true_if_unary_operator) {
	SyntaxCheck checker;
	EXPECT_TRUE(checker.isUnaryOp(Token("-", false), nullptr));

	Token t1("(", false);
	EXPECT_TRUE(checker.isUnaryOp(Token("-", false), &t1));
}

TEST(TSyntaxCheck, returns_false_if_not_unary_operator) {
	SyntaxCheck checker;

	EXPECT_FALSE(checker.isUnaryOp(Token("+", false), nullptr));

	Token t1("a", false);
	EXPECT_FALSE(checker.isUnaryOp(Token("-", false), &t1));

	Token t2("2", true);
	EXPECT_FALSE(checker.isUnaryOp(Token("-", false), &t2));
}

TEST(TSyntaxCheck, can_check_simple_example) {
	MakeTokens tokensMaker("1+2");
	TQueue<Token> tokens = tokensMaker.getTokens();

	SyntaxCheck checker;
	TQueue<Token> result(10);
	ASSERT_NO_THROW(result = checker.Check(tokens));

	EXPECT_EQ(3, result.size());
}

TEST(TSyntaxCheck, can_check_hard_example) {
	MakeTokens tokenizer("-(3 * 4) + 5 / - 2");
	TQueue<Token> tokens = tokenizer.getTokens();

	SyntaxCheck checker;
	TQueue<Token> result(20);
	ASSERT_NO_THROW(result = checker.Check(tokens));

	EXPECT_EQ(17, result.size());
}

TEST(TSyntaxCheck, can_handle_unary_minus) {
	MakeTokens tokensMaker("-1+2"); //должно стать (0-1)+2
	TQueue<Token> tokens = tokensMaker.getTokens();

	SyntaxCheck checker;
	TQueue<Token> result(10);
	ASSERT_NO_THROW(result = checker.Check(tokens));

	EXPECT_EQ(7, result.size());

	Token t1 = result.pop();
	EXPECT_FALSE(t1.isNumber);
	EXPECT_EQ("(", t1.val);

	Token t2 = result.pop();
	EXPECT_TRUE(t2.isNumber);
	EXPECT_EQ("0", t2.val);

	Token t3 = result.pop();
	EXPECT_FALSE(t3.isNumber);
	EXPECT_EQ("-", t3.val);

	Token t4 = result.pop();
	EXPECT_TRUE(t4.isNumber);
	EXPECT_EQ("1", t4.val);

	Token t5 = result.pop();
	EXPECT_FALSE(t5.isNumber);
	EXPECT_EQ(")", t5.val);
}

TEST(TSyntaxCheck, can_handle_unary_minus_befor_brackets) {
	MakeTokens tokensMaker("-(1+2)"); // должно стать (0-(1+2))
	TQueue<Token> tokens = tokensMaker.getTokens();

	SyntaxCheck checker;
	TQueue<Token> result(10);
	ASSERT_NO_THROW(result = checker.Check(tokens));

	EXPECT_EQ(9, result.size());
}

TEST(TSyntaxCheck, throws_when_two_operators_inline) {
	MakeTokens tokenizer("1++2");
	TQueue<Token> tokens = tokenizer.getTokens();

	SyntaxCheck checker;
	ASSERT_ANY_THROW(checker.Check(tokens));
}

TEST(TSyntaxCheck, throws_when_no_second_operand) {
	MakeTokens tokenizer("1+");
	TQueue<Token> tokens = tokenizer.getTokens();

	SyntaxCheck checker;
	ASSERT_ANY_THROW(checker.Check(tokens));
}

TEST(TSyntaxCheck, throws_when_no_open_breaket) {
	MakeTokens tokenizer("1+3)*2");
	TQueue<Token> tokens = tokenizer.getTokens();

	SyntaxCheck checker;
	ASSERT_ANY_THROW(checker.Check(tokens));
}

TEST(T, throws_when_no_close_breaket) {
	MakeTokens tokenizer("2*(1+3");
	TQueue<Token> tokens = tokenizer.getTokens();

	SyntaxCheck checker;
	ASSERT_ANY_THROW(checker.Check(tokens));
}