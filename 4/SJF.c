
#include <stdio.h>

int main() {
    int n, bt[20], p[20], wt[20], tat[20], total = 0;
    float avg_wt, avg_tat;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("p%d: ", i + 1);
        scanf("%d", &bt[i]);
        p[i] = i + 1;
    }

    // Sorting processes based on burst time
    for (int i = 0; i < n - 1; i++) {
        int pos = i;
        for (int j = i + 1; j < n; j++) {
            if (bt[j] < bt[pos])
                pos = j;
        }

        int temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }

    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
        total += wt[i];
    }

    avg_wt = (float)total / n;

    // Calculating Turnaround Time
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        total += tat[i];
    }

    avg_tat = (float)total / n;

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("p%d\t\t%d\t\t%d\t\t%d\n", p[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);

    return 0;
}

