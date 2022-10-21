//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: timeKeeper.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 20-Oct-2022 20:46:49
//

#ifndef TIMEKEEPER_H
#define TIMEKEEPER_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace time {
namespace impl {
void timeKeeper(double newTime_tv_sec, double newTime_tv_nsec);

void timeKeeper(double *outTime_tv_sec, double *outTime_tv_nsec);

} // namespace impl
} // namespace time
} // namespace internal
} // namespace coder
void savedTime_not_empty_init();

#endif
//
// File trailer for timeKeeper.h
//
// [EOF]
//
