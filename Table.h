#pragma once
#include "GRPVector.h" //����Vector���ڴ洢����
#include "Define.h"
#include <fstream>
#include <sstream>
#include "AVL.h"
//#include "AVL.h"
#include "AVL_Data_Node.h"

struct Data;

ostream& operator<<(ostream &os, Data data);
std::ofstream& operator<<(std::ofstream &file, Data data);

struct Data //���������ڴ洢ÿһ������
{
	bool valid; //��־λ����ʾ���������Ƿ���Ч������[��ɾ��]
	int id;
	string name;
	GRPVector<int> value;
	Data() : id(0), name(""), valid(true) {}
};

class Table
{
private:
	string table_name; //���ݱ�����ƣ����ļ��ĵ�һ�ж���
	GRPVector<string> key; //ÿһ�����Ե�����
	GRPVector<Data> data; //���ݱ�

	//�������ṹ��һ�������͵������������ֲ�ͬ�Ļ�������
	AVL<AVL_Data_Node<int> > id_tree;
	AVL<AVL_Data_Node<string> > name_tree;
	GRPVector<AVL<AVL_Data_Node<int> > > value_tree;
	//�������ṹEND
public:
	Table(string table_name);
	Table();
	~Table() {}
	void Read_Table_Name(string table_name); //��ȡ����
	void Read_Key_List(string key_list); //��ȡ�ļ��������б�
	void Read_Data(std::ifstream &file); //��ȡ������Ҫ������

	//������Ҫά���������Ľṹ
	void AVL_Insert_Data(const Data &data, const int &index);
	void test1();
	void test2();
};