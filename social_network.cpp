#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "network.h"
#include "user.h"

void print_menu() {
	cout << endl;
	cout << "Please select any of the following options." << endl;
	cout << "Enter command number followed by parameters" << endl;
	cout << "Option 1: Add a user (1 Full Name birth_year zipcode)" << endl;
	cout << "Option 2: Add friend connection (2 Username Username)" << endl;
	cout << "Option 3: Remove friend connection (3 Username Username)" << endl;
	cout << "Option 4: Print users (4)" << endl;
	cout << "Option 5: List friends (5 Username)" << endl;
	cout << "Option 6: Write to file (6 filename)" << endl;
	cout << "Enter 0 to quit" << endl;
	cout << endl;
}

int main(int argc, char *argv[]) {
	Network social_net;
	std::string filename = argv[1];
	int read_file = social_net.read_friends(filename.c_str());
	if (read_file == -1){
		cout << "Error opening file. Try again" << endl;
		return 0;
	}
	print_menu();
	int option;
	cin >> option;
	while (option < 7 && option > 0) {
		if (option == 1){
			std::string full_name, first, last;
			int birth_year, zipcode;
			cin >> first >> last >> birth_year >> zipcode;
			full_name = first + " " + last;
			social_net.add_user(full_name, birth_year, zipcode);
		}
		else if (option == 2) {
			std::string user1, user2, first1, last1, first2, last2;
			cin >> first1 >> last1 >> first2 >> last2;
			user1 = first1 + " " + last1;
			user2 = first2 + " " + last2;
			int result = social_net.add_connection(user1, user2);
			if (result == -1) {
				cout << "Error: Invalid user combination" << endl;
			}
		}
		else if (option == 3) {
			std::string user1, user2, first1, last1, first2, last2;
			cin >> first1 >> last1 >> first2 >> last2;
			user1 = first1 + " " + last1;
			user2 = first2 + " " + last2;
			int result = social_net.remove_connection(user1, user2);
			if (result == -1) {
				cout << "Error: Invalid user combination" << endl;
			}
		}
		else if (option == 4) {
			cout << "ID";
			cout << "Name"; 
			cout << "Year";
			cout << "Zip" << endl;
			cout << "================================================" << endl;
			for (int i = 0; i < social_net.get_users()->size(); i++){
				User curr = social_net.get_users()->at(i);
				cout << curr.get_userID() << ".";
				cout << curr.get_name();
				cout << curr.get_bday();
				cout << curr.get_zip() << endl;	
			}

		}
		else if (option == 5) {
			std::string first, last, full_name;
			cin >> first >> last;
			full_name = first + " " + last;
			cout << left << "ID" << setw(20) << "Name"; 
			cout << setw(15) << "Year";
			cout << setw(15) << "Zip" << endl;
			cout << "================================================" << endl;
			int curr_id = social_net.get_id(full_name);
			User curr = social_net.get_users()->at(curr_id);
			int num_friends = curr.get_friends()->size();
			for (int i=0; i < num_friends; i++) {
				User amigo = social_net.get_users()->at(curr.get_friends()->at(i));
				cout << left << amigo.get_userID() << "." << setw(20);
				cout << amigo.get_name() << setw(15);
				cout << amigo.get_bday() << setw(15);
				cout << amigo.get_zip() << endl;
			}

		}
		else if (option == 6) {
			std::string filename;
			cin >> filename;
			int write_to_file = social_net.write_friends(filename.c_str());
			if (write_to_file == -1)
				cout << "Error: Could not write to file" << endl;
		}
		else {
			return 0;
		}
		print_menu();
		cin >> option;
	}
	return 0;
}
