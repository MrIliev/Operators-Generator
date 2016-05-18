#include <iostream>
using namespace std;
#include "Stack.h"
#include "Operation.h"

double calculateExpression(char* filename, char* expression) //function is used to calculate expression-- here we get operations from file and use it in expression 
{
	Operation* buff;
	int buffcount;
	buff = getOperationsFromFile(buffcount,filename);
	Stack<Operation> operations;
	Stack<double> nums;
	
	int i=0;
	while (expression[i])
	{
		if (expression[i] == ' ')
		{
			if ( (expression[i+1]>='0' && expression[i+1]<='9') || expression[i+1] == '-')
			{
				double helper = atof(expression + i);
				nums.push(helper);
				int j = i + 1, count = 0;
				while (expression[j] != ' ')
				{
					// Validation about the numbers
					if( !(expression[j] >= '0' || expression[j] <= '9')  && expression[j] != '-' )
					
					{
						cout << "Incorrect input. There are symbols just after a digit."<<endl
							 << " Please put white spaces between the numbers, operations and brackets."<<endl;
						return 0;
					} 
					j++;
					count++;
				}
				i += count;
			}
			else if (isDefinedOperation(buff,buffcount,expression[i+1]))
			{
				while (!operations.isEmpty())
				{
					Operation op = operations.Top();
					if (op.priority < converter(buff, buffcount,expression[i+1]).priority)
						break;
					else if(op.priority == converter(buff, buffcount,expression[i+1]).priority)
					{
						if(converter(buff, buffcount,expression[i+1]).assoc != op.assoc)
						{
							cout << "The expresion is invalid, there are two operators with the same priority and diferent accociativity."<<endl;
							return 0;
						}
						if(converter(buff, buffcount,expression[i+1]).assoc)
							break;
						else
							nums.push(useOperation(nums.pop(),nums.pop(),operations.pop()));
					}
					else
						nums.push(useOperation(nums.pop(),nums.pop(),operations.pop()));
				}
				operations.push(converter(buff, buffcount,expression[i+1]));
			}
			else if(expression[i+1] == '(')
				operations.push(converter(buff, buffcount, '('));
			else if(expression[i+1] == ')')
			{
				Operation c;
				while( (c=operations.pop()).symbol != '(')
					nums.push(useOperation(nums.pop(),nums.pop(),c));
			}
		}
		i++;
	}
	while (!operations.isEmpty())
	{
		nums.push(useOperation(nums.pop(),nums.pop(),operations.pop()));
	}
	return nums.pop();
}


int main()
{
	double a = calculateExpression("rules.txt", " 31 a ( 5 b 32 f 10 e -230 ) c 324 d 19");
	cout<<a;

	return 0;
}