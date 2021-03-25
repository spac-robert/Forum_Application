#include "Tests.h"
#include <iostream>
#include <mysql.h>
#include "UI.h"

int main()
{

    Tests test;
    test.run_tests();
    system("PAUSE");
    system("cls");

    UsersRepo<User>* user_repository = new ConcreteUserRepository("forumdatabase");
    PostsRepo<Post, User>* post_repository = new ConcretePostRepository("forumdatabase");
    Service* service= new Service(user_repository, post_repository);
    UserValidator user_validator(user_repository);
    PostValidator post_validator(post_repository);
    UI ui(service, user_validator, post_validator);

    ui.run_ui();

    return 0;
}


