#include "Stack.h"
#include <cmath>
#include <string>
#include <iostream>


using namespace std;

void addition(Stack<double> &values) {
	double first = values.pop();
	double second = values.pop();
	values.push(first + second);
}

void subtraction(Stack<double> &values) {
	double first = values.pop();
	double second = values.pop();
	values.push(second - first);
}

void multiplication(Stack<double> &values) {
	double first = values.pop();
	double second = values.pop();
	values.push(first * second);
}

void division(Stack<double> &values, bool &quit) {
	double first = values.pop();
	double second = values.pop();
	if (first == 0) {
		cout << "Error: Division by zero" << endl;
		values.push(second);
		values.push(first);
		return;
	}
	values.push(second / first);
}

void duplicate(Stack<double> &values) {
	double popped = values.pop();
	values.push(popped);
	values.push(popped);
}

void reverse(Stack<double> &values) {
	double first = values.pop();
	double second = values.pop();
	values.push(first);
	values.push(second);
}

void print(Stack<double> &values) {
	cout << values.top() << endl;
}

void clear(Stack<double> &values) {
	while (!values.empty()) {
		values.pop();
	}
}

void all_print(Stack<double> &values) {
	cout << values << endl;
}

void negate_value(Stack<double> &values) {
	double popped = values.pop();
	values.push(-1 * popped);
}

void quit_func(bool &quit) {
	quit = true;
}

void readInOperation(const string &input, Stack<double> &values, bool &quit) {
	if (input == "c") clear(values);
	else if (input == "a") all_print(values);
	else if (input == "q") quit_func(quit);
	else if (input == "p") print(values);
	else if (input == "n") negate_value(values);
	else if (input == "d") duplicate(values);
	else if (input == "+") addition(values);
	else if (input == "-") subtraction(values);
	else if (input == "*") multiplication(values);
	else if (input == "/") division(values, quit);
	else if (input == "r") reverse(values);
	else values.push(stod(input));
}


int main() {
	cout.precision(4);
	Stack<double> values;
	string input;
	bool quit = 0;

	while (cin >> input) {
		readInOperation(input, values, quit);
		if (quit) return 0;
	}
	return 0;
}
