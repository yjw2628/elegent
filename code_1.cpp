


/*这款是没有划分函数且没有划分level的版本，执行4最高级*/
/* 附带输出源.c/.cpp 文件*/ 
//。 。 

#include<bits/stdc++.h>

using namespace std;

string key_word[32] =
{
	"auto","break","case","char","const","continue","default","do ",
	"double","else","enum","extern","float","for","goto","if","int",
	"long","register","return","short","signed","sizeof","stastic",
	"struct","switch","typedef","union","unsigned","void","volatile","while"
};

int main()
{
	int i=0,count=0;
	string str;
	char file_path[100];
	int level;
	cin.getline(file_path,100);
	cin >> level;
	fstream file;
	file.open(file_path);
	string a;
	string b;
	
	while(file.good())
	{
		getline(file,a);		
		b=b+a+'\n';
	}
	cout<<b;
	
	//预处理，把 1."...” 2.//... 3./* ... */ 处理掉	 
	for(int i=0,j=i;i<b.length();i++)
	{
		if(b[i] == '/' && b[i+1] == '/')
		{
			j=i;
			while( b[j] != '\n')
			{
				j++;
			}
			b.erase(i,j-i+1);
		}
		if(b[i] == '/' && b[i+1] == '*')
		{
			j=i+2;
			while( b[j] != '*' )
			{
				j++;
			}
			b.erase(i,j+2-i);
		}
		if(b[i] == '"')
		{
			j=i+1;
			while( b[j] != '"')
			{
				j++;
			}
			b.erase(i,j-i+1);
		}
	}

	cout<<"预处理后的结果如下"<<endl;
	cout<<b<<endl;
	//
	//统计关键字数量 
	size_t position;
	for(int i=0;i<32;i++)
	{
		position = b.find(key_word[i]);
		while( position != b.npos )
		{
			count++;
			position = b.find(key_word[i],position+1);
		}	
	}
	printf("\ntotal num: %d\n",count);
	
	//查找有几组switch case结构，每组switch有几个case
	size_t switch_position = b.find(key_word[25]); //最后一个switch出现位置 
	size_t case_position;
	int switch_num = 0;
	int case_num[10] = {0};
	while( switch_position != b.npos )
	{
		switch_num++;
		case_position = b.find(key_word[2],switch_position);
		while( case_position != b.npos )
		{
			case_num[switch_num-1]++;
			case_position = b.find(key_word[2],case_position+1);
		}
		switch_position = b.find(key_word[25],switch_position+1);
	}
	for(int i=0;i<switch_num-1;i++)
	{
		case_num[i] -= case_num[i+1];
	}
	cout<<"switch num: "<<switch_num<<endl;
	cout<<"case num: ";
	for(int i=0;i<switch_num;i++)
	{
		cout<<case_num[i]<<" ";
	}cout<<endl;
	
	//查找有几组if-else结构
	int c[100]={0};
	int head=0,ebp=0;
	int if_else=0,if_elseif_else=0;
	size_t if_position = b.find(key_word[15]);
	if( if_position != b.npos )
	{
		c[ebp] = 1;
		ebp++;
		for(int i = if_position+1;i < b.length(); i++)
		{
			if( b.compare(i,7,"else if") == 0)
			{
				c[ebp] = 2;
				ebp ++;
				i += 7;
			}
			else if( b.compare(i,2,"if") == 0 )
			{
				c[ebp] = 1;
				ebp ++;
				i += 2;
			}
			else if( b.compare(i,4,"else") == 0)
			{
				int j=ebp-1;
				if( c[j] != 1 && c[j] == 2 )
				{
					while( c[j] != 1 )
					{
						j--;
					}
					int ebp_1=j;
					for( j;j<ebp;j++)
					{
						c[j]=0;
					}
					ebp = ebp_1;
					if_elseif_else ++;
				}
				else if( c[j] == 1)
				{
					if_else ++;
					c[j] = 0;
					ebp = j;
				}
				i += 4;				
			}

		}
	}
	cout<<"if-else num: "<<if_else<<endl;
	cout<<"if-elseif-else num: "<<if_elseif_else<<endl;
	
//	cout<<"ebp: "<<ebp;
	file.close();
	return 0;
}

