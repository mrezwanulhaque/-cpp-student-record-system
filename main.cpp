#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

struct Student {
    int id;
    string name, department;
    double cgpa;
};

const string DATA_FILE = "students.txt";

vector<Student> loadStudents() {
    vector<Student> students;
    ifstream file(DATA_FILE);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        Student s;
        string id, cgpa;
        if (getline(ss, id, '|') && getline(ss, s.name, '|') &&
            getline(ss, s.department, '|') && getline(ss, cgpa)) {
            try {
                s.id = stoi(id);
                s.cgpa = stod(cgpa);
                students.push_back(s);
            } catch (...) {}
        }
    }
    return students;
}

void saveStudents(const vector<Student>& students) {
    ofstream file(DATA_FILE);
    for (const auto& s : students)
        file << s.id << '|' << s.name << '|' << s.department << '|' << s.cgpa << '\n';
}

int findStudent(const vector<Student>& students, int id) {
    for (int i = 0; i < (int)students.size(); ++i)
        if (students[i].id == id) return i;
    return -1;
}

void addStudent(vector<Student>& students) {
    Student s;
    cout << "Student ID: ";
    cin >> s.id;
    if (findStudent(students, s.id) != -1) {
        cout << "This ID already exists.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Full name: ";
    getline(cin, s.name);
    cout << "Department: ";
    getline(cin, s.department);
    cout << "CGPA (0-4): ";
    cin >> s.cgpa;

    if (s.cgpa < 0 || s.cgpa > 4) {
        cout << "Invalid CGPA.\n";
        return;
    }
    students.push_back(s);
    saveStudents(students);
    cout << "Student added.\n";
}

void viewStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No records found.\n";
        return;
    }
    cout << "\nID\tName\t\tDepartment\tCGPA\n";
    for (const auto& s : students)
        cout << s.id << '\t' << s.name << '\t' << s.department << '\t' << s.cgpa << '\n';
}

void searchStudent(const vector<Student>& students) {
    int id;
    cout << "Enter ID: ";
    cin >> id;
    int i = findStudent(students, id);
    if (i == -1) {
        cout << "Student not found.\n";
        return;
    }
    const auto& s = students[i];
    cout << "ID: " << s.id << "\nName: " << s.name
         << "\nDepartment: " << s.department << "\nCGPA: " << s.cgpa << '\n';
}

void updateStudent(vector<Student>& students) {
    int id;
    cout << "Enter ID to update: ";
    cin >> id;
    int i = findStudent(students, id);
    if (i == -1) {
        cout << "Student not found.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "New name: ";
    getline(cin, students[i].name);
    cout << "New department: ";
    getline(cin, students[i].department);
    cout << "New CGPA (0-4): ";
    cin >> students[i].cgpa;

    if (students[i].cgpa < 0 || students[i].cgpa > 4) {
        cout << "Invalid CGPA. Update cancelled.\n";
        return;
    }
    saveStudents(students);
    cout << "Student updated.\n";
}

void deleteStudent(vector<Student>& students) {
    int id;
    cout << "Enter ID to delete: ";
    cin >> id;
    int i = findStudent(students, id);
    if (i == -1) {
        cout << "Student not found.\n";
        return;
    }
    students.erase(students.begin() + i);
    saveStudents(students);
    cout << "Student deleted.\n";
}

int main() {
    vector<Student> students = loadStudents();
    int choice = -1;

    while (choice != 0) {
        cout << "\n=== Student Record Management System ===\n"
             << "1. Add student\n2. View students\n3. Search student\n"
             << "4. Update student\n5. Delete student\n0. Exit\n"
             << "Choose: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: addStudent(students); break;
            case 2: viewStudents(students); break;
            case 3: searchStudent(students); break;
            case 4: updateStudent(students); break;
            case 5: deleteStudent(students); break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    }
    return 0;
}
