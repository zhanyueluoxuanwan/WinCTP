//���õ�������д�����ݿ�
#pragma once
#include "mysql.h"
#include <string>
#include "DataInfo.h"

class DBWriter{
public:
	DBWriter();							//���캯�����������ݿ�����
	virtual ~DBWriter();				//���������������ͷ���Դ
	virtual void DBRead();				//��ȡ���ݿ����ݣ����ڲ���
	virtual void DBInsert(FT_DATA *fd); //����Ϣ���뵽���ݿ���
	void DBDelete();					//ɾ������ʱ����Ҫ
	const DBWriter *GetInstance();		//���س��������ݿ�ָ��
private:
	MYSQL *my_db;
	string user;
	string pswd;
	string host;
	string table;
	unsigned int port; //���ݿ�PORT
};