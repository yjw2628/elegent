/*��������ҵ� if-elseif-else ���Դ���*/

#include <iostream>

using namespace std;
 
int main ()
{
   // �ֲ���������
   int a = 100;
 
   // ��鲼������
   if( a == 10 )
   {
       // ��� if ����Ϊ�棬�������������
       cout << "a ��ֵ�� 10" << endl;
   }
   else if( a == 20 )
   {
       // ��� else if ����Ϊ�棬�������������
       cout << "a ��ֵ�� 20" << endl;
   }
   else if( a == 30 )
   {
       // ��� else if ����Ϊ�棬�������������
       cout << "a ��ֵ�� 30" << endl;
   }
   else
   {
       // ���������������Ϊ�棬�������������
       cout << "û��ƥ���ֵ" << endl;
   }
   cout << "a ��׼ȷֵ�� " << a << endl;
 
   return 0;
}
