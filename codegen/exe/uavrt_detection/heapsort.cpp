//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: heapsort.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 12:48:10
//

// Include Files
#include "heapsort.h"
#include "anonymous_function.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_internal_types.h"
#include "coder_array.h"

// Function Declarations
namespace coder {
namespace internal {
static void heapify(::coder::array<int, 1U> &x, int idx, int xstart, int xend,
                    const c_anonymous_function *cmp);

static void heapify(::coder::array<int, 1U> &x, int idx, int xstart, int xend,
                    const anonymous_function *cmp);

} // namespace internal
} // namespace coder

// Function Definitions
//
// Arguments    : ::coder::array<int, 1U> &x
//                int idx
//                int xstart
//                int xend
//                const c_anonymous_function *cmp
// Return Type  : void
//
namespace coder {
namespace internal {
static void heapify(::coder::array<int, 1U> &x, int idx, int xstart, int xend,
                    const c_anonymous_function *cmp)
{
  int cmpIdx;
  int extremum;
  int extremumIdx;
  int leftIdx;
  boolean_T changed;
  boolean_T exitg1;
  changed = true;
  extremumIdx = (idx + xstart) - 2;
  leftIdx = ((idx << 1) + xstart) - 1;
  exitg1 = false;
  while ((!exitg1) && (leftIdx < xend)) {
    int xcmp;
    changed = false;
    extremum = x[extremumIdx];
    cmpIdx = leftIdx - 1;
    xcmp = x[leftIdx - 1];
    if (cmp->workspace.x[x[leftIdx - 1] - 1] <
        cmp->workspace.x[x[leftIdx] - 1]) {
      cmpIdx = leftIdx;
      xcmp = x[leftIdx];
    }
    if (cmp->workspace.x[x[extremumIdx] - 1] < cmp->workspace.x[xcmp - 1]) {
      x[extremumIdx] = xcmp;
      x[cmpIdx] = extremum;
      extremumIdx = cmpIdx;
      leftIdx = ((((cmpIdx - xstart) + 2) << 1) + xstart) - 1;
      changed = true;
    } else {
      exitg1 = true;
    }
  }
  if (changed && (leftIdx <= xend)) {
    extremum = x[extremumIdx];
    cmpIdx = x[leftIdx - 1];
    if (cmp->workspace.x[x[extremumIdx] - 1] < cmp->workspace.x[cmpIdx - 1]) {
      x[extremumIdx] = cmpIdx;
      x[leftIdx - 1] = extremum;
    }
  }
}

//
// Arguments    : ::coder::array<int, 1U> &x
//                int idx
//                int xstart
//                int xend
//                const anonymous_function *cmp
// Return Type  : void
//
static void heapify(::coder::array<int, 1U> &x, int idx, int xstart, int xend,
                    const anonymous_function *cmp)
{
  int extremum;
  int extremumIdx;
  int i;
  int i1;
  int leftIdx;
  boolean_T changed;
  boolean_T exitg1;
  boolean_T varargout_1;
  changed = true;
  extremumIdx = (idx + xstart) - 2;
  leftIdx = ((idx << 1) + xstart) - 2;
  exitg1 = false;
  while ((!exitg1) && (leftIdx + 1 < xend)) {
    int cmpIdx;
    int i2;
    int xcmp;
    changed = false;
    extremum = x[extremumIdx];
    cmpIdx = leftIdx;
    xcmp = x[leftIdx];
    i = x[leftIdx + 1] - 1;
    i1 = cmp->workspace.a[x[leftIdx] - 1];
    i2 = cmp->workspace.a[i];
    if (i1 < i2) {
      varargout_1 = true;
    } else if (i1 == i2) {
      varargout_1 = (cmp->workspace.b[x[leftIdx] - 1] < cmp->workspace.b[i]);
    } else {
      varargout_1 = false;
    }
    if (varargout_1) {
      cmpIdx = leftIdx + 1;
      xcmp = x[leftIdx + 1];
    }
    i = cmp->workspace.a[x[extremumIdx] - 1];
    i1 = cmp->workspace.a[xcmp - 1];
    if (i < i1) {
      varargout_1 = true;
    } else if (i == i1) {
      varargout_1 =
          (cmp->workspace.b[x[extremumIdx] - 1] < cmp->workspace.b[xcmp - 1]);
    } else {
      varargout_1 = false;
    }
    if (varargout_1) {
      x[extremumIdx] = xcmp;
      x[cmpIdx] = extremum;
      extremumIdx = cmpIdx;
      leftIdx = ((((cmpIdx - xstart) + 2) << 1) + xstart) - 2;
      changed = true;
    } else {
      exitg1 = true;
    }
  }
  if (changed && (leftIdx + 1 <= xend)) {
    extremum = x[extremumIdx];
    i = cmp->workspace.a[x[extremumIdx] - 1];
    i1 = cmp->workspace.a[x[leftIdx] - 1];
    if (i < i1) {
      varargout_1 = true;
    } else if (i == i1) {
      varargout_1 = (cmp->workspace.b[x[extremumIdx] - 1] <
                     cmp->workspace.b[x[leftIdx] - 1]);
    } else {
      varargout_1 = false;
    }
    if (varargout_1) {
      x[extremumIdx] = x[leftIdx];
      x[leftIdx] = extremum;
    }
  }
}

//
// Arguments    : ::coder::array<int, 1U> &x
//                int xstart
//                int xend
//                const c_anonymous_function *cmp
// Return Type  : void
//
void b_heapsort(::coder::array<int, 1U> &x, int xstart, int xend,
                const c_anonymous_function *cmp)
{
  int idx;
  int n;
  n = (xend - xstart) - 1;
  for (idx = n + 2; idx >= 1; idx--) {
    heapify(x, idx, xstart, xend, cmp);
  }
  for (int k{0}; k <= n; k++) {
    int t;
    idx = (xend - k) - 1;
    t = x[idx];
    x[idx] = x[xstart - 1];
    x[xstart - 1] = t;
    heapify(x, 1, xstart, (xend - k) - 1, cmp);
  }
}

//
// Arguments    : ::coder::array<int, 1U> &x
//                int xstart
//                int xend
//                const anonymous_function *cmp
// Return Type  : void
//
void b_heapsort(::coder::array<int, 1U> &x, int xstart, int xend,
                const anonymous_function *cmp)
{
  int idx;
  int n;
  n = (xend - xstart) - 1;
  for (idx = n + 2; idx >= 1; idx--) {
    heapify(x, idx, xstart, xend, cmp);
  }
  for (int k{0}; k <= n; k++) {
    int t;
    idx = (xend - k) - 1;
    t = x[idx];
    x[idx] = x[xstart - 1];
    x[xstart - 1] = t;
    heapify(x, 1, xstart, (xend - k) - 1, cmp);
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for heapsort.cpp
//
// [EOF]
//
