#include "studentlist.h"


bool StudentList::empty()
{
    return last == nullptr || first == nullptr;
}

void StudentList::addStudent()
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
    cout << "\nBirthday(format dd.mm.yyyy): ";
    char birthday[sizeArray];
    cin >> birthday;
    iteration++;
    size++;
    StudentNode* n = new StudentNode();
    n->studentData = new student(iteration, (const char*) name, (const char*)secondname, (const char*)lastname, (const char*)birthday, (const char*) groupe);
    if(empty()) {
        first = last = n;
        first->nextStud = last;
        last->prevStud = first;
    }
    else {
        StudentNode* FindStud = findStudent(lastname);
        if(FindStud == last){
            last->nextStud = n;
            n->prevStud = last;
            last = n;
        }
        else if (FindStud == nullptr) {
            first->prevStud = n;
            n->nextStud = first;
            first = n;
        }
        else {
            StudentNode* tmpStud = FindStud->nextStud;
            FindStud->nextStud = n;
            n->nextStud = tmpStud;
            tmpStud->prevStud = n;
            n->prevStud = FindStud;
        }
    }
}

bool StudentList::saveBase()
{
    ofstream oFile;
    oFile.open("/Users/nikita/Desktop/Data.my",ios_base::binary | ios_base::trunc);
    if(oFile.is_open()){
        point = first;
        while(point != nullptr){
            oFile.write((const char*) point->studentData, sizeof (student));
            point = point->nextStud;
        }
        oFile.close();
    }

}

void StudentList::changeSort()
{
    switch (sort) {
    case sorting::up:
        sort = sorting::down;
        break;
    case sorting::down:
        sort = sorting::up;
        break;
    }
}

StudentNode* StudentList::findStudent(const char *lastname)
{
    if(empty()) return  nullptr;
    else{
        char* tmpLastName = point->studentData->getLastName();
        if(strcmp(lastname, tmpLastName) < 0) return nullptr;
        while(strcmp(lastname, tmpLastName) >= 0){
            if(point == last) return last;
            point = point->nextStud;
            tmpLastName = point->studentData->getLastName();
        }
        return point;
    }
}




