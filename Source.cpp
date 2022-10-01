#include <iostream>
#include "RBpriority_stack.h"
#include "stack.h"

int main()
{
	PriorityStack<int> pS;
	
	pS.Push(12, 12);
	pS.Push(4, 4);
	pS.Push(17, 17);
	pS.Push(3, 3);
	pS.Push(7, 7);
	pS.Push(5, 5);
	pS.Push(9, 9);
	pS.Push(10, 10);
	pS.Push(12, 12);
	std::cout << pS.IsEmpty() << '\n';
	std::cout << pS.Pop() << '\n';
	std::cout  << pS.Pop() << '\n';
	std::cout  << pS.Pop() << '\n';
	std::cout << pS.Pop() << '\n';
	std::cout << pS.Pop() << '\n';
	std::cout << pS.Pop() << '\n';
	std::cout << pS.Pop() << '\n';
	std::cout << pS.Pop() << '\n';
	std::cout << pS.Pop() << '\n';
	//std::cout << pS.Pop() << '\n'; //dвыбросит исключение, так как зафиксируется попытка удалить элемент из пустого стека
	pS.Clear();
	std::cout << pS.IsEmpty() << '\n';
	pS.Push(12, 12);
	pS.Push(4, 4);
	pS.Push(17, 17);
	pS.Push(3, 3);
	pS.Push(7, 7);
	pS.Push(5, 5);
	pS.Push(9, 9);
	pS.Push(10, 10);
	std::cout  << pS.Pop() << '\n';
}
