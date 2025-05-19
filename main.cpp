#include <iostream>
#include "Student.h"
#include "sortingAlg.cpp"

using namespace std;
int main() {
    ifstream file("students.txt");

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }
    int nofstud;
    file >> nofstud;
    file.ignore();
    deque<Student> students;
    for (int i = 0; i < nofstud; ++i) {
        string name, id, lname, fname;
        double gpa;
        string line;
        getline(file, line);
        fname=line;
        getline(file, line);
        id=line;
        getline(file, line);
        gpa= stod(line);
        students.push_back(Student( fname, lname,id, gpa));
    }
    insertionSort(students, sortByGPA,comparisonsGPA);
    insertionSort(students, sortByName,comparisonsName);

    deque<string >d={"Insertion Sort","Selection Sort","Bubble Sort","Shell Sort",
                     "Merge Sort","Quick Sort","Count Sort"};
    auto i=0;
    for (const SortingFunctionName& sortingFunctionName : sortingFunctionsName) {
        deque<Student> tempStudents = students; // Make a copy of the original data
        auto start = high_resolution_clock::now();
        sortingFunctionName(tempStudents);
        auto end =high_resolution_clock::now();
        auto duration =duration_cast<microseconds>(end - start);
        writetofilename(students,d[i],duration);
        i++;

    }
    auto j=0;
    for (const SortingFunction& sortingFunction : sortingFunctions) {
        std::deque<Student> tempStudents = students; // Make a copy of the original data
        // Make a copy of the original data
        auto start = high_resolution_clock::now();
        //sorting function
        sortingFunction(tempStudents);
        auto end =high_resolution_clock::now();
        auto duration =duration_cast<microseconds>(end - start);
        writetofileGpa(students, d[j], reinterpret_cast<microseconds *>(duration.count()));
        j++;

    }


}
