//将得到的行情写入数据库
#pragma once
#include "mysql.h"
#include <string>
#include "DataInfo.h"

class DBWriter{
public:
	DBWriter();					//构造函数，进行数据库链接
	~DBWriter();				//析构函数，用于释放资源
	virtual void DBRead();				//读取数据库内容，用于测试
	void DBInsert(FT_DATA &fd); //将信息插入到数据库中
	void DBDelete();			//删除，暂时不许需要
private:
	MYSQL *my_db;
	string user;
	string pswd;
	string host;
	string table;
	unsigned int port; //数据库PORT
};