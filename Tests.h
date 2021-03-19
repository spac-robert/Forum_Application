#pragma once
#include "UsersRepository.h"
#include "PostsRepository.h"
#include "ConcreteUserRepository.h"
#include "ConcretePostRepository.h"
#include "UsersRepository.h"
#include "PostsRepository.h"
#include <cassert>
class Tests {

private:

	void test_account() {
		User* user = new User(), *user1=new User("","asd","qwe","user");
		assert(user->get_id() == "");
		assert(user->get_name() == "");
		assert(user->get_pass() == "");
		assert(user->get_type() == "user");

		user->set_id("");
		user->set_name("asd");
		user->set_pass("qwe");
		user->set_type("user");

		assert(*user == *user1);
		
		user->set_type("admin");
		assert(*user != *user1);

		std::cout << "test_account passed\n";
	}

	void test_concrete_user_repository() {
		
		UsersRepo<User>* user_repository = new ConcreteUserRepository("testforumdatabase");
		//ConcreteUserRepository* user_repository = new ConcreteUserRepository("testforumdatabase");
		vector<User*>allAccounts, expectetAccountsInDatabase;
		User* user = new User("", "asd", "qwe", "user"),*user1= new User("", "zxc", "vbn", "user");
	
		expectetAccountsInDatabase.push_back(user);
		user_repository->insert_data(user);

		
		user_repository->insert_data(user1);
		expectetAccountsInDatabase.push_back(user1);
		allAccounts = user_repository->get_all();

		for (int i = 0; i<int(allAccounts.size()); i++) {
			assert(*allAccounts[i] == *expectetAccountsInDatabase[i]);
		}

		user_repository->delete_data(user);
		allAccounts = user_repository->get_all();
		expectetAccountsInDatabase.erase(expectetAccountsInDatabase.begin(), expectetAccountsInDatabase.begin() + 1);
		for (int i = 0; i<int(allAccounts.size()); i++) {
			assert(*allAccounts[i] == *expectetAccountsInDatabase[i]);
		}

		user_repository->update_data(user1);
		expectetAccountsInDatabase.erase(expectetAccountsInDatabase.begin(), expectetAccountsInDatabase.begin() + 1);
		user1->set_type("admin");
		expectetAccountsInDatabase.push_back(user1);
		allAccounts = user_repository->get_all();
		for (int i = 0; i<int(allAccounts.size()); i++) {
			assert(*allAccounts[i] == *expectetAccountsInDatabase[i]);
		}

		user_repository->delete_data(user1);

		cout << "test_concrete_user_repository passed\n";
	}

	void test_post() {

		Post* post = new Post(),*post1 = new Post("1", "1", "Text", "Some text");;

		assert(post->get_id() == "");
		assert(post->get_post() == "");
		assert(post->get_title() == "");
		assert(post->get_user_id() == "");
		
		post= new Post("1", "1", "Text", "Some text");
		assert(post->get_id() == "1");
		assert(post->get_post() == "Some text");
		assert(post->get_title() == "Text");
		assert(post->get_user_id() == "1");

		assert(*post == *post1);

		post->set_title("New Text");
		assert(*post != *post1);

		cout << "test_post passed\n";
	}

	void test_concrete_post_repository() {

		UsersRepo<User>* user_repository = new ConcreteUserRepository("testforumdatabase");
		User* user = new User("", "asd", "qwe", "user");
		user_repository->insert_data(user);
		vector<User*>allAccounts;
		allAccounts = user_repository->get_all();
		user = allAccounts[0];

		PostsRepo<Post, User>* post_repository = new ConcretePostRepository("testforumdatabase");
		Post* post = new Post("",user->get_id(),"Text","Some text");

		vector<Post*> allPosts, expectedPosts;

		post_repository->insert_data(post);
		allPosts = post_repository->get_all();
		expectedPosts.push_back(post);

		for (int i = 0; i<int(allPosts.size()); i++) {
			assert(*allPosts[i] == *expectedPosts[i]);
		}

		post_repository->delete_data(post_repository->find_posts_by_user(user)[0]);
		allPosts = post_repository->get_all();
		assert(int(allPosts.size()) == 0);

		post_repository->insert_data(post);
		allPosts = post_repository->get_all();

		post->set_title("New Title");
		post->set_post("New Post");
		post_repository->update_data(post);
		allPosts = post_repository->get_all();

		assert(*allPosts[0] == *post);

		user_repository->delete_data(user);
		allPosts = post_repository->get_all();
		assert(int(allPosts.size()) == 0);

		cout << "test_concrete_post_repository passed\n";
	}

public:

	void run_tests() {

		this->test_account();
		this->test_concrete_user_repository();
		this->test_post();
		this->test_concrete_post_repository();
	}
};