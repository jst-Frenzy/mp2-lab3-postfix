#include "TStack.h"
#include <gtest/gtest.h>

TEST(TVectorStack, can_create_stack) {
	ASSERT_NO_THROW(TVectorStack<char> st);
}

TEST(TVectorStack, can_push_and_top_element) {
	TVectorStack<int> st;
	st.Push(10);
	EXPECT_EQ(10, st.Top());
}

TEST(TVectorStack, can_pop_element) {
	TVectorStack<int> st;
	st.Push(10);
	st.Push(12);

	st.Pop();

	EXPECT_EQ(10, st.Top());
}

TEST(TVectorStack, can_get_true_if_stack_empty) {
	TVectorStack<int> st;
	EXPECT_EQ(true, st.IsEmpty());
}

TEST(TVectorStack, can_get_false_if_stack_not_empty) {
	TVectorStack<int> st;
	st.Push(2);
	EXPECT_EQ(false, st.IsEmpty());
}

TEST(TVectorStack, can_get_correct_size) {
	TVectorStack<int> st;
	st.Push(1);
	st.Push(2);
	st.Push(3);
	EXPECT_EQ(3, st.size());
}