#include "stdafx.h"
#include <stack>
#include <vector>
#include <iostream>
#include "stdlib.h"
#include <ctime>
#include <string>
#include "Calculator.h"

#define random(a,b) (rand()%(b-a+1)+a)

using namespace std;

Calculator::Calculator() {}

string Calculator::MakeFormula() {
	string formula = "";
	srand((unsigned int)time(NULL));
	int count = random(2, 3);
	int start = 0;
	int number1 = random(1, 100);
	formula += to_string(number1);
	int first;
	first = number1;
	while (start < count) {
		int operation = random(0, 3);
		int number2 = random(1, 100);

		if (operation == 1 || operation == 2) {
			first = number2;
		}
		else if(operation==3){
			cout << "first=" << first << "number2= " << number2 << endl;
			bool flag = true;
			if (first%number2 == 0) {
				first = first / number2;
				flag = false;
			}
			while (flag) {
				//除了之后有小数重新生成

				//方法一：只重新生成数字 （有的情况循环次数会比较多）
				number2 = random(1, 100);
				if (first%number2 == 0) {
					first = first / number2;
					flag = false;
				}
				cout << "first=" << first << "number2= " << number2 << endl;

				//方法二：运算符也重新生成
				/* 
				operation = random(0, 3);
				number2 = random(1, 100);
				if (operation == 0 || operation == 1) {
					first = number2;
					flag = false;
				}
				else if (operation == 2) {
					first = first*number2;
					flag = false;
				}
				else {
					if (first%number2 == 0) {
						flag = false;
					}
				}*/
			}
		}
		else {
			first = first*number2;
		}
		formula += op[operation] + to_string(number2);
		start++;
	}
	return formula;
};

string Calculator::Solve(string formula) {
	vector<string>* tempStack = new vector<string>();
	stack<char>* operatorStack = new stack<char>();
	int len = formula.length();
	int k = 0;
	for (int j = -1; j < len - 1; j++) {
		char formulaChar = formula[j + 1];
		if (j == len - 2 || formulaChar == '+' || formulaChar == '-' ||
			formulaChar == '*' || formulaChar == '/') {
			if (j == len - 2) {
				tempStack->push_back(formula.substr(k));
			}
			else {
				if (k < j) {
					tempStack->push_back(formula.substr(k, j + 1));
				}
				if (operatorStack->empty()) {
					operatorStack->push(formulaChar);
				}
				else {
					char stackChar = operatorStack->top();
					if ((stackChar == '+' || stackChar == '-')
						&& (formulaChar == '*' || formulaChar == '/')) {
						operatorStack->push(formulaChar);
					}
					else {
						tempStack->push_back(to_string(operatorStack->top()));
						operatorStack->pop();
						operatorStack->push(formulaChar);
					}
				}
			}
			k = j + 2;
		}
	}
	while (!operatorStack->empty()) {
		tempStack->push_back(string(1, operatorStack->top()));
		operatorStack->pop();
	}
	stack<string>* calcStack = new stack<string>();
	for (int i = 0; i < tempStack->size(); i++) {
		string peekChar = tempStack->at(i);
		if (peekChar != "+" && peekChar != "-"
			&& peekChar != "/" && peekChar != "*") {
			calcStack->push(peekChar);
		}
		else {
			int a1 = 0;
			int b1 = 0;
			if (!calcStack->empty()) {
				b1 = stoi(calcStack->top());
				calcStack->pop();
			}
			if (!calcStack->empty()) {
				a1 = stoi(calcStack->top());
				calcStack->pop();
			}
			if (peekChar == "+") {
				calcStack->push(to_string(a1 + b1));
			}
			else if (peekChar == "-") {
				calcStack->push(to_string(a1 - b1));
			}
			else if (peekChar == "*") {
				calcStack->push(to_string(a1 * b1));
			}
			else if (peekChar == "/") {
				calcStack->push(to_string(a1 / b1));
			}
		}
	}
	return formula + "=" + calcStack->top();
}

int main()
{
	Calculator* calc = new Calculator();
	string question = calc->MakeFormula();
	cout << question << endl;
	string ret = calc->Solve(question);
	cout << ret << endl;
	getchar();
}


