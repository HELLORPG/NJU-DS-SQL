#pragma once

#include <iostream>

using std::ostream;

class ID_Index_Node;

bool operator>(const ID_Index_Node &x, const ID_Index_Node &y);
bool operator==(const ID_Index_Node &x, const ID_Index_Node &y);
bool operator>=(const ID_Index_Node &x, const ID_Index_Node &y);
bool operator<(const ID_Index_Node &x, const ID_Index_Node &y);
bool operator<=(const ID_Index_Node &x, const ID_Index_Node &y);
bool operator!=(const ID_Index_Node &x, const ID_Index_Node &y);
static ostream& operator<<(ostream &os, const ID_Index_Node &x);

class ID_Index_Node //��Ϊû����value�����Բ���Ҫʹ��ģ���࣬������Ȼ����ͷ�ļ��ж��壬�����Զ���ڵ����ͳһ��
{
public:
	int id; //��ֵ
	//T value; //value����Ϊname��string������ʹ��ģ�������
	int index;
	//���������������һ���ڵ��������
	//��С�ıȽ�Ӧ��ֻ��id�йأ�����index�޹�

	ID_Index_Node(int id, int index) : id(id), index(index) {}
	ID_Index_Node() : ID_Index_Node(0, 0) {}
	friend bool operator>(const ID_Index_Node &x, const ID_Index_Node &y) { return x.id > y.id; }
	friend bool operator==(const ID_Index_Node &x, const ID_Index_Node &y) { return x.id == y.id; }
	friend bool operator>=(const ID_Index_Node &x, const ID_Index_Node &y) { return x == y || x > y; }
	friend bool operator<(const ID_Index_Node &x, const ID_Index_Node &y) { return (!(x == y)) && (!(x > y)); }
	friend bool operator<=(const ID_Index_Node &x, const ID_Index_Node &y) { return x == y || x < y; }
	friend bool operator!=(const ID_Index_Node &x, const ID_Index_Node &y) { return !(x == y); }

	friend ostream& operator<<(ostream &os, const ID_Index_Node &x);
};

static ostream& operator<<(ostream& os, const ID_Index_Node& x)
{
	os << "[" << x.id << " " << x.index << "]";
	return os;
}
