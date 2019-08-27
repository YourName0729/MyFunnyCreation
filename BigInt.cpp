#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;


#define UpperBound 300

class BigInt {
public:
	BigInt() {
		init();
	}
	
	int size() const {
		return s;
	}
	
	void clear() {
		for (int i = 0; i < s; i++) {
			a[i] = 0;
		}
		s = 0;
	}
	
	BigInt& operator=(BigInt& b) {
		clear();
		
		for (int i = 0; i < b.size(); i++) {
			a[i] = b.a[i];
		}
		s = b.size();
		
		return *this;
	}
	
	BigInt& operator=(int d) {
		clear();
		
		a[0] = d;
		carry(0);
		
		return *this;
	}
	
	BigInt& operator+=(const BigInt& b) {
		buf.clear();
		
		for (int i = 0; i < max(size(), b.size()); i++) {
			buf.a[i] += a[i] + b.a[i];
			buf.carry(i);
		}
		
		operator=(buf);
		
		return *this;
	}
	
	BigInt& operator+=(const int d) {
		BigInt b;
		b = d;
		return operator+=(b);
	}
	
	BigInt& operator*=(const BigInt& b) {
		buf.clear();
		
		for (int i = 0; i < size(); i++) {
			for (int j = 0; j < b.size(); j++) {
				buf.a[i + j] += a[i] * b.a[j];
				buf.carry(i + j);
			}
		}
		
		operator=(buf);
		
		return *this;
	}
	
	BigInt& operator*=(const int d) {
		BigInt b;
		b = d;
		return operator*=(b);
	}
	
	friend ostream& operator<<(ostream& out, const BigInt& b) {
		int idx = b.size();
		if (idx <= 1 && b.a[0] == 0) {
			out << '0';
			return out;
		}
		
		int p;
		
		out << b.a[idx - 1];
		for (int i = idx - 2; i >= 0; i--) {
			p = Unit / 10;
			while (p != 0 && b.a[i] / p == 0) {
				out << '0';
				p /= 10;
			}
			if (p)	out << b.a[i];
		}
		
		return out;
	}
private:
	void init() {
		a = new unsigned long long[UpperBound];
		for (int i = 0; i < UpperBound; i++) {
			a[i] = 0;
		}
		s = 0;
	}
	
	void carry(int dgt) {
		if (a[dgt] == 0)	return;
		
		s = max(s, dgt + 1);
		
		if (a[dgt] < Unit)	return;
		
		//s = max(s, dgt + 2);
		
		a[dgt + 1] += a[dgt] / Unit;
		a[dgt] %= Unit;
		carry(dgt + 1);
	}
	
	
	unsigned long long *a = NULL;
	int s;
	
	static BigInt buf;
	
	static const unsigned long long Unit = 1000000000;
	static const int Pow = 9;
};

BigInt BigInt::buf;

int main() {

	BigInt a;
	
	a = 1;

	for (int i = 1; i <= 100; i++) {
		a *= i;
		cout << a << '\n';
	}

	return 0;
}

