#pragma once

#include <iostream>
#include <fstream>
#include <assert.h>
#include <cstring>
#include <time.h>

//using namespace std;

#define MAX_COL_SIZE 10
#define MAX_ATTR_LEN 30
#define MAX_COMMAND_SEG 20
#define MAX_COMMAND_SEG_LEN 20

using std::ofstream;
using std::ifstream;
using std::cout;
using std::cin;
using std::string;
using std::endl;

#pragma warning(disable:4996) // ������VS�����±��룬�������̵�ָʾ����Ӵ���

class Record //�������Լ���˼�벻�Ƿǳ������ϣ�Ŀǰ���ദ������״̬
{
	static int attrc;
	static char attr_name[MAX_COL_SIZE][MAX_ATTR_LEN];

public:
	char *attrv[MAX_COL_SIZE];
	//TODO 
	//realize get and set attr; ʵ��get��set attr
	static int getAttr(char attrs[][MAX_ATTR_LEN]); //get attribute per record ��ȡÿ����¼������
	static bool setAttr(int num_attr, const char attrs[][MAX_ATTR_LEN]); //set attribute for record before reading records �ڶ�ȡ��¼֮ǰ���ü�¼������
	Record();
	~Record();
	friend ifstream & operator >> (ifstream &input, Record &record);
};

class Command 
{
public:
	int argc; //ָ��ʵĸ���
	char *argv[MAX_COMMAND_SEG]; //ָ��ʵ�������
	Command();
	~Command();
	friend ifstream & operator >> (ifstream &input, Command &command);
};

static ifstream & operator >> (ifstream &input, Record &record); //��κ���������������command���������ƣ����Ǵ�����û�н���ʹ�ã������Լ����в�֣�������Table�����ж���
ifstream & operator >> (ifstream &input, Command &command); //�������ṩ�Ŀ�ܴ�����ֱ��ʹ������һ�����أ���û�н��и���

void INFO(const char* msg);
void helper(Command &command, ofstream &file);
void loadData(char *datafile);