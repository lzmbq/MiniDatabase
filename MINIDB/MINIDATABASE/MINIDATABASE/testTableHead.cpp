/*
#include "TableHead.h"
#include <iostream>

using namespace std;

int main()
{
	TableHead h;
	Column c,t,e;
	string d;
	c.setColName("学号");
	c.setDataSize(10);
	c.setDataType(MY_LONG);
	c.setFlog(1);
	h.AddColumn(c);
	t = h.GetColmn(1);
	int i = h.GetColumnCount();
	cout << "列数为" << i << endl;
	cout << t.getColName() << endl;
	cout << t.getDataSize() << endl;
//	h.DeleteColumn(e,1);
	cout <<h.GetColumnCount() << endl;
	return 0;
}*/
