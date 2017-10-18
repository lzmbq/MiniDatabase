 //MINIDATABASE.cpp : 定义控制台应用程序的入口点。


#include "stdafx.h"
#include "Parser.h"
#include "UI.h"
#include "MINIDBCmd.h"
#include "DataBase.h"
#include "index.h"
#include <conio.h>
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	string password = "root";
	bool isQuit = false;
	bool isSqlEnd = false;
	bool isInputEnd = false;
	while (true)
	{
//-------------实现密码输入----------------
		cout << "请输入密码：" << endl;
		char pwd[20];
		MINIDBCmd::InputPassWord(pwd);
//-----------------------------------------
		if (!strcmp(pwd, password.c_str()))
		{
			DataBase db;
			//TableManager* tm = new TableManager("StudentDB");
			TableManager* tm = NULL;

			cout << "              Welcome to use My MINIDATABASE!" << endl; 
			cout << "                                     ——power by WangYi" << endl;
			//tm.selectData("wangyi", "student");
			//测试非主键索引
			string sql;
			char in_c;
			Parser parser;
			
			while(true)
			{
				try
				{
					// 字符输入
					int i = 0;
					sql = "";
					cout << "MINIDB>";
					in_c = getchar();
					if(in_c == 10)
					{
						continue;
					}
					sql = sql + in_c;
					while (true)
					{
						in_c = getchar();
						if (in_c == 10)
						{
							cout << "     ->";
							//sql += ' ';			// 回车符无法加进sql字符串中，故加一空格  -> 可以加，故删掉。
						}
						sql = sql + in_c;
						if (in_c == ';')
							break;
					}
					char c = getchar();
					//cout << sql;
					
					// 数据库解析
					
					// 解析sql
					string a[20];
					parser.Scanner(sql, a);
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
					else if (a[0] == "source")
						MINIDBCmd::ExecuteScript(a, tm, db);
					else if (a[0] == "quit")
					{	
						isQuit = true;
						break;				
					}	
					else
					{
						string e = "错误 A0010:'" + a[0] + "'不是SQL命令！";
						throw e;
					}

					
				}
				catch (const string e)
				{
					cout << e << "\007" << endl;
					cout << endl;
					continue;
				}
				cout << endl;
			}
		}
		else 
		{
			cout << "密码错误！" << "\007" << endl << endl;
		}
		if (isQuit)
			break;
	}
	return 0;
}

