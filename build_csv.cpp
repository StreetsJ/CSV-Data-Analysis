#include <iostream>
#include <fstream>
#include <random>
#include <time.h>
#include <chrono>
#include <list>

using namespace std;

void building(long long& sum)
{
    srand(time(0));
    ofstream ofs("test.csv");
    ofs << "Day" << ',' << "Client" << ',' << "Amount" << ',' << '\n';
    auto start = chrono::high_resolution_clock::now(); 
    for (unsigned int i = 0; i < 10'000; i++)
    {
        ofs << i << ',' << rand() % 100 << ',' << rand() % 100'000 << '\n';
    }
    ofs.close();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
    auto time = duration.count();
    sum = sum + time;
}

int main() {
    list<long long> data;
    long long sum = 0;
    for(unsigned short i = 0; i < 100; i++)
        building(sum);
    double avg = sum / 100;
    cout << "Average execution time for building csv: " << avg << endl;
    return 0;
}