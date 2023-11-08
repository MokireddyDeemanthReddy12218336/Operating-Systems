/*
Sudesh Sharma is a Linux expert who wants to have an online system where he can handle student queries. 
Since there can be multiple requests at any time he wishes to dedicate a fixed amount of time to every request
 so that everyone gets a fair share of his time. He will log into the system from 10am to 12am only. He wants to
  have separate requests queues for students and faculty. Implement a strategy for the same. The summary at the
   end of the session should include the total time he spent on handling queries and average query time.
*/

#include <stdio.h>

#define MAX_PROCESSES 20

struct Process {
    int process_id;
    char name[20];
    int arrival_time;
    int burst_time;
    int remaining_time;
};
float x,y,a;


void roundRobin(struct Process processes[], int n, int time_quantum) {
    int total_burst_time = 0;
    int current_time = 0;

    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        total_burst_time += processes[i].burst_time;
    }
     x=total_burst_time;
     y=n;

    while (total_burst_time > 0 && current_time <= 120) {
        int process_executed = 0; 
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                int execute_time = (processes[i].remaining_time < time_quantum) ? processes[i].remaining_time : time_quantum;
                if (current_time + execute_time <= 120) {
                    processes[i].remaining_time -= execute_time;
                    total_burst_time -= execute_time;
                    current_time += execute_time;
                    printf("Process %d (%s) is being handled for %d units of time. Current time: %d\n", processes[i].process_id, processes[i].name, execute_time, current_time);
                    process_executed = 1;
                    a=current_time;
                } else {
                    printf("Process %d (%s) cannot be handled to avoid exceeding the time limit. Current time: %d\n", processes[i].process_id, processes[i].name, current_time);
                    break; 
                }
            }
        }
        if (!process_executed) {
            current_time++;
            break;
        }
    }
}


int main() {
    int n;
    printf("Enter the number of processes (up to 20): ");
    scanf("%d", &n);

    if (n < 1 || n > MAX_PROCESSES) {
        printf("Invalid number of processes. Please enter a number between 1 and 20.\n");
        return 1; 
    }


    struct Process processes[MAX_PROCESSES];

    printf("Enter process details (name, arrival time, and burst time) for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Process %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", processes[i].name);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
    }

    int time_quantum;
    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    roundRobin(processes, n, time_quantum);
    
    printf("The total time taken for handling the queries is %f\n",a);
    printf("The average time taken for handling the queries is %2f\n",a/y);
    

    return 0;
}
