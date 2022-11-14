/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: circshift.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "circshift.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * Arguments    : emxArray_real_T *a
 * Return Type  : void
 */
void b_circshift(emxArray_real_T *a)
{
  emxArray_real_T *buffer;
  double *a_data;
  double *buffer_data;
  int i;
  int k;
  int ns;
  a_data = a->data;
  emxInit_real_T(&buffer, 2);
  if ((a->size[0] != 0) && (a->size[1] != 0) &&
      ((a->size[0] != 1) || (a->size[1] != 1))) {
    int npages;
    int nv;
    int pageroot;
    ns = 1;
    if (a->size[0] <= 1) {
      ns = 0;
    }
    pageroot = (int)((unsigned int)a->size[0] >> 1);
    i = buffer->size[0] * buffer->size[1];
    buffer->size[0] = 1;
    buffer->size[1] = pageroot;
    emxEnsureCapacity_real_T(buffer, i);
    buffer_data = buffer->data;
    for (i = 0; i < pageroot; i++) {
      buffer_data[i] = 0.0;
    }
    nv = a->size[0];
    npages = a->size[1];
    if ((a->size[0] > 1) && (ns > 0)) {
      for (ns = 0; ns < npages; ns++) {
        pageroot = ns * nv;
        buffer_data[0] = a_data[pageroot];
        for (k = 0; k <= nv - 2; k++) {
          i = pageroot + k;
          a_data[i] = a_data[i + 1];
        }
        a_data[(pageroot + nv) - 1] = buffer_data[0];
      }
    }
  }
  emxFree_real_T(&buffer);
}

/*
 * Arguments    : emxArray_real_T *a
 * Return Type  : void
 */
void c_circshift(emxArray_real_T *a)
{
  emxArray_real_T *buffer;
  double *a_data;
  double *buffer_data;
  int b_i;
  int i;
  int k;
  a_data = a->data;
  emxInit_real_T(&buffer, 2);
  if ((a->size[0] != 0) && (a->size[1] != 0) &&
      ((a->size[0] != 1) || (a->size[1] != 1))) {
    int npages;
    int ns;
    int nv;
    bool shiftright;
    ns = 1;
    shiftright = true;
    if (a->size[0] <= 1) {
      ns = -1;
    } else if ((a->size[0] >> 1) < 2) {
      ns = a->size[0] - 3;
      shiftright = false;
    }
    nv = (int)((unsigned int)a->size[0] >> 1);
    i = buffer->size[0] * buffer->size[1];
    buffer->size[0] = 1;
    buffer->size[1] = nv;
    emxEnsureCapacity_real_T(buffer, i);
    buffer_data = buffer->data;
    for (i = 0; i < nv; i++) {
      buffer_data[i] = 0.0;
    }
    nv = a->size[0];
    npages = a->size[1];
    if ((a->size[0] > 1) && (ns + 1 > 0)) {
      for (b_i = 0; b_i < npages; b_i++) {
        int pageroot;
        pageroot = b_i * nv;
        if (shiftright) {
          for (k = 0; k <= ns; k++) {
            buffer_data[k] = a_data[(((pageroot + k) + nv) - ns) - 1];
          }
          i = ns + 2;
          for (k = nv; k >= i; k--) {
            int i1;
            i1 = pageroot + k;
            a_data[i1 - 1] = a_data[(i1 - ns) - 2];
          }
          for (k = 0; k <= ns; k++) {
            a_data[pageroot + k] = buffer_data[k];
          }
        } else {
          for (k = 0; k <= ns; k++) {
            buffer_data[k] = a_data[pageroot + k];
          }
          i = nv - ns;
          for (k = 0; k <= i - 2; k++) {
            int i1;
            i1 = pageroot + k;
            a_data[i1] = a_data[(i1 + ns) + 1];
          }
          for (k = 0; k <= ns; k++) {
            a_data[(((pageroot + k) + nv) - ns) - 1] = buffer_data[k];
          }
        }
      }
    }
  }
  emxFree_real_T(&buffer);
}

/*
 * Arguments    : emxArray_real_T *a
 * Return Type  : void
 */
