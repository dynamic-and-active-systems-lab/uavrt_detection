//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: tic.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 12:48:10
//

// Include Files
#include "tic.h"
#include "rt_nonfinite.h"
#include "timeKeeper.h"
#include "uavrt_detection_data.h"
#include "coder_posix_time.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
namespace coder {
void tic()
{
  coderTimespec b_timespec;
  if (!freq_not_empty) {
    freq_not_empty = true;
    coderInitTimeFunctions(&freq);
  }
  coderTimeClockGettimeMonotonic(&b_timespec, freq);
  internal::time::impl::timeKeeper(b_timespec.tv_sec, b_timespec.tv_nsec);
}

} // namespace coder

//
// File trailer for tic.cpp
//
// [EOF]
//
