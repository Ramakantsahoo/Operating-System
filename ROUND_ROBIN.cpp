// Write a program to implement round robin algorithm.

#include <bits/stdc++.h>
using namespace std;

struct process
{
    bool inQueue = false;
    int pid, at, bt, idx;
};

bool compa(const process &p1, const process &p2)
{
    return p1.at < p2.at;
}

void calculateTime(process p[], int n, int q, float &avg_tat, float &avg_wt)
{
    sort(p, p + n, compa);
    int ct[n], tat[n], wt[n], rem[n];
    for (int i = 0; i < n; i++)
    {
        rem[i] = p[i].bt;
        p[i].idx = i;
    }
    vector<int> gantt;
    queue<process> rq;
    int i = 0, t = p[0].at;
    process curr;
    rq.push(p[0]);
    p[0].inQueue = true;

    while (!rq.empty())
    {
        curr = rq.front();
        rq.pop();
        curr.inQueue = false;
        i = curr.idx;

        for (int j = 0; j < n; j++)
        {
            if (t + min(rem[i], q) >= p[j].at and rem[i] and p[j].inQueue == false)
            {
                p[j].inQueue = true;
                rq.push(p[j]);
            }
        }
        if (rem[i] < q)
        {
            t += rem[i];
            rem[i] = 0;
            ct[i] = t;
        }
        else
        {
            t += q;
            rem[i] = rem[i] - q;
            if (!rem[i])
            {
                ct[i] = t;
            }
            else
            {
                curr.inQueue = true;
                rq.push(p[i]);
            }
        }
        gantt.push_back(p[i].pid);
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

    cout << "\t PID \t AT \t BT \t CT \t TAT \t WT" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "\t" << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
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
        cin >> p[i].pid >> p[i].at >> p[i].bt;
    }
    int q;
    cout << "Enter the time quantum: " << endl;
    cin >> q;
    float avg_tat = 0, avg_wt = 0;
    calculateTime(p, n, q, avg_tat, avg_wt);
    return 0;
}

// Terminal

// Enter the number of processes: 4
// Enter the process id, priority, arrival time and burst time:
// 1 0 5
// 2 1 4
// 3 2 2
// 4 4 1
// Enter the time quantum:
// 2
// Process sequence: 1 2 3 1 4 2 1
//          PID     AT      BT      CT      TAT     WT
//         1       0       5       12      12      7
//         2       1       4       11      10      6
//         3       2       2       6       4       2
//         4       4       1       9       5       4
// Avg turn around time: 7.75
// Avg Waiting time: 4.75