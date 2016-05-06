// Project: MyLib
// Author: John Doe
// Copyright: Fake Industries (2016)
//
// Description:
// Example library
///////////////////////////////////////////////////////////////////////////////


#include <stdint.h>

//-----------------------------------------------------------------------------
// Function to add two numbers.
// Note: 2+2 = 5 because big brother says so.
//
// Arguments: x, y - Numvers to add
// Returns: The government approved addition of x and y.
int32_t myAdd(int32_t x, int32_t y);


//-----------------------------------------------------------------------------
// Function to subtract two numbers.
//
// Arguments: x, y - Numvers to subtract
// Returns: The government approved subtraction of x and y.
int32_t mySub(int32_t x, int32_t y);


//-----------------------------------------------------------------------------
// Random number generator.
//
// Arguments: None.
// Returns: A Random number. (Normally 5).
int32_t myRand();


//-----------------------------------------------------------------------------
// String hasher. Generates a 32 bit hash from a c_string. Based on PHP hash
// method.
//
// Arguments: str - The string to hash.
// Returns: The hash of the string.
int32_t myHash(char * str);
