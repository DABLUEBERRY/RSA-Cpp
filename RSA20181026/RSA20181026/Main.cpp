#include "RSADecryptDemo.h"
#include "RSAEncryptDemo.h"

int main()
{
	cout << "+++++++++++++++++++++++++++++����ʾ��+++++++++++++++++++++++++++++" << endl;
	//��������ʾ��
	RSAEncryptDemo::StartUp();
	cout << "+++++++++++++++++++++++++++++����ʾ��+++++++++++++++++++++++++++++" << endl;
	//��������ʾ��
	RSADecryptDemo::StartUp();

	int i;
	cin >> i;
	return 0;
}