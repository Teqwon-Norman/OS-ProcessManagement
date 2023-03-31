#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define MAX_ITERATIONS 30
#define BUFFER_SIZE 100

void ChildProcess(void);
void ParentProcess(void);
void WaitForBothChildren(void);

int main() {
  pid_t pid1 = fork();

  if (pid1 < 0) {
    perror("Error: Failed to create first child process.\n");
    exit(1);

  } else if (pid1 == 0) {
    ChildProcess(); // first child process
  }

  pid_t pid2 = fork();
  if (pid2 < 0) {
    perror("Error: Failed to create second child process.\n");
    exit(1);

  } else if (pid2 == 0) {
    ChildProcess(); // second child process
  }

  ParentProcess(); // parent process
  return 0;
}

void ChildProcess(void) {
  int i, sleep_time;
  char message[BUFFER_SIZE];
  srandom(time(NULL));

  for (i = 0; i < random() % MAX_ITERATIONS; i++) {
    sleep_time = random() % 11;

    snprintf(message, 100, "Child Pid: %d is going to sleep!\n", getpid());
    printf("%s", message);
    sleep(sleep_time);
    snprintf(message, 100, "Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
    printf("%s", message);
  }

  exit(0);
}

void ParentProcess(void) {
  WaitForBothChildren();
  printf("Parent process has terminated.\n");
}

void WaitForBothChildren(void) {
  int status1, status2;
  pid_t pid1, pid2;

  pid1 = wait(&status1);
  printf("Child Pid: %d has completed.\n", pid1);
  printf("\n");

  pid2 = wait(&status2);
  printf("Child Pid: %d has completed.\n", pid2);
  printf("\n");
}
