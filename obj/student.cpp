#include "student.h"

//�������ݿ�ľ��
struct sqlite3* pdb = NULL;

//ѧ������ϵͳ����
void show()
{
	system("cls");
	cout << "=============================================" << endl;
	cout << "	    ��ӭ����ѧ������ϵͳ" << endl;
	cout << "	1----------------------������Ϣ��" << endl;
	cout << "	2----------------------ע��ѧ����Ϣ" << endl;
	cout << "	3----------------------�鿴ѧ����Ϣ" << endl;
	cout << "	4----------------------����������ѯ" << endl;
	cout << "	5----------------------��������ɾ��" << endl;
	cout << "	6----------------------����ѧ����Ϣ" << endl;
	cout << "	7----------------------�˳�ѧ������ϵͳ" << endl;
	cout << "=============================================" << endl;
	cout << " �����������ѡ�";
	int tmp = 0;
	cin >> tmp;
	student st;

	//�������ݿ�
	creatSqilite();

	switch (tmp)
	{
	case 1:
		//������
		creatTable();
		break;
	case 2:
		//���ѧ����Ϣ
		st.login();
		break;
	case 3:
		//�鿴
		st.find();
		break;
	case 4:
		//����������ѯ
		st.findSqilte();
		break;
	case 5:
		//��������ɾ��
		st.deleteSqlite();
		break;
	case 6:
		//����ѧ����Ϣ
		st.updateSqlite();
		break;
	case 7:
		//�˳�
		exit(0);
		cout << "	�밴������˳���";
	default:
		cout << " ��������������������룡" << endl;
		system("cls");
		show();
	}
}

