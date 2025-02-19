#include <iostream>
#include <string>
using namespace std;

#define MAX 100

typedef struct student {
	string name;
	string surname;
	int studentID;
	string department;
}STUDENT;

typedef struct course {
	STUDENT list[MAX];
	int size;
}COURSE;

void printMenu() {
	cout << "1- Add a New Student" << endl;
	cout << "2- Remove a Student" << endl;
	cout << "3- Update Student Info" << endl;
	cout << "4- Print All Registered Students" << endl;
	cout << "5- Exit" << endl;
	cout<<"\n";
}
int control_ID(COURSE* ptr, int* IDptr) {
	for (int i = 0; i < ptr->size; i++) {
		if (ptr->list[i].studentID == *IDptr) {
			return 0;
		}

	}

	return 1;
}

void insertStudent(STUDENT* ptr) {
	cout << "Enter name:";
	cin >> ptr->name;
	cout << "Enter surname:";
	cin >> ptr->surname;
	cout << "Enter ID:";
	cin >> ptr->studentID;
	cout << "Enter department:";
	cin >> ptr->department;
}
int ID_positiveornot(int* id) {
	if (*id > 0) {
		return 1;
	}
	else
		return 0;
}
void Add_New_Student(COURSE* ptr) {
	STUDENT a;
	insertStudent(&a);
	if (ID_positiveornot(&a.studentID) == 1) {

		if (control_ID(ptr, &a.studentID) == 1) {
			ptr->list[ptr->size] = a;
			(ptr->size)++;
		}
		else {
			cout << "ERROR !! This user already exist" << endl;
		}
	}
	else {
		cout << "ID is not valid" << endl;
	}
cout<<"\n";



}
void removeStudent(COURSE* ptr) {
	int ID, index;
	STUDENT temp;
	cout << "Enter the ID you want to delete:";
	cin >> ID;
	if (ID_positiveornot(&ID) == 1) {
		for (int i = 0; i < ptr->size; i++) {
			if (ptr->list[i].studentID == ID) {
				index = i;
			}
		}
		for (int i = index; i < (ptr->size) - 1; i++) {
			temp = ptr->list[i];
			ptr->list[i] = ptr->list[i + 1];
			ptr->list[i + 1] = temp;
		}
		(ptr->size)--;
	}
	else {
		cout << "ID is not valid !!" << endl;
	}

		cout<<"\n";
}
void updateStudent(COURSE* ptr) {
	STUDENT a;
	int ID;
	cout << "Enter the ID you want to change:";
	cin >> ID;
	if (ID_positiveornot(&ID) == 1) {
		insertStudent(&a);
		for (int i = 0; i < ptr->size; i++) {
			if (ptr->list[i].studentID == ID) {
				ptr->list[i] = a;
			}
		}
	}
	else {
		cout << "ID is not valid" << endl;
	}

	cout<<"\n";

}
void printStudentInformation(STUDENT* ptr) {
	cout << "Name is :" << ptr->name << endl;
	cout << "Surname is :" << ptr->surname << endl;
	cout << "ID is :" << ptr->studentID << endl;
	cout << "Department is:" << ptr->department << endl;
}

void printRegisteredStudents(COURSE* ptr) {
	for (int i = 0; i < ptr->size; i++) {
		printStudentInformation(&(ptr->list[i]));
		cout<<"\n";
	}
	

}
void orderStudents(COURSE* ptr) {
	STUDENT temp;
	

		for (int i = 0; i < (ptr->size)-1; i++) {
			for (int j = i; j < (ptr->size) - 1; j++) {
				if (ptr->list[i].studentID > ptr->list[i + 1].studentID) {
					temp = ptr->list[i];
					ptr->list[i] = ptr->list[i + 1];
					ptr->list[i+1] = temp;


				}
			}
		}
}




int main() {
	int option;
	COURSE ceng241;
	ceng241.size = 0;
	for (;;) {
		printMenu();
		cout << "Choose an option : ";
		cin >> option;
		switch (option) {

		case 1:
			Add_New_Student(&ceng241);
			orderStudents(&ceng241);
			break;
		case 2:
			removeStudent(&ceng241);
			orderStudents(&ceng241);
			break;
		case 3:
			updateStudent(&ceng241);
			orderStudents(&ceng241);
				break;
		case 4:
			printRegisteredStudents(&ceng241);
			break;
		case 5:

			return 0;

		}

	}

	return 0;

}