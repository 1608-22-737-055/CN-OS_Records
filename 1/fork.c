#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    // Create a new process
    pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child Process:\n");
        printf("PID: %d, Parent PID: %d\n", getpid(), getppid());
        printf("Child process is executing...\n");
    } else {
        // Parent process
        printf("Parent Process:\n");
        printf("PID: %d, Child PID: %d\n", getpid(), pid);
        printf("Parent process is waiting for the child to finish...\n");
        
        // Wait for the child process to complete
        wait(NULL);
        printf("Child process finished. Parent process resumes.\n");
    }

    printf("Process %d exiting...\n", getpid());
    return 0;
}
