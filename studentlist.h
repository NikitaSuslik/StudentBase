#ifndef STUDENTLIST_H
#define STUDENTLIST_H
#include "basestudent.h"

struct StudentNode {
public:
    student* data = nullptr;
    student* nextStud = nullptr;
    //student* prevStud = nullptr;
};

struct StudentList
{
public:
    StudentList() {}
    ~StudentList();
    bool addStudent();
    bool saveBase();
    void changeSort();
    StudentList* loadBase();
    void printInfoStudent(bool fullInfo);
    void printInfoBase();
    student findStudent(int iter);
    student findStudent(const char* name);

private:
    StudentNode* iter = nullptr;
    StudentNode* head = nullptr;
    int size = 0;
    enum sorting {up, down};
    sorting sort = sorting::down;

};

#endif // STUDENTLIST_H