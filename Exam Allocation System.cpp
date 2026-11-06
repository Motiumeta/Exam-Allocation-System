#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <limits>

using namespace std;

void clear(){
    #ifdef _WIN32
        system("cls");
    #else 
        system("clear");
    #endif
}

struct Course {
    string name;
    string id;
};
struct Student{
    string fName;
    string lName;
    string id;
    vector<string> coursesId;
};

struct Room{
    string id;
    string location;
    int capacity;
};

struct Seat{
    string roomId;
    string seatNumber;
    string studentId;
    bool isAvailable;
};

struct Exam{
    string examId;
    string courseId;
    string time;
    bool assigned = false;
    vector<string> roomsId;
    vector<Seat> seats;
};

struct Ticket{
    string time;
    string examId;
    string studentId;
    string courseId;
    string seatNumber;
    string roomId;
};

vector<Room> rooms;
vector<Course> courses;
vector<Student> students;
vector<Exam> exams;
vector<Ticket> tickets;


// Utility Functions
bool confirm(){
    string input;
    cout << string(25, '-') << endl;
    cout << "Enter '1' to Confirm: ";
    cin >> input;
    
    if(input == "1"){
        return true;
    }
    else {
        return false;
    }
}
void toContinue(){
    cout << "Enter to continue...";
    cin.get();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    clear();
}
void printHeader(string header, int num){
    cout << string(num, '-') << endl;
    cout << header << endl;
    cout << string(num, '-') << endl;
}
int getNumber(string prompt){
    string num;
    while(true){
        cout << prompt;
        cin >> num;
        if(num == "0"){
            return stoi(num);
        }
        bool found = false;
        for(char &c : num){
            if(!isdigit(c)){
                found = true;
                cout << "Enter Only Number." << endl;
                break;
            }
        }
        if(!found) return stoi(num);
    }

    
}
void printDivider() {
    clear();
    cout << string(25, '-') << endl;
}
void printDivider(string msg) {
    clear();
    cout << string(25, '-') << endl;
    cout << msg << endl;
}
void ignoreChar(){
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
// Getters
Course* getCourseById(string courseID){
    for(Course &c : courses){
        if(c.id == courseID){
            return &c;
        }
    }
    return nullptr;
}
Exam* getExamById(string examID){
    for(Exam &e : exams){
        if(examID == e.examId) return &e;
    }
    return nullptr;
}

bool inputCourse(Course &tCourse){
    clear();
    printHeader("INPUT COURSE", 25);
    cout << "Enter Course Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, tCourse.name);
    if(tCourse.name == "0"){
        clear();
        return false;
    }
    cout << "Enter Course Id: ";
    cin >> tCourse.id;
    if(tCourse.id == "0") {
        clear();
        return false;
    }
    return true;
}
bool isCourseExist(string courseID){
    for(Course &c : courses){
        if(c.id == courseID) return true;
    }
    return false;
}
void addCourseToList(Course tCourse){
    courses.push_back(tCourse); 
}
void addCourse2(){
    Course tCourse;
    if(!inputCourse(tCourse)){
        printDivider();
        return;
    }

    printDivider();
    if(!isCourseExist(tCourse.id)){
        if(confirm()){
            addCourseToList(tCourse);
            printDivider("Course Added");
        }
        else printDivider("Operation Canceled.");
        
    }
    else printDivider("Course with that ID already exists.");
    
}

void addCourse(){
    clear();
    printHeader("MANAGE COURSE", 25);
    Course tCourse;
    cout << "Enter Course Name: ";
    cin.ignore();
    getline(cin, tCourse.name);
    if(tCourse.name == "0"){
        clear();
        return;
    }
    cout << "Enter Course Id: ";
    cin >> tCourse.id;
    if(tCourse.id == "0") {
        clear();
        return;
    }
    for(Course &c : courses){
        if(c.id == tCourse.id){
            clear();
            cout << string(25, '-') << endl;
            cout << "Course with that ID already exists." << endl;
            return;
        }
    }

    if(confirm()){
        courses.push_back(tCourse);
        clear();
        cout << string(25, '-') << endl;
        cout << "Course Added" << endl;
    }
    else{
        clear();
        cout << string(25, '-') << endl;
        cout << "Operation Canceled." << endl;
    }
}
void listCourses(){    
    if(courses.size() == 0){
        cout << string(25, '-') << endl;
        cout << "No Course Available" << endl;
        return;
    }
    printHeader("LIST COURSES", 35);    
    cout << left << setw(15) << "Course ID" << setw(20) << "| Course Name" << endl;
    cout << string(35, '-') << endl;
    for(Course &c : courses){
        cout << setw(15) << c.id << "| " << setw(18) << c.name << endl;
    }
    cout << string(35, '-') << endl;
    cout << "Total Courses: " << courses.size() << endl;
    cout << string(25, '-') << endl;
    toContinue();

}
void updateCourse2(){
    clear();
    string tCourseId;
    printHeader("UPDATING COURSES", 25);
    cout << "Enter Course ID: ";
    cin >> tCourseId;
    if(tCourseId == "0"){
        clear();
        return;
    }
    if(isCourseExist(tCourseId)){
        Course *c = getCourseById(tCourseId);
        string newName;
        printHeader("UPDATING COURSES", 25);
        cout << "Name: " << c->name << endl;
        cout << "Enter New Name: ";
        cin.ignore();
        getline(cin, newName);
        if(newName == "0"){
            clear();
            return;
        }
        if(confirm()){
            c->name = newName;
            printDivider("Name Updated Successfully.");
        }
        else printDivider("Operation Canceled.");
    }
}
void updateCourse(){
    clear();
    string tCourseId;
    printHeader("UPDATING COURSES", 25);
    cout << "Enter Course ID: ";
    cin >> tCourseId;
    if(tCourseId == "0"){
        clear();
        return;
    }
    bool found = false;

    
    for(Course &c : courses){
        if(c.id == tCourseId){
            found = true;
            clear();
            string newName;
            printHeader("UPDATING COURSES", 25);
            cout << "Name: " << c.name << endl;
            cout << "Enter New Name: ";
            cin.ignore();
            getline(cin, newName);
            if(newName == "0"){
                clear();
                return;
            }
            
            if(confirm()){
                clear();
                c.name = newName;
                cout << string(25, '-') << endl;
                cout << "Name Updated Successfully." << endl;
            }
            else {
                clear();
                cout << string(25, '-') << endl;
                cout << "Operation Canceled." << endl;
            }
        }
    }

    if(!found){
        clear();
        cout << string(30, '-') << endl;
        cout << "Course with that ID is not available" << endl;
    }
    

}

string getInput(string prompt){
    string input;
    cout << prompt;
    ignoreChar();
    getline(cin, input);
    return input;
}
bool isRoomExist(string &roomID){
    for(Room &r : rooms){
        if(r.id == roomID){
            return true;
        }
    }
    return false;
}
bool inputRoom(Room &r){
    r.location = getInput("Enter Room Location: ");
    if(r.location == "0") return false;
    
    r.capacity = getNumber("Enter Room Capacity: ");
    if(r.capacity == 0) return false;

    return true;
}
void addRoom2(){
    clear();
    printHeader("ADDING ROOM", 25);
    Room tRoom;
    tRoom.id = getInput("Enter Room Id: ");
    if(tRoom.id == "0"){
        printDivider("Operation canceled.");
        return;
    }
    if(!isRoomExist(tRoom.id)){
        if(!inputRoom(tRoom)) return;
        if(confirm()){
            rooms.push_back(tRoom);
            printDivider("Room is Added.");
        }
        else printDivider("Operation canceled.");
    }
    else printDivider("Room with that ID already exists.");
}

void addRoom(){
    clear();
    printHeader("ADDING ROOM", 25);
    Room tRoom;
    cout << "Enter Room Id: ";
    cin >> tRoom.id;    
    if(tRoom.id == "0"){
        clear();
        cout << string(25, '-') << endl;
        cout << "Operation canceled." << endl;
        return;
    }
    for(Room &r : rooms){
        if(r.id == tRoom.id){
            clear();
            cout << string(25, '-') << endl;
            cout << "Room with that ID already exists." << endl;
            return;
        }
    }
    cout << "Enter Room Location: ";
    cin >> tRoom.location;
    if(tRoom.location == "0"){
        clear();
        cout << string(25, '-') << endl;
        cout << "Operation canceled." << endl;
        return;
    }
    tRoom.capacity = getNumber("Enter Room Capacity: ");
    if(tRoom.capacity == 0){
        clear();
        cout << string(25, '-') << endl;
        cout << "Operation canceled." << endl;
        return;
    }

    if(confirm()){
        rooms.push_back(tRoom);
        clear();
        cout << string(25, '-') << endl;
        cout << "Room is Added" << endl;
    }
    else {
        clear();
        cout << string(25, '-') << endl;
        cout << "Operation canceled." << endl;
        return;
    }

    

    
}
void listRooms(){
    clear();
    if(rooms.size() == 0){
        printDivider("No Room is Available");
        return;
    }
    printHeader("ROOM LIST", 36);
    cout << left << setw(6) << "| ID" << setw(15) << "| Location" << setw(14) << "| Capacity" << "|" << endl;
    cout << string(36, '-') << endl;
    for(Room &r : rooms){
        cout << "| " << setw(4) << r.id << "| " << setw(13) << r.location << "| " << setw(12) << r.capacity << "|" << endl;
    }
    cout << string(36, '-') << endl;
    cout << "Total Rooms: " << rooms.size() << endl;
    cout << string(36, '-') << endl;
    toContinue();
}
Room* getRoomById(string &roomId){
    for(Room &r : rooms){
        if(roomId == r.id) return &r;
    }
    return nullptr;
}
void updateRoom2(){
    clear();
    string tRoomId;
    printHeader("UPDATING ROOM", 25);
    tRoomId = getInput("Enter Room Id: ");
    if(tRoomId == "0") return;

    if(isRoomExist(tRoomId)){
        Room *r = getRoomById(tRoomId);
        clear();
        string choice;
        printHeader("UPDATING ROOM", 25);
        cout << "1 - Edit Location: " << r->location << endl;
        cout << "2 - Edit Capacity: " << r->capacity << endl;
        cout << "0 - Back" << endl;
        cout << string(25, '-') << endl;
        choice = getInput("> ");
        if(choice == "1"){
            clear();
            string newLocation;
            printHeader("UPDATING ROOM", 25);
            newLocation = getInput("Enter new location: ");
            if(newLocation == "0"){
                printDivider("Operation Canceled.");
                return;
            }
            if(confirm()){
                r->location = newLocation;
                printDivider("Room Location Updated Successfully");
            }
            else printDivider("Operation Canceled.");
        }
        else if(choice == "2"){
            clear();
            int newCapacity;
            printHeader("UPDATING ROOM", 25);
            newCapacity = getNumber("Enter new capacity: ");
            if(newCapacity == 0){
                printDivider("Operation Canceled.");
                return;
            }
            if(confirm()){
                r->capacity = newCapacity;
                printDivider("Room Location Updated Successfully");
            }
            else printDivider("Operation Canceled.");
        }
        else if(choice == "0") return;
    } 
    else printDivider("Room with that ID is not available"); 

}
void updateRoom(){
    clear();
    string tRoomId;
    printHeader("UPDATING ROOM", 25);
    tRoomId = getInput("Enter Room Id: ");
    if(tRoomId == "0") return;
    
    bool found = false;

    for(Room &r : rooms){
        if(r.id == tRoomId){
            clear();
            found = true;
            string choice;
            printHeader("UPDATING ROOM", 25);
            cout << "1 - Edit Location: " << r.location << endl;
            cout << "2 - Edit Capacity: " << r.capacity << endl;
            cout << "0 - Back" << endl;
            cout << string(25, '-') << endl;
            cout << "> ";
            cin >> choice;

            if(choice == "1"){
                clear();
                string newLocation;
                printHeader("UPDATING ROOM", 25);
                cout << "Enter new location: ";
                cin >> newLocation;
                if(newLocation == "0"){
                    clear();
                    cout << string(25, '-') << endl;
                    cout << "Operation Canceled." << endl;
                    return;
                }

                if(confirm()){
                    r.location = newLocation;
                    clear();
                    cout << string(25, '-') << endl;
                    cout << "Room Location Updated Successfully." << endl;
                }
                else {
                    clear();
                    cout << string(25, '-') << endl;
                    cout << "Operation Canceled." << endl;
                }
            }
            else if(choice == "2"){
                clear();
                printHeader("UPDATING ROOM", 25);
                int newCapacity;
                newCapacity = getNumber("Enter New Capacity: ");
                if(newCapacity == 0){
                    clear();
                    cout << string(25, '-') << endl;
                    cout << "Operation Canceled." << endl;
                    return;
                }

                if(confirm()){
                    r.capacity = newCapacity;
                    clear();
                    cout << string(25, '-') << endl;
                    cout << "Room's capacity is updated." << endl;
                }
                else {
                    clear();
                    cout << string(25, '-') << endl;
                    cout << "Operation canceled." << endl;
                }

            }
            else if(choice == "0"){
                clear();
                break;
            }
        }
    }

    if(!found){
        clear();
        cout << string(25, '-') << endl;
        cout << "Room with that ID is not available." << endl;
    }
}

bool isStudentsExist(string &studentdId){
    for(Student &s : students){
        if(s.id == studentdId) return true;
    }
    return false;
}
bool inputStudent(Student &tStudent){
    clear();
    printHeader("REGISTERING STUDENT", 25);
    tStudent.fName = getInput("Enter Fisrt Name: ");
    tStudent.lName = getInput("Enter Last Name: ");
    if(tStudent.fName == "0" || tStudent.lName == "0"){
        printDivider("Operation Canceled.");
        return false;
    }
    tStudent.id = getInput("Students Id: ");
    if(tStudent.id == "0"){
        printDivider("Operation Canceled.");
        return false;
    }
    if(!isStudentsExist(tStudent.id)) return true;
    else {
        printDivider("Student with that id already exist.");
        return false;
    }
    
}
void inputStudentCourse(vector<string> &coursesId){
    cout << "Enter the course id and when finished Enter 0" << endl;
    while(true){
        string courseId;
        cout << "> ";
        cin >> courseId;
        if(courseId == "0" && coursesId.size() != 0){
            break;
        }
        bool similarCourse = false;
        for(string &cId : coursesId){
            if(cId == courseId){
                similarCourse = true;
                cout << "Course is already added." << endl;
                break;
            }
        }
        if(similarCourse) continue;
        bool courseFound = false;
        for(Course &c : courses){
            if(c.id == courseId){
                courseFound = true;
                coursesId.push_back(courseId);
                break;
            }
        }
        if(!courseFound) cout << "Course ID invalid." << endl;
    }

}
void addStudent2(){
    Student tStudent;
    if(!inputStudent(tStudent)) return;
    if(courses.size() == 0){
        cout << "No available course to add." << endl;
    }
    else {
        clear();
        printHeader("REGISTERING STUDENT", 25);
        cout << "Available Courses" << endl;
        listCourses();
        inputStudentCourse(tStudent.coursesId);
        
    }
    if(confirm()){
        students.push_back(tStudent);
        printDivider("Student Added Successfully");
    }
    else {
        printDivider("Operation Canceled.");
    }
}

void addStudent(){
    clear();
    printHeader("REGISTERING STUDENT", 25);
    Student tStudent;
    cout << "Enter Name: ";
    cin >> tStudent.fName >> tStudent.lName;
    if(tStudent.fName == "0" || tStudent.lName == "0"){
        clear();
        cout << string(25, '-') << endl;
        cout << "Operation Canceled." << endl;
        return;
    }
    cout << "Students Id: ";
    cin >> tStudent.id;
    if(tStudent.id == "0"){
        clear();
        cout << string(25, '-') << endl;
        cout << "Operation Canceled." << endl;
        return;
    }
    for(Student &s : students){
        if(s.id == tStudent.id){
            clear();
            cout << string(25, '-') << endl;
            cout << "Student with that id already exist." << endl;
            return;
        }
    }
    if(courses.size() == 0){
        cout << "No available course to add." << endl;
    }
    else {
        clear();
        printHeader("REGISTERING STUDENT", 25);
        cout << "Available Courses" << endl;
        for(Course &c : courses){
            cout << "Name: " << c.name << " Id: " << c.id << endl;
        }

        cout << "Enter the course id and when finished Enter 0" << endl;
        while(true){
            string courseId;
            cout << "> ";
            cin >> courseId;
            if(courseId == "0"){
                break;
            }
            bool similarCourse = false;
            for(string &cId : tStudent.coursesId){
                if(cId == courseId){
                    similarCourse = true;
                    cout << "Course is already added." << endl;
                    break;
                }
            }
            if(similarCourse) continue;

            bool courseFound = false;
            for(Course &c : courses){
                if(c.id == courseId){
                    courseFound = true;
                    tStudent.coursesId.push_back(courseId);
                    break;
                }
            }
            if(!courseFound) cout << "Course ID invalid." << endl;
            
        }
    }

    if(confirm()){
        students.push_back(tStudent);
        clear();
        cout << string(25, '-') << endl;
        cout << "Student Added Successfully" << endl;
    }
    else {
        clear();
        cout << string(25, '-') << endl;
        cout << "Operation Canceled." << endl;
    }
    
}

void viewStudents(){
    if(students.size() == 0){
        printDivider("No Students are registered.");
        return;        
    }
    printHeader("LIST OF STUDENTS", 25);

    cout << left << setw(25) << "| Name" << setw(15) << "| ID" << setw(20) << "| Courses" << endl;
    cout << string(60, '-') << endl;
    for(Student &s : students){
        string studentName = s.fName + " " + s.lName;
        cout << "| " << setw(23) << studentName << "| " << setw(13) << s.id << "| " ;
        for(string &cId : s.coursesId){
            for(Course &c : courses){
                if(cId == c.id){
                    cout << c.id << ", ";
                }
            }
        }
        cout << endl;
    }
    cout << string(60, '-') << endl;
    cout << "Total Students: " << students.size() << endl;
    cout << string(25, '-') << endl;
    toContinue();
}
void editStudentCourse(){
    clear();
    printHeader("UPDATING STUDENT COURSE", 25);
    string studentId;
    cout << "Enter Student ID: ";
    cin >> studentId;
    if(studentId == "0"){
        clear();
        cout << string(25, '-') << endl;
        cout << "Operation Canceled" << endl;
        return;
    }
    bool found = false;

    for(Student &s : students){
        if(studentId == s.id){
            found = true;
            clear();
            while(true){
                printHeader("UPDATING STUDENT COURSE", 25);
                string choice;
                cout << "1 - Add Course" << endl;
                cout << "2 - Remove Course" << endl;
                cout << "0 - back" << endl;
                cout << string(35, '-') << endl;
                cout << "> ";
                cin >> choice;
                if(choice == "1"){
                    clear();
                    printHeader("UPDATING STUDENT COURSE", 25);
                    cout << "Choose Course ID to add and enter 0 when done." << endl;
                    cout << string(35, '-') << endl;
                    cout << left << setw(15) << "Course ID" << setw(20) << "| Course Name" << endl;
                    cout << string(35, '-') << endl;
                    for(Course &c : courses){
                        bool found = false;
                        for(string &cId : s.coursesId){
                            if(cId == c.id){
                                found = true;
                                break;
                            }
                        }
                        if(!found){
                            cout << setw(15) << c.id << "| " << setw(18) << c.name << endl;
                        }
                    }
                    cout << string(35, '-') << endl;
                    string tCourseId;
                    vector<string> coursesId;
                    while(true){
                        cout << "> ";
                        cin >> tCourseId;
                        
                        for(Course &c : courses){
                            bool found = false;

                            for(string &cId : s.coursesId){
                                if(cId == tCourseId){
                                    found = true;
                                    break;
                                }
                            }

                            if(!found){
                                coursesId.push_back(tCourseId);
                                break;
                            }
                        }
                        if(tCourseId == "0"){
                            break;
                        }
                    }
                    if(confirm()){
                        for(string &cId : coursesId){
                            s.coursesId.push_back(cId);
                        }
                        clear();
                        cout << string(25, '-') << endl;
                        cout << "Course are added successfully." << endl;
                    }
                    else {
                        clear();
                        cout << "Operation Canceled." << endl;
                    }

                }
                else if(choice == "2"){
                    clear();
                    if(s.coursesId.size() == 0){
                        cout << "No Course is enrolled to be removed." << endl;
                        continue;
                    }
                    printHeader("UPDATING STUDENT COURSE", 25);
                    cout << "Choose Course Id to Remove and enter 0 when done." << endl;
                    cout << left << setw(15) << "Course ID" << setw(20) << "| Course Name" << endl;
                    cout << string(35, '-') << endl;
                    for(Course &c : courses){
                        for(string &cId : s.coursesId){
                            if(cId == c.id){
                                cout << setw(15) << c.id << "| " << setw(18) << c.name << endl;
                                break;
                            }
                        }
                    }
                    cout << string(35, '-') << endl;
                    string tCourseId;
                    vector<string> coursesId;
                    while(true){
                        cout << "> ";
                        cin >> tCourseId;
                        if(tCourseId == "0"){
                            break;
                        }// If inp 
                        for(string &cId : s.coursesId){
                            for(Course &c : courses){
                                if(tCourseId == cId && tCourseId == c.id){
                                    coursesId.push_back(tCourseId);
                                }
                            }
                        }
                        
                    }
                    
                    if(confirm()){
                        for(int i = 0; i < coursesId.size(); ++i){
                            for(int j = 0; j < s.coursesId.size(); ++j){
                                if(s.coursesId[j] == coursesId[i]){
                                    s.coursesId.erase(s.coursesId.begin() + j);
                                    j--;
                                }
                            }                            
                        }
                        clear();
                        cout << string(25, '-') << endl;
                        cout << "Courses are removed successfully." << endl;
                    }
                    else {
                        clear();
                        cout << "Operation Canceled." << endl;
                    }

                }
                else if(choice == "0"){
                    clear();
                    break;
                }
                else {
                    clear();
                    cout << string(25, '-') << endl;
                    cout << "Invalid Input" << endl;
                }
            }

        }
    }

    if(!found){
        clear();
        cout << string(25, '-') << endl;
        cout << "Student with that ID is available." << endl;
    }
}
void updateStudent(){
    clear();
    while(true){
        string choice;
        printHeader("UPDATING STUDENT", 25);
        cout << "1 - Edit Name" << endl;
        cout << "2 - Edit Course" << endl;
        cout << "0 - Back" << endl;
        cout << string(25, '-') << endl;
        cout << "> ";
        cin >> choice;
        if(choice == "1"){
            clear();
            printHeader("UPDATING STUDENT", 25);
            string studentId;
            cout << "Enter Student ID: ";
            cin >> studentId;
            if(studentId == "0"){
                clear();
                cout << string(25, '-') << endl;
                cout << "Operation Canceled." << endl;
                return;
            }
            bool found = false;
            for(Student &s : students){
                if(s.id == studentId){
                    found = true;
                    string newFName, newLName;
                    cout << "Name: " << s.fName << " " << s.lName << endl;
                    cout << "Enter New Name(F&L): ";
                    cin >> newFName >> newLName;
                    if(newFName == "0" || newLName == "0"){
                        clear();
                        cout << string(25, '-') << endl;
                        cout << "Operation Canceled." << endl;
                        return;
                    }
                    if(confirm()){
                        clear();
                        s.fName = newFName;
                        s.lName = newLName;
                        cout << string(25, '-') << endl;
                        cout << "Name is Editted." << endl;
                        
                    }
                    else {
                        clear();
                        cout << string(25, '-') << endl;
                        cout << "Operation Canceled." << endl;
                        return;
                    }
                }
            }
            if(!found){
                clear();
                cout << string(25, '-') << endl;
                cout << "Student With that ID is not available." << endl;
            }
        }
        else if(choice == "2"){
            editStudentCourse();
        }
        else if(choice == "0"){
            clear();
            break;
        }
        else {
            clear();
            cout << string(25, '-') << endl;
            cout << "Invalid Input" << endl;
        }
    }

}

void addExam(){
    clear();
    // examid, courseid, room, time, seat
    printHeader("MANAGE EXAM", 25);
    Exam tExam;
    cout << "Enter Exam ID: ";
    cin >> tExam.examId;
    if(tExam.examId == "0"){
        clear();
        cout << string(25, '-') << endl;
        cout << "Operation canceled." << endl;
        return;
    }
    for(Exam &e : exams){
        if(e.examId == tExam.examId){
            clear();
            cout << string(25, '-') << endl;
            cout << "Exam with that ID already exist." << endl;
            return;
        }
    }

    cout << "Enter The time: ";
    cin >> tExam.time;
    if(tExam.time == "0"){
        clear();
        cout << string(25, '-') << endl;
        cout << "Operation canceled." << endl;
        return;
    }

    clear();
    printHeader("MANAGE EXAM", 25);

    cout << "Available Courses" << endl;
    cout << string(25, '-') << endl;
    cout << left << setw(15) << "Name" << setw(10) << "ID" << endl;
    cout << string(25, '-') << endl;
    for(Course &c : courses){
        cout << setw(15) << c.name << setw(10) << c.id << endl;
    }
    while(true){
        cout << string(25, '-') << endl;
        cout << "Choose One Course ID: ";
        cin >> tExam.courseId;

        if(tExam.courseId == "0"){
            clear();
            cout << string(25, '-') << endl;
            cout << "Operation canceled." << endl;
            return;
        }
        bool found = false;
        for(Course &c : courses){
            if(c.id == tExam.courseId){
                found = true;
                break;
            }
        }
        if(!found){
            cout << "The Course doesn't exists." << endl;
            continue;
        }
        break;
    }
    clear();
    printHeader("MANAGE EXAM", 25);
    cout << "Available Rooms" << endl;
    cout << string(25, '-') << endl;
    for(Room &r : rooms){
        cout << "ID: " << r.id << " | Location: " << r.location << " | Capacity: " << r.capacity << endl;
    }
    cout << string(25, '-') << endl;
    cout << "Choose Room ID or 0 when finished" << endl;
    cout << string(25, '-') << endl;
    while(true){
        string roomId;
        cout << "> ";
        cin >> roomId;
        if(roomId == "0"){
            break;
        }
        bool alreadyExist = false;
        for(string &rId : tExam.roomsId){
            if(rId == roomId){
                alreadyExist = true;
                break;
            }
        }
        if(alreadyExist){
            cout << "The Room is Already added." << endl;
            continue;
        }
        bool found = false;
        for(Room &r : rooms){
            if(roomId == r.id){
                found = true;
                tExam.roomsId.push_back(roomId);
                for(int i = 0; i < r.capacity; ++i){
                    Seat seat;
                    seat.roomId = r.id;
                    seat.isAvailable = true;
                    seat.seatNumber = "S" + to_string(i);

                    tExam.seats.push_back(seat);
                }
            }
        }
        if(!found){
            cout << string(25, '-') << endl;
            cout << "Room with that id doesnt exist" << endl;
        }
    }
    if(confirm()){
        exams.push_back(tExam);
        clear();
        cout << string(25, '-') << endl;
        cout << "Exam is Added" << endl;
    }
    else {
        clear();
        cout << string(25, '-') << endl;
        cout << "Operation Canceled." << endl;
    }
}
void viewExam(){
    clear();
    if(exams.size() == 0){
        clear();
        cout << string(25, '-') << endl;
        cout << "No Exam is added yet." << endl;
        return;
    }
    printHeader("VIEW EXAM", 25);
    cout << left << setw(8) << "ExamID" << setw(15) << "Course" << endl;
    cout << string(25, '-') << endl;
    for(Exam &e : exams){
        cout << left << setw(8) << e.examId << setw(15);
        Course* c = getCourseById(e.courseId);
        cout << c->name << endl;
     }
    cout << string(25, '-') << endl;
    string examID;
    cout << "Choose Exam Id: ";
    cin >> examID;
    if(examID == "0"){
        clear();
        cout << string(25, '-') << endl;
        cout << "Operation canceled." << endl;
    }

    clear();

    Exam* e = getExamById(examID);
    if(e == nullptr) {
        clear();
        cout << string(25, '-') << endl;
        cout << "Exam With That id doesnt exist." << endl;
        return;
    }
    Course * c = getCourseById(e->courseId);
    printHeader("VIEW EXAM", 25);
    cout << "ID: " << e->examId << " | Date: " << e->time << " | Course: " << c->name << endl;
    printHeader("ROOMS", 25);
    for(Room &r : rooms){
        for(string &rId : e->roomsId){
            if(rId == r.id){
                cout << "Room ID: " << r.id << " | Room Location: " << r.location << " | Room Capacity: " << r.capacity << endl;
                cout << string(25, '-') << endl;
                cout << "Seats In this Room" << endl;
                cout << string(20, '-') << endl;
                cout << left << setw(10) << "| SeatNo." << setw(9) << "| Status" << "|" << endl;
                cout << string(20, '-') << endl;
                for(Seat &s : e->seats){
                    if(s.roomId == r.id){
                        string status = s.isAvailable ? "[A]" : "[T]";
                        cout << "| " << setw(8) << s.seatNumber << "| " << setw(7) << status << "|" << endl;
                    }
                }
                cout << string(20, '-') << endl;
            }
            
        }
    }
    toContinue();
}
void updateExam(){
    
    clear();
    printHeader("UPDATE EXAM", 25);
    if(exams.size() == 0){
        clear();
        cout << string(25, '-') << endl;
        cout << "There are no Exams To edit." << endl;
        return;
    }
    cout << left << setw(8) << "ExamID" << setw(15) << "Course" << endl;
    cout << string(25, '-') << endl;
    for(Exam &e : exams){
        cout << left << setw(8) << e.examId << setw(15);
        for(Course &c : courses){
            if(e.courseId == c.id){
                cout << c.name << endl;
                break;
            }
        }
     }
    cout << string(25, '-') << endl;
    string examID;
    cout << "Choose Exam ID: ";
    cin >> examID;
    bool found = false;
    for(Exam &e : exams){
        if(examID == e.examId){
            found = true;
            clear();
            while(true){
                printHeader("UPDATE EXAM", 25);
                cout << "1 - Edit Course." << endl;
                cout << "2 - Edit Time." << endl;
                cout << "3 - Edit Room." << endl;
                cout << "0 - Back" << endl;
                cout << string(25, '-') << endl;
                string choice;
                cout << "> ";
                cin >> choice;

                if(choice == "1"){
                    clear();
                    printHeader("UPDATE EXAM", 25);
                    string newCourseID;
                    cout << "Old Course: " << e.courseId << endl;
                    cout << "Available Courses" << endl;
                    cout << string(25, '-') << endl;
                    cout << left << setw(15) << "Name" << setw(10) << "ID" << endl;
                    cout << string(25, '-') << endl;
                    for(Course &c : courses){
                        bool found = false;
                        if(c.id == e.courseId){
                            found = true;
                        }
                        if(!found){
                            cout << setw(15) << c.name << setw(10) << c.id << endl;
                        }
                    }
                    ifItIsTheSameCousres:
                    cout << string(25, '-') << endl;
                    cout << "Choose Course ID: ";
                    cin >> newCourseID;
                    if(newCourseID == "0"){
                        clear();
                        cout << string(25, '-') << endl;
                        cout << "Opearation canceled." << endl;
                        return;
                    }
                    if(newCourseID == e.courseId){
                        cout << "It is the same course as before. Try Again" << endl;
                        goto ifItIsTheSameCousres;
                    }
                    bool found = false;
                    for(Course &c : courses){
                        if(newCourseID == c.id){
                            found = true;
                            break;
                        }
                    }
                    if(!found){
                        cout << "The Course ID doesn't exist. Try Again" << endl;
                        goto ifItIsTheSameCousres;
                    }
                    if(confirm()){
                        e.courseId = newCourseID;
                        clear();
                        cout << string(25, '-') << endl;
                        cout << "Course ID is Changed." << endl;
                    }

                }
                else if(choice == "2"){
                    clear();
                    printHeader("UPDATE EXAM", 25);
                    cout << "Old Time: " << e.time << endl;
                    string newTime;
                    loop1:
                    cout << string(25, '-') << endl;
                    cout << "Enter New Time: ";
                    cin >> newTime;
                    if(newTime == "0"){
                        clear();
                        cout << string(25, '-') << endl;
                        cout << "Opearation canceled." << endl;
                        return;
                    }
                    if(newTime == e.time){
                        cout << "The new time is the same as before. Try again." << endl;
                        goto loop1;
                    }
                    if(confirm()){
                        e.time = newTime;
                        clear();
                        cout << string(25, '-') << endl;
                        cout << "The Time Is changed." << endl;
                    }
                    else {
                        clear();
                        cout << string(25, '-') << endl;
                        cout << "Opearation canceled." << endl;
                        return;
                    }
                }
                else if(choice == "3"){
                    clear();
                    if(rooms.size() == 0){
                        clear();
                        cout << string(25, '-') << endl;
                        cout << "There is no rooms to be assigned." << endl;
                        continue;
                    }
                    while(true){
                        printHeader("UPDATE EXAM", 25);
                        string choice;
                        cout << "1 - Add Room" << endl;
                        cout << "2 - Remove Room" << endl;
                        cout << "0 - Back" << endl;
                        cout << string(25, '-') << endl;
                        cout << "> ";
                        cin >> choice;
                        if(choice == "1"){
                            clear();
                            printHeader("UPDATE EXAM", 25);
                            vector<string> roomsID;
                            for(Room &r : rooms){
                                bool found = false;
                                for(string &rId : e.roomsId){
                                    if(rId == r.id){
                                        found = true;
                                        break;
                                    }
                                }
                                if(!found){
                                    roomsID.push_back(r.id);
                                }
                            }
                            if(roomsID.size() == 0){
                                clear();
                                cout << string(25, '-') << endl;
                                cout << "There are no room that are not assigned to this exam." << endl;
                                continue;                                
                            }
                            cout << "Available Rooms" << endl;
                            cout << string(25, '-') << endl;
                            cout << left << setw(8) << "ID" << setw(10) << "Location" << setw(10) << "Capacity" << endl;
                            cout << string(25, '-') << endl;
                            for(Room &r : rooms){
                                for(string &rId : roomsID){
                                    if(rId == r.id){
                                        cout << setw(8) << r.id << setw(10) << r.location << setw(10) << r.capacity << endl;
                                    }
                                }
                            }
                            cout << string(25, '-') << endl;
                            vector<string> tRoomsID;
                            cout << "Choose Room ID from above and 0 when done." << endl;
                            string newRoomID;
                            while(true){
                                cout << "> ";
                                cin >> newRoomID;
                                if(newRoomID == "0"){
                                    break;
                                }
                                for(string &rId : roomsID){
                                    if(newRoomID == rId){
                                        tRoomsID.push_back(newRoomID);
                                    }
                                }
                            }
                            if(confirm()){
                                for(string &rId : tRoomsID){
                                    e.roomsId.push_back(rId);
                                    
                                    for(Room &r : rooms){
                                        if(r.id == rId){
                                            for(int i = 0; i < r.capacity; ++i){
                                                Seat newSeat;
                                                newSeat.roomId = r.id;
                                                newSeat.seatNumber = "S" + to_string(i);
                                                newSeat.isAvailable = true;
                                                e.seats.push_back(newSeat);
                                            }
                                            break;
                                        }
                                    }
                                    clear();
                                    cout << string(25, '-') << endl;
                                    cout << "New Room is Added to the exam." << endl;
                                }
                            }
                            else {
                                clear();
                                cout << string(25, '-') << endl;
                                cout << "Operation Canceled" << endl;
                            }
                        }
                        else if(choice == "2"){
                            clear();
                            cout << string(25, '-') << endl;
                            
                            if(e.roomsId.size() == 0){
                                cout << "There are no room in this exam to remove." << endl;
                                continue;
                            }
                            cout << "Rooms In this Exam" << endl;
                            cout << string(25, '-') << endl;
                            cout << left << setw(8) << "ID" << setw(10) << "Location" << setw(10) << "Capacity" << endl;
                            for(Room &r : rooms){
                                for(string &rId : e.roomsId){
                                    if(rId == r.id){
                                        cout << setw(8) << r.id << setw(10) << r.location << setw(10) << r.capacity << endl;
                                    }
                                }
                            }
                            cout << string(25, '-') << endl;
                            vector<string> tRoomsID;
                            cout << "Choose Room ID to remove and 0 when done." << endl;
                            while(true){
                                string newRoomID;
                                cout << "> ";
                                cin >> newRoomID;
                                if(newRoomID == "0"){
                                    break;
                                }
                                for(string &rId : e.roomsId){
                                    if(newRoomID == rId){
                                        tRoomsID.push_back(newRoomID);
                                    }
                                }
                            }
                            if(confirm()){
                                for(string &rId : tRoomsID){
                                    for(int i = 0; i < e.roomsId.size(); ++i){
                                        if(rId == e.roomsId[i]){
                                            e.roomsId.erase(e.roomsId.begin() + i);
                                            break;
                                        }
                                    }
                                    for(int i = 0; i < e.seats.size(); ++i){
                                        if(rId == e.seats[i].roomId){
                                            e.seats.erase(e.seats.begin() + i);
                                            i--;
                                        }
                                    }
                                }
                                clear();
                                cout << string(25, '-') << endl;
                                cout << "Selected Rooms are removed from the exam Successfully." << endl;
                            }
                            else {
                                clear();
                                cout << string(25, '-') << endl;
                                cout << "Operation canceled." << endl;
                            }
                        }
                        else if(choice == "0"){
                            clear();
                            break;
                        }
                        else {
                            clear();
                            cout << string(25, '-') << endl;
                            cout << "Invalid Input." << endl;
                        }
                    }
                }
                else if(choice == "0"){
                    clear();
                    break;
                }
                else {
                    clear();
                    cout << string(25, '-') << endl;
                    cout << "Invalid Input." << endl;
                }
            }
        }
    }
    if(!found){
        clear();
        cout << string(25, '-') << endl;
        cout << "Exam With That ID doesnt exist." << endl;
    }
}

void allocateSeat(){
    clear();
    cout << string(25, '-') << endl;
    cout << "EXAM SEAT ALLOCATION" << endl;
    cout << string(25, '-') << endl;
    if(exams.size() == 0){
        clear();
        cout << string(25, '-') << endl;
        cout << "There Are No Exams" << endl;       
        return; 
    }
    cout << "Available Exams" << endl;
    cout << string(25, '-') << endl;
    cout << left << setw(10) << "ExamID" << setw(10) << "Course" << endl;
    for(Exam &e : exams){
        cout << setw(10) << e.examId <<setw(15);
        for(Course &c : courses){
            if(c.id == e.courseId){
                cout << c.name ;
                break;
            }
        }
        cout << endl;
    }
    cout << string(25, '-') << endl;
    cout << "Choose Exam ID: ";
    string tExamId;
    cin >> tExamId;

    if(tExamId == "0"){
        clear();
        cout << string(25, '-') << endl;
        cout << "Operation canceled." << endl;
        return;
    }

    bool found = false;
    for(Exam &e : exams){
        if(e.examId == tExamId){
            found = true;
            clear();
            while(true){
                string choice;
                cout << string(25, '-') << endl;
                cout << "EXAM SEAT ALLOCATION" << endl;
                cout << string(25, '-') << endl;
                cout << "1 - Allocate Seat" << endl;
                cout << "2 - Tickets for this Exam" << endl;
                cout << "0 - Back" << endl;
                cout << string(25, '-') << endl;
                cout << "> ";
                cin >> choice;
                if(choice == "1"){
                    if(e.assigned){
                        clear();
                        cout << string(25, '-') << endl;
                        cout << "Seat For this exam are already allocated." << endl;
                        continue;
                    }
                    int numStudent = 0;
                    for(Student &s : students){
                        bool found = false;

                        for(string &cId : s.coursesId){
                            if(cId == e.courseId){
                                found = true;
                                break;
                            }
                        }
                        if(found){
                            numStudent++;
                        }
                    }
                    int numRoomSeat = 0;
                    for(Room &r : rooms){
                        bool found1 = false;

                        for(string &rId : e.roomsId){
                            if(r.id == rId){
                                found1 = true;
                                break;
                            }
                        }
                        if(found1){
                            numRoomSeat += r.capacity;
                        }

                    }

                    if(numStudent > numRoomSeat){
                        clear();
                        cout << string(25, '-') << endl;
                        cout << "There are no Enough rooms for students. Add Rooms" << endl;
                        continue;
                    }
                    if(!confirm()){
                        continue;
                    }
                    for(Student &st : students) {
                        for(string &cId : st.coursesId){
                            if(e.courseId == cId){
                                for(Seat &s : e.seats){
                                    if(s.isAvailable){
                                        Ticket newTicket;
                                        newTicket.examId = e.examId;
                                        newTicket.roomId = s.roomId;
                                        newTicket.seatNumber = s.seatNumber;
                                        newTicket.studentId = st.id;
                                        newTicket.time = e.time;
                                        newTicket.courseId = e.courseId;
                                        tickets.push_back(newTicket);
                                        s.isAvailable = false;
                                        s.studentId = st.id;
                                        break;
                                    }
                                }

                            }
                        }
                    }
                    e.assigned = true;

                    clear();
                    cout << string(25, '-') << endl;
                    cout << "Seat are Allocated SuccessFully" << endl;
                    
                }
                else if(choice == "2"){
                    clear();
                    cout << string(25, '-') << endl;
                    if(!e.assigned){                        
                        cout << "Seats are not assigned yet" << endl;
                        continue;
                    }
                    cout << "ALL TICKETS FOR THIS EXAM" << endl;
                    cout << string(25, '-') << endl;
                    cout << string(90, '-') << endl;
                    cout << left << setw(25) << "| Student" << setw(15) << "| Time" << setw(30) << "| Course" << setw(10) << "| RoomNo." << setw(10) << "| SeatNo.|" << endl;
                    cout << string(90, '-') << endl;
                    for(Ticket &t : tickets){
                        cout << left;
                        if(t.examId == e.examId){
                            for(Student &s : students){
                                if(s.id == t.studentId){
                                    string name = s.fName + " " + s.lName;
                                    cout << "| " << setw(23) << name;
                                    break;
                                }
                            }
                            cout << "| " << setw(13) << t.time;
                            for(Course &c : courses){
                                if(c.id == e.courseId){
                                    cout << "| " << setw(28) << c.name;
                                }
                            }
                            cout << "|" << right << setw(9) << t.roomId << left << "|" << right << setw(8) << t.seatNumber << "|" << endl;
                        }
                    }
                    cout << string(90, '-') << endl;
                    toContinue();
                    continue;
                }
                else if(choice == "0"){
                    clear();
                    break;
                }
                else {
                    clear();
                    cout << string(25, '-') << endl;
                    cout << "Invalid Input." << endl;
                    continue;
                }
            }
            
        }
    }
    if(!found){
        clear();
        cout << "Exam with that ID doesnt exist" << endl;
    }
}

void manageCourse(){
    clear();
    while(true){
        string choice;
        cout << string(25, '-') << endl;
        cout << "MANAGE COURSES" << endl;
        cout << string(25, '-') << endl;
        cout << "1 - Add Courses" << endl;
        cout << "2 - View Courses" << endl;
        cout << "3 - Update Courses" << endl;
        cout << "0 - Back" << endl;
        cout << string(25, '-') << endl;
        cout << "> ";
        cin >> choice;

        if(choice == "1"){
            addCourse();
        }
        else if(choice == "2"){
            clear();
            listCourses();
        }
        else if(choice == "3"){
            updateCourse();
        }
        else if(choice == "0"){
            clear();
            break;
        }
        else {
            clear();
            cout << "Invalid Input" << endl;
        }

    }
}
void manageRoom(){
    clear();
    while(true){
        string choice;
        cout << string(25, '-') << endl;
        cout << "MANAGE ROOM" << endl;
        cout << string(25, '-') << endl;
        cout << "1 - Add Room" << endl;
        cout << "2 - View Rooms" << endl;
        cout << "3 - Update Rooms" << endl;
        cout << "0 - Back" << endl;
        cout << string(25, '-') << endl;
        cout << "> ";
        cin >> choice;

        if(choice == "1"){
            addRoom();
        }
        else if(choice == "2"){
            listRooms();
        }
        else if(choice == "3"){
            updateRoom();
        }
        else if(choice == "0"){
            clear();
            break;
        }
        else {
            clear();
            cout << "Invalid Input" << endl;
        }

    } 
}
void manageStudent(){
    clear();
    while(true){
        string choice;
        cout << string(25, '-') << endl;
        cout << "MANAGE STUDENTS" << endl;
        cout << string(25, '-') << endl;
        cout << "1 - Register Student" << endl;
        cout << "2 - View Students" << endl;
        cout << "3 - Update Student Info" << endl;
        cout << "0 - Back" << endl;
        cout << string(25, '-') << endl;
        cout << "> ";
        cin >> choice;

        if(choice == "1"){
            addStudent();
        }
        else if(choice == "2"){
            clear();
            viewStudents();
        }
        else if(choice == "3"){
            updateStudent();
        }
        else if(choice == "0"){
            clear();
            break;
        }
        else {
            clear();
            cout << "Invalid Input" << endl;
        }

    } 
}
void manageExam(){
    clear();
    while(true){
        string choice;
        cout << string(25, '-') << endl;
        cout << "MANAGE EXAM SCHEDULE" << endl;
        cout << string(25, '-') << endl;
        cout << "1 - Add Exam" << endl;
        cout << "2 - View Exam" << endl;
        cout << "3 - Update Exam" << endl;
        cout << "0 - Back" << endl;
        cout << string(25, '-') << endl;
        cout << "> ";
        cin >> choice;

        if(choice == "1"){
            addExam();
        }
        else if(choice == "2"){
            viewExam();
        }
        else if(choice == "3"){
            updateExam();
        }
        else if(choice == "0"){
            clear();
            break;
        }
        else {
            clear();
            cout << "Invalid Input" << endl;
        }

    } 
}


void studentPortal(string userID){
    bool foundStudent = false;
    bool foundTicket = false;
    for(Student &s : students){
        if(s.id == userID){
            foundStudent = true;
            clear();
            cout << string(25, '-') << endl;
            cout << "EXAM SEAT ALLOCATION PORTAL" << endl;
            cout << string(25, '-') << endl;
            cout << "Student Name: " << s.fName << " " << s.lName << endl;
            cout << "Student ID: " << s.id << endl; 
            cout << string(25, '-') << endl;
            cout << string(61, '-') << endl;
            cout << left << setw(15) << "| Date" << setw(25) << "| Courses" << setw(10) << "| RoomID" << setw(10) << "| SeatNo." << "|" <<endl; 
            cout << string(61, '-') << endl;
            for(Ticket &t : tickets){
                if(t.studentId == s.id){
                    foundTicket = true;
                    
                    cout << "| " << setw(13) << t.time ;
                    for(Course &c : courses){
                        if(t.courseId == c.id){
                            cout << "| " << setw(23) << c.name;
                            break;
                        }
                    }
                    cout << "| " << setw(8) << t.roomId << "| " << setw(8) << t.seatNumber << "|" << endl;

                    cout << string(61, '-') << endl;
                }
            }
        }
    }

    if(!foundStudent){
        clear();
        cout << string(25, '-') << endl;
        cout << "Invalid ID." << endl;
    }else if(!foundTicket){
        clear();
        cout << string(25, '-') << endl;
        cout << "You are not placed for any exam." << endl;
    }
    else toContinue();
    


}


int main(){

    Course course1;
    course1.id = "Ma";
    course1.name = "Maths";
    courses.push_back(course1);
    Course course2;
    course2.id = "Gl";
    course2.name = "Global";
    courses.push_back(course2);

    Student student1;
    student1.fName = "Moti";
    student1.lName = "Umeta";
    student1.id = "1054";
    student1.coursesId.push_back("Ma");
    student1.coursesId.push_back("Gl");

    //students.push_back(student1);

    Room room1;
    room1.id = "R1";
    room1.location = "B59";
    room1.capacity = 25;
    rooms.push_back(room1);
    Room room2;
    room2.id = "R2";
    room2.location = "B58";
    room2.capacity = 50;
    rooms.push_back(room2);
    Student student2;
student2.fName = "Abel";
student2.lName = "Tadesse";
student2.id = "1055";
student2.coursesId.push_back("Ma");

Student student3;
student3.fName = "Sara";
student3.lName = "Bekele";
student3.id = "1056";
student3.coursesId.push_back("Ma");

Student student4;
student4.fName = "Dawit";
student4.lName = "Kebede";
student4.id = "1057";
student4.coursesId.push_back("Ma");

Student student5;
student5.fName = "Hana";
student5.lName = "Mekonnen";
student5.id = "1058";
student5.coursesId.push_back("Ma");

Student student6;
student6.fName = "Samuel";
student6.lName = "Getachew";
student6.id = "1059";
student6.coursesId.push_back("Ma");

Student student7;
student7.fName = "Liya";
student7.lName = "Tesfaye";
student7.id = "1060";
student7.coursesId.push_back("Ma");

Student student8;
student8.fName = "Yonatan";
student8.lName = "Assefa";
student8.id = "1061";
student8.coursesId.push_back("Ma");

Student student9;
student9.fName = "Meron";
student9.lName = "Haile";
student9.id = "1062";
student9.coursesId.push_back("Ma");

Student student10;
student10.fName = "Nahom";
student10.lName = "Wolde";
student10.id = "1063";
student10.coursesId.push_back("Ma");

Student student11;
student11.fName = "Selam";
student11.lName = "Abate";
student11.id = "1064";
student11.coursesId.push_back("Ma");

Student student12;
student12.fName = "Yosef";
student12.lName = "Demissie";
student12.id = "1065";
student12.coursesId.push_back("Ma");

Student student13;
student13.fName = "Bethel";
student13.lName = "Fikru";
student13.id = "1066";
student13.coursesId.push_back("Ma");

Student student14;
student14.fName = "Henok";
student14.lName = "Tilahun";
student14.id = "1067";
student14.coursesId.push_back("Ma");

Student student15;
student15.fName = "Rahel";
student15.lName = "Kassa";
student15.id = "1068";
student15.coursesId.push_back("Ma");

Student student16;
student16.fName = "Eyob";
student16.lName = "Alemu";
student16.id = "1069";
student16.coursesId.push_back("Ma");

Student student17;
student17.fName = "Saron";
student17.lName = "Mulatu";
student17.id = "1070";
student17.coursesId.push_back("Ma");

Student student18;
student18.fName = "Kalkidan";
student18.lName = "Hailu";
student18.id = "1071";
student18.coursesId.push_back("Ma");

Student student19;
student19.fName = "Biruk";
student19.lName = "Girma";
student19.id = "1072";
student19.coursesId.push_back("Ma");

Student student20;
student20.fName = "Meklit";
student20.lName = "Worku";
student20.id = "1073";
student20.coursesId.push_back("Ma");

Student student21;
student21.fName = "Tewodros";
student21.lName = "Shiferaw";
student21.id = "1074";
student21.coursesId.push_back("Ma");
students.push_back(student1);
students.push_back(student2);
students.push_back(student3);
students.push_back(student4);
students.push_back(student5);
students.push_back(student6);
students.push_back(student7);
students.push_back(student8);
students.push_back(student9);
students.push_back(student10);
students.push_back(student11);
students.push_back(student12);
students.push_back(student13);
students.push_back(student14);
students.push_back(student15);
students.push_back(student16);
students.push_back(student17);
students.push_back(student18);
students.push_back(student19);
students.push_back(student20);
students.push_back(student21);

    while(true){
        cout << string(25, '-') << endl;
        cout << "EXAM SEAT ALLOCATION PORTAL" << endl;
        cout << string(25, '-') << endl;
        string userID;
        cout << "Enter Your ID: ";
        cin >> userID;
        if(userID == "0987"){
            clear();
            while(true){
                string choice;
                cout << string(25, '-') << endl;
                cout << "EXAM SEAT ALLOCATION SYSTEM" << endl;
                cout << string(25, '-') << endl;
                cout << "1 - Manage Courses" << endl;
                cout << "2 - Manage Rooms" << endl;
                cout << "3 - Manage Students" << endl;
                cout << "4 - Manage Exam" << endl;
                cout << "5 - Manage Allocation" << endl;
                cout << "0 - Back" << endl;
                cout << string(25, '-') << endl;
                cout << "> ";
                cin >> choice;

                if(choice == "1"){
                    manageCourse();
                }
                else if(choice == "2"){
                    manageRoom();
                }
                else if(choice == "3"){
                    manageStudent();
                }
                else if(choice == "4"){
                    manageExam();
                }
                else if(choice == "5"){
                    allocateSeat();
                }        
                else if(choice == "0"){
                    clear();
                    break;
                }
                else {
                    clear();
                    cout << "Invalid Input." << endl;
                }
            }
        }
        else {
            studentPortal(userID);
        }
    }
    return 0;
}