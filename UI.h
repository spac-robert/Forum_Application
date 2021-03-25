#pragma once
#include "Service.h"
#include "UserValidator.h"
#include "ValidationExepstion.h"
#include <conio.h>
#include "PostValidator.h"

class UI {

private:
    Service* service;
    UserValidator user_validator;
    PostValidator post_validator;

public:
    UI(Service* service, UserValidator user_validator, PostValidator post_validator) :service(service), user_validator(user_validator),
        post_validator(post_validator) {
    }
    ~UI() {

    }

    void forum_menu() {
        cout << "------------Forum------------\n";
        cout << "Commands:\n";
        cout << "1.Login\n" << "2.Sign in\n";
    }

    void admin_menu() {
        cout << "--------- Admin Menu ---------\n";
        cout << "0.Exit\n";
        cout << "1.Show posts by a user\n";
        cout << "2.Post\n";
        cout << "3.Delete user\n";
        cout << "4.Delete post\n";
        cout << "5.Update user type\n";
        cout << "6.Show all users\n";
        cout<<"7.Show all posts from all users\n";
    }

    void user_menu() {
        cout << "--------- User Menu ---------\n";
        cout << "0.Exit\n";
        cout << "1.Show posts by a user\n";
        cout << "2.Post\n";
        cout << "3.Delete post\n";
        cout << "4.Show all users\n";
        cout << "5.Show all posts from all users\n";
        cout << "6.Edit post\n";
    }
    void get_all_posts_from_all_users() {
        vector<User*> all_users = service->get_all_users();
        for (int i = 0; i<int(all_users.size()); i++) {
            cout << all_users[i] << "\n";
            read_all_posts_by_a_user(all_users[i]->get_name());
            cout << "\n\n\n";
        }
    }

    //write password and display * instead letters
    string read_password() {

        cout << "Password: ";
        string str;
        char* s = new char[15];
        int n = 0, x;
        int i;
        i = 0;
        while (i < 15) {
            x = _getch();
            if (x != 13 and x != 8) {
                s[n++] = x;
                _putch('*');
                i++;
            }
            else
                if (x == 8 and n > 0)
                {
                    s[n--];
                    _putch('\b');
                    _putch(' ');
                    _putch('\b');
                    i--;
                }
                else
                    if (x == 8 and i > 0)
                        i--;
                    else
                        if (x == 13)
                            i = 15;

        }
        str.resize(n);
        for (i = 0; i < n; i++)
            str[i] = s[i];
        return str;
    }

    User* user_login() {

        string name, password;
        std::cout << "ID: ";
        try {
           cin >> name;
           password = read_password();
           //validate if name and password metch with an account in database
           if (this->user_validator.name_exist(name,password)) {
               throw ValidationException(user_validator.toString());
           }
            cout << std::endl;
            cout << "Login succesful\n";
            return service->login(name, password);
        }
        catch (ValidationException& ex) {
            throw;
        }
    }

    //Validate if name exist
    string name_exist() {
        string name;
        bool ok = false;
        std::cout << "User name: ";
        try {
            cin >> name;
            if (this->user_validator.name_exist(name)) {
                throw ValidationException(user_validator.toString());
            }
            cout << std::endl;
        }
        catch (ValidationException & ex) {
            throw;
        }
        return name;
    }

    //write an user name and validate if it is not taken
    string read_and_validate_name() {

        string name;
        std::cout << "User name: ";
        try {
            cin >> name;
            if (this->user_validator.name_does_not_exist(name)) {
                throw ValidationException(user_validator.toString());
            }
            cout << std::endl;
        }
        catch (ValidationException& ex) {
            throw;
        }
        return name;
    }

    //write an validate password to contain minimum one upper letter and one symbol( !@#$%^&*()_+~ )
    string read_and_validate_password() {
        bool ok = false;
        string password;
        try {
            password = read_password();
            if (this->user_validator.validate_password(password)) {
                throw ValidationException(user_validator.toString());
            }
            return password;
        }
        catch (ValidationException& ex) {
            throw;
        }
    }

    //Sign in
    User* user_sign_in() {

        string name, password;
        try {
            name = read_and_validate_name();
            password = read_and_validate_password();
            return service->sign_in(name, password);
        }
        catch (ValidationException & ex) {
            throw;
        }
    }

    //Print all posts
    void print_all_posts_by_user(vector<Post*> all_posts) {
        for (int i = 0; i<int(all_posts.size()); i++) {
            cout << *all_posts[i] << "\n";
        }
    }

    //Read all post by a user
    void read_all_posts_by_a_user(string name) {
        User* user = service->find_user_by_name(name);
        print_all_posts_by_user(service->get_all_posts(user));
    }

    void all_posts_from_a_user() {
        string name;
        /*name = read_and_validate_name();
        show_all_posts_by_a_user(name);*/
        try {
            name = name_exist();
        }
        catch (ValidationException & ex) {
            cout << ex.what()<<"\n";
        }
        read_all_posts_by_a_user(name);
    }

