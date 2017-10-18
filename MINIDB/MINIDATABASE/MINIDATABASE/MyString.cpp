/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	MyString
	file ext:	cpp
	author:		
	
	purpose:	该类完成字符串的转换操作
*********************************************************************/
#include "MyString.h"
#include "Math.h"
bool MyString::Analyse(const string& allStr,string& s, int pos)
{
	int i = 0, temp = 0;
	int recordCount=0;
	while(allStr[i] != '\0')
	{
		if (allStr[i] == '/')
		{
			s = allStr.substr(temp, i - temp );
//			cout << s << endl;
			temp = i + 1;
			if (pos == recordCount)
				return true;
			recordCount ++;
		}
		i++;
	}
	return true;
}
string MyString::Create(const string s[], int n)
{
	string temp;
	for (int i = 0; i < n; i++)
	{
		if (s[i] == "")
		{
			temp=temp+"NULL"+'/';
		}
		else
			temp=temp+s[i]+'/';
	}
	return temp;
}
int MyString::StringToInt(const string& str)
{
	int num = 0;
	int scale = 10;
	long i = (long)str.length();
	for (long t = 0; t < i; t++)
	{
		char temp = str[t] - '0';
		if (temp < 0|| temp > 9)
		{
			string e = "错误 D0001:'" + str + "'不是本数据库支持的'INT'类型！";
			throw e;
		}
		num = (num + temp) * scale;
	}
	num /= 10;
	return num;
}

string MyString::IntToString(const int& num)
{
	string str = "";
	char temp;
	int i = num;
	AStack<char> s;
	do
	{
		temp = i%10;
		temp = temp + '0';
		s.push(temp);
	}while((i = i/10) != 0);
	while(s.pop(temp))
	{
		str += temp;
	}
	return str;
}
void MyString::IsChar(const string& str)
{
	if (str.length() == 1)
	{
		string e = "错误 D0002:'" + str + "'不是本数据库支持的'CHAR'类型！";
		throw e;
	}
}

void MyString::IsShort(const string& str)
{
	MyString::StringToInt(str);
}
void MyString::IsInt(const string& str)
{
	MyString::StringToInt(str);
}

void MyString::IsLong(const string& str)
{
	// TODO:未实现
	MyString::StringToInt(str);
}

void MyString::IsVarChar(const string& str, const int& length)
{
	if (str.length() >= length)
	{
		string e = "错误 D0003:'" + str + "'超出了本数据库支持的'VARCHAR'类型的长度" + "！";
		throw e;
	}
}