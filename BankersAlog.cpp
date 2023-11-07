// Write a program to implement Bankers algorithm for safe state

#include <iostream>
using namespace std;

int main()
{
    int np, nr;
    cout << "Enter the number of processes: ";
    cin >> np;
    cout << "Enter the number of resourses: ";
    cin >> nr;

    int avail[nr];
    cout << "Enter the available array: ";
    for (int i = 0; i < nr; i++)
    {
        cin >> avail[i];
    }

    int maxneed[np][nr];
    cout << "Enter maxneed matrix: " << endl;
    for (int i = 0; i < np; i++)
    {
        for (int j = 0; j < nr; j++)
        {
            cin >> maxneed[i][j];
        }
    }

    int allocated[np][nr];
    cout << "Enter allocated matrix: " << endl;
    for (int i = 0; i < np; i++)
    {
        for (int j = 0; j < nr; j++)
        {
            cin >> allocated[i][j];
        }
    }

    int need[np][nr];
    for (int i = 0; i < np; i++)
    {
        for (int j = 0; j < nr; j++)
        {
            need[i][j] = maxneed[i][j] - allocated[i][j];
        }
    }

    bool finish[np] = {0};
    int safeSeq[np];
    int work[nr];

    for (int i = 0; i < nr; i++)
    {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < np)
    {
        bool found = false;
        for (int i = 0; i < np; i++)
        {
            if (finish[i] == 0)
            {
                int j;

                for (j = 0; j < nr; j++)
                {
                    if (need[i][j] > work[j])
                        break;
                }

                if (j == nr)
                {
                    for (int k = 0; k < nr; k++)
                    {
                        work[k] += allocated[i][k];
                    }

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }
        if (found == false)
        {
            cout << "System is not in safe state" << endl;
            return 0;
        }
    }

    cout << "System is in safe state" << endl;
    for (int i = 0; i < np; i++)
    {
        cout << safeSeq[i] << " ";
    }
    cout << endl;
    return 0;
}

// Terminal

// Enter the number of processes: 5
// Enter the number of resourses: 3
// Enter the available array: 3 3 2
// Enter maxneed matrix: 
// 7 5 3
// 3 2 2
// 9 0 2
// 2 2 2
// 4 3 3
// Enter allocated matrix: 
// 0 1 0
// 2 0 0
// 3 0 2
// 2 1 1
// 0 0 2
// System is in safe state
// 1 3 4 0 2