    //write title and a post for posting 
    void to_post(User* user) {
        string title,for_posting;

        try {
            cout << "Title: ";
            cin.get();
            getline(cin, title);
            cout << "Post: ";
            getline(cin, for_posting);
            if (post_validator.post_len_validation(title, for_posting)) {
                throw ValidationException(post_validator.toString());
            }
            service->posting(user, title, for_posting);
        }
        catch (ValidationException & ex) {
            cout << ex.what() << "\n";
        }
    }

    //delete post by a user 
    void deleting_post_by_id(User* user) {
        string id_post,name;
        read_all_posts_by_a_user(user->get_name());
        try {
            cout << "Id post: ";
            cin >> id_post;
            if (post_validator.id_post_exist(id_post)) {
                throw ValidationException(post_validator.toString());
            }
            service->delete_post_by_id(id_post);
        }
        catch (ValidationException & ex) {
            cout << ex.what() << "\n";
        }
    }
  
    //delete user
    void delete_user() {
        string name;
        try {
            name = name_exist();
        }
        catch (ValidationException & ex) {
            cout << ex.what() << "\n";
        }
        service->delete_user(name);
    }

    //delete user post
    void deleting_user_post_by_id() {
        string name;
        try {
            name = name_exist();
            User* new_user = service->find_user_by_name(name);
            deleting_post_by_id(new_user);
        }
        catch (ValidationException & ex) {
            cout << ex.what() << "\n";
        }
    }

    void admin_commands(User* user) {
        string opt,name,title;
        do {
            admin_menu();
            cout << "Command: ";
            cin >> opt;
            if (opt == "1") {
                all_posts_from_a_user();
            }
            if (opt == "2") {
                to_post(user);
            }
            if (opt == "3") {
                delete_user();
            }
            if (opt == "4") {
                deleting_user_post_by_id();
            }
            if (opt == "5") {
                update_user();
            }
            if (opt == "6") {
                print_all_users(service->get_all_users());
            }
            if (opt == "7") {
                get_all_posts_from_all_users();
            }
            system("PAUSE");
            system("cls");

        } while (opt!="0");
    }

    //print all users
    void print_all_users(vector<User*> all_users) {
        cout << "\n"; 
        for (int i = 0; i<int(all_users.size()); i++) {
            cout << all_users[i] << "\n";
        }
    }

    //Edit post
    void edit_post_user(User* user) {
        string title_to_edit, post_to_edit,id_post;
        read_all_posts_by_a_user(user->get_name());
        try {
            cout << "Id post for edit: ";
            cin >> id_post;
            cout << "Title to edit: ";
            cin.get();
            getline(cin, title_to_edit);
            cout << "Post to edit: ";
            getline(cin, post_to_edit);
            service->edit_post(user, id_post, title_to_edit, post_to_edit);
        }
        catch (exception ex) {
            cout << ex.what() << "\n";
        }
    }

    //update user to admin if he is user
    void update_user() {
        string name;
        try {
            name = name_exist();
        }
        catch (ValidationException & ex) {
            cout << ex.what() << "\n";
        }
        try {
            service->promote_user(name);
        }
        catch (exception ex) {
            cout << ex.what() << "\n";
        }
    }

    void user_commands(User* user) {

        string opt;
        do {
            user_menu();
            cout << "Select an option: ";
            cin >> opt;
            if (opt == "1") {
                all_posts_from_a_user();
            }
            if (opt == "2") {
                to_post(user);
            }
            if (opt == "3") {
                deleting_post_by_id(user);
            }
            if (opt == "4") {
                print_all_users(service->get_all_users());
            }
            if (opt == "5") {
                get_all_posts_from_all_users();
            }
            if (opt == "6") {
                edit_post_user(user);
            }
            system("PAUSE");
            system("cls");

        } while (opt != "0");
    }

    void login_acoount(User* user) {
        try {
            //login
            user = user_login();
            system("PAUSE");
            system("cls");
            //verificate if user is admin or user
            if (user->get_type() == "admin") {
                //display admin menu
                admin_commands(user);
            }
            else
                //display user menu
                user_commands(user);
        }
        catch (ValidationException & ex) {
            cout << std::endl;
            cout << ex.what() << endl;

        }
    }

    void create_account(User* user) {
        bool ok = false;
        string opt;
        do {
            try {
                user = user_sign_in();
                ok = true;
                cout << "\nSign in succesful\n";
                system("PAUSE");
                system("cls");
            }
            catch (ValidationException & ex) {
                cout << std::endl;
                cout << ex.what() << "\n";
                cout << "Press 1 to retry\n Press 2 to login\n";
                cin >> opt;
                if (opt == "2")
                    ok = true;
            }
        } while (!ok);
    }

    //Main
	void run_ui() {
        string opt;
        User* user= new User();
        string name, password;
        do {
            forum_menu();//Display forum menu
            cout << "Command: ";
            cin >> opt;
            if (opt == "1") {
                //login
                login_acoount(user);
            }
            if (opt == "2") {
                //createing an account
                create_account(user);
            }
        } while (true);
	}
};