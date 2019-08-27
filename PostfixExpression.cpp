#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <stack>

using namespace std;

int pfex(stringstream& ss) {
	stack<int> stk;
	string stmp;
	
	while (ss >> stmp) {
		if (stmp == "+" || stmp == "-" || stmp == "*" || stmp == "/" || stmp == "%") {
			int d1, d2;
			if (stk.size() < 2)	throw ' ';
			d2 = stk.top();
			stk.pop();
			d1 = stk.top();
			stk.pop();
			
			char oprt = stmp[0];
			
			switch(oprt) {
				case '+':
					stk.push(d1 + d2);
					break;
				case '-':
					stk.push(d1 - d2);
					break;
				case '*':
					stk.push(d1 * d2);
					break;
				case '/':
					if (d2 == 0)	throw '/';
					stk.push(d1 / d2);
					break;
				case '%':
					if (d2 == 0)	throw '%';
					stk.push(d1 % d2);
					break;
			}
		}
		else {
			int d = stod(stmp);
			
			stk.push(d);
		}
	}
	
	if (stk.size() != 1) throw '1';
	
	return stk.top();
}

int main() {

	string s;
	while (getline(cin, s)) {
		stringstream ss;
		ss << s;
		
		try {
			cout << pfex(ss) << '\n';
		}
		catch(char c) {
			cout << "illegal\n";
		}
	}

	return 0;
}

