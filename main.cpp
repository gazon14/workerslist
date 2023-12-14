#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int MAX_NAME_LENGTH = 50;

struct Worker {
    char name[MAX_NAME_LENGTH];
    int age;
    double salary;
    
    
    // Constructor for convenience
        Worker(const char* n, int a, double s) : age(a), salary(s) {
            strncpy(name, n, MAX_NAME_LENGTH);
            name[MAX_NAME_LENGTH - 1] = '\0';  // Ensure null-terminated
        }

        // Method to compare workers based on name
        static bool compareByName(const Worker& a, const Worker& b) {
            return strcmp(a.name, b.name) < 0;
        }

        // Method to compare workers based on age
        static bool compareByAge(const Worker& a, const Worker& b) {
            return a.age < b.age;
        }

        // Method to compare workers based on salary
        static bool compareBySalary(const Worker& a, const Worker& b) {
            return a.salary < b.salary;
        }
    };

    void sortWorkers(vector<Worker>& workers, function<bool(const Worker&, const Worker&)> comparator) {
        sort(workers.begin(), workers.end(), comparator);
    }


    
};


void addWorker(ofstream& outfile) {
    Worker newWorker;
    cout << "Enter worker name: ";
    cin.getline(newWorker.name, MAX_NAME_LENGTH);
    cout << "Enter worker age: ";
    cin >> newWorker.age;
    cout << "Enter worker salary: ";
    cin >> newWorker.salary;
    cin.ignore(); // Ignore the newline character after entering the salary
    outfile << newWorker.name << " " << newWorker.age << " " << newWorker.salary << endl;
    cout << "Worker added successfully!" << endl;
}



void removeWorker(ifstream& infile, ofstream& outfile) {
    char name[MAX_NAME_LENGTH];
    cout << "Enter the name of the worker to remove: ";
    cin.getline(name, MAX_NAME_LENGTH);
    bool found = false;
    Worker currentWorker;
    while (infile >> currentWorker.name >> currentWorker.age >> currentWorker.salary) {
        if (strcmp(currentWorker.name, name) == 0) {
            found = true;
        }
        else {
            outfile << currentWorker.name << " " << currentWorker.age << " " << currentWorker.salary << endl;
        }
    }
    infile.close();
    outfile.close();
    remove("database.txt");
    rename("temp.txt", "database.txt");
    if (found) {
        cout << "Worker removed successfully!" << endl;
    }
    else {
        cout << "Worker not found in the database!" << endl;
    }
}



void searchWorker(ifstream& infile) {
    char name[MAX_NAME_LENGTH];
    int age;
    double salary;
    cout << "Enter the name of the worker to search for: ";
    cin.getline(name, MAX_NAME_LENGTH);
    cout << "Enter the age of the worker to search for (-1 to skip): ";
    cin >> age;
    cout << "Enter the salary of the worker to search for (-1 to skip): ";
    cin >> salary;
    cin.ignore();
    bool found = false;
    Worker currentWorker;
    while (infile >> currentWorker.name >> currentWorker.age >> currentWorker.salary) {
        if ((name[0] == '\0' || strcmp(currentWorker.name, name) == 0) &&
            (age == -1 || currentWorker.age == age) &&
            (salary == -1 || currentWorker.salary == salary)) {
            cout << "Name: " << currentWorker.name << endl;
            cout << "Age: " << currentWorker.age << endl;
            cout << "Salary: " << currentWorker.salary << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Worker not found in the database!" << endl;
    }
}


void displayAllWorkers(ifstream& infile) {
    Worker currentWorker;
    while (infile >> currentWorker.name >> currentWorker.age >> currentWorker.salary) {
        cout << "Name: " << currentWorker.name << endl;
        cout << "Age: " << currentWorker.age << endl;
        cout << "Salary: " << currentWorker.salary << endl;
        cout << "---------------------" << endl;
    }
}



int main() {
    int choice;
    do {
        cout << "Select an option:" << endl;
        cout << "1. Add worker" << endl;
        cout << "2. Remove worker" << endl;
        cout << "3. Search worker" << endl;
        cout << "4. Display all workers" << endl;
        cout << "5. Exit" << endl;
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: {
                ofstream outfile("database.txt", ios::app);
                addWorker(outfile);
                outfile.close();
                break;
            }
            case 2: {
                ifstream infile("database.txt");
                ofstream outfile("temp.txt", ios::out);
                removeWorker(infile, outfile);
                infile.close();
                break;
            }
            case 3: {
                ifstream infile("database.txt");
                searchWorker(infile);
                infile.close();
                break;
            }
            case 4:{
                ifstream infile("database.txt");
                displayAllWorkers(infile);
                infile.close();
                break;
            }
                
            case 5: {
                cout << "Exiting program...";
                return 0;
            }
        }
    } while (1);
    
    return 0;
    
}

