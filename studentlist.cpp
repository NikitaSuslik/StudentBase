#include "studentlist.h"


bool StudentList::addStudent()
{
    cout << "Print info about student:/nName ";
    char name[sizeArray];
    cin >> name;
    cout << "\nLastname: ";
    char lastname[sizeArray];
    cin >> lastname;
    cout << "\nSecondname: ";
    char secondname[sizeArray];
    cin >> secondname;
    cout << "\nGroupe: ";
    char groupe[sizeArray];
    cin >> groupe;
    cout << "\nBirthday: ";
    char birthday[sizeArray];
    cin >> birthday;


    StudentNode* n = new StudentNode();
    return true;
}
