/* _OU_ */

#ifndef AETHRA_TRACE_H
#define AETHRA_TRACE_H

#define AETHRA_TRACE_PRESENT 1

/* AethraTrace Subsystem */
#include "AethraTrace_typefwd.h" // Public type definitions

// AethraTrace Fingerprints
    /**
     * @brief Dynamic configuration driver to toggle log stream depth at runtime.
    */
    void CKtrace_setLogLevel(logLevel level);

    /**
     * @brief Retrieves the current logging level.
    */
    logLevel CKtrace_getLogLevel(void);

    /**
     * @brief Flushes the internal log stream to console or file output, depending on the configuration
    */
    void CKtrace_flushLog(logFormat format);

    /**
     * @brief Public utility to bubble up log messages to an output handler
    */
    void CKtrace_bubbleLog(logHandle handle, const char* message);
// AethraTrace Fingerprints

#endif // AETHRA_TRACE_H