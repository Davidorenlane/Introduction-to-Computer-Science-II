#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;


bool isValidString(string infix);

int evaluate(string infix, string& postfix, bool& result) {
	if (!isValidString(infix))
		return 1;
	postfix = "";
	stack<char> opstack;
	for (int i = 0; i < infix.size(); i++)
		switch (infix[i]) {
		case ' ':
			break;
		case 'T':
			postfix += infix[i];
			break;
		case 'F':
			postfix += infix[i];
			break;
		case '(':
			opstack.push(infix[i]);
			break;
		case ')':
			// pop stack until matching '('
			while (opstack.top() != '(') {
				postfix += opstack.top();
				opstack.pop();
			}
			opstack.pop();  // remove the '('
			break;
		case '!':
			while (!opstack.empty() && opstack.top() != '(' && opstack.top() == '!') {//the stack is not empty and the stack top is not '('
				//and precedence of ch <= precedence of stack top
				postfix += opstack.top();// append the stack top to postfix
				opstack.pop();
			}
			opstack.push('!');
			break;
		case '&':
			while (!opstack.empty() && opstack.top() != '(' && (opstack.top() == '!' || opstack.top() == '&')) {//the stack is not empty and the stack top is not '('
																					  //and precedence of ch <= precedence of stack top
				postfix += opstack.top();// append the stack top to postfix
				opstack.pop();
			}
			opstack.push('&');
			break;
		case '|':
			while (!opstack.empty() && opstack.top() != '(' && (opstack.top() == '!' || opstack.top() == '&' || opstack.top() == '|')) {//the stack is not empty and the stack top is not '('
																											  //and precedence of ch <= precedence of stack top
				postfix += opstack.top();// append the stack top to postfix
				opstack.pop();
			}
			opstack.push('|');
			break;
		}
	while (!opstack.empty()) {//While the stack is not empty
		postfix += opstack.top();	//append the stack top to postfix
		opstack.pop();
	}
	char op1;
	char op2;
	for (int i = 0; i < postfix.size(); i++)//For each character ch in the postfix string
		if (postfix[i] == 'T' || postfix[i] == 'F')//ch is an operand
			opstack.push(postfix[i]);// the value that ch represents onto the operand stack
		else // ch is a binary operator
		{
			if (postfix[i] == '!') {
				if (opstack.top() == 'T') {
					opstack.pop();
					opstack.push('F');
				}
				else if (opstack.top() == 'F') {
					opstack.pop();
					opstack.push('T');
				}
			}
			if (postfix[i] == '&') {
				op2 = opstack.top();
				opstack.pop();
				op1 = opstack.top();
				opstack.pop();
				if (op1 == op2 && op1 == 'T')
					opstack.push('T');
				else
					opstack.push('F');
			}
			if (postfix[i] == '|') {
				op2 = opstack.top();
				opstack.pop();
				op1 = opstack.top();
				opstack.pop();
				if (op1 == op2 && op1 == 'F')
					opstack.push('F');
				else
					opstack.push('T');
			}
		}
	if (opstack.top() == 'T')
		result = true;
	if (opstack.top() == 'F')
		result = false;
	return 0;
}

bool isValidString(string infix) {
	string noSpaces = "";
	for (int i = 0; i < infix.size(); i++) {
		if (infix[i] != ' ' && infix[i] != '|' && infix[i] != '&' && infix[i] != '!' && infix[i] != '(' && infix[i] != ')' && infix[i] != 'T' && infix[i] != 'F')
			return false;
		if (infix[i] != ' ')
			noSpaces += infix[i];
	}
	if (noSpaces == "")
		return false;

	int numOpen = 0;
	int numClose = 0;
	for (int i = 0; i < noSpaces.size(); i++) {
		if (noSpaces[i] == ')') {
			numClose++;
			if (i != noSpaces.size() - 1)
				if (noSpaces[i + 1] != ')' && noSpaces[i + 1] != '|' && noSpaces[i + 1] != '&')
					return false;
		}
		if (noSpaces[i] == '(') {
			numOpen++;
			if (i < noSpaces.size() - 1)
				if (noSpaces[i + 1] != '!' && noSpaces[i + 1] != 'T' && noSpaces[i + 1] != 'F' && noSpaces[i + 1] != '(')
					return false;
		}
		if (noSpaces[i] == 'T') {
			if (i < noSpaces.size() - 1)
				if (noSpaces[i + 1] == '!' || noSpaces[i + 1] == 'T' || noSpaces[i + 1] == 'F' || noSpaces[i + 1] == '(')
					return false;
		}
		if (noSpaces[i] == 'F') {
			if (i != noSpaces.size() - 1)
				if (noSpaces[i + 1] == '!' || noSpaces[i + 1] == 'T' || noSpaces[i + 1] == 'F' || noSpaces[i + 1] == '(')
					return false;
		}
		if (noSpaces[i] == '!') {
			if (i == noSpaces.size() - 1)
				return false;
			if (i != noSpaces.size() - 1)
				if (noSpaces[i + 1] != '!' && noSpaces[i + 1] != 'T' && noSpaces[i + 1] != 'F' && noSpaces[i + 1] != '(')
					return false;
		}
		if (noSpaces[i] == '|') {
			if (i == noSpaces.size() - 1)
				return false;
			if (i != noSpaces.size() - 1)
				if (noSpaces[i + 1] != '!' && noSpaces[i + 1] != 'T' && noSpaces[i + 1] != 'F' && noSpaces[i + 1] != '(')
					return false;
			int TF = 0;
			for (int j = 0; j < i; j++) {
				if (noSpaces[j] == 'T' || noSpaces[j] == 'F')
					TF++;
				if (noSpaces[j] == '|' || noSpaces[j] == '&')
					TF--;
			}
			if (TF != 1)
				return false;
			for (int j = i + 1; j < noSpaces.size(); j++) {
				if (noSpaces[j] == 'T' || noSpaces[j] == 'F')
					TF++;
				if (noSpaces[j] == '|' || noSpaces[j] == '&')
					TF--;
			}
			if (TF != 2)
				return false;
		}
		if (noSpaces[i] == '&') {
			if (i == noSpaces.size() - 1)
				return false;
			if (i != noSpaces.size() - 1)
				if (noSpaces[i + 1] != '!' && noSpaces[i + 1] != 'T' && noSpaces[i + 1] != 'F' && noSpaces[i + 1] != '(')
					return false;
			int TF = 0;
			for (int j = 0; j < i; j++) {
				if (noSpaces[j] == 'T' || noSpaces[j] == 'F')
					TF++;
				if (noSpaces[j] == '|' || noSpaces[j] == '&')
					TF--;
			}
			if (TF != 1)
				return false;
			for (int j = i + 1; j < noSpaces.size(); j++) {
				if (noSpaces[j] == 'T' || noSpaces[j] == 'F')
					TF++;
				if (noSpaces[j] == '|' || noSpaces[j] == '&')
					TF--;
			}
			if (TF != 2)
				return false;
		}
		if (numClose > numOpen)
			return false;
		if (i == noSpaces.size() - 1)
			if (numOpen != numClose)
				return false;
	}
	return true;
}

int main() {

}