#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Process {
    int id;
    int burst_time;
    int arrival_time;
    int completion_time = 0;
    int waiting_time = 0;
    int turnaround_time = 0;
};

bool compareByArrivalTime(const Process& a, const Process& b) {
    return a.arrival_time < b.arrival_time;
}

void calculate_turnaround_time(vector<Process>& processes) {
    for (auto& process : processes) {
        process.turnaround_time = process.completion_time - process.arrival_time;
    }
}

void calculate_waiting_time(vector<Process>& processes) {
    for (auto& process : processes) {
        process.waiting_time = process.turnaround_time - process.burst_time;
    }
}

void fcfs(vector<Process> processes) {
    sort(processes.begin(), processes.end(), compareByArrivalTime);

    int time = 0;
    for (auto& process : processes) {
        time = max(time, process.arrival_time);
        process.completion_time = time + process.burst_time;
        time += process.burst_time;
    }

    calculate_turnaround_time(processes);
    calculate_waiting_time(processes);

    cout << "\nFirst Come First Serve Scheduling\n";
    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    for (const auto& process : processes) {
        cout << "P" << process.id << "\t\t" << process.arrival_time << "\t\t" << process.burst_time
             << "\t\t" << process.completion_time << "\t\t" << process.waiting_time << "\t\t" << process.turnaround_time << "\n";
    }
}

void sjn(vector<Process> processes) {
    sort(processes.begin(), processes.end(), compareByArrivalTime);

    int time = 0;
    vector<bool> completed(processes.size(), false);
    int completed_count = 0;

    while (completed_count < processes.size()) {
        int shortest_idx = -1;
        for (size_t i = 0; i < processes.size(); i++) {
            if (!completed[i] && processes[i].arrival_time <= time) {
                if (shortest_idx == -1 || processes[i].burst_time < processes[shortest_idx].burst_time) {
                    shortest_idx = i;
                }
            }
        }

        if (shortest_idx != -1) {
            time = max(time, processes[shortest_idx].arrival_time);
            processes[shortest_idx].completion_time = time + processes[shortest_idx].burst_time;
            time += processes[shortest_idx].burst_time;
            completed[shortest_idx] = true;
            completed_count++;
        } else {
            time++;
        }
    }

    calculate_turnaround_time(processes);
    calculate_waiting_time(processes);

    cout << "\nShortest Job Next Scheduling\n";
    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    for (const auto& process : processes) {
        cout << "P" << process.id << "\t\t" << process.arrival_time << "\t\t" << process.burst_time
             << "\t\t" << process.completion_time << "\t\t" << process.waiting_time << "\t\t" << process.turnaround_time << "\n";
    }
}

void round_robin(vector<Process> processes, int quantum) {
    sort(processes.begin(), processes.end(), compareByArrivalTime);

    queue<int> ready_queue; // Queue to maintain process indices
    vector<int> burst_remaining(processes.size());
    vector<bool> in_queue(processes.size(), false); // Track if a process is already in the queue
    int time = 0; // Current time
    int completed = 0; // Count of completed processes

    // Initialize remaining burst times
    for (size_t i = 0; i < processes.size(); i++) {
        burst_remaining[i] = processes[i].burst_time;
    }

    // Add the first process to the ready queue
    ready_queue.push(0);
    in_queue[0] = true;

    while (completed < processes.size()) {
        if (!ready_queue.empty()) {
            int current = ready_queue.front();
            ready_queue.pop();
            in_queue[current] = false;

            // Process execution
            if (burst_remaining[current] > quantum) {
                time += quantum;
                burst_remaining[current] -= quantum;
            } else {
                time += burst_remaining[current];
                burst_remaining[current] = 0;
                processes[current].completion_time = time; // Update completion time
                completed++;
            }

            // Check for new arrivals during the current execution
            for (size_t i = 0; i < processes.size(); i++) {
                if (processes[i].arrival_time <= time && burst_remaining[i] > 0 && !in_queue[i]) {
                    ready_queue.push(i);
                    in_queue[i] = true;
                }
            }

            // Re-add the current process to the queue if it's not yet completed
            if (burst_remaining[current] > 0) {
                ready_queue.push(current);
                in_queue[current] = true;
            }
        } else {
            // If the queue is empty, jump to the next process arrival time
            for (size_t i = 0; i < processes.size(); i++) {
                if (burst_remaining[i] > 0) {
                    time = max(time, processes[i].arrival_time);
                    ready_queue.push(i);
                    in_queue[i] = true;
                    break;
                }
            }
        }
    }

    // Calculate turnaround time and waiting time
    for (size_t i = 0; i < processes.size(); i++) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

        // Ensure no negative waiting times
        if (processes[i].waiting_time < 0) {
            processes[i].waiting_time = 0;
        }
    }

    // Display results
    cout << "\nRound Robin Scheduling\n";
    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    for (const auto& process : processes) {
        cout << "P" << process.id << "\t\t" << process.arrival_time << "\t\t" << process.burst_time
             << "\t\t" << process.completion_time << "\t\t" << process.waiting_time << "\t\t" << process.turnaround_time << "\n";
    }
}




int main() {
    int choice, quantum;
    do {
        vector<Process> processes;
        int n;

        cout << "Enter the number of processes: ";
        cin >> n;

        for (int i = 0; i < n; i++) {
            Process process;
            process.id = i + 1;
            cout << "Enter arrival time for process P" << process.id << ": ";
            cin >> process.arrival_time;
            cout << "Enter burst time for process P" << process.id << ": ";
            cin >> process.burst_time;
            processes.push_back(process);
        }

        do {
            cout << "\nChoose Scheduling Algorithm:\n";
            cout << "1. First Come First Serve (FCFS)\n";
            cout << "2. Shortest Job Next (SJN)\n";
            cout << "3. Round Robin (RR)\n";
            cout << "4. Enter new set of processes\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    fcfs(processes);
                    break;
                case 2:
                    sjn(processes);
                    break;
                case 3:
                    cout << "Enter time quantum: ";
                    cin >> quantum;
                    round_robin(processes, quantum);
                    break;
                case 4:
                    cout << "Entering new set of processes.\n";
                    break;
                case 5:
                    cout << "Exiting program.\n";
                    break;
                default:
                    cout << "Invalid choice! Please try again.\n";
            }
        } while (choice != 4 && choice != 5);
    } while (choice != 5);

    return 0;
}
