#include <iostream>
#include <iomanip>
#include <fstream>
#include "WaitingQueue.h"
#include "Teller.h"
#include <string> 

using namespace std;

// Read  Customer data from the file 
void readCustomerData(ifstream& inputFile, WaitingQueue& waitingQueue) {
    int customerId, arrivalTime, serviceTime;
    while (inputFile >> customerId >> arrivalTime >> serviceTime) {
        Customer newCustomer(customerId, arrivalTime, 0, serviceTime);
        waitingQueue.Add(newCustomer);
    }
    waitingQueue.SortQueue();
}

// Print Customer data in a consol and file 
void printTableHeaders(ofstream& outputFile) {
    cout << left << setw(15) << "Teller" << setw(15) << "Customer ID" << setw(15) << "Arrival Time"
        << setw(15) << "Service Time" << setw(15) << "Waiting Time" << setw(15) << "Leaving Time" << endl;

    outputFile << left << setw(10) << "Teller" << setw(15) << "Customer ID" << setw(15) << "Arrival Time"
        << setw(15) << "Service Time" << setw(15) << "Waiting Time" << setw(15) << "Leaving Time" << endl;

    cout << "-------------------------------------------------------------------------------------" << endl;
    outputFile << "-------------------------------------------------------------------------------------" << endl;
}

//Style Functions
void printTableHeader(ostream& os) {
    os << "+-----------------------------------------+------------------+" << endl;
}

void printTableRow(ostream& os, const string& label, const string& value) {
    os << "| " << left << setw(40) << label << "| " << setw(18) << value << "|" << endl;
}

// BQMS Simulation 
void simulate(WaitingQueue& waitingQueue, TellerList& tellerList, ofstream& outputFile) {
    int completedServices = 0;
    int totalWaitingTime = 0;
    int totalServiceTime = 0;
    int maximumWaitingTime = 0;
    int numberOfTellers = 3;
    int totalArrivalTime = 0;
    int previousArrivalTime = 0;

    for (int i = 0; i < 100; i++) {
        if (!waitingQueue.IsEmpty()) {
            int tellerNumber;
            if ((tellerNumber = tellerList.GetFreeTellers()) != -1) {
                Customer nextCustomer = waitingQueue.Front();
                waitingQueue.Delete();
                tellerList.SetTellerBusy(tellerNumber, nextCustomer);
                nextCustomer.SetleaveTime();

                // Print data in a console and file
                cout << left << setw(18) << tellerNumber << setw(15) << nextCustomer.GetcustomerId()
                    << setw(15) << nextCustomer.GetArrivalTime() << setw(15) << nextCustomer.GetserviceTime()
                    << setw(15) << nextCustomer.GetWaitingTime() << setw(15) << nextCustomer.GetleaveTime() << endl;

                outputFile << left << setw(18) << tellerNumber << setw(15) << nextCustomer.GetcustomerId()
                    << setw(10) << nextCustomer.GetArrivalTime() << setw(15) << nextCustomer.GetserviceTime()
                    << setw(15) << nextCustomer.GetWaitingTime() << setw(15) << nextCustomer.GetleaveTime() << endl;

                cout << "-------------------------------------------------------------------------------------" << endl;
                outputFile << "-------------------------------------------------------------------------------------" << endl;


                // TotalArrival Time
                totalArrivalTime += (nextCustomer.GetArrivalTime() - previousArrivalTime);
                previousArrivalTime = nextCustomer.GetArrivalTime();

                completedServices++;
                totalWaitingTime += nextCustomer.GetWaitingTime();
                totalServiceTime += nextCustomer.GetserviceTime();

                //  Maximum waiting time
                if (nextCustomer.GetWaitingTime() > maximumWaitingTime) {
                    maximumWaitingTime = nextCustomer.GetWaitingTime();
                }
            }
            else if (waitingQueue.Front().GetArrivalTime() == i) {
                waitingQueue.UpdateWaitingQueue();
            }
            tellerList.UpdateTellers();
        }
    }

    double averageArrivalTimeDifference = static_cast<double>(totalArrivalTime) / completedServices;
    double averageWaitingTime = static_cast<double>(totalWaitingTime) / completedServices;
    double averageServiceTime = static_cast<double>(totalServiceTime) / completedServices;
    double percentageCustomersServed = (completedServices > 0) ?
        (static_cast<double>(completedServices) / (completedServices + waitingQueue.GetCurrentSize())) * 100 : 0.0;

    // Print Statistics in a consol
    cout << "\nStatistics:\n";
    printTableHeader(cout);
    printTableRow(cout, "Number of Tellers:", to_string(numberOfTellers));
    printTableRow(cout, "Average arrival time :", to_string(averageArrivalTimeDifference));
    printTableRow(cout, "Total waiting time:", to_string(totalWaitingTime));
    printTableRow(cout, "Completed services :", to_string(completedServices));
    printTableRow(cout, "Average waiting time:", to_string(averageWaitingTime));
    printTableRow(cout, "Total Service Time:", to_string(totalServiceTime));
    printTableRow(cout, "Maximum Waiting Time:", to_string(maximumWaitingTime));
    printTableRow(cout, "Average Service Time:", to_string(averageServiceTime));
    printTableRow(cout, "Percentage of Customers Served:", to_string(percentageCustomersServed) + "%");
    cout << "+-----------------------------------------+------------------+" << endl;

    // Print statistics in a output file
    outputFile << "\nStatistics:\n";
    printTableHeader(outputFile);
    printTableRow(outputFile, "Number of Tellers:", to_string(numberOfTellers));
    printTableRow(outputFile, "Average arrival time:", to_string(averageArrivalTimeDifference));
    printTableRow(outputFile, "Total waiting time:", to_string(totalWaitingTime));
    printTableRow(outputFile, "Completed services:", to_string(completedServices));
    printTableRow(outputFile, "Average waiting time:", to_string(averageWaitingTime));
    printTableRow(outputFile, "Total Service Time:", to_string(totalServiceTime));
    printTableRow(outputFile, "Maximum Waiting Time:", to_string(maximumWaitingTime));
    printTableRow(outputFile, "Average Service Time:", to_string(averageServiceTime));
    printTableRow(outputFile, "Percentage of Customers Served:", to_string(percentageCustomersServed) + "%");
    outputFile << "+-----------------------------------------+------------------+" << endl;

}



int main() {

    ifstream inputFile("InputData.txt");
    if (!inputFile.is_open()) {
        cerr << "Error: Can not open the InputData .\n";
        return 1;
    }

    int numberOfTellers = 3;
    WaitingQueue waitingQueue(50);
    TellerList tellerList(numberOfTellers);

    readCustomerData(inputFile, waitingQueue);
    ofstream outputFile("Results.txt");
    if (!outputFile.is_open()) {
        cerr << "Error:can not open the output file.\n";
        return 1;
    }

    printTableHeaders(outputFile);
    simulate(waitingQueue, tellerList, outputFile);

    outputFile.close();
    inputFile.close();
    return 0;
}
