#pragma once
#include <iostream>
#include <string>
#include <ostream>

class User {

private:
	std::string id, name, pass, type;

public:
	User() {
		this->id = "";
		this->name = "";
		this->pass = "";
		this->type = "user";
	}
	User(std::string id, std::string name, std::string pass, std::string type) {
		this->id = id;
		this->name = name;
		this->pass = pass;
		this->type = type;
	}
	~User() {
		this->id = "";
		this->name = "";
		this->pass = "";
		this->type = "";
	}
	//Getters
	std::string get_id() {
		return this->id;
	}
	std::string get_name() {
		return this->name;
	}
	std::string get_pass() {
		return this->pass;
	}
	std::string get_type() {
		return this->type;
	}

	//Setters
	void set_id(std::string new_id) {
		this->id = new_id;
	}
	void set_name(std::string new_name) {
		this->name = new_name;
	}
	void set_pass(std::string new_pass) {
		this->pass = new_pass;
	}

	void set_type(std::string new_type) {
		this->type = new_type;
	}

	bool operator ==(User account) {
		return account.name == name and account.pass == pass and account.type == type;
	}

	bool operator !=(User account) {
		return  !(account.name == name and account.pass == pass and account.type == type);
	}

	User& operator =(User &user){

		this->set_id(user.id);
		this->set_name(user.name);
		this->set_pass(user.pass);
		this->set_type(user.type);

		return *this;
	}

	User* clone()
	{
		return new User(*this);
	}

	friend std::ostream& operator <<(std::ostream& os, User* account) {

		os << "Id: " << account->get_id() << " | Name: " << account->get_name() << " | Type: " << account->get_type();
		return os;
	}
};