# CPU-Scheduling-Algorithms-Simulator

## Overview
This project implements a CPU Scheduling Simulator in C++ that allows users to simulate three common CPU scheduling algorithms:
1. First Come First Serve (FCFS)
2. Shortest Job Next (SJN)
3. Round Robin (RR)

The simulator takes input from the user, such as arrival and burst times for processes, and calculates various metrics like:
- Completion Time
- Waiting Time
- Turnaround Time

The program provides a menu-driven interface to execute the chosen scheduling algorithm or enter a new set of processes.

---

## Features
- **FCFS Scheduling**: Processes are executed in the order they arrive.
- **SJN Scheduling**: Processes with the shortest burst time are executed first.
- **Round Robin Scheduling**: Processes are executed in a cyclic order with a specified time quantum.
- **Dynamic Input**: Users can input a custom set of processes.
- **Metrics Calculation**: The program computes and displays completion time, waiting time, and turnaround time for all processes.

---

## How to Run
### Prerequisites:
- A C++ compiler (e.g., GCC, Clang, or Visual Studio).
- Basic knowledge of how to compile and execute C++ programs.

### Steps:
1. Copy the source code into a file named `cpu_scheduling.cpp`.
2. Compile the program using the following command:
   ```
   g++ -o cpu_scheduling cpu_scheduling.cpp
   ```
3. Run the executable:
   ```
   ./cpu_scheduling
   ```
4. Follow the on-screen instructions to input processes and choose scheduling algorithms.

---

## User Input Format
1. Enter the number of processes.
2. For each process, input:
   - Arrival time
   - Burst time

### Menu Options
After entering the processes, you can choose from the following options:
- **1**: Execute FCFS Scheduling.
- **2**: Execute SJN Scheduling.
- **3**: Execute Round Robin Scheduling (requires additional input for time quantum).
- **4**: Enter a new set of processes.
- **5**: Exit the program.

---

## Example
### Input:
```
Enter the number of processes: 3
Enter arrival time for process P1: 0
Enter burst time for process P1: 5
Enter arrival time for process P2: 1
Enter burst time for process P2: 3
Enter arrival time for process P3: 2
Enter burst time for process P3: 8

Choose Scheduling Algorithm:
1. First Come First Serve (FCFS)
2. Shortest Job Next (SJN)
3. Round Robin (RR)
4. Enter new set of processes
5. Exit
Enter your choice: 1
```

### Output:
```
First Come First Serve Scheduling
Process	Arrival Time	Burst Time	Completion Time	Waiting Time	Turnaround Time
P1		   0		           5		          5		             0		           5
P2		   1		           3		          8		             4		           7
P3		   2		           8		          16		           6		           14
```

---

## Code Structure
- **`Process` Structure**: Stores process ID, arrival time, burst time, completion time, waiting time, and turnaround time.
- **Helper Functions**:
  - `calculate_turnaround_time`: Calculates turnaround time for each process.
  - `calculate_waiting_time`: Calculates waiting time for each process.
  - `compareByArrivalTime`: Sorts processes based on arrival time.
- **Scheduling Algorithms**:
  - `fcfs`: Implements First Come First Serve scheduling.
  - `sjn`: Implements Shortest Job Next scheduling.
  - `round_robin`: Implements Round Robin scheduling.
- **Main Function**: Handles user input, menu navigation, and calls appropriate scheduling functions.

---

## Notes
- The program assumes all input values are valid integers.
- In SJN and Round Robin algorithms, processes arriving later will wait for earlier processes to complete if the CPU is idle.
- Negative waiting times are adjusted to zero.
- Round Robin requires the user to specify a time quantum.

---

## Future Enhancements
- Add support for preemptive algorithms like Preemptive SJF or Priority Scheduling.
- Include visualization of Gantt charts for better understanding.
- Allow input via file or graphical interface.

---



