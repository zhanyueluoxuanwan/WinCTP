//将得到的行情写入数据库
#pragma once
#include "mysql.h"
#include <string>
#include "DataInfo.h"

class DBWriter{
public:
	DBWriter();							//构造函数，进行数据库链接
	virtual ~DBWriter();				//析构函数，用于释放资源
	virtual void DBRead();				//读取数据库内容，用于测试
	virtual void DBInsert(FT_DATA *fd); //将信息插入到消息队列dq中
	virtual void DBUpdate();			//将消息队列中的数据插入到数据库中，由子线程操作
	void DBDelete() {};					//删除，暂时不需要
	const DBWriter *GetInstance();		//返回常量形数据库指针
private:
	MYSQL *my_db;
	string user;
	string pswd;
	string host;
	string table;
	unsigned int port;	//数据库PORT
	//数据库异步写变量
	std::thread DBWorker;					//异步写线程，采用简单的生产者消费者模型，当前负载采用单一线程
	std::condition_variable empty;			//同步信号量
	std::mutex mtx;							//互斥锁
	const int max_size = MAX_ARRAY_SIZE;	//队列最大长度
	deque<string> dq;						//数据库信息队列
};