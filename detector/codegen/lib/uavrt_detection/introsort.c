/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: introsort.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "introsort.h"
#include "heapsort.h"
#include "insertionsort.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Type Definitions */
#ifndef typedef_struct_T
#define typedef_struct_T
typedef struct {
  int xstart;
  int xend;
  int depth;
} struct_T;
#endif /* typedef_struct_T */

/* Function Definitions */
/*
 * Arguments    : emxArray_int32_T *x
 *                int xend
 *                const emxArray_int32_T *cmp_workspace_x
 * Return Type  : void
 */
void b_introsort(emxArray_int32_T *x, int xend,
                 const emxArray_int32_T *cmp_workspace_x)
{
  struct_T frame;
  const int *cmp_workspace_x_data;
  int j;
  int pmin;
  int *x_data;
  cmp_workspace_x_data = cmp_workspace_x->data;
  x_data = x->data;
  if (xend > 1) {
    if (xend <= 32) {
      b_insertionsort(x, 1, xend, cmp_workspace_x);
    } else {
      struct_T st_d_data[120];
      int MAXDEPTH;
      int pmax;
      int pow2p;
      bool exitg1;
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
      pmax = MAXDEPTH << 1;
      for (pmin = 0; pmin < pmax; pmin++) {
        st_d_data[pmin] = frame;
      }
      st_d_data[0] = frame;
      pow2p = 1;
      while (pow2p > 0) {
        frame = st_d_data[pow2p - 1];
        pow2p--;
        pmin = frame.xend - frame.xstart;
        if (pmin + 1 <= 32) {
          b_insertionsort(x, frame.xstart, frame.xend, cmp_workspace_x);
          x_data = x->data;
        } else if (frame.depth == MAXDEPTH) {
          c_heapsort(x, frame.xstart, frame.xend, cmp_workspace_x);
          x_data = x->data;
        } else {
          int pivot;
          pmax = (frame.xstart + pmin / 2) - 1;
          pmin = x_data[frame.xstart - 1];
          if (cmp_workspace_x_data[x_data[pmax] - 1] <
              cmp_workspace_x_data[pmin - 1]) {
            x_data[frame.xstart - 1] = x_data[pmax];
            x_data[pmax] = pmin;
          }
          if (cmp_workspace_x_data[x_data[frame.xend - 1] - 1] <
              cmp_workspace_x_data[x_data[frame.xstart - 1] - 1]) {
            pmin = x_data[frame.xstart - 1];
            x_data[frame.xstart - 1] = x_data[frame.xend - 1];
            x_data[frame.xend - 1] = pmin;
          }
          if (cmp_workspace_x_data[x_data[frame.xend - 1] - 1] <
              cmp_workspace_x_data[x_data[pmax] - 1]) {
            pmin = x_data[pmax];
            x_data[pmax] = x_data[frame.xend - 1];
            x_data[frame.xend - 1] = pmin;
          }
          pivot = x_data[pmax];
          x_data[pmax] = x_data[frame.xend - 2];
          x_data[frame.xend - 2] = pivot;
          pmax = frame.xstart - 1;
          j = frame.xend - 2;
          int exitg2;
          do {
            exitg2 = 0;
            pmax++;
            int exitg3;
            do {
              exitg3 = 0;
              pmin = cmp_workspace_x_data[pivot - 1];
              if (cmp_workspace_x_data[x_data[pmax] - 1] < pmin) {
                pmax++;
              } else {
                exitg3 = 1;
              }
            } while (exitg3 == 0);
            for (j--; pmin < cmp_workspace_x_data[x_data[j] - 1]; j--) {
            }
            if (pmax + 1 >= j + 1) {
              exitg2 = 1;
            } else {
              pmin = x_data[pmax];
              x_data[pmax] = x_data[j];
              x_data[j] = pmin;
            }
          } while (exitg2 == 0);
          x_data[frame.xend - 2] = x_data[pmax];
          x_data[pmax] = pivot;
          if (pmax + 2 < frame.xend) {
            st_d_data[pow2p].xstart = pmax + 2;
            st_d_data[pow2p].xend = frame.xend;
            st_d_data[pow2p].depth = frame.depth + 1;
            pow2p++;
          }
          if (frame.xstart < pmax + 1) {
            st_d_data[pow2p].xstart = frame.xstart;
            st_d_data[pow2p].xend = pmax + 1;
            st_d_data[pow2p].depth = frame.depth + 1;
            pow2p++;
          }
        }
      }
    }
  }
}

/*
 * Arguments    : emxArray_int32_T *x
 *                int xend
 *                const emxArray_int32_T *cmp_workspace_a
 *                const emxArray_int32_T *cmp_workspace_b
 * Return Type  : void
 */
