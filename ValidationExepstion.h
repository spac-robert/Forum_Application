#pragma once
#include <exception>
#include <string>
using namespace std;

class ValidationException : public exception {
private:
	char* msg;
public:
	ValidationException(const char* m) {
		msg = new char[strlen(m)] + 1;
		strcpy_s(msg, strlen(m) + 1, m);
	}

	ValidationException(string s) {
		msg = new char[s.size() + 1];
		for (int i = 0; i < s.size(); i++)
			msg[i] = s[i];
		msg[s.size()] = '\0';
	}

	ValidationException(const ValidationException& ex) {
		msg = new char[strlen(ex.msg)] + 1;
		strcpy_s(msg, strlen(ex.msg) + 1, ex.msg);
	}

	const char* what() const throw()
	{
		return msg;
	}

	~ValidationException() {
		if (this->msg != nullptr)
			delete this->msg;
	}
};
