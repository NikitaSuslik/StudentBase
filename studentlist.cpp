#include "studentlist.h"


bool StudentList::empty()
{
    return first == nullptr;
}

void StudentList::addStudent()
{
    cout << "Print info about student:\nName ";
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
    StudentNode* n = new StudentNode;
    n->studentData = new student(iteration, (const char*) name, (const char*)secondname, (const char*)lastname, (const char*)birthday, (const char*) groupe);
    if(empty()) {
        first = last = n;
    }
    else {
        StudentNode* FindStud = findStudent(lastname);
        if (FindStud == nullptr) {
            first->prevStud = n;
            n->nextStud = first;
            first = n;
        }
        else if(strcmp(lastname, FindStud->studentData->getLastName()) >= 0){
            last->nextStud = n;
            n->prevStud = last;
            last = n;
        }
        else {
            n->prevStud = FindStud->prevStud;
            n->nextStud = FindStud;
            FindStud->prevStud = n;
            n->prevStud->nextStud = n;
        }
    }
}

void StudentList::deleteSudent()
{
    if(point == last) {
        last = point->prevStud;
        last->nextStud = nullptr;
        delete point;
    }
    else if(point == first){
        first = point->nextStud;
        first->prevStud = nullptr;
        delete point;
    }
    else if(first == last){
        delete point;
        first = last = nullptr;
    }
    else {
        StudentNode* tmpNext = point->nextStud;
        StudentNode* tmpPrev = point->prevStud;
        delete point;
        point = nullptr;
        tmpNext->prevStud = tmpPrev;
        tmpPrev->nextStud = tmpNext;
    }
    size--;
}

void StudentList::addStudent(student* stud)
{
    iteration++;
    size++;
    StudentNode* n = new StudentNode;
    n->studentData = stud;
    if(empty()) {
        first = last = n;
        first->nextStud = last;
        last->prevStud = first;
    }
    else {
        StudentNode* FindStud = findStudent(stud ->getLastName());
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
        oFile.write((const char*)&iteration,sizeof (int));
        point = first;
        while(point != nullptr){
            oFile.write((const char*) point->studentData, sizeof (student));
            point = point->nextStud;
        }
        oFile.close();
    }
    return true;
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

bool StudentList::loadBase()
{
    ifstream iFile;
    iFile.open("/Users/nikita/Desktop/Data.my", ios_base::binary);
    if(iFile.is_open()){
        iFile.read((char*)&iteration,sizeof (int));
        while(iFile.eof()){
            student* tmpStudent;
            iFile.read((char*)&tmpStudent, sizeof (student));
            addStudent(tmpStudent);
        }
        iFile.close();
        return true;
    }
    else return false;
}

void StudentList::printInfoStudent(bool fullInfo)
{
    if(fullInfo){
        cout << "Lastname: " << point->studentData->getLastName() << " "
             << point->studentData->getName()
             << point->studentData->getSecondName() << "\n"
             <<"ID " << point->studentData->getID() << "\n"
             "Birtday " << point->studentData->getBirthDay() <<"\n"
             "Groupe " << point->studentData->getBirthDay() << "\n";
    }
    else {
        cout << point->studentData->getLastName() << " " << point->studentData->getName() <<"\n";
    }
}

void StudentList::printInfoBase()
{
    int iter = 1;
    switch (sort) {
    case StudentList::sorting::up:
        point = first;
        while (point != nullptr){
            cout << "\n" << iter << " ################################# " << iter << "\n";
            printInfoStudent();
            point = point->nextStud;
            iter++;
        }
        break;
    case StudentList::sorting::down:
        point = last;
        while (point != nullptr){
            cout << "\n" << iter << " ################################# " << iter << "\n";
            printInfoStudent();
            point = point->prevStud;
            iter++;
        }
        break;
    }
}

StudentNode* StudentList::findStudent(const char *lastname)
{
    if(empty()) return  nullptr;
    else{
        point = first;
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

void StudentList::ShowMenu()
{
    cout << "Please print:\n"
            "\"a\" - for adding student\n"
            "\"p\" - for printing base\n"
            "\"f\" - for find student\n"
            "\"e\" - check is empty\n"
            "\"c\" - for change sorting\n"
            "\"s\" - for save base\n"
            "\"l\" - for load base\n";
}

void StudentList::Initialize()
{
    char command = 'h';
    while (true){
        ShowMenu();

        cin.get(command);
        switch (command) {
        case 'a':
            addStudent();
            break;
        case 'p':
            if(empty()){
                cout << "Base is empty!";
                break;
            }
            printInfoBase();
            cout << "Press any key for quit\n";
            getchar();
            break;
        case 'f':
            char tmpLastName[sizeArray];
            cout << "Input Lastname for searching: ";
            cin >> tmpLastName;
            cout << '\n';
            findStudent(tmpLastName);
            if(point != nullptr)
                if(strcmp(tmpLastName, point->studentData->getLastName()) != 0)
                    break;
            while (command != 'q') {
                cout << "Find student:\n";
                printInfoStudent();
                cout << "What is next?\n"
                        "\"d\" - delete\n"
                        "\"p\" - print full info\n"
                        "\"q\" - qiut\n";
                cin.get(command);
                cin.get();
                switch (command) {
                case 'd':
                    deleteSudent();
                    cout << "Student deleted\n";
                    command ='q';
                    break;
                case 'p':
                    printInfoStudent(true);
                    cout << "Press any key for continue.\n";
                    cin.get();
                    break;
                case 'q':
                    break;
                default:
                    cout << "Unknow command.\nTry again.\nPress any key for continue.\n";
                    cin.get();
                    system("clear");
                    break;
                }
            }
            break;
        case 'q':
            return;
        case 'c':
            changeSort();
            switch (sort) {
            case StudentList::sorting::up:
                cout << "Sort up\n";
                break;
            case StudentList::sorting::down:
                cout << "Sort down\n";
                cout << "Press any key for continue.\n";
                cin.get();
                break;
            }
            break;
        case 'e':
            if(empty()) cout << "Empty!\n";
            else cout << "Not empty!\n";
            cout << "Press any key for continue.\n";
            cin.get();
            break;
        case 's':
            saveBase();
            cout << "Not empty!\n";
            cout << "Press any key for continue.\n";
            cin.get();
            break;
        case 'l':
            loadBase();
            break;
        default:
            cout << "Unkown commmand.\nTry again.\nPress any key for continue.\n";
            cin.get();
            break;
        }
        system("clear");
    }
}




