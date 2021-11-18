MAX_PROCESS = 10
num_of_process = 3
count = 0
remain = 0
time_quantum = 0

execution_time = [0 for i in range(MAX_PROCESS)]
period = [0 for i in range(MAX_PROCESS)]
remain_time = [0 for i in range(MAX_PROCESS)]
deadline = [0 for i in range(MAX_PROCESS)]
remain_deadline = [0 for i in range(MAX_PROCESS)]
burst_time = [0 for i in range(MAX_PROCESS)]
wait_time = [0 for i in range(MAX_PROCESS)]
completion_time = [0 for i in range(MAX_PROCESS)]
arrival_time = [0 for i in range(MAX_PROCESS)]


# collecting details of processes
def get_process_info(selected_algo):

    global MAX_PROCESS, num_of_process, count, remain, time_quantum, execution_time, period
    global remain_time, deadline, remain_deadline, burst_time, wait_time, completion_time, arrival_time

    num_of_process = int(input("Enter total number of processes: "))
    if (num_of_process < 1):
        print("At least one process is required")
        quit()

    if (selected_algo == 2):
        time_quantum = int(input(" Enter time quantum: "))
        if (time_quantum < 1):
            print("Invalid Input: Time quantum should be greater than 0 \n")
            quit()

    for i in range(num_of_process):
        print("\nProcess ", i+1, ":-\n")
        if (selected_algo == 1):
            burst_time[i] = int(input("==> Burst time: "))

        elif selected_algo == 2:
            arrival_time[i] = int(input("==> Arrival time: "))
            burst_time[i] = int(input("==> Burst time: "))
            remain_time[i] = burst_time[i]


# print scheduling sequence
def print_schedule(process_list, cycles):

	global MAX_PROCESS, num_of_process, count, remain, time_quantum, execution_time, period
	global remain_time, deadline, remain_deadline, burst_time, wait_time, completion_time, arrival_time

	print("Scheduling:- \n\n")
	print("Time: ")
	for i in range(cycles):
		if (i < 10): print("| 0", i, " ")
		else: print("| ", i, " ")

	print("|\n")

	for i in range(num_of_process):
		print | ("P[", i+1, "]: ")
		for j in range(cycles):
			if (process_list[j] == i+1): print("|####")
			else: print("|    ")
		print("|\n")

def round_robin(time):

        global MAX_PROCESS, num_of_process, count, remain, time_quantum, execution_time, period
        global remain_time, deadline, remain_deadline, burst_time, wait_time, completion_time, arrival_time

        i = 0
        current_time = 0
        temp_process = 0
        flag = 0
        count = 0
        total_wait = 0
        total_end = 0
        process_list = [0 for i in range(time)]
        process_cycle = [-1 for i in range(time)]
        avg_wait=float(0)
        avg_end=float(0)

        temp_process = num_of_process 
            
        print("\nProcess ID\t\tBurst Time\t Wait Time\t Completion Time\n")
                
        while(temp_process):
                process_cycle[count] = current_time
                count+=1
                if(remain_time[i] <= time_quantum and remain_time[i] > 0):	
                        current_time += remain_time[i]
                        remain_time[i] = 0
                        flag = 1

                elif (remain_time[i] > 0): 
                        remain_time[i] -= time_quantum 
                        current_time += time_quantum


                if(remain_time[i] == 0 and flag == 1):
                        temp_process-=1 
                        completion_time[i] = current_time - arrival_time[i]
                        print("\nProcess[%d]\t\t%d\t\t %d\t\t\t %d", i + 1, burst_time[i], current_time - arrival_time[i] - burst_time[i], current_time - arrival_time[i])
                        total_wait = total_wait + current_time - arrival_time[i] - burst_time[i] 
                        total_end = total_end + current_time - arrival_time[i]
                        flag = 0

                if (i == num_of_process - 1): i = 0

                elif (arrival_time[i + 1] <= current_time): i+=1

                else: i = 0


        avg_wait = float(total_wait) / num_of_process
        avg_end = float(total_end) / num_of_process
        print("\n\nAverage Waiting Time:\t%f", avg_wait) 
        print("\nAverage Completion Time:\t%f\n", avg_end)

        # calculating process list
        proc = 0
        update_process_cycle=[0 for i in range(time)]

        count=0
        for i in range(time):
                if (i == time - 1): update_process_cycle[count] = process_cycle[i]

                elif (process_cycle[i] != process_cycle[i+1]):
                        update_process_cycle[count] = process_cycle[i]
                        count+=1
                
        update_process_cycle[count] = current_time  #adding last completion time    

        for i in range (1, count+2):
                for j in range( update_process_cycle[i]-update_process_cycle[i-1]):
                        process_list[j+update_process_cycle[i-1]] = proc+1
                        
                        proc+=1

                        if (proc == num_of_process): proc = 0
                        while (completion_time[proc] < update_process_cycle[i]):
                                proc+=1
                                if (proc > 4): proc = 0
                
        # printing schedule
        print_schedule(process_list,time)




def main():
	
	print( "-----------------------------\n") 
	print( "CPU Scheduling Algorithms: \n") 
	print( "-----------------------------\n") 
	print( "1. First Come First Serve\n") 
	print( "2. Round Robin\n") 
	
	print( "-----------------------------\n") 
	option=int(input("Select Option: "))
	print( "-----------------------------\n") 

	get_process_info(option)		#collecting processes detail

	observation_time = 0
	for i in range(num_of_process): observation_time+=burst_time[i]

	# if (option == 1):
	#  	first_come_first_serve(observation_time)
	# elif (option == 2):
	round_robin(observation_time)
	

main()
