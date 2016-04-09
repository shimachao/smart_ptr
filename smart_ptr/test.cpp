#include "smart_ptr.h"
#include <iostream>
using std::cout;
using std::endl;

struct MyStruct
{
	MyStruct() = default;
	MyStruct(int a, int b) :a(a), b(b) {}
	int a;
	int b;
};

int main()
{
	MyStruct *s = new MyStruct();
	s->a = 10;
	s->b = 20;

	smart_ptr<MyStruct> sp(s);

	cout << sp->a << endl;
	cout << sp->b << endl;
	cout << (*sp).a << endl;

	auto sp2 = make_smart<MyStruct>(100, 200);
	cout << sp2->a << endl;
	cout << sp2->b << endl;

	auto p = sp2.release();
	cout << p->a << endl;
	cout << p->b << endl;
	delete p;

	return 0;
}
