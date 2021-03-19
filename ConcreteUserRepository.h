#pragma once
#include "UsersRepository.h"
#include <string>
#include <mysql.h>
#include "User.h"

using namespace std;

class ConcreteUserRepository :public UsersRepo<User> {
	//Class is wich is implemented all virtual functions from BaseRepository and UserRepository
private:
	MYSQL* conn;

public:
	ConcreteUserRepository(string nameDatabase) {
		//Connect to my database
		conn = mysql_init(NULL);
		mysql_real_connect(conn, "localhost", "root", "Spa306r*4834", nameDatabase.c_str(), 3306, NULL, 0);

	}
	~ConcreteUserRepository() {
	}

	//Return all users 
	vector<User*> get_all() {

		MYSQL_RES* result;
		MYSQL_ROW row;
		int num_fields;
		int i;
		vector<User*>arr;
		User* user;
		//retrieve and display data
		mysql_query(conn, "SELECT * FROM users");
		result = mysql_store_result(conn);
		num_fields = mysql_num_fields(result);
		while ((row = mysql_fetch_row(result)))
		{
			user = new User(row[0], row[1], row[2], row[3]);
			arr.push_back(user);

		}
		mysql_free_result(result);//clear result set from memory
		return arr;
	}

	//Insert user in database
	void insert_data(User* user) {

		string qstr;
		qstr = "insert into users values(null, '" + user->get_name() + "' , '" + user->get_pass() + "','user')";
		mysql_query(conn, qstr.c_str());
	}

	//Delete user from database
	void delete_data(User* user) {

		string qstr;
		qstr = "DELETE FROM users WHERE name= '" + user->get_name() + "'";
		mysql_query(conn, qstr.c_str());
	}

	//search user in database by a name return that user if it founds or an empty User
	User* find_user_by_name(string name) {
		MYSQL_RES* result;
		MYSQL_ROW row;
		int num_fields;
		User* user_find = new User();
		mysql_query(conn, "SELECT * FROM users");
		result = mysql_store_result(conn);
		num_fields = mysql_num_fields(result);
		while ((row = mysql_fetch_row(result)))
		{
			if (row[1] == name) {
				User* user_find = new User(row[0], row[1], row[2], row[3]);
				mysql_free_result(result);
				return user_find;
			}
		}
		mysql_free_result(result);
		return user_find;
	}

	//Update user to admin if he's type is user
	void update_data(User* user) {
		MYSQL_RES* result;
		MYSQL_ROW row;
		string str;
		if (user->get_type() == "user")
			str = "update users set type='admin' where name='" + user->get_name() + "'";
		else
			throw exception("Cand't promote an admin");
		mysql_query(conn, str.c_str());
	}

};