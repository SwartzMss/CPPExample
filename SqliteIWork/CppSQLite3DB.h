#ifndef _CppSQLite3_H_
#define _CppSQLite3_H_

#include "sqlite3.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <windows.h>
using namespace std;

#define CPPSQLITE_MAX_QUERY 1000000
#define CPPSQLITE_ERROR 1000

class CppSQLite3Exception
{
public:

	CppSQLite3Exception(const int nErrCode,
		char* szErrMess,
		bool bDeleteMsg = true);

	CppSQLite3Exception(const CppSQLite3Exception&  e);

	virtual ~CppSQLite3Exception();

	const int errorCode() { return mnErrCode; }

	const char* errorMessage() { return mpszErrMess; }

	static const char* errorCodeAsString(int nErrCode);

private:

	int mnErrCode;
	char* mpszErrMess;
};

class CppSQLite3Buffer
{
public:

	CppSQLite3Buffer();

	~CppSQLite3Buffer();

	const char* format(const char* szFormat, ...);

	operator const char*() { return mpBuf; }

	void clear();

private:

	char* mpBuf;
};

class CppSQLite3Binary
{
public:

	CppSQLite3Binary();

	~CppSQLite3Binary();

	void setBinary(const unsigned char* pBuf, int nLen);
	void setEncoded(const unsigned char* pBuf);

	const unsigned char* getEncoded();
	const unsigned char* getBinary();

	int getBinaryLength();

	unsigned char* allocBuffer(int nLen);

	void clear();

private:

	unsigned char* mpBuf;
	int mnBinaryLen;
	int mnBufferLen;
	int mnEncodedLen;
	bool mbEncoded;
};

class CppSQLite3Query
{
public:

	CppSQLite3Query();

	CppSQLite3Query(const CppSQLite3Query& rQuery);

	CppSQLite3Query(sqlite3* pDB,
		sqlite3_stmt* pVM,
		bool bEof,
		bool bOwnVM = true);

	CppSQLite3Query& operator=(const CppSQLite3Query& rQuery);

	virtual ~CppSQLite3Query();

	int numFields();

	int fieldIndex(const char* szField);
	const char* fieldName(int nCol);

	const char* fieldDeclType(int nCol);
	int fieldDataType(int nCol);

	const char* fieldValue(int nField);
	const char* fieldValue(const char* szField);

	int getIntField(int nField, int nNullValue = 0);
	int getIntField(const char* szField, int nNullValue = 0);

	double getFloatField(int nField, double fNullValue = 0.0);
	double getFloatField(const char* szField, double fNullValue = 0.0);

	const char* getStringField(int nField, const char* szNullValue = "");
	const char* getStringField(const char* szField, const char* szNullValue = "");

	const unsigned char* getBlobField(int nField, int& nLen);
	const unsigned char* getBlobField(const char* szField, int& nLen);

	bool fieldIsNull(int nField);
	bool fieldIsNull(const char* szField);
	bool fieldIsExist(const char* szField);
	bool eof();

	void nextRow();

	void finalize();

private:

	void checkVM();

	sqlite3* mpDB;
	sqlite3_stmt* mpVM;
	bool mbEof;
	int mnCols;
	bool mbOwnVM;
};

class IDataBase
{
public:
	virtual ~IDataBase() {};
	virtual int OpenDataBase(const char* pDBFileName) = 0;
};

class CppSQLite3DB : public IDataBase
{
public:
	CppSQLite3DB();

	virtual      ~CppSQLite3DB();

	/* �����ݿ� */
	int   OpenDataBase(const char* pDBFileName);
private:
	void         open(const char* szFile);
	void         close();
	void         setBusyTimeout(int nMillisecs);
	bool         tableExists(const char* szTable);
	int			execScalar(const char* szSQL);
	CppSQLite3Query execQuery(const char* szSQL);
	void            checkDB();
	sqlite3_stmt*   compile(const char* szSQL);
private:
	sqlite3*        mpDB;
	int             mnBusyTimeoutMs;
	CRITICAL_SECTION mpCS;
};
#endif