void introsort(emxArray_int32_T *x, int xend,
               const emxArray_int32_T *cmp_workspace_a,
               const emxArray_int32_T *cmp_workspace_b)
{
  struct_T frame;
  const int *cmp_workspace_a_data;
  const int *cmp_workspace_b_data;
  int i;
  int *x_data;
  cmp_workspace_b_data = cmp_workspace_b->data;
  cmp_workspace_a_data = cmp_workspace_a->data;
  x_data = x->data;
  if (xend > 1) {
    if (xend <= 32) {
      insertionsort(x, 1, xend, cmp_workspace_a, cmp_workspace_b);
    } else {
      struct_T st_d_data[120];
      int MAXDEPTH;
      int j;
      int pmax;
      int pmin;
      int pow2p;
      int st_n;
      bool exitg1;
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
      pmax = MAXDEPTH << 1;
      for (i = 0; i < pmax; i++) {
        st_d_data[i] = frame;
      }
      st_d_data[0] = frame;
      st_n = 1;
      while (st_n > 0) {
        frame = st_d_data[st_n - 1];
        st_n--;
        i = frame.xend - frame.xstart;
        if (i + 1 <= 32) {
          insertionsort(x, frame.xstart, frame.xend, cmp_workspace_a,
                        cmp_workspace_b);
          x_data = x->data;
        } else if (frame.depth == MAXDEPTH) {
          b_heapsort(x, frame.xstart, frame.xend, cmp_workspace_a,
                     cmp_workspace_b);
          x_data = x->data;
        } else {
          int pivot;
          bool varargout_1;
          pow2p = (frame.xstart + i / 2) - 1;
          i = x_data[frame.xstart - 1];
          pmax = cmp_workspace_a_data[x_data[pow2p] - 1];
          pmin = cmp_workspace_a_data[i - 1];
          if (pmax < pmin) {
            varargout_1 = true;
          } else if (pmax == pmin) {
            varargout_1 = (cmp_workspace_b_data[x_data[pow2p] - 1] <
                           cmp_workspace_b_data[i - 1]);
          } else {
            varargout_1 = false;
          }
          if (varargout_1) {
            x_data[frame.xstart - 1] = x_data[pow2p];
            x_data[pow2p] = i;
          }
          if (cmp_workspace_a_data[x_data[frame.xend - 1] - 1] <
              cmp_workspace_a_data[x_data[frame.xstart - 1] - 1]) {
            varargout_1 = true;
          } else {
            i = x_data[frame.xend - 1] - 1;
            pmax = x_data[frame.xstart - 1] - 1;
            if (cmp_workspace_a_data[i] == cmp_workspace_a_data[pmax]) {
              varargout_1 =
                  (cmp_workspace_b_data[i] < cmp_workspace_b_data[pmax]);
            } else {
              varargout_1 = false;
            }
          }
          if (varargout_1) {
            pmax = x_data[frame.xstart - 1];
            x_data[frame.xstart - 1] = x_data[frame.xend - 1];
            x_data[frame.xend - 1] = pmax;
          }
          if (cmp_workspace_a_data[x_data[frame.xend - 1] - 1] <
              cmp_workspace_a_data[x_data[pow2p] - 1]) {
            varargout_1 = true;
          } else {
            i = x_data[frame.xend - 1] - 1;
            if (cmp_workspace_a_data[i] ==
                cmp_workspace_a_data[x_data[pow2p] - 1]) {
              varargout_1 = (cmp_workspace_b_data[i] <
                             cmp_workspace_b_data[x_data[pow2p] - 1]);
            } else {
              varargout_1 = false;
            }
          }
          if (varargout_1) {
            pmax = x_data[pow2p];
            x_data[pow2p] = x_data[frame.xend - 1];
            x_data[frame.xend - 1] = pmax;
          }
          pivot = x_data[pow2p] - 1;
          x_data[pow2p] = x_data[frame.xend - 2];
          x_data[frame.xend - 2] = pivot + 1;
          pmin = frame.xstart - 1;
          j = frame.xend - 2;
          int exitg2;
          do {
            int exitg3;
            exitg2 = 0;
            pmin++;
            do {
              exitg3 = 0;
              i = cmp_workspace_a_data[x_data[pmin] - 1];
              if (i < cmp_workspace_a_data[pivot]) {
                varargout_1 = true;
              } else if (i == cmp_workspace_a_data[pivot]) {
                varargout_1 = (cmp_workspace_b_data[x_data[pmin] - 1] <
                               cmp_workspace_b_data[pivot]);
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
              i = cmp_workspace_a_data[x_data[j] - 1];
              if (cmp_workspace_a_data[pivot] < i) {
                varargout_1 = true;
              } else if (cmp_workspace_a_data[pivot] == i) {
                varargout_1 = (cmp_workspace_b_data[pivot] <
                               cmp_workspace_b_data[x_data[j] - 1]);
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
          x_data[frame.xend - 2] = x_data[pmin];
          x_data[pmin] = pivot + 1;
          if (pmin + 2 < frame.xend) {
            st_d_data[st_n].xstart = pmin + 2;
            st_d_data[st_n].xend = frame.xend;
            st_d_data[st_n].depth = frame.depth + 1;
            st_n++;
          }
          if (frame.xstart < pmin + 1) {
            st_d_data[st_n].xstart = frame.xstart;
            st_d_data[st_n].xend = pmin + 1;
            st_d_data[st_n].depth = frame.depth + 1;
            st_n++;
          }
        }
      }
    }
  }
}

/*
 * File trailer for introsort.c
 *
 * [EOF]
 */
