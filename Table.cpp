#include "Table.h"

ostream& operator<<(ostream& os, Data data)
{
	os << data.id << " " << data.name;
	const int value_list_len(data.value.size());
	for (int i(0); i < value_list_len; ++i)
		os << " " << data.value[i];
	return os;
}




Table::Table(string table_name) : table_name(table_name)
{
	for (int i(0); i < 10; ++i)
		value_tree.push_back(*(new AVL<AVL_Data_Node<int> >));

	ERROR.id = INT32_MAX; //�˴����쳣Ϊid�����ֵ
	//cout << value_tree.size() << endl;
}

Table::Table() : Table("") {}

void Table::Read_Table_Name(string table_name)
{
	this->table_name = table_name;
#ifdef EVERY_STEP_SHOW
	printf(LIGHT_GREEN "<TABLE NAME>  " NONE);
	cout << this->table_name << endl;
#endif

}

void Table::Read_Key_List(string key_list)
{
	//�������string�����Էָ���մ洢����Vector
	const char * dlim = " ,:";
	string a_key;
	char *p;
	p = strtok(&key_list[0], dlim);
	while (p)
	{
		a_key = p;
		if (a_key == "id" || a_key == "name")
			;
		//strcpy(record.attrv[i++], p);
		else
			key.push_back(a_key);
		p = strtok(NULL, dlim);
	}

#ifdef GET_DATAFILE_SHOW
	printf(LIGHT_GREEN "%s" NONE, "<GET KEY LIST>  ");
	for (int show_key_i(0); show_key_i < key.size(); ++show_key_i)
		cout << key[show_key_i] << " ";
	cout << "<" << key.size() << " keys>";
	cout << endl;
#endif

	return;
}

void Table::Read_Data(std::ifstream& file)
{
	std::stringstream data_line;
	string get_data_line, word;
	Data a_data;
	std::getline(file, get_data_line);
	int i(0);
	while (!get_data_line.empty())
	{
#ifdef GET_RAW_DATA_SHOW
		cout << get_data_line << endl;
#endif

		i = 0;
		data_line.clear();
		data_line << get_data_line;
		//do
		while (true)
		{
			data_line >> word;
			if (word.empty())
				break;
			switch (i)
			{
			case 0:a_data.id = stoi(word); break;
			case 1:a_data.name = word; break;
			default:a_data.value.push_back(stoi(word)); break;
			}
			//data.push_back(a_data);
			++i;
			word.clear();
		} //while (data_line);
		data.push_back(a_data); //��ʱ��a_data��һ�����������ݣ�����������������������Ľ������Ϳ��Լ���һ��O(n)�ı���

		AVL_Insert_Data(a_data, data.size() - 1);

#ifdef GET_DATAFILE_SHOW
		printf(LIGHT_BLUE "<GET DATA LINE>  " NONE);
		cout << "[" << a_data.id << "] {" << a_data.name << "} ";
		for (int a_data_i(0); a_data_i < a_data.value.size(); ++a_data_i)
			cout << a_data.value[a_data_i] << " ";
		cout << "<" << a_data.value.size() << " values>";
		cout << endl;
#endif
		get_data_line.clear();
		a_data.value.clear();
		std::getline(file, get_data_line);
	}
#ifdef EVERY_STEP_SHOW
	printf(LIGHT_GREEN "<DATA SIZE>  " NONE);
	cout << data.size() << " lines" << endl;
#endif

	//test2();
}

Data& Table::Get_Data_By_ID(const int& id)
{
	const AVL_Data_Node<int> place_data(id, 0, 0);
	BinNode<AVL_Data_Node<int> > *&which = id_tree.search(place_data);
	if (which)
		return data[which->data._index[0].index]; //��Ϊ��Ӧ��IDֻ��һ������
	else
		return ERROR; //���ش����־
}



void Table::AVL_Insert_Data(const Data &data, const int &index)
{
	//��Ҫ��ÿ�����������������
	AVL_Data_Node<int> int_avl_node(data.id, data.id, index);
	const AVL_Data_Node<string> string_avl_node(data.name, data.id, index);
	id_tree.insert(int_avl_node);
	name_tree.insert(string_avl_node);

	const int value_list_len(data.value.size());
	for (int i(0); i < value_list_len; ++i)
	{
		int_avl_node.ReLoad(data.value[i], data.id, index);
		value_tree[i].insert(int_avl_node);
	}
	//cout << "?" << endl;
	return;
}

