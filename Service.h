#pragma once
#include "ConcretePostRepository.h"
#include "ConcreteUserRepository.h"

class Service {
private:
	UsersRepo<User>* user_repository;
	PostsRepo<Post, User>* post_repository;
	//UserValidator user_validator;
	//ValidationException validation_exception;
public:
	Service(UsersRepo<User>* user_repository, PostsRepo<Post, User>* post_repository):user_repository(user_repository),
		post_repository(post_repository){
	}
	~Service() {
	}

	//Login to database
	User* login(string name, string password) {

		return user_repository->find_user_by_name(name);
	}

	//Createing an account
	User* sign_in(string name, string password) {

		User* user = new User("", name, password, "user");
		user_repository->insert_data(user);
		return user_repository->find_user_by_name(name);
	}

	//Find user using his name
	User* find_user_by_name(string name) {
		return user_repository->find_user_by_name(name);
	}

	//Inser post using user for his id
	void posting(User* user, string title, string to_post) {
		Post* post = new Post("", user->get_id(), title, to_post);
		post_repository->insert_data(post);
	}

	//Get all uers
	vector<User*> get_all_users() {
		return user_repository->get_all();
	}

	//Delete user using his name
	void delete_user(string name) {

		//Find if user exist in database
		User* user = user_repository->find_user_by_name(name);
		user_repository->delete_data(user);
	}

	//Get all posts from a user
	vector<Post*>get_all_posts(User* user) {
		return post_repository->find_posts_by_user(user);
	}

	//Delete post using his id
	void delete_post_by_id(string id_post) {
		Post* post = post_repository->search_post_by_id_post(id_post);
		post_repository->delete_data(post);
	}

	//Update to admin an user 
	void promote_user(string name) {
		User* user = user_repository->find_user_by_name(name);
		try {
			user_repository->update_data(user);
		}
		catch (exception ex) {
			throw;
		}
	}

	//Edit a post
	void edit_post(User* user,string id_post,string title, string to_post) {

		Post* post = post_repository->search_post_by_id_post(id_post);
		if (post->get_user_id() != user->get_id()) {
			throw exception("Can't finde the post");
		}
		else {
			post->set_title(title);
			post->set_post(to_post);
			post_repository->update_data(post);
		}
	}
};