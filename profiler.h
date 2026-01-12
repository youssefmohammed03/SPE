#ifndef PROFILER_H
#define PROFILER_H

#include <stdio.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

FILE *log_file;
char call_stack[100][50];
int stack_pointer = 0;
clock_t start_time;

// Initialize the profiler
void profile_init() {
    log_file = fopen("path_profile.txt", "w");
    if (log_file == NULL) {
        printf("Error opening log file!\n");
        return;
    }

    fprintf(log_file, "Timestamp,Event,Function,Caller\n");
    start_time = clock();
}

// Function to call at the beginning of a function
void profile_enter(const char* func_name) {
    double current_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    
    // Determine caller
    const char* caller = "ROOT";
    if (stack_pointer > 0) {
        caller = call_stack[stack_pointer - 1];
    }

    // Log the event
    if (log_file) {
        fprintf(log_file, "%.6f,ENTER,%s,%s\n", current_time, func_name, caller);
    }

    // Push to stack
    if (stack_pointer < 100) {
        strcpy(call_stack[stack_pointer], func_name);
        stack_pointer++;
    }
}

// Function to call at the end of a function
void profile_exit(const char* func_name) {
    double current_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;

    // Log the event
    if (log_file) {
        fprintf(log_file, "%.6f,EXIT,%s,-\n", current_time, func_name);
    }

    // Pop from stack
    if (stack_pointer > 0) {
        stack_pointer--;
    }
}

// Close the profiler
void profile_close() {
    if (log_file) {
        fclose(log_file);
    }
}

// Macros to make instrumentation cleaner
#define PROFILE_START profile_init();
#define PROFILE_END profile_close();
#define FUNC_ENTER profile_enter(__func__);
#define FUNC_EXIT profile_exit(__func__);

#endif