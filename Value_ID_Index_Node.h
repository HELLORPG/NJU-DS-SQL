#pragma once

#include <iostream>

using std::ostream;

template <typename T>
class Value_ID_Index_Node;

template <typename T>
class Value_ID_Index_Node
{
public:
	int id; //��ֵ
	T value; //value����Ϊname��string������ʹ��ģ�������
	int index;
	//�������������һ���ڵ��������

	Value_ID_Index_Node(int index, int id, T value) : index(index), id(id), value(value) { }
	//Value_ID_Index_Node();
	friend bool operator>(const Value_ID_Index_Node &x, const Value_ID_Index_Node &y);
	friend bool operator==(const Value_ID_Index_Node &x, const Value_ID_Index_Node &y);
	friend bool operator>=(const Value_ID_Index_Node &x, const Value_ID_Index_Node &y) { return x == y || x > y; }
	friend bool operator<(const Value_ID_Index_Node &x, const Value_ID_Index_Node &y) { return (!(x == y)) && (!(x > y)); }
	friend bool operator<=(const Value_ID_Index_Node &x, const Value_ID_Index_Node &y) { return x == y || x < y; }
	friend bool operator!=(const Value_ID_Index_Node &x, const Value_ID_Index_Node &y) { return !(x == y); }

	friend ostream& operator<< <T>(ostream &os, const Value_ID_Index_Node &x);
};


template <typename T>
bool operator>(const Value_ID_Index_Node<T> &x, const Value_ID_Index_Node<T> &y)
{
	if (x.value < y.value)
		return false;
	else if (x.value > y.value)
		return true;
	else
	{
		if (x.id > y.id)
			return true;
		else
			return false;
	}
}

template <typename T>
bool operator==(const Value_ID_Index_Node<T> &x, const Value_ID_Index_Node<T> &y)
{
	if (x.id == y.id && x.value == y.value)
		return true;
	else
		return false;
}


template <typename T>
ostream& operator<<(ostream &os, const Value_ID_Index_Node<T> &x)
{
	os << "[" << x.index << " " << x.id << " " << x.value << "]";
	return os;
}