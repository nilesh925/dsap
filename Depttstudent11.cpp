#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

class student {
    typedef struct stud {
        int roll;
        char name[30];
        char div;
        char add[50];
    } stud;

    stud rec;

public:
    void create();
    void display();
    int search();
    void Delete();
};

void student::create() {
    char ans;
    ofstream fout;
    fout.open("stud.dat", ios::app | ios::binary); // append instead of overwrite
    do {
        cout << "\n\tEnter Roll No of Student    : ";
        cin >> rec.roll;
        cout << "\n\tEnter Name of Student       : ";
        cin >> rec.name;
        cout << "\n\tEnter Division of Student   : ";
        cin >> rec.div;
        cout << "\n\tEnter Address of Student    : ";
        cin >> rec.add;

        fout.write((char *)&rec, sizeof(stud));
        cout << "\n\tDo you want to add more records? (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
    fout.close();
}

void student::display() {
    ifstream fin("stud.dat", ios::in | ios::binary);
    if (!fin) {
        cout << "\n\tError opening file!";
        return;
    }

    cout << "\n\tThe Contents of the File Are:\n";
    cout << "\n\tRoll\tName\t\tDiv\tAddress";
    while (fin.read((char *)&rec, sizeof(stud))) {
        if (rec.roll != -1) {
            cout << "\n\t" << rec.roll << "\t" << rec.name << "\t\t" << rec.div << "\t" << rec.add;
        }
    }
    fin.close();
}

int student::search() {
    int r, i = 0;
    ifstream fin("stud.dat", ios::in | ios::binary);
    if (!fin) {
        cout << "\n\tError opening file!";
        return -1;
    }

    cout << "\n\tEnter Roll No to Search: ";
    cin >> r;

    while (fin.read((char *)&rec, sizeof(stud))) {
        if (rec.roll == r) {
            cout << "\n\tRecord Found...";
            cout << "\n\tRoll\tName\t\tDiv\tAddress";
            cout << "\n\t" << rec.roll << "\t" << rec.name << "\t\t" << rec.div << "\t" << rec.add;
            fin.close();
            return i;
        }
        i++;
    }
    fin.close();
    return -1;
}

void student::Delete() {
    int pos = search();
    if (pos == -1) {
        cout << "\n\tRecord Not Found";
        return;
    }

    fstream f("stud.dat", ios::in | ios::out | ios::binary);
    if (!f) {
        cout << "\n\tError opening file!";
        return;
    }

    int offset = pos * sizeof(stud);
    f.seekp(offset);

    rec.roll = -1;
    strcpy(rec.name, "NULL");
    rec.div = 'N';
    strcpy(rec.add, "NULL");

    f.write((char *)&rec, sizeof(stud));
    f.close();

    cout << "\n\tRecord Deleted Successfully!";
}

int main() {
    student obj;
    int ch, key;
    char ans;

    do {
        cout << "\n\n\t***** Student Information *****";
        cout << "\n\t1. Create\n\t2. Display\n\t3. Delete\n\t4. Search\n\t5. Exit";
        cout << "\n\t..... Enter Your Choice: ";
        cin >> ch;

        switch (ch) {
            case 1: obj.create(); break;
            case 2: obj.display(); break;
            case 3: obj.Delete(); break;
            case 4:
                key = obj.search();
                if (key == -1)
                    cout << "\n\tRecord Not Found...";
                break;
            case 5: 
                cout << "\n\tExiting...";
                return 0;
            default:
                cout << "\n\tInvalid Choice!";
        }

        cout << "\n\t..... Do You Want to Continue in Main Menu? (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');

    return 0;
}
