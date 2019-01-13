#pragma once
#include "GRPVector.h" //����Vector���ڴ洢����
#include "Define.h"
#include <fstream>
#include <sstream>


struct Data //���������ڴ洢ÿһ������
{
	int id;
	string name;
	GRPVector<int> value;
	Data() : id(0), name("") {}
};

class Table
{
private:
	string table_name; //���ݱ�����ƣ����ļ��ĵ�һ�ж���
	GRPVector<string> key; //ÿһ�����Ե�����
	GRPVector<Data> data; //���ݱ�
public:
	Table(string table_name);
	Table();
	~Table() {}
	void Read_Table_Name(string table_name); //��ȡ����
	void Read_Key_List(string key_list); //��ȡ�ļ��������б�
	void Read_Data(std::ifstream &file); //��ȡ������Ҫ������

};