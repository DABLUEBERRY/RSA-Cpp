
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
class RSAEncryptDemo {

public:

	static int StartUp()
	{

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

		std::string _message = "appkey=A9F49FDD39&userid=A443CCCA8AB6633&token=651e3766-1d8d-46ba-aa3e-83f034234e7b";


		RSACrypto* _RSACrypto = new RSACrypto(_publicKey, _privateKey);
		_RSACrypto->InitRsa();
		std::string _utf8Message;
		std::string  _encrypted;
		std::string _encryptedBase64;
		std::string verify_data;

		//����ʾ��******************************************************************************************************

		//��Կ����
		//===========================================================================================
		Encoder _encoder = Encoder();
		//1�� src =  UTF8.encode����(��Ϣ��)
		_utf8Message = _encoder.AnsiStringToUTF8String(_message);
		//2�� _encrypted =  RSA��Կ���ܣ�src��
		bool success = _RSACrypto->EncryptByPublicKey(_utf8Message, _encrypted);
		//3�� base64Str =   base64.encode����(_encrypted )
		_encryptedBase64 = OpenSSL_Base64Encode(_encrypted.data(), _encrypted.length(), false);
		//4�� ����verify_data = UrlEncode���루base64Str ��
		verify_data = _encoder.UrlEncode(_encryptedBase64);
		//===========================================================================================

		//˽Կǩ��
		//===========================================================================================
		std::string _sign;
		//1�� _sign = RSA˽Կǩ������Ϣ�壩
		bool success2 = _RSACrypto->SignByPrivateKey(_message, _sign);
		//2�� base64Str =   base64����(_sign )
		std::string _signBase64 = OpenSSL_Base64Encode(_sign.data(), _sign.length(), false);
		//3�� ����verify_sign = UrlEncode���루_signBase64 ��
		auto verify_sign = _encoder.UrlEncode(_signBase64);
		//===========================================================================================

		//�õ� ���յ� ��֤��¼״̬ url  : finalStr
		std::string finalStr = "https://api.mguwp.com/user/verifySignin?verify_data=" + verify_data + "&verify_sign=" + verify_sign + "\n";
		cout << "Url:\n" << finalStr << endl;
		OutputDebugStringA(LPCSTR(finalStr.data()));

		//����ʾ��******************************************************************************************************
		return 0;
	}
};
