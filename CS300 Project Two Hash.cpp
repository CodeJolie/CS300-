#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;
};

class CourseHashTable {
private:
    unordered_map<string, Course> courseMap;

public:
    void loadCoursesFromFile(const string& filePath);
    Course* searchCourse(const string& courseNumber);
    void printCourseList();
    void printCourseInfo(const string& courseNumber);
};

void CourseHashTable::loadCoursesFromFile(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, title, prereq;

        getline(ss, courseNumber, ',');
        getline(ss, title, ',');

        Course course;
        course.courseNumber = courseNumber;
        course.title = title;

        while (getline(ss, prereq, ',')) {
            course.prerequisites.push_back(prereq);
        }

        courseMap[courseNumber] = course;
    }
    file.close();
}

Course* CourseHashTable::searchCourse(const string& courseNumber) {
    if (courseMap.find(courseNumber) != courseMap.end()) {
        return &courseMap[courseNumber];
    }
    return nullptr;
}

void CourseHashTable::printCourseList() {
    for (const auto& pair : courseMap) {
        cout << pair.second.courseNumber << ", " << pair.second.title << endl;
    }
}

void CourseHashTable::printCourseInfo(const string& courseNumber) {
    Course* course = searchCourse(courseNumber);
    if (course) {
        cout << "Course Number: " << course->courseNumber << endl;
        cout << "Title: " << course->title << endl;
        if (!course->prerequisites.empty()) {
            cout << "Prerequisites: ";
            for (const string& prereq : course->prerequisites) {
                cout << prereq << " ";
            }
            cout << endl;
        } else {
            cout << "No prerequisites" << endl;
        }
    } else {
        cout << "Course not found." << endl;
    }
}

int main() {
    CourseHashTable courseTable;
    string filePath = "U:\\CS 300 ABCU_Advising_Program_Input.csv";  // Update with your actual CSV file path
    courseTable.loadCoursesFromFile(filePath);

    int choice = 0;
    while (choice != 3) {
        cout << "Menu:" << endl;
        cout << "1. Print Course List" << endl;
        cout << "2. Print Course Information" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                courseTable.printCourseList();
                break;
            case 2: {
                string courseNumber;
                cout << "Enter course number: ";
                cin >> courseNumber;
                courseTable.printCourseInfo(courseNumber);
                break;
            }
            case 3:
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}
