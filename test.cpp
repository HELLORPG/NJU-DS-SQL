#include "common.h"
#include "test.h"
//#include "Table.h"

#include "Define.h"



void Timer::tic(char t[]) //���������ַ��������ҿ�����ʱ
{
    strcpy(test_name, t);
    cout << test_name << " test begin." << endl;
    start = clock(); //��ȡ��ǰʱ��

}

void Timer::toc(){
    end = clock();
    used_time = double(end - start) / CLOCKS_PER_SEC;
    cout << test_name << " test done. Use time: " << used_time << endl;
}


Tester::Tester(const char *test_file, const char *result_file)
//���캯���������ļ��������������ļ�������ǽ���ļ�
{
    fin.open(test_file);
    fout.open(result_file);

#ifdef EVERY_STEP_SHOW
	if (fin && fout)
		printf(LIGHT_GREEN "<OPEN THE FILE>  " NONE "%s %s\n", test_file, result_file);
	if (!fin)
		printf(LIGHT_RED "<FILE OPEN FAIL>  " NONE "%s\n", test_file);
	if (!fout)
		printf(LIGHT_RED "<FILE OPEN FAIL>  " NONE "%s\n", result_file);
#endif

    assert((fin && fout) || (INFO("open file failed!"), 0));
}

Tester::~Tester()
{
    fin.close();
    fout.close();
}

void Tester::exec()
{
    Command command; //�����࣬���������˲�����>>������fin>>���Ǽ򵥵Ķ��룬�Ѿ��ָ����
    Timer timer;
    timer.tic(test_name);
    while (fin >> command) //���ϲ���������Ҷ��������ִ�У�ͨ��helper����
	{
        helper(command, fout);
    }
    timer.toc();
}

SingleTester::SingleTester(const char *test_file, const char *result_file):Tester(test_file, result_file)
{
    strcpy(test_name, "Single");   
}

SectionTester::SectionTester(const char *test_file, const char *result_file):Tester(test_file, result_file)
{
    strcpy(test_name, "Section");
}

SetTester::SetTester(const char *test_file, const char *result_file):Tester(test_file, result_file)
{
    strcpy(test_name, "Set");
}