#pragma once
#include <vector>

template <typename T>
class BaseRepository {
	//Base class for CRUD operetions
	//C - create
	//R - read
	//U - update
	//D - delete
public: 

	BaseRepository() {
	};
	~BaseRepository() {
	};
	virtual std::vector<T*> get_all() = 0;
	
	virtual void insert_data(T* data) = 0;

	virtual void delete_data(T* data) = 0;
	
	virtual void update_data(T* data) = 0;
	
};
