#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "ChongWanSiong.h"
#include "report.h"
#include "billing.h"

using namespace std;
const int MAX_USERS = 100;

struct Role {
    string MANAGER;
    string USER;
};

struct User {
    string username;
    string password;
    Role role;
};

User users[MAX_USERS];
int user_count = 0;

void add_user(string username, string password, Role role) {
    users[user_count].username = username;
    users[user_count].password = password;
    users[user_count].role = role;
    user_count++;
}

//// Function to split a string into an array of strings
//vector<string> split(const string& s, char delimiter) {
//    vector<string> tokens;
//    string token;
//    istringstream tokenStream(s);
//    while (getline(tokenStream, token, delimiter)) {
//        if (!token.empty()) {  // add this line to skip empty tokens
//            tokens.push_back(token);
//        }
//    }
//    return tokens;
//}
//vector<Vehicle> arrayvehicle( ) {
//    vector<Vehicle> vehicles;
//    int numVehicles = 0;
//    ifstream inputFile("carlist.csv");
//    string line;
//    getline(inputFile, line);  // skip the header line
//
//    while (getline(inputFile, line)) {
//        vector<string> fields = split(line, ',');
//        if (fields.size() != 12) {  // skip rows with missing fields
//            continue;
//        }
//        vehicles[numVehicles].title = fields[0];
//        vehicles[numVehicles].price = fields[1].substr(2);
//        vehicles[numVehicles].registrationDate = fields[2];
//        vehicles[numVehicles].fuelType = fields[4];
//        vehicles[numVehicles].transmission = fields[5];
//        vehicles[numVehicles].engineSize = fields[6];
//        vehicles[numVehicles].doors = fields[7];
//        vehicles[numVehicles].color = fields[8];
//        vehicles[numVehicles].bodyType = fields[9];
//        vehicles[numVehicles].URL = fields[10];
//        vehicles[numVehicles].saleDates = fields[11];
//        numVehicles++;
//    }
//    inputFile.close();
//    return vehicles;
//}


int totalCars(vector<Vehicle>vehicles) {
    return vehicles.size();
}
bool login(string username, string password, Role& role) {
    if (username == "manager" && password == "manager") {
        role = Role{ "manager", "" };
        return true;
    }

    for (int i = 0; i < user_count; i++) {
        if (users[i].username == username) {
            if (users[i].password == password) {
                role = users[i].role;
                return true;
            }
            else {
                return false;
            }
        }
    }
    return false;
}



