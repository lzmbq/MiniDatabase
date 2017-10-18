/********************************************************************
	created:	2008/06/15
	created:	15:6:2008   23:02
	modified:	
	filename: 	MyString
	file ext:	cpp
	author:		
	
	purpose:	��������ַ�����ת������
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
			string e = "���� D0001:'" + str + "'���Ǳ����ݿ�֧�ֵ�'INT'���ͣ�";
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
		string e = "���� D0002:'" + str + "'���Ǳ����ݿ�֧�ֵ�'CHAR'���ͣ�";
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
	// TODO:δʵ��
	MyString::StringToInt(str);
}

void MyString::IsVarChar(const string& str, const int& length)
{
	if (str.length() >= length)
	{
		string e = "���� D0003:'" + str + "'�����˱����ݿ�֧�ֵ�'VARCHAR'���͵ĳ���" + "��";
		throw e;
	}
}