#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<cstring>
#include<cstdlib>
using namespace std;

const char* fileName = "Employee.txt";

class Employee {
private:
    int EmpID;
    char EmpName[50], Post[50], Department[10];
    float Salary;
public:
    void ReadData();
    int GetID();
    void DisplayRecord();
    char* GetDepartment();
};

void Employee::ReadData() {
    cout << "\nEmployee ID: ";
    cin >> EmpID;
    cin.ignore();
    cout << "Employee Name: ";
    cin.getline(EmpName, 50);
    cout << "Employee's Post: ";
    cin.getline(Post, 50);
    cout << "Employee's Department: ";
    cin.getline(Department, 10);
    cout << "Salary: ";
    cin >> Salary;
}

void Employee::DisplayRecord() {
    cout << endl << "_______________________________";
    cout << endl << setw(5) << EmpID << setw(15) << EmpName
         << setw(15) << Post << setw(15) << Department << setw(8) << Salary;
}

int Employee::GetID() {
    return EmpID;
}

char* Employee::GetDepartment() {
    return Department;
}

int main() {
    Employee emp, e;
    char option, ch, Dept[50];
    int ID, isFound;
    fstream file;
    file.open(fileName, ios::in | ios::out | ios::binary | ios::app);
    if (!file) {
        file.open(fileName, ios::out | ios::binary);
        file.close();
        file.open(fileName, ios::in | ios::out | ios::binary);
    }

    do {
        cout << "\n******* Menu ********";
        cout << "\n1 => Add a new record";
        cout << "\n2 => Search record from employee id";
        cout << "\n3 => List Employee of particular department";
        cout << "\n4 => Display all employee";
        cout << "\n5 => Update record of an employee";
        cout << "\n6 => Delete record of particular employee";
        cout << "\n7 => Exit from the program";
        cout << "\n*******************************\n";
        cin >> option;

        switch (option) {
        case '1': {
            emp.ReadData();
            file.clear();
            file.seekg(0, ios::beg);
            isFound = 0;
            while (file.read((char*)&e, sizeof(e))) {
                if (e.GetID() == emp.GetID()) {
                    cout << "This ID already exists...Try another ID.";
                    isFound = 1;
                    break;
                }
            }
            if (isFound) break;
            file.clear();
            file.seekp(0, ios::end);
            file.write((char*)&emp, sizeof(emp));
            cout << "\nNew record has been added successfully...";
            break;
        }

        case '2': {
            isFound = 0;
            cout << "\nEnter ID of an employee to be searched: ";
            cin >> ID;
            file.clear();
            file.seekg(0, ios::beg);
            while (file.read((char*)&e, sizeof(e))) {
                if (e.GetID() == ID) {
                    cout << "\nThe record found....\n";
                    cout << "\n" << setw(5) << "ID" << setw(15) << "Name"
                         << setw(15) << "Post" << setw(15) << "Department" << setw(8) << "Salary";
                    e.DisplayRecord();
                    isFound = 1;
                    break;
                }
            }
            if (!isFound)
                cout << "\nData not found for employee ID#" << ID;
            break;
        }

        case '3': {
            isFound = 0;
            cout << "Enter department name to list employees: ";
            cin >> Dept;
            file.clear();
            file.seekg(0, ios::beg);
            while (file.read((char*)&e, sizeof(e))) {
                if (strcmp(e.GetDepartment(), Dept) == 0) {
                    if (!isFound) {
                        cout << "\nRecords found in department " << Dept << ":\n";
                        cout << setw(5) << "ID" << setw(15) << "Name"
                             << setw(15) << "Post" << setw(15) << "Department" << setw(8) << "Salary";
                    }
                    e.DisplayRecord();
                    isFound = 1;
                }
            }
            if (!isFound)
                cout << "\nNo data found for department: " << Dept;
            break;
        }

        case '4': {
            cout << "\nAll employee records:";
            file.clear();
            file.seekg(0, ios::beg);
            int counter = 0;
            while (file.read((char*)&e, sizeof(e))) {
                if (counter == 0)
                    cout << "\n" << setw(5) << "ID" << setw(15) << "Name"
                         << setw(15) << "Post" << setw(15) << "Department" << setw(8) << "Salary";
                e.DisplayRecord();
                counter++;
            }
            cout << "\n" << counter << " records found.";
            break;
        }

        case '5': {
            int recordNo = 0;
            cout << "\nEnter employee ID to be updated: ";
            cin >> ID;
            isFound = 0;
            file.clear();
            file.seekg(0, ios::beg);
            while (file.read((char*)&e, sizeof(e))) {
                recordNo++;
                if (e.GetID() == ID) {
                    cout << "Old record of employee with ID " << ID << " is:";
                    e.DisplayRecord();
                    isFound = 1;
                    break;
                }
            }
            if (!isFound) {
                cout << "\nData not found for employee ID#" << ID;
                break;
            }
            int location = (recordNo - 1) * sizeof(e);
            file.clear();
            file.seekp(location, ios::beg);
            cout << "\nEnter new record for employee ID " << ID << ":\n";
            e.ReadData();
            file.write((char*)&e, sizeof(e));
            cout << "\nRecord updated successfully.";
            break;
        }

        case '6': {
            cout << "\nEnter employee ID to be deleted: ";
            cin >> ID;
            isFound = 0;
            fstream temp("temp.txt", ios::out | ios::binary);
            file.clear();
            file.seekg(0, ios::beg);
            while (file.read((char*)&e, sizeof(e))) {
                if (e.GetID() != ID)
                    temp.write((char*)&e, sizeof(e));
                else {
                    isFound = 1;
                    cout << "\nDeleted record: ";
                    e.DisplayRecord();
                }
            }
            file.close();
            temp.close();
            if (!isFound) {
                cout << "\nNo record found with ID#" << ID;
                break;
            }
            remove(fileName);
            rename("temp.txt", fileName);
            file.open(fileName, ios::in | ios::out | ios::binary);
            cout << "\nRecord deleted successfully.";
            break;
        }

        case '7':
            cout << "\nExiting program...";
            file.close();
            return 0;

        default:
            cout << "\nInvalid Option!";
        }

        cout << "\nDo you want to continue? (y/n): ";
        cin >> ch;
    } while (ch != 'n' && ch != 'N');

    file.close();
    return 0;
}
