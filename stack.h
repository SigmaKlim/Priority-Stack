#pragma once
#include <iostream>
#include <exception>
template <typename T> class Stack
{
	template <typename T> class StackItem
	{
	public:
		T value;
		StackItem<T>* under;
		StackItem(T value_, StackItem<T>* under_) : value(value_), under(under_) {};
		~StackItem() { under = NULL; };
		void Print() const
		{
			std::cout << value << ' ';
			if (under != NULL)
				under->Print();
		}
	};

	StackItem<T>* top;
	bool isEmpty;
public:
	Stack() : top(NULL), isEmpty(true) {};
	~Stack()
	{
		while (!isEmpty)
			Pop();
		top = NULL;
	}
	void Push(T value_)
	{
		top = new StackItem<T>(value_, top);
		isEmpty = false;
	}
	void Print() const
	{
		top->Print();
	}
	T Pop()
	{
		if (isEmpty)
			throw std::out_of_range("Can't pop from an empty stack");
		T toReturn = top->value;
		StackItem<T>*tmp = top;
		top = tmp->under;
		delete tmp;
		if (!top)
			isEmpty = true;
		return toReturn;
	}
	bool IsEmpty() const { return isEmpty; }

};
