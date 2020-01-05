#pragma once
#include <iostream>
#include <string>

//数据库
#include "sqlite3.h"
#include  <direct.h>  //获取文件路径
#define size 200

using namespace std;

int creatSqilite(); //创建库
int creatTable(); //创建表
void show();  //显示菜单


class student
{
public:
	//初始化
	student()
	{
		num = 0;
		age = 0;
		memset(name, 0, size);
	}
	int login(); //注册学生信息
	int find(); //查找学生信息
	int findSqilte(); //按照条件查找学生信息
	int deleteSqlite(); //按照条件删除
	int updateSqlite(); //更新学生信息

private:
	int num; //学号
	char name[size]; //姓名
	int age; //年龄
};

