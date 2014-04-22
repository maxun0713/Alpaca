/*
 * main.cpp
 *
 *  Created on: 2014年4月22日
 *      Author: marv
 */




#include <map>
#include <iostream>
using namespace std;

int main()
{

    multimap<int, int> ms;
    ms.insert(multimap<int, int>::value_type(1,1));
	ms.insert(multimap<int, int>::value_type(100,1));
	ms.insert(multimap<int, int>::value_type(100,1));
	// 打印数据
//	iend = ms.end();
//	for (i=ms.begin(); i!=iend; ++i)
//		cout << *i << ' ';
	cout << endl;
	return 0;
}
