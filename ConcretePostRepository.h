#pragma once

#include <string>
#include <mysql.h>
#include "User.h"
#include "PostsRepository.h"
#include "Post.h"
#include <vector>


class ConcretePostRepository :public PostsRepo<Post,User> {
	//Class is wich is implemented all virtual functions from BaseRepository and PostRepository
private:
	MYSQL* conn;
public:
	/*ConcretePostRepository() {
		conn = mysql_init(NULL);
		mysql_real_connect(conn, "localhost", "root", "Spa306r*4834", "forumdatabase", 3306, NULL, 0);

	}*/
	ConcretePostRepository(std::string nameDatabase) {
		//Connect to my database
		conn = mysql_init(NULL);
		mysql_real_connect(conn, "localhost", "root", "Spa306r*4834", nameDatabase.c_str(), 3306, NULL, 0);

	}
	~ConcretePostRepository() {
	}

	//Return all posts 
	std::vector<Post*> get_all() {
		
		MYSQL_RES* result;
		MYSQL_ROW row;
		int num_fields;
		std::vector<Post*>arr;
		Post* account;
		//retrieve and display data
		mysql_query(conn, "SELECT * FROM posts");
		result = mysql_store_result(conn);
		num_fields = mysql_num_fields(result);
		while ((row = mysql_fetch_row(result)))
		{
			account = new Post(row[0], row[1], row[2], row[3]);
			arr.push_back(account);

		}
		mysql_free_result(result);//clear result set from memory
		return arr;
	}


	//Insert post in database
	void insert_data(Post* post) {
		MYSQL_RES* result;
		MYSQL_ROW row;
		std::string str;
		str = "insert into posts values(null," + post->get_user_id() + ",'" + post->get_title() + "','" + post->get_post() + "')";
		mysql_query(conn, str.c_str());
	}

	//Search and return all post from an user if taht user has post or return an empty vector with posts
	std::vector<Post*> find_posts_by_user(User* user) {

		MYSQL_RES* result;
		MYSQL_ROW row;
		std::vector<Post*>arr;

		std::string str = "SELECT * FROM posts where id_user='" + user->get_id() + "'";
		const char* c = str.c_str();
		mysql_query(conn, c);
		result = mysql_store_result(conn);

		while ((row = mysql_fetch_row(result)))
		{
			if (row[1] == user->get_id()) {
				Post* post = new Post(row[0], std::string(row[1]), std::string(row[2]), std::string(row[3]));
				arr.push_back(post);
			}
		}
		mysql_free_result(result);
		return arr;
	}

	//Delete post from database using post's id for deleting
	void delete_data(Post* post) {

		std::string qstr;
		qstr = "DELETE FROM posts WHERE id_post= '" + post->get_id() + "'";
		mysql_query(conn, qstr.c_str());
	}

	//Update post, change title or post , or bouth
	void update_data(Post* post) {

		MYSQL_RES* result;
		MYSQL_ROW row;
		std::string str;
		str = "update posts set title='" + post->get_title() + "',post='" + post->get_post() + "' where id_user='" + post->get_user_id() + "'";
		mysql_query(conn, str.c_str());
	}

	//Search post using his id , if exist return that post or return an empty post
	Post* search_post_by_id_post(string id_post) {
		MYSQL_RES* result;
		MYSQL_ROW row;
		Post* post;

		std::string str = "SELECT * FROM posts where id_post='" + id_post + "'";
		const char* c = str.c_str();
		mysql_query(conn, c);
		result = mysql_store_result(conn);

		while ((row = mysql_fetch_row(result)))
		{
			if (row[0] == id_post) {
				Post* post = new Post(row[0], std::string(row[1]), std::string(row[2]), std::string(row[3]));
				return post;
			}
		}
		mysql_free_result(result);
		return new Post();
	}
};