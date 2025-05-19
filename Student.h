//
// Created by DELL on 4/21/2024.
//

#ifndef UNTITLED7_STUDENT_H
#define UNTITLED7_STUDENT_H
#include <iostream>
#include <deque>
#include <algorithm>
#include <fstream>
#include <stack>

using namespace std;


class Student {

    string id;
  string fname;
  string lname;
public:
    double gpa;

//    Student();
    Student(string name ,string lname,string id,  double gpa)
            : id(id), fname(name),lname(lname) , gpa(gpa) {}
    bool operator< (Student& other){
        return fname<other.fname;
    }
    bool operator>(const Student& other) const {
        return gpa > other.gpa;
    }
    Student * operator=(const Student& other) {
            fname = other.fname;
            gpa = other.gpa;
        return this;
    }
    string  getID() const { return id; }
    string getFullName() const { return lname.empty() ? fname : fname + " " + lname; }
    double getGPA() const { return gpa; }
    void setID(string newID) {
        id = newID;
    }
    void setName(const std::string& newFirstName) {
        fname = newFirstName;
    }
    void setGPA(double newGPA) {
        gpa = newGPA;
    }
    friend std::ostream& operator<<(std::ostream& os, const Student& student) {
        os << "ID: " << student.id << ", Name: " << student.fname << ", GPA: " << student.gpa;
        return os;
    }
    Student() {}
};
//using CompareFunc = bool (*)( Student&, Student&);
bool sortByGPA( Student& a,  Student& b) {
    return a.getGPA() < b.getGPA();
}

// Comparison function for sorting by name
bool sortByName( Student& a,  Student& b) {
    return a.getFullName() < b.getFullName();
}



// Function to perform Insertion Sort
template<typename T,typename Compare>
void insertionSort(T& arr, Compare comp, int& comparisons) {
    for (int i = 1; i < arr.size(); ++i) {
        auto key = arr[i];
        int j = i - 1;
        while (j >= 0 && comp( key,arr[j])) {
            arr[j + 1] = arr[j];
            j--;
            comparisons++;
        }
        arr[j + 1] = key;
    }
}

// Function to perform Selection Sort
template<typename T,typename Compare>
void selectionSort(T& arr,Compare comp, int& comparisons) {
    int n = arr.size();

    for (int i = 0; i < n - 1; ++i) {
        int min = i;
        for (int j = i + 1; j < n; ++j) {
            if(comp(arr[j] , arr[min]))
                min = j,comparisons++;
        }
        if (min != i) { swap(arr[min], arr[i]); }
    }
}
template<typename T,typename Compare>
void bubbleSort(T& arr,Compare comp, int& comparisons){
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (!comp(arr[j] , arr[j+1])) {
                swap(arr[j], arr[j + 1]),comparisons++;
            }
        }
    }
}


template<typename T,typename Compare>
void shellSort(T& arr,Compare comp, int& comparisons){
    int n=arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            auto temp = arr[i];
            int j;
            for (j = i; j >= gap && !comp(arr[j - gap] , temp); j -= gap) {
                arr[j] = arr[j - gap],comparisons++;
            }
            arr[j] = temp;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, typename Compare>
int partition(deque<T>& arr, int low, int high, Compare comp, int& comparisons) {
    T pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (comp(arr[j], pivot)) {
            ++i,comparisons++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

template<typename T,typename Compare>
void quickSort(T& arr,int low,int high,Compare comp, int& comparisons){
    if (low < high) {
        int pi = partition(arr, low, high, comp,comparisons);
        quickSort(arr, low, pi - 1, comp,comparisons);
        quickSort(arr, pi + 1, high, comp,comparisons);
    }
}
template<typename T, typename Compare>
void merge(deque<T>& arr, int l, size_t m, size_t r, Compare comp,int& comparisons) {
    size_t n1 = m - l + 1,n2 = r - m;

//    deque<T>L((arr.begin()) + left, arr.begin() + left + n1);
//    deque<T>R(arr.begin() + m + 1, arr.begin() + m + 1 + n2);

    deque<T>L(n1);
    deque<T>R(n2);

    for (int i = 0; i < n1; ++i) {
        L[i] = (arr[l + i]);
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[m + 1 + j];
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (comp(L[i], R[j])) {
            arr[k++] = L[i++],comparisons++;
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }
}

template<typename T,typename Compare>
void mergeSort(deque<T>& arr, int l, int r, Compare comp,int& comparisons) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, comp,comparisons);
        mergeSort(arr, m + 1, r, comp,comparisons);
        merge(arr, l, m, r, comp,comparisons);
    }
}
template<typename T,typename Compare>

void countSort(deque<T>& arr,Compare comp,int& comparisons) {
    // Find the maximum GPA in the array
    double maxGPA = 0;
    for (const auto& student : arr) {
        maxGPA = std::max(maxGPA, student.gpa);
    }

    // Create a count array to store the count of each GPA
    deque<int> count(static_cast<int>(maxGPA) + 1, 0);
    for (const auto& student : arr) {
        ++count[static_cast<int>(student.gpa)];
    }

    // Modify the count array to store the actual position of each GPA in the output array
    for (int i = 1; i <= maxGPA; ++i) {
        count[i] += count[i - 1];
    }

    // Create a temporary array to store the sorted output
    deque<T> output(arr.size());
    for (int i = arr.size() - 1; i >= 0; --i) {
        output[count[static_cast<int>(arr[i].gpa)] - 1] = arr[i];
        --count[static_cast<int>(arr[i].gpa)];
    }

    // Copy the sorted output back to the original array
    for (size_t i = 0; i < arr.size(); ++i) {
        arr[i] = output[i];
    }
}
//using SortingFunctionName = std::function<void(std::deque<Student>&)>;
//
//// Function to apply a sorting function to a deque of students
//void applySortingFunctionName(std::deque<Student>& students, SortingFunctionName sortingFunctionName) {
//    sortingFunctionName(students);
//}


//using SortingFunctionGpa = std::function<void(std::deque<Student>&)>;
//
//// Function to apply a sorting function to a deque of students
//void applySortingFunctionGpa(std::deque<Student>& students, SortingFunctionGpa sortingFunctionGpa) {
//    sortingFunctionGpa(students);
//}

using SortingFunction = std::function<void(deque<Student>&)>;
using SortingFunctionName = std::function<void(deque<Student>&)>;


#endif //UNTITLED7_STUDENT_H
