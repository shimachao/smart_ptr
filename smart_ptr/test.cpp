#include "smart_ptr.h"
#include <iostream>
using std::cout;
using std::endl;

struct MyStruct
{
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

	return 0;
}
