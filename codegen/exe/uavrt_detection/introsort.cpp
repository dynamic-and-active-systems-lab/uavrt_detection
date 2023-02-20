//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: introsort.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 14:31:55
//

// Include Files
#include "introsort.h"
#include "anonymous_function.h"
#include "heapsort.h"
#include "insertionsort.h"
#include "rt_nonfinite.h"
#include "stack1.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "omp.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include <string>

// Function Declarations
static void jb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void jb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Cannot push onto a fixed-size stack which is at capacity.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

//
// Arguments    : int x_data[]
//                int xend
//                const anonymous_function cmp
// Return Type  : void
//
namespace coder {
namespace internal {
void introsort(int x_data[], int xend, const anonymous_function cmp)
{
  static rtDoubleCheckInfo b_emlrtDCI{
      48,            // lineNo
      48,            // colNo
      "stack/stack", // fName
      "C:\\Program "
      "Files\\MATLAB\\toolbox\\shared\\coder\\coder\\lib\\+coder\\+"
      "internal\\stack.m", // pName
      4                    // checkKind
  };
  static rtRunTimeErrorInfo kb_emlrtRTEI{
      62,          // lineNo
      "stack/push" // fName
  };
  struct_T frame;
  if (xend > 1) {
    if (xend <= 32) {
      insertionsort(1, xend);
    } else {
      stack st;
      int MAXDEPTH;
      int i;
      int j;
      int pmax;
      int pmin;
      int pow2p;
      boolean_T exitg1;
      pmax = 31;
      pmin = 0;
      exitg1 = false;
      while ((!exitg1) && (pmax - pmin > 1)) {
        j = (pmin + pmax) >> 1;
        pow2p = 1 << j;
        if (pow2p == xend) {
          pmax = j;
          exitg1 = true;
        } else if (pow2p > xend) {
          pmax = j;
        } else {
          pmin = j;
        }
      }
      MAXDEPTH = (pmax - 1) << 1;
      frame.xstart = 1;
      frame.xend = xend;
      frame.depth = 0;
      i = MAXDEPTH << 1;
      if (i < 0) {
        rtNonNegativeError(static_cast<double>(i), &b_emlrtDCI);
      }
      if (i <= 0) {
        jb_rtErrorWithMessageID(kb_emlrtRTEI.fName, kb_emlrtRTEI.lineNo);
      }
      st.d.data[0] = frame;
      st.n = 1;
      while (st.n > 0) {
        int i1;
        int s_depth_tmp_tmp;
        frame = st.d.data[0];
        s_depth_tmp_tmp = st.d.data[0].depth;
        st.n = 0;
        i1 = st.d.data[0].xend - st.d.data[0].xstart;
        if (i1 + 1 <= 32) {
          insertionsort(st.d.data[0].xstart, st.d.data[0].xend);
        } else if (st.d.data[0].depth == MAXDEPTH) {
          b_heapsort(st.d.data[0].xstart, st.d.data[0].xend);
        } else {
          int pivot;
          boolean_T varargout_1;
          pow2p = (st.d.data[0].xstart + i1 / 2) - 1;
          i1 = x_data[st.d.data[0].xstart - 1];
          pmax = cmp.workspace.a.data[x_data[pow2p] - 1];
          pmin = cmp.workspace.a.data[i1 - 1];
          if (pmax < pmin) {
            varargout_1 = true;
          } else if (pmax == pmin) {
            varargout_1 = (cmp.workspace.b.data[x_data[pow2p] - 1] <
                           cmp.workspace.b.data[i1 - 1]);
          } else {
            varargout_1 = false;
          }
          if (varargout_1) {
            x_data[st.d.data[0].xstart - 1] = x_data[pow2p];
            x_data[pow2p] = i1;
          }
          if (cmp.workspace.a.data[x_data[st.d.data[0].xend - 1] - 1] <
              cmp.workspace.a.data[x_data[st.d.data[0].xstart - 1] - 1]) {
            varargout_1 = true;
          } else {
            i1 = x_data[st.d.data[0].xend - 1] - 1;
            pmax = x_data[st.d.data[0].xstart - 1] - 1;
            if (cmp.workspace.a.data[i1] == cmp.workspace.a.data[pmax]) {
              varargout_1 =
                  (cmp.workspace.b.data[i1] < cmp.workspace.b.data[pmax]);
            } else {
              varargout_1 = false;
            }
          }
          if (varargout_1) {
            pmax = x_data[st.d.data[0].xstart - 1];
            x_data[st.d.data[0].xstart - 1] = x_data[st.d.data[0].xend - 1];
            x_data[st.d.data[0].xend - 1] = pmax;
          }
          if (cmp.workspace.a.data[x_data[st.d.data[0].xend - 1] - 1] <
              cmp.workspace.a.data[x_data[pow2p] - 1]) {
            varargout_1 = true;
          } else {
            i1 = x_data[st.d.data[0].xend - 1] - 1;
            if (cmp.workspace.a.data[i1] ==
                cmp.workspace.a.data[x_data[pow2p] - 1]) {
              varargout_1 = (cmp.workspace.b.data[i1] <
                             cmp.workspace.b.data[x_data[pow2p] - 1]);
            } else {
              varargout_1 = false;
            }
          }
          if (varargout_1) {
            pmax = x_data[pow2p];
            x_data[pow2p] = x_data[st.d.data[0].xend - 1];
            x_data[st.d.data[0].xend - 1] = pmax;
          }
          pivot = x_data[pow2p] - 1;
          x_data[pow2p] = x_data[st.d.data[0].xend - 2];
          x_data[st.d.data[0].xend - 2] = pivot + 1;
          pmin = st.d.data[0].xstart - 1;
          j = st.d.data[0].xend - 2;
          int exitg2;
          do {
            int exitg3;
            exitg2 = 0;
            pmin++;
            do {
              exitg3 = 0;
              i1 = cmp.workspace.a.data[x_data[pmin] - 1];
              if (i1 < cmp.workspace.a.data[pivot]) {
                varargout_1 = true;
              } else if (i1 == cmp.workspace.a.data[pivot]) {
                varargout_1 = (cmp.workspace.b.data[x_data[pmin] - 1] <
                               cmp.workspace.b.data[pivot]);
              } else {
                varargout_1 = false;
              }
              if (varargout_1) {
                pmin++;
              } else {
                exitg3 = 1;
              }
            } while (exitg3 == 0);
            j--;
            do {
              exitg3 = 0;
              i1 = cmp.workspace.a.data[x_data[j] - 1];
              if (cmp.workspace.a.data[pivot] < i1) {
                varargout_1 = true;
              } else if (cmp.workspace.a.data[pivot] == i1) {
                varargout_1 = (cmp.workspace.b.data[pivot] <
                               cmp.workspace.b.data[x_data[j] - 1]);
              } else {
                varargout_1 = false;
              }
              if (varargout_1) {
                j--;
              } else {
                exitg3 = 1;
              }
            } while (exitg3 == 0);
            if (pmin + 1 >= j + 1) {
              exitg2 = 1;
            } else {
              pmax = x_data[pmin];
              x_data[pmin] = x_data[j];
              x_data[j] = pmax;
            }
          } while (exitg2 == 0);
          x_data[st.d.data[0].xend - 2] = x_data[pmin];
          x_data[pmin] = pivot + 1;
          if (pmin + 2 < st.d.data[0].xend) {
            st.d.data[0].xstart = pmin + 2;
            st.d.data[0].xend = frame.xend;
            st.d.data[0].depth++;
            st.n = 1;
          }
          if (frame.xstart < pmin + 1) {
            if (st.n >= i) {
              jb_rtErrorWithMessageID(kb_emlrtRTEI.fName, kb_emlrtRTEI.lineNo);
            }
            st.d.data[0].xstart = frame.xstart;
            st.d.data[0].xend = pmin + 1;
            st.d.data[0].depth = s_depth_tmp_tmp + 1;
            st.n = 1;
          }
        }
      }
    }
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for introsort.cpp
//
// [EOF]
//
