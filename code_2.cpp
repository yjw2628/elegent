#include<iostream>
#include<string>
#include<fstream>
 
using namespace std;

string key_word[32] =
{
	"auto","break","case","char","const","continue","default","do ",
	"double","else","enum","extern","float","for","goto","if","int",
	"long","register","return","short","signed","sizeof","stastic",
	"struct","switch","typedef","union","unsigned","void","volatile","while"
};
string str_txt;

//ִ��Ԥ���� ���� 1."...�� 2.//... 3./* ... */ �����	 
void Pretreatment( )
{
	for ( int i = 0,j = i; i < (int)str_txt.length(); i++ )
	{
		if ( str_txt[i] == '/' && str_txt[i+1] == '/' )
		{
			j = i;
			while ( str_txt[j] != '\n' )
			{
				j ++;
			}
			str_txt.erase(i,j - i + 1);
		}
		if ( str_txt[i] == '/' && str_txt[i+1] == '*' )
		{
			j = i + 2;
			while ( str_txt[j] != '*' )
			{
				j ++;
			}
			str_txt.erase(i,j+2-i);
		}
		if ( str_txt[i] == '"')
		{
			j = i+1;
			while ( str_txt[j] != '"' )
			{
				j ++;
			}
			str_txt.erase(i,j-i+1);
		}
	}
}

//����keyword������������ 
void keyword_find( )
{
	int total=0;
	for ( int i=0; i<32; i++ )
	{
		int count = 0;
		size_t position = str_txt.find(key_word[i]);
		while ( position != str_txt.npos )
		{
			count ++;
			position = str_txt.find(key_word[i],position+1);
		}
		total += count;
	}
	printf ("total num: %d\n",total);	
}

//�����м���switch-case�ṹ���������case����
void switch_case_find()
{
 	size_t switch_position = str_txt.find(key_word[25]); 
	size_t case_position;
	int switch_num = 0;
	int case_num[100] = {0};
	while ( switch_position != str_txt.npos )
	{
		switch_num ++;
		case_position = str_txt.find(key_word[2],switch_position);
		while ( case_position != str_txt.npos )
		{
			case_num[switch_num-1] ++;
			case_position = str_txt.find(key_word[2],case_position+1);
		}
		switch_position = str_txt.find(key_word[25],switch_position+1);
	}
	for ( int i=0; i < switch_num - 1; i++ )
	{
		case_num[i] -= case_num[i+1];
	}
	cout << "switch num: " << switch_num << endl;
	cout << "case num: ";
	for ( int i=0; i<switch_num; i++)
	{
		cout << case_num[i] << " ";
	}
	cout << endl;
} 
//�����м���if-else/if-elseif-else �ṹ
void if_else_find(int level_1)
{
	int c[100] = {0};
	int head = 0,ebp = 0;
	int if_else = 0,if_elseif_else = 0;
	size_t if_position = str_txt.find(key_word[15]);
	if ( if_position != str_txt.npos )
	{
		c[ebp] = 1;
		ebp ++;
		for ( int i = if_position+1; i < (int)str_txt.length(); i++ )
		{
			if ( str_txt.compare(i,7,"else if") == 0)
			{
				c[ebp] = 2;
				ebp ++;
				i += 7;
			}
			else if ( str_txt.compare(i,2,"if") == 0 )
			{
				c[ebp] = 1;
				ebp ++;
				i += 2;
			}
			else if ( str_txt.compare(i,4,"else") == 0)
			{
				int j = ebp-1;
				if ( c[j] != 1 && c[j] == 2 )
				{
					while ( c[j] != 1 )
					{
						j--;
					}
					int ebp_1 = j;
					for ( j; j<ebp; j++)
					{
						c[j] = 0;
					}
					ebp = ebp_1;
					if_elseif_else ++;
				}
				else if ( c[j] == 1 )
				{
					if_else ++;
					c[j] = 0;
					ebp = j;
				}
				i += 4;				
			}

		}
	}
	if ( level_1 >= 3 ) cout << "if-else num: " << if_else << endl;
	if ( level_1 == 4 )	cout << "if-elseif-else num: " << if_elseif_else << endl;
}
 
int main()
{
	int count = 0;
	char file_path[100] = {'\0'};
	int level;
	cin.getline (file_path,100);
	cin >> level;
	fstream file;
	file.open (file_path);
	string temp;
	while ( file.good() )
	{
		getline(file,temp);		
		str_txt = str_txt + temp + '\n';
	}
	
	//Ԥ����
	Pretreatment();	
	//ͳ�ƹؼ������� 
	keyword_find();
	if ( level > 1 )
	{
	 	//����switch-case�ṹ
		switch_case_find();
		if ( level > 2 )
		{
			//�����м���if-else�ṹ
			if_else_find( level );
		}  
	}
	file.close(); //�ر��ļ� 
	return 0;
}

