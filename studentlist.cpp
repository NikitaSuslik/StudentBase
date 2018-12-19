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
    StudentNode* n = new StudentNode;
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

void StudentList::deleteSudent()
{
    StudentNode* tmpNext = point->nextStud;
    StudentNode* tmpPrev = point->prevStud;
    delete point;
    point = nullptr;
    tmpNext->prevStud = tmpPrev;
    tmpPrev->nextStud = tmpNext;
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
    point = first;
    int iter = 1;
    while (point != nullptr){
        cout << "\n" << iter << " ################################# " << iter << "\n";
        printInfoStudent();
        point = point->nextStud;
        iter++;
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

void StudentList::ShowMenu()
{
    cout << "Please print:\n"
            "\"a\" - for adding student\n"
            "\"p\" - for printing base\n"
            "\"f\" - for find student\n"
            "\"e\" - check is empty\n";
}

void StudentList::Initialize()
{
    char command = 'h';
    while (true){
        ShowMenu();
        cin.get(command);
        cin.clear();
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
                cin.clear();
                switch (command) {
                case 'd':
                    deleteSudent();
                    cout << "Student deleted\n";
                    command ='q';
                    break;
                case 'p':
                    printInfoStudent(true);
                    cout << "Press any key for continue.\n";
                    getchar();
                    break;
                case 'q':
                    break;
                default:
                    cout << "Unknow command.\nTry again.\nPress any key for continue.\n";
                    getchar();
                    system("clear");
                    break;
                }
            }
            break;
        case 'q':
            return;
        case 'e':
            if(empty()) cout << "Empty!\n";
            else cout << "Not empty!\n";
            cout << "Press any key for continue.\n";
            getchar();
            break;
        default:
            cout << "Unkown commmand.\nTry again.\nPress any key for continue.\n";
            getchar();
            break;
        }
        system("clear");
    }
}




