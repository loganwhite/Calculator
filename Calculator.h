// 我真诚地保证：

// 我自己独立地完成了整个程序从分析、设计到编码的所有工作。
// 如果在上述过程中，我遇到了什么困难而求教于人，那么，我将在程序实习报告中
// 详细地列举我所遇到的问题，以及别人给我的提示。

// 在此，我感谢蔡老师对我的启发和帮助。下面的报告中，我还会具体地提到
// 他们在各个方法对我的帮助。

// 我的程序里中凡是引用到其他程序或文档之处，
// 例如教材、课堂笔记、网上的源代码以及其他参考书上的代码段,
// 我都已经在程序的注释里很清楚地注明了引用的出处。

// 我从未没抄袭过别人的程序，也没有盗用别人的程序，
// 不管是修改式的抄袭还是原封不动的抄袭。

// 我编写这个程序，从来没有想过要去破坏或妨碍其他计算机系统的正常运转。

// 冯温迪



#include "DataStructure.h"
#include<string>
#include<iostream>
using namespace DataStructure::LinearSturcture;


//notice: this class specification is from the lecture notes given by teacher.

class Calculator
{
public:
	Calculator();
	void run();
	void clear();
	~Calculator();
private:
	int lp(char op);
	int rp(char op);

	stack<char> optr;//operator stack
	stack<char> openning_stack;//this stack is used for matching brackets
	stack<double> opnd;//number stack
	double value;

	bool isMissNumber(const std::string &str)const;
	bool isMissOptrAmid(const std::string &str)const;
	bool use_brac(const std::string &str)const;
	bool bracMatch(const std::string &str);
	double operate(char theta, double a, double b);
};

Calculator::Calculator()
{//we initialize the class with empty member stack variables, and 
//push a '#' at the bottom of the operator stack.
	while(!optr.empty())
		optr.pop();
	while(!opnd.empty())
		opnd.pop();
	while(!openning_stack.empty())
		openning_stack.pop();
	optr.push('#');
}

void Calculator::clear()
{//this procedure does the exactly the same function as the constructor.
	while(!optr.empty())
		optr.pop();
	while(!opnd.empty())
		opnd.pop();
	while(!openning_stack.empty())
		openning_stack.pop();
	optr.push('#');
}



Calculator::~Calculator()
{//clear the useless data.
	clear();
}


//test if the expression miss numbers.
bool Calculator::isMissNumber(const std::string &str)const
{
	//define a flag,
	bool isMiss = false;
	//auxiliary string used to process the string later.
	std::string processed = "";
	for (int i = 0; i < (int)str.length(); i++)
	{
		//if it is a useless character, omit it.
		if ((str[i] >= 58 && str[i] <= 127) ||
			(str[i] >= 0 && str[i] <= 34)||
			(str[i] >= 36 && str[i] <= 39)||
			(str[i] == 44))
			continue;
		else
			//store the valuable characters into processed.
			processed += str[i];
	}
	//traverse process and find out if there are number before or behind a operator.
	for (int i = 0; i < (int)processed.length(); i++)
	{
		//now i just separate the first char and other chars, 'cause the first has no former elements.
		//if it is not the first
		if (i > 0)
		{
			if ((processed[i] == '+' && (!isdigit(processed[i-1])))||(processed[i] == '+'&&(!isdigit(processed[i+1]))))
			{
				if (processed[i+1]=='(' || processed[i-1] == '(' || processed[i+1] == ')'|| processed[i-1] == ')')
					isMiss = false;
				else
				{
					isMiss = true;
					break;
				}
			}
			if ((processed[i] == '*' && (!isdigit(processed[i-1])))||(processed[i] == '*'&&(!isdigit(processed[i+1]))))
			{
				if (processed[i+1]=='(' || processed[i-1] == '(' || processed[i+1] == ')'|| processed[i-1] == ')')
					isMiss = false;
				else
				{
					isMiss = true;
					break;
				}
			}
			if ((processed[i] == '/' && (!isdigit(processed[i-1])))||(processed[i] == '/'&&(!isdigit(processed[i+1]))))
			{
				if (processed[i+1]=='(' || processed[i-1] == '(' || processed[i+1] == ')'|| processed[i-1] == ')')
					isMiss = false;
				else
				{
					isMiss = true;
					break;
				}
			}
			//because we can calculate negative numbers, so we should treat the
			//'-' operator specially.
			if (processed[i] == '-' && (!isdigit(processed[i-1])))
			{
				isMiss = false;
			}
			if (processed[i] == '-' && (!isdigit(processed[i+1])))
			{
				if (processed[i+1]=='(' || processed[i+1] == ')')
					isMiss = false;
				else
				{
					isMiss = true;
					break;
				}
			}
		}
		//if is the first element
		else
		{
			if (processed[i] == '+' && (!isdigit(processed[i+1])))
			{
				if (processed[i+1]=='(' || processed[i+1] == ')')
					isMiss = false;
				else
				{
					isMiss = true;
					break;
				}
			}
			if (processed[i] == '*' && (!isdigit(processed[i+1])))
			{
				if (processed[i+1]=='(' || processed[i+1] == ')')
					isMiss = false;
				else
				{
					isMiss = true;
					break;
				};
			}
			if (processed[i] == '/' && (!isdigit(processed[i+1])))
			{
				if (processed[i+1]=='('|| processed[i+1] == ')')
					isMiss = false;
				else
				{
					isMiss = true;
					break;
				}
			}
			if (processed[i] == '-' && (!isdigit(processed[i+1])))
			{
				if (processed[i+1]=='(' || processed[i+1] == ')')
					isMiss = false;
				else
				{
					isMiss = true;
					break;
				}
			}
		}
	}
	return isMiss;

}