void Table::Insert_Data(Command& command)
{
	Data x;
	x.valid = true; //�ٽ���һ��ǿ�Ƹ�ֵ�������ϲ���Ҫ
	x.id = atoi(command.argv[1]);
	x.name = command.argv[2];
	for (int i(3); i < command.argc; ++i)
		x.value.push_back(atoi(command.argv[i]));
	data.push_back(x);
	AVL_Insert_Data(x, data.size() - 1);
#ifdef RUN_COMMAND_SHOW
	printf(LIGHT_BLUE "<COMMAND INSERT>  " NONE);
	cout << x << " ";
	printf(LIGHT_BLUE "OVER" NONE);
	cout << endl;
#endif
	//cout << data.size() << endl; //��֤�����ݱ����Ƿ������ӳɹ�
	return;
}

void Table::Delete_Data(Command& command)
{
	switch (command.argc)
	{
	case 2:
	{
		//����ɾ��
		const AVL_Data_Node<int> delete_place(atoi(command.argv[1]), 0, 0); //���ҽڵ��data
		BinNode<AVL_Data_Node<int> > *&which = id_tree.search(delete_place);
		if (which)
		{
			//��ʱ��Ҫɾ���Ľڵ��Ǵ��ڵ�
			data[which->data._index[0].index].valid = false; //����Чλ��Ϊ��Ч�����˶���   [αɾ��]
#ifdef RUN_COMMAND_SHOW
			printf(LIGHT_BLUE "<DELETE POINT>  " NONE);
			cout << data[which->data._index[0].index];
			cout << " ";
			printf(LIGHT_BLUE "OVER" NONE);
			cout << endl;
#endif

		}
	}break;
	case 3:
	{
		assert(0);
		//����ɾ��
	}break;
	default:break;
	}
	return;
}

void Table::Set_Data(Command& command)
{
	switch (command.argc)
	{
	case 4:
	{
		//�������
		Data &set_place_data = Get_Data_By_ID(atoi(command.argv[1]));
		if (set_place_data.id == ERROR.id)
			break;//������ص��Ǵ���ڵ㣬��ֱ���˳��ò�ѭ��
		const string key_name = command.argv[2];
		const int new_value = atoi(command.argv[3]);
		int key_index = 0;
		for (; key_index < key.size(); ++key_index)
		{
			if (key_name == key[key_index])
				break;
		}
		if (key_index == key.size())
			break;//��ʱ�����Բ�����

#ifdef RUN_COMMAND_SHOW
		printf(LIGHT_BLUE "<SET POINT>  " NONE);
		cout << set_place_data << " ";
#endif
		AVL_Reset_Data(set_place_data, new_value, key_index);
#ifdef RUN_COMMAND_SHOW
		cout << "=> " << set_place_data;
		printf(LIGHT_BLUE " OVER" NONE);
		cout << endl;
#endif

	}break;
	case 5:
	{
		assert(0);
		//�������
	}break;
	default:break;
	}
}

void Table::AVL_Reset_Data(/*const */Data& data, const int& new_value, const int& value_index)
{
	const int data_id = data.id;
	const AVL_Data_Node<int> delete_place_data(data.value[value_index], 0, 0);
	const ID_Index_Node index_node(data_id, 0);
	BinNode<AVL_Data_Node<int> > *&delete_place = value_tree[value_index].search(delete_place_data);
	const int delete_index = delete_place->data._index.find(index_node);
	const int data_index = delete_place->data._index[delete_index].index; //�ҵ����ݵ�����
	delete_place->data._index.erase(delete_index); //���ڵ��index�����еĸ�indexɾ��
	//Data new_data = data;
	data.value[value_index] = new_value;
	//cout << "?" << endl;
	AVL_Insert_Data(data, data_index);
}








//�Զ��������ܵĲ��Ժ���
void Table::test1()
{
	AVL_Data_Node<int> x(998911, 0, 0);
	BinNode<AVL_Data_Node<int> > *find = id_tree.search(x);
	for (int i(0); i < find->data._index.size(); ++i)
		//cout << data[find->data._index[i].index].id << endl;
		cout << data[find->data._index[i].index] << endl;
}

void Table::test2()
{
	AVL_Data_Node<int> x(72, 0, 0);
	BinNode<AVL_Data_Node<int> > *&find = value_tree[0].search(x);
	find = find->succ();
	for (int i(0); i < find->data._index.size(); ++i)
		//cout << data[find->data._index[i].index].id << endl;
		cout << data[find->data._index[i].index] << endl;
}
