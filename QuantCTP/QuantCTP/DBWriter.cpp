#include "stdafx.h"
#include "DBWriter.h"

DBWriter::DBWriter() {
	user = ROOT;
	pswd = PSWD;
	host = DBHOST;
	table = FUTURE_TABLE;
	port = 3306;
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
	if (mysql_query(my_db, "select * from future_info")) {

	}
	else {
		cout << "Query error!" << endl;
	}
}

void DBWriter::DBInsert(FT_DATA &fd) {

}
