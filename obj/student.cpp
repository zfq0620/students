#include "student.h"

//操作数据库的句柄
struct sqlite3* pdb = NULL;

//学生管理系统窗口
void show()
{
	system("cls");
	cout << "=============================================" << endl;
	cout << "	    欢迎进入学生管理系统" << endl;
	cout << "	1----------------------创建信息表" << endl;
	cout << "	2----------------------注册学生信息" << endl;
	cout << "	3----------------------查看学生信息" << endl;
	cout << "	4----------------------按照条件查询" << endl;
	cout << "	5----------------------按照条件删除" << endl;
	cout << "	6----------------------更新学生信息" << endl;
	cout << "	7----------------------退出学生管理系统" << endl;
	cout << "=============================================" << endl;
	cout << " 请输入操作的选项：";
	int tmp = 0;
	cin >> tmp;
	student st;

	//创建数据库
	creatSqilite();

	switch (tmp)
	{
	case 1:
		//创建表
		creatTable();
		break;
	case 2:
		//添加学生信息
		st.login();
		break;
	case 3:
		//查看
		st.find();
		break;
	case 4:
		//按照条件查询
		st.findSqilte();
		break;
	case 5:
		//按照条件删除
		st.deleteSqlite();
		break;
	case 6:
		//更新学生信息
		st.updateSqlite();
		break;
	case 7:
		//退出
		exit(0);
		cout << "	请按任意键退出！";
	default:
		cout << " 您输入的有误，请重新输入！" << endl;
		system("cls");
		show();
	}
}

//创建一个数据库 并打开 --返回操作数据库的句柄pdb
int creatSqilite()
{
	//设置库所保存的路径
	char* pPath = NULL;
	char* pErrMsg = NULL;
	char dbName[] = "/mysqlite";
	pPath = (char*)malloc(size + 10);
	if (NULL == pPath)
	{
		return -1;
	}
	memset(pPath, 0, size + 10);
	if (NULL == _getcwd(pPath, size))
	{
		return -1;
	}
	memcpy(pPath + strlen(pPath), dbName, strlen(dbName));

	//打开数据库
	int iResult = sqlite3_open((const char*)pPath, &pdb);
	if (0 != iResult || NULL == pdb)
	{
		printf("invoke sqlite3_open function error!\n");
		free(pPath);
		pPath = NULL;
		return -1;
	}
	return 0;
}



//创建一个数据库表
int creatTable()
{
	char* pErrMsg = NULL;

	//在数据库中创建表
	char buf[size] = "create table students(num integer,"
		" name text ,"
		" age integer )";

	//用sqlite3_exec函数执行创建命令
	int iResult = sqlite3_exec(pdb, buf, 0, 0, &pErrMsg);
	if (0 != iResult)
	{
		printf("%s\n", pErrMsg);
		sqlite3_free(pErrMsg);
	}
	sqlite3_free(pErrMsg);

	cout << " 创建表成功，请按任意键返回上一级目录" << endl;
	system("pause>nul");
	show();
	return 0;
}



//类的成员函数 注册学生信息
int student::login()
{
	system("cls");
	student std1;
	cout << "==============添加学生信息===========" << endl;
	cout << "	请输入学生学号:";
	cin >> std1.num;
	cout << endl << "	请输入学生姓名:";
	cin >> std1.name;
	cout << endl << "	请输入学生年龄:";
	cin >> std1.age;
	cout << "=====================================" << endl;
	char buf[size] = { 0 };
	sprintf_s(buf, "insert into students(num,name,age) values(%d,'%s',%d)",
		std1.num, std1.name, std1.age);

	char* pErrMsg = NULL;
	//插入数据
	int iResult = sqlite3_exec(pdb, buf, 0, 0, &pErrMsg);

	if (SQLITE_OK != iResult)
	{
		printf("%s\n", pErrMsg);
		sqlite3_free(pErrMsg);
	}
	sqlite3_free(pErrMsg);

	cout << " 学生信息添加成功，按任意键返回上一级目录！" << endl;
	system("pause>nul");
	show();
	return 0;
}


//查看数据库学生信息
int student::find()
{
	system("cls");
	cout << "=============学生信息==========" << endl;
	char* pErrMsg = NULL;

	//查看
	char buf[size] = "select * from students";
	char** ppTable = NULL;
	int iRow = 0;
	int iColumn = 0;
	int iResult = sqlite3_get_table(pdb, buf, &ppTable, &iRow, &iColumn, &pErrMsg);

	if (SQLITE_OK != iResult)
	{
		printf("%s\n", pErrMsg);
	}
	sqlite3_free(pErrMsg);
	printf("select sql row %d column %d\n", iRow, iColumn);
	cout << "num\t name\t age" << endl;
	if (NULL != ppTable)
	{
		int k = 1;
		for (; k <= iRow; k++)
		{
			int j = 0;
			for (; j < iColumn; j++)
			{
				if (NULL != ppTable[k * iColumn + j])
				{
					cout << ppTable[k * iColumn + j];
					cout << "\t ";
				}
			}
			cout << endl;
		}
	}
	cout << endl << " 查看信息成功，按任意键返回上一级目录" << endl;
	system("pause>nul");
	show();
	return 0;
}


