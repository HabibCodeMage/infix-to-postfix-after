// infix to postfix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include"stackarray.h"
#include<sstream>
using namespace std;
string tobereturn;
bool flag = false;
void higherpriority(char value, stackarray<char>& object);
void samepriority(char value, stackarray<char>& object);
void lowerpriority(char value, stackarray<char>& object);
string postfix(string&);
int evaluationofposfix();
int main()
{
	
    string input;
	cout << "enter infix expression:";
    getline(cin, input, '\n');
	cout<<postfix(input);
	cout << tobereturn<<endl;// fine conversion
	cout << evaluationofposfix();                          //push string in stackarray class 
}
string postfix(string& input)
{
	stackarray<char> object;
	for (size_t i = 0; i < input.length(); i++)
	{
		if (isalpha(input[i]) || isdigit(input[i]))
			tobereturn += input[i];
		else if (input[i] == '*' || input[i] == '+' || input[i] == '-' || input[i]=='/' || input[i]=='(' )   
		{
			if (object.empty())
			{
				object.push(input[i]);
			}
			else if(input[i]=='(')
				object.push(input[i]);
		    else
              lowerpriority(input[i],object);
		}
		else if (input[i] == ')')
		{
			if(!object.empty())
			{ 

				while (object.top()!='(')
				{
					tobereturn +=object.top();
					object.pop();
				}
				object.pop();
			}
		}
		
	}
	while (!object.empty())
	{
		tobereturn += object.top();
		object.pop();

	}
	return " ";
}
int evaluationofposfix()
{
	stackarray<string>obj;
	for (size_t i = 0; i < tobereturn.length(); i++)
	{
		if (isdigit(tobereturn[i]))
		{
			string v (1, tobereturn[i]);
			obj.push(v); 
		}
		else if(tobereturn[i]=='+')
		{
			int value1 = stoi(obj.top(),nullptr,10);
			obj.pop();
			int value2= stoi(obj.top(), nullptr, 10);
			obj.pop();
			value1=value2 + value1;
			obj.push(std::to_string(value1));
		}
		else if (tobereturn[i] == '-')
		{
			int value1 = stoi(obj.top(), nullptr, 10);
			obj.pop();
			int value2 = stoi(obj.top(), nullptr, 10);
			obj.pop();
			value1 = value2 - value1;
			obj.push(std::to_string(value1));
		}
		else if (tobereturn[i] == '*')
		{
			int value1 = stoi(obj.top(), nullptr, 10);
			obj.pop();
			int value2 = stoi(obj.top(), nullptr, 10);
			obj.pop();
			value1 = value2 * value1;
			obj.push(std::to_string(value1));
		}
		else if (tobereturn[i] == '/')
		{
			int value1 = stoi(obj.top(), nullptr, 10);
			obj.pop();
			int value2 = stoi(obj.top(), nullptr, 10);
			obj.pop();
			value1 = value2 / value1;
			obj.push(std::to_string(value1));
		}

	}
	return  stoi(obj.top(), nullptr, 10);
}
void higherpriority(char value, stackarray<char>& object)
{
	while (flag != true)
	{
		tobereturn += object.top();
		object.pop();
		lowerpriority(value, object);
	}
}
void samepriority(char value, stackarray<char>& object)
{
	tobereturn += object.top();
	object.pop();
	object.push(value);
	flag = true;
}
void lowerpriority(char value, stackarray<char>& object)
{
	flag = false;
	if (value == object.top())
		samepriority(value, object);
	else if (object.top() == '(')
	{
		object.push(value);
		flag = true;
	}
	else if (value == '*' &&  object.top()=='/')
		samepriority(value,object);
	else if (value == '/' &&  object.top()=='*')
		samepriority(value, object);
	else if (value == '+' &&  object.top()=='-')
		samepriority(value, object);
	else if (value == '-'&& object.top()=='+')
	{
	   samepriority(value, object);
	}
	else if (value == '*' && '*' < object.top())
	{
		object.push('*');
		flag = true;
	}
	else if (value == '/' && '/' > object.top())
	{
		object.push('/');
			flag = true;
	}
	else
	{
		higherpriority(value, object);
	}
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
