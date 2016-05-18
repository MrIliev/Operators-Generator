#pragma once
#include <iostream>
#include <fstream>
using namespace std;
#define MAXPRIORITY 10

class Operation  //class representing type of operation with its symbol, sign, prioity and associativity
{
public:
	char symbol,sign;
	int priority;
	bool assoc;
	Operation (char symb, char signn, int prior,bool assocc) : symbol(symb), sign(signn), priority(prior), assoc(assocc){}
	Operation():symbol(NULL), sign(NULL), priority(0){}
	Operation(const Operation& other)
	{
		this->setOperation(other.symbol, other.sign, other.priority, other.assoc);
	}
	void setOperation(char symb, char signn, int prior,bool assocc)
	{
		symbol = symb;
		sign = signn;
		priority = prior;
		assoc = assocc;
	}
};



Operation* getOperationsFromFile(int& counter,const char* fileName) // reading operations from file and returns array of operations readen from file and how much are they
{
	int operationsCounter = 0;  //used to count number of different operations when read it from file
	ifstream file;
	file.open(fileName,ios::in);
	char tmp[10];
	if(file)
	{
		while (file.getline(tmp, 10))
		{
			operationsCounter++;
		}
		char symbol, sign;
		int priority;
		bool assocc;
		Operation* buff = new Operation[operationsCounter];
		file.clear();
		file.seekg(0,file.beg);
		for (int i = 0; i < operationsCounter; ++i)
		{
			file>>symbol>>sign>>priority>>assocc;
			if (priority > MAXPRIORITY)
			{
				priority = MAXPRIORITY;
			}
			buff[i].setOperation(symbol,sign,priority,assocc);
		}
		counter = operationsCounter;
		return buff;

	}
	else
	{
		cout<<"File error"<<endl;
		return NULL;
	}



}
bool isDefinedOperation (Operation* array, int size, char c) // function used to chek if one operation is in array with operations
{
	for(int i = 0;i < size; ++i)
	{
		if (c ==  array[i].symbol)
		{
			return true;
		}
	}
	return false;
}
Operation converter(Operation* array, int size, char c) // converts one char into operation if operation exists
{
	for(int i = 0;i < size; ++i)
	{
		if (c == array[i].symbol)
		{
			return array[i];
		}
		if(c == '(' )
			return *new Operation(c,' ',0,0);
		if(c == ')' )
			return *new Operation(c,' ',0,0);
	}
}

double useOperation(double num1, double num2, Operation op) // function used to calculate with operation
{
	switch (op.sign)
	{
	case '+':
		return num1 + num2;
	case '-':
		return num1 - num2;
	case '*':
		return num1 * num2;
	case '/':
		return num1 / num2;
	default:
		break;
	}
}
