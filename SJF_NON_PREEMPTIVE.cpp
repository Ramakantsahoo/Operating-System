// Write a program to implement non preemptive shortest job first (SJF) algorithm.

#include <iostream>
using namespace std;

#define pid 0
#define at 1
#define bt 2
#define ct 3
#define tat 4
#define wt 5

void arrivalSort(int data[][6], int n, int param)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (data[j][param] > data[j + 1][param])
            {
                for (int k = 0; k < 6; k++)
                {
                    swap(data[j][k], data[j + 1][k]);
                }
            }
        }
    }
}

void calculateTime(int data[][6], int n, float &av_tat, float &av_wt)
{
    arrivalSort(data, n, at);
    int temp, val;
    float taat = 0, wwt = 0;

    for (int i = 0; i < n; i++)
    {
        if (i)
            temp = data[i-1][ct];
        else
            temp = data[i][at];
        int low = data[i][bt];
        for (int j = i; j < n; j++)
        {
            if (temp >= data[j][at] and low >= data[j][bt])
            {
                low = data[j][bt];
                val = j;
            }
        }
        data[val][ct] = temp + data[val][bt];
        data[val][tat] = data[val][ct] - data[val][at];
        data[val][wt] = data[val][tat] - data[val][bt];

        taat += data[val][tat];
        wwt += data[val][wt];
        for (int k = 0; k < 6; k++)
        {
            swap(data[val][k], data[i][k]);
        }
    }

    av_tat = taat / (float)n;
    av_wt = wwt / (float)n;
}

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    int data[n][6];
    cout << "Enter process id, arrival time and burst time of the processes: " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> data[i][pid] >> data[i][at] >> data[i][bt];
    }
    float av_tat, av_wt;
    calculateTime(data, n, av_tat, av_wt);
    cout << "\t PID \t AT \t BT \t CT \t TAT \t WT " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "\t" << data[i][pid] << "\t" << data[i][at] << "\t" << data[i][bt] << "\t" << data[i][ct] << "\t" << data[i][tat] << "\t" << data[i][wt] << endl;
    }
    cout<<endl;
    cout << "Average turn around time and average waiting time is: " << av_tat << " and " << av_wt << endl;
}

// Terminal

// Enter the number of processes: 4
// Enter process id, arrival time and burst time of the processes:
// 1 1 3
// 2 2 4
// 3 1 2
// 4 4 4
//          PID     AT      BT      CT      TAT     WT
//         3       1       2       3       2       0
//         1       1       3       6       5       2
//         4       4       4       10      6       2
//         2       2       4       14      12      8

// Average turn around time and average waiting time is: 6.25 and 3