//find out if there's )( straight forward.
bool Calculator::isMissOptrAmid(const std::string &str)const
{
	std::string::size_type position;
	position = str.find(")(");
	if (position == str.npos)
		return false;
	else
		return true;
}

//this function is used for testing if the express uses brackets
//thus we can decide if it's the brackets errors occur.
bool Calculator::use_brac(const std::string &str)const
{
	bool is_use = false;
	for (int i = 0; i < (int)str.length(); i++)
	{
		if (str[i] == '(' || str[i] == ')')
			is_use = true;
	}
	return is_use;
}

//this function is used for testing if the brackets are matched perfectly
bool Calculator::bracMatch(const std::string &s)
{
	bool isMatch = true;
	for (int i = 0; i < (int)s.length(); i ++)
	{
		//push '(' into the stack
		if (s[i] == '(')
			openning_stack.push(s[i]);
		//when it is ')',test what case it belongs to.
		if (s[i] == ')')
		{
			//if the openning_stack is empty, it means there's no '(' ahead.
			if (openning_stack.empty())
			{
				isMatch = false;
				break;
			}
			else
			{
				//get the top element of openning_stack test if it is '(' matches
				char match;
				openning_stack.top(match);
				openning_stack.pop();
				isMatch = (match == '(');
				if (!isMatch)
					break;
			}
		}
	}
	//if all is tested but the openning_stack is not empty, failed!
	if (!openning_stack.empty())
		isMatch = false;

	return isMatch;
}
//this function is the one who does all most every bit of detailed work.
//and thanks to the teacher had given us the framework.^v^
void Calculator::run()
{
	char ch, op, theta;
	std::string formula;
	double val, a, b;
	int i = 0;
	//These variables are added by me as flags of using brackets or not and whether the brackets using has errors.
	bool ismatch = true,use_bracket = false, ismissop = false, is_lacknum = false;
	std::cin>>formula;
	ismatch = bracMatch(formula);
	use_bracket = use_brac(formula);
	ismissop = isMissOptrAmid(formula);
	is_lacknum = isMissNumber(formula);

	for (int i = formula.length()-1; i >= 0; i--)
	{
		std::cin.putback(formula[i]);
	}
	std::cin>>ch;
	op = '#';
	while(((ch != '#') || (op !='#')))
	{
		////this if statement filtered all the unwanted alphabets.
		if ((ch >= 58 && ch <= 127) ||
			(ch >= 0 && ch <= 34)||
			(ch >= 36 && ch <= 39)||
			(ch == 44))
		{
			
			std::cin>>ch;
		}

		//if the character is a number, then we put it back and reacquire it in the form of number.
		else if(isdigit(ch))
		{
			std::cin.putback(ch);
			std::cin>>val;
			opnd.push(val);
			
			std::cin>>ch;
		}

		//the lp() and rp() function contain all the imformation of operator values.
		//and lp means left operator whose value is the value of an operation when it was pushed into
		//the operator stack and rp() is the the value the operator holds before being pushed into the stack. 
		else if(lp(op) < rp(ch))
		{ 
			optr.push(ch);
			
			std::cin>>ch;
		}
		else if(lp(op) == rp(ch))
		{ 
			optr.pop();
			
			std::cin>>ch;
		}
		else
		{ 
			optr.top(theta);
			optr.pop();
			opnd.top(b);	
			opnd.pop();
			if (opnd.top(a) == DataStructure::underflow)
				a = 0;
			opnd.pop();
			opnd.push(operate(theta,a,b)); 
		}

		optr.top(op);
	}

	double number;
	opnd.top(number);
	if (!ismissop)
	{
		if (!is_lacknum)
		{
			if (use_bracket)
			{
				if (ismatch)
					std::cout<<" "<<'='<<" "<<number<<std::endl;
				else
					std::cout<<"Error, brackets mismatch!"<<std::endl;
			}
			else
				std::cout<<" "<<'='<<" "<<number<<std::endl;
		}
		else
			std::cout<<"Missing Number!"<<std::endl;
	}
	else
		std::cout<<"Missing operator amid ')('"<<std::endl;
}

//simply return the left theta value of a operator.
int Calculator::lp(char op)
{
	int ltheta;
	switch(op)
	{
	case '+':
		ltheta = 3;
		break;
	case '-':
		ltheta = 3;
		break;
	case '*':
		ltheta = 5;
		break;
	case '/':
		ltheta = 5;
		break;
	case '(':
		ltheta = 1;
		break;
	case ')':
		ltheta = 6;
		break;
	case '#':
		ltheta = 0;
		break;
	}
	return ltheta;
}


//simply return the right theta value of a operator.
int Calculator::rp(char op)
{
	int rtheta;
	switch(op)
	{
	case '+':
		rtheta = 2;
		break;
	case '-':
		rtheta = 2;
		break;
	case '*':
		rtheta = 4;
		break;
	case '/':
		rtheta = 4;
		break;
	case '(':
		rtheta = 6;
		break;
	case ')':
		rtheta = 1;
		break;
	case '#':
		rtheta = 0;
		break;
	}
	return rtheta;
}

double Calculator::operate(char theta, double a, double b)
{
	switch(theta)
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		{
			if (b == 0)
			{
				std::cout<<"Error, 0 can not be divided!"<<std::endl;
				return 0;
			}
			else
				return a/b;
		}////////We gotta add some exception handler right here.
	default:
		return INT_MAX;
	}
}