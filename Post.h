#pragma once
#include <string>
#include <ostream>
class Post {

private:
	std::string title, posts, id, id_user;

public:
	Post() {
		id = "";
		id_user = "";
		title = "";
		posts = "";
	}
	Post(std::string  id, std::string  id_user, std::string title, std::string posts) {

		this->id = id;
		this->id_user = id_user;
		this->title = title;
		this->posts = posts;
	}

	Post(const Post& post) {
		this->id = post.id;
		this->id_user = post.id_user;
		this->title = post.title;
		this->posts = post.posts;
	}
	~Post() {
		id = "";
		id_user = "";
		title = "";
		posts = "";
	}

	//Setters
	void set_id(std::string id) {
		this->id = id;
	}
	void set_id_user(std::string id) {
		this->id_user = id;
	}
	void set_title(std::string title) {
		this->title = title;
	}
	void set_post(std::string posts) {
		this->posts = posts;
	}

	//Getters
	std::string get_id() {
		return this->id;
	}
	std::string get_user_id() {
		return this->id_user;
	}
	std::string get_title() {
		return this->title;
	}
	std::string get_post() {
		return this->posts;
	}

	bool operator == (Post post) {

		return (post.id_user == id_user and post.posts == posts and post.title == title);
	}

	bool operator != (Post post) {

		return !(post.id_user == id_user and post.posts == posts and post.title == title);
	}

	friend std::ostream& operator <<(std::ostream& os, Post post) {
		os << "----------------------------------\n";
		os << "ID: " << post.get_id() << "\n" << "Title: " << post.get_title() << "\n" << "Post: " << post.get_post() << "\n";

		return os;
	}
};