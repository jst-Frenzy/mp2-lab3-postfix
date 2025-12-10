#ifndef __TSTACK_H__
#define __TSTACK_H__

#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class TVectorStack {
	int top;
	vector<T> mem;
public:
	TVectorStack() : top(-1){}

	size_t size() const {
		return top + 1;
	}

	bool IsEmpty() const {
		return top == -1;
	}

	void Push(const T& val) {
		mem.push_back(val);
		top++;
	}

	void Pop() {
		mem.pop_back();
		top--;
	}

	T Top() {
		return mem[top];
	}
};

#endif