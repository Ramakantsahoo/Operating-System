// Write a program to detect deadlock

#include <iostream>
using namespace std;
int main()
{
    int p, r;
    cout << "enter no. of process and resource type :" << endl;
    cin >> p >> r;
    int allo[p][r], request[p][r];
    cout << "enter allocated resources of each resource type for each process :" << endl;
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
        {
            cin >> allo[i][j];
        }
    }
    cout << "enter requested resources of each resource type for each process :" << endl;
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
        {
            cin >> request[i][j];
        }
    }
    int total[r];
    cout << "total no.of instances available for each resource type :" << endl;
    for (int i = 0; i < r; i++)
    {
        cin >> total[i];
    }

    int available[r], sum;
    for (int i = 0; i < r; i++)
    {
        sum = 0;
        for (int j = 0; j < p; j++)
        {
            sum += allo[j][i];
        }
        available[i] = total[i] - sum;
    }
    bool finish[p] = {0};
    bool found;
    int safe[p];
    int count = 0, flag = 1;
    while (count < p)
    {
        found = false;
        for (int i = 0; i < p; i++)
        {
            if (finish[i] == 0)
            {
                int j;
                for (j = 0; j < r; j++)
                {
                    if (request[i][j] > available[j])
                        break;
                }
                if (j == r)
                {
                    for (int k = 0; k < r; k++)
                    {
                        available[k] += allo[i][k];
                    }
                    finish[i] = 1;
                    safe[count++] = i;
                    found = true;
                }
            }
        }
        if (found == false)
        {
            cout << "it is in deadlock" << endl;
            for (int i = 0; i < p; i++)
            {
                if (finish[i] == 0)
                {
                    cout << i << " ";
                }
            }
            cout << endl;
            flag = 0;
            break;
        }
    }
    if (flag == 1)
    {
        cout << "safe sequence of processes are:";
        for (int i = 0; i < p; i++)
            cout << safe[i] << " ";
    }
    return 0;
}

// Terminal

// enter no. of process and resource type :
// 5 3
// enter allocated resources of each resource type for each process :
// 0 1 0
// 2 0 0
// 3 0 3
// 2 1 1
// 0 0 2
// enter requested resources of each resource type for each process :
// 0 0 0
// 2 0 2
// 0 0 0
// 1 0 0
// 0 0 2
// total no.of instances available for each resource type :
// 7 2 6
// safe sequence of processes are:0 2 3 4 1