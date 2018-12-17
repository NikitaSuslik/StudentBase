#ifndef BASESTUDENT_H
#define BASESTUDENT_H

#include <iostream>
#include <string.h>



struct student {
public:
    student(const char* name, const char* secondname, const char* lastname, const char* birthday, const char* groupe);
    ~student();
    bool deleteStudent(student* stud);
    void changeSorting(int);                                // 0 - up or 1 - down
    bool saveBase();
    student* loadbase();
    static void printBase();
    void printStudent(student* stud, bool fullInfo);
    static student* findStudent(const char* name);

    static student* head;
    static student* iter;



private:
    int id;
    char name[10] = "";
    char secondname[10] = "";
    char lastname[10] = "";
    char groupe[10] = "";
    char birthday[10] = "";
    enum sort {up, down};
    student* nextStudent = nullptr;
    student* prevStudent = nullptr;
    static int size;
    static int iterator;
};




#endif // BASESTUDENT_H
