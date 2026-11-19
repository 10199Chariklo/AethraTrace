/* _CK_ */

#ifndef AETHRA_TRACE_TYPEFWD_H
#define AETHRA_TRACE_TYPEFWD_H

// Logger flags for runtime configuration
typedef enum {
    LOG_NONE         = 0X00,     // No logging 
    LOG_LIFECYCLE    = 0X01,     // Tracks tree adjustments, attachments, and structural modifications
    LOG_TRAVERSAL    = 0X02,     // Details node visitation, depth tracking and backtracking
    LOG_ALL          = 0XFF      // Enables all logging flags for maximum verbosity
} logLevel;

typedef enum {
    LOG_CONSOLE, // Default; Console output stream
    LOG_JSON,    // JSON structured output for external parsing and analysis
} logFormat;

typedef void* logHandle; // Public type-agnostic Handle

#endif // AETHRA_TRACE_TYPEFWD_H