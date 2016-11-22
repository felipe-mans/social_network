#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "network.h"
#include "user.h"


Network::Network() {
	
}

Network::~Network() {

}

int Network::read_friends(const char *filename) {
	int num_users;
	ifstream ifile;
	ifile.open(filename);
	if (ifile.fail())
		return -1;
	ifile >> num_users;
	for (int i=0; i < num_users; i++) {
		int user_id, yr, zipcode;
		std::string first, last, full_name;
		ifile >> user_id >> first >> last >> yr >> zipcode;
		ifile.ignore();

		full_name = first + " " + last;
		
		add_user(full_name,yr, zipcode);

		std::string line = "";
		getline(ifile, line);
		stringstream connect(line);
		int friend_id;
		while (connect) {
			connect >> friend_id;
			if (!connect.fail())
				users[i].add_friend(friend_id);
		}
	}
	ifile.close();
	return 0;
}

int Network::write_friends(const char *filename) {
	int num_users = users.size();
	ofstream new_file;
	new_file.open(filename);
	if (new_file.fail())
		return -1;
	if (new_file.is_open()) {
		new_file << num_users << "\n";
		for (int i=0; i < num_users; i++) {
			User curr = users[i];
			new_file << curr.get_userID() << "\n";
			new_file << "\t" << curr.get_name() << "\n";
			new_file << "\t" << curr.get_bday() << "\n";
			new_file << "\t" << curr.get_zip() << "\n\t";
			int num_friends = curr.get_friends()->size();
			for (int j=0; j < num_friends; j++) {
				new_file << curr.get_friends()->at(j) << " ";
			}
			new_file << "\n";
		}
	}
	new_file.close();
	return 0;
}

void Network::add_user(std::string username, int yr, int zipcode) {
	int new_id = users.size();
	User new_user = User(username, new_id, yr, zipcode);
	users.push_back(new_user);
}

void Network::add_user(User new_user) {
	users.push_back(new_user);
}

int Network::add_connection(std::string name1, std::string name2) {
	bool exists1 = false;
	bool exists2 = false;
	int id1, id2;
	for (int i=0; i < users.size(); i++) {
		if (users[i].get_name() == name1) {
			exists1 = true;
			id1 = users[i].get_userID();
		}
		if (users[i].get_name() == name2) {
			exists2 = true;
			id2 = users[i].get_userID();
		}
	}
	if (exists1 && exists2) {
		for (int i=0; i < users.size(); i++) {
			if (users[i].get_name() == name1)
				users[i].get_friends()->push_back(id2);
			if (users[i].get_name() == name2)
				users[i].get_friends()->push_back(id1);				
		}
		return 0;
	}
	else
		return -1;

}

int Network::remove_connection(std::string name1, std::string name2) {
	bool exists1 = false;
	bool exists2 = false;
	int id1, id2;
	for (int i=0; i < users.size(); i++) {
		if (users[i].get_name() == name1) {
			exists1 = true;
			id1 = users[i].get_userID();
		}
		if (users[i].get_name() == name2) {
			exists2 = true;
			id2 = users[i].get_userID();
		}
	}
	if (exists1 && exists2) {
		for (int i=0; i < users.size(); i++) {
			if (users[i].get_name() == name1) {
				for (int j=0; j < users[i].get_friends()->size(); j++) {
					if (users[i].get_friends()->at(j) == id2)
						users[i].get_friends()->erase(users[i].get_friends()->begin()+j);
				}
			}
			if (users[i].get_name() == name2) {
				for (int j=0; j < users[i].get_friends()->size(); j++) {
					if (users[i].get_friends()->at(j) == id1)
						users[i].get_friends()->erase(users[i].get_friends()->begin()+j);
				}
			}
		}
		return 0;
	}
	else
		return -1;
}


int Network::get_id(std::string username) {
	int result = -1;
	for (int i=0; i < users.size(); i++) {
		if (users[i].get_name() == username)
			result = users[i].get_userID();
	}
	return result;
}

vector<User>* Network::get_users() {
	return &users;
}
