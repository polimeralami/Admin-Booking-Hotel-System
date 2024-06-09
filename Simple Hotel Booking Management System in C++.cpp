#include <fstream>   // For file operations
#include <iostream>  // For input/output operations
#include <conio.h>   // For console input/output, _getch() function
#include <stdio.h>   // For standard input/output operations
#include <string.h>  // For string manipulation functions
#include <stdlib.h>  // For general purpose functions
#include <process.h> // For process control functions
#include <regex>     // For regular expression operations
#include <limits>    // For handling input stream limits

using namespace std;

// Function to display introductory message
void intro() {
    cout << "\n\t            ";
    cout << "     Hotel Booking Management System";
    cout << "\n====================================";
    cout << "====================================";
}

// Function to display header lines
void head() {
    cout << "\n====================================";
    cout << "====================================\n\n";
}

// Function to simulate connecting to server and syncing data
void time() {
    int i = 0;
    long long j;
    cout << "	\n\n\n	Connecting to Server\n 	Syncing Data";
    while (i < 10) {
        for (j = 5; j > 4; j++) {
            if (j == 99999) {
                cout << ".";
                break;
            }
        }
        ++i;
    }
}

// MARK:- Hotel Class Here =>
class hotel {
private:
    int room_no;      // Room number
    char name[30];    // Customer name
    char address[50]; // Customer address
    char phone[15];   // Customer phone number
    int days;         // Number of days of stay
    float fare;       // Total fare for the stay

public:
    void main_menu();        // to display the main menu
    void add();              // to book a room
    void display();          // to display the customer record
    void rooms();            // to display allotted rooms
    void edit();             // to edit the customer record
    int check(int);          // to check room status
    void modify(int);        // to modify the record
    void delete_rec(int);    // to delete the record
    void verify_password();  // to verify admin password
    void show_rooms();       // to show list of rooms
};

// Function to verify admin password
void hotel::verify_password() {
    system("cls");
    head();
    string pass; // Variable to store password
    int attempts = 0;
    const int maxAttempts = 3; // Maximum allowed attempts

    while (attempts < maxAttempts) {
        pass.clear(); // Clear previous password input
        cout << "\n\n\t\t\t\tpassword => ";
        char ch = _getch();  // Read password character by character
        while (ch != 13) {  // Character 13 is Enter
            pass.push_back(ch);  // Append character to password string
            cout << '*';  // Display asterisk for each character entered
            ch = _getch();  // Read next character
        }
        cout << endl;

        if (pass == "HBook#Admin821") {  // Correct password
            cout << "\n\n\t\t\t  !!!Verification Successful!!!";
            break;
        } else {  // Incorrect password
            attempts++;
            cout << "\n\n\t\t\t!!!Password is incorrect!!!";
            cout << "\n\t\t\tAttempt " << attempts << " of " << maxAttempts << "\n";
            if (attempts >= maxAttempts) {
                cout << "\n\n\t\t\tMaximum attempts reached. Exiting...";
                getch();
                exit(-1);  // Exit program
            }
            getch();
            system("cls");
            head();
        }
    }
}

// Function to display main menu
void hotel::main_menu() {
    int choice;  // Variable to store user choice
    while (true) {
        system("cls");
        head();
        cout << "\n\t\t\t\t*************";
        cout << "\n\t\t\t\t* MAIN MENU *";
        cout << "\n\t\t\t\t*************";
        cout << "\n\n\n\t\t\t1. Book A Room";
        cout << "\n\t\t\t2. Customer Record";
        cout << "\n\t\t\t3. Rooms Allotted";
        cout << "\n\t\t\t4. Edit Record";
        cout << "\n\t\t\t5. Exit";
        cout << "\n\n\t\t\tEnter Your Choice: ";
        cin >> choice; //Read user choice
        if (cin.fail() || choice < 1 || choice > 5) {  // Invalid input handling
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n\n\t\t\t!!! ERROR: Invalid choice. Please enter a number between 1 and 5: ";
        } else {
            switch (choice) {
            case 1:
                add(); //Book a room
                break;
            case 2:
                verify_password();  // Verify password before displaying customer record
                display();
                break;
            case 3:
                rooms();  // Display allotted rooms
                break;
            case 4:
                verify_password();  // Verify password before editing record
                edit();
                break;
            case 5:
                return;
            }
        }
    }
}

// Function to show the list of rooms
void hotel::show_rooms() {
    cout << "\n\t\t\t    List Of Rooms (1-10)";
    cout << "\n\t\t\t    --------------------";
    for (int i = 1; i <= 10; i++) {
        if (check(i)) {  // Check if room is occupied
            cout << "\n Room no: " << i << " is Occupied";
        } else {
            cout << "\n Room no: " << i << " is Available";
        }
    }
}

