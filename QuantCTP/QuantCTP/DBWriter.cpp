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
	if (mysql_real_connect(my_db, host.c_str(), user.c_str(), pswd.c_str(), table.c_str(), port, NULL, 0)) {
		cout << "Future database connect succeed!" << endl;
	}
	else
		cout << "Failed to connect future database!" << endl;
}

DBWriter::~DBWriter() {
	if (my_db) {
		mysql_close(my_db);
		cout << "Succeed closing db connection!" << endl;
	}
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
	string insert_sentence = "INSERT INTO future_info (future_id, time, open, high, low, close, ask1, bid1, askvol1, bidvol1, vol, interest, holding) VALUES (";
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
	int res = mysql_query(my_db, insert_sentence.c_str());
	/*
	if (!res) {
		cout << "Successfully inserted contract info!" << endl;
	}
	*/
	if (res) cout << mysql_error(my_db) << endl;
}

const DBWriter *DBWriter::GetInstance() {
	return this;
}