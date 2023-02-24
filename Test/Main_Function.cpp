#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "ChongWanSiong.h"
#include "report.h"
#include "billing.h"

using namespace std;

struct Role {
    string MANAGER;
    string USER;
};

struct User {
    string username;
    string password;
    Role role;
};

User users[100];
int user_count = 0;


void add_user(string username, string password, Role role) {
    users[user_count].username = username;
    users[user_count].password = password;
    users[user_count].role = role;
    user_count++;
}



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

    vector<Vehicle> vehicles = {
        {"Toyota Camry", 25000.00, "Red", false},
        {"Honda Civic", 22000.00, "Blue", false},
        {"Ford Mustang", 35000.00, "Black", false},
        {"Chevrolet Corvette", 65000.00, "Yellow", false},
        {"Jeep Wrangler", 32000.00, "Green", false},
        {"BMW 3 Series", 42000.00, "Silver", false},
        {"Audi A4", 38000.00, "Gray", false},
        {"Tesla Model S", 80000.00, "White", false},
        {"Nissan Altima", 24000.00, "Red", false},
        {"Kia Soul", 20000.00, "Black", false},
        {"Mazda CX-5", 28000.00, "Blue", false},
        {"Subaru Outback", 32000.00, "Gray", false},
        {"Toyota RAV4", 27000.00, "White", false},
        {"Honda CR-V", 26000.00, "Green", false},
        {"Ford Explorer", 40000.00, "Silver", false}
    };

    vector<vector<string>> content;
    Client clients[100];
    vector<Invoice>invoices;
    vector<Bill> bills;
    int numClients = 0;
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
                                main();
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
                        report r;

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

                                r.generateClientReport(content);
                            }
                            else if (choice == "3") {
                                // Generate billing report

   /*                             r.generateBillingReport(bills);*/

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
                cout << "Welcome to the salesperson page." << endl;
                int choice;
                do {
                    cout << "Please select an option:\n";
                    cout << "1. Search\n";
                    cout << "2. Create Invoice\n";
                    cout << "3. Regiter Client\n";
                    cout << "4. Create bill\n";
                    cout << "5. Book Vehicle\n";
                    cout << "6. Exit\n";
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
                                main();
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
                        addClient(clients, numClients);
                        cout << "Client: " << clients[numClients-1].name << "\n" << endl;
                        break;
                    }
                    case 4: {
                        // Call generateBill function
                        generateBill(clients, numClients, content);
                        break;

                    }
                    case 5: {
                        bookVehicle(clients, numClients, vehicles);
                        break;
                    }
                    case 6: {
                        cout << "Going out \n";
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
                cout << "5. Book Vehicle\n";
                cout << "6. Exit\n";
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
                            main();
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
                    addClient(clients, numClients);
                    cout << "Client: " << clients[numClients - 1].name << "\n" << endl;
                    break;
                }
                case 4:{
                    // Call generateBill function
                    generateBill(clients, numClients, content);
                    break;
                }
                case 5: {
                    bookVehicle(clients, numClients, vehicles);
                    break;
                }
                case 6: {
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