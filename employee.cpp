#include <iostream>
#include <cstring>
#include <fstream>
#include <limits>
using namespace std;

#define MAX_NAME 30
#define MAX_DESIGNATION 30

string filename = "employeeNode.txt";

// Structure to hold employee data
struct EmpData {
    int empNo;                         // Employee number
    char empName[MAX_NAME];            // Employee name
    char designation[MAX_DESIGNATION]; // Employee designation
};

// Structure for the linked list node
struct Nodetype {
    EmpData info;                      // Employee data
    Nodetype* next;                    // Pointer to the next node in the list
};

// Function prototypes
// void Initialize(Nodetype*& plist);
Nodetype* GetNode();
void FreeNode(Nodetype* p);
Nodetype* CreateList(Nodetype* plist, int n);
void Traverse(Nodetype* plist);
int CountNode(Nodetype* plist);
void SearchNode(Nodetype* plist);
Nodetype* InsertNode(Nodetype* plist);
Nodetype* DeleteNode(Nodetype* plist);
void Sort(Nodetype* plist);
void LoadFromFile(Nodetype*& plist);
void SaveToFile(Nodetype* plist);
void FreeList(Nodetype* plist);

// Initialize the list to null
// void Initialize(Nodetype*& plist) {
//     plist = nullptr;
// }

// Create a new node and return its pointer
Nodetype* GetNode() {
    Nodetype* p = new Nodetype();
    p->next = nullptr;
    return p;
}

// Free the memory allocated for a node
void FreeNode(Nodetype* p) {
    delete p;
}

void SaveToFileDelete(Nodetype* plist) {
    
    ofstream file(filename,ios::trunc);
    
    if (!file) {
    cout << "Error opening file for writing!" << endl;
    return ;
    // Handle the error as needed
}
    Nodetype* ptr = plist;

    while (ptr != nullptr) {
        file << ptr->info.empNo << endl;
        file << ptr->info.empName << endl;
        file << ptr->info.designation << endl;
        ptr = ptr->next;
    }

    file.close();
    cout << " \t + Employee data saved to file!" << endl << endl;
}


// Save the list to a file
void SaveToFile(Nodetype* plist) {
    
    ofstream file(filename);
    
    if (!file) {
    cout << "Error opening file for writing!" << endl;
    // Handle the error as needed
}
    Nodetype* ptr = plist;

    while (ptr != nullptr) {
        file << ptr->info.empNo << endl;
        file << ptr->info.empName << endl;
        file << ptr->info.designation << endl;
        ptr = ptr->next;
    }

    file.close();
    cout << " \t + Employee data saved to file!" << endl << endl;
}


void SaveToFile1(Nodetype* plist) {
    
    ofstream file(filename,ios::app);
    
    if (!file) {
    cout << "Error opening file for writing!" << endl;
    // Handle the error as needed
}
    Nodetype* ptr = plist;

    while (ptr != nullptr) {
        file << ptr->info.empNo << endl;
        file << ptr->info.empName << endl;
        file << ptr->info.designation << endl;
        ptr = ptr->next;
    }

    file.close();
    cout << " \t + Employee data saved to file!" << endl << endl;
}