//按照学号查找数据库学生信息
int student::findSqilte()
{
	system("cls");

	char buf[size] = { 0 };
	char name[size] = { 0 };

	char** ppTable = NULL;
	char* pErrMsg = NULL;
	int iRow = 0;
	int iColumn = 0;

	//菜单
	cout << "============按照条件查询===========" << endl;
	cout << "   1-----------------按照学号查找" << endl;
	cout << "   2-----------------按照姓名查找" << endl;
	cout << "   3-----------------按照年龄查找" << endl;
	cout << "===================================" << endl;
	cout << "请选择需要操作的选项：";
	int tmp = 0;
	cin >> tmp;
	switch (tmp)
	{
	case 1:
		//按照学号查找
		cout << " 请输入需要查询的学生学号" << endl;
		int num;
		cin >> num;
		sprintf_s(buf, "select *from students where num = %d", num);
		break;
	case 2:
		//按照姓名查找
		cout << " 请输入需要查询的学生姓名" << endl;
		cin >> name;
		sprintf_s(buf, "select *from students where name = %s", name);
		break;
	case 3:
		//按照年龄查找
		cout << " 请输入需要查询的学生年龄" << endl;
		int age;
		cin >> age;
		sprintf_s(buf, "select *from students where age = %d", age);
		break;
	default:
		cout << " 输入有误,查询失败！";
		return 0;
	}

	int iResult = sqlite3_get_table(pdb, buf, &ppTable, &iRow, &iColumn, &pErrMsg);
	if (SQLITE_OK != iResult)
	{
		printf("%s\n", pErrMsg);
	}
	sqlite3_free(pErrMsg);

	cout << "num\t name\t age" << endl;
	if (NULL != ppTable)
	{
		int k = 1;
		for (; k <= iRow; k++)
		{
			int j = 0;
			for (; j < iColumn; j++)
			{
				if (NULL != ppTable[k * iColumn + j])
				{
					cout << ppTable[k * iColumn + j];
					cout << "\t ";
				}
			}
			cout << endl;
		}
	}
	cout << endl << " 查看信息成功，按任意键返回上一级目录" << endl;
	system("pause>nul");
	show();
	return 0;
}

//按照条件删除
int student::deleteSqlite()
{
	system("cls");

	char buf[size] = { 0 };
	char name[size] = { 0 };
	char* pErrMsg = NULL;

	//菜单
	cout << "============按照条件删除===========" << endl;
	cout << "   1-----------------按照学号删除" << endl;
	cout << "   2-----------------按照姓名删除" << endl;
	cout << "   3-----------------按照年龄删除" << endl;
	cout << "===================================" << endl;
	cout << "请选择需要操作的选项：";
	int tmp = 0;
	cin >> tmp;
	switch (tmp)
	{
	case 1:
		//按照学号删除
		cout << " 请输入需要删除的学生学号" << endl;
		int num;
		cin >> num;
		sprintf_s(buf, "delete from students where num = %d", num);
		break;
	case 2:
		//按照姓名删除
		cout << " 请输入需要删除的学生姓名" << endl;
		cin >> name;
		sprintf_s(buf, "delete from students where name  = %s", name);
		break;
	case 3:
		//按照年龄删除
		cout << " 请输入需要删除的学生年龄" << endl;
		int age;
		cin >> age;
		sprintf_s(buf, "delete from students where age = %d", age);
		break;
	default:
		cout << " 输入有误,删除失败！";
		return 0;
	}

	int iResult = sqlite3_exec(pdb, buf, 0, 0, &pErrMsg);
	if (SQLITE_OK != iResult)
	{
		printf("%s\n", pErrMsg);
	}
	sqlite3_free(pErrMsg);

	cout << endl << " 删除学生信息成功，按任意键返回上一级目录" << endl;
	system("pause>nul");
	show();
	return 0;
}

//更新学生信息
int student::updateSqlite()
{
	system("cls");

	char buf[size] = { 0 };
	char name1[size] = { 0 };
	char name2[size] = { 0 };
	char* pErrMsg = NULL;

	//菜单
	cout << "============按照条件修改===========" << endl;
	cout << "   1-----------------按照学号修改" << endl;
	cout << "   2-----------------按照姓名修改" << endl;
	cout << "   3-----------------按照年龄修改" << endl;
	cout << "===================================" << endl;
	cout << "请选择需要操作的选项：";
	int tmp = 0;
	cin >> tmp;
	switch (tmp)
	{
	case 1:
		//按照学号修改
		cout << " 请输入需要更改的学生学号" << endl;
		int num1, num2;
		cin >> num1;
		cout << " 请输入新的学生学号" << endl;
		cin >> num2;
		sprintf_s(buf, "update students set num = %d where num = %d", num2, num1);
		break;
	case 2:
		//按照姓名修改
		cout << " 请输入需要修改的学生姓名" << endl;
		cin >> name1;
		cout << " 请输入新的学生姓名" << endl;
		cin >> name2;
		sprintf_s(buf, "update students set name = '%s' where name = %s", name2, name1);
		break;
	case 3:
		//按照年龄删除
		int age1;
		int age2;
		cout << " 请输入需要修改的学生年龄" << endl;
		cin >> age1;
		cout << " 请输入新的学生年龄" << endl;
		cin >> age2;
		sprintf_s(buf, "update students set age = %d where age = %d", age2, age1);
		break;
	default:
		cout << " 输入有误,修改失败！";
		return 0;
	}

	int iResult = sqlite3_exec(pdb, buf, 0, 0, &pErrMsg);
	if (SQLITE_OK != iResult)
	{
		printf("%s\n", pErrMsg);
	}
	sqlite3_free(pErrMsg);

	cout << endl << " 更新学生信息成功，按任意键返回上一级目录" << endl;
	system("pause>nul");
	show();
	return 0;
}