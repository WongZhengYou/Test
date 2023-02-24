#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const int MAX_VEHICLES = 2000;  // Maximum number of vehicles in the CSV file

struct Invoice {
    string invoice_id,
        vehicle_title,
        registration_year,
        mileage,
        engine_size,
        url,
        invoice_date,
        price;
};
int calculateRevenue(vector<vector<string>>content) {
    int totalRevenue = 0;
    int numVehicles = content.size();
    int maxVehicles = min(numVehicles, 1500);
    for (int i = 0; i < numVehicles; i++) {
        if (!content[i][1].empty()) { // check if the price field is not empty
            try {
                // convert the price string to an integer using std::stoi with std::string::c_str()
                int price = stoi(content[i][1].c_str());
                totalRevenue += price;
            }
            catch (const std::invalid_argument& e) {
                // handle invalid argument exception

            }
        }
    }
    return totalRevenue;
}


float calculateAveragePrice(vector<vector<string>>content) {
    int totalRevenue = 0;
    int numVehicles = content.size();
    int maxVehicles = min(numVehicles, 1500);
    for (int i = 0; i < numVehicles; i++) {
        try {
            //convert the price string to an integer
            int price = stoi(content[i][1]);
            totalRevenue += price;
        }
        catch (const invalid_argument& e) {

        }
    }
    float avgPrice = static_cast<float>(totalRevenue) / numVehicles;
    return avgPrice;
}

struct report
{
    void generateClientReport(const vector<vector<string>>& content) {
        vector<Invoice>invoices;

        // Generate report header
        cout << "---------------------- CLIENT REPORT ----------------------" << endl;
        cout << "Name:" << "" << endl;
        // Add the current date to the report header
        cout << "Date of purchase:" << "" << endl;
        cout << "--------------------- VEHICLE DETAILS ----------------------" << endl;
        cout << "Vehicle Information:" << endl;

        for (const auto& invoice : invoices) {

            //if (invoice.vehicle_title == xxx.title) {
                // Generate report body for this vehicle
                cout << "Vehicle Title:" << "" << endl;
                cout << "Vehicle Price:" << "" << endl;
                cout << "Vehicle Registration Date:" << "" << endl;
                cout << "Vehicle Fuel Type: " << "" << endl;
                cout << "Vehicle Color: " << "" << endl;
                cout << "-----------------------------------------------------------" << endl;
           // }

        }
    }
    
    void generateSalesReport(vector<vector<string>>& content, vector<Invoice>& invoices) {
        // Convert content to vector of Vehicle objects

        int revenue = calculateRevenue(content);
        float averageRevenue = calculateAveragePrice(content);
        int numVehicles = content.size();
        int maxVehicles = min(numVehicles, 1500);

        // Generate report header
        cout << "---------------------- SALES REPORT ----------------------" << endl;
        cout << "Total vehicles sold: " << numVehicles << endl;
        cout << "Total revenue: $" << revenue << endl;
        cout << "Average revenue: $" << averageRevenue << endl;

        //Generate report body
        cout << "--------------------- SALES DETAILS ----------------------" << endl;
        if (invoices.size() == 0) {
            cout << "No invoices to display." << endl;
        }
        else {
            cout << invoices[0].invoice_id << endl;
            cout << invoices[1].vehicle_title << endl;
            cout << invoices[7].price << endl;
            cout << invoices[2].registration_year << endl;
            //Generate report end
            cout << "-----------------------------------------------------------" << endl;
        }
    }

    void generateBillingReport(/*const vector<Bill>& bills*/) {
        // Generate billing report
        //cout << "-----------------Billing Report-----------------" << endl;
        //cout << "Total number of bills generated: " << bills.size() << endl;
        //if (bills.empty()) {
        //    cout << "No bills found." << endl;
        //    return;
        //}
        //float totalRevenue = 0.0;
        //for (auto bill : bills) {
        //    totalRevenue += bill.total;
        //}
        //cout << "Total revenue generated: " << totalRevenue << endl;

        //// Generate individual bill reports
        //for (auto bill : bills) {
        //    cout << "---------------BILL REPORT--------------" << endl;
        //    cout << "Bill ID:" << bill.bill_id << endl;
        //    cout << "Client: " << bill.client.name << endl;
        //    cout << "Vehicle Title: " << bill.vehicleTitle << endl;
        //    cout << "Price: " << bill.price << endl;
        //    cout << "Tax: " << bill.tax << endl;
        //    cout << "Total: " << bill.total << endl;
        }
    
};
