#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
struct TRAIN
{
    string NAZV;
    int NUMR;
    string DATE;
    string TIME;
};

TRAIN readTrainFromConsole() {
    TRAIN train;
    cout << "Enter the destination: ";
    cin >> train.NAZV;
    cout << "Enter the train number: ";
    cin >> train.NUMR;
    cout << "Enter the departure date: ";
    cin >> train.DATE;
    cout << "Enter the departure time: ";
    cin >> train.TIME;
    return train;
}

void writeTrain(ofstream& file, const TRAIN& train)
{
    file << train.NAZV << " " << train.NUMR << " " << train.DATE << " " << train.TIME << "\n";
}


void searchRecords(const string& fileName, const string& searchTerm, const string& searchField)
{
    ifstream inputFile(fileName);
    if (inputFile.is_open())
    {
        TRAIN train;
        bool found = false;

        while (inputFile >> train.NAZV >> train.NUMR >> train.DATE >> train.TIME)
        {
            if ((searchField == "NAZV" && train.NAZV == searchTerm)||
                (searchField == "NUMR" && train.NUMR == stoi(searchTerm))||
                (searchField == "DATE" && train.DATE == searchTerm) ||
                (searchField == "TIME" && train.TIME == searchTerm))
            {
                cout << "Record found: " << train.NAZV << " " << train.NUMR << " " << train.DATE << " " << train.TIME << " " << endl;
                found = true;
            }
        }

        if (!found)
        {
            cout << "Record not found." << endl;
        }

        inputFile.close();
    }
    else
    {
        cerr << "Error opening file: " << fileName << endl;
    }
}

void addRecord(const string& fileName, const TRAIN& newRecord)
{
    ofstream outputFile(fileName, ios::app);
    if (outputFile.is_open())
    {
        writeTrain(outputFile, newRecord);
        outputFile.close();
        cout << "Record added successfully." << endl;
    }
    else
    {
        cerr << "Error opening file: " << fileName << endl;
    }
}

void deleteRecord(const string& fileName, int recordNumber)
{
    ifstream inputFile(fileName);
    vector<TRAIN> trains;

    if (inputFile.is_open())
    {
        TRAIN train;
        while (inputFile >> train.NAZV >> train.NUMR >> train.DATE >> train.TIME)
        {
            trains.push_back(train);
        }

        inputFile.close();

        if (recordNumber >= 0 && recordNumber < trains.size())
        {
            trains.erase(trains.begin() + recordNumber);
            ofstream outputFile(fileName);
            for (const auto& remainingTrain : trains)
            {
                writeTrain(outputFile, remainingTrain);
            }

            cout << "Record deleted successfully." << endl;
        }
        else
        {
            cerr << "Invalid record number." << endl;
        }
    }
    else
    {
        cerr << "Error opening file: " << fileName << endl;
    }
}

int main()
{
    const string fileName = "trains.txt";
    int choice;

    do
    {
        cout << "\n1. Add Record\n2. Search Records\n3. Delete Record\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addRecord(fileName, readTrainFromConsole());
            break;
        case 2:
        {
            string searchField, searchTerm;
            cout << "Enter the field to search (NAZV, NUMR, DATE, TIME): ";
            cin >> searchField;
            cout << "Enter the search term: ";
            cin >> searchTerm;
            searchRecords(fileName, searchTerm, searchField);
            break;
        }
        case 3:
        {
            int recordNumber;
            cout << "Enter the record number to delete: ";
            cin >> recordNumber;
            deleteRecord(fileName, recordNumber);
            break;
        }
        case 0:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}