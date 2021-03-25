#pragma once
#include "User.h"
#include "ConcreteUserRepository.h"
#include <exception>
#include <vector>
#include <algorithm>
#include <regex>  
#include <string>
#include "ConcretePostRepository.h"

class PostValidator {
protected:
	int err;
	string message;
	PostsRepo<Post, User>* post_repository;

public:
	PostValidator(PostsRepo<Post, User>* post_repository): post_repository(post_repository) {
		err = 0;
		message = "";
	}

	int title_len_validation(string title) {
		err = 0;
		if (int(title.size()) > 100) {
			err++;
			message = "Title must have 100 characters\n";
		}
		return err;
	}

	int post_len_validation(string title,string post) {
		err = 0;
		if (int(title.size()) > 100) {
			err++;
			message = "Title must have 100 characters\n Title must have 250 characters\n";
		}
		if (int(post.size()) > 250) {
			err++;
			message = "Title must have 100 characters\n Title must have 250 characters\n";
		}
		return err;
	}

	int id_post_exist(string id_post) {
		Post* post = post_repository->search_post_by_id_post(id_post);
		if (post->get_id() != id_post) {
			err++;
			message = "Id post dosen't exist\n";
		}

		return err;
	}

	string toString() {

		return message;
	}
};