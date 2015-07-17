#include <iostream>

using namespace std;

class A {

public:
	int m;

	A() {
		m = 0;
	}

};

class B {

private:
static A m_a;

public:
	A& a() {
return m_a;
}

};

A B::m_a;

int main() {

	B b;
	cout<<b.a().m<<endl;

	B b1;
	
	A aa = b1.a();
	aa.m = 100;
	
cout<<b.a().m<<endl;
cout<<b1.a().m<<endl;
	
}
