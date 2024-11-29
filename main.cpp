#define _CRT_SECURE_NO_WARNINGS
#include <tchar.h>
#include "MyBD.h"
#define	  stop __asm nop

int _tmain(int argc, _TCHAR* argv[])
{
	//////////////////////////////////////////////////////////////////////

	/*

		 ����������� "���� ������" � ����������� ����������� ��������������
		//�������. ������ �������� ������� (���� � ������� ��������, ������� ���������� ��������
		//� ���� ���� �� �����), � �������: ���, �������, ���������, ��������...
		//����������:
		//���������� ����������� � ����
		//���������� ���������� �� ����
		//����� ���������� � ���������� ����������
		//����� ���� (��� ������������) ���������� � ���� �����������
	*/



	stop
		Base bd1;	//�������� ������ ����

	//��������� ����������� � ����
	bd1["Ivanov"] = MyData(MALE, 20, "AAA", 4);
	bd1["Petrova"] = MyData(FMALE, 30, "BBB", 7);
	bd1["Sidorov"] = MyData(MALE, 40, "CCC", 9);

	stop
	
	std::cout << bd1; //������� ���������� ��� ���� �����������

	std::cout << bd1["Petrova"]; //������� ���������� � ����������

	bd1.deletePair("Petrova"); //��������� ����������
	std::cout << bd1; 



	//������� 2.1. �������� 2 �����  ����  bd1
	Base bd2 = bd1;

	std::cout << bd2; //������� ���������� ��� ���� �����������  �� ���� bd2
	Base bd3 = bd1;
	std::cout << bd3; //������� ���������� ��� ���� �����������  �� ���� bd3

	//������� 2.2.  
	//�������� ����������� � ����  bd2
	bd2["Alekseva"] = MyData(FMALE, 50, "DDD", 11);
	std::cout << bd2; 
	bd1 = bd2;   //  �� "�������" � "���������"

	std::cout << bd1; 
	bd2["Dmitriev"] = MyData(MALE, 60, "EEE", 12);

	bd1 = bd2;   //  �� "�������" � "���������"
	std::cout << bd1; 

	//������� 2.3.
	bd1 = bd3;   //  �� "���������"  � "�������" 

	std::cout << bd1; 


	//������� 3. ���������� ��� ��������� �����������

	Base bd4 = std::move(bd2);
	std::cout << bd4; 
	std::cout << bd2; 

	//	������� 3.2. 
	
	bd3 = std::move(bd4);	
	std::cout << bd3;
	std::cout << bd4; 

	//������� 4.  ����������

	std::cout << bd3;
	bd3.Sort();
	std::cout << bd3;


	return 0;
}

