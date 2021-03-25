#pragma once
#include "BaseRepository.h"
#include "Post.h"
#include "User.h"

template <typename T, typename H>
class PostsRepo:public BaseRepository<T> {
	//Class for operation for posts
public:

	virtual std::vector<T*> find_posts_by_user(H* user) = 0;
	virtual T* search_post_by_id_post(std::string id_post) = 0;
};