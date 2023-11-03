// Write a program to implement first come first serve cpu scheduling algorithm (FCFS) with arrival time.

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    int pid[n], at[n], bt[n], tat[n], wt[n], ct[n];
    cout << "Enter processId, Arrival time and Burst time of the program: " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> pid[i] >> at[i] >> bt[i];
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (at[j] > at[j + 1])
            {
                swap(pid[j], pid[j + 1]);
                swap(at[j], at[j + 1]);
                swap(bt[j], bt[j + 1]);
            }
        }
    }

    int temp = at[0];
    for (int i = 0; i < n; i++)
    {
        temp += bt[i];
        ct[i] = temp;
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }
    float avg_tat = 0, avg_wt = 0;
    for (int i = 0; i < n; i++)
    {
        avg_tat += tat[i];
        avg_wt += wt[i];
    }
    avg_tat = avg_tat / (float)n;
    avg_wt = avg_wt / (float)n;

    cout << "\t PId \t AT \t BT \t CT \t TAT \t WT" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "\t" << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
    }
    cout << endl;
    cout << "Average turn around time and average waiting time are respectively: " << avg_tat << " and " << avg_wt << endl;
    return 0;
}

// Terminal

// Enter the number of processes: 4
// Enter processId, Arrival time and Burst time of the program:
// 1 0 10
// 2 1 6
// 3 3 2
// 4 5 4
//          PId     AT      BT      CT      TAT     WT
//         1       0       10      10      10      0
//         2       1       6       16      15      9
//         3       3       2       18      15      13
//         4       5       4       22      17      13

// Average turn around time and average waiting time are respectively: 14.25 and 8.75