// check if the employee number is duplicate
bool IsDuplicate(Nodetype* plist, int empNo) {
    Nodetype* temp = plist;
    while (temp != nullptr) {
        if (temp->info.empNo == empNo) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Create a list of employees
Nodetype* CreateList(Nodetype* plist, int n) {
    plist = nullptr;

    Nodetype* p;
    Nodetype* ptr;
    int empNo;
    char name[MAX_NAME];
    char designation[MAX_DESIGNATION];

    for (int i = 0; i < n; ++i) {
        // Get employee details from user
        bool validInput = false;

        while (!validInput) {
            cout << "\n \t -> Enter the employee number: ";
            cin >> empNo;

           if (cin.fail()) {
                cout << " \t [Error] Invalid input. Please enter a valid employee number (integer).\n";
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input

            } else if (IsDuplicate(plist, empNo)) {
                cout << " \t [Error] Employee number already exists. Please enter a different employee number.\n";

            } else {
                validInput = true;
            }
        }

        cout << " \t -> Enter the employee name: ";
        cin.ignore(); // To clear the newline character from the input buffer
        cin.getline(name, MAX_NAME);

        cout << " \t -> Enter the employee designation: ";
        cin.getline(designation, MAX_DESIGNATION);

        // Create a new node
        p = GetNode();
        p->info.empNo = empNo;
        strcpy(p->info.empName, name);
        strcpy(p->info.designation, designation);

        // Insert the node into the list
        if (plist == nullptr) {
            plist = p;
        } else {
            ptr = plist;
            while (ptr->next != nullptr) {
                ptr = ptr->next;
            }
            ptr->next = p;
        }
    }

    // Call function to save the list to a file
    SaveToFile1(plist);

    cout << "\n \t -> Linked List created successfully!" << endl << endl;

    return plist;
}





// Load the list from a file
void LoadFromFile(Nodetype*& plist) {
    ifstream file(filename, ios::in);
    if (!file) {
        cout << " \t + No existing file found, starting with an empty list." << endl;
        return;
    }

    FreeList(plist);
    Nodetype* ptr = nullptr;
    Nodetype* temp = nullptr;

    while (!file.eof()) {
        temp = GetNode();
        file >> temp->info.empNo;
        file.ignore(); //clear buffer after reading integer and before reading string
        file.getline(temp->info.empName, MAX_NAME);
        file.getline(temp->info.designation, MAX_DESIGNATION);

        if (!file.fail()) {
            if (plist == nullptr) {
                plist = temp;
            } else {
                ptr = plist;
                while (ptr->next != nullptr) {
                    ptr = ptr->next;
                }
                ptr->next = temp;
            }
        }
    }

    file.close();
    cout << " \t + Employee data loaded from file!" << endl << endl;
}


void Traverse(Nodetype* plist) {
    
    Nodetype* ptr = plist;

    if (ptr == nullptr) {
        cout << endl << " \t + Linked list is empty" << endl << endl;
    } else {
        cout << endl;
        cout << " \t Show all elements from list: " << endl;
        while (ptr != nullptr) {
            cout << "Employee No: " << ptr->info.empNo << ", ";
            cout << "Name: " << ptr->info.empName << ", ";
            cout << "Designation: " << ptr->info.designation << endl;

            ptr = ptr->next;
        }
        cout << endl << endl;
    }
}


// Count the number of nodes in the list
int CountNode(Nodetype* plist) {
    Nodetype* p = plist;
    int count = 0;

    while (p != nullptr) {
        ++count;
        p = p->next;
    }

    return count;
}

void SearchNode(Nodetype* plist) {
    int empNo;
    string name;
    bool isFound = false;
    int option;

    cout << "1. Search by Employee Number\n";
    cout << "2. Search by Name\n";
    cout << "Enter your choice: ";
    cin >> option;
    cin.ignore(); // To ignore the newline left in the input buffer

    if (option == 1) {
        cout << "\n \t Enter the employee number to be searched: ";
        cin >> empNo;

        Nodetype* p = plist;
        while (p != nullptr) {
            if (p->info.empNo == empNo) {
                cout << "\n \t -> Employee found!" << endl;
                cout << "Employee No: " << p->info.empNo << ", ";
                cout << "Name: " << p->info.empName << ", ";
                cout << "Designation: " << p->info.designation << endl;
                isFound = true;
                break;
            }
            p = p->next;
        }
    } else if (option == 2) {
        cout << "\n \t Enter the employee name to be searched: ";
        getline(cin, name);

        Nodetype* p = plist;
        while (p != nullptr) {
            if (name == p->info.empName) {
                cout << "\n \t -> Employee found!" << endl;
                cout << "Employee No: " << p->info.empNo << ", ";
                cout << "Name: " << p->info.empName << ", ";
                cout << "Designation: " << p->info.designation << endl;
                isFound = true;
                break;
            }
            p = p->next;
        }
    } else {
        cout << " \t + Invalid option!" << endl;
    }

    if (!isFound) {
        cout << " \t + Employee not found!" << endl << endl;
    }
}



// Insert a node into the list
Nodetype* InsertNode(Nodetype* plist) {
    Nodetype* p;
    Nodetype* ptr;
    char ch;
    int pos;
    int empNo;
    char name[MAX_NAME];
    char designation[MAX_DESIGNATION];
    bool validInput = false;

    // Get employee details from user
        while (!validInput) {
            cout << "\n \t -> Enter the employee number: ";
            cin >> empNo;

           if (cin.fail()) {
                cout << " \t [Error] Invalid input. Please enter a valid employee number (integer).\n";
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input

            } else if (IsDuplicate(plist, empNo)) {
                cout << " \t [Error] Employee number already exists. Please enter a different employee number.\n";

            } else {
                validInput = true;
            }
        }

    cout << " \t Enter the employee name: "; cin.ignore(); cin.getline(name, MAX_NAME);
    cout << " \t Enter the employee designation: "; cin.getline(designation, MAX_DESIGNATION);

    p = GetNode();
    p->info.empNo = empNo;
    strcpy(p->info.empName, name);
    strcpy(p->info.designation, designation);

    // Insert the node at the specified position
    if (plist == nullptr) {
        plist = p;
    } else {
        cout << "======================================================" << endl;
        cout << "\n \t Where do you want to insert the employee? ";
        cout << "\n\t\t1. At the beginning ";
        cout << "\n\t\t2. At the end ";
        cout << "\n\t\t3. Position after node ptr* ";
        cout << "\n\t\t\t -> Please choose one(1,2,3): "; cin >> ch;

        switch (ch) {
            case '1':
                p->next = plist;
                plist = p;
                cout << " \t + An employee has been inserted at the beginning of the list!" << endl << endl;
                break;
            case '2':
                ptr = plist;
                while (ptr->next != nullptr) {
                    ptr = ptr->next;
                }
                ptr->next = p;
                cout << " \t + An employee has been inserted at the end of the list!" << endl << endl;
                break;
            case '3':
                cout << " \t Enter the position to be inserted: "; cin >> pos;
                ptr = plist;
                for (int i = 1; i < pos - 1; ++i) {
                    if (ptr != nullptr) {
                        ptr = ptr->next;
                    }
                }
                if (ptr != nullptr) {
                    p->next = ptr->next;
                    ptr->next = p;
                    cout << " \t + An employee has been inserted to the list!" << endl << endl;
                } else {
                    cout << " \t + Invalid position!" << endl << endl;
                }
                break;
            default:
                cout << " \t + Invalid choice!" << endl << endl;
                break;
        }
    }
    SaveToFile(plist);

    return plist;
}

// Delete a node from the list
Nodetype* DeleteNode(Nodetype* plist) {
    
    Nodetype* p;
    Nodetype* temp;
    int empNo;
    bool isFound = false;

    if (plist != nullptr) {

           bool validInput = false;
           while (!validInput) {
            cout << "\n \t -> Enter the employee number you want to delete: ";
            cin >> empNo;

           if (cin.fail()) {
                cout << " \t [Error] Invalid input. Please enter a valid employee number (integer).\n";
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input

            }  else {
                validInput = true;
            }
        }

        p = plist;
        if (p->info.empNo == empNo) {
            plist = p->next;
            FreeNode(p);
            cout << " \t + Deleted node at the beginning!" << endl << endl;
            isFound = true;
        } else {
            while (p->next != nullptr && p->next->info.empNo != empNo) {
                p = p->next;
            }
            if (p->next != nullptr) {
                temp = p->next;
                p->next = temp->next;
                FreeNode(temp);
                cout << " \t + Deleted node with the specific employee number!" << endl << endl;
                isFound = true;
            }
        }

        if (!isFound) {
            cout << " \t + Unable to find the employee number to delete!" << endl << endl;
        }
    } else {
        cout << " \t + List is empty, employee can't be deleted!" << endl << endl;
    }
  
    SaveToFileDelete(plist);
    return plist;
}

// Sort the list by employee number
void Sort(Nodetype* plist, bool ascending = true) {
    if (plist != nullptr) {
        Nodetype* p;
        Nodetype* ptr;
        Nodetype* minOrMax;
        EmpData tempInfo;

        // Selection sort algorithm with the option for ascending or descending
        for (p = plist; p != nullptr; p = p->next) {
            minOrMax = p;
            for (ptr = p->next; ptr != nullptr; ptr = ptr->next) {
                // For ascending order
                if (ascending) {
                    if (ptr->info.empNo < minOrMax->info.empNo) {
                        minOrMax = ptr;
                    }
                }
                // For descending order
                else {
                    if (ptr->info.empNo > minOrMax->info.empNo) {
                        minOrMax = ptr;
                    }
                }
            }

            if (minOrMax != p) {
                // Swap employee data
                tempInfo = p->info;
                p->info = minOrMax->info;
                minOrMax->info = tempInfo;
            }
        }

        cout << " \t + List sorted by employee number in " 
             << (ascending ? "ascending" : "descending") << " order!" << endl << endl;
    } else {
        cout << " \t + List is empty, cannot sort!" << endl << endl;
    }
}

// Free the entire list
void FreeList(Nodetype* plist) {
    Nodetype* temp;
    while (plist != nullptr) {
        temp = plist;
        plist = plist->next;
        FreeNode(temp);
    }
}





void ShowMenu() {
    cout << "+=============================================+\n";
    cout << "|       Employee Management System       |\n";
    cout << "+=============================================+\n";
    cout << "| 1. Create the list of employees             |\n";
    cout << "| 2. Display all records                      |\n";
    cout << "| 3. Count the number of records              |\n";
    cout << "| 4. Search the records                       |\n";
    cout << "| 5. Insert a record                          |\n";
    cout << "|    5.1 At the beginning                     |\n";
    cout << "|    5.2 At the end                           |\n";
    cout << "|    5.3 At a specific position               |\n";
    cout << "| 6. Sort the records by employee number      |\n";
    cout << "| 7. Delete a record from the database        |\n";
    cout << "| 0. Exit                                     |\n";
    cout << "+=============================================+\n";
    cout << "Enter your option: ";
}



// Main function
int main() {

    Nodetype* plist = nullptr;

    LoadFromFile(plist);

    char ch;
    int n;

    do {
        
        ShowMenu();
        cin >> ch;

        system("cls"); // For Windows users
        // system("clear"); // For Linux users
        
        switch (ch) {
            case '1':
                // Create list of employees
                cout << " \t Enter number of elements: "; cin >> n;
                plist = CreateList(plist, n);
                break;
            case '2':
                // Traverse and display the list
                Traverse(plist);
                break;
            case '3':
                // Count the number of nodes in the list
                cout << endl << " \t Number of nodes = " << CountNode(plist) << endl << endl;
                break;
            case '4':
                // Search for an employee in the list
                SearchNode(plist);
                break;
            case '5':
                // Insert a new node into the list
                plist = InsertNode(plist);
                break;
            case '6':
                // Sort the list by employee number
                int n;
                cout << " \t Sort by employee number in ascending order (1) or descending order (2): ";
                cin >> n;
                if (n == 1) {
                    Sort(plist,true);
                } else if (n == 2) {
                    Sort(plist, false);
                } else {
                    cout << " \t + Invalid choice!" << endl;
                }
                
                break;
            case '7':
                // Delete a node from the list
                plist = DeleteNode(plist);
                break;
            case '0':
                // Exit the program
                cout << " \t Exiting..." << endl;
                break;
            default:
                // Invalid selection
                cout << " \t + Invalid selection! " << endl;
                break;
        }
    } while (ch != '0');

    // Free the entire list before exiting
    FreeList(plist);
    return 0;
}
