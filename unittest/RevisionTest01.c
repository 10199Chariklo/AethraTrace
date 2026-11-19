/* Standard C11 Libraries */
#include <stddef.h>
#include <stdio.h>
#include <conio.h>

/* AethraTrace Subsystem */
#if defined(__has_include)
    #if __has_include("AethraTrace.h")
        #include "AethraTrace.h"
    #endif
#endif

#if defined(AETHRA_TRACE_PRESENT) && (AETHRA_TRACE_PRESENT == 1)
    #define REVISION_TRACE_EVENT(level, handle, message)            \
        do {                                                        \
            if (CKtrace_getLogLevel() & (level)) {                  \
                CKtrace_bubbleLog((handle), (message));             \
            }                                                       \
        } while (0)
#else
    #define REVISION_TRACE_EVENT(level, handle, message)            \
        do {                                                        \
            /* Optional: Custom user logging hook fallback */       \
        } while (0)
#endif

/**     Define a fake handle for testing 
 *  This is the same pattern NULL uses
*/
#define DUMBHAND ((void*)0xDEAD0BEEF0CAFE00)

/**
 * @brief Rapidly bubbleLog a series of messages for testing
*/
void rapidLogger(int count) {
    for (int i = 0 ; i < count; i++) {
        char message[64];
        snprintf(message, sizeof(message), "Rapid log entry #%d", i + 1);
        REVISION_TRACE_EVENT(LOG_ALL, NULL, message);
    }
}

void teardown(void) {
    // Flush remaining logs
    CKtrace_flushLog(LOG_CONSOLE);

    // getch wait for input
    printf("\nPress 'ESC' to exit; All remaining logs have been flushed for review prior to exit.\n");
    char input;
    do {
        input = getch();
    } while (input != 27);
}

int main(void) {
    // Set logging to LOG_ALL
    CKtrace_setLogLevel(LOG_ALL);

    // Bubble and flush to console a single message to indicate start
    CKtrace_bubbleLog(DUMBHAND, "Starting unit test; rapidLogger will be invoked to test static buffer");
    CKtrace_flushLog(LOG_CONSOLE);

    // getch wait for input
    printf("\nPress 'y' to continue, or 'ESC' to begin exit\n");
    char input;
    do {
        input = getch();
    } while (input != 'y' && input != 27);

    if (input == 27) {
        teardown();
        return 0;
    }

    // run rapidLogger enough times to overflow static buffer
    rapidLogger(128);

    // Teardown
    teardown();
    return 0;
}