// Function to add a new booking
void hotel::add() {
    int r, flag;  // Variables for room number and check flag
    char temp_name[30], temp_address[50], temp_phone[15];  // Temporary variables for input
    int temp_days;
    float temp_fare;
    ofstream fout("Record.dat", ios::app | ios::binary);  // Open file for appending in binary mode

    while (true) {
        system("cls");
        head();
        show_rooms();  // Display list of rooms
        cout << "\n\n Enter Customer Details";
        cout << "\n ----------------------";
        cout << "\n\n Room no: ";
        cin >> r;  // Read room number
        if (cin.fail() || r < 1 || r > 10) {  // Invalid room number handling
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n !!! ERROR: Wrong Input, Please Enter A Number From 1-10 Only !!!\n";
            getch();
        } else {
            flag = check(r);  // Check if room is occupied
            if (flag) {
                cout << "\n Room Number " << r << " Is Occupied, Please Select Different Room Number\n";
                getch();
            } else {
                room_no = r;
                cin.ignore();  // Clear input buffer before using getline
                while (true) {
                    cout << "\n Name: ";
                    cin.getline(temp_name, 30);
                    if (regex_match(temp_name, regex("^[A-Za-z ]+$"))) {  // Validate name
                        strcpy(name, temp_name);
                        break;
                    } else {
                        cout << " !!! ERROR: Name must contain only alphabets. Please enter again.\n";
                    }
                }
                while (true) {
                    cout << " Address: ";
                    cin.getline(temp_address, 50);
                    if (regex_match(temp_address, regex("^[A-Za-z0-9 ,.]+$"))) {  // Validate address
                        strcpy(address, temp_address);
                        break;
                    } else {
                        cout << " !!! ERROR: Address must contain only alphabets, numbers, commas, and periods. Please enter again.\n";
                    }
                }
                while (true) {
                    cout << " Phone No: ";
                    cin.getline(temp_phone, 15);
                    if (regex_match(temp_phone, regex("^[0-9]+$"))) {  // Validate phone number
                        strcpy(phone, temp_phone);
                        break;
                    } else {
                        cout << " !!! ERROR: Phone number must contain only digits. Please enter again.\n";
                    }
                }
                while (true) {
                    cout << " No of Days to Checkout: ";
                    cin >> temp_days;
                    if (cin.fail() || temp_days <= 0) {  // Invalid days handling
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << " !!! ERROR: Number of days must be a positive integer. Please enter again.\n";
                    } else {
                        days = temp_days;
                        break;
                    }
                }
                fare = days * 20;  // Calculate fare
                fout.write(reinterpret_cast<char*>(this), sizeof(hotel));  // Write record to file
                cout << "\n Room is booked...!!!";
                fout.close(); //Close file
                break;
            }
        }
    }
    cout << "\n Press any key to continue.....!!";
    getch();
}

// Function to display customer record
void hotel::display() {
    system("cls");
    head();
    show_rooms();

    ifstream fin("Record.dat", ios::in | ios::binary);  // Open file for reading in binary mode
    int occupiedCount = 0;
    while (fin.read(reinterpret_cast<char*>(this), sizeof(hotel))) {  // Read records from file
        occupiedCount++;
    }
    fin.close();

    if (occupiedCount == 0) {
        cout << "\n\n No rooms are currently occupied.";
        cout << "\n\n Press any key to go back to the main menu....!!";
        getch();
        return;
    }

    int r, flag;
    while (true) {
        cout << "\n\n Enter room no: ";
        cin >> r;
        if (cin.fail() || r < 1 || r > 10) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //To avoid the message displayed first before user input
            cout << " !!! ERROR: Please enter a valid room number between 1 and 10: ";
        } else {
            flag = 0;
            fin.open("Record.dat", ios::in | ios::binary);  // Open file for reading in binary mode
            while (fin.read(reinterpret_cast<char*>(this), sizeof(hotel))) { //Read records from file to assign to the variable
                if (room_no == r) {
                    head();
                    cout << "\n Customer Details";
                    cout << "\n ----------------";
                    cout << "\n\n Room no: " << room_no;
                    cout << "\n Name: " << name;
                    cout << "\n Address: " << address;
                    cout << "\n Phone no: " << phone;
                    cout << "\n Days: " << days;
                    cout << "\n Total Fare: " << fare;
                    flag = 1;
                    break;
                }
            }
            fin.close();

            if (flag == 0) {
                cout << "\n Sorry Room no. " << r << " not found or vacant....!!";
            } else {
                break;
            }
        }
    }
    cout << "\n\n Press any key to continue....!!";
    getch();
}