//����һ�����ݿ� ���� --���ز������ݿ�ľ��pdb
int creatSqilite()
{
	//���ÿ��������·��
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

	//�����ݿ�
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



//����һ�����ݿ��
int creatTable()
{
	char* pErrMsg = NULL;

	//�����ݿ��д�����
	char buf[size] = "create table students(num integer,"
		" name text ,"
		" age integer )";

	//��sqlite3_exec����ִ�д�������
	int iResult = sqlite3_exec(pdb, buf, 0, 0, &pErrMsg);
	if (0 != iResult)
	{
		printf("%s\n", pErrMsg);
		sqlite3_free(pErrMsg);
	}
	sqlite3_free(pErrMsg);

	cout << " ������ɹ����밴�����������һ��Ŀ¼" << endl;
	system("pause>nul");
	show();
	return 0;
}



//��ĳ�Ա���� ע��ѧ����Ϣ
int student::login()
{
	system("cls");
	student std1;
	cout << "==============���ѧ����Ϣ===========" << endl;
	cout << "	������ѧ��ѧ��:";
	cin >> std1.num;
	cout << endl << "	������ѧ������:";
	cin >> std1.name;
	cout << endl << "	������ѧ������:";
	cin >> std1.age;
	cout << "=====================================" << endl;
	char buf[size] = { 0 };
	sprintf_s(buf, "insert into students(num,name,age) values(%d,'%s',%d)",
		std1.num, std1.name, std1.age);

	char* pErrMsg = NULL;
	//��������
	int iResult = sqlite3_exec(pdb, buf, 0, 0, &pErrMsg);

	if (SQLITE_OK != iResult)
	{
		printf("%s\n", pErrMsg);
		sqlite3_free(pErrMsg);
	}
	sqlite3_free(pErrMsg);

	cout << " ѧ����Ϣ��ӳɹ����������������һ��Ŀ¼��" << endl;
	system("pause>nul");
	show();
	return 0;
}


//�鿴���ݿ�ѧ����Ϣ
int student::find()
{
	system("cls");
	cout << "=============ѧ����Ϣ==========" << endl;
	char* pErrMsg = NULL;

	//�鿴
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
	cout << endl << " �鿴��Ϣ�ɹ����������������һ��Ŀ¼" << endl;
	system("pause>nul");
	show();
	return 0;
}


//����ѧ�Ų������ݿ�ѧ����Ϣ
int student::findSqilte()
{
	system("cls");

	char buf[size] = { 0 };
	char name[size] = { 0 };

	char** ppTable = NULL;
	char* pErrMsg = NULL;
	int iRow = 0;
	int iColumn = 0;

	//�˵�
	cout << "============����������ѯ===========" << endl;
	cout << "   1-----------------����ѧ�Ų���" << endl;
	cout << "   2-----------------������������" << endl;
	cout << "   3-----------------�����������" << endl;
	cout << "===================================" << endl;
	cout << "��ѡ����Ҫ������ѡ�";
	int tmp = 0;
	cin >> tmp;
	switch (tmp)
	{
	case 1:
		//����ѧ�Ų���
		cout << " ��������Ҫ��ѯ��ѧ��ѧ��" << endl;
		int num;
		cin >> num;
		sprintf_s(buf, "select *from students where num = %d", num);
		break;
	case 2:
		//������������
		cout << " ��������Ҫ��ѯ��ѧ������" << endl;
		cin >> name;
		sprintf_s(buf, "select *from students where name = %s", name);
		break;
	case 3:
		//�����������
		cout << " ��������Ҫ��ѯ��ѧ������" << endl;
		int age;
		cin >> age;
		sprintf_s(buf, "select *from students where age = %d", age);
		break;
	default:
		cout << " ��������,��ѯʧ�ܣ�";
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
	cout << endl << " �鿴��Ϣ�ɹ����������������һ��Ŀ¼" << endl;
	system("pause>nul");
	show();
	return 0;
}

//��������ɾ��
int student::deleteSqlite()
{
	system("cls");

	char buf[size] = { 0 };
	char name[size] = { 0 };
	char* pErrMsg = NULL;

	//�˵�
	cout << "============��������ɾ��===========" << endl;
	cout << "   1-----------------����ѧ��ɾ��" << endl;
	cout << "   2-----------------��������ɾ��" << endl;
	cout << "   3-----------------��������ɾ��" << endl;
	cout << "===================================" << endl;
	cout << "��ѡ����Ҫ������ѡ�";
	int tmp = 0;
	cin >> tmp;
	switch (tmp)
	{
	case 1:
		//����ѧ��ɾ��
		cout << " ��������Ҫɾ����ѧ��ѧ��" << endl;
		int num;
		cin >> num;
		sprintf_s(buf, "delete from students where num = %d", num);
		break;
	case 2:
		//��������ɾ��
		cout << " ��������Ҫɾ����ѧ������" << endl;
		cin >> name;
		sprintf_s(buf, "delete from students where name  = %s", name);
		break;
	case 3:
		//��������ɾ��
		cout << " ��������Ҫɾ����ѧ������" << endl;
		int age;
		cin >> age;
		sprintf_s(buf, "delete from students where age = %d", age);
		break;
	default:
		cout << " ��������,ɾ��ʧ�ܣ�";
		return 0;
	}

	int iResult = sqlite3_exec(pdb, buf, 0, 0, &pErrMsg);
	if (SQLITE_OK != iResult)
	{
		printf("%s\n", pErrMsg);
	}
	sqlite3_free(pErrMsg);

	cout << endl << " ɾ��ѧ����Ϣ�ɹ����������������һ��Ŀ¼" << endl;
	system("pause>nul");
	show();
	return 0;
}

//����ѧ����Ϣ
int student::updateSqlite()
{
	system("cls");

	char buf[size] = { 0 };
	char name1[size] = { 0 };
	char name2[size] = { 0 };
	char* pErrMsg = NULL;

	//�˵�
	cout << "============���������޸�===========" << endl;
	cout << "   1-----------------����ѧ���޸�" << endl;
	cout << "   2-----------------���������޸�" << endl;
	cout << "   3-----------------���������޸�" << endl;
	cout << "===================================" << endl;
	cout << "��ѡ����Ҫ������ѡ�";
	int tmp = 0;
	cin >> tmp;
	switch (tmp)
	{
	case 1:
		//����ѧ���޸�
		cout << " ��������Ҫ���ĵ�ѧ��ѧ��" << endl;
		int num1, num2;
		cin >> num1;
		cout << " �������µ�ѧ��ѧ��" << endl;
		cin >> num2;
		sprintf_s(buf, "update students set num = %d where num = %d", num2, num1);
		break;
	case 2:
		//���������޸�
		cout << " ��������Ҫ�޸ĵ�ѧ������" << endl;
		cin >> name1;
		cout << " �������µ�ѧ������" << endl;
		cin >> name2;
		sprintf_s(buf, "update students set name = '%s' where name = %s", name2, name1);
		break;
	case 3:
		//��������ɾ��
		int age1;
		int age2;
		cout << " ��������Ҫ�޸ĵ�ѧ������" << endl;
		cin >> age1;
		cout << " �������µ�ѧ������" << endl;
		cin >> age2;
		sprintf_s(buf, "update students set age = %d where age = %d", age2, age1);
		break;
	default:
		cout << " ��������,�޸�ʧ�ܣ�";
		return 0;
	}

	int iResult = sqlite3_exec(pdb, buf, 0, 0, &pErrMsg);
	if (SQLITE_OK != iResult)
	{
		printf("%s\n", pErrMsg);
	}
	sqlite3_free(pErrMsg);

	cout << endl << " ����ѧ����Ϣ�ɹ����������������һ��Ŀ¼" << endl;
	system("pause>nul");
	show();
	return 0;
}