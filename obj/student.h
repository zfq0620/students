#pragma once
#include <iostream>
#include <string>

//���ݿ�
#include "sqlite3.h"
#include  <direct.h>  //��ȡ�ļ�·��
#define size 200

using namespace std;

int creatSqilite(); //������
int creatTable(); //������
void show();  //��ʾ�˵�


class student
{
public:
	//��ʼ��
	student()
	{
		num = 0;
		age = 0;
		memset(name, 0, size);
	}
	int login(); //ע��ѧ����Ϣ
	int find(); //����ѧ����Ϣ
	int findSqilte(); //������������ѧ����Ϣ
	int deleteSqlite(); //��������ɾ��
	int updateSqlite(); //����ѧ����Ϣ

private:
	int num; //ѧ��
	char name[size]; //����
	int age; //����
};

