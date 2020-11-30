#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

typedef struct process {
	int PID;
	int cpu_burst;
	int waiting_time;
}Process;

void FCFS(Process* ps);
void SJF(Process* ps);
void RR(Process* ps);

void create_readyqueue(Process* ps, Process* ps2);	
void print_gantt_waiting(Process* ps);	

void sort_process_arrival(Process* ps);	// 도착순서(PID)대로 정렬
void sort_process_cpuburst(Process* ps);// CPU burst 순 대로 정렬

int main() {
	STARTUPINFO si; //new process의 특성
	PROCESS_INFORMATION pi; // new process/thread에 대한 핸들/식별자

	/*allocate memory*/
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	/*create child process*/

	clock_t start1 = clock();
	CreateProcess(NULL, "C:\\Users\\이태경\\Desktop\\process\\process1.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi); //process1 = Simple loop
	WaitForSingleObject(pi.hProcess, INFINITE);
	clock_t end1 = clock();
	double p1_burst_time = (end1 - start1);
	printf("P1_burst_time : %f\n", p1_burst_time);
	printf("------------------------------------------------\n");

	clock_t start2 = clock();
	CreateProcess(NULL, "C:\\Users\\이태경\\Desktop\\process\\process2.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi); //process2 = Hanoi Top
	WaitForSingleObject(pi.hProcess, INFINITE);
	clock_t end2 = clock(); // 끝난 시간;
	double p2_burst_time = (end2 - start2);
	printf("P2_burst_time : %f\n", p2_burst_time);
	printf("------------------------------------------------\n");

	clock_t start3 = clock();
	CreateProcess(NULL, "C:\\Users\\이태경\\Desktop\\process\\process3.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi); //process3 = Fibonacci
	WaitForSingleObject(pi.hProcess, INFINITE);
	clock_t end3 = clock(); // 끝난 시간;
	double p3_burst_time = (end3 - start3);
	printf("P3_burst_time : %f\n", p3_burst_time);
	printf("------------------------------------------------\n");

	clock_t start4 = clock();
	CreateProcess(NULL, "C:\\Users\\이태경\\Desktop\\process\\process4.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi); //process4 = Double loop
	WaitForSingleObject(pi.hProcess, INFINITE);
	clock_t end4 = clock(); // 끝난 시간;
	double p4_burst_time = (end4 - start4);
	printf("P4_burst_time : %f\n", p4_burst_time);
	printf("------------------------------------------------\n");

	clock_t start5 = clock();
	CreateProcess(NULL, "C:\\Users\\이태경\\Desktop\\process\\process5.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi); //process5 = Factorial
	WaitForSingleObject(pi.hProcess, INFINITE);
	clock_t end5 = clock(); // 끝난 시간;
	double p5_burst_time = (end5 - start5);
	printf("P5_burst_time : %f\n", p5_burst_time);
	printf("------------------------------------------------\n");

	CloseHandle(pi.hProcess); // new process에 대한 핸들 닫기
	CloseHandle(pi.hThread); // new threead에 대한 핸들 닫기

	Process ps[5];
	Process ready_queue[5];

	ps[0].PID = 1;
	ps[0].cpu_burst = p1_burst_time;
	ps[1].PID = 2;
	ps[1].cpu_burst = p2_burst_time;
	ps[2].PID = 3;
	ps[2].cpu_burst = p3_burst_time;
	ps[3].PID = 4;
	ps[3].cpu_burst = p4_burst_time;
	ps[4].PID = 5;
	ps[4].cpu_burst = p5_burst_time;

	printf("\n-------------------------------------- FCFS ----------------------------------------");
	create_readyqueue(ps, ready_queue);
	FCFS(ready_queue);
	print_gantt_waiting(ready_queue);


	printf("------------------------------ Nonpreemptive SJF ------------------------------------");
	create_readyqueue(ps, ready_queue);
	SJF(ready_queue);
	print_gantt_waiting(ready_queue);

	printf("--------------------------------------- RR -----------------------------------------");
	create_readyqueue(ps, ready_queue);
	RR(ready_queue);

	system("PAUSE"); // cmd창이 꺼지는 것을 방지하기 위함.
	return 0;
}

void create_readyqueue(Process* ps, Process* ps2) {

	int i;
	for (i = 0; i < 5; i++)
	{
		ps2[i].PID = ps[i].PID;
		ps2[i].cpu_burst = ps[i].cpu_burst;
		ps2[i].waiting_time = ps[i].waiting_time;
	}
}

void FCFS(Process* ps) {
	sort_process_arrival(ps);
	int i, j = 0;
	ps[0].waiting_time = 0;
	//calculate waiting time
	for (i = 1; i < 5; i++)
	{
		ps[i].waiting_time = 0;
		for (j = 0; j < i; j++)
			ps[i].waiting_time += ps[j].cpu_burst;
	}
}

void SJF(Process* ps) {
	sort_process_cpuburst(ps);
	int i, j;
	ps[0].waiting_time = 0;
	//calculate waiting time
	for (i = 1; i < 5; i++)
	{
		ps[i].waiting_time = 0;
		for (j = 0; j < i; j++)
			ps[i].waiting_time += ps[j].cpu_burst;
	}
}

void RR(Process* ps) {
	int i, index = 0;
	int order_queue[500];				// RR에서 다음으로 할당 될 프로세스의 PID를 담은 큐
	int order[5] = { 1,2,3,4,5 };		// 큐에 저장할 PID
	int head = 0, tail = 0;				// 큐의 가장 처음(head)과 맨 끝(tail)
	int process_remain_time[6];
	int total_remain_time = 0, total_run_time = 0, avg_waiting_time = 0;
	int arrival_time[5];
	int tmp_cpu_burst = 0;
	int time_slice = 50;

	sort_process_arrival(ps);
	// 남은 시간을 확인하기 위해 process_remain_time을 입력받은 cpu_burst로 초기화
	process_remain_time[0] = 0;
	for (i = 0; i < 5; i++) {
		process_remain_time[i + 1] = ps[i].cpu_burst;
		total_remain_time += ps[i].cpu_burst;
	}

	for (i = 0; i < 5; i++)
	{
		ps[i].waiting_time = 0;
	}
	for (i = 0; i < 5; i++) {
		order_queue[tail++] = order[i];
	}

	// 도착시간
	arrival_time[0] = 0;
	for (i = 1; i < 5; i++) {
		if (ps[i - 1].cpu_burst <= time_slice) {
			arrival_time[i] = arrival_time[i - 1] + ps[i - 1].cpu_burst;
		}
		else {
			arrival_time[i] = arrival_time[i - 1] + time_slice;
		}
	}
	printf("\n");
	while (1) {
		index = order_queue[head];
		if (index <= 0) {
			break;
		}

		if (process_remain_time[index] <= time_slice && process_remain_time[index] > 0 && index) {

			//cpu burst만큼 해당 프로세스 출력
			for (i = 0; i < process_remain_time[index]; i++) {
				printf("P%d ", ps[index - 1].PID);
				total_run_time += 1;
			}

			//프로세스남은시간 0으로 초기화
			process_remain_time[index] = 0;
			//큐 헤드 += 1
			head += 1;
			printf(": ");
			printf("%d\n", total_run_time);
			total_remain_time -= process_remain_time[index];
		}
		else {
			//타임 퀀텀만큼 해당 프로세스 출력
			
			for (i = 0; i < time_slice; i++) {
				printf("P%d ", ps[index - 1].PID);
				total_run_time += 1;
			}
			
			//프로세스 남은시간 -= time quantum
			process_remain_time[index] -= time_slice;

			//큐 헤드 += 1, 큐 테일에 해당 프로세스 번호 삽입
			order_queue[tail] = index;
			head += 1;
			tail += 1;
			total_remain_time -= time_slice;
			printf(": ");
			printf("%d\n", total_run_time);
		}

		if (total_remain_time <= 0) {
			break;
		}
		
	}
}

void sort_process_arrival(Process* ps) {
	Process tmp_process;
	int i, j;

	for (i = 4; i > 0; i--) {
		for (j = 0; j < i; j++) {
			if (ps[j].PID > ps[j + 1].PID) {
				tmp_process = ps[j + 1];
				ps[j + 1] = ps[j];
				ps[j] = tmp_process;
			}
		}
	}
}

void sort_process_cpuburst(Process* ps) {
	Process tmp_process;
	int i, j;

	for (i = 4; i > 0; i--) {
		for (j = 0; j < i; j++) {
			if (ps[j].cpu_burst > ps[j + 1].cpu_burst) {
				tmp_process = ps[j + 1];
				ps[j + 1] = ps[j];
				ps[j] = tmp_process;
			}
		}
	}
}

void print_gantt_waiting(Process* ps) {
	int total_time = 0;
	int i = 0;
	double avg_waiting_time = 0;
	int a[500];
	int idx = 0;

	for (i = 0; i < 5; i++) {
		total_time = total_time + ps[i].cpu_burst;
	}

	printf("\n");
	for (i = 0; i < total_time; i++) {
		a[i] = ps[idx].PID;
		printf("P%d ", a[i]);
		ps[idx].cpu_burst -= 1;
		if (ps[idx].cpu_burst == 0) {
			idx += 1;
			
			printf(": ");
			printf("%d\n", i + 1);
		}
	}

	sort_process_arrival(ps);
	printf("waiting time : ");

	for (i = 0; i < 5; i++) {
		printf("P%d = %d(ms), ", i + 1, ps[i].waiting_time);
		avg_waiting_time += ps[i].waiting_time;
	}
	printf("\n");
	printf("average waiting time : %f(ms)\n\n", avg_waiting_time / 5);

}
