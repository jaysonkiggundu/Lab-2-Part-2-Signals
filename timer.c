#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

volatile bool handler_fired = false;
volatile int alarm_counter = 0;
time_t program_start;

void periodic_handler(int sig) {
    printf("Hello World!\n");
    handler_fired = true;
    alarm_counter++;
    alarm(5); // next alarm in 5 seconds
}

void exit_handler(int sig) {
    time_t program_end = time(NULL);
    int runtime = (int)difftime(program_end, program_start);
    printf("\nTotal execution time: %d seconds\n", runtime);
    printf("Total alarms triggered: %d\n", alarm_counter);
    exit(0);
}

int main() {
    program_start = time(NULL);

    signal(SIGALRM, periodic_handler);
    signal(SIGINT, exit_handler);

    alarm(5); // first alarm in 5 seconds

    while (1) {
        pause(); // wait for signals
        if (handler_fired) {
            printf("Turing was right!\n");
            handler_fired = false;
        }
    }

    return 0;
}
