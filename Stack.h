#pragma once 
#include <iostream>

template <typename T>        //classic stack structure used in function calculateExpression
struct Node
{
public:
	T data;
	Node<T>* next;
	
	Node<T>(T elem) : next(NULL), data(elem) {}


};

template <typename T>
class Stack
{
private:
	Node<T>* top;
	int size;

public:
	bool isEmpty()
	{
		return (size == 0);
	}
	Stack(): top(NULL), size(0) {}
	~Stack()
	{
		delete [] top;
	}
	void push(T elem)
	{
		Node<T>* tmp = new Node<T> (elem);
		if (isEmpty())
		{
			top = tmp;
			size = 1;

		}
		else
		{
			tmp->next = top;
			top = tmp;
			size++;
		}
//		cout<<"Element added! Top element : "<<get_topData()<<"Number of elements: "<<get_size()<<endl;
	}

	T pop()
	{
		if (isEmpty())
		{
		}
		else if(size == 1 )
		{
			T tmp = top->data;
			delete top;
			top = NULL;
			size--;
			return tmp ;
			
		}
		else
		{
			Node<T>* tmp = top;
			T exmp = top->data;
			top = top->next;
			tmp->next = NULL;
			delete tmp;
			size--;
			return exmp;
		}
	}
	int get_size()
	{
		return size;
	}
	T Top()
	{
		return top->data;
	}
};

