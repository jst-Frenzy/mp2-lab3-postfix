#include "Token.h"
#include <gtest/gtest.h>

TEST(Token, can_create_tokes_maker) {
	ASSERT_NO_THROW(MakeTokens tokensMaker("1+2"));
}

TEST(Token, can_get_top_from_no_empty_string) {
	MakeTokens tokensMaker("1+2");
	ASSERT_EQ(tokensMaker.top(), '1');
}

TEST(Token, can_get_element_from_no_empty_string) {
	MakeTokens tokensMaker("1+2");
	ASSERT_EQ(tokensMaker.get(), '1');
	EXPECT_EQ('+', tokensMaker.top());
}

TEST(Token, returns_true_if_operator) {
	MakeTokens tokensMaker("1+2");
	ASSERT_TRUE(tokensMaker.isOperator('*'));
	ASSERT_TRUE(tokensMaker.isOperator('+'));
	ASSERT_TRUE(tokensMaker.isOperator('-'));
	ASSERT_TRUE(tokensMaker.isOperator('/'));
	ASSERT_TRUE(tokensMaker.isOperator('('));
	ASSERT_TRUE(tokensMaker.isOperator(')'));
}

TEST(Token, returns_false_if_not_operator) {
	MakeTokens tokensMaker("1+2");
	ASSERT_FALSE(tokensMaker.isOperator('7'));
	ASSERT_FALSE(tokensMaker.isOperator('.'));
	ASSERT_FALSE(tokensMaker.isOperator('d'));
}

TEST(Token, returns_true_if_digit) {
	MakeTokens tokensMaker("1+2");
	ASSERT_TRUE(tokensMaker.isDigitOrDot('3'));
}

TEST(Token, returns_true_if_dot) {
	MakeTokens tokensMaker("1+2");
	ASSERT_TRUE(tokensMaker.isDigitOrDot('.'));
	ASSERT_TRUE(tokensMaker.isDigitOrDot(','));
}

TEST(Token, returns_false_if_not_dot_or_digit) {
	MakeTokens tokensMaker("1+2");
	ASSERT_FALSE(tokensMaker.isDigitOrDot('='));
}

TEST(Token, correctly_skip_spaces) {
	MakeTokens tokensMaker("   1+2"); //3 пробела,  pos = 0 после 3
	tokensMaker.skipSpaces();
	ASSERT_EQ('1', tokensMaker.top());
}

TEST(Token, can_correctly_read_number) {
	MakeTokens tokensMaker("100+200");
	ASSERT_EQ("100", tokensMaker.readNumber());
}

TEST(Token, throw_when_two_dot_in_number) {
	MakeTokens tokensMaker("1.0.0+200");
	ASSERT_ANY_THROW(tokensMaker.readNumber());
}

TEST(Token, throw_when_number_end_with_dot) {
	MakeTokens tokensMaker("100.+200");
	ASSERT_ANY_THROW(tokensMaker.readNumber());
}

TEST(Token, throw_when_not_number) {
	MakeTokens tokensMaker("+");
	ASSERT_ANY_THROW(tokensMaker.readNumber());
}

TEST(Token, correctly_make_tokens) {
	MakeTokens tokensMaker("10+24");

	TQueue<Token> tokens = tokensMaker.getTokens();

	Token t1 = tokens.pop();
	EXPECT_TRUE(t1.isNumber);
	EXPECT_EQ("10", t1.val);

	Token t2 = tokens.pop();
	EXPECT_FALSE(t2.isNumber);
	EXPECT_EQ("+", t2.val);

	Token t3 = tokens.pop();
	EXPECT_TRUE(t3.isNumber);
	EXPECT_EQ("24", t3.val);

	EXPECT_TRUE(tokens.isEmpty());
}

TEST(Token, correctly_make_tokens_with_brackets) {
	MakeTokens tokensMaker("5*(6-2)");

	TQueue<Token> tokens = tokensMaker.getTokens();
	std::string expected[] = { "5", "*", "(", "6", "-", "2", ")" };
	bool isNum[] = { true, false, false, true, false, true, false };

	for (int i = 0; i < 7; i++) {
		Token t = tokens.pop();
		EXPECT_EQ(isNum[i], t.isNumber);
		EXPECT_EQ(expected[i], t.val);
	}
}

TEST(Token, throws_when_no_number) {
	MakeTokens tokensMaker("10+a");
	ASSERT_ANY_THROW(tokensMaker.getTokens());
}