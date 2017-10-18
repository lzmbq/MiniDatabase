/********************************************************************
	created:	2008/07/26
	created:	
	modified:	
	filename: 	MINIDBCmd
	file ext:	h
	author:		
	
	purpose:	MINI数据库提供的非SQL语句命令
*********************************************************************/
#ifndef MINIDBCMD_H_
#define MINIDBCMD_H_
#pragma warning( disable : 4290 )
#include <string>
#include <fstream>
#include <conio.h>
#include "UI.h"
#include "Parser.h"
class MINIDBCmd
{
public:
	bool static ExecuteScript(string a[], TableManager*& tm, DataBase& db) throw (const string);
	bool static InputPassWord(char pwd[]);
	//bool static ParseSQL(char pwd[]);

};

bool MINIDBCmd::ExecuteScript(std::string a[], TableManager*& tm, DataBase& db)
{
	int i = 1;
	ifstream in;
	string scriptPath = "";
	Parser parser;
	while (a[i] != "")
	{
		if (a[i] == "sql")
			scriptPath += ".";
		scriptPath += a[i];
		i++;
	}
	try
	{
		in.open(scriptPath.c_str());
		if (NULL == in)
		{
			string e = scriptPath + "无法打开！";
			throw e;
		}
	}
	catch(const string s)
	{
		cout << s << endl;
		return false;
	}

	char c;
	bool isEnd = false;
	while (true)
	{
		string sql = "";
		do
		{
			if (in.eof())
			{
				isEnd = true;
				break;
			}
			in.get(c);
			sql += c;
		}while (c != ';');
		if (isEnd == true)
			break;
//		cout << sql; 测试
		parser.Scanner(sql,a);

		if (a[0] == "use")
			UI::use(a,i,tm, db);
		else if (a[0] == "select")
			UI::select(a ,i, tm, db);
		else if (a[0] == "delete")
			UI::Delete(a ,i, tm);
		else if (a[0] == "insert")
			UI::insert(a, i, tm);
		else if (a[0] == "show")
			UI::show(a, i, tm, db);
		else if (a[0] == "drop")
			UI::drop(a, i, tm, db);
		else if (a[0] == "alter")
			UI::alter(a, i, tm);
		else if (a[0] == "update")
			UI::update(a, i, tm);
		else if (a[0] == "create")
			UI::create(a, i, tm, db);
		else if (a[0] == "describe")
			UI::describe(a, i, tm);
		//else if (a[0] == "save")
		//	UI::save(a, i, tm);
		else
		{
			cout << "Script error!" << "\007" << endl;
			continue;
		}
	}
	return true;
}

bool MINIDBCmd::InputPassWord(char pwd[])
{
	int pos = 0;
		char c = 'a';  
		while('\r' != c)    
		{  
			c = getch();  
			if(c == 0x08)  
			{  
				pwd[pos] = ' ';
				printf("%c",0x08);  
				printf(" ");  
				printf("%c",0x08);  
				continue;  
			}  
			else if ('\r' != c)
			{
				printf("*");  
				pwd[pos] = c;
				pos ++;
			}
   		} 
		pwd[pos] = '\0';
		cout << endl;
		return true;
}
#endif