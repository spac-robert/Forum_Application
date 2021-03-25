#pragma once
#include "User.h"
#include "ConcreteUserRepository.h"
#include <exception>
#include <vector>
#include <algorithm>
#include <regex>  
#include <string>

using namespace std;

class UserValidator
{
protected:
	int err;
	string message;
	UsersRepo<User>* user_repository;

public:

	UserValidator(UsersRepo<User>* user_repository):user_repository(user_repository) {
		err = 0;
		message = "";
	}
	int name_exist(string name) {
		err = 0;
		User* user = user_repository->find_user_by_name(name);
		if (user->get_name() == "") {
			err++;
			message = "Username doesn't exist\n";
		}
		return err;
	}

	int name_exist(string name,string password) {

		err = 0;
		User* user = user_repository->find_user_by_name(name);

		if (!(user->get_name() == name and user->get_pass() == password)) {
			err++;
			message = "Username or password incorect\n";
		}
		return err;
	}

	int name_does_not_exist(string name) {

		err = 0;
		User* user = user_repository->find_user_by_name(name);
		if (!(user->get_name() == "")) {
			err++;
			message = "Username already taken\n";
		}
		return err;
	}

	int validate_password(string password) {
		err = 0;
		regex regx("[@_!#$%^&*()<>?/|}{~:]");
		if(all_of(password.begin(),password.end(),islower) ){
			err++;
			message = "Password must contain minimum one:\n -upper letter \n -symbol( !@#$%^&*()_+~ )\n ";
		}
		if (regex_search(password, regx) == 0) {
			err++;
			message = "Password must contain minimum one:\n -upper letter \n -symbol( !@#$%^&*()_+~ )\n ";
		}
		return err;
	}


	string toString(){

		return message;
	}
	~UserValidator() {}
};

