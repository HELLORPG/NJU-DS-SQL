#pragma once

#include "common.h"
#include "GRPVector.h" //����ģ�壬������vector�����Ҷ���
#include <string>

#include "Table.h"

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
private:
	Table table1;
	Table table2;

public:
	void Read_Key_List(int i, string key_list);
	void Read_Data(int i, ifstream &file);
	void Read_Table_Name(int i, string table_name);
};