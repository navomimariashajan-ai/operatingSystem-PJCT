#include <stdio.h>
#include <string.h>

struct Process {
    char pid[5];
    int at, bt, pr;
    int rt;   // remaining time
    int ct;   // completion time
    int wt;   // waiting time
    int tat;  // turnaround time
};

int main() {
    int n, i, time = 0, completed = 0;
    struct Process p[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input
    printf("Enter Process ID,AT,BT,PR:\n ");
    for(i = 0; i < n; i++) {
        scanf("%s %d %d %d", p[i].pid, &p[i].at, &p[i].bt, &p[i].pr);
        p[i].rt = p[i].bt; // initialize remaining time
    }

    int min_pr, idx;

    // Scheduling
    while(completed < n) {
        min_pr = 9999;
        idx = -1;

        for(i = 0; i < n; i++) {
            if(p[i].at <= time && p[i].rt > 0) {
                if(p[i].pr < min_pr) {
                    min_pr = p[i].pr;
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            p[idx].rt--;   // execute process
            time++;

            if(p[idx].rt == 0) {
                p[idx].ct = time;
                completed++;

                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
            }
        } else {
            time++; // idle CPU
        }
    }

    float total_wt = 0, total_tat = 0;

    printf("\nWaiting Time:\n");
    for(i = 0; i < n; i++) {
        printf("%s  %d\n", p[i].pid, p[i].wt);
        total_wt += p[i].wt;
    }

    printf("\nTurnaround Time:\n");
    for(i = 0; i < n; i++) {
        printf("%s  %d\n", p[i].pid, p[i].tat);
        total_tat += p[i].tat;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
