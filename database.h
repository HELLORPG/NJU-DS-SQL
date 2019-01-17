#pragma once

#include "common.h"
#include "GRPVector.h" //����ģ�壬������vector�����Ҷ���
#include <string>
//#include <fstream>

#include "Table.h"

//using std::ifstream;

//class MyDatabase;

extern int TEST_TYPE;
/*
 * ���ݲ�ͬ��TEST_TYPEָ��ѡ��ͬ�����ݽṹ����ʵ��
 * TEST_TYPE = 0��
 */

class MyDatabase 
{
	//TODO
	//do what you want to.
	//int haha;
	//������ҪһЩ���ݽṹ������������ݿ�Ĺ���
public:
	Table table1;
	Table table2;
	Table table3;

	
public:
	int now_table = 1;
	void Read_Key_List(int i, string key_list);
	void Read_Data(int i, ifstream &file);
	void Read_Table_Name(int i, string table_name);

	void Insert(int i, Command &command);
	void Delete(int i, Command &command);
	void Set(int i, Command &command);
	void Add(int i, Command &command);
	void Query(int i, Command &command, ofstream &file);
	void SUM(int i, Command &command, ofstream &file);
	void Inter(Command &command, ofstream &file);
	void Union(Command &command, ofstream &file);
};