void circshift(emxArray_real_T *a)
{
  emxArray_real_T *buffer;
  double *a_data;
  double *buffer_data;
  int i;
  int k;
  int ns;
  a_data = a->data;
  emxInit_real_T(&buffer, 2);
  if ((a->size[0] != 0) && (a->size[1] != 0) &&
      ((a->size[0] != 1) || (a->size[1] != 1))) {
    int npages;
    int nv;
    int pageroot;
    ns = 1;
    if (a->size[0] <= 1) {
      ns = 0;
    }
    pageroot = (int)((unsigned int)a->size[0] >> 1);
    i = buffer->size[0] * buffer->size[1];
    buffer->size[0] = 1;
    buffer->size[1] = pageroot;
    emxEnsureCapacity_real_T(buffer, i);
    buffer_data = buffer->data;
    for (i = 0; i < pageroot; i++) {
      buffer_data[i] = 0.0;
    }
    nv = a->size[0];
    npages = a->size[1];
    if ((a->size[0] > 1) && (ns > 0)) {
      for (ns = 0; ns < npages; ns++) {
        pageroot = ns * nv;
        buffer_data[0] = a_data[(pageroot + nv) - 1];
        for (k = nv; k >= 2; k--) {
          i = pageroot + k;
          a_data[i - 1] = a_data[i - 2];
        }
        a_data[pageroot] = buffer_data[0];
      }
    }
  }
  emxFree_real_T(&buffer);
}

/*
 * Arguments    : emxArray_real_T *a
 * Return Type  : void
 */
void d_circshift(emxArray_real_T *a)
{
  emxArray_real_T *buffer;
  double *a_data;
  double *buffer_data;
  int b_i;
  int i;
  int k;
  a_data = a->data;
  emxInit_real_T(&buffer, 2);
  if ((a->size[0] != 0) && (a->size[1] != 0) &&
      ((a->size[0] != 1) || (a->size[1] != 1))) {
    int npages;
    int ns;
    int nv;
    bool shiftright;
    ns = 1;
    shiftright = false;
    if (a->size[0] <= 1) {
      ns = -1;
    } else if ((a->size[0] >> 1) < 2) {
      ns = a->size[0] - 3;
      shiftright = true;
    }
    nv = (int)((unsigned int)a->size[0] >> 1);
    i = buffer->size[0] * buffer->size[1];
    buffer->size[0] = 1;
    buffer->size[1] = nv;
    emxEnsureCapacity_real_T(buffer, i);
    buffer_data = buffer->data;
    for (i = 0; i < nv; i++) {
      buffer_data[i] = 0.0;
    }
    nv = a->size[0];
    npages = a->size[1];
    if ((a->size[0] > 1) && (ns + 1 > 0)) {
      for (b_i = 0; b_i < npages; b_i++) {
        int pageroot;
        pageroot = b_i * nv;
        if (shiftright) {
          for (k = 0; k <= ns; k++) {
            buffer_data[k] = a_data[(((pageroot + k) + nv) - ns) - 1];
          }
          i = ns + 2;
          for (k = nv; k >= i; k--) {
            int i1;
            i1 = pageroot + k;
            a_data[i1 - 1] = a_data[(i1 - ns) - 2];
          }
          for (k = 0; k <= ns; k++) {
            a_data[pageroot + k] = buffer_data[k];
          }
        } else {
          for (k = 0; k <= ns; k++) {
            buffer_data[k] = a_data[pageroot + k];
          }
          i = nv - ns;
          for (k = 0; k <= i - 2; k++) {
            int i1;
            i1 = pageroot + k;
            a_data[i1] = a_data[(i1 + ns) + 1];
          }
          for (k = 0; k <= ns; k++) {
            a_data[(((pageroot + k) + nv) - ns) - 1] = buffer_data[k];
          }
        }
      }
    }
  }
  emxFree_real_T(&buffer);
}

/*
 * Arguments    : emxArray_real_T *a
 * Return Type  : void
 */
