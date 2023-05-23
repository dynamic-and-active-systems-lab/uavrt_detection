//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: toc.cpp
//
<<<<<<< HEAD
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 23-May-2023 12:05:02
=======
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 04-Apr-2023 11:47:02
>>>>>>> 3930a1e557481905555f2756f2f70ac82e87beba
//

// Include Files
#include "toc.h"
#include "rt_nonfinite.h"
#include "timeKeeper.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_posix_time.h"
#include <string>

// Function Definitions
//
// Arguments    : void
// Return Type  : double
//
namespace coder {
double toc()
{
  coderTimespec b_timespec;
  double tstart_tv_nsec;
  double tstart_tv_sec;
  int status;
  tstart_tv_sec = internal::b_time::impl::timeKeeper(tstart_tv_nsec);
  if (!freq_not_empty) {
    freq_not_empty = true;
    status = coderInitTimeFunctions(&freq);
    if (status != 0) {
      rtErrorWithMessageID(std::string(&cv1[0], 22), status, kb_emlrtRTEI.fName,
                           kb_emlrtRTEI.lineNo);
    }
  }
  status = coderTimeClockGettimeMonotonic(&b_timespec, freq);
  if (status != 0) {
    rtErrorWithMessageID(std::string(&cv2[0], 30), status, kb_emlrtRTEI.fName,
                         kb_emlrtRTEI.lineNo);
  }
  return (b_timespec.tv_sec - tstart_tv_sec) +
         (b_timespec.tv_nsec - tstart_tv_nsec) / 1.0E+9;
}

} // namespace coder

//
// File trailer for toc.cpp
//
// [EOF]
//
