/********************************************************************
	created:	2008/07/25
	modified:	
	filename: 	Parser
	file ext:	h
	author:		
	
	purpose:	解析SQL语句
*********************************************************************/
#ifndef PARSER_H_
#define PARSER_H_
#include "UI.h"
#include <string>
class Parser
{
private:
	char m_cDivision[20];
	char m_cOperator[20];
	int m_iDLength;
	int m_iOLength;
	bool IsDivision(const char& in_char);
	bool IsOperator(const char& in_char);
public:
	Parser()
	{
		m_cDivision[0] = ' ';
		m_cDivision[1] = ',';
//		m_cDivision[2] = '.';
		m_cDivision[2] = 10 ;	//回车符 c=getchar()时为10	c=getch()时为13
		m_cDivision[3] = '(' ;
		m_cDivision[4] = ')' ;
	
		m_cOperator[0] = '=';
		m_cOperator[1] = '<';
		m_cOperator[2] = '>';
		m_cOperator[3] = '*';
		//m_cOperator[4] = '(';
		//m_cOperator[5] = ')';

		
		m_iDLength = 5;
		m_iOLength = 4;
	
	}
	bool Scanner(const string& sql, string a[]);
};

bool Parser::IsDivision(const char& in_char)
{
	for (int i = 0; i < m_iDLength; i++)
	{
		if (in_char == m_cDivision[i])
			return true;
	}
	return false;
}
bool Parser::IsOperator(const char& in_char)
{
	for (int i = 0; i < m_iOLength; i++)
	{
		if (in_char == m_cOperator[i])
			return true;
	}
	return false;
}
bool Parser::Scanner(const string& sql, string a[])
{
	int i = 0, temp = 0;
	int recordCount=0;
	while(true)
	{
		if (IsDivision(sql[i])||IsOperator(sql[i])||sql[i] == ';')
		{
			if ((i-temp) != 0 )			// 等于零的情况为操作符之后跟分割符
			{
				a[recordCount] = sql.substr(temp, i - temp );
				//cout << a[recordCount] << endl; //测试分词是否正确
				recordCount ++;
			}
			if (sql[i] == ';')
				break;
			
			if (IsOperator(sql[i]))
			{
				a[recordCount] = sql[i];
				//cout << a[recordCount] << endl;  //测试分词是否正确
				recordCount ++;
				i++;
			}
			while(IsDivision(sql[i]))
			{
				i++;
			}
			temp = i;
		}
		else
			i++;
	}

	return true;
}

#endif