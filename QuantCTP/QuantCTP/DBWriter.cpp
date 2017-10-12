#include "stdafx.h"
#include "DBWriter.h"

DBWriter::DBWriter() {
	user = ROOT;
	pswd = PSWD;
	host = DBHOST;
	table = FUTURE_TABLE;
	port = 3306;
	my_db = new MYSQL();
	mysql_init(my_db);
	DBWorker = thread(&DBWriter::DBUpdate, this);
	if (mysql_real_connect(my_db, host.c_str(), user.c_str(), pswd.c_str(), table.c_str(), port, NULL, 0)) {
		cout << "Future database connect succeed!" << endl;
	}
	else
		cout << "Failed to connect future database!" << endl;
}

DBWriter::~DBWriter() {
	//数据库终止操作
	if (my_db) {
		mysql_close(my_db);
		cout << "Succeed closing db connection!" << endl;
	}
	//线程终止操作
	dq.push_back("EOF"); //表示传输终止
	empty.notify_all();
	DBWorker.join();
}

void DBWriter::DBRead() {
	if (!mysql_query(my_db, "select * from future_info")) {
		MYSQL_RES *result = mysql_store_result(my_db);
		MYSQL_ROW sql_row;
		if (result) {
			int i, j;
			j = mysql_num_fields(result);
			while (sql_row = mysql_fetch_row(result)) {
				for (i = 0; i<j; i++)
				{
					cout << sql_row[i] << " ";
				}
				cout << endl;
			}
		}
		else {
			cout << "Empty data!" << endl;
		}
	}
	else {
		cout << "Query error!" << endl;
	}
}

void DBWriter::DBInsert(FT_DATA *fd) {
	string fid = fd->id;
	string insert_sentence;
	if(fid.substr(0,2)=="IF") //handle IF contract exception
		insert_sentence = "INSERT INTO ifsh (future_id, time, open, high, low, close, ask1, bid1, askvol1, bidvol1, vol, interest, holding) VALUES (";
	else
		insert_sentence = "INSERT INTO " + ((fid[1]>='0' && fid[1] <= '9')? fid.substr(0,1): fid.substr(0, 2)) + " (future_id, time, open, high, low, close, ask1, bid1, askvol1, bidvol1, vol, interest, holding) VALUES (";
	insert_sentence += "'"+ fd->id + "', ";
	insert_sentence += "'" + fd->time + "', ";
	insert_sentence += std::to_string(fd->open) + ", ";
	insert_sentence += std::to_string(fd->high) + ", ";
	insert_sentence += std::to_string(fd->low) + ", ";
	insert_sentence += std::to_string(fd->close) + ", ";
	insert_sentence += std::to_string(fd->ask1) + ", ";
	insert_sentence += std::to_string(fd->bid1) + ", ";
	insert_sentence += std::to_string(fd->askvol1) + ", ";
	insert_sentence += std::to_string(fd->bidvol1) + ", ";
	insert_sentence += std::to_string(fd->vol) + ", ";
	insert_sentence += std::to_string(fd->interest) + ", ";
	insert_sentence += std::to_string(fd->holding) + ");";
	std::unique_lock <std::mutex> lck(mtx);
	if (dq.size() == max_size) //非阻塞模式生产者
		cout << "Buffer is full! Drop current data!" << endl;
	else 
		dq.push_back(insert_sentence);
	empty.notify_all();
	lck.unlock();
}

const DBWriter *DBWriter::GetInstance() {
	return this;
}

void DBWriter::DBUpdate() {
	while (true) {
		std::unique_lock <std::mutex> lck(mtx);
		while (dq.size() == 0)
			empty.wait(lck);
		if (dq[0] == "EOF") 
			return;
		int res = mysql_query(my_db, dq[0].c_str());
		if (res) 
			cout << mysql_error(my_db) << endl;
		dq.pop_front();
		lck.unlock();
	}
}