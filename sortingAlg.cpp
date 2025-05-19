//
// Created by DELL on 4/21/2024.
//
#include "Student.h"
#include "fstream"
#include <iostream>
#include <sstream>
#include <deque>
#include <chrono>
#include <functional>
#include <time.h>
#include <locale>


using namespace std::chrono;
ofstream filex("SortedByGPA.txt");
int comparisonsGPA = 0;
int comparisonsName=0;

void writetofileGpa(deque<Student>& students, string algorithmName, microseconds *duration){
    filex << "Algorithm: " << algorithmName << endl;
    filex<<"Number of comparisons: "<<comparisonsGPA<<endl;
//    auto duration =duration_cast<microseconds>(e - s);

    filex << "Running Time: " << duration << endl;

    for (auto &student: students) {
        filex << student.getFullName() << endl;
        filex << student.getID() << endl;
        filex << student.getGPA() << std::endl;
    }

}
ofstream filen("SortedByName.txt");

void writetofilename( deque<Student>& students,string algorithmName,microseconds duration){

     // Calculate duration

    filen << "Algorithm: " << algorithmName << endl;
    filen<<"Number of comparisons: "<<comparisonsName<<endl;

//    auto duration =duration_cast<microseconds>(e - s);
    filen << "Running Time: " << duration.count() << endl;

    for (auto &student: students) {
        filen << student.getFullName() << endl;
        filen << student.getID() << endl;
        filen << student.getGPA() << std::endl;
    }

}
SortingFunctionName sortingFunctionsName[] = {
        [](std::deque<Student>& students) { insertionSort(students, sortByName,comparisonsName); },
        [](std::deque<Student>& students) { selectionSort(students, sortByName,comparisonsName); },
        [](std::deque<Student>& students) { bubbleSort(students, sortByName,comparisonsName); },
        [](std::deque<Student>& students) { shellSort(students, sortByName,comparisonsName); },
        [](std::deque<Student>& students) { mergeSort(students,0,students.size()-1, sortByName,comparisonsName); },
        [](std::deque<Student>& students) { quickSort(students,0,students.size()-1, sortByName,comparisonsName); },
//        [](std::deque<Student>& students) { countSort(students, sortByName,comparisonsName); },
};

SortingFunction sortingFunctions[] = {
        [](std::deque<Student>&students) {insertionSort(students, sortByGPA,comparisonsGPA); },
        [](std::deque<Student>& students) { selectionSort(students, sortByGPA,comparisonsGPA);},
        [](std::deque<Student>& students) {bubbleSort(students, sortByGPA,comparisonsGPA); },
        [](std::deque<Student>& students) {  shellSort(students, sortByGPA,comparisonsGPA); },
        [](std::deque<Student>& students) {  mergeSort(students, 0, students.size()-1, sortByGPA,comparisonsGPA); },
        [](std::deque<Student>& students) { quickSort(students,0,students.size()-1, sortByGPA,comparisonsGPA); },
        [](std::deque<Student>& students) { countSort(students, sortByGPA,comparisonsGPA);}
};

