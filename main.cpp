//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: main.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 16-Feb-2023 15:25:26
//

/*************************************************************************/
/* This automatically generated example C++ main file shows how to call  */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

// Include Files
#include "main.h"
#include "rt_nonfinite.h"
#include "uavrt_detection.h"
#include "uavrt_detection_terminate.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include <string>

// Function Declarations
static coder::array<char, 2U> argInit_1xUnbounded_char_T();

static char argInit_char_T();

static void ic_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void main_uavrt_detection();

//
// Arguments    : void
// Return Type  : void
//
static void main_uavrt_detection(const char* configPathAsChar)
{
  coder::array<char, 2U> configPathAsArray;

  configPathAsArray.set_size(1, strlen(configPathAsChar));

  // Loop over the array to initialize each element.
  for (int idx1{0}; idx1 < configPathAsArray.size(1); idx1++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    configPathAsArray[idx1] = configPathAsChar[idx1];
  }


  uavrt_detection(configPathAsArray);
}

//
// Arguments    : int argc
//                char **argv
// Return Type  : int
//
int main(int argc, char ** argv)
{
  if (argc != 2) {
    std::fprintf(stderr, "Path to config file must be provided\n");
    std::abort();
  }

  // The initialize function is being called automatically from your entry-point
  // function. So, a call to initialize is not included here. Invoke the
  // entry-point functions.
  // You can call entry-point functions multiple times.
  main_uavrt_detection(argv[1]);

  // Terminate the application.
  // You do not need to do this more than one time.
  uavrt_detection_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
