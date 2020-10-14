#include <stdio.h>
#include <windows.h>

int main(void)
{
	STARTUPINFO si; //new process의 특성
	PROCESS_INFORMATION pi; // new process/thread에 대한 핸들/식별자

	/*allocate memory*/
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	/*create child process*/
	if (!CreateProcess(NULL, "C:\\WINDOWS\\system32\\mspaint.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{ // use command line, command, don't inherit process handle, don't inherit thread handle, disable handle inheritance, no creation flags,
		// use parent's environment block, use parent's existing directory
		fprintf(stderr, "Create Process Failed");
		return -1;
	}
	/*parent will wait for the child to complte */
	WaitForSingleObject(pi.hProcess, INFINITE);
	printf("Child Complete");

	/*close handles*/
	CloseHandle(pi.hProcess); // new process에 대한 핸들 닫기
	CloseHandle(pi.hThread); // new threead에 대한 핸들 닫기

}