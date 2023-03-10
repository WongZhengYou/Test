#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

struct Client {
    string name;
    string address;
    string email;
    string dob;
    string bookedVehicles;
};

struct Vehicle
{
    string title;
    double price;
    string color;
    bool isBooked;
}; 

struct Bill {
    string bill_id;
    Client client;
    string vehicleTitle;
    float price;
    float tax;
    float total;
};
vector<Bill>bills;

void addClient(Client clients[], int& numClients) {
    if (numClients >= 100) {
        cout << "Error: Maximum number of clients reached." << endl;
        return;
    }
    Client newClient;
    string inname, inaddress, inemail, indob;
    cout << "Enter client name: ";
    cin >> inname;
    cout << "Enter client address: ";
    cin >> inaddress;
    cout << "Enter client email: ";
    cin >> inemail;
    cout << "Enter client date of birth: ";
    cin >> indob;
    char choice;
    newClient.name = inname;
    newClient.address = inaddress;
    newClient.email = inemail;
    newClient.dob = indob;
    clients[numClients] = newClient;
    numClients++;
    cout << "Add another client? (y/n): ";
    cin >> choice;
    cin.ignore(); // consume newline character left in input buffer
    if (choice == 'y' || choice == 'Y') {
        addClient(clients, numClients);
    }

}
void generateBill(Client clients[], int numClients, vector<vector<string>> content) {
    static int id_counter = 1;
    string bill_id = "ID" + to_string(id_counter++);
    float price = 0.0;
    string invoice_date, url;
    string registration_year;
    string mileage, engine_size;
    string name;
    float tax = 0.0;
    float total = 0.0;
    cout << "Enter client name: ";
    cin >> name;

    // Find the client in the clients array
    Client client;
    bool foundClient = false;
    for (int i = 0; i < numClients; i++) {
        if (clients[i].name == name) {
            client = clients[i];
            foundClient = true;
            break;
        }
    }
    if (!foundClient)
    {
        cout << "Error: Client not found." << endl;
        return;
    }


    string vehicleTitle;
    cout << "Enter the complete vehicle title:  ";
    cin.ignore();
    getline(cin, vehicleTitle);
    bool found = false;
    while (!found) {
        for (auto& row : content) {
            if (row[0] == vehicleTitle) {
                price = stof(row[1].substr(2));
                found = true;
                break;
            }
        }
    }
    if (!found) {
        cout << "Vehicle not found. Please enter a valid title." << endl;
        cout << "Enter the complete vehicle title:  ";
        getline(cin, vehicleTitle);
    }
    // Calculate the bill amount
    tax = price * 0.10;
    total = price + tax;

    struct Bill bill = {
           bill_id,
           client,
           vehicleTitle,
           price,
           tax,
           total
    };

    // Create the bill and add it to the bills vector
    bills.push_back(bill);
    // Display the bill details
    cout << "Bill generated and added to list." << endl;
    cout << "---------------BILL--------------" << endl;
    cout << "Bill ID:" << bill_id << endl;
    cout << "Client: " << client.name << endl;
    cout << "Vehicle Title: " << vehicleTitle << endl;
    cout << "Price: " << price << endl;
    cout << "Tax: " << tax << endl;
    cout << "Total: " << total << endl;
    return;
}



void bookVehicle(Client clients[], int numClients, vector<Vehicle>& vehicles) {

    // Prompt user to enter client name
    string name;
    cout << "Enter client name: ";
    cin >> name;

    // Find the client in the clients array
    Client client;
    bool foundClient = false;
    for (int i = 0; i < numClients; i++) {
        if (clients[i].name == name) {
            client = clients[i];
            foundClient = true;
            break;
        }
    }
    if (!foundClient) {
        cout << "Error: Client not found." << endl;
        return;
    }

    // Display the list of vehicles
    cout << "List of vehicles: " << endl;
    for (int i = 0; i < vehicles.size(); i++) {
        cout << i + 1 << ". " << vehicles[i].title << " - " << vehicles[i].color << " - $" << vehicles[i].price;
        if (vehicles[i].isBooked) {
            cout << " (Booked)";
        }
        cout << endl;
    }

    // Prompt user to select a vehicle
    int choice;
    cout << "Enter the number of the vehicle you would like to book: ";
    cin >> choice;

    // Validate user input
    if (choice < 1 || choice > vehicles.size()) {
        cout << "Error: Invalid choice." << endl;
        return;
    }

    // Check if selected vehicle is already booked
    if (vehicles[choice - 1].isBooked) {
        cout << "Error: Vehicle is already booked." << endl;
        return;
    }

    // Add the selected vehicle to the client's booked vehicles
    string vehicleTitle = vehicles[choice - 1].title;
    vector<Vehicle> bookedVehicles;
    bookedVehicles.push_back(vehicles[choice - 1]);
    // Update the booked status of the selected vehicle
    vehicles[choice - 1].isBooked = true;

    // Display booking information
    cout << "Vehicle booked: " << vehicles[choice - 1].title << endl;

    cout << endl << "Booking Receipt for " << client.name << ":" << endl << endl;
    cout << "Vehicle: " << bookedVehicles.back().title << endl;
    cout << "Color: " << bookedVehicles.back().color << endl;
    cout << "Price: $" << bookedVehicles.back().price << endl;
    return;
}









