#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile int handler_done = 0;

void alarm_handler(int sig) {
    printf("Hello World!\n");
    handler_done = 1;
}

int main() {
    // Register SIGALRM handler
    signal(SIGALRM, alarm_handler);

    // Trigger alarm in 1 second
    alarm(1);

    // Wait until signal handler executes
    while (!handler_done) {
        pause(); // efficiently wait for signals
    }

    // Print main program message after handler
    printf("Turing was right!\n");

    return 0;
}
