// C++ Implementation of Non-Preemptive Priority Scheduling Algorithm

#include <bits/stdc++.h>
using namespace std;

struct process
{
    int pid, at, bt, pr;
};

bool compa(const process &p1, const process &p2)
{
    return p1.at < p2.at;
}

void calculateTime(process p[], int n, float &avg_tat, float &avg_wt)
{
    sort(p, p + n, compa);
    int ct[n], tat[n], wt[n], rem[n];
    for (int i = 0; i < n; i++)
    {
        rem[i] = p[i].bt;
    }
    vector<int> gantt;
    int complete = 0, mpp, t = p[0].at, priority = p[0].pr;
    while (complete != n)
    {
        for (int i = 0; i < n; i++)
        {
            if (t >= p[i].at and p[i].pr > priority and rem[i])
            {
                priority = p[i].pr;
                mpp = i;
            }
        }

        t += rem[mpp];
        rem[mpp] = 0;
        gantt.push_back(p[mpp].pid);
        ct[mpp] = t;
        complete++;
        priority = INT_MIN;
    }

    for (int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - p[i].at;
        wt[i] = tat[i] - p[i].bt;
        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    avg_tat = avg_tat / n;
    avg_wt = avg_wt / n;

    cout << "Process sequence: ";
    for (auto it : gantt)
    {
        cout << it << " ";
    }
    cout << endl;

    cout << "\t PID \t PRT \t AT \t BT \t TAT \t WT" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "\t" << p[i].pid << "\t" << p[i].pr << "\t" << p[i].at << "\t" << p[i].bt << "\t" << tat[i] << "\t" << wt[i] << endl;
    }

    cout << "Avg turn around time: " << avg_tat << endl;
    cout << "Avg Waiting time: " << avg_wt << endl;
}

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    process p[n];
    cout << "Enter the process id, priority, arrival time and burst time: " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> p[i].pid >> p[i].pr >> p[i].at >> p[i].bt;
    }
    float avg_tat = 0, avg_wt = 0;
    calculateTime(p, n, avg_tat, avg_wt);
    return 0;
}

// Terminal

// Enter the number of processes: 4
// Enter the process id, priority, arrival time and burst time:
// 1 2 0 5
// 2 1 0 4
// 3 4 0 3
// 4 3 0 6
// Process sequence: 3 4 1 2
//          PID     PRT     AT      BT      TAT     WT
//         1       2       0       5       14      9
//         2       1       0       4       18      14
//         3       4       0       3       3       0
//         4       3       0       6       9       3
// Avg turn around time: 11
// Avg Waiting time: 6.5