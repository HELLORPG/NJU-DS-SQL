#pragma once
#include "GRPVector.h" //����Vector���ڴ洢����
#include "Define.h"
#include <fstream>
#include <sstream>
#include "AVL.h"
#include "common.h"
//#include "AVL.h"
#include "AVL_Data_Node.h"
#include <algorithm>

using std::sort;
using std::stable_sort;

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
	friend class MyDatabase;
public:
	string table_name; //���ݱ�����ƣ����ļ��ĵ�һ�ж���
	GRPVector<string> key; //ÿһ�����Ե�����
	GRPVector<Data> data; //���ݱ�

	//�������ṹ��һ�������͵������������ֲ�ͬ�Ļ�������
	AVL<AVL_Data_Node<int> > id_tree;
	AVL<AVL_Data_Node<string> > name_tree;
	GRPVector<AVL<AVL_Data_Node<int> > > value_tree;
	//�������ṹEND

	Data ERROR; //�����ȡdataʧ��
public:
	Table(string table_name);
	Table();
	~Table() {}
	void Read_Table_Name(string table_name); //��ȡ����
	void Read_Key_List(string key_list); //��ȡ�ļ��������б�
	void Read_Data(std::ifstream &file); //��ȡ������Ҫ������

	//һ���ֹ��ܺ�������������
	Data& Get_Data_By_ID(const int &id);
	int Get_Key_Index(const string &key_name);
	//void printf
	void Equal_Data(BinNode<AVL_Data_Node<int> > *&find_result, ofstream &file);
	void After_Data(BinNode<AVL_Data_Node<int> > *begin_node, ofstream &file/*, const int &value_index*/);
	void Before_Data(BinNode<AVL_Data_Node<int> > *begin_node, BinNode<AVL_Data_Node<int> > *end_node, ofstream &file/*, const int &value_index*/);
	void Equal_Data_Section(BinNode<AVL_Data_Node<int> > *&find_result, ofstream &file, int l, int r);
	void After_Data_Section(BinNode<AVL_Data_Node<int> > *begin_node, ofstream &file, int l, int r);
	void Before_Data_Section(BinNode<AVL_Data_Node<int> > *begin_node, BinNode<AVL_Data_Node<int> > *end_node, ofstream &file, int l, int r);
	//END


	void Insert_Data(Command &command);
	void Delete_Data(Command &command);
	void Set_Data(Command &command);
	void Add_Data(Command &command);
	void Query_Data(Command &command, ofstream &file);
	void Sum_Data(Command &command, ofstream &file);

	

	//������Ҫά���������Ľṹ
	void AVL_Insert_Data(const Data &data, const int &index);
	void AVL_Reset_Data(/*const */Data &data, const int &new_value, const int &value_index); //����value������Щʱ����Ҫ����ڵ��λ�ã�����SET����
	void test1();
	void test2();

	string Name() { return table_name; }
};