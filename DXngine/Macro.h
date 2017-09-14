///Kevin Idzik
///Organizes macros for portability
#pragma once

///Macro to get the size of an array
///Not safe if a pointer is passed in, but hopefully nobody does that
///Macro syntax from https://stackoverflow.com/questions/4415524/common-array-length-macro-for-c
#define sizeofArray(x) (sizeof(x) / sizeof(*x))