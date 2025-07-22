#ifndef WBE_ERROR_H
#define WBE_ERROR_H

/*
Case     0       reserved for No Error.
Case     1-999   reserved for Startup Errors.
Case  1000-1999  reserved for Clock Errors.
Case  2000-2999  reserved for Keyboard Input Errors.
Case  3000-3999  reserved for Mouse Input Errors.
Case  4000-4999  reserved for Controller Input Errors.
Case  5000-5999  reserved for Window Errors.
Case  6000-6999  reserved for Renderer Errors.
Case  7000-7999  reserved for World Errors.
Case  8000-8999  reserved for Camera Errors.
Case  9000-9999  reserved for Splash Errors.
Case 10000-10999 reserved for Math Errors.
*/

typedef enum {
    WBE_NO_ERROR_FOUND = 0,
    WBE_ChangeBit_ERROR_1 = 10000,
    WBE_ChangeBit_ERROR_2,
    WBE_ChangeBit_ERROR_3,
    WBE_ChangeBit_Error_4,
    WBE_UNKNOWN_ERROR
} WBE_ErrorCodes;

void WBE_GetError (int errorCode);

#endif