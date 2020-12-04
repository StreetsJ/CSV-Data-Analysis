#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <sstream>
#include <utility>

using namespace std;

struct Client {
    int ID;
    vector<pair<int, int>> payed;
    int total_payment;
    Client(int id, pair<int, int> pay) { ID = id; payed.push_back(pay); total_payment = pay.second; } 
};

struct Analysis {
    vector<Client> client_list;
    int revenue;
    Analysis() { revenue = 0; }
};

int main() {

    /* Our csv file will be layed out as Day, Client#, Payment Amout */
    auto start = chrono::high_resolution_clock::now();
    Analysis client_database;
    ifstream ifs("test.csv");
    string temp;
    getline(ifs, temp);
    int day;
    long int cli, amt;
    char com1;
    char com2;
    while (ifs >> day >> com1 >> cli >> com2 >> amt)
    {
        bool inList = false;
        for (Client elem: client_database.client_list)
        {
            if (cli == elem.ID) 
            {
                elem.payed.push_back(make_pair(day, amt));
                elem.total_payment += amt;
                inList = true;
            }
        }
        if (!inList) 
        {
            Client newClient(cli, make_pair(day, amt));
            client_database.client_list.push_back(newClient);
        }
    }

    for (Client elem : client_database.client_list)
    {
        client_database.revenue += elem.total_payment;
    }

    ofstream ofs("data.csv");
    ofs << "TotalRevenue, " << client_database.revenue << "\nClient,TotalPayment\n";
    for (Client elem : client_database.client_list)
    {
        ofs << elem.ID << ',' << elem.total_payment << "\n";
    }
    
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
    cout << "Execution time: " << duration.count() << " microseconds\n"; 
    return 0;
}