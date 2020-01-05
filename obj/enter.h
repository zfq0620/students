#pragma once

// 账户登录
#include <iostream>
#include <string>
#include <fstream>
#include <io.h>
#include "student.h"
using namespace std;

void windows();

//定义一个类
class enter
{
private:
	string ID;
	string password1;
	string password2;
public:
	//注册
	void signIN();
	//登录
	void logIN();
};

//enter类的成员函数
void enter::signIN()
{
	system("cls");
	cout << "===================================" << endl;
	cout << "	**********注册**********" << endl;
	cout << endl<<" 请输入用户名:";
	cin >> ID;

	string str;
	ifstream outfile("enter.txt", ios::binary | ios::app);
	outfile >> str;

	while ( !outfile.eof() )
	{
		if (ID == str)
		{
			cout << endl<<" 该账号已经注册,请按任意键返回重新注册" << endl;
			system("pause>nul");
			windows();
		}
		else
		{
			outfile >> str;
			outfile >> str;
		}
	}
	outfile.close();
	cout <<endl<< " 请输入密码:";
	cin >> password1;
	cout <<endl<<" 请再次输入密码:";
	cin >> password2;

	if (password1 == password2)
	{
		ofstream infile("enter.txt", ios::app);
		infile << ID <<" "<< password1 << endl;
		infile.close();
		cout << " 注册成功，请按任意键返回主菜单" << endl;
		system("pause>nul");
		windows();
	}
}


//enter类的成员函数
void enter::logIN()
{
	system("cls");
	cout << "===================================" << endl;
	cout << "	 *********登录*********" << endl;
	string id;
	string pass;
	string n;
	string m;
	cout << endl<<" " << " 请输入用户名：";
	cin >> id;
	cout << endl<<" " << " 请输入密码：";
	cin >> pass;

	//判断文件是否存在
	if ((_access("enter.txt",0)) == -1)
	{
		cout << endl << " 此账户不存在，请先注册"<<endl<<endl;
		cout << " 请按任意键返回上一级!" << endl<<endl;
		system("pause>nul");
		windows();
	}

	ifstream outfile("enter.txt", ios::binary);
	//读取两个数据 账户 密码
	outfile >> n >> m;
	while (!outfile.eof())
	{
		if (id == n)
		{
			if (pass == m)
			{
				//cout << endl << endl << " 登录成功！请按任意键进入系统" << endl;
				//system("pause>nul");
				//进入系统
				show();
			}
			else
			{
				cout << " 您输入的用户名或密码有误，请按任意键重新登录！" << endl;
				system("pause>nul");
				windows();
			}
		}
		else
		{
			outfile >> n >> m;
		}
	}
	outfile.close();
	cout << " 您输入的用户名或密码有误，请按任意键重新登录！" << endl;
	system("pause>nul");
	windows();
}

//登录窗口
void windows()
{
	//清屏
	system("cls");
	enter u;
	cout << "===================================" << endl;
	cout << "	       账户管理系统" << endl;
	cout << "    1----------------------注册" << endl;
	cout << "    2----------------------登录" << endl;
	cout << "    3----------------------退出" << endl;
	cout << "===================================" << endl;
	cout << "  请选择:";

	int tmp = 0;
	cin >> tmp;

	switch (tmp)
	{
	case 1:
		u.signIN();
		break;
	case 2:
		u.logIN();
		break;
	case 3:
		exit(0);
		cout << " 请按任意键退出....";
	default:
		cout << " 输入错误，请按任意键重新输入" << endl;
		system("pause>nul");
		windows();
	}
}