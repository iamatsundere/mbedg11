#include <iostream>
using namespace std;
int main() {
	int a,b,c,d;
	a=10;
	b=13;
	c=a|b;
	d=a&b;
	cout<<"a "<<a<<" ~a "<<~a<<endl;
	cout<<"b "<<b<<" ~b "<<~b<<endl;
	cout<<(10|12)<<" "<<~13<<endl;
	
	//a|b=bonus bits from a to b: 1+1=1; 1+0=1; 0+0=0
	//~a=(a+1)*-1
	
	cout<<"a|b "<<(a|b)<<" a|~b "<<(a|~b)<<endl;
	cout<<"b|a "<<(b|a)<<" b|~a "<<(b|~a)<<endl;
	cout<<"a&b "<<(a&b)<<" a&~b "<<(a&~b)<<endl;
	cout<<"b&a "<<(b&a)<<" a&~b "<<(b&~a)<<endl;
}