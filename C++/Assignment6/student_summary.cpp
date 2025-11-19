#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>

using namespace std;

struct Student {
    string name;
    int math;
    int cs;
    int eng;
    double avg;
};

void printHeader() {
    cout << "===== Student Summary =====\n";
    cout << left << setw(15) << "Name"
         << setw(7) << "Math"
         << setw(7) << "CS"
         << setw(7) << "Eng"
         << setw(7) << "Avg" << endl;
    cout << string(38, '-') << endl;
}

double computeAverage(int a, int b, int c) {
    return (a + b + c) / 3.0;
}

bool loadStudents(const string& filename, vector<Student>& students) {
    ifstream fin;

    fin.exceptions(ios::failbit | ios::badbit);
    
    fin.open(filename);

    fin.exceptions(ios::badbit);

    string line;
    while (getline(fin, line)) {
        istringstream iss(line);
        Student s;
        iss >> s.name >> s.math >> s.cs >> s.eng;
        s.avg = computeAverage(s.math, s.cs, s.eng);
        students.push_back(s);
    }
    return true;
}

void printStudents(const vector<Student>& students) {

    for (size_t i = 0; i < students.size(); ++i) {
        cout << left << setw(15) << students.at(i).name
             << setw(7) << students.at(i).math
             << setw(7) << students.at(i).cs
             << setw(7) << students.at(i).eng
             << setw(7) << fixed << setprecision(2) << students.at(i).avg
             << endl;
    }
    cout << string(38, '-') << endl;
}

void updateScore(Student& s, int addMath, int addCS, int addEng) {
    s.math += addMath;
    s.cs   += addCS;
    s.eng  += addEng;
    s.avg  = computeAverage(s.math, s.cs, s.eng);
}


void sortByAverage(vector<Student>& students) {
    sort(students.begin(), students.end(),
         [](const Student& a, const Student& b) {
             if (a.avg != b.avg) return a.avg > b.avg;  
             return a.name < b.name;                    
         });
}

void printTopStudent(Student* ptr) {
    cout << "Top student: " << ptr->name << endl;
}

double computeClassAverage(const vector<Student>& students) {
    if (students.empty()) return 0.0;
    double total = 0.0;
    for (const auto& s : students) total += s.avg;
    return total / static_cast<double>(students.size());
}

static void verifySorted(const vector<Student>& students) {
    for (size_t i = 1; i < students.size(); ++i) {

        assert(students[i - 1].avg >= students[i].avg && "should be descending by avg"); 
    }
}

static void printStudentsReverse(const vector<Student>& students) {
    
    for (int i = static_cast<int>(students.size()) - 1; i >= 0; --i) {
        const auto& s = students.at(i);
        cout << left << setw(15) << s.name
             << setw(7) << s.math
             << setw(7) << s.cs
             << setw(7) << s.eng
             << setw(7) << fixed << setprecision(2) << s.avg
             << endl;
    }
    cout << string(38, '-') << endl;
}

int main() {
    vector<Student> students;

    cout << "Loading students from file...\n";
    if (!loadStudents("students.txt", students)) {
        cerr << "File open failed!\n";
        return 1;
    }

    printHeader();
    printStudents(students);

    if (!students.empty()) {
        updateScore(students[0], 5, 5, 5);  
    }

    sortByAverage(students);               

    verifySorted(students);                

    double classAvg = computeClassAverage(students); 

    Student* topPtr = &students.front();                        
    printTopStudent(topPtr);           

    printHeader();
    printStudentsReverse(students);

    cout << "Class average: " << fixed << setprecision(2) << classAvg << endl;
    return 0;
}
