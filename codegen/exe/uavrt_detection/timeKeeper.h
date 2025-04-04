//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: timeKeeper.h
//
// MATLAB Coder version            : 23.2
// C/C++ source code generated on  : 04-Mar-2024 13:02:36
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
namespace b_time {
namespace impl {
void timeKeeper(double newTime_tv_sec, double newTime_tv_nsec);

double timeKeeper(double &outTime_tv_nsec);

} // namespace impl
} // namespace b_time
} // namespace internal
} // namespace coder
void timeKeeper_init();

#endif
//
// File trailer for timeKeeper.h
//
// [EOF]
//
