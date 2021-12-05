# CPU_Scheduling Algorithm
## How to run the Code

### 1. FCFS
For first come first serve algorithm, just run the following command:
```
    g++ -o fcfs fcfs.cpp
    ./fcfs
```
Then insert, number of processes and for each process insert Arrival Time and Burst Time for all processes.

The output will be a table showing Wait Time (wt), Turn Around Time (tat) and Completion Time (ct).

### 2. Round Robin
For Round Robin algorithm, just run the following command:
```
    g++ -o rr rr.cpp
    ./rr
```
Then insert, number of processes, then Time Quantum and for each process insert Arrival Time and Burst Time for all processes.

The output will be a table showing Wait Time (wt), Turn Around Time (tat) and Completion Time (ct).

### 3. Proposed Algoritm
For Round Robin algorithm, just run the following command:
```
    g++ -o proposed_algo proposed_algo.cpp
    ./proposed_algo
```
Then insert, number of processes, and for each process insert Arrival Time and Burst Time for all processes.

The output will be a table showing Wait Time (wt), Turn Around Time (tat) and Completion Time (ct).