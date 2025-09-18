#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

volatile bool handler_triggered = false;

void recurring_handler(int sig) {
    printf("Hello World!\n");
    handler_triggered = true;
    alarm(5); // schedule next alarm
}

int main() {
    // Register the signal handler
    signal(SIGALRM, recurring_handler);

    // Start first alarm
    alarm(5);

    // Infinite loop
    while (1) {
        pause(); // wait for signal
        if (handler_triggered) {
            printf("Turing was right!\n");
            handler_triggered = false;
        }
    }

    return 0;
}