// Function to display list of rooms
void hotel::rooms() {
    system("cls");
    head();
    ifstream fin("Record.dat", ios::in | ios::binary);  // Open file for reading in binary mode
    cout << "\n\t\t\t    List Of Rooms Allotted";
    cout << "\n\t\t\t    ----------------------";
    while (fin.read(reinterpret_cast<char*>(this), sizeof(hotel))) { //Read records from file to assign to the variable
        cout << "\n Room no: " << room_no << "\n Name: " << name;
        cout << "\n Days: " << days;
        cout << "\n**********************************";
    }
    cout << "\n\n\n\t\t\tPress any key to continue.....!!";
    getch();
    fin.close();
}

// Function to edit a record
void hotel::edit() {
    int choice;

    while (true) {
        system("cls");
        head();
        cout << "\n EDIT MENU";
        cout << "\n ---------";
        cout << "\n\n 1. Modify Customer Record";
        cout << "\n 2. Delete Customer Record";
        cout << "\n 3. Back to Main Menu";
        cout << "\n Enter your choice: ";
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > 3) {  // Invalid input handling
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << " !!! ERROR: Please enter a valid choice (1, 2 or 3): ";
        } else if (choice == 3) {
            return; // Return to main menu
        } else {
            system("cls");
            head();
            show_rooms();

            ifstream fin("Record.dat", ios::in | ios::binary);  // Open file for reading in binary mode
            bool anyOccupied = false;
            hotel temp;
            while (fin.read(reinterpret_cast<char*>(&temp), sizeof(hotel))) { //Check for any occupied rooms
                if (temp.check(temp.room_no)) {
                    anyOccupied = true;
                    break;
                }
            }
            fin.close();

            if (!anyOccupied) { //All room is vacant
                cout << "\n\n No rooms are currently occupied.";
                cout << "\n\n Press any key to go back to the edit menu....!!";
                getch();
                continue;
            }

            int r;
            while (true) {
                cout << "\n Enter room no: ";
                cin >> r;
                if (cin.fail() || r < 1 || r > 10) {  // Invalid room number handling
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Avoid the message displayed first before user can enter an input
                    cout << " !!! ERROR: Please enter a valid room number between 1 and 10: ";
                } else {
                    if (!check(r)) { //Check if the room that is choosen vacant or not
                        cout << "\n Room no. " << r << " is vacant. Please enter an occupied room number: ";
                    } else {
                        if (choice == 1) {
                            modify(r); //Direct user to the modify() function
                        } else if (choice == 2) {
                            delete_rec(r); //Direct user to the delete_rec() function
                        }
                        break;
                    }
                }
            }
        }
    }
    cout << "\n Press any key to continue....!!!";
    getch();
}

// Function to check room status
int hotel::check(int r) {
    int flag = 0;
    ifstream fin("Record.dat", ios::in | ios::binary);  // Open file for reading in binary mode
    while (fin.read(reinterpret_cast<char*>(this), sizeof(hotel))) { //Read records from file to assign to the variable
        if (room_no == r) {
            flag = 1;
            break;
        }
    }
    fin.close();
    return flag;  // Return 1 if room is occupied, 0 otherwise
}

// Function to modify a record
void hotel::modify(int r) {
    system("cls");
    head();
    long pos;
    int flag = 0;
    char temp_name[30], temp_address[50], temp_phone[15];  // Temporary variables for input
    int temp_days;
    fstream file("Record.dat", ios::in | ios::out | ios::binary);  // Open file for reading and writing in binary mode
    
    while (!file.eof()) {
        pos = file.tellg();
        file.read(reinterpret_cast<char*>(this), sizeof(hotel));  // Read records from file
        if (room_no == r) {
            cout << "\n Enter New Details";
            cout << "\n -----------------";
            cin.ignore();  // Clear input buffer before using getline
            while (true) {
                cout << "\n Name: ";
                cin.getline(temp_name, 30);
                if (regex_match(temp_name, regex("^[A-Za-z ]+$"))) {  // Validate name
                    strcpy(name, temp_name);
                    break;
                } else {
                    cout << " !!! ERROR: Name must contain only alphabets. Please enter again.\n";
                }
            }
            while (true) {
                cout << " Address: ";
                cin.getline(temp_address, 50);
                if (regex_match(temp_address, regex("^[A-Za-z0-9 ,.]+$"))) {  // Validate address
                    strcpy(address, temp_address);
                    break;
                } else {
                    cout << " !!! ERROR: Address must contain only alphabets, numbers, commas, and periods. Please enter again.\n";
                }
            }
            while (true) {
                cout << " Phone no: ";
                cin.getline(temp_phone, 15);
                if (regex_match(temp_phone, regex("^[0-9]+$"))) {  // Validate phone
                    strcpy(phone, temp_phone);
                    break;
                } else {
                    cout << " !!! ERROR: Phone number must contain only digits. Please enter again.\n";
                }
            }
            while (true) {
                cout << " Days: ";
                cin >> temp_days;
                if (cin.fail() || temp_days <= 0) {  // Invalid days handling
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << " !!! ERROR: Number of days must be a positive integer. Please enter again.\n";
                } else {
                    days = temp_days;
                    break;
                }
            }
            
            // Confirm modification
            char confirm;
            cout << "\n Do you want to modify this record (y/n): ";
            cin >> confirm;
            cin.ignore(); // Clear newline character left in buffer

            if (confirm == 'y' || confirm == 'Y') {
                fare = days * 20;  // Calculate fare
                file.seekg(pos);   // Move file pointer to the position of the record to be modified
                file.write(reinterpret_cast<char*>(this), sizeof(hotel));  // Write modified record to file
                cout << "\n Record is modified....!!";
                flag = 1;
            } else {
                cout << "\n Modification cancelled. Returning to edit menu....!!";
            }
            break; // Break out of the loop whether modified or not
        }
    }

    if (flag == 0) {
        cout << "\nSorry room no. " << r << "not found or vacant...!!";
    }

    file.close(); //Close file
    cout << "\n Press any key to continue....!!!";
    getch();
    // Call to the function that displays the edit menu
    edit();
}

