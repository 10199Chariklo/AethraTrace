/* _CU_ */

/* Standard C11 Libraries */
#include <stddef.h>
#include <stdio.h>

/* AethraTrace Subsystem */
#include "AethraTrace.h" // Public module header
// #include "AethraTrace_typedef.h" // Internal type definitions (Unused)

/* Runtime logging configuration flag */
static logLevel g_current_log_level = LOG_NONE;

/* Runtime logging stream buffer */
static char g_log_buffer[1024];
static size_t g_log_offset = 0;

void CKtrace_setLogLevel(logLevel level) {
    g_current_log_level = level;
}

logLevel CKtrace_getLogLevel(void) {
    return g_current_log_level;
}

void CKtrace_flushLog(logFormat format) {
    // If structured output is requested, wrap or dump raw records
    if (format == LOG_JSON) {
        // Placeholder for \n line serialization logic
    } else {
        printf("%s", g_log_buffer);
        printf("\n > AethraTrace: Log Stream Flushed.\n");
    }
    // Completely clear the static buffer footprint and reset tracking cursor
    for (size_t i = 0; i < sizeof(g_log_buffer); i++) {
        g_log_buffer[i] = '\0';
    }
    g_log_offset = 0;
}

void CKtrace_bubbleLog(logHandle handle, const char* message) {
    // Only execute if logging is globally active
    if (g_current_log_level == LOG_NONE) return;

    // Remaining capacity check
    if (g_log_offset >= sizeof(g_log_buffer) - 1) return;

    size_t capacity = sizeof(g_log_buffer) - g_log_offset;
    
    // Format the line out safely: Include node pointer hex for address tracing
    int written = snprintf(&g_log_buffer[g_log_offset], capacity, 
                           "[HANDLE: %p] -> %s\n", (void*)handle, message);

    // Advance cursor if print was successful and fit within limits
    if (written > 0 && (size_t)written < capacity) {
        g_log_offset += written;
    }
}