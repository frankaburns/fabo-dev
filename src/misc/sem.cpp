#include <iostream>
#include <fcntl.h>   // For O_CREAT, O_EXCL
#include <sys/stat.h> // For mode constants
#include <semaphore.h>
#include <unistd.h>  // For fork
#include <sys/wait.h> // For wait
#include <cerrno>    // For errno

const char* SEM_NAME = "/my_semaphore";

void child_process() {
    // Open the existing semaphore
    sem_t *sem = sem_open(SEM_NAME, 0); // 0 means open existing
    if (sem == SEM_FAILED) {
        perror("child sem_open");
        exit(EXIT_FAILURE);
    }

    std::cout << "Child: Attempting to acquire semaphore." << std::endl;
    if (sem_wait(sem) == -1) { // Wait (P operation)
        perror("child sem_wait");
    }
    std::cout << "Child: Acquired semaphore, doing work." << std::endl;
    // Critical section simulated with sleep
    sleep(2);
    std::cout << "Child: Releasing semaphore." << std::endl;

    if (sem_post(sem) == -1) { // Post (V operation)
        perror("child sem_post");
    }
    if (sem_close(sem) == -1) {
        perror("child sem_close");
    }
    exit(EXIT_SUCCESS);
}

int main() {
    sem_t *sem;
    // Create/open a named semaphore with an initial value of 1 (binary semaphore)
    sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0644, 1);
    if (sem == SEM_FAILED) {
        perror("parent sem_open");
        return 1;
    }
    // Unlink the semaphore name so it is removed when all processes close it or on system shutdown
    // This prevents the semaphore from persisting forever if a crash occurs
    sem_unlink(SEM_NAME);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork error");
        return 1;
    } else if (pid == 0) {
        child_process();
    } else {
        // Parent process
        std::cout << "Parent: Attempting to acquire semaphore." << std::endl;
        if (sem_wait(sem) == -1) {
            perror("parent sem_wait");
        }
        std::cout << "Parent: Acquired semaphore, doing work." << std::endl;
        sleep(2);
        std::cout << "Parent: Releasing semaphore." << std::endl;
        if (sem_post(sem) == -1) {
            perror("parent sem_post");
        }

        // Wait for the child to finish
        wait(NULL);
        
        if (sem_close(sem) == -1) {
            perror("parent sem_close");
        }
        std::cout << "Parent: Child finished, semaphore closed and unlinked." << std::endl;
    }

    return 0;
}

