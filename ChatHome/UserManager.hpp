#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
class User{
    private:
	std::string nick_name;
	std::string school;
	std::string passwd;
    public:
	User(const std::string &n_, const std::string &s_,\
			const std::string pwd_):
		nick_name(n_),school(s_),passwd(pwd_)
	{}
	~User()
	{}
};

class UserManager{
	private:
	    unsigned int assign_id;
	    std::unordered_map<unsigned int, User> Users;
	    std::unordered_map<unsigned int, struct sockaddr_in> online_users;
	public:
	    UserManager():assigned_id(100000)
	    {}
	    


};
