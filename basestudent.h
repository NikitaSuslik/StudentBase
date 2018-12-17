#ifndef BASESTUDENT_H
#define BASESTUDENT_H

#include <iostream>
#include <string.h>

const int sizeArray = 15;

struct student {
public:
    student(int id, const char* name, const char* secondname, const char* lastname, const char* birthday, const char* groupe);
    ~student();
    void getInfo(bool fullInfo);


private:
    int id;
    char name[sizeArray] = "";
    char secondname[sizeArray] = "";
    char lastname[sizeArray] = "";
    char groupe[sizeArray] = "";
    char birthday[10] = "";
};




#endif // BASESTUDENT_H
