// Write a program to implement first come first serve cpu scheduling algorithm (FCFS) with arrival time.

#include <iostream>
using namespace std;

int main()
{
    int n, bt[20], at[20], wt[20], tat[20], temp[20];
    float awt = 0;
    float atat = 0;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the burst time of the processes: ";
    for (int i = 0; i < n; i++)
        cin >> bt[i];

    cout << "Enter the arrival time of the processes: ";
    for (int i = 0; i < n; i++)
        cin >> at[i];

    temp[0] = 0;
    cout << "Process\t Burst time\t Arrival time\t Waiting time\t Turn around time" << endl;
    for (int i = 0; i < n; i++)
    {
        wt[i] = 0;
        tat[i] = 0;
        temp[i + 1] = temp[i] + bt[i];
        wt[i] = temp[i] - at[i];
        tat[i] = wt[i] + bt[i];
        awt = awt + wt[i];
        atat = atat + tat[i];
        cout << i + 1 << "\t" << bt[i] << "\t\t" << at[i] << "\t\t" << wt[i] << "\t\t" << tat[i] << endl;
    }
    awt = awt / n;
    atat = atat / n;
    cout << "Average waiting time and avegate turn around time is: " << awt << " and " << atat << " respectively" << endl;
    return 0;
}

// Terminal

// Enter the number of processes: 4
// Enter the burst time of the processes: 5 4 1 3
// Enter the arrival time of the processes: 0 1 2 3
// Process  Burst time      Arrival time    Waiting time    Turn around time
// 1       5               0               0               5
// 2       4               1               4               8
// 3       1               2               7               8
// 4       3               3               7               10
// Average waiting time and avegate turn around time is: 4.5 and 7.75 respectively