int main() {

    vector<vector<string>> content;

    // Open the CSV file
    ifstream file("carlist.csv");

    // Read the header row from the file
    string header;
    getline(file, header);

    // Read the data from the file
    string line;
    while (getline(file, line)) {
        vector<string> row;
        istringstream ss(line);
        string cell;
        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        content.push_back(row);
    }

    file.close();

    Role role;
    while (true) {
        string username;
        cout << "Enter username: ";
        cin >> username;

        if (username == "exit") {
            break;
        }

        string password;
        cout << "Enter password: ";
        cin >> password;

        if (login(username, password, role)) {
            cout << "Login successful!" << endl;
            if (role.MANAGER != "") {
                cout << "Welcome to the manager page." << endl;
                int choice;
                do {
                    cout << "Please select an option:\n";
                    cout << "1. Search\n";
                    cout << "2. Create Invoice\n";
                    cout << "3. Generate Report\n";
                    cout << "4. Exit\n";
                    cout << "Your choice: ";
                    cin >> choice;

                    switch (choice) {
                    case 1: {
                        int search_choice;
                        do {
                            cout << "Please select a search option:\n";
                            cout << "1. Search by year and fuel\n";
                            cout << "2. Search by transmission and engine size\n";
                            cout << "3. Back to main menu\n";
                            cout << "Your choice: ";
                            cin >> search_choice;

                            switch (search_choice) {
                            case 1: {
                                search searchobj;
                                searchobj.searchbyYearFuelh(content);
                                break;
                            }
                            case 2: {
                                search searchobj;
                                searchobj.searchbyTransEngine(content);
                                break;
                            }
                            case 3: {
                                // Back to main menu
                                break;
                            }
                            default: {
                                cout << "Invalid choice. Please try again.\n";
                                break;
                            }
                            }
                        } while (search_choice != 3);
                        break;
                    }
                    case 2: {
                        // Create invoice function
                        search invoice;
                        invoice.create_invoice(content);
                        break;
                    }
                    case 3: {
                        string choice;
                        bool validInput = false;
                        vector<Vehicle>vehicles;
                        vector<Invoice>invoices;
                        ;                   report r;

                        while (!validInput) {
                            cout << "What report you want to generate:\n1)Sales report\n2)Client report\n3)Billing report\nMy choice is (1/2/3):";
                            cin >> choice;

                            if (choice == "1") {
                                // Generate sales report
                                validInput = true;
                                r.generateSalesReport(content, invoices);

                            }
                            else if (choice == "2") {
                                // Generate client report
                                validInput = true;

                                r.generateClientReport(content, vehicles);
                            }
                            else if (choice == "3") {
                                // Generate billing report
                                validInput = true;
                                r.generateBilingReport(content, vehicles);
                            }
                            else {
                                cout << "Invalid input. Please enter 1, 2, or 3.\n";
                            }
                            break;
                        }
                    }
                    case 4: {
                        cout << "geting out ......" << endl;
                        main();
                        break;
                    }
                    default: {
                        cout << "Invalid choice. Please try again.\n";
                        break;
                    }
                    }
                } while (choice != 3);
            
            }
            else {
                cout << "Welcome to the staff page." << endl;
                int choice;
                do {
                    cout << "Please select an option:\n";
                    cout << "1. Search\n";
                    cout << "2. Create Invoice\n";
                    cout << "3. Regiter Client\n";
                    cout << "4. Create bill\n";
                    cout << "5. Exit\n";
                    cout << "Your choice: ";
                    cin >> choice;

                    switch (choice) {
                    case 1: {
                        int search_choice;
                        do {
                            cout << "Please select a search option:\n";
                            cout << "1. Search by year and fuel\n";
                            cout << "2. Search by transmission and engine size\n";
                            cout << "3. Back to main menu\n";
                            cout << "Your choice: ";
                            cin >> search_choice;

                            switch (search_choice) {
                            case 1: {
                                search searchobj;
                                searchobj.searchbyYearFuelh(content);
                                break;
                            }
                            case 2: {
                                search searchobj;
                                searchobj.searchbyTransEngine(content);
                                break;
                            }
                            case 3: {
                                // Back to main menu
                                break;
                            }
                            default: {
                                cout << "Invalid choice. Please try again.\n";
                                break;
                            }
                            }
                        } while (search_choice != 3);
                        break;
                    }
                    case 2: {
                        // Create invoice function
                        search invoice;
                        invoice.create_invoice(content);
                        break;
                    }
                    case 3: {
                        Client clients[100];
                        int numClients = 0;
                        addClient(clients, numClients);
                        break;
                    }
                    case 4: {
                        Client clients[100];
                        int numClients = 0;

                        vector<Bill> bills;
        

                        // call the generateBill function
                        generateBill(clients, numClients, content);
                        break;

                    }
                    case 5: {
                        cout << "Going out haiyaa\n";
                        main();
                    }
                    default: {
                        cout << "Invalid choice. Please try again.\n";
                        break;
                    }
                    }
                } while (choice != 3);
        
            }
        }
            
        else {
            add_user(username, password, Role{ "", "staff" });
            cout << "Welcome, new user. You have been added to the system." << endl;

            int choice;
            do {
                cout << "Please select an option:\n";
                cout << "1. Search\n";
                cout << "2. Create Invoice\n";
                cout << "3. Regiter Client\n";
                cout << "4. Create bill\n";
                cout << "5. Exit\n";
                cout << "Your choice: ";
                cin >> choice;

                switch (choice) {
                case 1: {
                    int search_choice;
                    do {
                        cout << "Please select a search option:\n";
                        cout << "1. Search by year and fuel\n";
                        cout << "2. Search by transmission and engine size\n";
                        cout << "3. Back to main menu\n";
                        cout << "Your choice: ";
                        cin >> search_choice;

                        switch (search_choice) {
                        case 1: {
                            search searchobj;
                            searchobj.searchbyYearFuelh(content);
                            break;
                        }
                        case 2: {
                            search searchobj;
                            searchobj.searchbyTransEngine(content);
                            break;
                        }
                        case 3: {

                            break;
                        }

                        default: {
                            cout << "Invalid choice. Please try again.\n";
                            break;
                        }
                        }
                    } while (search_choice != 3);
                    break;
                }
                case 2: {
                    // Create invoice function
                    search invoice;
                    invoice.create_invoice(content);
                    break;
                }
                case 3: {
                    Client clients[100];
                    int numClients = 0;
                    addClient(clients, numClients);
                    cout << "Client:"<<clients->name <<"\n" << endl;
                    break;
                }
                case 4:{
                    Client clients[100];
                    int numClients = 0;
                    vector<Bill> bills;
                    vector<vector<string>> content;
                    // Call generateBill function
                    generateBill(clients, numClients, content);
                    break;
                }
                case 5: {
                    cout << "existing system.....\n";
                    main();
                    break;
                }

                default: {
                    cout << "Invalid choice. Please try again.\n";
                    break;
                }
                }
            } while (choice != 3);
        }
    }

    return 0;
}