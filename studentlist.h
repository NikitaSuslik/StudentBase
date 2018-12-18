#ifndef STUDENTLIST_H
#define STUDENTLIST_H

#include <iostream>
#include <fstream>


#include "basestudent.h"

using namespace std;

struct StudentNode {
public:
    StudentNode();
    student* studentData = nullptr;
    StudentNode* nextStud = nullptr;
    StudentNode* prevStud = nullptr;
};

struct StudentList
{
public:
    StudentList() {}
    ~StudentList();
    bool empty();
    void addStudent();
    bool saveBase();
    void changeSort();
    StudentList* loadBase();
    void printInfoStudent(bool fullInfo);
    void printInfoBase();
    StudentNode* findStudent(int iter);
    StudentNode* findStudent(const char* lastname);


private:
    
    StudentNode* point = nullptr;
    StudentNode* last = nullptr;
    StudentNode* first = nullptr;
    int size = 0;
    int iteration = 0;
    enum sorting {up, down};
    sorting sort = sorting::down;

};

#endif // STUDENTLIST_H
