#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits> // For numeric_limits

// Student class definition
class Student {
private:
    std::string name;
    std::vector<int> grades;

public:
    // Constructor to initialize name and grades
    Student(std::string name, std::vector<int> grades)
        : name(name), grades(grades) {}

    // Getters for name and grades
    const std::string& getName() const {
        return name;
    }

    const std::vector<int>& getGrades() const {
        return grades;
    }

    // Mark getAverage as a const method since it doesn't modify the object
    double getAverage() const {
        double sum = 0;
        for (int grade : grades) {
            sum += grade;
        }
        return grades.empty() ? 0 : sum / grades.size();
    }
};

// Function to display student details
void viewStudents(const std::vector<Student>& students) {
    std::cout << "\nStudent List:\n";
    std::cout << std::setw(30) << "Name" << std::setw(20) << "Average" << std::endl;

    // Loop through each student and display their name and average
    for (const Student& student : students) {
        std::cout << std::setw(30) << student.getName()
                  << std::setw(20) << std::fixed << std::setprecision(2) << student.getAverage() << std::endl;
    }
}

// Function to sort students by average grade in descending order
void sortStudentsByAverage(std::vector<Student>& students) {
    std::sort(students.begin(), students.end(),
              [](const Student& a, const Student& b) {
                  return a.getAverage() > b.getAverage(); // Sort in descending order
              });
}

// Function to add a new student to the list
void addStudent(std::vector<Student>& students) {
    std::string name;
    int numGrades;

    std::cout << "\nEnter the student's name: ";
    std::cin.ignore(); // To clear the input buffer before getting the name
    std::getline(std::cin, name);

    std::cout << "Enter the number of grades: ";
    std::cin >> numGrades;

    // Validate the number of grades (must be a positive number)
    while (numGrades <= 0) {
        std::cout << "Please enter a valid number of grades (greater than 0): ";
        std::cin >> numGrades;
    }

    // Clear any leftover newline character in the buffer
    std::cin.ignore();

    std::vector<int> grades(numGrades);
    for (int i = 0; i < numGrades; ++i) {
        std::cout << "Enter grade " << (i + 1) << ": ";
        std::cin >> grades[i];

        // Validate the input grade (must be a valid integer)
        while (std::cin.fail() || grades[i] < 0 || grades[i] > 100) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore incorrect input
            std::cout << "Invalid input. Please enter a grade between 0 and 100: ";
            std::cin >> grades[i];
        }
    }

    students.push_back(Student(name, grades)); // Add student to list
}

// Main menu for the program
void showMenu() {
    std::cout << "\nStudent Grade Management System\n";
    std::cout << "1. View Students\n";
    std::cout << "2. Add Student\n";
    std::cout << "3. Sort Students by Average\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    std::vector<Student> students;
    int choice;

    do {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                viewStudents(students);
                break;
            case 2:
                addStudent(students);
                break;
            case 3:
                sortStudentsByAverage(students);
                std::cout << "\nStudents sorted by average grade.\n";
                break;
            case 4:
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
