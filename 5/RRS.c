// RRS- Round Robin Scheduling
#include <stdio.h>

int main() {
    int n;

    printf("Enter Total Number of Processes: ");
    scanf("%d", &n);

    int wait_time = 0, ta_time = 0, arr_time[n], burst_time[n], temp_burst_time[n];
    int x = n;

    for (int i = 0; i < n; i++) {
        printf("Enter Details of Process %d \n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &arr_time[i]);
        printf("Burst Time: ");
        scanf("%d", &burst_time[i]);
        temp_burst_time[i] = burst_time[i];
    }

    int time_slot;
    printf("Enter Time Slot: ");
    scanf("%d", &time_slot);

    int total = 0, counter = 0, i;
    printf("Process ID\tBurst Time\tTurnaround Time\tWaiting Time\n");

    for (total = 0, i = 0; x != 0;) {
        if (temp_burst_time[i] <= time_slot && temp_burst_time[i] > 0) {
            total += temp_burst_time[i];
            temp_burst_time[i] = 0;
            counter = 1;
        } else if (temp_burst_time[i] > 0) {
            temp_burst_time[i] -= time_slot;
            total += time_slot;
        }

        if (temp_burst_time[i] == 0 && counter == 1) {
            x--;
            printf("Process No %d\t\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], total - arr_time[i], total - arr_time[i] - burst_time[i]);
            wait_time += total - arr_time[i] - burst_time[i];
            ta_time += total - arr_time[i];
            counter = 0;
        }

        if (i == n - 1) {
            i = 0;
        } else if (arr_time[i + 1] <= total) {
            i++;
        } else {
            i = 0;
        }
    }

    float average_wait_time = (float)wait_time / n;
    float average_turnaround_time = (float)ta_time / n;

    printf("\nAverage Waiting Time: %.2f", average_wait_time);
    printf("\nAverage Turnaround Time: %.2f\n", average_turnaround_time);

    return 0;
}