void e_circshift(emxArray_real_T *a)
{
  emxArray_real_T *buffer;
  double *a_data;
  double *buffer_data;
  int k;
  int ns;
  int stride;
  a_data = a->data;
  emxInit_real_T(&buffer, 2);
  if ((a->size[0] != 0) && (a->size[1] != 0) &&
      ((a->size[0] != 1) || (a->size[1] != 1))) {
    int unnamed_idx_1;
    ns = 1;
    if (a->size[1] <= 1) {
      ns = 0;
    }
    unnamed_idx_1 = (int)((unsigned int)a->size[1] >> 1);
    stride = buffer->size[0] * buffer->size[1];
    buffer->size[0] = 1;
    buffer->size[1] = unnamed_idx_1;
    emxEnsureCapacity_real_T(buffer, stride);
    buffer_data = buffer->data;
    for (stride = 0; stride < unnamed_idx_1; stride++) {
      buffer_data[stride] = 0.0;
    }
    unnamed_idx_1 = a->size[1];
    stride = a->size[0];
    if ((a->size[1] > 1) && (ns > 0)) {
      for (ns = 0; ns < stride; ns++) {
        buffer_data[0] = a_data[ns + (unnamed_idx_1 - 1) * stride];
        for (k = unnamed_idx_1; k >= 2; k--) {
          a_data[ns + (k - 1) * stride] = a_data[ns + (k - 2) * stride];
        }
        a_data[ns] = buffer_data[0];
      }
    }
  }
  emxFree_real_T(&buffer);
}

/*
 * Arguments    : emxArray_real_T *a
 * Return Type  : void
 */
void f_circshift(emxArray_real_T *a)
{
  emxArray_real_T *buffer;
  double *a_data;
  double *buffer_data;
  int k;
  int ns;
  int stride;
  a_data = a->data;
  emxInit_real_T(&buffer, 2);
  if ((a->size[0] != 0) && (a->size[1] != 0) &&
      ((a->size[0] != 1) || (a->size[1] != 1))) {
    int unnamed_idx_1;
    ns = 1;
    if (a->size[1] <= 1) {
      ns = 0;
    }
    unnamed_idx_1 = (int)((unsigned int)a->size[1] >> 1);
    stride = buffer->size[0] * buffer->size[1];
    buffer->size[0] = 1;
    buffer->size[1] = unnamed_idx_1;
    emxEnsureCapacity_real_T(buffer, stride);
    buffer_data = buffer->data;
    for (stride = 0; stride < unnamed_idx_1; stride++) {
      buffer_data[stride] = 0.0;
    }
    unnamed_idx_1 = a->size[1] - 2;
    stride = a->size[0];
    if ((a->size[1] > 1) && (ns > 0)) {
      for (ns = 0; ns < stride; ns++) {
        buffer_data[0] = a_data[ns];
        for (k = 0; k <= unnamed_idx_1; k++) {
          a_data[ns + k * stride] = a_data[ns + (k + 1) * stride];
        }
        a_data[ns + (unnamed_idx_1 + 1) * stride] = buffer_data[0];
      }
    }
  }
  emxFree_real_T(&buffer);
}

/*
 * Arguments    : emxArray_boolean_T *a
 * Return Type  : void
 */
void g_circshift(emxArray_boolean_T *a)
{
  emxArray_boolean_T *buffer;
  int k;
  int ns;
  int stride;
  bool *a_data;
  bool *buffer_data;
  a_data = a->data;
  emxInit_boolean_T(&buffer, 2);
  if ((a->size[0] != 0) && (a->size[1] != 0) &&
      ((a->size[0] != 1) || (a->size[1] != 1))) {
    int unnamed_idx_1;
    ns = 1;
    if (a->size[1] <= 1) {
      ns = 0;
    }
    unnamed_idx_1 = (int)((unsigned int)a->size[1] >> 1);
    stride = buffer->size[0] * buffer->size[1];
    buffer->size[0] = 1;
    buffer->size[1] = unnamed_idx_1;
    emxEnsureCapacity_boolean_T(buffer, stride);
    buffer_data = buffer->data;
    for (stride = 0; stride < unnamed_idx_1; stride++) {
      buffer_data[stride] = false;
    }
    unnamed_idx_1 = a->size[1] - 2;
    stride = a->size[0];
    if ((a->size[1] > 1) && (ns > 0)) {
      for (ns = 0; ns < stride; ns++) {
        buffer_data[0] = a_data[ns];
        for (k = 0; k <= unnamed_idx_1; k++) {
          a_data[ns + k * stride] = a_data[ns + (k + 1) * stride];
        }
        a_data[ns + (unnamed_idx_1 + 1) * stride] = buffer_data[0];
      }
    }
  }
  emxFree_boolean_T(&buffer);
}

/*
 * File trailer for circshift.c
 *
 * [EOF]
 */
