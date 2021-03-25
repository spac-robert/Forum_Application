#pragma once
#include "BaseRepository.h"
#include <string>

template <typename T>
class UsersRepo :public BaseRepository<T> {
	//Class for operation for users
public:
	virtual T* find_user_by_name(std::string name)= 0;
};