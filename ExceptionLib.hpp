#pragma once

#include <Base.h>
#include <cstdint>
#include <Library/BaseLib.h>

typedef std::uint64_t ERROR_CODE;
constexpr ERROR_CODE EXCEPTION_SUCCESS       = 0;     // No error
constexpr ERROR_CODE EXCEPTION_UNKNOWN       = 1;     // Generic unknown error
constexpr ERROR_CODE EXCEPTION_INVALID_ARG   = 2;     // Invalid argument
constexpr ERROR_CODE EXCEPTION_OUT_OF_MEMORY = 3;     // Memory allocation failed
constexpr ERROR_CODE EXCEPTION_ACCESS_DENIED = 4;     // Insufficient permissions
constexpr ERROR_CODE EXCEPTION_NOT_FOUND     = 5;     // Resource not found
constexpr ERROR_CODE EXCEPTION_OVERFLOW      = 6;     // Numeric overflow
constexpr ERROR_CODE EXCEPTION_UNDERFLOW     = 7;     // Numeric underflow
constexpr ERROR_CODE EXCEPTION_IO_ERROR      = 8;     // Input/output failure
constexpr ERROR_CODE EXCEPTION_TIMEOUT       = 9;     // Operation timed out
constexpr ERROR_CODE EXCEPTION_UNSUPPORTED   = 10;    // Operation not supported
constexpr ERROR_CODE EXCEPTION_ASSERTION     = 11;    // Assertion failed

class Exception
{
public:
    char*
    __cdecl
    what(
        void
    )
    {
        switch (pErrorCode)
        {
            case EXCEPTION_SUCCESS:       return "Success";
            case EXCEPTION_UNKNOWN:       return "Unknown Error";
            case EXCEPTION_INVALID_ARG:   return "Invalid Argument";
            case EXCEPTION_OUT_OF_MEMORY: return "Out of Memory";
            case EXCEPTION_ACCESS_DENIED: return "Access Denied";
            case EXCEPTION_NOT_FOUND:     return "Not Found";
            case EXCEPTION_OVERFLOW:      return "Overflow";
            case EXCEPTION_UNDERFLOW:     return "Underflow";
            case EXCEPTION_IO_ERROR:      return "I/O Error";
            case EXCEPTION_TIMEOUT:       return "Timeout";
            case EXCEPTION_UNSUPPORTED:   return "Unsupported Operation";
            case EXCEPTION_ASSERTION:     return "Assertion Failed";
            default:                      return "Undefined Error";
        }
    }

    ERROR_CODE&
    __cdecl
    code(
        void
    )
    {
        return pErrorCode;
    }

    BASE_LIBRARY_JUMP_BUFFER&
    __cdecl
    jumpBuffer(
        void
    )
    {
        return pJumpBuffer;
    }

private:
    ERROR_CODE pErrorCode = 0;
    BASE_LIBRARY_JUMP_BUFFER pJumpBuffer;
};

Exception gException;

#define try \
    if ((gException.code() = SetJump(&gException.jumpBuffer())) == 0)

#define throw(Code) \
    LongJump(&(gException).jumpBuffer(), Code)
    
#define catch(ExceptionVar) \
    else if (Exception& ExceptionVar = gException; ExceptionVar.code())