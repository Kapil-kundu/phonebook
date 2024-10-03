#include<bits/stdc++.h>
using namespace std;

struct information {
	char name[6], address[6], phone[11];
};
information info;
 
int compare_phone(char a[], char id_[]) {	
	for(int i = 0; i < 10; i++) {
		if(a[i] == id_[i]) {
			continue;
		} else {
			return 0;
		}
	}
	return 1;
}

void writeFile(ofstream& my_file) {	
	cout << "Enter name ";
	cin >> info.name;
	cout <<  "Enter address ";
	cin >> info.address;
	cout << "Enter phone ";
	cin >> info.phone;
	my_file << info.name << '\t' << info.address << '\t' << info.phone << endl;
}

void readfile(ifstream& inFile) {
	char id_[10];
	cout << "Enter number of the user "; 
	cin >> id_;
	int i = 0;
	while(true) {
		inFile.seekg(sizeof(information) * i , ios::beg);
		//cout << "\nTellg : " << inFile.tellg() << endl;
		if (inFile.eof()) {
			cout << "\nEOF reached\n";
			break;
		}
   		inFile >> info.name >> info.address >> info.phone;
   		
   		int a = compare_phone(info.phone, id_);
   		if(a == 1) {
	   		cout << "Name: " << info.name << endl;
	  	 	cout << "Adress: " << info.address << endl;
	  	 	cout << "Phone: " << info.phone << endl;
	  	 	break;
	  	}
		i++;
  	}
}	

void update_file(ifstream& inFile) {	
	information newdata;
	ofstream temp_file("temp.txt");
	char id_[11];
	cout << "Enter number of the user" << endl;
	cin >> id_;
	int i = 0;
	 while(!inFile.eof()) {
	 	inFile.seekg(sizeof(information) * i, ios::beg);
	 	if(inFile.eof()) {
	 		cout << "EOF reached";
	 		break;
	 	}
	 	inFile >> info.name >> info.address >> info.phone;
        if(compare_phone(info.phone, id_)) {
            cout << "Updating information for user with phone: " << info.phone << endl;
            cout << "Enter new name: ";
            cin >> newdata.name;
            cout << "Enter new address: ";
            cin >> newdata.address;
            temp_file << newdata.name << '\t' << newdata.address << '\t' << info.phone << endl; 
        } else {
            temp_file << info.name << '\t' << info.address << '\t' << info.phone << endl;
        }
        i++;
    }
    inFile.close();
    temp_file.close();

    remove("E.txt");
    rename("temp.txt", "E.txt");
}
void delete_info(ifstream& inFile) {
	ofstream temp_file;
	temp_file.open("temp.txt", ios_base::app);
	cout << "enter the number of user you want to delete details : ";
	char id_[10];
	cin >> id_;
	int i = 0;
	while(!inFile.eof()) {
		inFile.seekg(sizeof(information) * i, ios::beg);
		inFile >> info.name >> info.address >> info.phone;
		int a = compare_phone(info.phone, id_);
		if(a == 0) {
			temp_file << info.name << '\t' << info.address << '\t' << info.phone << endl;
		} else {
			cout << "data deleted successfully" << endl;
		}
		i++;	
	}
	remove("E.txt");
	rename("temp.txt", "E.txt");
	temp_file.close();
}

int main() {
	ofstream my_file;
	my_file.open("E.txt", ios_base::app);
	ifstream inFile("E.txt");
	while(1) {
		int a;
		cout << "enter 1 for create\nenter 2 for read\nenter 3 for update\nenter 4 for delete\nenter 5 for exit\n";
		cin >> a;			
		if(a == 1) {
			writeFile(my_file);
		} else if(a == 2 ) {
        	readfile(inFile);
		} else if (a == 3) {
			update_file(inFile);
		} else if(a == 4) {
			delete_info(inFile);
		} else if(a == 5) {
			break;
		} 		
	}
	inFile.close();
	my_file.close();
}
