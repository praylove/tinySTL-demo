// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "stl/vector.h"

using namespace std;

int main()
{
	Vector<int> a;
	Vector<int> b(10, 2);
	Vector<int> c = {1, 2, 3, 4, 5};
	for (auto it = c.begin(); it != c.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	c.pop_back();
	for (auto it = c.begin(); it != c.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	getchar();
    return 0;
}

