#include "basestudent.h"




student::student(const char *name, const char *secondname, const char *lastname, const char *birthday, const char *groupe)
{
    size++;
    iterator++;
    id = iterator;
    strcpy(this->name, name);
    strcpy(this->secondname, secondname);
    strcpy(this->lastname, lastname);
    strcpy(this->birthday, birthday);
    strcpy(this->groupe, groupe);

}

student::~student()
{
    //!!!!!!!!!!!!!!!!
}

bool student::deleteStudent(student *stud)
{
    prevStudent->nextStudent = nextStudent;
}
