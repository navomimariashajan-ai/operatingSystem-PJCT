#include <stdio.h>
#include <string.h>

struct Process {
    char id[10];
    int at, bt, pr, remaining_bt;
    int wt, tat, ct;
};

int main() {
    int n;
    scanf("%d", &n);
    struct Process p[n];

    for (int i = 0; i < n; i++) {
        scanf("%s %d %d %d", p[i].id, &p[i].at, &p[i].bt, &p[i].pr);
        p[i].remaining_bt = p[i].bt;
    }

    int completed = 0, current_time = 0;
    int is_completed[n];
    for (int i = 0; i < n; i++) is_completed[i] = 0;

    while (completed != n) {
        int idx = -1;
        int min_pr = 1e9;

        // Find process with highest priority (lowest value) available at current_time
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && !is_completed[i]) {
                if (p[i].pr < min_pr) {
                    min_pr = p[i].pr;
                    idx = i;
                }
                // If priorities are equal, pick the one that arrived first (FCFS)
                else if (p[i].pr == min_pr) {
                    if (p[idx] != NULL && p[i].at < p[idx].at) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            p[idx].remaining_bt--;
            current_time++;

            if (p[idx].remaining_bt == 0) {
                p[idx].ct = current_time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                is_completed[idx] = 1;
                completed++;
            }
        } else {
            current_time++;
        }
    }

    float total_wt = 0, total_tat = 0;
    printf("Waiting Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s  %d\n", p[i].id, p[i].wt);
        total_wt += p[i].wt;
    }

    printf("Turnaround Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s  %d\n", p[i].id, p[i].tat);
        total_tat += p[i].tat;
    }

    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
