#ifndef CHTTP_CLIENT_H
#define CHTTP_CLIENT_H
#include <string>

class CHttpClient
{
public:
	CHttpClient();
	~CHttpClient();
	/**
	*@brief HTTP POST����
	*@param strUrl �������,�����Url��ַ,��:http://www.baidu.com
	*@param strPost �������,ʹ�����¸�ʽpara1=val12=val2&��
	*@param strResponse�������,���ص�����
	*@return  �����Ƿ�Post�ɹ�
	*/
	int Post(const std::string & strUrl, const std::string & strPost, std::string & strResponse);

	/**
	*@brief HTTP GET����
	*@param strUrl�������,�����Url��ַ,��:http://www.baidu.com
	*@param strResponse�������,���ص�����
	*@return �����Ƿ�Post�ɹ�
	*/
	int Get(const std::string& strUrl, std::string& strResponse);

	/**
	*@brief HTTPS POST����,��֤��汾
	*@param strUrl�������,�����Url��ַ,��:https://www.alipay.com
	*@param strPost�������,ʹ�����¸�ʽpara1=val12=val2&��
	*@param strResponse�������,���ص�����
	*@param pCaPath�������,ΪCA֤���·��.�������ΪNULL,����֤��������֤�����Ч��.
	*@return �����Ƿ�Post�ɹ�
	*/
	int Posts(const std::string& strUrl, const std::string& strPost, std::string& strResponse, const char* pCaPath = NULL);

	/**
	*@brief HTTPS GET����,��֤��汾
	*@param strUrl�������,�����Url��ַ,��:https://www.alipay.com
	*@param strResponse�������,���ص�����
	*@param pCaPath�������,ΪCA֤���·��.�������ΪNULL,����֤��������֤�����Ч��.
	*@return �����Ƿ�Post�ɹ�
	*/
	int Gets(const std::string& strUrl, std::string& strResponse, const char* pCaPath = NULL);
public:
	void SetDebug(bool bDebug);

private:
	bool m_bDebug;
};
#endif