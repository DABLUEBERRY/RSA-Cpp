
//�������������ɹ�Կ�Լ���Ӧ˽Կ����Կ�ϴ��������ߺ�̨
//���ڴ���վ http ://web.chacuo.net/netrsakeypair �����ɣ�����ʱ��Կλ��ѡ��1024����Կ��ʽ��PKCS#1
//RSA�㷨ʹ�� openssl ,��ʾ��ʹ�� emersonfxbx.openssl.v140.desktop.x86   NuGet��

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include "RSACrypto.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "UrlEncode.h"
#include "OpenSSL_Base64.h"

using namespace std;

class RSADecryptDemo {
public:
	static int StartUp()
	{
		//�ص�����ʾ������������$param_data��$sign
		std::string param_data = "etRzkAmBx5dbb%2BzggET0Z5rJ6FG8Jsh2hFFHD173og3vr%2F7bwPoueJFytrDFT7g13AkXmpz3vr9sEXFymsueG9UMMPELgJQW0gKLkhj96pA%2BNQLAN53H2%2F%2Fi8Z1Rderj%2Fes59T%2FK7bNQnHS%2Fc1LK3rduAkRFmSdm%2FLACNxHIUXpzXPZtyKRxRb7BuxJX%2B31ytaVrrDRseB9NPD9DFK4TuAMJPZqSZqNFWfzZXcyqTg2a9YVYsW6NCIFoBYv5G7%2F%2FQAFcqNQpXjCUb9ISdLHRffq1fvcqYwwdDAU8FkcGXdOQ9wNjixPj3x67GkJLaYAtwzYnCDLGMIl3T%2F%2B%2FM%2B66qw%3D%3D";
		std::string sign = "cPniGrltgyofwkEeQBVdADTOuOV5rNGi55VM%2FAwd%2BPRySCMqrU0DrE90gi36Q14O00A7x8DbYl2mD9wOu%2F2ZxsaSoIf5CHHjIEEL0xhuFqAA05zP3qvD9D5m8f3ru%2F3oGgRfCbjAOr%2BHHbhZcwcuBwSlGSbJEuVGd6Ia%2ByqbvWQ%3D";

		//MG��Կ��������֤ǩ������ֵ���䡣														-------��Կʹ�� pkcs#8  
		const std::string & _publicKey =
			"-----BEGIN PUBLIC KEY-----\n"\
			"MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDNFs7manJerSGmFOx0mvrCthq8\n"\
			"OTUDEtLJ7d7OaFnoRTuWgYhQ8RiCxYY78Y8UywMk2eiWWcnx7aB86VpqEtua0zl4\n"\
			"XSkc54FHeBkyISjxFdBYiT1PP9ZQY9LEziTGJUnKVItpSKKttzFErY+0YK9BOovr\n"\
			"/yK37RPGDiWpTTJR0QIDAQAB\n"\
			"-----END PUBLIC KEY-----\n";

		//������˽Կ���ɿ������������ɣ����ڽ��ܻص����ݣ��뽫��˽Կ�޸�Ϊ���������ѵ�˽Կ��	--------˽Կʹ�� pkcs#1
		const std::string & _privateKey =
			"-----BEGIN RSA PRIVATE KEY-----\n"\
			"MIICXAIBAAKBgQCLF/ZGuuNwGpS+YRFPr1kMEz+hO7HesleruuyoepVnex4cLP1V\n"\
			"PDVUN6l1VgO6bJk3ToHWGme+MYIyduQwVafm6mJcL3gj5k6UymXFyZCp/+n1B1u3\n"\
			"6NQQLP4/HvW/HhGBwFXhhGTdkzLUhrZE2Xfz6NbwsMdEkDq9nhcXxAC96wIDAQAB\n"\
			"AoGAPUd0R9sEYppDV9CZ+NpOx+QfD2CmT2+Q8maq5tsCwZFbRZyIi6m38P+I19nq\n"\
			"UJKRue0LhJEjjYZwTt1UUPsbuhTYGNpVHzCsie1QVkBX19tlRrhjETisCQF8QSiT\n"\
			"DXnhmaqNXAUGchnCntp85viCXPxHmj0m0ymU5/ctr4CBXIkCQQDq64bdPet2Ky+1\n"\
			"FoFNm/mYk6UlUnkBz+z1akvWYQn3H9fmhOf1gPQknPoHo7A6LZGaL+K/qPTW/7ts\n"\
			"3+qFDuotAkEAl5Mnwd+grqqn0nIW/A6TxZqMBJlqxpbjcfqL+TvEprVXJMFI+ufb\n"\
			"NVrpuljDVfHSZk2NYYtCVy0cK4tLlcZPdwJAIbOsY20QrKFBdN9HqZSo2CTGWnZc\n"\
			"edAUlJitTJIbVeKxnJaQmH3piJ8kl5f6Hj6PVulrxEc+6OFDSDlPcctT+QJAdz53\n"\
			"mpg5qu/q0y6aUnWNX3m0CbJARDdUe8il8c9JZ/Vlty6wIWPiGlmJYuaN1cFGyuDc\n"\
			"Bw8tg7OjY8ZUEmJPBQJBAOao0jpWLKD/9HMM79k5v8Yhm+v5M58B1qtoguhED+Id\n"\
			"UKM5FzeT04lfQtOx10DhkOaS4Rb7/h05hz+in/AQXSo=\n"\
			"-----END RSA PRIVATE KEY-----\n";


		RSACrypto* _RSACrypto = new RSACrypto(_publicKey, _privateKey);
		_RSACrypto->InitRsa();
		std::string _urlDecodeStr;
		std::string _decryptedBase64;
		std::string _decrypted;
		Encoder _encoder = Encoder();

		//����ʾ��******************************************************************************************************
		//ʹ�ÿ�����˽Կ����
		//===========================================================================================
		//1��_urlDecodeStr = UrlDecode���루param_data��
		_urlDecodeStr = _encoder.UrlDecode(param_data);
		//2��_decryptedBase64 = Base64Decode���루_urlDecodeStr��
		_decryptedBase64 = OpenSSL_Base64Decode(const_cast<char*>(_urlDecodeStr.c_str()), _urlDecodeStr.length(), false);
		OutputDebugStringW(LPCWSTR(_decryptedBase64.data()));
		//3��_decrypted = ʹ�ÿ�����˽Կ����RSA����
		bool success = _RSACrypto->DecryptByPrivateKey(_decryptedBase64, _decrypted);
		//4�� �õ����ܺ�� param_data ���� _decrypted
		cout << "param_data = \n" << _decrypted << endl;
		//===========================================================================================

		//ʹ��MG��Կ��֤ǩ��
		//===========================================================================================
		std::string _sign;
		std::string _signDeBase64;
		//1�� _sign = UrlDecode���루sign��
		_sign = _encoder.UTF8UrlDecode(sign);
		OutputDebugStringA(LPCSTR(_sign.data()));
		//2�� _signBase64 = Base64Decode���루_sign��
		_signDeBase64 = OpenSSL_Base64Decode(const_cast<char*>(_sign.c_str()), _sign.length(), false);
		OutputDebugStringA(LPCSTR("\n"));
		OutputDebugStringW(LPCWSTR(_signDeBase64.data()));
		//3�� ʹ��MG��Կ��֤ǩ���� ����1��˽Կ���ܺ�����ݣ�����2��ת���� sign
		bool success2 = _RSACrypto->VerifyByPublicKey(_decrypted, _signDeBase64);
		//3�� ������֤��� = success2
		cout << "��֤���:0Ϊʧ�ܣ�1Ϊ�ɹ� = \n" << success2 << endl;
		//===========================================================================================
		//����ʾ��******************************************************************************************************

		return 0;
	}
};