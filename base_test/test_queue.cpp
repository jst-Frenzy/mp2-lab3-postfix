#include "TQueue.h"
#include <gtest/gtest.h>

TEST(TQueue, can_create_queue_with_positive_length) {
	ASSERT_NO_THROW(TQueue<int> q(5));
}

TEST(TQueue, throws_when_create_queue_with_negative_length)
{
	ASSERT_ANY_THROW(TQueue<int> q(-5));
}

TEST(TQueue, can_create_copied_queue)
{
	TQueue<int> v(10);

	ASSERT_NO_THROW(TQueue<int> v1(v));
}

TEST(TQueue, can_push_and_top_element) {
	TQueue<int> q(10);
	q.push(10);
	EXPECT_EQ(10, q.pop());
}

TEST(TQueue, can_get_correct_size_queue) {
	TQueue<int> q(10);
	q.push(1);
	q.push(2);
	q.push(2);
	q.push(3);
	EXPECT_EQ(4, q.size());
}

TEST(TQueue, throws_when_push_to_full_queue) {
	TQueue<int> q(2);
	q.push(1);
	q.push(2);
	ASSERT_ANY_THROW(q.push(3));
}

TEST(TQueue, can_get_true_if_queue_empty) {
	TQueue<int> q(10);
	EXPECT_TRUE(q.isEmpty());
}

TEST(TQueue, can_get_false_if_queue_not_empty) {
	TQueue<int> q(10);
	q.push(2);
	EXPECT_FALSE(q.isEmpty());
}

TEST(TQueue, can_get_true_if_queue_full) {
	TQueue<int> q(3);
	q.push(1);
	q.push(1);
	q.push(1);
	EXPECT_TRUE(q.isFull());
}

TEST(TQueue, can_get_false_if_queue_not_full) {
	TQueue<int> q(3);
	q.push(2);
	EXPECT_FALSE(q.isFull());
}

TEST(TQueue, can_get_next_index_queue) {
	TQueue<int> q(3);
	EXPECT_EQ(1, q.next(0));
	EXPECT_EQ(2, q.next(1));
	EXPECT_EQ(0, q.next(2));
}

TEST(TQueue, check_fifo_order) {
	TQueue<int> q(5);
	q.push(1);
	q.push(2);
	q.push(3);

	EXPECT_EQ(1, q.pop());
	EXPECT_EQ(2, q.pop());
	EXPECT_EQ(3, q.pop());
}