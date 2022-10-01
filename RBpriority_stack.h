#pragma once
#include <limits>
#include "stack.h"
template <typename T> class PriorityStack
{
	template <typename T> class PriorityStackItem
	{
	public:
		Stack<T>* item;
		int priority;
		bool isRed;
		PriorityStackItem<T>* parent;
		PriorityStackItem<T>* childLeft;
		PriorityStackItem<T>* childRight;

		PriorityStackItem(int priority_)
		{
			priority = priority_;
			item = new Stack<T>();
			isRed = true;
			parent = NULL;
			childLeft = NULL;
			childRight = NULL;
		}
		~PriorityStackItem()
		{
			Clear();
		} 
		void Push(T value_)
		{
			item->Push(value_);
		}
		T Pop()
		{
			return item->Pop();
		}
		void Clear()
		{
			delete item;
			item = NULL;
			if (parent)
				if (this == parent->childLeft)
					parent->childLeft = NULL;
				else if (this == parent->childRight)
					parent->childRight = NULL;
			childLeft = NULL;
			childRight = NULL;
			parent = NULL;
		}
		void ClearAll()
		{
			if (childLeft)
				childLeft->Clear();
			if (childRight)
				childRight->Clear();
			Clear();
		}
	};

	PriorityStackItem<T>* top;
	bool isEmpty;
	PriorityStackItem<T>* separator;

	void RotateLeft(PriorityStackItem<T>* pivot)
	{
		PriorityStackItem<T>* pivotChildToRotate = pivot->childRight;
		pivot->childRight = pivotChildToRotate->childLeft;
		if (pivot->childRight != separator)
			pivot->childRight->parent = pivot;
		if (pivot == top)
			top = pivotChildToRotate;
		else if (pivot->parent->childLeft == pivot)
			pivot->parent->childLeft = pivotChildToRotate;
		else
			pivot->parent->childRight = pivotChildToRotate;
		pivotChildToRotate->parent = pivot->parent;
	
		pivotChildToRotate->childLeft = pivot;
		pivot->parent = pivotChildToRotate;
	}
	void RotateRight(PriorityStackItem<T>* pivot)
	{
		PriorityStackItem<T>* pivotChildToRotate = pivot->childLeft;
		pivot->childLeft = pivotChildToRotate->childRight;
		if (pivot->childLeft != separator)
			pivot->childLeft->parent = pivot;
		if (pivot == top)
			top = pivotChildToRotate;
		else if (pivot->parent->childLeft == pivot)
			pivot->parent->childLeft = pivotChildToRotate;
		else
			pivot->parent->childRight = pivotChildToRotate;
		pivotChildToRotate->parent = pivot->parent;
		
		pivotChildToRotate->childRight = pivot;
		pivot->parent = pivotChildToRotate;
	}
	void RepairAfterPush(PriorityStackItem<T>* toRepair)
	{
		while (toRepair->parent->isRed)
			if (toRepair->parent == toRepair->parent->parent->childLeft)
			{
				PriorityStackItem<T>* uncle = toRepair->parent->parent->childRight;
				if (uncle->isRed)
				{
					toRepair->parent->isRed = false;
					uncle->isRed = false;
					uncle->parent->isRed = true;
					toRepair = uncle->parent;
				}
				else
				{
					if (toRepair == toRepair->parent->childRight)
					{
						toRepair = toRepair->parent;
						RotateLeft(toRepair);
					}
					toRepair->parent->isRed = false;
					uncle->parent->isRed = true;
					RotateRight(uncle->parent);
				}
			}
			else
			{
				PriorityStackItem<T>* uncle = toRepair->parent->parent->childLeft;
				if (uncle->isRed)
				{
					toRepair->parent->isRed = false;
					uncle->isRed = false;
					uncle->parent->isRed = true;
					toRepair = uncle->parent;
				}
				else
				{
					if (toRepair == toRepair->parent->childLeft)
					{
						toRepair = toRepair->parent;
						RotateRight(toRepair);
					}
					toRepair->parent->isRed = false;
					uncle->parent->isRed = true;
					RotateLeft(uncle->parent);
				}
			}
		top->isRed = false;
	}
	void RepairAfterPop(PriorityStackItem<T>* toRepair)
	{
		if (toRepair == top || toRepair->isRed)
			return;
			
		PriorityStackItem<T>* sibling = toRepair->parent->childLeft;
		if (sibling == toRepair)
			throw std::out_of_range("Sibling == toRepair");
		PriorityStackItem<T>* nephewLeft = sibling->childLeft;
		PriorityStackItem<T>* nephewRight = sibling->childRight;
		if (!sibling->isRed)
		{
			if (nephewLeft->isRed)
			{
				sibling->isRed = sibling->parent->isRed;
				sibling->parent->isRed = false;
				nephewLeft->isRed = false;
				RotateRight(sibling->parent);
			}
			else if (nephewRight->isRed)
			{
				sibling->isRed = true;
				nephewRight->isRed = false;
				RotateLeft(sibling);
				RepairAfterPop(toRepair);
			}
			else
			{
				sibling->isRed = true;
				bool parentWasRed = sibling->parent->isRed;
				sibling->parent->isRed = false;
				if (!parentWasRed)
					RepairAfterPop(sibling->parent);
			}
		}
		else
		{
			sibling->parent->isRed = true;
			sibling->isRed = false;
			RotateRight(sibling->parent);
			RepairAfterPop(toRepair);
		}
	}
public:
	PriorityStack() 
	{
		separator = new PriorityStackItem<T>(INT_MIN);
		separator->isRed = false;
		separator->childLeft = NULL;
		separator->childRight = NULL;
		top = NULL;
		isEmpty = true;
	};
	~PriorityStack()
	{
		Clear();
		delete separator;
	}
	void Push(int priority, T value)
	{
		PriorityStackItem<T>* son;
		if (isEmpty)
		{
			top = new PriorityStackItem<T>(priority);
			top->isRed = false;
			top->parent = separator;
			top->childLeft = separator;
			top->childRight = separator;
			son = top;
			isEmpty = false;
		}
		else
		{
			son = top;
			PriorityStackItem<T>* father = top;
			bool foundCopy = false;
			while (son != separator)
			{
				father = son;
				if (priority < son->priority)
					son = son->childLeft;
				else if (priority == son->priority)
				{
					foundCopy = true;
					break;
				}
				else
					son = son->childRight;
			}
			if (!foundCopy)
			{
				if (priority < father->priority)
				{
					father->childLeft = new PriorityStackItem<T>(priority);
					son = father->childLeft;
				}
				else
				{
					father->childRight = new PriorityStackItem<T>(priority);
					son = father->childRight;
				}
				son->parent = father;
				son->childLeft = separator;
				son->childRight = separator;
				RepairAfterPush(son);
			}
		}
		son->Push(value);
	}
	T Pop()
	{
		if (isEmpty)
			throw std::out_of_range("Attempted to pop from an empty stack!");
		PriorityStackItem<T>* toDelete = top;
		while (toDelete->childRight != separator)
			toDelete = toDelete->childRight;
		T toReturn = toDelete->Pop();
		if (toDelete->item->IsEmpty())
		{
			if (toDelete->childLeft->isRed)
			{
				toDelete->parent->childRight = toDelete->childLeft;
				toDelete->childLeft->parent = toDelete->parent;
				toDelete->childLeft->isRed = false;
			}
			else
			{
				RepairAfterPop(toDelete);
				toDelete->parent->childRight = separator;
			}
			if (toDelete == top)
				if (top->childLeft != separator)
				{
					top = top->childLeft;
					delete toDelete;
				}
				else
					Clear();
		}
		return toReturn;
	}
	void Clear()
	{
		top->ClearAll();
		isEmpty = true;
	}
	bool IsEmpty()
	{
		return isEmpty;
	}
};

