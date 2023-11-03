// Write a program to implement Preemptive shortest job first (SJF) algorithm.

#include <bits/stdc++.h>
using namespace std;

struct process
{
    int at, bt, pid; // at = arrival time , bt = burst time , ct = completion time
};

void findAvgWT(process p[], int n, int wt[])
{
    int rem[n];
    for (int i = 0; i < n; i++)
    {
        rem[i] = p[i].bt;
    }
    vector<int> gantt;
    bool check = false;
    int complete = 0, minn = INT_MAX, t = 0, shortest = 0;

    while (complete != n)
    {
        for (int i = 0; i < n; i++)
        {
            if (rem[i] > 0 and rem[i] < minn and t >= p[i].at)
            {
                minn = rem[i];
                shortest = i;
                check = true;
            }
        }
        if (check == false)
        {
            gantt.push_back(0);
            t++;
            continue;
        }

        minn = --rem[shortest];

        if (rem[shortest] == 0)
        {
            minn = INT_MAX;
            complete++;
            check = false;
            wt[shortest] = t + 1 - p[shortest].bt - p[shortest].at;

            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }

        gantt.push_back(p[shortest].pid);
        t++;
    }
    cout << "Process Sequence: ";
    for (auto &x : gantt)
    {
        cout << x << " ";
    }
    cout << endl;
}

void findAvgTAT(process p[], int n, int tat[], int wt[])
{
    for (int i = 0; i < n; i++)
    {
        tat[i] = p[i].bt + wt[i];
    }
}

void calculateAvgTime(process p[], int n)
{
    int wt[n], tat[n];

    findAvgWT(p, n, wt);
    findAvgTAT(p, n, tat, wt);
    float avgWt = 0, avgTat = 0;
    cout << "\t PID \t AT \t BT \t WT \t TAT" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "\t" << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t" << wt[i] << "\t" << tat[i] << endl;
        avgWt += wt[i];
        avgTat += tat[i];
    }
    avgTat = avgTat / n;
    avgWt = avgWt / n;
    cout << "\nAverage Waiting Time = " << avgWt << endl;
    cout << "Average Turnaround Time = " << avgTat << endl;
}

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    process p[n];
    cout << "Enter the process id, arrival time and burst time for the processes: " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> p[i].pid >> p[i].at >> p[i].bt;
    }

    calculateAvgTime(p, n);
    return 0;
}

// Terminal

// Enter the number of processes: 4
// Enter the process id, arrival time and burst time for the processes:
// 1 0 8
// 2 1 4
// 3 2 9
// 4 3 5
// Process Sequence: 1 2 2 2 2 4 4 4 4 4 1 1 1 1 1 1 1 3 3 3 3 3 3 3 3 3
//          PID     AT      BT      WT      TAT
//         1       0       8       9       17
//         2       1       4       0       4
//         3       2       9       15      24
//         4       3       5       2       7

// Average Waiting Time = 6.5
// Average Turnaround Time = 13