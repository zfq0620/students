#pragma once

// �˻���¼
#include <iostream>
#include <string>
#include <fstream>
#include <io.h>
#include "student.h"
using namespace std;

void windows();

//����һ����
class enter
{
private:
	string ID;
	string password1;
	string password2;
public:
	//ע��
	void signIN();
	//��¼
	void logIN();
};

//enter��ĳ�Ա����
void enter::signIN()
{
	system("cls");
	cout << "===================================" << endl;
	cout << "	**********ע��**********" << endl;
	cout << endl<<" �������û���:";
	cin >> ID;

	string str;
	ifstream outfile("enter.txt", ios::binary | ios::app);
	outfile >> str;

	while ( !outfile.eof() )
	{
		if (ID == str)
		{
			cout << endl<<" ���˺��Ѿ�ע��,�밴�������������ע��" << endl;
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
	cout <<endl<< " ����������:";
	cin >> password1;
	cout <<endl<<" ���ٴ���������:";
	cin >> password2;

	if (password1 == password2)
	{
		ofstream infile("enter.txt", ios::app);
		infile << ID <<" "<< password1 << endl;
		infile.close();
		cout << " ע��ɹ����밴������������˵�" << endl;
		system("pause>nul");
		windows();
	}
}


//enter��ĳ�Ա����
void enter::logIN()
{
	system("cls");
	cout << "===================================" << endl;
	cout << "	 *********��¼*********" << endl;
	string id;
	string pass;
	string n;
	string m;
	cout << endl<<" " << " �������û�����";
	cin >> id;
	cout << endl<<" " << " ���������룺";
	cin >> pass;

	//�ж��ļ��Ƿ����
	if ((_access("enter.txt",0)) == -1)
	{
		cout << endl << " ���˻������ڣ�����ע��"<<endl<<endl;
		cout << " �밴�����������һ��!" << endl<<endl;
		system("pause>nul");
		windows();
	}

	ifstream outfile("enter.txt", ios::binary);
	//��ȡ�������� �˻� ����
	outfile >> n >> m;
	while (!outfile.eof())
	{
		if (id == n)
		{
			if (pass == m)
			{
				//cout << endl << endl << " ��¼�ɹ����밴���������ϵͳ" << endl;
				//system("pause>nul");
				//����ϵͳ
				show();
			}
			else
			{
				cout << " ��������û��������������밴��������µ�¼��" << endl;
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
	cout << " ��������û��������������밴��������µ�¼��" << endl;
	system("pause>nul");
	windows();
}

//��¼����
void windows()
{
	//����
	system("cls");
	enter u;
	cout << "===================================" << endl;
	cout << "	       �˻�����ϵͳ" << endl;
	cout << "    1----------------------ע��" << endl;
	cout << "    2----------------------��¼" << endl;
	cout << "    3----------------------�˳�" << endl;
	cout << "===================================" << endl;
	cout << "  ��ѡ��:";

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
		cout << " �밴������˳�....";
	default:
		cout << " ��������밴�������������" << endl;
		system("pause>nul");
		windows();
	}
}