// Function to delete a record
void hotel::delete_rec(int r) {
    system("cls");
    head();
    int flag = 0;
    char ch;
    ifstream fin("Record.dat", ios::in | ios::binary);  // Open file for reading in binary mode
    ofstream fout("temp.dat", ios::out | ios::binary);  // Open temporary file for writing in binary mode

    while (fin.read(reinterpret_cast<char*>(this), sizeof(hotel))) {  // Read records from file
        if (room_no == r) {
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone No: " << phone;
            cout << "\n Days: " << days;
            cout << "\n Total Fare: " << fare;
            cout << "\n\n Do you want to delete this record (y/n): ";
            cin >> ch;  // Confirm deletion
            if (ch == 'y' || ch == 'Y') {
                cin.ignore(); // Clear input buffer
                string confirmation;
                cout << "\n To confirm deletion, please type: 'I Confirm To Delete The Data'\n";
                getline(cin, confirmation);
                if (confirmation == "I Confirm To Delete The Data") {
                    cout << "\n Record deleted....!!";
                    flag = 1;
                } else {
                    cout << "\n Confirmation failed. Record not deleted.";
                    fout.write(reinterpret_cast<char*>(this), sizeof(hotel));  // Write record to temporary file if not deleting
                }
            } else {
                fout.write(reinterpret_cast<char*>(this), sizeof(hotel));  // Write record to temporary file
            }
        } else {
            fout.write(reinterpret_cast<char*>(this), sizeof(hotel));  // Write record to temporary file if not deleting
        }
    }

    fin.close();  // Close input file
    fout.close();  // Close output file

    if (flag == 0) {
        cout << "\n Sorry room no. " << r << "not found or vacant...!!";
    } else if (flag == 1) {
        remove("Record.dat");  // Remove original file
        rename("temp.dat", "Record.dat");  // Rename temporary file to original file
    } else {
        remove("temp.dat");  // Remove temporary file
    }

    cout << "\n Press any key to continue....!!!";
    getch();
    edit();
}

// Main Function
int main() {
    hotel h;

    intro();
    time();
    cout << "\n\n\n\t\t\tPress any key to continue....!!";
    getch();

// Login part starts here
    head();
    string id, pass;
    int attempts = 0;
    const int maxAttempts = 3;

    while (attempts < maxAttempts) {
        cout << "\n\n\t\t\t\tusername => ";
        cin >> id;
        pass.clear();
        cout << "\n\t\t\t\tpassword => ";
        char ch = _getch();
        while (ch != 13) {  // Character 13 is Enter
            pass.push_back(ch);
            cout << '*';
            ch = _getch();
        }
        cout << endl;

        if (id == "admin" && pass == "HBook#Admin821") {
            cout << "\n\n\t\t\t  !!!Login Successful!!!";
            break;
        } else {
            attempts++;
            cout << "\n\n\t\t\t!!!Username or Password is incorrect!!!";
            cout << "\n\t\t\tAttempt " << attempts << " of " << maxAttempts << "\n";
            if (attempts >= maxAttempts) {
                cout << "\n\n\t\t\tMaximum attempts reached. Exiting...";
                getch();
                exit(-1);
            }
            getch();
            system("cls");
            head();
        }
    }
// Login part ends here

    h.main_menu();
    getch();

    return 0;
}