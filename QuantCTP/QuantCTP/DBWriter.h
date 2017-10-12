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
	virtual void DBInsert(FT_DATA *fd); //����Ϣ���뵽��Ϣ����dq��
	virtual void DBUpdate();			//����Ϣ�����е����ݲ��뵽���ݿ��У������̲߳���
	void DBDelete() {};					//ɾ������ʱ����Ҫ
	const DBWriter *GetInstance();		//���س��������ݿ�ָ��
private:
	MYSQL *my_db;
	string user;
	string pswd;
	string host;
	string table;
	unsigned int port;	//���ݿ�PORT
	//���ݿ��첽д����
	std::thread DBWorker;					//�첽д�̣߳����ü򵥵�������������ģ�ͣ���ǰ���ز��õ�һ�߳�
	std::condition_variable empty;			//ͬ���ź���
	std::mutex mtx;							//������
	const int max_size = MAX_ARRAY_SIZE;	//������󳤶�
	deque<string> dq;						//���ݿ���Ϣ����
};