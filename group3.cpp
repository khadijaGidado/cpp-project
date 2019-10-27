#include <iostream>
#include <string>
#include <list>
#include <fstream>

using namespace std;

int next_id;		// The next vacant ID.

class Student
{
private:

public:
	int id				{next_id};
	string firstname	{""};
	string surname		{""};
	int age				{0};
	string department	{""};
	string status		{"studying"};
	float gpa			{0.0};
	
	Student()
	{
	}
	
	void ChangeStatus()
	{
		if (status == "studying") {
			status = "not studying";
		} else {
			status = "studying";
		}
	}

	void Print(ostream& stream, char delimiter)
	{
		stream << id << delimiter;
		stream << firstname << delimiter;
		stream << surname << delimiter;
		stream << age << delimiter;
		stream << department << delimiter;
		stream << status << delimiter;
		stream << gpa << endl;
	}
};

list<Student> records;

void register_student()
{
	while (true)
	{
		system("cls");
		Student s;
		cout<<"Enter the student first name"<<endl;
		cin>>s.firstname;
		cout<<"Enter the student surname"<<endl;
		cin>>s.surname;
		cout<<"Enter the student age"<<endl;
		cin>>s.age;
		cin.ignore();
		cout<<"Enter the student department"<<endl;
		getline(cin, s.department);
		cout<<"Enter the student gpa"<<endl;
		cin>>s.gpa;
		// ID?

		// save to list
		records.push_back(s);
		// save to file
		ofstream database("database.csv", ios_base::app);

		s.Print(database, ',');

		database.close();

		cout << "Student saved!\n";
		char option;
		cout << "do you want to register another student? [y/n]"<<endl;
		cin>>option;
		if (option == 'y' || option == 'Y'){
			continue;
		} else{
			return;
		}
	}
}

void display_studying_students()
{
	system("cls");
	for (auto& student: records ){
		if (student.status == "studying"){
			student.Print(cout, '\t');
		}
	}
}

void search_student()
{
	system("cls");
	int id;
	bool found = false;
	// Get the ID
	cout<< "Enter the id "<<endl;
	cin>>id;
	// Find the student
	for(auto& student: records ){
		if(student.id == id){
			// Display the student
			found = true;
			student.Print(cout, '\t');
		}
	}
	if (!found) {
		cout<<"the student wasnt found\n";
	}
}

void change_student_status()
{
	system("cls");
	int id;
	// Ask for the student
	cout<<"Enter the student id "<<endl;
	cin>>id;
	// student.ChangeStatus();
	for(auto& student: records){
		if(student.id == id ){
			student.ChangeStatus();
			// Print result
			student.Print(cout, '\t');
			cout<<"Status has been changed\n";
		}
	}
	// TODO: and if no student exists with that id?
}

void delete_student()
{
	int id;
	cout<<"Enter the student id "<<endl;
	cin>>id;
	for(auto& student: records){
		if(student.id == id){
			records.remove(student);
			cout <<"Student has been deleted\n";
		}
	}
	// TODO: and if no student exists with that id?
}

void highest_gpa_student()
{
	// TODO
}

void exit()
{
	// TODO
}

void menu()
{
	while (true)
	{
		system("cls");

		cout << "====== STUDENT INFORMATION SYSTEM ======";
		cout << "\n\n";
		cout << "MENU\n\n";
		cout << "1. Register student\n";
		cout << "2. Display studying students\n";
		cout << "3. Search student\n";
		cout << "4. Change student's status\n";
		cout << "5. Delete student\n";
		cout << "6. Highest GPA student\n";
		cout << "7. Exit\n\n";
		cout << "Select Your Choice :=> ";

		int choice;
		cin >> choice;

		switch(choice){
			case 1:
				register_student();
				break;
			case 2:
				display_studying_students();
				break;
			case 3:
				search_student();
				break;
			case 4:
				change_student_status();
				break;
			case 5:
				delete_student();
				break;
			case 6:
				highest_gpa_student();
				break;
			case 7:
				exit();
				break;
			default:
				// Error message
				break;

		}

		char option;
		cout << "Do you want to to return to menu? Y/N: ";
		cin >> option;
		if (option == 'y' || option == 'Y') {
			continue;
		} else if (option == 'n' || option == 'N') {
			return;
		}		
	}
}

int main(){	
	// Load the file
	ifstream database("database.csv");
	Student s;
	
	int i = 0;
	while (database >> s.id)
	{
		database.ignore(1, ',');
		getline(database, s.firstname, ',');
		getline(database, s.surname, ',');
		database >> s.age;
		database.ignore(1, ',');
		getline(database, s.department, ',');
		getline(database, s.status, ',');
		database >> s.gpa;
		
		records.push_back(s);		
		i++;
	}
	
	// Use the last student's id to set the next id
	next_id = records.back().id + 1;
	// TODO: what if there's no last student?

	database.close();

	cout << i << endl;
	menu();
	
	return 0;
}

