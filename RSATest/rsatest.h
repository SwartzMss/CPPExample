#ifndef RSATEST_H
#define RSATEST_H

#include <QtWidgets/QDialog>
#include "ui_rsatest.h"
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <string>
#include <iostream>
#include <io.h>
#include <fstream>
using namespace  std;
class RSATest : public QDialog
{
	Q_OBJECT

public:
	RSATest(QWidget *parent = 0);
	~RSATest();
	//产生公钥和密钥
	void CreateKey();
	//解密
	std::string DecryptData(string data);
	//	加密
	std::string EncryptData(string data);
	//获取公钥的字符
	std::string ReadPublicKey();
public slots:
	void Encode();
	void Decode();


private:
	Ui::RSATestClass ui;
	string m_strdata;
	/* BASE64加密算法实现 */
	int	Base64Encode(const char* pInputBuf, int nInputBufLen, char* pOutputBuf);
	/* BASE64解密算法实现 */
	int	Base64Decode(const char *pInputBuf, int nInputBufLen, char *pOutputBuf);


};

#endif // RSATEST_H
