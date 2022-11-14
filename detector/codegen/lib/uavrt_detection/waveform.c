/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: waveform.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "waveform.h"
#include "FFTImplementationCallback.h"
#include "abs.h"
#include "all.h"
#include "allOrAny.h"
#include "buildtimecorrelatormatrix.h"
#include "circshift.h"
#include "div.h"
#include "fftshift.h"
#include "find.h"
#include "horzcatStructList.h"
#include "ifWhileCond.h"
#include "imresize.h"
#include "incohsumtoeplitz.h"
#include "interp1.h"
#include "linspace.h"
#include "makepulsestruc.h"
#include "mean.h"
#include "minOrMax.h"
#include "pulsestats.h"
#include "repmat.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "stft.h"
#include "strcmp.h"
#include "sum.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "unaryMinOrMax.h"
#include "validator_check_size.h"
#include "weightingmatrix.h"
#include "wfmstft.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Declarations */
static void b_and(emxArray_boolean_T *in1, const emxArray_boolean_T *in2, const
                  emxArray_boolean_T *in3);
static void c_and(emxArray_boolean_T *in1, const emxArray_boolean_T *in2);
static void d_binary_expand_op(waveform *in1, int in2, double in3, const
  emxArray_real_T *in4, const emxArray_real_T *in5);
static void e_binary_expand_op(emxArray_boolean_T *in1, const emxArray_real_T
  *in2, const emxArray_real_T *in3, const emxArray_real_T *in4, const
  emxArray_real_T *in5, const emxArray_real_T *in6, const emxArray_real_T *in7,
  const emxArray_real_T *in8, const emxArray_real_T *in9);
static void f_binary_expand_op(emxArray_real_T *in1, double in2, double in3,
  double in4, const emxArray_real_T *in5);
static void g_binary_expand_op(emxArray_real_T *in1, double in2, double in3,
  const emxArray_real_T *in4, double in5);
static void h_binary_expand_op(emxArray_boolean_T *in1, unsigned int in2, const
  emxArray_boolean_T *in3, const emxArray_real_T *in4, double in5, const
  emxArray_real_T *in6, const emxArray_real_T *in7, const emxArray_real_T *in8,
  int in9, const emxArray_real_T *in10, double in11, double in12);
static void k_binary_expand_op(emxArray_real_T *in1, const waveform *in2);
static void l_binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
  const emxArray_boolean_T *in3, unsigned int in4, const emxArray_boolean_T *in5);
static void m_binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
  const emxArray_boolean_T *in3);
static void n_binary_expand_op(emxArray_boolean_T *in1, const emxArray_boolean_T
  *in2, const emxArray_boolean_T *in3, const emxArray_boolean_T *in4, const
  emxArray_boolean_T *in5, const emxArray_boolean_T *in6, const
  emxArray_boolean_T *in7, const emxArray_boolean_T *in8, const
  emxArray_boolean_T *in9);
static void o_binary_expand_op(emxArray_boolean_T *in1, const emxArray_real_T
  *in2, int in3, int in4);
static void p_binary_expand_op(emxArray_boolean_T *in1, const emxArray_real_T
  *in2, int in3, int in4, int in5);
static void q_binary_expand_op(emxArray_real_T *in1, double in2, const
  emxArray_real_T *in3);
static void r_binary_expand_op(emxArray_real_T *in1, const waveform *in2, const
  emxArray_real_T *in3);
static void s_binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
  const emxArray_real_T *in3, int in4, int in5);
static void t_binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
  const emxArray_real_T *in3, const emxArray_real_T *in4, const emxArray_real_T *
  in5);
static void u_binary_expand_op(emxArray_boolean_T *in1, const emxArray_real_T
  *in2, const emxArray_real_T *in3, const emxArray_real_T *in4, const
  emxArray_real_T *in5);
static void waveform_findpulse(const waveform *obj, const char
  time_searchtype_data[], const int time_searchtype_size[2], const char
  freq_searchtype_data[], const int freq_searchtype_size[2], const
  emxArray_real_T *excluded_freq_bands_in, emxArray_struct_T *pl_out,
  emxArray_boolean_T *indiv_msk, emxArray_real_T *peak_ind);

/* Function Definitions */
/*
 * Arguments    : emxArray_boolean_T *in1
 *                const emxArray_boolean_T *in2
 *                const emxArray_boolean_T *in3
 * Return Type  : void
 */
static void b_and(emxArray_boolean_T *in1, const emxArray_boolean_T *in2, const
                  emxArray_boolean_T *in3)
{
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  const bool *in2_data;
  const bool *in3_data;
  bool *in1_data;
  in3_data = in3->data;
  in2_data = in2->data;
  i = in1->size[0];
  if (in3->size[0] == 1) {
    in1->size[0] = in2->size[0];
  } else {
    in1->size[0] = in3->size[0];
  }

  emxEnsureCapacity_boolean_T(in1, i);
  in1_data = in1->data;
  stride_0_0 = (in2->size[0] != 1);
  stride_1_0 = (in3->size[0] != 1);
  if (in3->size[0] == 1) {
    loop_ub = in2->size[0];
  } else {
    loop_ub = in3->size[0];
  }

  for (i = 0; i < loop_ub; i++) {
    in1_data[i] = (in2_data[i * stride_0_0] && in3_data[i * stride_1_0]);
  }
}

/*
 * Arguments    : emxArray_boolean_T *in1
 *                const emxArray_boolean_T *in2
 * Return Type  : void
 */
static void c_and(emxArray_boolean_T *in1, const emxArray_boolean_T *in2)
{
  emxArray_boolean_T *b_in1;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  const bool *in2_data;
  bool *b_in1_data;
  bool *in1_data;
  in2_data = in2->data;
  in1_data = in1->data;
  emxInit_boolean_T(&b_in1, 1);
  i = b_in1->size[0];
  if (in2->size[0] == 1) {
    b_in1->size[0] = in1->size[0];
  } else {
    b_in1->size[0] = in2->size[0];
  }

  emxEnsureCapacity_boolean_T(b_in1, i);
  b_in1_data = b_in1->data;
  stride_0_0 = (in1->size[0] != 1);
  stride_1_0 = (in2->size[0] != 1);
  if (in2->size[0] == 1) {
    loop_ub = in1->size[0];
  } else {
    loop_ub = in2->size[0];
  }

  for (i = 0; i < loop_ub; i++) {
    b_in1_data[i] = (in1_data[i * stride_0_0] && in2_data[i * stride_1_0]);
  }

  i = in1->size[0];
  in1->size[0] = b_in1->size[0];
  emxEnsureCapacity_boolean_T(in1, i);
  in1_data = in1->data;
  loop_ub = b_in1->size[0];
  for (i = 0; i < loop_ub; i++) {
    in1_data[i] = b_in1_data[i];
  }

  emxFree_boolean_T(&b_in1);
}

/*
 * Arguments    : waveform *in1
 *                int in2
 *                double in3
 *                const emxArray_real_T *in4
 *                const emxArray_real_T *in5
 * Return Type  : void
 */
static void d_binary_expand_op(waveform *in1, int in2, double in3, const
  emxArray_real_T *in4, const emxArray_real_T *in5)
{
  emxArray_real_T *r;
  const double *in4_data;
  const double *in5_data;
  double *r1;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  in5_data = in5->data;
  in4_data = in4->data;
  emxInit_real_T(&r, 1);
  i = r->size[0];
  r->size[0] = in2 + in4->size[1];
  emxEnsureCapacity_real_T(r, i);
  r1 = r->data;
  for (i = 0; i < in2; i++) {
    r1[i] = 0.0;
  }

  loop_ub = in4->size[1];
  for (i = 0; i < loop_ub; i++) {
    r1[i + in2] = in3 * in4_data[i];
  }

  i = in1->Wf->size[0];
  if (in5->size[1] == 1) {
    in1->Wf->size[0] = r->size[0];
  } else {
    in1->Wf->size[0] = in5->size[1];
  }

  emxEnsureCapacity_real_T(in1->Wf, i);
  stride_0_0 = (r->size[0] != 1);
  stride_1_0 = (in5->size[1] != 1);
  if (in5->size[1] == 1) {
    loop_ub = r->size[0];
  } else {
    loop_ub = in5->size[1];
  }

  for (i = 0; i < loop_ub; i++) {
    in1->Wf->data[i] = r1[i * stride_0_0] + in5_data[i * stride_1_0];
  }

  emxFree_real_T(&r);
}

/*
 * Arguments    : emxArray_boolean_T *in1
 *                const emxArray_real_T *in2
 *                const emxArray_real_T *in3
 *                const emxArray_real_T *in4
 *                const emxArray_real_T *in5
 *                const emxArray_real_T *in6
 *                const emxArray_real_T *in7
 *                const emxArray_real_T *in8
 *                const emxArray_real_T *in9
 * Return Type  : void
 */
static void e_binary_expand_op(emxArray_boolean_T *in1, const emxArray_real_T
  *in2, const emxArray_real_T *in3, const emxArray_real_T *in4, const
  emxArray_real_T *in5, const emxArray_real_T *in6, const emxArray_real_T *in7,
  const emxArray_real_T *in8, const emxArray_real_T *in9)
{
  const double *in2_data;
  const double *in3_data;
  const double *in4_data;
  const double *in5_data;
  const double *in6_data;
  const double *in7_data;
  const double *in8_data;
  const double *in9_data;
  int i;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  int stride_2_1;
  int stride_3_1;
  int stride_4_1;
  int stride_5_1;
  int stride_6_1;
  int stride_7_1;
  bool *in1_data;
  in9_data = in9->data;
  in8_data = in8->data;
  in7_data = in7->data;
  in6_data = in6->data;
  in5_data = in5->data;
  in4_data = in4->data;
  in3_data = in3->data;
  in2_data = in2->data;
  i = in1->size[0] * in1->size[1];
  in1->size[0] = 1;
  if (in9->size[1] == 1) {
    stride_0_1 = in8->size[1];
  } else {
    stride_0_1 = in9->size[1];
  }

  if (stride_0_1 == 1) {
    if (in7->size[1] == 1) {
      stride_0_1 = in6->size[1];
    } else {
      stride_0_1 = in7->size[1];
    }
  } else if (in9->size[1] == 1) {
    stride_0_1 = in8->size[1];
  } else {
    stride_0_1 = in9->size[1];
  }

  if (stride_0_1 == 1) {
    if (in5->size[1] == 1) {
      stride_0_1 = in4->size[1];
    } else {
      stride_0_1 = in5->size[1];
    }

    if (stride_0_1 == 1) {
      if (in3->size[1] == 1) {
        in1->size[1] = in2->size[1];
      } else {
        in1->size[1] = in3->size[1];
      }
    } else if (in5->size[1] == 1) {
      in1->size[1] = in4->size[1];
    } else {
      in1->size[1] = in5->size[1];
    }
  } else {
    if (in9->size[1] == 1) {
      stride_0_1 = in8->size[1];
    } else {
      stride_0_1 = in9->size[1];
    }

    if (stride_0_1 == 1) {
      if (in7->size[1] == 1) {
        in1->size[1] = in6->size[1];
      } else {
        in1->size[1] = in7->size[1];
      }
    } else if (in9->size[1] == 1) {
      in1->size[1] = in8->size[1];
    } else {
      in1->size[1] = in9->size[1];
    }
  }

  emxEnsureCapacity_boolean_T(in1, i);
  in1_data = in1->data;
  stride_0_1 = (in2->size[1] != 1);
  stride_1_1 = (in3->size[1] != 1);
  stride_2_1 = (in4->size[1] != 1);
  stride_3_1 = (in5->size[1] != 1);
  stride_4_1 = (in6->size[1] != 1);
  stride_5_1 = (in7->size[1] != 1);
  stride_6_1 = (in8->size[1] != 1);
  stride_7_1 = (in9->size[1] != 1);
  if (in9->size[1] == 1) {
    i = in8->size[1];
  } else {
    i = in9->size[1];
  }

  if (i == 1) {
    if (in7->size[1] == 1) {
      i = in6->size[1];
    } else {
      i = in7->size[1];
    }
  } else if (in9->size[1] == 1) {
    i = in8->size[1];
  } else {
    i = in9->size[1];
  }

  if (i == 1) {
    if (in5->size[1] == 1) {
      i = in4->size[1];
    } else {
      i = in5->size[1];
    }

    if (i == 1) {
      if (in3->size[1] == 1) {
        loop_ub = in2->size[1];
      } else {
        loop_ub = in3->size[1];
      }
    } else if (in5->size[1] == 1) {
      loop_ub = in4->size[1];
    } else {
      loop_ub = in5->size[1];
    }
  } else {
    if (in9->size[1] == 1) {
      i = in8->size[1];
    } else {
      i = in9->size[1];
    }

    if (i == 1) {
      if (in7->size[1] == 1) {
        loop_ub = in6->size[1];
      } else {
        loop_ub = in7->size[1];
      }
    } else if (in9->size[1] == 1) {
      loop_ub = in8->size[1];
    } else {
      loop_ub = in9->size[1];
    }
  }

  for (i = 0; i < loop_ub; i++) {
    in1_data[i] = ((in2_data[i * stride_0_1] <= in3_data[i * stride_1_1]) &&
                   (in4_data[i * stride_2_1] >= in5_data[i * stride_3_1]) &&
                   ((in6_data[i * stride_4_1] >= in7_data[i * stride_5_1] -
                     100.0) && (in8_data[i * stride_6_1] <= in9_data[i *
      stride_7_1] + 100.0)));
  }
}

/*
 * Arguments    : emxArray_real_T *in1
 *                double in2
 *                double in3
 *                double in4
 *                const emxArray_real_T *in5
 * Return Type  : void
 */
static void f_binary_expand_op(emxArray_real_T *in1, double in2, double in3,
  double in4, const emxArray_real_T *in5)
{
  emxArray_real_T *b_in2;
  const double *in5_data;
  double *in1_data;
  double *in2_data;
  int i;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  in5_data = in5->data;
  in1_data = in1->data;
  emxInit_real_T(&b_in2, 2);
  i = b_in2->size[0] * b_in2->size[1];
  b_in2->size[0] = 1;
  if (in5->size[1] == 1) {
    b_in2->size[1] = in1->size[1];
  } else {
    b_in2->size[1] = in5->size[1];
  }

  emxEnsureCapacity_real_T(b_in2, i);
  in2_data = b_in2->data;
  stride_0_1 = (in1->size[1] != 1);
  stride_1_1 = (in5->size[1] != 1);
  if (in5->size[1] == 1) {
    loop_ub = in1->size[1];
  } else {
    loop_ub = in5->size[1];
  }

  for (i = 0; i < loop_ub; i++) {
    in2_data[i] = (in2 + in3 * in1_data[i * stride_0_1]) + in4 * in5_data[i *
      stride_1_1];
  }

  i = in1->size[0] * in1->size[1];
  in1->size[0] = 1;
  in1->size[1] = b_in2->size[1];
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  loop_ub = b_in2->size[1];
  for (i = 0; i < loop_ub; i++) {
    in1_data[i] = in2_data[i];
  }

  emxFree_real_T(&b_in2);
}

/*
 * Arguments    : emxArray_real_T *in1
 *                double in2
 *                double in3
 *                const emxArray_real_T *in4
 *                double in5
 * Return Type  : void
 */
static void g_binary_expand_op(emxArray_real_T *in1, double in2, double in3,
  const emxArray_real_T *in4, double in5)
{
  emxArray_real_T *b_in2;
  const double *in4_data;
  double *in1_data;
  double *in2_data;
  int i;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  in4_data = in4->data;
  in1_data = in1->data;
  emxInit_real_T(&b_in2, 2);
  i = b_in2->size[0] * b_in2->size[1];
  b_in2->size[0] = 1;
  if (in1->size[1] == 1) {
    b_in2->size[1] = in4->size[1];
  } else {
    b_in2->size[1] = in1->size[1];
  }

  emxEnsureCapacity_real_T(b_in2, i);
  in2_data = b_in2->data;
  stride_0_1 = (in4->size[1] != 1);
  stride_1_1 = (in1->size[1] != 1);
  if (in1->size[1] == 1) {
    loop_ub = in4->size[1];
  } else {
    loop_ub = in1->size[1];
  }

  for (i = 0; i < loop_ub; i++) {
    in2_data[i] = (in2 + in3 * in4_data[i * stride_0_1]) - in5 * in1_data[i *
      stride_1_1];
  }

  i = in1->size[0] * in1->size[1];
  in1->size[0] = 1;
  in1->size[1] = b_in2->size[1];
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  loop_ub = b_in2->size[1];
  for (i = 0; i < loop_ub; i++) {
    in1_data[i] = in2_data[i];
  }

  emxFree_real_T(&b_in2);
}

/*
 * Arguments    : emxArray_boolean_T *in1
 *                unsigned int in2
 *                const emxArray_boolean_T *in3
 *                const emxArray_real_T *in4
 *                double in5
 *                const emxArray_real_T *in6
 *                const emxArray_real_T *in7
 *                const emxArray_real_T *in8
 *                int in9
 *                const emxArray_real_T *in10
 *                double in11
 *                double in12
 * Return Type  : void
 */
static void h_binary_expand_op(emxArray_boolean_T *in1, unsigned int in2, const
  emxArray_boolean_T *in3, const emxArray_real_T *in4, double in5, const
  emxArray_real_T *in6, const emxArray_real_T *in7, const emxArray_real_T *in8,
  int in9, const emxArray_real_T *in10, double in11, double in12)
{
  emxArray_boolean_T *b_in1;
  const double *in10_data;
  const double *in4_data;
  const double *in6_data;
  const double *in7_data;
  const double *in8_data;
  double b_in8;
  double c_in8;
  double d_in8;
  double in8_tmp;
  double in8_tmp_tmp;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  int stride_2_0;
  int stride_3_0;
  int stride_4_0;
  int stride_5_0;
  const bool *in3_data;
  bool *b_in1_data;
  bool *in1_data;
  in10_data = in10->data;
  in8_data = in8->data;
  in7_data = in7->data;
  in6_data = in6->data;
  in4_data = in4->data;
  in3_data = in3->data;
  in1_data = in1->data;
  in8_tmp_tmp = in8_data[((int)in10_data[(int)in2 - 1] + in8->size[0] * in9) - 1];
  in8_tmp = in8_tmp_tmp + in11;
  b_in8 = in8_tmp + in12;
  c_in8 = in8_tmp - in12;
  in8_tmp = in8_tmp_tmp - in11;
  d_in8 = in8_tmp - in12;
  in8_tmp_tmp = in8_tmp + in12;
  emxInit_boolean_T(&b_in1, 1);
  i = b_in1->size[0];
  if (in7->size[0] == 1) {
    if (in6->size[0] == 1) {
      stride_0_0 = in4->size[0];
    } else {
      stride_0_0 = in6->size[0];
    }
  } else {
    stride_0_0 = in7->size[0];
  }

  if (in8->size[0] == 1) {
    if (stride_0_0 == 1) {
      stride_0_0 = in3->size[0];
    } else if (in7->size[0] == 1) {
      if (in6->size[0] == 1) {
        stride_0_0 = in4->size[0];
      } else {
        stride_0_0 = in6->size[0];
      }
    } else {
      stride_0_0 = in7->size[0];
    }
  } else {
    stride_0_0 = in8->size[0];
  }

  if (stride_0_0 == 1) {
    b_in1->size[0] = in1->size[0];
  } else if (in8->size[0] == 1) {
    if (in7->size[0] == 1) {
      if (in6->size[0] == 1) {
        stride_0_0 = in4->size[0];
      } else {
        stride_0_0 = in6->size[0];
      }
    } else {
      stride_0_0 = in7->size[0];
    }

    if (stride_0_0 == 1) {
      b_in1->size[0] = in3->size[0];
    } else if (in7->size[0] == 1) {
      if (in6->size[0] == 1) {
        b_in1->size[0] = in4->size[0];
      } else {
        b_in1->size[0] = in6->size[0];
      }
    } else {
      b_in1->size[0] = in7->size[0];
    }
  } else {
    b_in1->size[0] = in8->size[0];
  }

  emxEnsureCapacity_boolean_T(b_in1, i);
  b_in1_data = b_in1->data;
  stride_0_0 = (in1->size[0] != 1);
  stride_1_0 = (in3->size[0] != 1);
  stride_2_0 = (in4->size[0] != 1);
  stride_3_0 = (in6->size[0] != 1);
  stride_4_0 = (in7->size[0] != 1);
  stride_5_0 = (in8->size[0] != 1);
  if (in7->size[0] == 1) {
    if (in6->size[0] == 1) {
      i = in4->size[0];
    } else {
      i = in6->size[0];
    }
  } else {
    i = in7->size[0];
  }

  if (in8->size[0] == 1) {
    if (i == 1) {
      i = in3->size[0];
    } else if (in7->size[0] == 1) {
      if (in6->size[0] == 1) {
        i = in4->size[0];
      } else {
        i = in6->size[0];
      }
    } else {
      i = in7->size[0];
    }
  } else {
    i = in8->size[0];
  }

  if (i == 1) {
    loop_ub = in1->size[0];
  } else if (in8->size[0] == 1) {
    if (in7->size[0] == 1) {
      if (in6->size[0] == 1) {
        i = in4->size[0];
      } else {
        i = in6->size[0];
      }
    } else {
      i = in7->size[0];
    }

    if (i == 1) {
      loop_ub = in3->size[0];
    } else if (in7->size[0] == 1) {
      if (in6->size[0] == 1) {
        loop_ub = in4->size[0];
      } else {
        loop_ub = in6->size[0];
      }
    } else {
      loop_ub = in7->size[0];
    }
  } else {
    loop_ub = in8->size[0];
  }

  for (i = 0; i < loop_ub; i++) {
    in8_tmp = in8_data[i * stride_5_0 + in8->size[0] * in9];
    b_in1_data[i] = (in1_data[i * stride_0_0 + in1->size[0] * ((int)in2 - 1)] ||
                     in1_data[i * stride_0_0 + in1->size[0] * (int)in2] ||
                     (in3_data[i * stride_1_0] || ((in4_data[i * stride_2_0] <=
      in5) || (in6_data[i * stride_3_0] <= in5) || (in7_data[i * stride_4_0] <=
      in5)) || (((in8_tmp < b_in8) && (in8_tmp > c_in8)) || ((in8_tmp > d_in8) &&
      (in8_tmp < in8_tmp_tmp)))));
  }

  loop_ub = b_in1->size[0];
  for (i = 0; i < loop_ub; i++) {
    in1_data[i + in1->size[0] * (int)in2] = b_in1_data[i];
  }

  emxFree_boolean_T(&b_in1);
}

/*
 * Arguments    : emxArray_real_T *in1
 *                const waveform *in2
 * Return Type  : void
 */
static void k_binary_expand_op(emxArray_real_T *in1, const waveform *in2)
{
  emxArray_real_T *b_in1;
  double *b_in1_data;
  double *in1_data;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  int stride_2_0;
  in1_data = in1->data;
  emxInit_real_T(&b_in1, 1);
  i = b_in1->size[0];
  if (in2->thresh.threshVecFine->size[0] == 1) {
    stride_0_0 = in1->size[0];
  } else {
    stride_0_0 = in2->thresh.threshVecFine->size[0];
  }

  if (stride_0_0 == 1) {
    b_in1->size[0] = in1->size[0];
  } else if (in2->thresh.threshVecFine->size[0] == 1) {
    b_in1->size[0] = in1->size[0];
  } else {
    b_in1->size[0] = in2->thresh.threshVecFine->size[0];
  }

  emxEnsureCapacity_real_T(b_in1, i);
  b_in1_data = b_in1->data;
  stride_0_0 = (in1->size[0] != 1);
  stride_1_0 = (in1->size[0] != 1);
  stride_2_0 = (in2->thresh.threshVecFine->size[0] != 1);
  if (in2->thresh.threshVecFine->size[0] == 1) {
    i = in1->size[0];
  } else {
    i = in2->thresh.threshVecFine->size[0];
  }

  if (i == 1) {
    loop_ub = in1->size[0];
  } else if (in2->thresh.threshVecFine->size[0] == 1) {
    loop_ub = in1->size[0];
  } else {
    loop_ub = in2->thresh.threshVecFine->size[0];
  }

  for (i = 0; i < loop_ub; i++) {
    b_in1_data[i] = in1_data[i * stride_0_0] * (double)(in1_data[i * stride_1_0]
      >= in2->thresh.threshVecFine->data[i * stride_2_0]);
  }

  i = in1->size[0];
  in1->size[0] = b_in1->size[0];
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  loop_ub = b_in1->size[0];
  for (i = 0; i < loop_ub; i++) {
    in1_data[i] = b_in1_data[i];
  }

  emxFree_real_T(&b_in1);
}

/*
 * Arguments    : emxArray_real_T *in1
 *                const emxArray_real_T *in2
 *                const emxArray_boolean_T *in3
 *                unsigned int in4
 *                const emxArray_boolean_T *in5
 * Return Type  : void
 */
static void l_binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
  const emxArray_boolean_T *in3, unsigned int in4, const emxArray_boolean_T *in5)
{
  const double *in2_data;
  double *in1_data;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  int stride_2_0;
  const bool *in3_data;
  const bool *in5_data;
  in5_data = in5->data;
  in3_data = in3->data;
  in2_data = in2->data;
  i = in1->size[0];
  if (in5->size[0] == 1) {
    if (in3->size[0] == 1) {
      in1->size[0] = in2->size[0];
    } else {
      in1->size[0] = in3->size[0];
    }
  } else {
    in1->size[0] = in5->size[0];
  }

  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  stride_0_0 = (in2->size[0] != 1);
  stride_1_0 = (in3->size[0] != 1);
  stride_2_0 = (in5->size[0] != 1);
  if (in5->size[0] == 1) {
    if (in3->size[0] == 1) {
      loop_ub = in2->size[0];
    } else {
      loop_ub = in3->size[0];
    }
  } else {
    loop_ub = in5->size[0];
  }

  for (i = 0; i < loop_ub; i++) {
    in1_data[i] = in2_data[i * stride_0_0] * (double)!in3_data[i * stride_1_0 +
      in3->size[0] * (int)in4] * (double)in5_data[i * stride_2_0];
  }
}

/*
 * Arguments    : emxArray_real_T *in1
 *                const emxArray_real_T *in2
 *                const emxArray_boolean_T *in3
 * Return Type  : void
 */
static void m_binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
  const emxArray_boolean_T *in3)
{
  const double *in2_data;
  double *in1_data;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  const bool *in3_data;
  in3_data = in3->data;
  in2_data = in2->data;
  i = in1->size[0];
  if (in3->size[0] == 1) {
    in1->size[0] = in2->size[0];
  } else {
    in1->size[0] = in3->size[0];
  }

  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  stride_0_0 = (in2->size[0] != 1);
  stride_1_0 = (in3->size[0] != 1);
  if (in3->size[0] == 1) {
    loop_ub = in2->size[0];
  } else {
    loop_ub = in3->size[0];
  }

  for (i = 0; i < loop_ub; i++) {
    in1_data[i] = in2_data[i * stride_0_0] * (double)in3_data[i * stride_1_0];
  }
}

/*
 * Arguments    : emxArray_boolean_T *in1
 *                const emxArray_boolean_T *in2
 *                const emxArray_boolean_T *in3
 *                const emxArray_boolean_T *in4
 *                const emxArray_boolean_T *in5
 *                const emxArray_boolean_T *in6
 *                const emxArray_boolean_T *in7
 *                const emxArray_boolean_T *in8
 *                const emxArray_boolean_T *in9
 * Return Type  : void
 */
static void n_binary_expand_op(emxArray_boolean_T *in1, const emxArray_boolean_T
  *in2, const emxArray_boolean_T *in3, const emxArray_boolean_T *in4, const
  emxArray_boolean_T *in5, const emxArray_boolean_T *in6, const
  emxArray_boolean_T *in7, const emxArray_boolean_T *in8, const
  emxArray_boolean_T *in9)
{
  emxArray_boolean_T *b_in4;
  emxArray_boolean_T *b_in7;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  int stride_2_0;
  int stride_3_0;
  int stride_4_0;
  int stride_5_0;
  int stride_6_0;
  int stride_7_0;
  const bool *in2_data;
  const bool *in3_data;
  const bool *in4_data;
  const bool *in5_data;
  const bool *in6_data;
  const bool *in7_data;
  const bool *in8_data;
  const bool *in9_data;
  bool *b_in4_data;
  bool *b_in7_data;
  bool *in1_data;
  in9_data = in9->data;
  in8_data = in8->data;
  in7_data = in7->data;
  in6_data = in6->data;
  in5_data = in5->data;
  in4_data = in4->data;
  in3_data = in3->data;
  in2_data = in2->data;
  emxInit_boolean_T(&b_in4, 1);
  i = b_in4->size[0];
  if (in5->size[0] == 1) {
    b_in4->size[0] = in4->size[0];
  } else {
    b_in4->size[0] = in5->size[0];
  }

  emxEnsureCapacity_boolean_T(b_in4, i);
  b_in4_data = b_in4->data;
  stride_0_0 = (in4->size[0] != 1);
  stride_1_0 = (in5->size[0] != 1);
  if (in5->size[0] == 1) {
    loop_ub = in4->size[0];
  } else {
    loop_ub = in5->size[0];
  }

  for (i = 0; i < loop_ub; i++) {
    b_in4_data[i] = ((!in4_data[i * stride_0_0]) && in5_data[i * stride_1_0]);
  }

  i = in1->size[0];
  in1->size[0] = b_in4->size[0] + 1;
  emxEnsureCapacity_boolean_T(in1, i);
  in1_data = in1->data;
  in1_data[0] = true;
  loop_ub = b_in4->size[0];
  for (i = 0; i < loop_ub; i++) {
    in1_data[i + 1] = b_in4_data[i];
  }

  i = b_in4->size[0];
  if (in8->size[0] == 1) {
    b_in4->size[0] = in7->size[0];
  } else {
    b_in4->size[0] = in8->size[0];
  }

  emxEnsureCapacity_boolean_T(b_in4, i);
  b_in4_data = b_in4->data;
  stride_0_0 = (in7->size[0] != 1);
  stride_1_0 = (in8->size[0] != 1);
  if (in8->size[0] == 1) {
    loop_ub = in7->size[0];
  } else {
    loop_ub = in8->size[0];
  }

  for (i = 0; i < loop_ub; i++) {
    b_in4_data[i] = ((!in7_data[i * stride_0_0]) && in8_data[i * stride_1_0]);
  }

  emxInit_boolean_T(&b_in7, 1);
  i = b_in7->size[0];
  b_in7->size[0] = b_in4->size[0] + 1;
  emxEnsureCapacity_boolean_T(b_in7, i);
  b_in7_data = b_in7->data;
  loop_ub = b_in4->size[0];
  for (i = 0; i < loop_ub; i++) {
    b_in7_data[i] = b_in4_data[i];
  }

  b_in7_data[b_in4->size[0]] = true;
  i = b_in4->size[0];
  if (in3->size[0] == 1) {
    stride_0_0 = in9->size[0];
  } else {
    stride_0_0 = in3->size[0];
  }

  if (stride_0_0 == 1) {
    stride_0_0 = b_in7->size[0];
  } else if (in3->size[0] == 1) {
    stride_0_0 = in9->size[0];
  } else {
    stride_0_0 = in3->size[0];
  }

  if (stride_0_0 == 1) {
    if (in6->size[0] == 1) {
      stride_0_0 = in2->size[0];
    } else {
      stride_0_0 = in6->size[0];
    }

    if (stride_0_0 == 1) {
      stride_0_0 = in1->size[0];
    } else if (in6->size[0] == 1) {
      stride_0_0 = in2->size[0];
    } else {
      stride_0_0 = in6->size[0];
    }

    if (stride_0_0 == 1) {
      if (in3->size[0] == 1) {
        b_in4->size[0] = in2->size[0];
      } else {
        b_in4->size[0] = in3->size[0];
      }
    } else {
      if (in6->size[0] == 1) {
        stride_0_0 = in2->size[0];
      } else {
        stride_0_0 = in6->size[0];
      }

      if (stride_0_0 == 1) {
        b_in4->size[0] = in1->size[0];
      } else if (in6->size[0] == 1) {
        b_in4->size[0] = in2->size[0];
      } else {
        b_in4->size[0] = in6->size[0];
      }
    }
  } else {
    if (in3->size[0] == 1) {
      stride_0_0 = in9->size[0];
    } else {
      stride_0_0 = in3->size[0];
    }

    if (stride_0_0 == 1) {
      b_in4->size[0] = b_in7->size[0];
    } else if (in3->size[0] == 1) {
      b_in4->size[0] = in9->size[0];
    } else {
      b_in4->size[0] = in3->size[0];
    }
  }

  emxEnsureCapacity_boolean_T(b_in4, i);
  b_in4_data = b_in4->data;
  stride_0_0 = (in2->size[0] != 1);
  stride_1_0 = (in3->size[0] != 1);
  stride_2_0 = (in1->size[0] != 1);
  stride_3_0 = (in2->size[0] != 1);
  stride_4_0 = (in6->size[0] != 1);
  stride_5_0 = (b_in7->size[0] != 1);
  stride_6_0 = (in9->size[0] != 1);
  stride_7_0 = (in3->size[0] != 1);
  if (in3->size[0] == 1) {
    i = in9->size[0];
  } else {
    i = in3->size[0];
  }

  if (i == 1) {
    i = b_in7->size[0];
  } else if (in3->size[0] == 1) {
    i = in9->size[0];
  } else {
    i = in3->size[0];
  }

  if (i == 1) {
    if (in6->size[0] == 1) {
      i = in2->size[0];
    } else {
      i = in6->size[0];
    }

    if (i == 1) {
      i = in1->size[0];
    } else if (in6->size[0] == 1) {
      i = in2->size[0];
    } else {
      i = in6->size[0];
    }

    if (i == 1) {
      if (in3->size[0] == 1) {
        loop_ub = in2->size[0];
      } else {
        loop_ub = in3->size[0];
      }
    } else {
      if (in6->size[0] == 1) {
        i = in2->size[0];
      } else {
        i = in6->size[0];
      }

      if (i == 1) {
        loop_ub = in1->size[0];
      } else if (in6->size[0] == 1) {
        loop_ub = in2->size[0];
      } else {
        loop_ub = in6->size[0];
      }
    }
  } else {
    if (in3->size[0] == 1) {
      i = in9->size[0];
    } else {
      i = in3->size[0];
    }

    if (i == 1) {
      loop_ub = b_in7->size[0];
    } else if (in3->size[0] == 1) {
      loop_ub = in9->size[0];
    } else {
      loop_ub = in3->size[0];
    }
  }

  for (i = 0; i < loop_ub; i++) {
    b_in4_data[i] = ((in2_data[i * stride_0_0] && in3_data[i * stride_1_0]) ||
                     (in1_data[i * stride_2_0] && (in2_data[i * stride_3_0] &&
      in6_data[i * stride_4_0])) || (b_in7_data[i * stride_5_0] && (in9_data[i *
      stride_6_0] && in3_data[i * stride_7_0])));
  }

  emxFree_boolean_T(&b_in7);
  i = in1->size[0];
  in1->size[0] = b_in4->size[0];
  emxEnsureCapacity_boolean_T(in1, i);
  in1_data = in1->data;
  loop_ub = b_in4->size[0];
  for (i = 0; i < loop_ub; i++) {
    in1_data[i] = b_in4_data[i];
  }

  emxFree_boolean_T(&b_in4);
}

/*
 * Arguments    : emxArray_boolean_T *in1
 *                const emxArray_real_T *in2
 *                int in3
 *                int in4
 * Return Type  : void
 */
static void o_binary_expand_op(emxArray_boolean_T *in1, const emxArray_real_T
  *in2, int in3, int in4)
{
  emxArray_real_T *r;
  const double *in2_data;
  double *r1;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  bool *in1_data;
  in2_data = in2->data;
  emxInit_real_T(&r, 1);
  i = r->size[0];
  r->size[0] = in4 + 2;
  emxEnsureCapacity_real_T(r, i);
  r1 = r->data;
  r1[0] = 0.0;
  for (i = 0; i <= in4; i++) {
    r1[i + 1] = in2_data[i];
  }

  i = in1->size[0];
  if (r->size[0] == 1) {
    in1->size[0] = in3 + 1;
  } else {
    in1->size[0] = r->size[0];
  }

  emxEnsureCapacity_boolean_T(in1, i);
  in1_data = in1->data;
  stride_0_0 = (in3 + 1 != 1);
  stride_1_0 = (r->size[0] != 1);
  if (r->size[0] == 1) {
    loop_ub = in3 + 1;
  } else {
    loop_ub = r->size[0];
  }

  for (i = 0; i < loop_ub; i++) {
    in1_data[i] = (in2_data[i * stride_0_0] > r1[i * stride_1_0]);
  }

  emxFree_real_T(&r);
}

/*
 * Arguments    : emxArray_boolean_T *in1
 *                const emxArray_real_T *in2
 *                int in3
 *                int in4
 *                int in5
 * Return Type  : void
 */
static void p_binary_expand_op(emxArray_boolean_T *in1, const emxArray_real_T
  *in2, int in3, int in4, int in5)
{
  emxArray_real_T *b_in2;
  const double *in2_data;
  double *b_in2_data;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  bool *in1_data;
  in2_data = in2->data;
  emxInit_real_T(&b_in2, 1);
  loop_ub = in5 - in4;
  i = b_in2->size[0];
  b_in2->size[0] = loop_ub + 2;
  emxEnsureCapacity_real_T(b_in2, i);
  b_in2_data = b_in2->data;
  for (i = 0; i <= loop_ub; i++) {
    b_in2_data[i] = in2_data[in4 + i];
  }

  b_in2_data[loop_ub + 1] = 0.0;
  i = in1->size[0];
  if (b_in2->size[0] == 1) {
    in1->size[0] = in3 + 1;
  } else {
    in1->size[0] = b_in2->size[0];
  }

  emxEnsureCapacity_boolean_T(in1, i);
  in1_data = in1->data;
  stride_0_0 = (in3 + 1 != 1);
  stride_1_0 = (b_in2->size[0] != 1);
  if (b_in2->size[0] == 1) {
    loop_ub = in3 + 1;
  } else {
    loop_ub = b_in2->size[0];
  }

  for (i = 0; i < loop_ub; i++) {
    in1_data[i] = (in2_data[i * stride_0_0] > b_in2_data[i * stride_1_0]);
  }

  emxFree_real_T(&b_in2);
}

/*
 * Arguments    : emxArray_real_T *in1
 *                double in2
 *                const emxArray_real_T *in3
 * Return Type  : void
 */
static void q_binary_expand_op(emxArray_real_T *in1, double in2, const
  emxArray_real_T *in3)
{
  emxArray_real_T *b_in2;
  const double *in3_data;
  double *in1_data;
  double *in2_data;
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  in3_data = in3->data;
  in1_data = in1->data;
  emxInit_real_T(&b_in2, 2);
  i = b_in2->size[0] * b_in2->size[1];
  if (in1->size[0] == 1) {
    b_in2->size[0] = in3->size[0];
  } else {
    b_in2->size[0] = in1->size[0];
  }

  if (in1->size[1] == 1) {
    b_in2->size[1] = in3->size[1];
  } else {
    b_in2->size[1] = in1->size[1];
  }

  emxEnsureCapacity_real_T(b_in2, i);
  in2_data = b_in2->data;
  stride_0_0 = (in3->size[0] != 1);
  stride_0_1 = (in3->size[1] != 1);
  stride_1_0 = (in1->size[0] != 1);
  stride_1_1 = (in1->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  if (in1->size[1] == 1) {
    loop_ub = in3->size[1];
  } else {
    loop_ub = in1->size[1];
  }

  for (i = 0; i < loop_ub; i++) {
    i1 = in1->size[0];
    if (i1 == 1) {
      b_loop_ub = in3->size[0];
    } else {
      b_loop_ub = i1;
    }

    for (i1 = 0; i1 < b_loop_ub; i1++) {
      in2_data[i1 + b_in2->size[0] * i] = in2 * in3_data[i1 * stride_0_0 +
        in3->size[0] * aux_0_1] - in1_data[i1 * stride_1_0 + in1->size[0] *
        aux_1_1];
    }

    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }

  i = in1->size[0] * in1->size[1];
  in1->size[0] = b_in2->size[0];
  in1->size[1] = b_in2->size[1];
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  loop_ub = b_in2->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = b_in2->size[0];
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      in1_data[i1 + in1->size[0] * i] = in2_data[i1 + b_in2->size[0] * i];
    }
  }

  emxFree_real_T(&b_in2);
}

/*
 * Arguments    : emxArray_real_T *in1
 *                const waveform *in2
 *                const emxArray_real_T *in3
 * Return Type  : void
 */
static void r_binary_expand_op(emxArray_real_T *in1, const waveform *in2, const
  emxArray_real_T *in3)
{
  emxArray_creal_T *b_in2;
  creal_T *in2_data;
  const double *in3_data;
  int aux_0_1;
  int aux_1_1;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  in3_data = in3->data;
  emxInit_creal_T(&b_in2, 2);
  i = b_in2->size[0] * b_in2->size[1];
  if (in3->size[0] == 1) {
    b_in2->size[0] = in2->stft->S->size[0];
  } else {
    b_in2->size[0] = in3->size[0];
  }

  if (in3->size[1] == 1) {
    b_in2->size[1] = in2->stft->S->size[1];
  } else {
    b_in2->size[1] = in3->size[1];
  }

  emxEnsureCapacity_creal_T(b_in2, i);
  in2_data = b_in2->data;
  stride_0_0 = (in2->stft->S->size[0] != 1);
  stride_0_1 = (in2->stft->S->size[1] != 1);
  stride_1_0 = (in3->size[0] != 1);
  stride_1_1 = (in3->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  if (in3->size[1] == 1) {
    loop_ub = in2->stft->S->size[1];
  } else {
    loop_ub = in3->size[1];
  }

  for (i = 0; i < loop_ub; i++) {
    int b_loop_ub;
    i1 = in3->size[0];
    if (i1 == 1) {
      b_loop_ub = in2->stft->S->size[0];
    } else {
      b_loop_ub = i1;
    }

    for (i1 = 0; i1 < b_loop_ub; i1++) {
      in2_data[i1 + b_in2->size[0] * i].re = in2->stft->S->data[i1 * stride_0_0
        + in2->stft->S->size[0] * aux_0_1].re + in3_data[i1 * stride_1_0 +
        in3->size[0] * aux_1_1];
      in2_data[i1 + b_in2->size[0] * i].im = in2->stft->S->data[i1 * stride_0_0
        + in2->stft->S->size[0] * aux_0_1].im;
    }

    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }

  b_abs(b_in2, in1);
  emxFree_creal_T(&b_in2);
}

/*
 * Arguments    : emxArray_real_T *in1
 *                const emxArray_real_T *in2
 *                const emxArray_real_T *in3
 *                int in4
 *                int in5
 * Return Type  : void
 */
static void s_binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
  const emxArray_real_T *in3, int in4, int in5)
{
  emxArray_real_T *b_in2;
  const double *in2_data;
  const double *in3_data;
  double *b_in2_data;
  double *in1_data;
  int aux_0_1;
  int aux_1_1;
  int aux_2_1;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  int stride_2_0;
  int stride_2_1;
  in3_data = in3->data;
  in2_data = in2->data;
  in1_data = in1->data;
  emxInit_real_T(&b_in2, 2);
  i = b_in2->size[0] * b_in2->size[1];
  if (in3->size[0] == 1) {
    if (in1->size[0] == 1) {
      b_in2->size[0] = in2->size[0];
    } else {
      b_in2->size[0] = in1->size[0];
    }
  } else {
    b_in2->size[0] = in3->size[0];
  }

  if (in3->size[1] == 1) {
    if (in1->size[1] == 1) {
      b_in2->size[1] = in2->size[1];
    } else {
      b_in2->size[1] = in1->size[1];
    }
  } else {
    b_in2->size[1] = in3->size[1];
  }

  emxEnsureCapacity_real_T(b_in2, i);
  b_in2_data = b_in2->data;
  stride_0_0 = (in2->size[0] != 1);
  stride_0_1 = (in2->size[1] != 1);
  stride_1_0 = (in1->size[0] != 1);
  stride_1_1 = (in1->size[1] != 1);
  stride_2_0 = (in3->size[0] != 1);
  stride_2_1 = (in3->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  aux_2_1 = 0;
  if (in3->size[1] == 1) {
    if (in1->size[1] == 1) {
      loop_ub = in2->size[1];
    } else {
      loop_ub = in1->size[1];
    }
  } else {
    loop_ub = in3->size[1];
  }

  for (i = 0; i < loop_ub; i++) {
    int b_loop_ub;
    i1 = in3->size[0];
    b_loop_ub = in1->size[0];
    if (i1 == 1) {
      if (b_loop_ub == 1) {
        b_loop_ub = in2->size[0];
      }
    } else {
      b_loop_ub = i1;
    }

    for (i1 = 0; i1 < b_loop_ub; i1++) {
      b_in2_data[i1 + b_in2->size[0] * i] = (in2_data[i1 * stride_0_0 +
        in2->size[0] * aux_0_1] + in1_data[i1 * stride_1_0 + in1->size[0] *
        aux_1_1]) + in3_data[i1 * stride_2_0 + in3->size[0] * aux_2_1];
    }

    aux_2_1 += stride_2_1;
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }

  double b_in4[2];
  b_in4[0] = (unsigned int)in4;
  b_in4[1] = (unsigned int)in5;
  imresize(b_in2, b_in4, in1);
  emxFree_real_T(&b_in2);
}

/*
 * Arguments    : emxArray_real_T *in1
 *                const emxArray_real_T *in2
 *                const emxArray_real_T *in3
 *                const emxArray_real_T *in4
 *                const emxArray_real_T *in5
 * Return Type  : void
 */
static void t_binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
  const emxArray_real_T *in3, const emxArray_real_T *in4, const emxArray_real_T *
  in5)
{
  emxArray_real_T *b_in1;
  const double *in2_data;
  const double *in3_data;
  const double *in4_data;
  const double *in5_data;
  double *b_in1_data;
  double *in1_data;
  int aux_0_1;
  int aux_1_1;
  int aux_2_1;
  int aux_3_1;
  int aux_4_1;
  int b_loop_ub;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  int stride_2_0;
  int stride_2_1;
  int stride_3_0;
  int stride_3_1;
  int stride_4_0;
  int stride_4_1;
  in5_data = in5->data;
  in4_data = in4->data;
  in3_data = in3->data;
  in2_data = in2->data;
  in1_data = in1->data;
  emxInit_real_T(&b_in1, 2);
  i = b_in1->size[0] * b_in1->size[1];
  if (in5->size[0] == 1) {
    if (in4->size[0] == 1) {
      if (in3->size[0] == 1) {
        if (in2->size[0] == 1) {
          b_in1->size[0] = in1->size[0];
        } else {
          b_in1->size[0] = in2->size[0];
        }
      } else {
        b_in1->size[0] = in3->size[0];
      }
    } else {
      b_in1->size[0] = in4->size[0];
    }
  } else {
    b_in1->size[0] = in5->size[0];
  }

  if (in5->size[1] == 1) {
    if (in4->size[1] == 1) {
      if (in3->size[1] == 1) {
        if (in2->size[1] == 1) {
          b_in1->size[1] = in1->size[1];
        } else {
          b_in1->size[1] = in2->size[1];
        }
      } else {
        b_in1->size[1] = in3->size[1];
      }
    } else {
      b_in1->size[1] = in4->size[1];
    }
  } else {
    b_in1->size[1] = in5->size[1];
  }

  emxEnsureCapacity_real_T(b_in1, i);
  b_in1_data = b_in1->data;
  stride_0_0 = (in1->size[0] != 1);
  stride_0_1 = (in1->size[1] != 1);
  stride_1_0 = (in2->size[0] != 1);
  stride_1_1 = (in2->size[1] != 1);
  stride_2_0 = (in3->size[0] != 1);
  stride_2_1 = (in3->size[1] != 1);
  stride_3_0 = (in4->size[0] != 1);
  stride_3_1 = (in4->size[1] != 1);
  stride_4_0 = (in5->size[0] != 1);
  stride_4_1 = (in5->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  aux_2_1 = 0;
  aux_3_1 = 0;
  aux_4_1 = 0;
  if (in5->size[1] == 1) {
    if (in4->size[1] == 1) {
      if (in3->size[1] == 1) {
        if (in2->size[1] == 1) {
          loop_ub = in1->size[1];
        } else {
          loop_ub = in2->size[1];
        }
      } else {
        loop_ub = in3->size[1];
      }
    } else {
      loop_ub = in4->size[1];
    }
  } else {
    loop_ub = in5->size[1];
  }

  for (i = 0; i < loop_ub; i++) {
    int i2;
    int i3;
    i1 = in5->size[0];
    b_loop_ub = in4->size[0];
    i2 = in3->size[0];
    i3 = in2->size[0];
    if (i1 == 1) {
      if (b_loop_ub == 1) {
        if (i2 == 1) {
          if (i3 == 1) {
            b_loop_ub = in1->size[0];
          } else {
            b_loop_ub = i3;
          }
        } else {
          b_loop_ub = i2;
        }
      }
    } else {
      b_loop_ub = i1;
    }

    for (i1 = 0; i1 < b_loop_ub; i1++) {
      b_in1_data[i1 + b_in1->size[0] * i] = (((in1_data[i1 * stride_0_0 +
        in1->size[0] * aux_0_1] + in2_data[i1 * stride_1_0 + in2->size[0] *
        aux_1_1]) + in3_data[i1 * stride_2_0 + in3->size[0] * aux_2_1]) +
        in4_data[i1 * stride_3_0 + in4->size[0] * aux_3_1]) + in5_data[i1 *
        stride_4_0 + in5->size[0] * aux_4_1];
    }

    aux_4_1 += stride_4_1;
    aux_3_1 += stride_3_1;
    aux_2_1 += stride_2_1;
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }

  i = in1->size[0] * in1->size[1];
  in1->size[0] = b_in1->size[0];
  in1->size[1] = b_in1->size[1];
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  loop_ub = b_in1->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = b_in1->size[0];
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      in1_data[i1 + in1->size[0] * i] = b_in1_data[i1 + b_in1->size[0] * i];
    }
  }

  emxFree_real_T(&b_in1);
}

/*
 * Arguments    : emxArray_boolean_T *in1
 *                const emxArray_real_T *in2
 *                const emxArray_real_T *in3
 *                const emxArray_real_T *in4
 *                const emxArray_real_T *in5
 * Return Type  : void
 */
static void u_binary_expand_op(emxArray_boolean_T *in1, const emxArray_real_T
  *in2, const emxArray_real_T *in3, const emxArray_real_T *in4, const
  emxArray_real_T *in5)
{
  emxArray_boolean_T *b_in2;
  const double *in2_data;
  const double *in3_data;
  const double *in4_data;
  const double *in5_data;
  int aux_0_1;
  int aux_1_1;
  int aux_2_1;
  int aux_3_1;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  int stride_2_0;
  int stride_2_1;
  int stride_3_0;
  int stride_3_1;
  bool *b_in2_data;
  in5_data = in5->data;
  in4_data = in4->data;
  in3_data = in3->data;
  in2_data = in2->data;
  emxInit_boolean_T(&b_in2, 2);
  i = b_in2->size[0] * b_in2->size[1];
  if (in5->size[0] == 1) {
    i1 = in4->size[0];
  } else {
    i1 = in5->size[0];
  }

  if (i1 == 1) {
    if (in3->size[0] == 1) {
      b_in2->size[0] = in2->size[0];
    } else {
      b_in2->size[0] = in3->size[0];
    }
  } else if (in5->size[0] == 1) {
    b_in2->size[0] = in4->size[0];
  } else {
    b_in2->size[0] = in5->size[0];
  }

  if (in5->size[1] == 1) {
    i1 = in4->size[1];
  } else {
    i1 = in5->size[1];
  }

  if (i1 == 1) {
    if (in3->size[1] == 1) {
      b_in2->size[1] = in2->size[1];
    } else {
      b_in2->size[1] = in3->size[1];
    }
  } else if (in5->size[1] == 1) {
    b_in2->size[1] = in4->size[1];
  } else {
    b_in2->size[1] = in5->size[1];
  }

  emxEnsureCapacity_boolean_T(b_in2, i);
  b_in2_data = b_in2->data;
  stride_0_0 = (in2->size[0] != 1);
  stride_0_1 = (in2->size[1] != 1);
  stride_1_0 = (in3->size[0] != 1);
  stride_1_1 = (in3->size[1] != 1);
  stride_2_0 = (in4->size[0] != 1);
  stride_2_1 = (in4->size[1] != 1);
  stride_3_0 = (in5->size[0] != 1);
  stride_3_1 = (in5->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  aux_2_1 = 0;
  aux_3_1 = 0;
  if (in5->size[1] == 1) {
    i = in4->size[1];
  } else {
    i = in5->size[1];
  }

  if (i == 1) {
    if (in3->size[1] == 1) {
      loop_ub = in2->size[1];
    } else {
      loop_ub = in3->size[1];
    }
  } else if (in5->size[1] == 1) {
    loop_ub = in4->size[1];
  } else {
    loop_ub = in5->size[1];
  }

  for (i = 0; i < loop_ub; i++) {
    int b_loop_ub;
    int i2;
    int i3;
    i1 = in5->size[0];
    b_loop_ub = in4->size[0];
    i2 = in3->size[0];
    if (i1 == 1) {
      i3 = b_loop_ub;
    } else {
      i3 = i1;
    }

    if (i3 == 1) {
      if (i2 == 1) {
        b_loop_ub = in2->size[0];
      } else {
        b_loop_ub = i2;
      }
    } else if (i1 != 1) {
      b_loop_ub = i1;
    }

    for (i1 = 0; i1 < b_loop_ub; i1++) {
      b_in2_data[i1 + b_in2->size[0] * i] = ((!(in2_data[i1 * stride_0_0 +
        in2->size[0] * aux_0_1] >= in3_data[i1 * stride_1_0 + in3->size[0] *
        aux_1_1])) || (!(in4_data[i1 * stride_2_0 + in4->size[0] * aux_2_1] <=
                         in5_data[i1 * stride_3_0 + in5->size[0] * aux_3_1])));
    }

    aux_3_1 += stride_3_1;
    aux_2_1 += stride_2_1;
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }

  all(b_in2, in1);
  emxFree_boolean_T(&b_in2);
}

/*
 * FINDPULSE Looks for pulses in the waveform based on its pulse
 * statistics object
 *
 * This method implemets the incoherent summation algorithm for
 * the waveform. The number of pulses summed (blocks considere)
 * is defined based on the length of obj.x and its priori
 * pulsestats object. When the waveform object is created, the
 * length of data (x property) included should be defined to be
 * long enough so that it is assure to contain no fewer than K
 * pulses. This method doesn't know K, but will create as many
 * blocks as it can based on the priori information.
 *
 * Note: The algorithm used for pulse peak energy detection
 * requires that the center frequency of the pulse not be at the
 * edges of the frequency bins in Wf. There needs to be rolloff
 * in signal power above and below the pulse center frequency.
 * Pulses at or just above/below the upper/lower limits of Wf may
 * exceeed the threshold for detection, but not get recorded in
 * the pl_out because the peeling algorithm can't catch them. If
 * this happens, the frequencies used in the priori to describe
 * the bounds of the pulse frequencies should be adjusted or
 * widened to ensure the pulse's spectral power has rolloff above
 * and below the center frequency and that this rolloff is within
 * the bounds of the Wf input.
 *
 *
 * INPUTS:
 *     obj            Waveform object
 *     W              spectral weighting matrix
 *     Wf             frequencies list from baseband of
 *                    corresponding to each row of W
 *     time_searchtype     'naive' or 'informed'
 *     freq_searchtype     'naive' or 'informed'
 *     excluded_freq_bands_in   nx2    matrix of bands of
 *                                  frequencies to exclude in
 *                                  the search. This is useful if
 *                                  there has already been a tag
 *                                  found and you want to exclude
 *                                  that band when looking for
 *                                  other frequencies. The lower
 *                                  frequecies of the band should
 *                                  be in the first column and
 *                                  the upper should be in the
 *                                  second. Leave empty [] if no
 *                                  exclusion zones are
 *                                  necessary. These frequencies
 *                                  are used regardless of the
 *                                  freq_searchtype setting.
 * OUPUTS:
 *  pl_out      A matrix of all potential pulses. This will
 *                have as many rows as Wf elements and as many
 *                rows as blocks that were possible given the
 *                length of the data in obj. The number of pulses
 *                to be searched for would be defined at the
 *                time of the creation of obj and used to define
 *                the length of its data.
 *
 *    indiv_msk   A logical matrix who's columns identify the
 *                peaks and sideband locations in the spectrum of
 *                each peak. The ith column of indiv_msk
 *                identifies the spectral location of the ith
 *                most powerful pulse group identified.
 *    peak_ind    A vector of the frequency indicies (of Wf)
 *                where the power of the pulses were found.
 *                These are the row indicies of pl_out where the
 *                peaks exist.
 *                These are the center frequency of the pulse
 *                where the most energy was detected. The
 *                sidebands of the ith peak listed in peak_ind is
 *                identified in the ith column of indiv_msk
 *
 *             %%
 *
 * Arguments    : const waveform *obj
 *                const char time_searchtype_data[]
 *                const int time_searchtype_size[2]
 *                const char freq_searchtype_data[]
 *                const int freq_searchtype_size[2]
 *                const emxArray_real_T *excluded_freq_bands_in
 *                emxArray_struct_T *pl_out
 *                emxArray_boolean_T *indiv_msk
 *                emxArray_real_T *peak_ind
 * Return Type  : void
 */
static void waveform_findpulse(const waveform *obj, const char
  time_searchtype_data[], const int time_searchtype_size[2], const char
  freq_searchtype_data[], const int freq_searchtype_size[2], const
  emxArray_real_T *excluded_freq_bands_in, emxArray_struct_T *pl_out,
  emxArray_boolean_T *indiv_msk, emxArray_real_T *peak_ind)
{
  b_struct_T b_expl_temp;
  b_struct_T *pl_out_data;
  d_sparse expl_temp;
  emxArray_boolean_T *freq_mask;
  emxArray_boolean_T *greater_than_next;
  emxArray_boolean_T *greater_than_prev;
  emxArray_boolean_T *msk;
  emxArray_boolean_T *r10;
  emxArray_boolean_T *r12;
  emxArray_boolean_T *r14;
  emxArray_boolean_T *r16;
  emxArray_boolean_T *sideband_msk;
  emxArray_boolean_T *slope_peak;
  emxArray_boolean_T *slope_val;
  emxArray_boolean_T *y;
  emxArray_creal_T *b_obj;
  emxArray_int32_T *r;
  emxArray_int32_T *r18;
  emxArray_int32_T *r19;
  emxArray_int32_T *r2;
  emxArray_int32_T *r21;
  emxArray_int32_T *r5;
  emxArray_int32_T *r6;
  emxArray_int32_T *r8;
  emxArray_int32_T *r9;
  emxArray_real_T b_freq_ind_rng_data;
  emxArray_real_T b_wind_start;
  emxArray_real_T *S_cols;
  emxArray_real_T *b_excluded_freq_bands;
  emxArray_real_T *b_refmat;
  emxArray_real_T *bandwidth_of_peak;
  emxArray_real_T *excluded_freq_bands;
  emxArray_real_T *indsOfBinsValid;
  emxArray_real_T *peak;
  emxArray_real_T *r20;
  emxArray_real_T *r3;
  emxArray_real_T *r4;
  emxArray_real_T *refmat;
  emxArray_real_T *scores;
  emxArray_real_T *signalAmps;
  emxArray_real_T *timeBlinderVec;
  emxArray_real_T *timeSearchRange;
  emxArray_real_T *wind_start;
  emxArray_real_T *x;
  emxArray_real_T *yw_max_all_freq;
  creal_T *obj_data;
  double freq_ind_rng_data[2];
  double t_srch_rng[2];
  const double *excluded_freq_bands_in_data;
  double J;
  double M;
  double N;
  double a;
  double diff_thresh;
  double naive_wind_end;
  double stft_dt;
  double t_lastknown;
  double timetol;
  double tip_temp;
  double tp_temp;
  double wind_start_data;
  double *S_cols_data;
  double *b_excluded_freq_bands_data;
  double *b_refmat_data;
  double *bandwidth_of_peak_data;
  double *excluded_freq_bands_data;
  double *indsOfBinsValid_data;
  double *peak_data;
  double *refmat_data;
  double *scores_data;
  double *signalAmps_data;
  double *timeBlinderVec_data;
  double *timeSearchRange_data;
  double *yw_max_all_freq_data;
  int freq_ind_rng;
  int i;
  int i1;
  int i2;
  int i3;
  int i4;
  int i5;
  int i6;
  int i7;
  int inds_frwd_2_next_valley_data;
  int inds_frwd_2_next_valley_size;
  int k;
  int loop_ub;
  int nColsOfS;
  int n_freqs;
  int nx;
  unsigned int p;
  int stride_1_0;
  int trueCount;
  int wind_end_size;
  int wind_start_size;
  int *r1;
  int *r7;
  bool t6_con_dec;
  bool t6_det_dec;
  bool *freq_mask_data;
  bool *greater_than_prev_data;
  bool *msk_data;
  bool *r11;
  bool *r13;
  bool *r15;
  bool *r17;
  bool *sideband_msk_data;
  bool *slope_peak_data;
  bool *slope_val_data;
  bool *y_data;
  excluded_freq_bands_in_data = excluded_freq_bands_in->data;
  emxInit_real_T(&excluded_freq_bands, 2);
  if (excluded_freq_bands_in->size[0] == 0) {
    i = excluded_freq_bands->size[0] * excluded_freq_bands->size[1];
    excluded_freq_bands->size[0] = 1;
    excluded_freq_bands->size[1] = 2;
    emxEnsureCapacity_real_T(excluded_freq_bands, i);
    excluded_freq_bands_data = excluded_freq_bands->data;
    excluded_freq_bands_data[0] = rtInf;
    excluded_freq_bands_data[1] = rtMinusInf;
  } else {
    i = excluded_freq_bands->size[0] * excluded_freq_bands->size[1];
    excluded_freq_bands->size[0] = excluded_freq_bands_in->size[0];
    excluded_freq_bands->size[1] = 2;
    emxEnsureCapacity_real_T(excluded_freq_bands, i);
    excluded_freq_bands_data = excluded_freq_bands->data;
    loop_ub = excluded_freq_bands_in->size[0] * 2;
    for (i = 0; i < loop_ub; i++) {
      excluded_freq_bands_data[i] = excluded_freq_bands_in_data[i];
    }
  }

  /* Get relavent variables and rename for readable code. */
  N = obj->N;
  M = obj->M;
  J = obj->J;

  /* Define naive search window for pulse 1 */
  diff_thresh = N + M;
  naive_wind_end = diff_thresh + J;

  /* The caller of this method should have already set the */
  /* threshold in the posteriori pulse stats. We just rename it */
  /* here to simplify code. */
  /* thresh = obj.ps_pos.thresh; */
  /* The caller of this method should have already set the */
  /* threshold. We just rename it */
  /* here to simplify code. */
  /* NAIVE SEARCH */
  emxInit_real_T(&peak, 1);
  emxInit_real_T(&x, 1);
  emxInit_boolean_T(&y, 1);
  if (s_strcmp(time_searchtype_data, time_searchtype_size)) {
    wind_start_size = 1;
    wind_start_data = 1.0;
    wind_end_size = 1;

    /* INFORMED SEARCH BUT NOT PRIORI FOR START TIME */
  } else {
    /* Due to segment lengths and overlapping, there can */
    /* sometimes be more than the desired number of pulses in a */
    /* segment. One more. If for example we were looking for 3 */
    /* pulses, but the previous segment contained 4, the  */
    /* algorithm may have localized the latter 3 rather than the */
    /* first 3. Here we set up the time window search range.  */
    /* If the last known pulse is in the first part of the time  */
    /* range of this segement currently getting processed, we  */
    /* search around that very narrow region. If it */
    /* isn't (doesn't existing in this segement, only the  */
    /* previous) we project the last known pulse forward one */
    /* interpulse time, and develop search region in accordance */
    /* with the uncertainty of the subsequent pulse. */
    /* Project out search range for first pulse in this segment */
    /* based on previous pulses. */
    t_lastknown = obj->ps_pre->pl->data[obj->ps_pre->pl->size[1] - 1].t_0;
    tp_temp = obj->ps_pre->t_p;

    /* If the last pulse identified occured in this segement, use */
    /* it to downselect the first pulse search range. */
    /* Time steps in the STFT windows: */
    stft_dt = obj->stft->t->data[1] - obj->stft->t->data[0];

    /* IF LAST SEGMENT'S LAST PULSE ALSO LIVES IN THIS SEGMENT */
    /* BECAUSE OF OVERLAP: */
    timetol = obj->n_ws / obj->Fs;
    if (t_lastknown >= obj->stft->t->data[0] - stft_dt / 2.0) {
      /* The stft_dt/2 is because the stft time stamps are for */
      /*  the middle of each time windpw */
      /* wind_start = find(obj.stft.t-stft_dt/2 >=t_lastknown,1,'first'); */
      /* wind_end   = find(obj.stft.t-stft_dt/2 <=t_lastknown+tp_temp,1,'last'); */
      /* The logic below executes the same logic as the two */
      /* lines above (left commented for reference) but avoids */
      /* issues associated when comparing floating point */
      /* numbers. There can be small errors that make two */
      /* numbers not equal each other and this addresses that */
      /* problem. See the Matlab help file on eq.m under the */
      /* section 'Compare Floating-Point Numbers'. */
      tip_temp = stft_dt / 2.0;
      i = x->size[0];
      x->size[0] = obj->stft->t->size[0];
      emxEnsureCapacity_real_T(x, i);
      timeSearchRange_data = x->data;
      loop_ub = obj->stft->t->size[0];
      for (i = 0; i < loop_ub; i++) {
        timeSearchRange_data[i] = (obj->stft->t->data[i] - tip_temp) -
          t_lastknown;
      }

      nx = x->size[0];
      i = peak->size[0];
      peak->size[0] = x->size[0];
      emxEnsureCapacity_real_T(peak, i);
      peak_data = peak->data;
      for (k = 0; k < nx; k++) {
        peak_data[k] = fabs(timeSearchRange_data[k]);
      }

      i = y->size[0];
      y->size[0] = peak->size[0];
      emxEnsureCapacity_boolean_T(y, i);
      y_data = y->data;
      loop_ub = peak->size[0];
      for (i = 0; i < loop_ub; i++) {
        y_data[i] = (peak_data[i] <= timetol);
      }

      c_eml_find(y, (int *)&inds_frwd_2_next_valley_data,
                 &inds_frwd_2_next_valley_size);
      wind_start_size = inds_frwd_2_next_valley_size;
      for (i = 0; i < inds_frwd_2_next_valley_size; i++) {
        wind_start_data = inds_frwd_2_next_valley_data;
      }

      stft_dt /= 2.0;
      t_lastknown += tp_temp;
      i = x->size[0];
      x->size[0] = obj->stft->t->size[0];
      emxEnsureCapacity_real_T(x, i);
      timeSearchRange_data = x->data;
      loop_ub = obj->stft->t->size[0];
      for (i = 0; i < loop_ub; i++) {
        timeSearchRange_data[i] = (obj->stft->t->data[i] - stft_dt) -
          t_lastknown;
      }

      nx = x->size[0];
      i = peak->size[0];
      peak->size[0] = x->size[0];
      emxEnsureCapacity_real_T(peak, i);
      peak_data = peak->data;
      for (k = 0; k < nx; k++) {
        peak_data[k] = fabs(timeSearchRange_data[k]);
      }

      i = y->size[0];
      y->size[0] = peak->size[0];
      emxEnsureCapacity_boolean_T(y, i);
      y_data = y->data;
      loop_ub = peak->size[0];
      for (i = 0; i < loop_ub; i++) {
        y_data[i] = (peak_data[i] <= timetol);
      }

      d_eml_find(y, (int *)&inds_frwd_2_next_valley_data,
                 &inds_frwd_2_next_valley_size);
      wind_end_size = inds_frwd_2_next_valley_size;
      for (i = 0; i < inds_frwd_2_next_valley_size; i++) {
        naive_wind_end = inds_frwd_2_next_valley_data;
      }

      /* IF LAST SEGMENT'S LAST PULSE DOESN'T LIVE IN THIS SEGMENT: */
    } else {
      /* Project forward one pulse in time with */
      /* +/-2M uncertainty in search range. */
      tip_temp = obj->ps_pre->t_ip;
      a = obj->ps_pre->t_ipu;
      tp_temp = t_lastknown + tip_temp;

      /* +tp_temp/2; */
      /* These are the times of the START OF THE PULSE...not  */
      /* the center. This is why we have stft_dt/2 terms in  */
      /* subsequent equations. */
      t_srch_rng[0] = -a + tp_temp;
      t_srch_rng[1] = a + tp_temp;
      if (t_srch_rng[0] < obj->stft->t->data[0] - stft_dt / 2.0) {
        /* If for some reason the last known pulse is more */
        /* that one pulse repetition interval away from the */
        /* current waveform start time, use the naive search */
        /* range. */
        wind_start_size = 1;
        wind_start_data = 1.0;
        wind_end_size = 1;
      } else {
        /* wind_start = find(obj.stft.t-stft_dt/2>=t_srch_rng(1),1,'first'); */
        /* wind_end   = find(obj.stft.t-stft_dt/2<=t_srch_rng(2),1,'last'); */
        /* The logic below executes the same logic as the two */
        /* lines above (left commented for reference) but  */
        /* avoids issues associated when comparing floating  */
        /* point numbers. There can be small errors that */
        /* make two numbers not equal each other and this  */
        /* addresses that problem. See the Matlab help file */
        /* on eq.m under the section 'Compare Floating-Point */
        /* Numbers'. */
        tip_temp = stft_dt / 2.0;
        i = x->size[0];
        x->size[0] = obj->stft->t->size[0];
        emxEnsureCapacity_real_T(x, i);
        timeSearchRange_data = x->data;
        loop_ub = obj->stft->t->size[0];
        for (i = 0; i < loop_ub; i++) {
          timeSearchRange_data[i] = (obj->stft->t->data[i] - tip_temp) -
            t_srch_rng[0];
        }

        nx = x->size[0];
        i = peak->size[0];
        peak->size[0] = x->size[0];
        emxEnsureCapacity_real_T(peak, i);
        peak_data = peak->data;
        for (k = 0; k < nx; k++) {
          peak_data[k] = fabs(timeSearchRange_data[k]);
        }

        i = y->size[0];
        y->size[0] = peak->size[0];
        emxEnsureCapacity_boolean_T(y, i);
        y_data = y->data;
        loop_ub = peak->size[0];
        for (i = 0; i < loop_ub; i++) {
          y_data[i] = (peak_data[i] <= timetol);
        }

        c_eml_find(y, (int *)&inds_frwd_2_next_valley_data,
                   &inds_frwd_2_next_valley_size);
        wind_start_size = inds_frwd_2_next_valley_size;
        for (i = 0; i < inds_frwd_2_next_valley_size; i++) {
          wind_start_data = inds_frwd_2_next_valley_data;
        }

        stft_dt /= 2.0;
        i = x->size[0];
        x->size[0] = obj->stft->t->size[0];
        emxEnsureCapacity_real_T(x, i);
        timeSearchRange_data = x->data;
        loop_ub = obj->stft->t->size[0];
        for (i = 0; i < loop_ub; i++) {
          timeSearchRange_data[i] = (obj->stft->t->data[i] - stft_dt) -
            t_srch_rng[1];
        }

        nx = x->size[0];
        i = peak->size[0];
        peak->size[0] = x->size[0];
        emxEnsureCapacity_real_T(peak, i);
        peak_data = peak->data;
        for (k = 0; k < nx; k++) {
          peak_data[k] = fabs(timeSearchRange_data[k]);
        }

        i = y->size[0];
        y->size[0] = peak->size[0];
        emxEnsureCapacity_boolean_T(y, i);
        y_data = y->data;
        loop_ub = peak->size[0];
        for (i = 0; i < loop_ub; i++) {
          y_data[i] = (peak_data[i] <= timetol);
        }

        d_eml_find(y, (int *)&inds_frwd_2_next_valley_data,
                   &inds_frwd_2_next_valley_size);
        wind_end_size = inds_frwd_2_next_valley_size;
        for (i = 0; i < inds_frwd_2_next_valley_size; i++) {
          naive_wind_end = inds_frwd_2_next_valley_data;
        }
      }
    }
  }

  /* time_search_range = [wind_start,wind_end]; */
  /* Build a time search range matrix with one row for each pulse */
  /* The first column is the first window where that pulse might */
  /* live in the S matrix, and the second column is the last window */
  /* wher that pulse might live in the S matrix. */
  emxInit_real_T(&timeSearchRange, 2);
  i = (int)obj->K;
  i1 = timeSearchRange->size[0] * timeSearchRange->size[1];
  timeSearchRange->size[0] = i;
  timeSearchRange->size[1] = 2;
  emxEnsureCapacity_real_T(timeSearchRange, i1);
  timeSearchRange_data = timeSearchRange->data;
  loop_ub = i << 1;
  for (i1 = 0; i1 < loop_ub; i1++) {
    timeSearchRange_data[i1] = 0.0;
  }

  emxInit_real_T(&wind_start, 2);
  i1 = wind_start->size[0] * wind_start->size[1];
  wind_start->size[0] = wind_start_size;
  wind_start->size[1] = 2;
  emxEnsureCapacity_real_T(wind_start, i1);
  peak_data = wind_start->data;
  for (i1 = 0; i1 < wind_start_size; i1++) {
    peak_data[0] = wind_start_data;
  }

  for (i1 = 0; i1 < wind_end_size; i1++) {
    peak_data[wind_start->size[0]] = naive_wind_end;
  }

  timeSearchRange_data[0] = peak_data[0];
  timeSearchRange_data[timeSearchRange->size[0]] = peak_data[1];
  i1 = (int)(obj->K - 1.0);
  for (wind_start_size = 0; wind_start_size < i1; wind_start_size++) {
    t_srch_rng[1] = timeSearchRange_data[timeSearchRange->size[0]] + ((((double)
      wind_start_size + 2.0) - 1.0) * diff_thresh + J);
    timeSearchRange_data[wind_start_size + 1] = timeSearchRange_data[0] +
      ((((double)wind_start_size + 2.0) - 1.0) * (N - M) - J);
    timeSearchRange_data[(wind_start_size + timeSearchRange->size[0]) + 1] =
      t_srch_rng[1];
  }

  nx = obj->stft->S->size[1];

  /* Limit the search to ranges of time that will be in the sftf */
  /* matrix */
  wind_end_size = (timeSearchRange->size[0] << 1) - 1;
  trueCount = 0;
  for (wind_start_size = 0; wind_start_size <= wind_end_size; wind_start_size++)
  {
    if (timeSearchRange_data[wind_start_size] > nx) {
      trueCount++;
    }
  }

  emxInit_int32_T(&r, 1);
  i1 = r->size[0];
  r->size[0] = trueCount;
  emxEnsureCapacity_int32_T(r, i1);
  r1 = r->data;
  trueCount = 0;
  for (wind_start_size = 0; wind_start_size <= wind_end_size; wind_start_size++)
  {
    if (timeSearchRange_data[wind_start_size] > nx) {
      r1[trueCount] = wind_start_size + 1;
      trueCount++;
    }
  }

  loop_ub = r->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    timeSearchRange_data[r1[i1] - 1] = nx;
  }

  wind_end_size = (timeSearchRange->size[0] << 1) - 1;
  trueCount = 0;
  for (wind_start_size = 0; wind_start_size <= wind_end_size; wind_start_size++)
  {
    if (timeSearchRange_data[wind_start_size] < 1.0) {
      trueCount++;
    }
  }

  emxInit_int32_T(&r2, 1);
  i1 = r2->size[0];
  r2->size[0] = trueCount;
  emxEnsureCapacity_int32_T(r2, i1);
  r1 = r2->data;
  trueCount = 0;
  for (wind_start_size = 0; wind_start_size <= wind_end_size; wind_start_size++)
  {
    if (timeSearchRange_data[wind_start_size] < 1.0) {
      r1[trueCount] = wind_start_size + 1;
      trueCount++;
    }
  }

  loop_ub = r2->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    timeSearchRange_data[r1[i1] - 1] = 1.0;
  }

  emxFree_int32_T(&r2);
  emxInit_real_T(&timeBlinderVec, 1);
  i1 = timeBlinderVec->size[0];
  timeBlinderVec->size[0] = nx;
  emxEnsureCapacity_real_T(timeBlinderVec, i1);
  timeBlinderVec_data = timeBlinderVec->data;
  for (i1 = 0; i1 < nx; i1++) {
    timeBlinderVec_data[i1] = 0.0;
  }

  for (wind_start_size = 0; wind_start_size < i; wind_start_size++) {
    stft_dt = timeSearchRange_data[wind_start_size];
    tp_temp = timeSearchRange_data[wind_start_size + timeSearchRange->size[0]];
    if (stft_dt > tp_temp) {
      i1 = 0;
      i2 = 0;
    } else {
      i1 = (int)stft_dt - 1;
      i2 = (int)tp_temp;
    }

    loop_ub = i2 - i1;
    for (i2 = 0; i2 < loop_ub; i2++) {
      timeBlinderVec_data[i1 + i2] = 1.0;
    }
  }

  /* Build the excluded frequency mask */
  /* False where we want to exclude */
  /* VECFIND creates a logical matrix based on the input operator comparing a */
  /* reference vector and a vector to be compared. */
  /*    This function can be used to do comparison operations of vectors of */
  /*    difference sizes. Comparing a single to a vector work natively */
  /*    in Matlab and create a resulting logic vector, i.e. [1 3 5]>4 outputs */
  /*    [0 0 1]. Many cases though require comparison of on vector to all the */
  /*    elements of another. i.e. [1 3 5]>[2 4] would ask which elements of  */
  /*    [1 3 5] are greater than 2 and which are greater than 4? This function */
  /*    produces an output matrix whose columns are the logicial comparion of */
  /*    the reference vector to each element of the search vector. Logicals fpr */
  /*    comparison are input to this function as strings. */
  /*  */
  /*    Example: */
  /*              outmat = vecfind([1 3 5],'>',[2 4]) */
  /*   */
  /*              outmat = */
  /*   */
  /*              3×2 logical array */
  /*   */
  /*              0   0 */
  /*              1   0 */
  /*              1   1 */
  /*  */
  /* INPUTS: */
  /*    refvec              n-element vector of numerics to be compared. */
  /*    comparison_op_string   A string of the comparison operator to be used */
  /*                        Valid options are '<' '<=' '>' '>=' '==' '~=' */
  /*    searchvec           m-element vector of numerics used for comparison */
  /* OUTPUTS: */
  /*    outmat              nxm logical matrix comparing the ref and search */
  /*                        vectors */
  /*  */
  /* Author: Michael Shafer */
  /* Date:   2021-05-25 */
  /*  */
  /* 2022-01-24 - Updated to use limited comparison operators and removed use */
  /*              of the eval.m function. */
  /*  */
  /* Ensure column vector */
  emxInit_real_T(&refmat, 2);
  repmat(obj->Wf, excluded_freq_bands->size[0], refmat);
  refmat_data = refmat->data;

  /* outmat = eval(['refmat',logical_op_string,'searchmat']); */
  /* VECFIND creates a logical matrix based on the input operator comparing a */
  /* reference vector and a vector to be compared. */
  /*    This function can be used to do comparison operations of vectors of */
  /*    difference sizes. Comparing a single to a vector work natively */
  /*    in Matlab and create a resulting logic vector, i.e. [1 3 5]>4 outputs */
  /*    [0 0 1]. Many cases though require comparison of on vector to all the */
  /*    elements of another. i.e. [1 3 5]>[2 4] would ask which elements of  */
  /*    [1 3 5] are greater than 2 and which are greater than 4? This function */
  /*    produces an output matrix whose columns are the logicial comparion of */
  /*    the reference vector to each element of the search vector. Logicals fpr */
  /*    comparison are input to this function as strings. */
  /*  */
  /*    Example: */
  /*              outmat = vecfind([1 3 5],'>',[2 4]) */
  /*   */
  /*              outmat = */
  /*   */
  /*              3×2 logical array */
  /*   */
  /*              0   0 */
  /*              1   0 */
  /*              1   1 */
  /*  */
  /* INPUTS: */
  /*    refvec              n-element vector of numerics to be compared. */
  /*    comparison_op_string   A string of the comparison operator to be used */
  /*                        Valid options are '<' '<=' '>' '>=' '==' '~=' */
  /*    searchvec           m-element vector of numerics used for comparison */
  /* OUTPUTS: */
  /*    outmat              nxm logical matrix comparing the ref and search */
  /*                        vectors */
  /*  */
  /* Author: Michael Shafer */
  /* Date:   2021-05-25 */
  /*  */
  /* 2022-01-24 - Updated to use limited comparison operators and removed use */
  /*              of the eval.m function. */
  /*  */
  /* Ensure column vector */
  emxInit_real_T(&b_refmat, 2);
  repmat(obj->Wf, excluded_freq_bands->size[0], b_refmat);
  b_refmat_data = b_refmat->data;

  /* outmat = eval(['refmat',logical_op_string,'searchmat']); */
  /* Build the priori frequency mask */
  /* Naive or informed frequency search */
  emxInit_boolean_T(&freq_mask, 1);
  emxInit_boolean_T(&sideband_msk, 1);
  if (t_strcmp(freq_searchtype_data, freq_searchtype_size)) {
    tp_temp = obj->ps_pre->fstart;
    tip_temp = obj->ps_pre->fend;

    /* Check to makesure the informed search range is covered by */
    /* the frequencies available. If the prev bw is listed */
    /* as NaN, this will fail and will default to the naive */
    /* search. Freq_mask variable is a logicial vector of the */
    /* same size as Wf indicating which frequencies to look at. */
    /* IF FREQS ARE UNAVILABLE, USE NAIVE */
    if ((tp_temp < unaryMinOrMax_anonFcn1(obj->Wf)) || (tip_temp > maximum
         (obj->Wf))) {
      /* isnan(obj.ps_pre.fc) %Naive */
      wind_start_size = 1;
      wind_start_data = 1.0;
      wind_end_size = 1;
      naive_wind_end = obj->Wf->size[0];

      /* size(Sw,1); */
      /* IF FREQS ARE AVILABLE, USE INFORMED */
    } else {
      i = sideband_msk->size[0];
      sideband_msk->size[0] = obj->Wf->size[0];
      emxEnsureCapacity_boolean_T(sideband_msk, i);
      sideband_msk_data = sideband_msk->data;
      loop_ub = obj->Wf->size[0];
      for (i = 0; i < loop_ub; i++) {
        sideband_msk_data[i] = (obj->Wf->data[i] >= obj->ps_pre->fstart);
      }

      c_eml_find(sideband_msk, (int *)&inds_frwd_2_next_valley_data,
                 &inds_frwd_2_next_valley_size);
      wind_start_size = inds_frwd_2_next_valley_size;
      for (i = 0; i < inds_frwd_2_next_valley_size; i++) {
        wind_start_data = inds_frwd_2_next_valley_data;
      }

      i = sideband_msk->size[0];
      sideband_msk->size[0] = obj->Wf->size[0];
      emxEnsureCapacity_boolean_T(sideband_msk, i);
      sideband_msk_data = sideband_msk->data;
      loop_ub = obj->Wf->size[0];
      for (i = 0; i < loop_ub; i++) {
        sideband_msk_data[i] = (obj->Wf->data[i] <= obj->ps_pre->fend);
      }

      d_eml_find(sideband_msk, (int *)&inds_frwd_2_next_valley_data,
                 &inds_frwd_2_next_valley_size);
      wind_end_size = inds_frwd_2_next_valley_size;
      for (i = 0; i < inds_frwd_2_next_valley_size; i++) {
        naive_wind_end = inds_frwd_2_next_valley_data;
      }
    }

    i = timeSearchRange->size[0] * timeSearchRange->size[1];
    timeSearchRange->size[0] = wind_start_size;
    timeSearchRange->size[1] = 2;
    emxEnsureCapacity_real_T(timeSearchRange, i);
    timeSearchRange_data = timeSearchRange->data;
    for (i = 0; i < wind_start_size; i++) {
      timeSearchRange_data[0] = wind_start_data;
    }

    for (i = 0; i < wind_end_size; i++) {
      timeSearchRange_data[timeSearchRange->size[0]] = naive_wind_end;
    }

    for (i = 0; i < wind_start_size; i++) {
      freq_ind_rng_data[0] = wind_start_data;
    }

    for (i = 0; i < wind_end_size; i++) {
      freq_ind_rng_data[wind_start_size] = naive_wind_end;
    }

    loop_ub = obj->Wf->size[0];
    i = freq_mask->size[0];
    freq_mask->size[0] = obj->Wf->size[0];
    emxEnsureCapacity_boolean_T(freq_mask, i);
    freq_mask_data = freq_mask->data;
    for (i = 0; i < loop_ub; i++) {
      freq_mask_data[i] = false;
    }

    if ((int)timeSearchRange_data[0] > (int)timeSearchRange_data[1]) {
      i = 0;
      i1 = 0;
    } else {
      i = (int)freq_ind_rng_data[0] - 1;
      i1 = (int)freq_ind_rng_data[1];
    }

    loop_ub = i1 - i;
    for (i1 = 0; i1 < loop_ub; i1++) {
      freq_mask_data[i + i1] = true;
    }
  } else {
    /* Naive frequency search */
    loop_ub = obj->Wf->size[0];
    i = freq_mask->size[0];
    freq_mask->size[0] = obj->Wf->size[0];
    emxEnsureCapacity_boolean_T(freq_mask, i);
    freq_mask_data = freq_mask->data;
    for (i = 0; i < loop_ub; i++) {
      freq_mask_data[i] = true;
    }
  }

  /* If using informed search and excluded frequencies overlap with */
  /* priori frequencies, warn the user. */
  emxInit_real_T(&b_excluded_freq_bands, 2);
  i = b_excluded_freq_bands->size[0] * b_excluded_freq_bands->size[1];
  b_excluded_freq_bands->size[0] = 1;
  b_excluded_freq_bands->size[1] = excluded_freq_bands->size[0];
  emxEnsureCapacity_real_T(b_excluded_freq_bands, i);
  b_excluded_freq_bands_data = b_excluded_freq_bands->data;
  loop_ub = excluded_freq_bands->size[0];
  for (i = 0; i < loop_ub; i++) {
    b_excluded_freq_bands_data[i] = excluded_freq_bands_data[i];
  }

  emxInit_real_T(&r3, 2);
  b_repmat(b_excluded_freq_bands, obj->Wf->size[0], r3);
  peak_data = r3->data;
  i = b_excluded_freq_bands->size[0] * b_excluded_freq_bands->size[1];
  b_excluded_freq_bands->size[0] = 1;
  b_excluded_freq_bands->size[1] = excluded_freq_bands->size[0];
  emxEnsureCapacity_real_T(b_excluded_freq_bands, i);
  b_excluded_freq_bands_data = b_excluded_freq_bands->data;
  loop_ub = excluded_freq_bands->size[0];
  for (i = 0; i < loop_ub; i++) {
    b_excluded_freq_bands_data[i] = excluded_freq_bands_data[i +
      excluded_freq_bands->size[0]];
  }

  emxInit_real_T(&r4, 2);
  b_repmat(b_excluded_freq_bands, obj->Wf->size[0], r4);
  timeSearchRange_data = r4->data;
  emxInit_boolean_T(&msk, 2);
  if (refmat->size[0] == 1) {
    i = r3->size[0];
  } else {
    i = refmat->size[0];
  }

  if (b_refmat->size[0] == 1) {
    i1 = r4->size[0];
  } else {
    i1 = b_refmat->size[0];
  }

  if (refmat->size[1] == 1) {
    i2 = r3->size[1];
  } else {
    i2 = refmat->size[1];
  }

  if (b_refmat->size[1] == 1) {
    i3 = r4->size[1];
  } else {
    i3 = b_refmat->size[1];
  }

  if ((refmat->size[0] == r3->size[0]) && (refmat->size[1] == r3->size[1]) &&
      (b_refmat->size[0] == r4->size[0]) && (b_refmat->size[1] == r4->size[1]) &&
      (i == i1) && (i2 == i3)) {
    i = msk->size[0] * msk->size[1];
    msk->size[0] = refmat->size[0];
    msk->size[1] = refmat->size[1];
    emxEnsureCapacity_boolean_T(msk, i);
    msk_data = msk->data;
    loop_ub = refmat->size[0] * refmat->size[1];
    for (i = 0; i < loop_ub; i++) {
      msk_data[i] = ((!(refmat_data[i] >= peak_data[i])) || (!(b_refmat_data[i] <=
        timeSearchRange_data[i])));
    }

    all(msk, sideband_msk);
    sideband_msk_data = sideband_msk->data;
  } else {
    u_binary_expand_op(sideband_msk, refmat, r3, b_refmat, r4);
    sideband_msk_data = sideband_msk->data;
  }

  if (freq_mask->size[0] == sideband_msk->size[0]) {
    loop_ub = freq_mask->size[0];
    for (i = 0; i < loop_ub; i++) {
      freq_mask_data[i] = (freq_mask_data[i] && sideband_msk_data[i]);
    }
  } else {
    c_and(freq_mask, sideband_msk);
    freq_mask_data = freq_mask->data;
  }

  /* Check that we actually have something to search */
  /* Determine the number of blocks to cut the data into. Should */
  /* always be the number of pulses currently looking for.  */
  timetol = ((double)obj->stft->S->size[1] - 1.0) / diff_thresh;
  timetol = floor(timetol);
  emxInitStruct_sparse(&expl_temp);
  buildtimecorrelatormatrix(N, M, J, obj->K, &expl_temp);
  emxInit_creal_T(&b_obj, 2);
  i = b_obj->size[0] * b_obj->size[1];
  b_obj->size[0] = obj->W->size[1];
  b_obj->size[1] = obj->W->size[0];
  emxEnsureCapacity_creal_T(b_obj, i);
  obj_data = b_obj->data;
  loop_ub = obj->W->size[0];
  for (i = 0; i < loop_ub; i++) {
    nx = obj->W->size[1];
    for (i1 = 0; i1 < nx; i1++) {
      obj_data[i1 + b_obj->size[0] * i].re = obj->W->data[i + obj->W->size[0] *
        i1].re;
      obj_data[i1 + b_obj->size[0] * i].im = -obj->W->data[i + obj->W->size[0] *
        i1].im;
    }
  }

  emxInit_real_T(&yw_max_all_freq, 2);
  emxInit_real_T(&S_cols, 2);
  incohsumtoeplitz(freq_mask, b_obj, obj->stft->S, timeBlinderVec, expl_temp.d,
                   expl_temp.colidx, expl_temp.rowidx, expl_temp.m, expl_temp.n,
                   yw_max_all_freq, S_cols);
  S_cols_data = S_cols->data;
  yw_max_all_freq_data = yw_max_all_freq->data;
  emxFreeStruct_sparse(&expl_temp);

  /* obj.TimeCorr.Wq(obj.K)); */
  /* Only pass a freq_msk subset of the Sw matrix to the incohsum */
  /* function. Run the algorithm             */
  /*              tic */
  /*              [yw_max_all_freq,S_cols,S_rows] = incohsumfast(Sw(freq_mask,:),... */
  /*                                                          N,M,... */
  /*                                                          time_search_range,... */
  /*                                                          n_blks); */
  /*              time(1) = toc; */
  /*              tic */
  /*              [yw_max_all_freq,S_cols,S_rows] = incohsum(Sw(freq_mask,:),... */
  /*                                                          N,M,... */
  /*                                                          time_search_range,... */
  /*                                                          n_blks); */
  /*              time(2) = toc; */
  /*              time */
  /*              yw_max_all_freq2 = NaN(numel(Wf),n_blks); */
  /*              yw_max_all_freq2(freq_mask,:) = yw_max_all_freq; */
  /*              yw_max_all_freq = yw_max_all_freq2;                          */
  /*              S_cols2 = NaN(numel(Wf),n_blks); */
  /*              S_cols2(freq_mask,:) = S_cols; */
  /*              S_cols = S_cols2; */
  /* PAPER EQUATION 14 */
  /* y_vec_w = Sw(sub2ind(size(Sw),out(:,1),out(:,2))); */
  /*  %PAPER EQUATION pre-29 */
  /* gamma   = abs(y_vec_w); */
  /* PAPER EQUATION 29 */
  /* z       = sum(gamma.^2); */
  /*             %% PEELING ALGORITHM */
  /*  The following algorithm is used to help tease out the central */
  /*  peaks of the outputs of filter and sort out those entries */
  /*  that are sideband. It looks through all of the scores  */
  /*  (yw_max_all_freqs), beginning with the highest score. It */
  /*  looks for other scores that are correlated in time and nearby */
  /*  frequency and identifies them as sidebands. Once the highest */
  /*  peak's sidebands are identified and excluded from further */
  /*  consideration as a separate pulse, the algorithm moves to the */
  /*  next highest score, repeating the sideband identification. */
  /*  This continues until no more scores that exceed the decision */
  /*  threshold remain.  */
  /* Number of pulses identified for each frequency. This should be */
  /* equal to the K pulses of the search or n_blks.  */
  n_freqs = yw_max_all_freq->size[0];

  /* Calculate the sum of the yw values - the score/test statistic */
  emxInit_real_T(&scores, 1);
  d_sum(yw_max_all_freq, scores);
  scores_data = scores->data;

  /* Calculate an estimate of the noise only power in each bin */
  /* based on the PSD */
  /* psdAtZetas = interp1(obj.stft.f,obj.stft.psd,Wf,'linear','extrap'); */
  /* freqBinPowAtZetas = psdAtZetas*(Wf(2)-Wf(1)); */
  nColsOfS = obj->stft->S->size[1];
  inds_frwd_2_next_valley_size = obj->stft->S->size[0];

  /* sIndsOfBins = sub2ind([nRowsOfS nColsOfS],repmat((1:nRowsOfS)',1,nColsOfS),S_cols); */
  /* sIndsOfBins = sub2ind([nZetas*nRowsOfS nColsOfS],transpose(1:numel(Wf)),S_cols); */
  /* The few lines below finds the noisePSD, but excludes regions */
  /* in time and frequency around possible detection. We do */
  /* detections as the zeta steps, but use the S matrix for PSD */
  /* estimates so there is a size mismatch that necessitates the */
  /* code below.  */
  nx = obj->Wf->size[0];
  if (nx < 1) {
    b_excluded_freq_bands->size[0] = 1;
    b_excluded_freq_bands->size[1] = 0;
  } else {
    i = b_excluded_freq_bands->size[0] * b_excluded_freq_bands->size[1];
    b_excluded_freq_bands->size[0] = 1;
    b_excluded_freq_bands->size[1] = nx;
    emxEnsureCapacity_real_T(b_excluded_freq_bands, i);
    b_excluded_freq_bands_data = b_excluded_freq_bands->data;
    loop_ub = nx - 1;
    for (i = 0; i <= loop_ub; i++) {
      b_excluded_freq_bands_data[i] = (double)i + 1.0;
    }
  }

  i = peak->size[0];
  peak->size[0] = b_excluded_freq_bands->size[1];
  emxEnsureCapacity_real_T(peak, i);
  peak_data = peak->data;
  loop_ub = b_excluded_freq_bands->size[1];
  for (i = 0; i < loop_ub; i++) {
    peak_data[i] = b_excluded_freq_bands_data[i];
  }

  repmat(peak, obj->K, refmat);
  refmat_data = refmat->data;

  /* sub2ind doesn't support NaN values, so we focus here on those */
  /* that don't have NaN */
  i = msk->size[0] * msk->size[1];
  msk->size[0] = S_cols->size[0];
  msk->size[1] = S_cols->size[1];
  emxEnsureCapacity_boolean_T(msk, i);
  msk_data = msk->data;
  loop_ub = S_cols->size[0] * S_cols->size[1];
  for (i = 0; i < loop_ub; i++) {
    msk_data[i] = rtIsNaN(S_cols_data[i]);
  }

  loop_ub = msk->size[0] * msk->size[1];
  for (i = 0; i < loop_ub; i++) {
    msk_data[i] = !msk_data[i];
  }

  wind_end_size = msk->size[0] * msk->size[1] - 1;
  trueCount = 0;
  for (wind_start_size = 0; wind_start_size <= wind_end_size; wind_start_size++)
  {
    if (msk_data[wind_start_size]) {
      trueCount++;
    }
  }

  emxInit_int32_T(&r5, 1);
  i = r5->size[0];
  r5->size[0] = trueCount;
  emxEnsureCapacity_int32_T(r5, i);
  r1 = r5->data;
  trueCount = 0;
  for (wind_start_size = 0; wind_start_size <= wind_end_size; wind_start_size++)
  {
    if (msk_data[wind_start_size]) {
      r1[trueCount] = wind_start_size + 1;
      trueCount++;
    }
  }

  wind_end_size = msk->size[0] * msk->size[1] - 1;
  trueCount = 0;
  for (wind_start_size = 0; wind_start_size <= wind_end_size; wind_start_size++)
  {
    if (msk_data[wind_start_size]) {
      trueCount++;
    }
  }

  emxInit_int32_T(&r6, 1);
  i = r6->size[0];
  r6->size[0] = trueCount;
  emxEnsureCapacity_int32_T(r6, i);
  r7 = r6->data;
  trueCount = 0;
  for (wind_start_size = 0; wind_start_size <= wind_end_size; wind_start_size++)
  {
    if (msk_data[wind_start_size]) {
      r7[trueCount] = wind_start_size + 1;
      trueCount++;
    }
  }

  tp_temp = (double)obj->Wf->size[0] / (double)inds_frwd_2_next_valley_size *
    (double)inds_frwd_2_next_valley_size;
  i = timeBlinderVec->size[0];
  timeBlinderVec->size[0] = r5->size[0];
  emxEnsureCapacity_real_T(timeBlinderVec, i);
  timeBlinderVec_data = timeBlinderVec->data;
  loop_ub = r5->size[0];
  for (i = 0; i < loop_ub; i++) {
    timeBlinderVec_data[i] = (int)refmat_data[r1[i] - 1] + (int)tp_temp * ((int)
      S_cols_data[r7[i] - 1] - 1);
  }

  emxFree_int32_T(&r6);
  emxFree_int32_T(&r5);
  i = sideband_msk->size[0];
  sideband_msk->size[0] = timeBlinderVec->size[0];
  emxEnsureCapacity_boolean_T(sideband_msk, i);
  sideband_msk_data = sideband_msk->data;
  loop_ub = timeBlinderVec->size[0];
  for (i = 0; i < loop_ub; i++) {
    sideband_msk_data[i] = false;
  }

  wind_end_size = sideband_msk->size[0] - 1;
  trueCount = 0;
  for (wind_start_size = 0; wind_start_size <= wind_end_size; wind_start_size++)
  {
    trueCount++;
  }

  emxInit_real_T(&indsOfBinsValid, 1);
  i = indsOfBinsValid->size[0];
  indsOfBinsValid->size[0] = trueCount;
  emxEnsureCapacity_real_T(indsOfBinsValid, i);
  indsOfBinsValid_data = indsOfBinsValid->data;
  for (wind_start_size = 0; wind_start_size <= wind_end_size; wind_start_size++)
  {
    indsOfBinsValid_data[wind_start_size] = timeBlinderVec_data[wind_start_size];
  }

  /* binMaskMatrix will be a matrix of NaN at potential pulse */
  /* locations */
  i = refmat->size[0] * refmat->size[1];
  refmat->size[0] = (int)tp_temp;
  refmat->size[1] = nColsOfS;
  emxEnsureCapacity_real_T(refmat, i);
  refmat_data = refmat->data;
  loop_ub = (int)tp_temp * nColsOfS;
  for (i = 0; i < loop_ub; i++) {
    refmat_data[i] = 0.0;
  }

  i = r->size[0];
  r->size[0] = indsOfBinsValid->size[0];
  emxEnsureCapacity_int32_T(r, i);
  r1 = r->data;
  loop_ub = indsOfBinsValid->size[0];
  for (i = 0; i < loop_ub; i++) {
    r1[i] = (int)indsOfBinsValid_data[i];
  }

  loop_ub = r->size[0];
  for (i = 0; i < loop_ub; i++) {
    refmat_data[r1[i] - 1] = rtNaN;
  }

  emxFree_int32_T(&r);

  /* 0; */
  /* Now add some buffer around the potential pulse locations */
  i = r3->size[0] * r3->size[1];
  r3->size[0] = refmat->size[0];
  r3->size[1] = refmat->size[1];
  emxEnsureCapacity_real_T(r3, i);
  peak_data = r3->data;
  loop_ub = refmat->size[0] * refmat->size[1];
  for (i = 0; i < loop_ub; i++) {
    peak_data[i] = refmat_data[i];
  }

  circshift(r3);
  peak_data = r3->data;
  i = r4->size[0] * r4->size[1];
  r4->size[0] = refmat->size[0];
  r4->size[1] = refmat->size[1];
  emxEnsureCapacity_real_T(r4, i);
  timeSearchRange_data = r4->data;
  loop_ub = refmat->size[0] * refmat->size[1];
  for (i = 0; i < loop_ub; i++) {
    timeSearchRange_data[i] = refmat_data[i];
  }

  b_circshift(r4);
  timeSearchRange_data = r4->data;
  i = b_refmat->size[0] * b_refmat->size[1];
  b_refmat->size[0] = refmat->size[0];
  b_refmat->size[1] = refmat->size[1];
  emxEnsureCapacity_real_T(b_refmat, i);
  b_refmat_data = b_refmat->data;
  loop_ub = refmat->size[0] * refmat->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_refmat_data[i] = refmat_data[i];
  }

  c_circshift(b_refmat);
  b_refmat_data = b_refmat->data;
  emxInit_real_T(&signalAmps, 2);
  i = signalAmps->size[0] * signalAmps->size[1];
  signalAmps->size[0] = refmat->size[0];
  signalAmps->size[1] = refmat->size[1];
  emxEnsureCapacity_real_T(signalAmps, i);
  signalAmps_data = signalAmps->data;
  loop_ub = refmat->size[0] * refmat->size[1];
  for (i = 0; i < loop_ub; i++) {
    signalAmps_data[i] = refmat_data[i];
  }

  d_circshift(signalAmps);
  signalAmps_data = signalAmps->data;
  if (refmat->size[0] == 1) {
    i = r3->size[0];
  } else {
    i = refmat->size[0];
  }

  if (refmat->size[1] == 1) {
    i1 = r3->size[1];
  } else {
    i1 = refmat->size[1];
  }

  if (refmat->size[0] == 1) {
    i2 = r3->size[0];
  } else {
    i2 = refmat->size[0];
  }

  if (i2 == 1) {
    i2 = r4->size[0];
  } else if (refmat->size[0] == 1) {
    i2 = r3->size[0];
  } else {
    i2 = refmat->size[0];
  }

  if (refmat->size[1] == 1) {
    i3 = r3->size[1];
  } else {
    i3 = refmat->size[1];
  }

  if (i3 == 1) {
    i3 = r4->size[1];
  } else if (refmat->size[1] == 1) {
    i3 = r3->size[1];
  } else {
    i3 = refmat->size[1];
  }

  if (refmat->size[0] == 1) {
    nx = r3->size[0];
  } else {
    nx = refmat->size[0];
  }

  if (nx == 1) {
    nx = r4->size[0];
  } else if (refmat->size[0] == 1) {
    nx = r3->size[0];
  } else {
    nx = refmat->size[0];
  }

  if (refmat->size[0] == 1) {
    wind_start_size = r3->size[0];
  } else {
    wind_start_size = refmat->size[0];
  }

  if (nx == 1) {
    nx = b_refmat->size[0];
  } else if (wind_start_size == 1) {
    nx = r4->size[0];
  } else if (refmat->size[0] == 1) {
    nx = r3->size[0];
  } else {
    nx = refmat->size[0];
  }

  if (refmat->size[1] == 1) {
    wind_start_size = r3->size[1];
  } else {
    wind_start_size = refmat->size[1];
  }

  if (wind_start_size == 1) {
    wind_start_size = r4->size[1];
  } else if (refmat->size[1] == 1) {
    wind_start_size = r3->size[1];
  } else {
    wind_start_size = refmat->size[1];
  }

  if (refmat->size[1] == 1) {
    trueCount = r3->size[1];
  } else {
    trueCount = refmat->size[1];
  }

  if (wind_start_size == 1) {
    wind_start_size = b_refmat->size[1];
  } else if (trueCount == 1) {
    wind_start_size = r4->size[1];
  } else if (refmat->size[1] == 1) {
    wind_start_size = r3->size[1];
  } else {
    wind_start_size = refmat->size[1];
  }

  if ((refmat->size[0] == r3->size[0]) && (refmat->size[1] == r3->size[1]) && (i
       == r4->size[0]) && (i1 == r4->size[1]) && (i2 == b_refmat->size[0]) &&
      (i3 == b_refmat->size[1]) && (nx == signalAmps->size[0]) &&
      (wind_start_size == signalAmps->size[1])) {
    loop_ub = refmat->size[0] * refmat->size[1];
    for (i = 0; i < loop_ub; i++) {
      refmat_data[i] = (((refmat_data[i] + peak_data[i]) +
                         timeSearchRange_data[i]) + b_refmat_data[i]) +
        signalAmps_data[i];
    }
  } else {
    t_binary_expand_op(refmat, r3, r4, b_refmat, signalAmps);
    refmat_data = refmat->data;
  }

  /* figure;spy(freqtimeShiftedBinMaskMatrix_scaled) */
  tp_temp = 1.0 / obj->Fs;

  /* noisePSD = dt^2/T*abs(mean(obj.stft.S+freqtimeShiftedBinMaskMatrixScaled,2,'omitnan')).^2;%Add since it is 0 where we expect noise and NaN where there might be a pulse */
  tip_temp = tp_temp * tp_temp / (obj->n_w / obj->Fs);
  i = r3->size[0] * r3->size[1];
  r3->size[0] = refmat->size[0];
  r3->size[1] = refmat->size[1];
  emxEnsureCapacity_real_T(r3, i);
  peak_data = r3->data;
  loop_ub = refmat->size[0] * refmat->size[1];
  for (i = 0; i < loop_ub; i++) {
    peak_data[i] = refmat_data[i];
  }

  e_circshift(r3);
  peak_data = r3->data;
  i = r4->size[0] * r4->size[1];
  r4->size[0] = refmat->size[0];
  r4->size[1] = refmat->size[1];
  emxEnsureCapacity_real_T(r4, i);
  timeSearchRange_data = r4->data;
  loop_ub = refmat->size[0] * refmat->size[1];
  for (i = 0; i < loop_ub; i++) {
    timeSearchRange_data[i] = refmat_data[i];
  }

  f_circshift(r4);
  timeSearchRange_data = r4->data;
  if (refmat->size[0] == 1) {
    i = r3->size[0];
  } else {
    i = refmat->size[0];
  }

  if (refmat->size[1] == 1) {
    i1 = r3->size[1];
  } else {
    i1 = refmat->size[1];
  }

  if ((refmat->size[0] == r3->size[0]) && (refmat->size[1] == r3->size[1]) && (i
       == r4->size[0]) && (i1 == r4->size[1])) {
    i = b_refmat->size[0] * b_refmat->size[1];
    b_refmat->size[0] = refmat->size[0];
    b_refmat->size[1] = refmat->size[1];
    emxEnsureCapacity_real_T(b_refmat, i);
    b_refmat_data = b_refmat->data;
    loop_ub = refmat->size[0] * refmat->size[1];
    for (i = 0; i < loop_ub; i++) {
      b_refmat_data[i] = (refmat_data[i] + peak_data[i]) +
        timeSearchRange_data[i];
    }

    t_srch_rng[0] = inds_frwd_2_next_valley_size;
    t_srch_rng[1] = nColsOfS;
    imresize(b_refmat, t_srch_rng, r3);
    peak_data = r3->data;
  } else {
    s_binary_expand_op(r3, refmat, r4, inds_frwd_2_next_valley_size, nColsOfS);
    peak_data = r3->data;
  }

  emxFree_real_T(&r4);
  if ((obj->stft->S->size[0] == r3->size[0]) && (obj->stft->S->size[1] ==
       r3->size[1])) {
    i = b_obj->size[0] * b_obj->size[1];
    b_obj->size[0] = obj->stft->S->size[0];
    b_obj->size[1] = obj->stft->S->size[1];
    emxEnsureCapacity_creal_T(b_obj, i);
    obj_data = b_obj->data;
    loop_ub = obj->stft->S->size[0] * obj->stft->S->size[1];
    for (i = 0; i < loop_ub; i++) {
      obj_data[i].re = obj->stft->S->data[i].re + peak_data[i];
      obj_data[i].im = obj->stft->S->data[i].im;
    }

    b_abs(b_obj, refmat);
    refmat_data = refmat->data;
  } else {
    r_binary_expand_op(refmat, obj, r3);
    refmat_data = refmat->data;
  }

  emxFree_creal_T(&b_obj);

  /* Add since it is 0 where we expect noise and NaN where there might be a pulse */
  i = r3->size[0] * r3->size[1];
  r3->size[0] = refmat->size[0];
  r3->size[1] = refmat->size[1];
  emxEnsureCapacity_real_T(r3, i);
  peak_data = r3->data;
  loop_ub = refmat->size[0] * refmat->size[1];
  for (i = 0; i < loop_ub; i++) {
    tp_temp = refmat_data[i];
    peak_data[i] = tp_temp * tp_temp;
  }

  mean(r3, timeBlinderVec);
  timeBlinderVec_data = timeBlinderVec->data;
  emxFree_real_T(&r3);
  i = peak->size[0];
  peak->size[0] = timeBlinderVec->size[0];
  emxEnsureCapacity_real_T(peak, i);
  peak_data = peak->data;
  loop_ub = timeBlinderVec->size[0];
  for (i = 0; i < loop_ub; i++) {
    peak_data[i] = tip_temp * timeBlinderVec_data[i];
  }

  interp1(obj->stft->f, peak, obj->Wf, timeBlinderVec);
  timeBlinderVec_data = timeBlinderVec->data;
  wind_end_size = timeBlinderVec->size[0];
  for (wind_start_size = 0; wind_start_size < wind_end_size; wind_start_size++)
  {
    if (timeBlinderVec_data[wind_start_size] < 0.0) {
      timeBlinderVec_data[wind_start_size] = 0.0;
    }
  }

  tp_temp = obj->stft->f->data[1] - obj->stft->f->data[0];

  /* Not the delta f of the Wf vector, because the frequency bins are the same width, just with half bin steps % */
  /* noisePowers = noisePSDAtZetas*fBinWidthZetas; */
  /* Calculate the power at each of the S locations that were */
  /* selected by the incohsum function. Scores are the mag squared */
  /* S values. Mult by dt^2/T to get psd, then mult by the width of */
  /* the frequency bin to get power. We have to do this because the */
  /* psd in the stft object uses dt^2/T factor for the psd calc.  */
  /* scores; */
  /* signalPlusNoisePSDPulseGroup   = dt^2/T*scores;%scores; */
  repmat(timeBlinderVec, yw_max_all_freq->size[1], b_refmat);
  if ((yw_max_all_freq->size[0] == b_refmat->size[0]) && (yw_max_all_freq->size
       [1] == b_refmat->size[1])) {
    loop_ub = yw_max_all_freq->size[0] * yw_max_all_freq->size[1];
    i = b_refmat->size[0] * b_refmat->size[1];
    b_refmat->size[0] = yw_max_all_freq->size[0];
    b_refmat->size[1] = yw_max_all_freq->size[1];
    emxEnsureCapacity_real_T(b_refmat, i);
    b_refmat_data = b_refmat->data;
    for (i = 0; i < loop_ub; i++) {
      b_refmat_data[i] = tip_temp * yw_max_all_freq_data[i] - b_refmat_data[i];
    }
  } else {
    q_binary_expand_op(b_refmat, tip_temp, yw_max_all_freq);
    b_refmat_data = b_refmat->data;
  }

  /* signalPSDPulseGroup   = signalPlusNoisePSDPulseGroup-noisePSDAtZetas; */
  wind_end_size = b_refmat->size[0] * b_refmat->size[1] - 1;
  trueCount = 0;
  for (wind_start_size = 0; wind_start_size <= wind_end_size; wind_start_size++)
  {
    if (b_refmat_data[wind_start_size] < 0.0) {
      trueCount++;
    }
  }

  emxInit_int32_T(&r8, 1);
  i = r8->size[0];
  r8->size[0] = trueCount;
  emxEnsureCapacity_int32_T(r8, i);
  r1 = r8->data;
  trueCount = 0;
  for (wind_start_size = 0; wind_start_size <= wind_end_size; wind_start_size++)
  {
    if (b_refmat_data[wind_start_size] < 0.0) {
      r1[trueCount] = wind_start_size + 1;
      trueCount++;
    }
  }

  loop_ub = r8->size[0];
  for (i = 0; i < loop_ub; i++) {
    b_refmat_data[r1[i] - 1] = 0.0;
  }

  emxFree_int32_T(&r8);

  /* Can't have negative values */
  /* signalPSDPulseGroup(signalPSD<0)   = 0; %Can't have negative values */
  i = signalAmps->size[0] * signalAmps->size[1];
  signalAmps->size[0] = b_refmat->size[0];
  signalAmps->size[1] = b_refmat->size[1];
  emxEnsureCapacity_real_T(signalAmps, i);
  signalAmps_data = signalAmps->data;
  loop_ub = b_refmat->size[0] * b_refmat->size[1];
  for (i = 0; i < loop_ub; i++) {
    signalAmps_data[i] = b_refmat_data[i] * tp_temp;
  }

  nx = signalAmps->size[0] * signalAmps->size[1];
  for (k = 0; k < nx; k++) {
    signalAmps_data[k] = sqrt(signalAmps_data[k]);
  }

  /* signalPlusNoisePowers = signalPlusNoisePSD*fBinWidthZetas; */
  /* signalPowers          = signalPlusNoisePowers-noisePowers; */
  /* SNRdB = 10*log10(powers./freqBinPowAtZetas); */
  /* Signal power ratio to  noise power in its frequency bin for all pulses in group */
  /* SNRdB = 10*log10(powers./sum(freqBinPowAtZetas));          %Signal power ratio to all noise power in bandwidth */
  /* SNRdB = 10*log10(powers./obj.K*1./sum(freqBinPowAtZetas)); %Average the power across all pulses */
  /* SNRdB = 10*log10(signalPowers./obj.K*1./noisePowers); %Average the power across all pulses */
  repmat(timeBlinderVec, yw_max_all_freq->size[1], refmat);
  refmat_data = refmat->data;
  if ((b_refmat->size[0] == refmat->size[0]) && (b_refmat->size[1] ==
       refmat->size[1])) {
    loop_ub = b_refmat->size[0] * b_refmat->size[1];
    for (i = 0; i < loop_ub; i++) {
      b_refmat_data[i] /= refmat_data[i];
    }
  } else {
    rdivide(b_refmat, refmat);
    b_refmat_data = b_refmat->data;
  }

  nx = b_refmat->size[0] * b_refmat->size[1];
  for (k = 0; k < nx; k++) {
    b_refmat_data[k] = log10(b_refmat_data[k]);
  }

  loop_ub = b_refmat->size[0] * b_refmat->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_refmat_data[i] *= 10.0;
  }

  /* SNRdBPulseGroup = 10*log10(signalPSDPulseGroup./noisePSDAtZetas); */
  wind_end_size = b_refmat->size[0] * b_refmat->size[1] - 1;
  trueCount = 0;
  for (wind_start_size = 0; wind_start_size <= wind_end_size; wind_start_size++)
  {
    if (b_refmat_data[wind_start_size] == rtInf) {
      trueCount++;
    }
  }

  emxInit_int32_T(&r9, 1);
  i = r9->size[0];
  r9->size[0] = trueCount;
  emxEnsureCapacity_int32_T(r9, i);
  r1 = r9->data;
  trueCount = 0;
  for (wind_start_size = 0; wind_start_size <= wind_end_size; wind_start_size++)
  {
    if (b_refmat_data[wind_start_size] == rtInf) {
      r1[trueCount] = wind_start_size + 1;
      trueCount++;
    }
  }

  loop_ub = r9->size[0];
  for (i = 0; i < loop_ub; i++) {
    b_refmat_data[r1[i] - 1] = rtNaN;
  }

  emxFree_int32_T(&r9);

  /* SNRdBPulseGroup(SNRdBPulseGroup==Inf) = NaN; */
  /* Calculate the first and second frequency derivatives of the  */
  /* scores. We'll use these for slope and curvature assessments. */
  /* These aren't truely the frequency derivatives because we don't */
  /* divide by deltaf. The are really dsdfrequency bin. We don't */
  /* really care about the magnitude though, just the sign. Each */
  /* dsdf value is the average of the slope ahead and behind the */
  /* point.  */
  /* dsdf     = [0; mean([diff(scores(1:end-1)),diff(scores(2:end))],2);0];%See notebook entry 2021-02-10 */
  /* d2sdf2   = [0; mean([diff(dsdf(1:end-1)),diff(dsdf(2:end))],2);0];%See notebook entry 2021-02-10 */
  /* This block of code determines where there are peaks (negative */
  /* slopes to the left and right) and where there are valleys */
  /* (positive slopes to left and right) */
  /* greater_than_next = scores(2:end-1)>scores(3:end); */
  /* greater_than_prev = scores(2:end-1)>scores(1:end-2); */
  if (scores->size[0] < 1) {
    loop_ub = 0;
  } else {
    loop_ub = scores->size[0];
  }

  if (scores->size[0] < 2) {
    i = 0;
    i1 = 0;
  } else {
    i = 1;
    i1 = scores->size[0];
  }

  nx = i1 - i;
  emxInit_boolean_T(&greater_than_next, 1);
  if (loop_ub == nx + 1) {
    i1 = peak->size[0];
    peak->size[0] = nx + 1;
    emxEnsureCapacity_real_T(peak, i1);
    peak_data = peak->data;
    for (i1 = 0; i1 < nx; i1++) {
      peak_data[i1] = scores_data[i + i1];
    }

    peak_data[nx] = 0.0;
    i = greater_than_next->size[0];
    greater_than_next->size[0] = loop_ub;
    emxEnsureCapacity_boolean_T(greater_than_next, i);
    msk_data = greater_than_next->data;
    for (i = 0; i < loop_ub; i++) {
      msk_data[i] = (scores_data[i] > peak_data[i]);
    }
  } else {
    p_binary_expand_op(greater_than_next, scores, loop_ub - 1, i, i1 - 1);
    msk_data = greater_than_next->data;
  }

  if (scores->size[0] < 1) {
    loop_ub = 0;
  } else {
    loop_ub = scores->size[0];
  }

  if (scores->size[0] - 1 < 1) {
    nx = 1;
  } else {
    nx = scores->size[0];
  }

  emxInit_boolean_T(&greater_than_prev, 1);
  if (loop_ub == nx) {
    i = peak->size[0];
    peak->size[0] = nx;
    emxEnsureCapacity_real_T(peak, i);
    peak_data = peak->data;
    peak_data[0] = 0.0;
    for (i = 0; i <= nx - 2; i++) {
      peak_data[i + 1] = scores_data[i];
    }

    i = greater_than_prev->size[0];
    greater_than_prev->size[0] = loop_ub;
    emxEnsureCapacity_boolean_T(greater_than_prev, i);
    greater_than_prev_data = greater_than_prev->data;
    for (i = 0; i < loop_ub; i++) {
      greater_than_prev_data[i] = (scores_data[i] > peak_data[i]);
    }
  } else {
    o_binary_expand_op(greater_than_prev, scores, loop_ub - 1, nx - 2);
    greater_than_prev_data = greater_than_prev->data;
  }

  /* slope_pos = [false;~greater_than_next&greater_than_prev;false]; */
  /* slope_neg = [false; greater_than_next&~greater_than_prev;false]; */
  /* slope_val = [false;~greater_than_next&~greater_than_prev;false]; */
  /* slope_peak = [false;greater_than_next&greater_than_prev;false]; */
  i = sideband_msk->size[0];
  sideband_msk->size[0] = greater_than_next->size[0];
  emxEnsureCapacity_boolean_T(sideband_msk, i);
  sideband_msk_data = sideband_msk->data;
  loop_ub = greater_than_next->size[0];
  for (i = 0; i < loop_ub; i++) {
    sideband_msk_data[i] = !msk_data[i];
  }

  i = y->size[0];
  y->size[0] = greater_than_prev->size[0];
  emxEnsureCapacity_boolean_T(y, i);
  y_data = y->data;
  loop_ub = greater_than_prev->size[0];
  for (i = 0; i < loop_ub; i++) {
    y_data[i] = !greater_than_prev_data[i];
  }

  emxInit_boolean_T(&slope_val, 1);
  if (sideband_msk->size[0] == y->size[0]) {
    i = slope_val->size[0];
    slope_val->size[0] = sideband_msk->size[0];
    emxEnsureCapacity_boolean_T(slope_val, i);
    slope_val_data = slope_val->data;
    loop_ub = sideband_msk->size[0];
    for (i = 0; i < loop_ub; i++) {
      slope_val_data[i] = (sideband_msk_data[i] && y_data[i]);
    }
  } else {
    b_and(slope_val, sideband_msk, y);
    slope_val_data = slope_val->data;
  }

  if (scores->size[0] < 2) {
    i = 0;
    i1 = 0;
  } else {
    i = 1;
    i1 = scores->size[0];
  }

  if (scores->size[0] - 1 < 1) {
    loop_ub = 0;
  } else {
    loop_ub = scores->size[0] - 1;
  }

  if (scores->size[0] - 1 < 1) {
    nx = 0;
  } else {
    nx = scores->size[0] - 1;
  }

  if (scores->size[0] < 2) {
    i2 = 0;
    i3 = 0;
  } else {
    i2 = 1;
    i3 = scores->size[0];
  }

  /* [score_left_bndry&slope_neg,score_right_bndry&slope_pos,scores] */
  /* This deals with the frequency masking and some scores will be */
  /* NaN because they were excluded from consideration in the */
  /* incohsum processing. If the score is a left boundary */
  /* (frequencies lower were excluded) and the slope is negative, */
  /* this would be considered a peak. Visa-versa for right */
  /* boundaries.  */
  emxInit_boolean_T(&r10, 1);
  trueCount = i1 - i;
  i1 = r10->size[0];
  r10->size[0] = trueCount;
  emxEnsureCapacity_boolean_T(r10, i1);
  r11 = r10->data;
  for (i1 = 0; i1 < trueCount; i1++) {
    r11[i1] = rtIsNaN(scores_data[i + i1]);
  }

  emxInit_boolean_T(&r12, 1);
  i = r12->size[0];
  r12->size[0] = loop_ub;
  emxEnsureCapacity_boolean_T(r12, i);
  r13 = r12->data;
  for (i = 0; i < loop_ub; i++) {
    r13[i] = rtIsNaN(scores_data[i]);
  }

  emxInit_boolean_T(&r14, 1);
  i = r14->size[0];
  r14->size[0] = nx;
  emxEnsureCapacity_boolean_T(r14, i);
  r15 = r14->data;
  for (i = 0; i < nx; i++) {
    r15[i] = rtIsNaN(scores_data[i]);
  }

  emxInit_boolean_T(&r16, 1);
  loop_ub = i3 - i2;
  i = r16->size[0];
  r16->size[0] = loop_ub;
  emxEnsureCapacity_boolean_T(r16, i);
  r17 = r16->data;
  for (i = 0; i < loop_ub; i++) {
    r17[i] = rtIsNaN(scores_data[i2 + i]);
  }

  emxInit_boolean_T(&slope_peak, 1);
  if (r10->size[0] == 1) {
    i = r12->size[0];
  } else {
    i = r10->size[0];
  }

  if (greater_than_next->size[0] == 1) {
    i1 = y->size[0];
  } else {
    i1 = greater_than_next->size[0];
  }

  if (greater_than_next->size[0] == 1) {
    i2 = greater_than_prev->size[0];
  } else {
    i2 = greater_than_next->size[0];
  }

  if (r10->size[0] == 1) {
    i3 = r12->size[0];
  } else {
    i3 = r10->size[0];
  }

  if (r10->size[0] == 1) {
    nx = r12->size[0];
  } else {
    nx = r10->size[0];
  }

  if (i3 + 1 == 1) {
    if (greater_than_next->size[0] == 1) {
      i3 = y->size[0];
    } else {
      i3 = greater_than_next->size[0];
    }
  } else {
    i3 = nx + 1;
  }

  if (r14->size[0] == 1) {
    nx = r16->size[0];
  } else {
    nx = r14->size[0];
  }

  if (sideband_msk->size[0] == 1) {
    wind_start_size = greater_than_prev->size[0];
  } else {
    wind_start_size = sideband_msk->size[0];
  }

  if (greater_than_next->size[0] == 1) {
    trueCount = greater_than_prev->size[0];
  } else {
    trueCount = greater_than_next->size[0];
  }

  if (r10->size[0] == 1) {
    wind_end_size = r12->size[0];
  } else {
    wind_end_size = r10->size[0];
  }

  if (r10->size[0] == 1) {
    loop_ub = r12->size[0];
  } else {
    loop_ub = r10->size[0];
  }

  if (trueCount == 1) {
    if (wind_end_size + 1 == 1) {
      if (greater_than_next->size[0] == 1) {
        trueCount = y->size[0];
      } else {
        trueCount = greater_than_next->size[0];
      }
    } else {
      trueCount = loop_ub + 1;
    }
  } else if (greater_than_next->size[0] == 1) {
    trueCount = greater_than_prev->size[0];
  } else {
    trueCount = greater_than_next->size[0];
  }

  if (r14->size[0] == 1) {
    wind_end_size = r16->size[0];
  } else {
    wind_end_size = r14->size[0];
  }

  if (r14->size[0] == 1) {
    loop_ub = r16->size[0];
  } else {
    loop_ub = r14->size[0];
  }

  if (wind_end_size + 1 == 1) {
    if (sideband_msk->size[0] == 1) {
      wind_end_size = greater_than_prev->size[0];
    } else {
      wind_end_size = sideband_msk->size[0];
    }
  } else {
    wind_end_size = loop_ub + 1;
  }

  if ((greater_than_next->size[0] == greater_than_prev->size[0]) && (r10->size[0]
       == r12->size[0]) && (greater_than_next->size[0] == y->size[0]) && (i + 1 ==
       i1) && (i2 == i3) && (r14->size[0] == r16->size[0]) &&
      (sideband_msk->size[0] == greater_than_prev->size[0]) && (nx + 1 ==
       wind_start_size) && (trueCount == wind_end_size)) {
    i = slope_peak->size[0];
    slope_peak->size[0] = r10->size[0] + 1;
    emxEnsureCapacity_boolean_T(slope_peak, i);
    slope_peak_data = slope_peak->data;
    slope_peak_data[0] = true;
    loop_ub = r10->size[0];
    for (i = 0; i < loop_ub; i++) {
      slope_peak_data[i + 1] = ((!r11[i]) && r13[i]);
    }

    i = r10->size[0];
    r10->size[0] = r14->size[0] + 1;
    emxEnsureCapacity_boolean_T(r10, i);
    r11 = r10->data;
    loop_ub = r14->size[0];
    for (i = 0; i < loop_ub; i++) {
      r11[i] = ((!r15[i]) && r17[i]);
    }

    r11[r14->size[0]] = true;
    i = slope_peak->size[0];
    slope_peak->size[0] = greater_than_next->size[0];
    emxEnsureCapacity_boolean_T(slope_peak, i);
    slope_peak_data = slope_peak->data;
    loop_ub = greater_than_next->size[0];
    for (i = 0; i < loop_ub; i++) {
      slope_peak_data[i] = ((msk_data[i] && greater_than_prev_data[i]) ||
                            (slope_peak_data[i] && (msk_data[i] && y_data[i])) ||
                            (r11[i] && (sideband_msk_data[i] &&
        greater_than_prev_data[i])));
    }
  } else {
    n_binary_expand_op(slope_peak, greater_than_next, greater_than_prev, r10,
                       r12, y, r14, r16, sideband_msk);
    slope_peak_data = slope_peak->data;
  }

  emxFree_boolean_T(&r16);
  emxFree_boolean_T(&r14);
  emxFree_boolean_T(&r12);
  emxFree_boolean_T(&r10);
  emxFree_boolean_T(&greater_than_prev);
  emxFree_boolean_T(&greater_than_next);

  /* How many time windows difference do we considered the found */
  /* pulse to be the same as one found at a different frequency? */
  /* We'll say that if they are within two pulse time width of  */
  /* each other they are the same pulse.  */
  diff_thresh = 2.0 * obj->n_p / obj->n_ws;
  p = 1U;

  /* Initilize a peak counter variable */
  /* Initially these are the same. */
  /* The peak and peak_ind variables are a vector of scores and the */
  /* frequency index of the identified peaks of the pulses. There */
  /* could only ever be n_freqs peaks, so we preallocate the */
  /* vectors to be that long, although there will typically be far */
  /* fever of them - ideally the number of tags in the signal.  */
  i = peak->size[0];
  peak->size[0] = yw_max_all_freq->size[0];
  emxEnsureCapacity_real_T(peak, i);
  peak_data = peak->data;
  loop_ub = yw_max_all_freq->size[0];
  for (i = 0; i < loop_ub; i++) {
    peak_data[i] = 0.0;
  }

  i = peak_ind->size[0];
  peak_ind->size[0] = yw_max_all_freq->size[0];
  emxEnsureCapacity_real_T(peak_ind, i);
  refmat_data = peak_ind->data;
  loop_ub = yw_max_all_freq->size[0];
  for (i = 0; i < loop_ub; i++) {
    refmat_data[i] = 0.0;
  }

  emxInit_real_T(&bandwidth_of_peak, 1);
  i = bandwidth_of_peak->size[0];
  bandwidth_of_peak->size[0] = yw_max_all_freq->size[0];
  emxEnsureCapacity_real_T(bandwidth_of_peak, i);
  bandwidth_of_peak_data = bandwidth_of_peak->data;
  loop_ub = yw_max_all_freq->size[0];
  for (i = 0; i < loop_ub; i++) {
    bandwidth_of_peak_data[i] = 0.0;
  }

  i = msk->size[0] * msk->size[1];
  msk->size[0] = yw_max_all_freq->size[0];
  msk->size[1] = yw_max_all_freq->size[0];
  emxEnsureCapacity_boolean_T(msk, i);
  msk_data = msk->data;
  loop_ub = yw_max_all_freq->size[0] * yw_max_all_freq->size[0];
  for (i = 0; i < loop_ub; i++) {
    msk_data[i] = false;
  }

  i = indiv_msk->size[0] * indiv_msk->size[1];
  indiv_msk->size[0] = yw_max_all_freq->size[0];
  indiv_msk->size[1] = yw_max_all_freq->size[0];
  emxEnsureCapacity_boolean_T(indiv_msk, i);
  greater_than_prev_data = indiv_msk->data;
  loop_ub = yw_max_all_freq->size[0] * yw_max_all_freq->size[0];
  for (i = 0; i < loop_ub; i++) {
    greater_than_prev_data[i] = false;
  }

  /* peak_masked_curr_scores is a vector of scores where only the */
  /* peaks have scores. All others (valleys, +slope, -slope) are */
  /* set to zero. As we identify peaks, they will also be set to */
  /* zero so that we can work our way through these peaks.  */
  if (scores->size[0] == slope_peak->size[0]) {
    i = timeBlinderVec->size[0];
    timeBlinderVec->size[0] = scores->size[0];
    emxEnsureCapacity_real_T(timeBlinderVec, i);
    timeBlinderVec_data = timeBlinderVec->data;
    loop_ub = scores->size[0];
    for (i = 0; i < loop_ub; i++) {
      timeBlinderVec_data[i] = scores_data[i] * (double)slope_peak_data[i];
    }
  } else {
    m_binary_expand_op(timeBlinderVec, scores, slope_peak);
    timeBlinderVec_data = timeBlinderVec->data;
  }

  /* This checks to make sure that at least one frequency has a */
  /* threshold exceeding score. If there isn't one (all the scroes */
  /* are below the threshold), we set the output variables as NaN */
  /* so that the caller knows nothing was detected.         */
  /* 2021-10-11 */
  /* Update to to set all peak_masked_curr_scores less than the */
  /* threshold to zero. This wasn't needed when there was one */
  /* threshold, but with local frequency specific thresholds, we */
  /* only want threshold positive peaks listed in this vector so */
  /* the while loop below doesn't try to sort out sub-threshold */
  /* peaks. This can happen when there is a sub threhold peak that */
  /* has a higher score than a score at a different frequency that */
  /* was lower, but exceeded it's local threshold.  */
  if (timeBlinderVec->size[0] == 1) {
    i = obj->thresh.threshVecFine->size[0];
  } else {
    i = timeBlinderVec->size[0];
  }

  if ((timeBlinderVec->size[0] == obj->thresh.threshVecFine->size[0]) &&
      (timeBlinderVec->size[0] == i)) {
    loop_ub = timeBlinderVec->size[0];
    for (i = 0; i < loop_ub; i++) {
      timeBlinderVec_data[i] *= (double)(timeBlinderVec_data[i] >=
        obj->thresh.threshVecFine->data[i]);
    }
  } else {
    k_binary_expand_op(timeBlinderVec, obj);
    timeBlinderVec_data = timeBlinderVec->data;
  }

  /* ------------------------------------------------ */
  /* thresh_hold = thresh;thresh = interp1(obj.stft.f,thresh,Wf); */
  i = y->size[0];
  if (obj->thresh.threshVecFine->size[0] == 1) {
    y->size[0] = timeBlinderVec->size[0];
  } else {
    y->size[0] = obj->thresh.threshVecFine->size[0];
  }

  emxEnsureCapacity_boolean_T(y, i);
  y_data = y->data;
  nx = (timeBlinderVec->size[0] != 1);
  stride_1_0 = (obj->thresh.threshVecFine->size[0] != 1);
  if (obj->thresh.threshVecFine->size[0] == 1) {
    loop_ub = timeBlinderVec->size[0];
  } else {
    loop_ub = obj->thresh.threshVecFine->size[0];
  }

  for (i = 0; i < loop_ub; i++) {
    y_data[i] = (timeBlinderVec_data[i * nx] > obj->thresh.threshVecFine->data[i
                 * stride_1_0]);
  }

  if (!allOrAny_anonFcn1(y)) {
    /* peak_ind = []; */
    i = peak_ind->size[0];
    peak_ind->size[0] = 1;
    emxEnsureCapacity_real_T(peak_ind, i);
    refmat_data = peak_ind->data;
    refmat_data[0] = rtNaN;
    i = peak->size[0];
    peak->size[0] = 1;
    emxEnsureCapacity_real_T(peak, i);
    peak_data = peak->data;

    /* []; */
  }

  /* Keep doing this loop below while there are scores that exceed */
  /* the threshold which aren't masked as a valley, +slope, -slope, */
  /* or previously identified peak/sideband.  */
  /* figure; plot3([1:160],ones(160,1)*0,curr_scores) */
  stride_1_0 = (obj->thresh.threshVecFine->size[0] != 1);
  emxInit_int32_T(&r18, 2);
  int exitg1;
  do {
    exitg1 = 0;
    i = y->size[0];
    if (obj->thresh.threshVecFine->size[0] == 1) {
      y->size[0] = timeBlinderVec->size[0];
    } else {
      y->size[0] = obj->thresh.threshVecFine->size[0];
    }

    emxEnsureCapacity_boolean_T(y, i);
    y_data = y->data;
    nx = (timeBlinderVec->size[0] != 1);
    if (obj->thresh.threshVecFine->size[0] == 1) {
      loop_ub = timeBlinderVec->size[0];
    } else {
      loop_ub = obj->thresh.threshVecFine->size[0];
    }

    for (i = 0; i < loop_ub; i++) {
      y_data[i] = (timeBlinderVec_data[i * nx] > obj->thresh.threshVecFine->
                   data[i * stride_1_0]);
    }

    if (allOrAny_anonFcn1(y)) {
      /*    hold on; plot3([1:160],ones(160,1)*p,curr_scores) */
      /* Identify the highest scoring peak of the currently */
      /* identifed scores.  */
      c_maximum(timeBlinderVec, &J, &nx);
      peak_data[(int)p - 1] = J;
      refmat_data[(int)p - 1] = nx;

      /* Build a mask that highlights all the elements whose time */
      /* windows share (or are close) to any of the time windows */
      /* of the pulses associated with the current peak. */
      i = (int)timetol;
      for (k = 0; k < i; k++) {
        /* This block of code is used to find the number of time */
        /* windows between the current peak and the others in */
        /* the same block. It checks the blocks in front and */
        /* behind  */
        /* n_diff_to_curr_pk is a vector of time window */
        /* differences between the currently identified peaks and */
        /* all the other identified time windows in the current */
        /* block */
        i1 = timeBlinderVec->size[0];
        timeBlinderVec->size[0] = n_freqs;
        emxEnsureCapacity_real_T(timeBlinderVec, i1);
        timeBlinderVec_data = timeBlinderVec->data;
        i1 = indsOfBinsValid->size[0];
        indsOfBinsValid->size[0] = n_freqs;
        emxEnsureCapacity_real_T(indsOfBinsValid, i1);
        indsOfBinsValid_data = indsOfBinsValid->data;
        for (i1 = 0; i1 < n_freqs; i1++) {
          timeBlinderVec_data[i1] = rtNaN;
          indsOfBinsValid_data[i1] = rtNaN;
        }

        /* Remember that the segments are long enough to */
        /* guarentee K pulses, but can get K+1. If we identified */
        /* the first or last K peaks, but there is an extra, its */
        /* side bands might be in this list in nearby frequencies. */
        /* We need to exclude these like we do the sidebands that */
        /* are nearby in time. In this case, we want to see if */
        /* any of the identified peaks are +/-tp+/-tip from the */
        /* current peak. Here we look a block forward and/or  */
        /* backward at the reported columns of the S matrix that  */
        /* were identified as exceeding the decision threshold  */
        /* and see if those columns are the same as the current */
        /* blocks identified column. We'll check later in the */
        /* code to see if these are less than a threshold.  */
        if ((double)k + 1.0 <= timetol - 1.0) {
          /* Don't compute forward check when k=n_blks */
          a = S_cols_data[((int)refmat_data[(int)p - 1] + S_cols->size[0] * k) -
            1];
          i1 = x->size[0];
          x->size[0] = S_cols->size[0];
          emxEnsureCapacity_real_T(x, i1);
          timeSearchRange_data = x->data;
          loop_ub = S_cols->size[0];
          for (i1 = 0; i1 < loop_ub; i1++) {
            timeSearchRange_data[i1] = a - S_cols_data[i1 + S_cols->size[0] * (k
              + 1)];
          }

          nx = x->size[0];
          i1 = indsOfBinsValid->size[0];
          indsOfBinsValid->size[0] = x->size[0];
          emxEnsureCapacity_real_T(indsOfBinsValid, i1);
          indsOfBinsValid_data = indsOfBinsValid->data;
          for (nColsOfS = 0; nColsOfS < nx; nColsOfS++) {
            indsOfBinsValid_data[nColsOfS] = fabs(timeSearchRange_data[nColsOfS]);
          }
        } else if ((unsigned int)k + 1U >= 2U) {
          /* Don't compute backward check when k=1 */
          a = S_cols_data[((int)refmat_data[(int)p - 1] + S_cols->size[0] * k) -
            1];
          i1 = x->size[0];
          x->size[0] = S_cols->size[0];
          emxEnsureCapacity_real_T(x, i1);
          timeSearchRange_data = x->data;
          loop_ub = S_cols->size[0];
          for (i1 = 0; i1 < loop_ub; i1++) {
            timeSearchRange_data[i1] = a - S_cols_data[i1 + S_cols->size[0] * (k
              - 1)];
          }

          nx = x->size[0];
          i1 = timeBlinderVec->size[0];
          timeBlinderVec->size[0] = x->size[0];
          emxEnsureCapacity_real_T(timeBlinderVec, i1);
          timeBlinderVec_data = timeBlinderVec->data;
          for (nColsOfS = 0; nColsOfS < nx; nColsOfS++) {
            timeBlinderVec_data[nColsOfS] = fabs(timeSearchRange_data[nColsOfS]);
          }
        }

        /* There could be instances when a single block contains */
        /* two pulses, as mentioned above, but if the search is */
        /* only for one pulse (K = 1) then the if statments above */
        /* won't run. We need here to check if there are */
        /* identified scores within the current block that are */
        /* also one time repetition interval (tip+/tipu) away */
        /* from the current peak */
        /* This code below builds a mask that highlights the  */
        /* sidebands of the peak. It looks for the frequency bin */
        /* (higher and lower) where the score no longer meets  */
        /* the threshold. If no threshold crossings are found,  */
        /* it assumes the entire frequeny list is a sideband.  */
        /* This happens often in an informed search method when */
        /* the frequency search has been narrowed to a small  */
        /* band on either side of a known peak. */
        /* These are the number of frequency bins foward or */
        /* backward from the peak to the last score>threshold */
        /* inds_bkwd_2_thresh_xing = find(scores(peak_ind(p)-1:-1:1)<thresh,1,'first')-1; */
        /* inds_frwd_2_thresh_xing = find(scores(peak_ind(p)+1:end)<thresh,1,'first')-1; */
        stft_dt = refmat_data[(int)p - 1];
        if (stft_dt - 1.0 < 1.0) {
          i1 = 0;
          i2 = 1;
          i3 = -1;
          nColsOfS = 0;
          nx = 1;
          trueCount = -1;
        } else {
          i1 = (int)(stft_dt - 1.0) - 1;
          i2 = -1;
          i3 = 0;
          nColsOfS = (int)(stft_dt - 1.0) - 1;
          nx = -1;
          trueCount = 0;
        }

        loop_ub = div_s32(i3 - i1, i2);
        if (loop_ub + 1 == div_s32(trueCount - nColsOfS, nx) + 1) {
          i3 = y->size[0];
          y->size[0] = loop_ub + 1;
          emxEnsureCapacity_boolean_T(y, i3);
          y_data = y->data;
          for (i3 = 0; i3 <= loop_ub; i3++) {
            y_data[i3] = (scores_data[i1 + i2 * i3] < obj->
                          thresh.threshVecFine->data[nColsOfS + nx * i3]);
          }

          c_eml_find(y, (int *)&inds_frwd_2_next_valley_data,
                     &inds_frwd_2_next_valley_size);
        } else {
          j_binary_expand_op((int *)&inds_frwd_2_next_valley_data,
                             &inds_frwd_2_next_valley_size, scores, i1, i2, i3,
                             obj, nColsOfS, nx, trueCount);
        }

        wind_start_size = inds_frwd_2_next_valley_size;
        for (i1 = 0; i1 < inds_frwd_2_next_valley_size; i1++) {
          wind_start_data = (double)inds_frwd_2_next_valley_data - 1.0;
        }

        if (stft_dt + 1.0 > scores->size[0]) {
          i1 = 0;
          i2 = 0;
        } else {
          i1 = (int)(stft_dt + 1.0) - 1;
          i2 = scores->size[0];
        }

        if (stft_dt + 1.0 > obj->thresh.threshVecFine->size[0]) {
          i3 = 0;
          nColsOfS = 0;
        } else {
          i3 = (int)(refmat_data[(int)p - 1] + 1.0) - 1;
          nColsOfS = obj->thresh.threshVecFine->size[0];
        }

        loop_ub = i2 - i1;
        if (loop_ub == nColsOfS - i3) {
          i2 = y->size[0];
          y->size[0] = loop_ub;
          emxEnsureCapacity_boolean_T(y, i2);
          y_data = y->data;
          for (i2 = 0; i2 < loop_ub; i2++) {
            y_data[i2] = (scores_data[i1 + i2] < obj->thresh.threshVecFine->
                          data[i3 + i2]);
          }

          c_eml_find(y, (int *)&inds_frwd_2_next_valley_data,
                     &inds_frwd_2_next_valley_size);
        } else {
          i_binary_expand_op((int *)&inds_frwd_2_next_valley_data,
                             &inds_frwd_2_next_valley_size, scores, i1, i2 - 1,
                             obj, i3, nColsOfS - 1);
        }

        wind_end_size = inds_frwd_2_next_valley_size;
        for (i1 = 0; i1 < inds_frwd_2_next_valley_size; i1++) {
          naive_wind_end = (double)inds_frwd_2_next_valley_data - 1.0;
        }

        /* Here we look for the location where the slope changes. */
        /* We don't use the -1 like above because we want to be */
        /* sure to capture the entire saddle between peaks, so */
        /* we include the point after the transition of the slope */
        /* sign. If we didn't do this, then the lowest point */
        /* between the peaks that was still above the threshold */
        /* wouldn't be included in a sideband mask and might get */
        /* picked up later as an additional peak.  */
        if (stft_dt - 1.0 < 1.0) {
          i1 = 0;
          i2 = 1;
          i3 = -1;
        } else {
          i1 = (int)(refmat_data[(int)p - 1] - 1.0) - 1;
          i2 = -1;
          i3 = 0;
        }

        loop_ub = div_s32(i3 - i1, i2);
        i3 = y->size[0];
        y->size[0] = loop_ub + 1;
        emxEnsureCapacity_boolean_T(y, i3);
        y_data = y->data;
        for (i3 = 0; i3 <= loop_ub; i3++) {
          y_data[i3] = slope_val_data[i1 + i2 * i3];
        }

        c_eml_find(y, (int *)&inds_frwd_2_next_valley_data,
                   &inds_frwd_2_next_valley_size);
        trueCount = inds_frwd_2_next_valley_size;
        for (i1 = 0; i1 < inds_frwd_2_next_valley_size; i1++) {
          nx = inds_frwd_2_next_valley_data;
        }

        if (stft_dt + 1.0 > slope_val->size[0]) {
          i1 = 0;
          i2 = 0;
        } else {
          i1 = (int)(refmat_data[(int)p - 1] + 1.0) - 1;
          i2 = slope_val->size[0];
        }

        loop_ub = i2 - i1;
        i2 = y->size[0];
        y->size[0] = loop_ub;
        emxEnsureCapacity_boolean_T(y, i2);
        y_data = y->data;
        for (i2 = 0; i2 < loop_ub; i2++) {
          y_data[i2] = slope_val_data[i1 + i2];
        }

        c_eml_find(y, (int *)&inds_frwd_2_next_valley_data,
                   &inds_frwd_2_next_valley_size);

        /* Wf_sub = Wf(freq_mask); */
        if ((wind_end_size == 0) && (wind_start_size == 0)) {
          /* If it can't find a place backwards or forwards */
          /* that is less than the threshold, the whole thing */
          /* could be sideband. Often the case for informed */
          /* search.  */
          /*                         sideband_msk = true(n_freqs,1); */
          /* Alternatively, the interactions of */
          /* adjacent sidebands might be so large, that there */
          /* are no adjacent scores that are below the */
          /* threshold. We need to deal with both of these */
          /* cases. In the latter, we need to find the */
          /* frequency bin ahead of and behind the peak where */
          /* the slope changes and define that as the */
          /* sidebands. If the slope doesn't change, then we */
          /* are likely the former case wherein the entire set */
          /* of scores are side band and we make the mask all */
          /* true.  */
          i1 = sideband_msk->size[0];
          sideband_msk->size[0] = n_freqs;
          emxEnsureCapacity_boolean_T(sideband_msk, i1);
          sideband_msk_data = sideband_msk->data;
          for (i1 = 0; i1 < n_freqs; i1++) {
            sideband_msk_data[i1] = false;
          }

          if ((trueCount == 0) && (inds_frwd_2_next_valley_size == 0)) {
            i1 = sideband_msk->size[0];
            sideband_msk->size[0] = n_freqs;
            emxEnsureCapacity_boolean_T(sideband_msk, i1);
            sideband_msk_data = sideband_msk->data;
            for (i1 = 0; i1 < n_freqs; i1++) {
              sideband_msk_data[i1] = true;
            }
          } else if ((trueCount == 0) && (inds_frwd_2_next_valley_size != 0)) {
            if (refmat_data[(int)p - 1] < 1.0) {
              loop_ub = 0;
            } else {
              loop_ub = (int)refmat_data[(int)p - 1];
            }

            for (i1 = 0; i1 < loop_ub; i1++) {
              sideband_msk_data[i1] = true;
            }
          } else if ((trueCount != 0) && (inds_frwd_2_next_valley_size == 0)) {
            if (stft_dt > n_freqs) {
              i1 = 0;
              i2 = 0;
            } else {
              i1 = (int)refmat_data[(int)p - 1] - 1;
              i2 = n_freqs;
            }

            loop_ub = i2 - i1;
            for (i2 = 0; i2 < loop_ub; i2++) {
              sideband_msk_data[i1 + i2] = true;
            }
          } else if ((trueCount != 0) && (inds_frwd_2_next_valley_size != 0)) {
            if (inds_frwd_2_next_valley_data < -(double)nx) {
              b_excluded_freq_bands->size[0] = 1;
              b_excluded_freq_bands->size[1] = 0;
            } else {
              i1 = b_excluded_freq_bands->size[0] * b_excluded_freq_bands->size
                [1];
              b_excluded_freq_bands->size[0] = 1;
              loop_ub = inds_frwd_2_next_valley_data - (int)-(double)nx;
              b_excluded_freq_bands->size[1] = loop_ub + 1;
              emxEnsureCapacity_real_T(b_excluded_freq_bands, i1);
              b_excluded_freq_bands_data = b_excluded_freq_bands->data;
              for (i1 = 0; i1 <= loop_ub; i1++) {
                b_excluded_freq_bands_data[i1] = -(double)nx + (double)i1;
              }
            }

            i1 = r18->size[0] * r18->size[1];
            r18->size[0] = 1;
            r18->size[1] = b_excluded_freq_bands->size[1];
            emxEnsureCapacity_int32_T(r18, i1);
            r1 = r18->data;
            loop_ub = b_excluded_freq_bands->size[1];
            for (i1 = 0; i1 < loop_ub; i1++) {
              r1[i1] = (int)(stft_dt + b_excluded_freq_bands_data[i1]);
            }

            loop_ub = r18->size[1];
            for (i1 = 0; i1 < loop_ub; i1++) {
              sideband_msk_data[r1[i1] - 1] = true;
            }
          }

          /* If there was a threhold crossing before and/or after  */
          /* the peak, sort out the sidebands here */
        } else {
          i1 = sideband_msk->size[0];
          sideband_msk->size[0] = n_freqs;
          emxEnsureCapacity_boolean_T(sideband_msk, i1);
          sideband_msk_data = sideband_msk->data;
          for (i1 = 0; i1 < n_freqs; i1++) {
            sideband_msk_data[i1] = false;
          }

          if ((wind_end_size == 0) && (wind_start_size != 0)) {
            /* Threshold crossing back was found but not */
            /* forwards. */
            /* What is smaller, the distance from the peak to */
            /* the first entry backwards, or the distance */
            /* from the peak to the threshold crossing in */
            /* front of the peak? Use that distance as the */
            /* 1/2 width of the sideband. */
            i1 = excluded_freq_bands->size[0] * excluded_freq_bands->size[1];
            excluded_freq_bands->size[0] = trueCount;
            excluded_freq_bands->size[1] = 2;
            emxEnsureCapacity_real_T(excluded_freq_bands, i1);
            excluded_freq_bands_data = excluded_freq_bands->data;
            for (i1 = 0; i1 < trueCount; i1++) {
              excluded_freq_bands_data[0] = nx;
            }

            excluded_freq_bands_data[excluded_freq_bands->size[0]] =
              wind_start_data;
            b_wind_start = *excluded_freq_bands;
            i4 = 2;
            b_wind_start.size = &i4;
            b_wind_start.numDimensions = 1;
            bandwidth_of_peak_data[(int)p - 1] = unaryMinOrMax_anonFcn1
              (&b_wind_start);

            /* Had to code this way so coder/simulink would know the size of the min operation */
          } else if ((wind_end_size != 0) && (wind_start_size == 0)) {
            /* Threshold crossing forward was found but not */
            /* backwards. */
            /* What is smaller, the distance from the peak to */
            /* the last entry forwards, or the distance */
            /* from the peak to the threshold crossing in */
            /* back of the peak? Use that distance as the */
            /* 1/2 width of the sideband. */
            i1 = excluded_freq_bands->size[0] * excluded_freq_bands->size[1];
            excluded_freq_bands->size[0] = inds_frwd_2_next_valley_size;
            excluded_freq_bands->size[1] = 2;
            emxEnsureCapacity_real_T(excluded_freq_bands, i1);
            excluded_freq_bands_data = excluded_freq_bands->data;
            for (i1 = 0; i1 < inds_frwd_2_next_valley_size; i1++) {
              excluded_freq_bands_data[0] = inds_frwd_2_next_valley_data;
            }

            excluded_freq_bands_data[excluded_freq_bands->size[0]] =
              naive_wind_end;
            b_wind_start = *excluded_freq_bands;
            i5 = 2;
            b_wind_start.size = &i5;
            b_wind_start.numDimensions = 1;
            bandwidth_of_peak_data[(int)p - 1] = unaryMinOrMax_anonFcn1
              (&b_wind_start);

            /* Had to code this way so coder/simulink  */
            /* would know the size of the min operation */
          } else {
            /* Threshold crossing forward and backward was */
            /* found. */
            /* What is smaller, the distance */
            /* from the peak to the threshold crossing in */
            /* or the distance from the peak to the nearby  */
            /* valley? Use that distance as the 1/2 width of */
            /* the sideband. Do this both forwards and */
            /* backwards.  */
            if (trueCount != 0) {
              i1 = wind_start->size[0] * wind_start->size[1];
              wind_start->size[0] = wind_start_size;
              wind_start->size[1] = 2;
              emxEnsureCapacity_real_T(wind_start, i1);
              peak_data = wind_start->data;
              for (i1 = 0; i1 < wind_start_size; i1++) {
                peak_data[0] = wind_start_data;
              }

              peak_data[wind_start->size[0]] = nx;
              wind_start_size = 1;
              b_wind_start = *wind_start;
              i6 = 2;
              b_wind_start.size = &i6;
              b_wind_start.numDimensions = 1;
              wind_start_data = unaryMinOrMax_anonFcn1(&b_wind_start);
            }

            if (inds_frwd_2_next_valley_size != 0) {
              i1 = excluded_freq_bands->size[0] * excluded_freq_bands->size[1];
              excluded_freq_bands->size[0] = 1;
              excluded_freq_bands->size[1] = 2;
              emxEnsureCapacity_real_T(excluded_freq_bands, i1);
              excluded_freq_bands_data = excluded_freq_bands->data;
              excluded_freq_bands_data[0] = inds_frwd_2_next_valley_data;
              for (i1 = 0; i1 < wind_end_size; i1++) {
                excluded_freq_bands_data[excluded_freq_bands->size[0]] =
                  naive_wind_end;
              }

              wind_end_size = 1;
              b_wind_start = *excluded_freq_bands;
              i7 = 2;
              b_wind_start.size = &i7;
              b_wind_start.numDimensions = 1;
              naive_wind_end = unaryMinOrMax_anonFcn1(&b_wind_start);
            }

            for (i1 = 0; i1 < wind_start_size; i1++) {
              freq_ind_rng_data[0] = wind_start_data;
            }

            for (i1 = 0; i1 < wind_end_size; i1++) {
              freq_ind_rng_data[wind_start_size] = naive_wind_end;
            }

            freq_ind_rng = wind_start_size << 1;
            b_freq_ind_rng_data.data = &freq_ind_rng_data[0];
            b_freq_ind_rng_data.size = &freq_ind_rng;
            b_freq_ind_rng_data.allocatedSize = 2;
            b_freq_ind_rng_data.numDimensions = 1;
            b_freq_ind_rng_data.canFreeData = false;
            bandwidth_of_peak_data[(int)p - 1] = maximum(&b_freq_ind_rng_data);
          }

          /* Make sure we aren't requesting masking of elements */
          /* that are outside the bounds of what we have  */
          /* available in the vector */
          t_srch_rng[0] = 1.0;
          tp_temp = bandwidth_of_peak_data[(int)p - 1];
          t_srch_rng[1] = stft_dt - tp_temp;
          tip_temp = d_maximum(t_srch_rng);
          t_srch_rng[0] = n_freqs;
          t_srch_rng[1] = stft_dt + tp_temp;
          tp_temp = minimum(t_srch_rng);
          if (tip_temp > tp_temp) {
            i1 = 0;
            i2 = 0;
          } else {
            i1 = (int)tip_temp - 1;
            i2 = (int)tp_temp;
          }

          loop_ub = i2 - i1;
          for (i2 = 0; i2 < loop_ub; i2++) {
            sideband_msk_data[i1 + i2] = true;
          }
        }

        /*                      timecheck(:,k) = (n_diff_to_curr_pk<=diff_thresh)|... */
        /*                                       (n_diff_check_back<=diff_thresh)|... */
        /*                                       (n_diff_check_for<=diff_thresh); */
        /* Here we build up a mask that incorporates all the */
        /* peaks and their sidebands that we have identified  */
        /* so far. The msk(:,p+1) entry is here because we are */
        /* looping through n_blks and are updating the p+1 column */
        /* each time.  */
        trueCount = (int)refmat_data[(int)p - 1] - 1;
        a = S_cols_data[trueCount + S_cols->size[0] * k];
        i1 = x->size[0];
        x->size[0] = S_cols->size[0];
        emxEnsureCapacity_real_T(x, i1);
        timeSearchRange_data = x->data;
        loop_ub = S_cols->size[0];
        for (i1 = 0; i1 < loop_ub; i1++) {
          timeSearchRange_data[i1] = a - S_cols_data[i1 + S_cols->size[0] * k];
        }

        nx = x->size[0];
        i1 = peak->size[0];
        peak->size[0] = x->size[0];
        emxEnsureCapacity_real_T(peak, i1);
        peak_data = peak->data;
        for (nColsOfS = 0; nColsOfS < nx; nColsOfS++) {
          peak_data[nColsOfS] = fabs(timeSearchRange_data[nColsOfS]);
        }

        loop_ub = msk->size[0];
        if (peak->size[0] == 1) {
          i1 = timeBlinderVec->size[0];
        } else {
          i1 = peak->size[0];
        }

        if (peak->size[0] == 1) {
          i2 = timeBlinderVec->size[0];
        } else {
          i2 = peak->size[0];
        }

        if (i2 == 1) {
          i2 = indsOfBinsValid->size[0];
        } else if (peak->size[0] == 1) {
          i2 = timeBlinderVec->size[0];
        } else {
          i2 = peak->size[0];
        }

        if (peak->size[0] == 1) {
          i3 = timeBlinderVec->size[0];
        } else {
          i3 = peak->size[0];
        }

        if (sideband_msk->size[0] == 1) {
          if (i3 == 1) {
            i3 = indsOfBinsValid->size[0];
          } else if (peak->size[0] == 1) {
            i3 = timeBlinderVec->size[0];
          } else {
            i3 = peak->size[0];
          }
        } else {
          i3 = sideband_msk->size[0];
        }

        if (peak->size[0] == 1) {
          nx = timeBlinderVec->size[0];
        } else {
          nx = peak->size[0];
        }

        if (sideband_msk->size[0] == 1) {
          if (nx == 1) {
            nx = indsOfBinsValid->size[0];
          } else if (peak->size[0] == 1) {
            nx = timeBlinderVec->size[0];
          } else {
            nx = peak->size[0];
          }
        } else {
          nx = sideband_msk->size[0];
        }

        if (peak->size[0] == 1) {
          wind_start_size = timeBlinderVec->size[0];
        } else {
          wind_start_size = peak->size[0];
        }

        if (nx == 1) {
          nx = S_cols->size[0];
        } else if (sideband_msk->size[0] == 1) {
          if (wind_start_size == 1) {
            nx = indsOfBinsValid->size[0];
          } else if (peak->size[0] == 1) {
            nx = timeBlinderVec->size[0];
          } else {
            nx = peak->size[0];
          }
        } else {
          nx = sideband_msk->size[0];
        }

        if ((peak->size[0] == timeBlinderVec->size[0]) && (i1 ==
             indsOfBinsValid->size[0]) && (sideband_msk->size[0] == i2) && (i3 ==
             S_cols->size[0]) && (msk->size[0] == nx)) {
          tp_temp = S_cols_data[trueCount + S_cols->size[0] * k] + N;
          a = tp_temp + M;
          t_lastknown = tp_temp - M;
          tp_temp = S_cols_data[trueCount + S_cols->size[0] * k] - N;
          wind_start_data = tp_temp - M;
          tip_temp = tp_temp + M;
          i1 = sideband_msk->size[0];
          sideband_msk->size[0] = msk->size[0];
          emxEnsureCapacity_boolean_T(sideband_msk, i1);
          sideband_msk_data = sideband_msk->data;
          for (i1 = 0; i1 < loop_ub; i1++) {
            stft_dt = S_cols_data[i1 + S_cols->size[0] * k];
            sideband_msk_data[i1] = (msk_data[i1 + msk->size[0] * ((int)p - 1)] ||
              msk_data[i1 + msk->size[0] * (int)p] || (sideband_msk_data[i1] ||
              ((peak_data[i1] <= diff_thresh) || (timeBlinderVec_data[i1] <=
              diff_thresh) || (indsOfBinsValid_data[i1] <= diff_thresh)) ||
              (((stft_dt < a) && (stft_dt > t_lastknown)) || ((stft_dt >
              wind_start_data) && (stft_dt < tip_temp)))));
          }

          loop_ub = sideband_msk->size[0];
          for (i1 = 0; i1 < loop_ub; i1++) {
            msk_data[i1 + msk->size[0] * (int)p] = sideband_msk_data[i1];
          }
        } else {
          h_binary_expand_op(msk, p, sideband_msk, peak, diff_thresh,
                             timeBlinderVec, indsOfBinsValid, S_cols, k,
                             peak_ind, N, M);
          msk_data = msk->data;
        }
      }

      /* Extract the mask for this peak and no others */
      loop_ub = msk->size[0];
      for (i = 0; i < loop_ub; i++) {
        greater_than_prev_data[i + indiv_msk->size[0] * ((int)p - 1)] =
          (msk_data[i + msk->size[0] * (int)p] - msk_data[i + msk->size[0] *
           ((int)p - 1)] != 0);
      }

      /* Update the current scores to exclude peaks and sidebands */
      /* we have identified so far.  */
      /* Mask the recently found sidebands                 */
      if (scores->size[0] == 1) {
        i = msk->size[0];
      } else {
        i = scores->size[0];
      }

      if ((scores->size[0] == msk->size[0]) && (i == slope_peak->size[0])) {
        i = timeBlinderVec->size[0];
        timeBlinderVec->size[0] = scores->size[0];
        emxEnsureCapacity_real_T(timeBlinderVec, i);
        timeBlinderVec_data = timeBlinderVec->data;
        loop_ub = scores->size[0];
        for (i = 0; i < loop_ub; i++) {
          timeBlinderVec_data[i] = scores_data[i] * (double)!msk_data[i +
            msk->size[0] * (int)p] * (double)slope_peak_data[i];
        }
      } else {
        l_binary_expand_op(timeBlinderVec, scores, msk, p, slope_peak);
        timeBlinderVec_data = timeBlinderVec->data;
      }

      /* Mask to only look at peaks */
      if (timeBlinderVec->size[0] == 1) {
        i = obj->thresh.threshVecFine->size[0];
      } else {
        i = timeBlinderVec->size[0];
      }

      if ((timeBlinderVec->size[0] == obj->thresh.threshVecFine->size[0]) &&
          (timeBlinderVec->size[0] == i)) {
        loop_ub = timeBlinderVec->size[0];
        for (i = 0; i < loop_ub; i++) {
          timeBlinderVec_data[i] *= (double)(timeBlinderVec_data[i] >=
            obj->thresh.threshVecFine->data[i]);
        }
      } else {
        k_binary_expand_op(timeBlinderVec, obj);
        timeBlinderVec_data = timeBlinderVec->data;
      }

      /* Eliminate non-threshold exceeding scores from consideration */
      /*                  hold on;plot(peak_masked_curr_scores) */
      /*                  pause(1) */
      /* peak_masked_curr_scores = curr_scores.*slope_peak.*independent_super_thresh_msk; */
      p++;
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  emxFree_real_T(&b_excluded_freq_bands);
  emxFree_real_T(&wind_start);
  emxFree_real_T(&x);
  emxFree_int32_T(&r18);
  emxFree_boolean_T(&sideband_msk);
  emxFree_real_T(&bandwidth_of_peak);
  emxFree_real_T(&peak);
  emxFree_boolean_T(&slope_peak);
  emxFree_boolean_T(&slope_val);
  emxFree_real_T(&indsOfBinsValid);
  emxFree_real_T(&timeBlinderVec);
  emxFree_real_T(&excluded_freq_bands);

  /* Clean up the msk and indiv_mask so their columns align with */
  /* n_pulsegroup_found.  */
  g_circshift(msk);
  emxFree_boolean_T(&msk);
  if ((int)(p - 1U) < 1) {
    loop_ub = 0;
  } else {
    loop_ub = (int)p - 1;
  }

  nx = indiv_msk->size[0];
  for (i = 0; i < loop_ub; i++) {
    for (i1 = 0; i1 < nx; i1++) {
      greater_than_prev_data[i1 + nx * i] = greater_than_prev_data[i1 +
        indiv_msk->size[0] * i];
    }
  }

  i = indiv_msk->size[0] * indiv_msk->size[1];
  indiv_msk->size[1] = loop_ub;
  emxEnsureCapacity_boolean_T(indiv_msk, i);
  if ((int)(p - 1U) > 0) {
    /* Only update from NaN if there were some found.  */
    i = peak_ind->size[0];
    peak_ind->size[0] = (int)(p - 1U);
    emxEnsureCapacity_real_T(peak_ind, i);
  }

  /* Each row of msk is a mask that isolates the elements of the */
  /* yw_max_all_freq vector associated with that column's peak and all */
  /* higher power peaks. For exampl msk(:,2) provides a mask that */
  /* highlights which elements of yw_max_all_freq are associated in */
  /* time with the second highest peak and the first highest peak. */
  /* Plotting scores.*~msk(:,2) will plot all of the scores of */
  /* yw_max_all_freq that are not associated in time with the first */
  /* or second highest power peak. */
  /*             %% CODE FOR REPORTING A CANDIDATE PULSE AT ALL THE FREQUENCY */
  /* BINS WITHOUTH DOING THE THRESHOLDING. */
  /* Preallocate cur_pl matrix */
  /* This was the original code, but it doesn't work with Code */
  /* Generation */
  /* cur_pl(1:n_freqs,1:n_pls) = pulse; */
  /* cur_pl = pulse.empty(n_freqs,n_pls,0);  %Build empty array           */
  /* cur_pl(n_freqs,n_pls,1) = pulse;        %This will cause all array elements to fill with the empty constructor */
  /* cur_pl = pulse; */
  /* cur_pl(n_freqs,n_pls) = pulse; */
  emxInitStruct_struct_T(&b_expl_temp);
  makepulsestruc(&tip_temp, &tp_temp, &a, &t_lastknown, &wind_start_data,
                 &stft_dt, b_expl_temp.t_next, &timetol, &diff_thresh,
                 &naive_wind_end, b_expl_temp.mode, &t6_det_dec, &t6_con_dec);
  b_expl_temp.con_dec = t6_con_dec;
  b_expl_temp.det_dec = t6_det_dec;
  b_expl_temp.fend = naive_wind_end;
  b_expl_temp.fstart = diff_thresh;
  b_expl_temp.fp = timetol;
  b_expl_temp.t_f = stft_dt;
  b_expl_temp.t_0 = wind_start_data;
  b_expl_temp.yw = t_lastknown;
  b_expl_temp.SNR = a;
  b_expl_temp.P = tp_temp;
  b_expl_temp.A = tip_temp;
  c_repmat(&b_expl_temp, yw_max_all_freq->size[0], yw_max_all_freq->size[1],
           pl_out);
  pl_out_data = pl_out->data;
  emxFreeStruct_struct_T(&b_expl_temp);

  /* Create a frequency array that accounts for the masking that */
  /* was done to reduce the frequency space. */
  /* freq_found = Wf_sub(S_rows); */
  /* t_found here is the start of the pulse - not the center like */
  /* in the time stamps in the stft, which are the centers of the */
  /* windows. The dt_stft/2 term offfset would affect both the first */
  /* and second terms of the equation below and therefore cancel. */
  i = refmat->size[0] * refmat->size[1];
  refmat->size[0] = yw_max_all_freq->size[0];
  refmat->size[1] = yw_max_all_freq->size[1];
  emxEnsureCapacity_real_T(refmat, i);
  refmat_data = refmat->data;
  loop_ub = yw_max_all_freq->size[0] * yw_max_all_freq->size[1];
  for (i = 0; i < loop_ub; i++) {
    refmat_data[i] = rtNaN;
  }

  /* t_found    = obj.stft.t(S_cols)-obj.stft.t(1)+obj.t_0;%Don't forget the add the t_0 of this waveform */
  wind_end_size = freq_mask->size[0] - 1;
  trueCount = 0;
  for (wind_start_size = 0; wind_start_size <= wind_end_size; wind_start_size++)
  {
    if (freq_mask_data[wind_start_size]) {
      trueCount++;
    }
  }

  emxInit_int32_T(&r19, 1);
  i = r19->size[0];
  r19->size[0] = trueCount;
  emxEnsureCapacity_int32_T(r19, i);
  r1 = r19->data;
  trueCount = 0;
  for (wind_start_size = 0; wind_start_size <= wind_end_size; wind_start_size++)
  {
    if (freq_mask_data[wind_start_size]) {
      r1[trueCount] = wind_start_size + 1;
      trueCount++;
    }
  }

  emxInit_real_T(&r20, 2);
  i = r20->size[0] * r20->size[1];
  r20->size[0] = r19->size[0];
  r20->size[1] = S_cols->size[1];
  emxEnsureCapacity_real_T(r20, i);
  peak_data = r20->data;
  loop_ub = S_cols->size[1];
  for (i = 0; i < loop_ub; i++) {
    nx = r19->size[0];
    for (i1 = 0; i1 < nx; i1++) {
      peak_data[i1 + r20->size[0] * i] = obj->stft->t->data[(int)S_cols_data
        [(r1[i1] + S_cols->size[0] * i) - 1] - 1];
    }
  }

  emxFree_int32_T(&r19);
  emxFree_real_T(&S_cols);
  wind_end_size = freq_mask->size[0] - 1;
  trueCount = 0;
  for (wind_start_size = 0; wind_start_size <= wind_end_size; wind_start_size++)
  {
    if (freq_mask_data[wind_start_size]) {
      trueCount++;
    }
  }

  emxInit_int32_T(&r21, 1);
  i = r21->size[0];
  r21->size[0] = trueCount;
  emxEnsureCapacity_int32_T(r21, i);
  r1 = r21->data;
  trueCount = 0;
  for (wind_start_size = 0; wind_start_size <= wind_end_size; wind_start_size++)
  {
    if (freq_mask_data[wind_start_size]) {
      r1[trueCount] = wind_start_size + 1;
      trueCount++;
    }
  }

  emxFree_boolean_T(&freq_mask);
  tp_temp = obj->stft->t->data[0];
  loop_ub = r20->size[1];
  for (i = 0; i < loop_ub; i++) {
    nx = r20->size[0];
    for (i1 = 0; i1 < nx; i1++) {
      refmat_data[(r1[i1] + refmat->size[0] * i) - 1] = (peak_data[i1 +
        r20->size[0] * i] - tp_temp) + obj->t_0;
    }
  }

  emxFree_int32_T(&r21);
  emxFree_real_T(&r20);

  /* Don't forget the add the t_0 of this waveform */
  /* f_bands    = [Wf_sub-(Wf_sub(2)-Wf_sub(1))/2,... */
  /*               Wf_sub+(Wf_sub(2)-Wf_sub(1))/2]; */
  tp_temp = (obj->Wf->data[1] - obj->Wf->data[0]) / 2.0;
  i = timeSearchRange->size[0] * timeSearchRange->size[1];
  timeSearchRange->size[0] = obj->Wf->size[0];
  timeSearchRange->size[1] = 2;
  emxEnsureCapacity_real_T(timeSearchRange, i);
  timeSearchRange_data = timeSearchRange->data;
  loop_ub = obj->Wf->size[0];
  for (i = 0; i < loop_ub; i++) {
    timeSearchRange_data[i] = obj->Wf->data[i] - tp_temp;
  }

  loop_ub = obj->Wf->size[0];
  for (i = 0; i < loop_ub; i++) {
    timeSearchRange_data[i + timeSearchRange->size[0]] = obj->Wf->data[i] +
      tp_temp;
  }

  /* Build out the pulse object for each one found */
  i = yw_max_all_freq->size[1];
  for (wind_start_size = 0; wind_start_size < i; wind_start_size++) {
    for (nx = 0; nx < n_freqs; nx++) {
      stft_dt = refmat_data[nx + refmat->size[0] * wind_start_size];
      t_srch_rng[0] = ((stft_dt + obj->ps_pos->t_ip) - obj->ps_pos->t_ipu) -
        (-obj->ps_pos->t_ipj);
      t_srch_rng[1] = ((stft_dt + obj->ps_pos->t_ip) + obj->ps_pos->t_ipu) +
        obj->ps_pos->t_ipj;
      b_makepulsestruc(signalAmps_data[nx + signalAmps->size[0] *
                       wind_start_size], yw_max_all_freq_data[nx +
                       yw_max_all_freq->size[0] * wind_start_size],
                       b_refmat_data[nx + b_refmat->size[0] * wind_start_size],
                       stft_dt, stft_dt + obj->ps_pre->t_p, t_srch_rng, obj->
                       Wf->data[nx], timeSearchRange_data[nx],
                       timeSearchRange_data[nx + timeSearchRange->size[0]],
                       &pl_out_data[nx + pl_out->size[0] * wind_start_size]);

      /* %NaN,... */
      pl_out_data[nx + pl_out->size[0] * wind_start_size].con_dec = false;

      /* Confirmation status */
      loop_ub = obj->thresh.threshVecFine->size[0];
      i1 = y->size[0];
      y->size[0] = loop_ub;
      emxEnsureCapacity_boolean_T(y, i1);
      y_data = y->data;
      for (i1 = 0; i1 < loop_ub; i1++) {
        y_data[i1] = (scores_data[nx] >= obj->thresh.threshVecFine->data[i1]);
      }

      if (ifWhileCond(y)) {
        /* scores(j)>=thresh(j) */
        pl_out_data[nx + pl_out->size[0] * wind_start_size].det_dec = true;
      }
    }
  }

  emxFree_boolean_T(&y);
  emxFree_real_T(&b_refmat);
  emxFree_real_T(&refmat);
  emxFree_real_T(&yw_max_all_freq);
  emxFree_real_T(&signalAmps);
  emxFree_real_T(&scores);
  emxFree_real_T(&timeSearchRange);
}

/*
 * SPECTRO Executes an STFT of x and sets up the wfmstst object
 * for the waveform
 *
 * INPUTS:
 *    obj     The waveform object
 * OUTPUTS:
 *    none
 *
 *             %%
 *
 * Arguments    : waveform *obj
 *                wfmstft *iobj_0
 * Return Type  : void
 */
void b_waveform_spectro(waveform *obj, wfmstft *iobj_0)
{
  emxArray_creal32_T *S;
  emxArray_creal_T *in;
  emxArray_real32_T *local_time;
  emxArray_real32_T *r;
  emxArray_real_T *out;
  creal_T *in_data;
  creal32_T *S_data;
  double n_est;
  double *out_data;
  float *local_time_data;
  float *r1;
  int i;
  int inVectorLength;
  int n;

  /* WFMSTFT Constructs and returns an instance of this class */
  /*  */
  /* An waveform object must be passed to this construction method */
  /* so that the constructor has access to the data vector, desired */
  /* overlap fraction, and priori pulse data, which is used to */
  /* develop the window sizes.  */
  /* INPUTS: */
  /*    waveform_obj   A single waveform object with prior */
  /*                   dependent properties set.  */
  /* OUTPUTS: */
  /*    obj             A wfmstft object */
  /*             %% */
  /*  */
  /* The following are variable sized properties. To tell coder */
  /* that they may vary setup as a local variable size variable */
  /* first, then set. */
  /* Instructions on https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html */
  /* maxFs*maxpulsewidth */
  /* Now actually assign them */
  emxInit_creal_T(&in, 2);
  iobj_0->S->size[0] = 0;
  iobj_0->S->size[1] = 0;
  emxInit_real_T(&out, 1);
  iobj_0->t->size[0] = 0;
  iobj_0->f->size[0] = 0;
  iobj_0->psd->size[0] = 0;
  iobj_0->wind->size[0] = 0;
  iobj_0->dt = 0.0;
  iobj_0->T = 0.0;

  /* wind = hann(waveform_obj.n_w,'periodic'); */
  /* wind = tukeywin(waveform_obj.n_w,0.3); */
  n_est = obj->n_w;
  if (n_est == floor(n_est)) {
    n = (int)n_est;
  } else {
    n = (int)rt_roundd_snf(n_est);
  }

  inVectorLength = 1;
  if (n != 1) {
    inVectorLength = n;
  }

  if (n == 1) {
    i = out->size[0];
    out->size[0] = inVectorLength;
    emxEnsureCapacity_real_T(out, i);
    out_data = out->data;
    for (i = 0; i < inVectorLength; i++) {
      out_data[i] = 1.0;
    }
  } else if (n == 0) {
    i = out->size[0];
    out->size[0] = inVectorLength;
    emxEnsureCapacity_real_T(out, i);
    out_data = out->data;
    for (i = 0; i < inVectorLength; i++) {
      out_data[i] = 1.0;
    }
  } else {
    i = out->size[0];
    out->size[0] = inVectorLength;
    emxEnsureCapacity_real_T(out, i);
    out_data = out->data;
    for (i = 0; i < inVectorLength; i++) {
      out_data[i] = 1.0;
    }
  }

  i = iobj_0->wind->size[0];
  iobj_0->wind->size[0] = out->size[0];
  emxEnsureCapacity_real_T(iobj_0->wind, i);
  n = out->size[0];
  for (i = 0; i < n; i++) {
    iobj_0->wind->data[i] = 1.0;
  }

  emxInit_creal32_T(&S, 2);
  emxInit_real32_T(&r, 1);
  emxInit_real32_T(&local_time, 1);
  stft(obj->x, obj->Fs, iobj_0->wind, obj->n_ol, obj->n_w, S, r, local_time);
  local_time_data = local_time->data;
  r1 = r->data;
  S_data = S->data;
  i = out->size[0];
  out->size[0] = r->size[0];
  emxEnsureCapacity_real_T(out, i);
  out_data = out->data;
  n = r->size[0];
  for (i = 0; i < n; i++) {
    out_data[i] = r1[i];
  }

  emxFree_real32_T(&r);
  inVectorLength = 1;
  if (out->size[0] != 1) {
    inVectorLength = out->size[0];
  }

  if (out->size[0] == 1) {
    n_est = out_data[0];
    i = out->size[0];
    out->size[0] = inVectorLength;
    emxEnsureCapacity_real_T(out, i);
    out_data = out->data;
    for (i = 0; i < inVectorLength; i++) {
      out_data[i] = n_est;
    }
  } else {
    i = out->size[0];
    out->size[0] = inVectorLength;
    emxEnsureCapacity_real_T(out, i);
    out_data = out->data;
  }

  i = iobj_0->f->size[0];
  iobj_0->f->size[0] = out->size[0];
  emxEnsureCapacity_real_T(iobj_0->f, i);
  n = out->size[0];
  for (i = 0; i < n; i++) {
    iobj_0->f->data[i] = out_data[i];
  }

  i = in->size[0] * in->size[1];
  in->size[0] = S->size[0];
  in->size[1] = S->size[1];
  emxEnsureCapacity_creal_T(in, i);
  in_data = in->data;
  n = S->size[0] * S->size[1];
  for (i = 0; i < n; i++) {
    in_data[i].re = S_data[i].re;
    in_data[i].im = S_data[i].im;
  }

  emxFree_creal32_T(&S);
  if ((in->size[0] == 1) && (in->size[1] == 1)) {
    double in_im;
    n_est = in_data[0].re;
    in_im = in_data[0].im;
    i = in->size[0] * in->size[1];
    in->size[0] = 1;
    in->size[1] = 1;
    emxEnsureCapacity_creal_T(in, i);
    in_data = in->data;
    in_data[0].re = n_est;
    in_data[0].im = in_im;
  }

  i = iobj_0->S->size[0] * iobj_0->S->size[1];
  iobj_0->S->size[0] = in->size[0];
  iobj_0->S->size[1] = in->size[1];
  emxEnsureCapacity_creal_T(iobj_0->S, i);
  n = in->size[0] * in->size[1];
  for (i = 0; i < n; i++) {
    iobj_0->S->data[i] = in_data[i];
  }

  emxFree_creal_T(&in);

  /*  Incoming x data in waveform is single precision, but sparse matrix multipliation later is only supported for double precision. */
  i = out->size[0];
  out->size[0] = local_time->size[0];
  emxEnsureCapacity_real_T(out, i);
  out_data = out->data;
  n = local_time->size[0];
  for (i = 0; i < n; i++) {
    out_data[i] = local_time_data[i] + obj->t_0;
  }

  emxFree_real32_T(&local_time);
  inVectorLength = 1;
  if (out->size[0] != 1) {
    inVectorLength = out->size[0];
  }

  if (out->size[0] == 1) {
    n_est = out_data[0];
    i = out->size[0];
    out->size[0] = inVectorLength;
    emxEnsureCapacity_real_T(out, i);
    out_data = out->data;
    for (i = 0; i < inVectorLength; i++) {
      out_data[i] = n_est;
    }
  } else {
    i = out->size[0];
    out->size[0] = inVectorLength;
    emxEnsureCapacity_real_T(out, i);
    out_data = out->data;
  }

  i = iobj_0->t->size[0];
  iobj_0->t->size[0] = out->size[0];
  emxEnsureCapacity_real_T(iobj_0->t, i);
  n = out->size[0];
  for (i = 0; i < n; i++) {
    iobj_0->t->data[i] = out_data[i];
  }

  emxFree_real_T(&out);

  /* Convert to global time of waveform. Double cast is needed because if x data in stft is single precision then the output t will be single as well. */
  n_est = 1.0 / obj->Fs;
  iobj_0->dt = n_est;
  n_est = obj->n_w / obj->Fs;
  iobj_0->T = n_est;
  wfmstft_updatepsd(iobj_0);

  /* obj.psd = obj.dt^2/obj.T*mean(abs(obj.S).^2,2);% Sxx = dt^2/T*|xhat(f)|^2  */
  /* Vestigial properties no longer used. Kept in case we want */
  /* to resurect them.  */
  /* obj.wind_per_pulse = floor(waveform_obj.n_w/waveform_obj.n_p); %How many windows are needed to capture a pulse */
  /* obj.stft_steps_per_pulse = floor(waveform_obj.t_ws/waveform_obj.ps_pre.t_p);%How many stft steps are needed to capture a pulse */
  obj->stft = iobj_0;
}

/*
 * WAVEFORM Constructs an instance of this class
 * INPUTS:
 *    x       1xn     Vector of samples
 *    Fs      1x1     Sample frequency (Hz)
 *    t_0     1x1     Time stamp of first element (s)
 *  ps_pre  1x1     Pulse stats object from previous data (priori)
 *    OLF     1x1     Overlap fraction as decimal (0.5 = 50%
 *                    overlap)
 * OUTPUTS:
 *    obj             The waveform object
 *             %%
 *
 * Arguments    : b_waveform *obj
 *                const creal32_T x[1000]
 *                double Fs
 *                pulsestats *ps_pre
 *                pulsestats *iobj_0
 *                wfmstft *iobj_1
 * Return Type  : b_waveform *
 */
b_waveform *b_waveform_waveform(b_waveform *obj, const creal32_T x[1000], double
  Fs, pulsestats *ps_pre, pulsestats *iobj_0, wfmstft *iobj_1)
{
  b_waveform *b_obj;
  pulsestats *obj_out;
  int i;
  b_obj = obj;
  b_obj->x->size[0] = 1;
  b_obj->x->size[1] = 0;

  /* Flatten input to row */
  i = b_obj->x->size[0] * b_obj->x->size[1];
  b_obj->x->size[0] = 1;
  b_obj->x->size[1] = 1000;
  emxEnsureCapacity_creal32_T(b_obj->x, i);
  for (i = 0; i < 1000; i++) {
    b_obj->x->data[i] = x[i];
  }

  double b_ps_pre[2];
  double n_ol;
  double n_p;

  /* Data vector */
  /* Elements in the data */
  b_obj->Fs = Fs;

  /* Sample rate */
  b_obj->t_0 = 0.0;

  /* Time stamp of first element */
  /* Time stamp of last element */
  /* This is the time when next */
  /* segment should start to */
  /* ensure sufficient overlap. */
  /* Will need to be updated  */
  /* elsewhere.  */
  b_obj->ps_pre = ps_pre;
  b_obj->OLF = 0.5;

  /* Overlap Fraction for STFT */
  b_obj->K = rtNaN;

  /* Unknown number of pulses. */
  /* WFMSTFT Constructs and returns an instance of this class */
  /*  */
  /* An waveform object must be passed to this construction method */
  /* so that the constructor has access to the data vector, desired */
  /* overlap fraction, and priori pulse data, which is used to */
  /* develop the window sizes.  */
  /* INPUTS: */
  /*    waveform_obj   A single waveform object with prior */
  /*                   dependent properties set.  */
  /* OUTPUTS: */
  /*    obj             A wfmstft object */
  /*             %% */
  /*  */
  /* The following are variable sized properties. To tell coder */
  /* that they may vary setup as a local variable size variable */
  /* first, then set. */
  /* Instructions on https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html */
  /* maxFs*maxpulsewidth */
  /* Now actually assign them */
  iobj_1->S->size[0] = 0;
  iobj_1->S->size[1] = 0;
  iobj_1->t->size[0] = 0;
  iobj_1->f->size[0] = 0;
  iobj_1->psd->size[0] = 0;
  iobj_1->wind->size[0] = 0;
  iobj_1->dt = 0.0;
  iobj_1->T = 0.0;
  b_obj->stft = iobj_1;

  /* Unknown values but set types */
  /* Copy over ps_ */
  /* COPY Creates an exact copy of the pulse stats object as a separate object */
  b_ps_pre[0] = ps_pre->tmplt[0];
  b_ps_pre[1] = ps_pre->tmplt[1];
  obj_out = b_pulsestats_pulsestats(iobj_0, ps_pre->t_p, ps_pre->t_ip,
    ps_pre->t_ipu, ps_pre->t_ipj, ps_pre->fp, ps_pre->fstart, ps_pre->fend,
    b_ps_pre, ps_pre->mode, ps_pre->pl, ps_pre->clst, ps_pre->cmsk, ps_pre->cpki);

  /* ,... */
  /* obj.thresh); */
  b_obj->ps_pos = obj_out;

  /* Current stats are same as previous during construction */
  /* obj.ps_pos = pulsestats();%TESTING FOR CODER - NEEDS TO BE REVERTED BACK TO LAST LINE */
  /* obj.TimeCorr = TemporalCorrelator(10, 0, 0);%Generate a temporalcorrelator object so coder knows the type of the object */
  /* SETPRIORIDEPENDENTVARS updates the properties in the */
  /* waveform that are dependent on properties in a pulsestats */
  /* object.  */
  /*  */
  /* INPUTS:   */
  /*    obj     waveform object */
  /*    ps_obj  a pulse stats object */
  /* OUTPUTS:  */
  /*    None (This method modifies the waveform object properties)  */
  /*  */
  /*             %% */
  /* GETPRIORIDEPENDENTVARS returns the properties in the */
  /* waveform that are dependent on prior pulse data estimates. It */
  /* depends on the waveform properties list Fs etc, as well as */
  /* pulse stats like t_ip, etc. */
  /* INPUTS:  ps_obj  1x1 pulse stats object */
  /* OUTPUTS:  pulse stats object */
  /* WHAT WAS DONE BY THIS METHOD IS NOW DONE BY A METHOD OF THE */
  /* PULSESTATS CLASS.  */
  /*          function [] = update_posteriori(obj,pulselist) */
  /*              %UPDATE_POSTERIORI updates the posteriori pulse statistics of */
  /*              %this waveform object using the new pulse list (input) and the */
  /*              %apriori stats. The pulse contained in the waveform's ps_pos */
  /*              %property is not used directly so that the caller can decide */
  /*              %which pulses on which to focus the posteriori.  */
  /*               */
  /*              t_found    = [pulselist(:).t_0]'; */
  /*              freq_found = mean([pulselist(:).fp],'omitnan'); */
  /*               */
  /*              %Create a vector of bandwidths from the pulselist */
  /*              bw_found = 2*(mean([pulselist.fend],'omitnan')-mean([pulselist.fstart],'omitnan')); */
  /*              if isempty(bw_found) */
  /*                  bw_found = 100; */
  /*                  if coder.target('MATLAB') */
  /*                      warning(['UAV-R: No bandwidth could be calculated ',...  */
  /*                           'from the start and stop frequencies of the ',... */
  /*                           'identified pulses. A bandwidth of 100 Hz ',... */
  /*                           'will be used for continued informed search.']) */
  /*                  end */
  /*              end */
  /*               */
  /*              %Here is where we update the stats. These methods of updates */
  /*              %could be improved in the future.  */
  /*              %obj.ps_pre.t_p; %tp doesn't change. We assume it is stationary */
  /*               */
  /*              if numel(pulselist)==1% Happens if K=1 */
  /*                  %We only have one pulse to reference, so we need to check */
  /*                  %the prior pulse too.  */
  /*                  if ~isempty(obj.ps_pre.pl) && ~isnan(obj.ps_pre.pl(end).t_0) */
  /*                      recent_tip = pulselist.t_0-obj.ps_pre.pl(end).t_0; */
  /*                      %There could be a case where the last segment and this */
  /*                      %segement identified the same pulse. In this case */
  /*                      %recent_tip will be very small. In this case, we just */
  /*                      %say we learned nothing about t_ip in this segment.  */
  /*                      if recent_tip < obj.ps_pre.t_ipu + obj.ps_pre.t_ipJ */
  /*                          recent_tip = NaN; */
  /*                      end */
  /*                  else */
  /*                      %No new information because we don't know the last  */
  /*                      %pulse time */
  /*                      recent_tip = NaN; */
  /*                  end */
  /*              else */
  /*                  recent_tip = diff(t_found); */
  /*              end */
  /*              %Do a check here to make sure the new tip isn't a huge change. */
  /*              %This could potentially happen if we are in the K = 1 case and */
  /*              %the block getting processed contained two pulses, with the */
  /*              %latter pulse getting identified/detected. The lines above */
  /*              %would look back to the last identified pulse and it might be */
  /*              %2*tip back in time, producing a very large recenttip values. */
  /*              %If something like this happens, we ignore it so it doesn't */
  /*              %affect our new tip estimates.  */
  /*              if recent_tip > 1.5*obj.ps_pre.t_ip & recent_tip < 0.5*obj.ps_pre.t_ip */
  /*                  recent_tip = NaN; */
  /*              end */
  /*               */
  /*              %Only update time parameters if we are in tracking mode. If we */
  /*              %aren't, we may have identified somethign that isn't a pulse */
  /*              if strcmp(obj.ps_pos.mode,'T') || strcmp(obj.ps_pre.mode,'T') */
  /*                  obj.ps_pos.t_ip  = mean([recent_tip;obj.ps_pre.t_ip],'omitnan'); */
  /*                  obj.ps_pos.t_ipu = obj.ps_pre.t_ipu; %Don't update this because it can get too narrow.%mean([3*std(diff(t_found));obj.ps_pre.t_ipu]); */
  /*                  obj.ps_pos.t_ipj = obj.ps_pre.t_ipj; */
  /*              end */
  /*              fp_pos           = freq_found;%nanmean([freq_found;obj.ps_pre.fp]);%Previous fc may be nan if unknown */
  /*              obj.ps_pos.fp    = fp_pos; */
  /*              obj.ps_pos.fstart = fp_pos-bw_found/2; */
  /*              obj.ps_pos.fend   = fp_pos+bw_found/2; */
  /*               */
  /*              obj.ps_pos.psdHist = obj.stft.psd */
  /*          end */
  n_p = ps_pre->t_p * b_obj->Fs;
  n_p = ceil(n_p);

  /* Samples per pulse */
  /* Number of elements in STFT window */
  n_ol = b_obj->OLF * n_p;

  /* Number of elements overlap in STFT window */
  /* Number of elements in each step of STFT */
  /* Time of each step of STFT */
  /* Samples per pulse */
  b_obj->n_w = n_p;

  /* Number of elements in STFT window */
  b_obj->n_ol = floor(n_ol);

  /* Number of elements overlap in STFT window */
  /* Number of elements in each step of STFT */
  /* Time of each step of STFT */
  /* Samples of interpulse duration */
  /* Baseline interpulse duration in units of STFT windows */
  /* Interpulse duration deviation from baselines in units of STFT windows */
  /* Amount of deviation from the PRI means to search */
  /*              if K ~= 1 */
  /*                  samplesforKpulses = n_ws*(K*(N+M)-2*M)+n_ol; */
  /*              else */
  /*                  samplesforKpulses = n_ws*(N+M+J+1)+n_ol; */
  /*              end */
  /* See 2022-07-11 for updates to samples def */
  /* obj.t_nextsegstart  = obj.t_0+(samplesforKpulses)/obj.Fs; %Don't need the overlap here since the next segment starts at samplesforKpulses+n_ol-n_ol from current sample */
  /* Don't need the overlap here since the next segment starts at samplesforKpulses+n_ol-n_ol from current sample */
  /*              if isempty(obj.TimeCorr) */
  /*                  obj.TimeCorr = TemporalCorrelator(N, M, J); */
  /*              else */
  /*                  obj.TimeCorr.update(N, M, J); */
  /*              end */
  return b_obj;
}

/*
 * SETPRIORIDEPENDENTVARS updates the properties in the
 * waveform that are dependent on properties in a pulsestats
 * object.
 *
 * INPUTS:
 *    obj     waveform object
 *    ps_obj  a pulse stats object
 * OUTPUTS:
 *    None (This method modifies the waveform object properties)
 *
 *             %%
 *
 * Arguments    : waveform *obj
 *                const pulsestats *ps_obj
 * Return Type  : void
 */
void c_waveform_setprioridependentpr(waveform *obj, const pulsestats *ps_obj)
{
  double M;
  double N;
  double n_ip;
  double n_ipj;
  double n_ipu;
  double n_ol;
  double n_p;
  double n_ws;
  double val;

  /* GETPRIORIDEPENDENTVARS returns the properties in the */
  /* waveform that are dependent on prior pulse data estimates. It */
  /* depends on the waveform properties list Fs etc, as well as */
  /* pulse stats like t_ip, etc. */
  /* INPUTS:  ps_obj  1x1 pulse stats object */
  /* OUTPUTS:  pulse stats object */
  /* WHAT WAS DONE BY THIS METHOD IS NOW DONE BY A METHOD OF THE */
  /* PULSESTATS CLASS.  */
  /*          function [] = update_posteriori(obj,pulselist) */
  /*              %UPDATE_POSTERIORI updates the posteriori pulse statistics of */
  /*              %this waveform object using the new pulse list (input) and the */
  /*              %apriori stats. The pulse contained in the waveform's ps_pos */
  /*              %property is not used directly so that the caller can decide */
  /*              %which pulses on which to focus the posteriori.  */
  /*               */
  /*              t_found    = [pulselist(:).t_0]'; */
  /*              freq_found = mean([pulselist(:).fp],'omitnan'); */
  /*               */
  /*              %Create a vector of bandwidths from the pulselist */
  /*              bw_found = 2*(mean([pulselist.fend],'omitnan')-mean([pulselist.fstart],'omitnan')); */
  /*              if isempty(bw_found) */
  /*                  bw_found = 100; */
  /*                  if coder.target('MATLAB') */
  /*                      warning(['UAV-R: No bandwidth could be calculated ',...  */
  /*                           'from the start and stop frequencies of the ',... */
  /*                           'identified pulses. A bandwidth of 100 Hz ',... */
  /*                           'will be used for continued informed search.']) */
  /*                  end */
  /*              end */
  /*               */
  /*              %Here is where we update the stats. These methods of updates */
  /*              %could be improved in the future.  */
  /*              %obj.ps_pre.t_p; %tp doesn't change. We assume it is stationary */
  /*               */
  /*              if numel(pulselist)==1% Happens if K=1 */
  /*                  %We only have one pulse to reference, so we need to check */
  /*                  %the prior pulse too.  */
  /*                  if ~isempty(obj.ps_pre.pl) && ~isnan(obj.ps_pre.pl(end).t_0) */
  /*                      recent_tip = pulselist.t_0-obj.ps_pre.pl(end).t_0; */
  /*                      %There could be a case where the last segment and this */
  /*                      %segement identified the same pulse. In this case */
  /*                      %recent_tip will be very small. In this case, we just */
  /*                      %say we learned nothing about t_ip in this segment.  */
  /*                      if recent_tip < obj.ps_pre.t_ipu + obj.ps_pre.t_ipJ */
  /*                          recent_tip = NaN; */
  /*                      end */
  /*                  else */
  /*                      %No new information because we don't know the last  */
  /*                      %pulse time */
  /*                      recent_tip = NaN; */
  /*                  end */
  /*              else */
  /*                  recent_tip = diff(t_found); */
  /*              end */
  /*              %Do a check here to make sure the new tip isn't a huge change. */
  /*              %This could potentially happen if we are in the K = 1 case and */
  /*              %the block getting processed contained two pulses, with the */
  /*              %latter pulse getting identified/detected. The lines above */
  /*              %would look back to the last identified pulse and it might be */
  /*              %2*tip back in time, producing a very large recenttip values. */
  /*              %If something like this happens, we ignore it so it doesn't */
  /*              %affect our new tip estimates.  */
  /*              if recent_tip > 1.5*obj.ps_pre.t_ip & recent_tip < 0.5*obj.ps_pre.t_ip */
  /*                  recent_tip = NaN; */
  /*              end */
  /*               */
  /*              %Only update time parameters if we are in tracking mode. If we */
  /*              %aren't, we may have identified somethign that isn't a pulse */
  /*              if strcmp(obj.ps_pos.mode,'T') || strcmp(obj.ps_pre.mode,'T') */
  /*                  obj.ps_pos.t_ip  = mean([recent_tip;obj.ps_pre.t_ip],'omitnan'); */
  /*                  obj.ps_pos.t_ipu = obj.ps_pre.t_ipu; %Don't update this because it can get too narrow.%mean([3*std(diff(t_found));obj.ps_pre.t_ipu]); */
  /*                  obj.ps_pos.t_ipj = obj.ps_pre.t_ipj; */
  /*              end */
  /*              fp_pos           = freq_found;%nanmean([freq_found;obj.ps_pre.fp]);%Previous fc may be nan if unknown */
  /*              obj.ps_pos.fp    = fp_pos; */
  /*              obj.ps_pos.fstart = fp_pos-bw_found/2; */
  /*              obj.ps_pos.fend   = fp_pos+bw_found/2; */
  /*               */
  /*              obj.ps_pos.psdHist = obj.stft.psd */
  /*          end */
  n_p = ps_obj->t_p * obj->Fs;
  n_p = ceil(n_p);

  /* Samples per pulse */
  /* Number of elements in STFT window */
  n_ol = obj->OLF * n_p;
  n_ol = floor(n_ol);

  /* Number of elements overlap in STFT window */
  n_ws = n_p - n_ol;

  /* Number of elements in each step of STFT */
  val = n_ws / obj->Fs;

  /* Time of each step of STFT */
  n_ip = ps_obj->t_ip * obj->Fs;
  n_ip = ceil(n_ip);
  n_ipu = ps_obj->t_ipu * obj->Fs;
  n_ipu = ceil(n_ipu);
  n_ipj = ps_obj->t_ipj * obj->Fs;
  n_ipj = ceil(n_ipj);
  N = floor(n_ip / n_ws);
  M = ceil(n_ipu / n_ws);
  n_ipj = ceil(n_ipj / n_ws);
  obj->n_p = n_p;

  /* Samples per pulse */
  obj->n_w = n_p;

  /* Number of elements in STFT window */
  obj->n_ol = n_ol;

  /* Number of elements overlap in STFT window */
  obj->n_ws = n_ws;

  /* Number of elements in each step of STFT */
  obj->t_ws = val;

  /* Time of each step of STFT */
  obj->n_ip = n_ip;

  /* Samples of interpulse duration */
  obj->N = N;

  /* Baseline interpulse duration in units of STFT windows */
  obj->M = M;

  /* Interpulse duration deviation from baselines in units of STFT windows */
  obj->J = n_ipj;

  /* Amount of deviation from the PRI means to search */
  n_ipu = obj->K;

  /*              if K ~= 1 */
  /*                  samplesforKpulses = n_ws*(K*(N+M)-2*M)+n_ol; */
  /*              else */
  /*                  samplesforKpulses = n_ws*(N+M+J+1)+n_ol; */
  /*              end */
  /* See 2022-07-11 for updates to samples def */
  /* obj.t_nextsegstart  = obj.t_0+(samplesforKpulses)/obj.Fs; %Don't need the overlap here since the next segment starts at samplesforKpulses+n_ol-n_ol from current sample */
  n_ipu = obj->t_0 + ((n_ws * ((n_ipu * (N + M) + n_ipj) + 1.0) + n_ol) - n_ws *
                      (2.0 * (n_ipu * M + n_ipj))) / obj->Fs;
  obj->t_nextsegstart[0] = n_ipu;
  obj->t_nextsegstart[1] = n_ipu;

  /* Don't need the overlap here since the next segment starts at samplesforKpulses+n_ol-n_ol from current sample */
  /*              if isempty(obj.TimeCorr) */
  /*                  obj.TimeCorr = TemporalCorrelator(N, M, J); */
  /*              else */
  /*                  obj.TimeCorr.update(N, M, J); */
  /*              end */
}

/*
 * WAVEFORM Constructs an instance of this class
 * INPUTS:
 *    x       1xn     Vector of samples
 *    Fs      1x1     Sample frequency (Hz)
 *    t_0     1x1     Time stamp of first element (s)
 *  ps_pre  1x1     Pulse stats object from previous data (priori)
 *    OLF     1x1     Overlap fraction as decimal (0.5 = 50%
 *                    overlap)
 * OUTPUTS:
 *    obj             The waveform object
 *             %%
 *
 * Arguments    : waveform *obj
 *                const emxArray_creal32_T *x
 *                double Fs
 *                double t_0
 *                pulsestats *ps_pre
 *                const threshold thresh
 *                pulsestats *iobj_0
 *                wfmstft *iobj_1
 * Return Type  : waveform *
 */
waveform *c_waveform_waveform(waveform *obj, const emxArray_creal32_T *x, double
  Fs, double t_0, pulsestats *ps_pre, const threshold thresh, pulsestats *iobj_0,
  wfmstft *iobj_1)
{
  emxArray_creal32_T *in;
  pulsestats *obj_out;
  waveform *b_obj;
  const creal32_T *x_data;
  creal32_T *in_data;
  int i;
  int inVectorLength;
  x_data = x->data;
  b_obj = obj;
  emxInit_creal32_T(&in, 2);
  b_obj->x->size[0] = 1;
  b_obj->x->size[1] = 0;
  b_obj->W->size[0] = 0;
  b_obj->W->size[1] = 0;
  b_obj->Wf->size[0] = 0;

  /* Flatten input to row */
  inVectorLength = 1;
  if (x->size[0] != 1) {
    inVectorLength = x->size[0];
  }

  if (x->size[0] == 1) {
    i = in->size[0] * in->size[1];
    in->size[0] = 1;
    in->size[1] = inVectorLength;
    emxEnsureCapacity_creal32_T(in, i);
    in_data = in->data;
    for (i = 0; i < inVectorLength; i++) {
      in_data[i] = x_data[0];
    }
  } else if (x->size[0] == 0) {
    i = in->size[0] * in->size[1];
    in->size[0] = 1;
    in->size[1] = inVectorLength;
    emxEnsureCapacity_creal32_T(in, i);
    in_data = in->data;
    for (i = 0; i < inVectorLength; i++) {
      in_data[i] = x_data[i];
    }
  } else {
    i = in->size[0] * in->size[1];
    in->size[0] = 1;
    in->size[1] = inVectorLength;
    emxEnsureCapacity_creal32_T(in, i);
    in_data = in->data;
    for (i = 0; i < inVectorLength; i++) {
      in_data[i] = x_data[i];
    }
  }

  i = b_obj->x->size[0] * b_obj->x->size[1];
  b_obj->x->size[0] = 1;
  b_obj->x->size[1] = in->size[1];
  emxEnsureCapacity_creal32_T(b_obj->x, i);
  inVectorLength = in->size[1];
  for (i = 0; i < inVectorLength; i++) {
    b_obj->x->data[i] = in_data[i];
  }

  double b_ps_pre[2];
  emxFree_creal32_T(&in);

  /* Data vector */
  b_obj->l = x->size[0];

  /* Elements in the data */
  b_obj->Fs = Fs;

  /* Sample rate */
  b_obj->t_0 = t_0;

  /* Time stamp of first element */
  b_obj->t_f = t_0 + ((double)x->size[0] - 1.0) / Fs;

  /* Time stamp of last element */
  b_obj->t_nextsegstart[0] = t_0;
  b_obj->t_nextsegstart[1] = t_0;

  /* This is the time when next */
  /* segment should start to */
  /* ensure sufficient overlap. */
  /* Will need to be updated  */
  /* elsewhere.  */
  b_obj->ps_pre = ps_pre;
  b_obj->OLF = 0.5;

  /* Overlap Fraction for STFT */
  b_obj->K = rtNaN;

  /* Unknown number of pulses. */
  /* WFMSTFT Constructs and returns an instance of this class */
  /*  */
  /* An waveform object must be passed to this construction method */
  /* so that the constructor has access to the data vector, desired */
  /* overlap fraction, and priori pulse data, which is used to */
  /* develop the window sizes.  */
  /* INPUTS: */
  /*    waveform_obj   A single waveform object with prior */
  /*                   dependent properties set.  */
  /* OUTPUTS: */
  /*    obj             A wfmstft object */
  /*             %% */
  /*  */
  /* The following are variable sized properties. To tell coder */
  /* that they may vary setup as a local variable size variable */
  /* first, then set. */
  /* Instructions on https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html */
  /* maxFs*maxpulsewidth */
  /* Now actually assign them */
  iobj_1->S->size[0] = 0;
  iobj_1->S->size[1] = 0;
  iobj_1->t->size[0] = 0;
  iobj_1->f->size[0] = 0;
  iobj_1->psd->size[0] = 0;
  iobj_1->wind->size[0] = 0;
  iobj_1->dt = 0.0;
  iobj_1->T = 0.0;
  b_obj->stft = iobj_1;

  /* Unknown values but set types */
  b_obj->W->size[0] = 0;
  b_obj->W->size[1] = 0;
  b_obj->Wf->size[0] = 0;

  /* Copy over ps_ */
  /* COPY Creates an exact copy of the pulse stats object as a separate object */
  b_ps_pre[0] = ps_pre->tmplt[0];
  b_ps_pre[1] = ps_pre->tmplt[1];
  obj_out = b_pulsestats_pulsestats(iobj_0, ps_pre->t_p, ps_pre->t_ip,
    ps_pre->t_ipu, ps_pre->t_ipj, ps_pre->fp, ps_pre->fstart, ps_pre->fend,
    b_ps_pre, ps_pre->mode, ps_pre->pl, ps_pre->clst, ps_pre->cmsk, ps_pre->cpki);

  /* ,... */
  /* obj.thresh); */
  b_obj->ps_pos = obj_out;

  /* Current stats are same as previous during construction */
  /* obj.ps_pos = pulsestats();%TESTING FOR CODER - NEEDS TO BE REVERTED BACK TO LAST LINE */
  /* obj.TimeCorr = TemporalCorrelator(10, 0, 0);%Generate a temporalcorrelator object so coder knows the type of the object */
  c_waveform_setprioridependentpr(b_obj, ps_pre);
  emxCopyStruct_threshold(&b_obj->thresh, &thresh);
  return b_obj;
}

/*
 * PROCESS is a method that runs the pulse detection algorithm on
 * a waveform object.
 *
 * This method is is intended to be run on a waveform
 * segment that is short enought to contain at most K+1 pulses,
 * but at least K pulses, where K is the number of pulses to be
 * summed. Input paramets allow for the selection of search mode,
 * the focus mode, and the selection mode. The search mode
 * ('mode') is eithr 'discovery', 'confirmation', or 'tracking'
 * and selection of each of these affects how priori information
 * is used to reduce the frequency or time scope of the pulse
 * search. This also affects how the resulting ps_pos property of
 * the waveform is set. The false alarm probabilty is used along
 * with the decision table in order to determine the thresholds
 * used for the decision making on pulse detection.
 *
 * Arguments    : waveform *obj
 *                char mode
 *                const emxArray_real_T *excluded_freq_bands
 * Return Type  : void
 */
void waveform_process(waveform *obj, char mode, const emxArray_real_T
                      *excluded_freq_bands)
{
  static const char b_cv[8] = { 'i', 'n', 'f', 'o', 'r', 'm', 'e', 'd' };

  static const char b_cv3[7] = { 'c', 'o', 'n', 'f', 'i', 'r', 'm' };

  static const char b_cv2[6] = { 's', 'e', 'a', 'r', 'c', 'h' };

  static const char b_cv1[5] = { 'n', 'a', 'i', 'v', 'e' };

  static const char cv4[5] = { 't', 'r', 'a', 'c', 'k' };

  b_struct_T val;
  b_struct_T *b_candidatelist_data;
  b_struct_T *candidatelist_data;
  emxArray_boolean_T b_conflog;
  emxArray_boolean_T *conflog;
  emxArray_boolean_T *msk;
  emxArray_boolean_T *r;
  emxArray_real_T *b;
  emxArray_real_T *pk_ind;
  emxArray_real_T *pulseendtimes_withuncert;
  emxArray_real_T *pulsestarttimes_withuncert;
  emxArray_real_T *r1;
  emxArray_real_T *r3;
  emxArray_real_T *r5;
  emxArray_real_T *r7;
  emxArray_real_T *r9;
  emxArray_struct_T c_obj;
  emxArray_struct_T *b_candidatelist;
  emxArray_struct_T *c_candidatelist;
  emxArray_struct_T *candidatelist;
  pulsestats *b_obj;
  double tip;
  double tipj;
  double tipu;
  double tref;
  double x;
  double *b_data;
  double *pulseendtimes_withuncert_data;
  double *pulsestarttimes_withuncert_data;
  double *r10;
  double *r2;
  double *r4;
  double *r6;
  double *r8;
  int freq_search_type_size[2];
  int runmode_size[2];
  int time_search_type_size[2];
  int b_index;
  int d_candidatelist;
  int e_candidatelist;
  int f_candidatelist;
  int i;
  int i1;
  int ip;
  char freq_search_type_data[8];
  char time_search_type_data[8];
  char runmode_data[7];
  bool have_priori_freq_band;
  bool have_priori_time;
  bool *conflog_data;

  /* Mode description: */
  /* Processing can be done in either discovery 'D', confirmation */
  /* 'C', or tracking 'T' modes. The selection of these modes */
  /* affects how time and frequency focusing is used to improve */
  /* processing time. In discovery mode is used for intial */
  /* detection when little is know about where pulses might exist */
  /* in time or frequeny. Confirmation is similar to discovery, but */
  /* is used after an initial detection to confirm that the */
  /* subsequent pulses exists where they should based on  */
  /* forecasting from a previous detection. After pulses are */
  /* confirmed, the mode can be set to tracking which reduces the */
  /* frequency and time search space to improve processing speed.  */
  /*  */
  /*    Discovey mode:      'D' */
  /*        This mode uses no priori information and looks at the  */
  /*        widest possible time bounds for pulses. If there is  */
  /*        no priori frequency information in the ps_pre property  */
  /*        or the focus mode is set to 'open', discovery mode  */
  /*        will search across all frequencies. Otherwise it */
  /*        will search over all frequencies. If it detects pulses */
  /*        in the dataset that exceed the decision threshold, the */
  /*        posterior pulsestats object will be set to a mode of */
  /*        'C' so that the next segment processed will run in */
  /*        confirmation mode. If a detection or set of detections */
  /*        are made, the 'selection_mode' input will dictate how */
  /*        the posterior pulsestat property is set.  */
  /*  */
  /*    Confirmation mode:  'C' */
  /*        This mode is similar to discovery mode, but after a */
  /*        detection is made, it will compare the spectral and */
  /*        temporal location of the detected pulses to determine */
  /*        if the pulses align with what could be predicted from */
  /*        the pulses listed in the priori information of the */
  /*        waveform getting processed. If these pulses are */
  /*        confirmed, then the posteriori pulsestats mode property */
  /*        is set to 'T' so that subsequent segments can move to */
  /*        tracking mode. If pulses are detected but not where */
  /*        they should have been based on predictions from the */
  /*        priori, then the posteriori mode is set back to 'D'. */
  /*  */
  /*    Tracking mode:      'T' */
  /*        Tracking mode uses priori pulsestats information in */
  /*        order to reduce the time and/or frequency space used */
  /*        for detection. The significantly speed processing */
  /*        speeds, but can miss detections if pulses move in time */
  /*        from where they should be based on a previous segment's */
  /*        detection. If using tracking mode and pulses aren't */
  /*        detected (scores don't meet the decision threhold), the */
  /*        posteriori pulsestats mode is set back to 'D'. */
  /*  */
  /* INPUTS: */
  /*    mode    The search mode used. Must be string 'D' for */
  /*            discovery, 'C' for confirmation, or 'T' for */
  /*            tracking.  */
  /*    focus_mode  How the algorithm decided whether or not to */
  /*            focus on a particular pulse. This mode can be set */
  /*            to 'open' wherein no focusing is done and the */
  /*            processing always proceeds along in discovery mode */
  /*            without narrowing the frequency or time span of the */
  /*            search. If this mode is set to 'focus', the method */
  /*            will allow for down selection of detected pulses */
  /*            for subsequent processing. The method of this */
  /*            downselection is determined by the 'selection_mode' */
  /*            input.  */
  /*    selection_mode  How the algorithm narrows the scope for */
  /*            subsequent segment processing. This input is */
  /*            used when in 'discovery' mode. If pulses are */
  /*            detected, the focus mode will dictate which */
  /*            pulse is focused on for subsequent data */
  /*            segments. Focus mode can be set to 'most' to */
  /*            focus on the most powerful detecte pulse or */
  /*            'least' to focus on the least powerful detected */
  /*            pulse. See DETECT.M for more */
  /*            information on these focus modes.  */
  /*    zetas   A vector of fractions of the DFT frequency bin */
  /*            width for which to compute and include in the */
  /*            spectral weighting matrix output. If no interbin */
  /*            shifting is desired, enter 0. Range of inputs */
  /*            [0,1). See WEIGHTINGMATRIX.m for more information */
  /*            on this vector. */
  /*    PF      A numeric probability of false alarm for decision */
  /*            threshold determination. Value range of PF must be */
  /*            within the pf property vector of the decision_table */
  /*            input.  */
  /*    decision_table  A structure with two properties - 'pf' and */
  /*            'values'. The pf property is a vector of false alarm */
  /*            probabilities in decimal form (not percentage). The */
  /*            values property is vector of the same size as pf */
  /*            with the decision thresholds for the corresponding */
  /*            false alarm probability.  */
  /*    excluded_freq_bands   nx2    matrix of bands of */
  /*                                 frequencies to exclude in */
  /*                                 the search. This is useful if */
  /*                                 there has already been a tag */
  /*                                 found and you want to exclude */
  /*                                 that band when looking for */
  /*                                 other frequencies. The lower */
  /*                                 frequecie of the band should */
  /*                                 be in the first column and */
  /*                                 the upper should be in the */
  /*                                 second. This is only used in */
  /*                                 the naive frequency search */
  /*                                 mode. Leave empty [] if no */
  /*                                 exclusion zones are */
  /*                                 necessary. */
  /*  */
  /* OUTPUTS: */
  /*    None. This method updates the ps_pos property of the */
  /*    waveform object 'obj'. */
  /*  */
  /*             %% */
  /*  */
  /*         %% CHECK MODE ENTRANCE REQUIREMENTS */
  /* Determine if there is sufficient priori for the operation of each */
  /* mode. Check to see if they have entries and if they are finite (not Nan or Inf). */
  /* We just catch that and then set the have_priori flag to false.  */
  x = obj->ps_pre->fstart;
  tref = obj->ps_pre->fend;
  have_priori_freq_band = ((!rtIsInf(x)) && (!rtIsNaN(x)) && ((!rtIsInf(tref)) &&
    (!rtIsNaN(tref))));
  x = obj->ps_pre->pl->data[obj->ps_pre->pl->size[1] - 1].t_0;
  tref = obj->ps_pre->t_p;
  tip = obj->ps_pre->t_ip;
  tipu = obj->ps_pre->t_ipu;
  tipj = obj->ps_pre->t_ipj;
  have_priori_time = ((!rtIsInf(x)) && (!rtIsNaN(x)) && ((!rtIsInf(tref)) &&
    (!rtIsNaN(tref))) && ((!rtIsInf(tip)) && (!rtIsNaN(tip))) && ((!rtIsInf(tipu))
    && (!rtIsNaN(tipu))) && ((!rtIsInf(tipj)) && (!rtIsNaN(tipj))));

  /* Enforce entry requirements on the modes so we don't get errors in */
  /* the 'C' and 'T' modes, as they required priori freq and time info. */
  if ((mode == 'T') && (!have_priori_time) && (!have_priori_freq_band)) {
    /* if strcmp(mode,'C'); attemptedmodestring = 'confirmation';end */
    mode = 'D';
  }

  if ((mode == 'C') && (!have_priori_time)) {
    mode = 'D';
  }

  if ((mode == 'I') && (!have_priori_freq_band)) {
    mode = 'D';
  }

  if (mode == 'D') {
    b_index = 0;
  } else if (mode == 'I') {
    b_index = 1;
  } else if (mode == 'C') {
    b_index = 2;
  } else if (mode == 'T') {
    b_index = 3;
  } else {
    b_index = -1;
  }

  switch (b_index) {
   case 0:
    {
      freq_search_type_size[0] = 1;
      freq_search_type_size[1] = 5;
      time_search_type_size[0] = 1;
      time_search_type_size[1] = 5;
      for (i = 0; i < 5; i++) {
        char c;
        c = b_cv1[i];
        freq_search_type_data[i] = c;
        time_search_type_data[i] = c;
      }

      runmode_size[0] = 1;
      runmode_size[1] = 6;
      for (i = 0; i < 6; i++) {
        runmode_data[i] = b_cv2[i];
      }
    }
    break;

   case 1:
    freq_search_type_size[0] = 1;
    freq_search_type_size[1] = 8;
    for (i = 0; i < 8; i++) {
      freq_search_type_data[i] = b_cv[i];
    }

    time_search_type_size[0] = 1;
    time_search_type_size[1] = 5;
    for (i = 0; i < 5; i++) {
      time_search_type_data[i] = b_cv1[i];
    }

    runmode_size[0] = 1;
    runmode_size[1] = 6;
    for (i = 0; i < 6; i++) {
      runmode_data[i] = b_cv2[i];
    }
    break;

   case 2:
    {
      freq_search_type_size[0] = 1;
      freq_search_type_size[1] = 5;
      time_search_type_size[0] = 1;
      time_search_type_size[1] = 5;
      for (i = 0; i < 5; i++) {
        char c;
        c = b_cv1[i];
        freq_search_type_data[i] = c;
        time_search_type_data[i] = c;
      }

      runmode_size[0] = 1;
      runmode_size[1] = 7;
      for (i = 0; i < 7; i++) {
        runmode_data[i] = b_cv3[i];
      }
    }
    break;

   case 3:
    {
      freq_search_type_size[0] = 1;
      freq_search_type_size[1] = 8;
      time_search_type_size[0] = 1;
      time_search_type_size[1] = 8;
      for (i = 0; i < 8; i++) {
        char c;
        c = b_cv[i];
        freq_search_type_data[i] = c;
        time_search_type_data[i] = c;
      }

      runmode_size[0] = 1;
      runmode_size[1] = 5;
      for (i = 0; i < 5; i++) {
        runmode_data[i] = cv4[i];
      }
    }
    break;

   default:
    {
      freq_search_type_size[0] = 1;
      freq_search_type_size[1] = 5;
      time_search_type_size[0] = 1;
      time_search_type_size[1] = 5;
      for (i = 0; i < 5; i++) {
        char c;
        c = b_cv1[i];
        freq_search_type_data[i] = c;
        time_search_type_data[i] = c;
      }

      runmode_size[0] = 1;
      runmode_size[1] = 6;
      for (i = 0; i < 6; i++) {
        runmode_data[i] = b_cv2[i];
      }
    }
    break;
  }

  if (p_strcmp(runmode_data, runmode_size)) {
    b_index = 0;
  } else if (q_strcmp(runmode_data, runmode_size)) {
    b_index = 1;
  } else if (r_strcmp(runmode_data, runmode_size)) {
    b_index = 2;
  } else {
    b_index = -1;
  }

  emxInit_struct_T(&candidatelist);
  emxInit_boolean_T(&msk, 2);
  emxInit_real_T(&pk_ind, 1);
  emxInitStruct_struct_T(&val);
  emxInit_boolean_T(&r, 1);
  emxInit_struct_T(&b_candidatelist);
  emxInit_struct_T(&c_candidatelist);
  switch (b_index) {
   case 0:
    /*             %% SEARCH RUN MODE */
    /* Find all the potential pulses in the dataset */
    waveform_findpulse(obj, time_search_type_data, time_search_type_size,
                       freq_search_type_data, freq_search_type_size,
                       excluded_freq_bands, candidatelist, msk, pk_ind);
    pulseendtimes_withuncert_data = pk_ind->data;
    candidatelist_data = candidatelist->data;
    i = r->size[0];
    r->size[0] = pk_ind->size[0];
    emxEnsureCapacity_boolean_T(r, i);
    conflog_data = r->data;
    b_index = pk_ind->size[0];
    for (i = 0; i < b_index; i++) {
      conflog_data[i] = rtIsNaN(pulseendtimes_withuncert_data[i]);
    }

    b_index = r->size[0];
    for (i = 0; i < b_index; i++) {
      conflog_data[i] = !conflog_data[i];
    }

    if (ifWhileCond(r)) {
      /* Set the pulselist property in the ps_pos based on the */
      /* downselection of pulses */
      b_obj = obj->ps_pos;
      i = b_candidatelist->size[0] * b_candidatelist->size[1];
      b_candidatelist->size[0] = 1;
      b_candidatelist->size[1] = candidatelist->size[1];
      emxEnsureCapacity_struct_T(b_candidatelist, i);
      b_candidatelist_data = b_candidatelist->data;
      b_index = candidatelist->size[1];
      for (i = 0; i < b_index; i++) {
        emxCopyStruct_struct_T(&b_candidatelist_data[i], &candidatelist_data
          [((int)pulseendtimes_withuncert_data[0] + candidatelist->size[0] * i)
          - 1]);
      }

      b_validator_check_size(b_candidatelist, b_obj->pl);
    } else {
      /* If nothing above threshold was found, fill with empty  */
      /* pulse object */
      b_obj = obj->ps_pos;
      makepulsestruc(&val.A, &val.P, &val.SNR, &val.yw, &val.t_0, &val.t_f,
                     val.t_next, &val.fp, &val.fstart, &val.fend, val.mode,
                     &val.det_dec, &val.con_dec);
      i = b_obj->pl->size[0] * b_obj->pl->size[1];
      b_obj->pl->size[0] = 1;
      b_obj->pl->size[1] = 1;
      emxEnsureCapacity_struct_T(b_obj->pl, i);
      emxCopyStruct_struct_T(&b_obj->pl->data[0], &val);
    }

    /* Record all candidates for posterity */
    b_obj = obj->ps_pos;
    c_validator_check_size(candidatelist);
    candidatelist_data = candidatelist->data;
    i = b_obj->clst->size[0] * b_obj->clst->size[1];
    b_obj->clst->size[0] = candidatelist->size[0];
    b_obj->clst->size[1] = candidatelist->size[1];
    emxEnsureCapacity_struct_T(b_obj->clst, i);
    b_index = candidatelist->size[0] * candidatelist->size[1];
    for (i = 0; i < b_index; i++) {
      emxCopyStruct_struct_T(&b_obj->clst->data[i], &candidatelist_data[i]);
    }

    b_obj = obj->ps_pos;
    d_validator_check_size(msk);
    conflog_data = msk->data;
    i = b_obj->cmsk->size[0] * b_obj->cmsk->size[1];
    b_obj->cmsk->size[0] = msk->size[0];
    b_obj->cmsk->size[1] = msk->size[1];
    emxEnsureCapacity_boolean_T(b_obj->cmsk, i);
    b_index = msk->size[0] * msk->size[1];
    for (i = 0; i < b_index; i++) {
      b_obj->cmsk->data[i] = conflog_data[i];
    }

    b_obj = obj->ps_pos;
    e_validator_check_size(pk_ind);
    pulseendtimes_withuncert_data = pk_ind->data;
    i = b_obj->cpki->size[0] * b_obj->cpki->size[1];
    b_obj->cpki->size[0] = pk_ind->size[0];
    b_obj->cpki->size[1] = 1;
    emxEnsureCapacity_real_T(b_obj->cpki, i);
    b_index = pk_ind->size[0];
    for (i = 0; i < b_index; i++) {
      b_obj->cpki->data[i] = pulseendtimes_withuncert_data[i];
    }

    /*  Detection? */
    if (ifWhileCond(r)) {
      /* Dection was made */
      /* True -> */
      /* Update confirmation property for each pulse. False  */
      /* recorded for confirmation property since we are  */
      /* currently in discovery mode and can't confirm anything */
      /* yet.  */
      i = obj->ps_pos->pl->size[1] - 1;
      for (ip = 0; ip <= i; ip++) {
        i1 = b_candidatelist->size[0] * b_candidatelist->size[1];
        b_candidatelist->size[0] = 1;
        b_candidatelist->size[1] = obj->ps_pos->pl->size[1];
        emxEnsureCapacity_struct_T(b_candidatelist, i1);
        b_candidatelist_data = b_candidatelist->data;
        b_index = obj->ps_pos->pl->size[1];
        for (i1 = 0; i1 < b_index; i1++) {
          emxCopyStruct_struct_T(&b_candidatelist_data[i1], &obj->ps_pos->
            pl->data[i1]);
        }

        b_candidatelist_data[ip].con_dec = false;
        b_obj = obj->ps_pos;
        i1 = c_candidatelist->size[0] * c_candidatelist->size[1];
        c_candidatelist->size[0] = 1;
        c_candidatelist->size[1] = b_candidatelist->size[1];
        emxEnsureCapacity_struct_T(c_candidatelist, i1);
        candidatelist_data = c_candidatelist->data;
        b_index = b_candidatelist->size[0] * b_candidatelist->size[1] - 1;
        for (i1 = 0; i1 <= b_index; i1++) {
          emxCopyStruct_struct_T(&candidatelist_data[i1],
            &b_candidatelist_data[i1]);
        }

        b_validator_check_size(c_candidatelist, b_candidatelist);
        b_candidatelist_data = b_candidatelist->data;
        i1 = b_obj->pl->size[0] * b_obj->pl->size[1];
        b_obj->pl->size[0] = 1;
        b_obj->pl->size[1] = b_candidatelist->size[1];
        emxEnsureCapacity_struct_T(b_obj->pl, i1);
        b_index = b_candidatelist->size[1];
        for (i1 = 0; i1 < b_index; i1++) {
          emxCopyStruct_struct_T(&b_obj->pl->data[i1], &b_candidatelist_data[i1]);
        }
      }

      /*                      %Only update posteriori if we are focusing. If in open */
      /*                      %mode, we don't evolve the understanding of pulse */
      /*                      %timing in the priori.  */
      /*                      if strcmp(focus_mode,'focus') */
      /*                      %Calculate & set post. stats (reduced uncertainty) */
      /*                      %obj.update_posteriori(obj.ps_pos.pl) */
      /*                      obj.ps_pos.updateposteriori(obj.ps_pre,obj.ps_pos.pl) */
      /*                      end */
      /*    Update Mode Recommendation -> Confirmation */
      b_obj = obj->ps_pos;
      b_obj->mode = 'C';
    } else {
      /* Dection was not made */
      /* False -> */
      /* Just update the mode recommendation to 'S' (search)  */
      /* so we keep an open search */
      b_obj = obj->ps_pos;
      b_obj->mode = 'S';

      /* 'D'; */
      /* obj.ps_pos.updateposteriori(obj.ps_pre,[]);%No pulses to update the posteriori */
    }

    /* Set the mode in the pulse and candidate listing for  */
    /* records. This records the mode that was used in the  */
    /* detection of the record pulses. This is useful for  */
    /* debugging.  */
    i = obj->ps_pos->pl->size[1] - 1;
    for (ip = 0; ip <= i; ip++) {
      i1 = b_candidatelist->size[0] * b_candidatelist->size[1];
      b_candidatelist->size[0] = 1;
      b_candidatelist->size[1] = obj->ps_pos->pl->size[1];
      emxEnsureCapacity_struct_T(b_candidatelist, i1);
      b_candidatelist_data = b_candidatelist->data;
      b_index = obj->ps_pos->pl->size[1];
      for (i1 = 0; i1 < b_index; i1++) {
        emxCopyStruct_struct_T(&b_candidatelist_data[i1], &obj->ps_pos->pl->
          data[i1]);
      }

      i1 = b_candidatelist_data[ip].mode->size[0] * b_candidatelist_data[ip].
        mode->size[1];
      b_candidatelist_data[ip].mode->size[0] = 1;
      b_candidatelist_data[ip].mode->size[1] = 1;
      emxEnsureCapacity_char_T(b_candidatelist_data[ip].mode, i1);
      b_candidatelist_data[ip].mode->data[0] = mode;
      b_obj = obj->ps_pos;
      i1 = c_candidatelist->size[0] * c_candidatelist->size[1];
      c_candidatelist->size[0] = 1;
      c_candidatelist->size[1] = b_candidatelist->size[1];
      emxEnsureCapacity_struct_T(c_candidatelist, i1);
      candidatelist_data = c_candidatelist->data;
      b_index = b_candidatelist->size[0] * b_candidatelist->size[1] - 1;
      for (i1 = 0; i1 <= b_index; i1++) {
        emxCopyStruct_struct_T(&candidatelist_data[i1], &b_candidatelist_data[i1]);
      }

      b_validator_check_size(c_candidatelist, b_candidatelist);
      b_candidatelist_data = b_candidatelist->data;
      i1 = b_obj->pl->size[0] * b_obj->pl->size[1];
      b_obj->pl->size[0] = 1;
      b_obj->pl->size[1] = b_candidatelist->size[1];
      emxEnsureCapacity_struct_T(b_obj->pl, i1);
      b_index = b_candidatelist->size[1];
      for (i1 = 0; i1 < b_index; i1++) {
        emxCopyStruct_struct_T(&b_obj->pl->data[i1], &b_candidatelist_data[i1]);
      }

      /* 'D'; */
    }

    i = obj->ps_pos->clst->size[0] * obj->ps_pos->clst->size[1] - 1;
    for (ip = 0; ip <= i; ip++) {
      i1 = candidatelist->size[0] * candidatelist->size[1];
      candidatelist->size[0] = obj->ps_pos->clst->size[0];
      candidatelist->size[1] = obj->ps_pos->clst->size[1];
      emxEnsureCapacity_struct_T(candidatelist, i1);
      candidatelist_data = candidatelist->data;
      b_index = obj->ps_pos->clst->size[0] * obj->ps_pos->clst->size[1];
      for (i1 = 0; i1 < b_index; i1++) {
        emxCopyStruct_struct_T(&candidatelist_data[i1], &obj->ps_pos->clst->
          data[i1]);
      }

      i1 = candidatelist_data[ip].mode->size[0] * candidatelist_data[ip]
        .mode->size[1];
      candidatelist_data[ip].mode->size[0] = 1;
      candidatelist_data[ip].mode->size[1] = 1;
      emxEnsureCapacity_char_T(candidatelist_data[ip].mode, i1);
      candidatelist_data[ip].mode->data[0] = mode;
      b_obj = obj->ps_pos;
      c_validator_check_size(candidatelist);
      candidatelist_data = candidatelist->data;
      i1 = b_obj->clst->size[0] * b_obj->clst->size[1];
      b_obj->clst->size[0] = candidatelist->size[0];
      b_obj->clst->size[1] = candidatelist->size[1];
      emxEnsureCapacity_struct_T(b_obj->clst, i1);
      b_index = candidatelist->size[0] * candidatelist->size[1];
      for (i1 = 0; i1 < b_index; i1++) {
        emxCopyStruct_struct_T(&b_obj->clst->data[i1], &candidatelist_data[i1]);
      }

      /*  'D'; */
    }

    /*             %% CONFIRMATION MODE */
    break;

   case 1:
    {
      /* Find all the potential pulses in the dataset */
      waveform_findpulse(obj, time_search_type_data, time_search_type_size,
                         freq_search_type_data, freq_search_type_size,
                         excluded_freq_bands, candidatelist, msk, pk_ind);
      pulseendtimes_withuncert_data = pk_ind->data;
      candidatelist_data = candidatelist->data;
      i = r->size[0];
      r->size[0] = pk_ind->size[0];
      emxEnsureCapacity_boolean_T(r, i);
      conflog_data = r->data;
      b_index = pk_ind->size[0];
      for (i = 0; i < b_index; i++) {
        conflog_data[i] = rtIsNaN(pulseendtimes_withuncert_data[i]);
      }

      b_index = r->size[0];
      for (i = 0; i < b_index; i++) {
        conflog_data[i] = !conflog_data[i];
      }

      if (ifWhileCond(r)) {
        /* Record the detection pulses */
        /* We only use the highest power pulse group for now */
        /* because if we are in confirmation mode, we only allow */
        /* for the selection mode to be 'most' */
        b_obj = obj->ps_pos;
        i = b_candidatelist->size[0] * b_candidatelist->size[1];
        b_candidatelist->size[0] = 1;
        b_candidatelist->size[1] = candidatelist->size[1];
        emxEnsureCapacity_struct_T(b_candidatelist, i);
        b_candidatelist_data = b_candidatelist->data;
        b_index = candidatelist->size[1];
        for (i = 0; i < b_index; i++) {
          emxCopyStruct_struct_T(&b_candidatelist_data[i], &candidatelist_data
            [((int)pulseendtimes_withuncert_data[0] + candidatelist->size[0] * i)
            - 1]);
        }

        b_validator_check_size(b_candidatelist, b_obj->pl);
      } else {
        /* If nothing above threshold was found, fill with empty  */
        /* pulse object */
        b_obj = obj->ps_pos;
        makepulsestruc(&val.A, &val.P, &val.SNR, &val.yw, &val.t_0, &val.t_f,
                       val.t_next, &val.fp, &val.fstart, &val.fend, val.mode,
                       &val.det_dec, &val.con_dec);
        i = b_obj->pl->size[0] * b_obj->pl->size[1];
        b_obj->pl->size[0] = 1;
        b_obj->pl->size[1] = 1;
        emxEnsureCapacity_struct_T(b_obj->pl, i);
        emxCopyStruct_struct_T(&b_obj->pl->data[0], &val);
      }

      /* Record all candidates for posterity */
      b_obj = obj->ps_pos;
      c_validator_check_size(candidatelist);
      candidatelist_data = candidatelist->data;
      i = b_obj->clst->size[0] * b_obj->clst->size[1];
      b_obj->clst->size[0] = candidatelist->size[0];
      b_obj->clst->size[1] = candidatelist->size[1];
      emxEnsureCapacity_struct_T(b_obj->clst, i);
      b_index = candidatelist->size[0] * candidatelist->size[1];
      for (i = 0; i < b_index; i++) {
        emxCopyStruct_struct_T(&b_obj->clst->data[i], &candidatelist_data[i]);
      }

      b_obj = obj->ps_pos;
      d_validator_check_size(msk);
      conflog_data = msk->data;
      i = b_obj->cmsk->size[0] * b_obj->cmsk->size[1];
      b_obj->cmsk->size[0] = msk->size[0];
      b_obj->cmsk->size[1] = msk->size[1];
      emxEnsureCapacity_boolean_T(b_obj->cmsk, i);
      b_index = msk->size[0] * msk->size[1];
      for (i = 0; i < b_index; i++) {
        b_obj->cmsk->data[i] = conflog_data[i];
      }

      b_obj = obj->ps_pos;
      e_validator_check_size(pk_ind);
      pulseendtimes_withuncert_data = pk_ind->data;
      i = b_obj->cpki->size[0] * b_obj->cpki->size[1];
      b_obj->cpki->size[0] = pk_ind->size[0];
      b_obj->cpki->size[1] = 1;
      emxEnsureCapacity_real_T(b_obj->cpki, i);
      b_index = pk_ind->size[0];
      for (i = 0; i < b_index; i++) {
        b_obj->cpki->data[i] = pulseendtimes_withuncert_data[i];
      }

      emxInit_boolean_T(&conflog, 2);
      i = conflog->size[0] * conflog->size[1];
      conflog->size[0] = 1;
      conflog->size[1] = 1;
      emxEnsureCapacity_boolean_T(conflog, i);
      conflog_data = conflog->data;
      conflog_data[0] = false;

      /* Set to all false. Needed */
      /*  Detection? */
      if (ifWhileCond(r)) {
        int i2;
        int i3;

        /* ~isempty(pulselist)%obj.decide(pulselist,PF,decision_table) %Decision on IDed pulses */
        /* True -> */
        tref = obj->ps_pre->pl->data[obj->ps_pre->pl->size[1] - 1].t_0;
        tip = obj->ps_pre->t_ip;
        tipu = obj->ps_pre->t_ipu;
        tipj = obj->ps_pre->t_ipj;
        emxInit_real_T(&pulsestarttimes_withuncert, 2);
        emxInit_real_T(&pulseendtimes_withuncert, 2);
        pulseendtimes_withuncert_data = pulseendtimes_withuncert->data;
        emxInit_real_T(&b, 2);
        if (tref > obj->t_0) {
          /* First pulse in this segment exists in last segment as well because of overlap */
          x = obj->K - 1.0;
          if (rtIsNaN(x)) {
            i = pulseendtimes_withuncert->size[0] *
              pulseendtimes_withuncert->size[1];
            pulseendtimes_withuncert->size[0] = 1;
            pulseendtimes_withuncert->size[1] = 1;
            emxEnsureCapacity_real_T(pulseendtimes_withuncert, i);
            pulseendtimes_withuncert_data = pulseendtimes_withuncert->data;
            pulseendtimes_withuncert_data[0] = rtNaN;
          } else if (x < 0.0) {
            pulseendtimes_withuncert->size[0] = 1;
            pulseendtimes_withuncert->size[1] = 0;
          } else {
            i = pulseendtimes_withuncert->size[0] *
              pulseendtimes_withuncert->size[1];
            pulseendtimes_withuncert->size[0] = 1;
            pulseendtimes_withuncert->size[1] = (int)x + 1;
            emxEnsureCapacity_real_T(pulseendtimes_withuncert, i);
            pulseendtimes_withuncert_data = pulseendtimes_withuncert->data;
            b_index = (int)x;
            for (i = 0; i <= b_index; i++) {
              pulseendtimes_withuncert_data[i] = i;
            }
          }

          x = tip - tipu;
          i = pulsestarttimes_withuncert->size[0] *
            pulsestarttimes_withuncert->size[1];
          pulsestarttimes_withuncert->size[0] = 1;
          pulsestarttimes_withuncert->size[1] = (int)obj->K;
          emxEnsureCapacity_real_T(pulsestarttimes_withuncert, i);
          pulsestarttimes_withuncert_data = pulsestarttimes_withuncert->data;
          b_index = (int)obj->K;
          for (i = 0; i < b_index; i++) {
            pulsestarttimes_withuncert_data[i] = 1.0;
          }

          if (pulseendtimes_withuncert->size[1] ==
              pulsestarttimes_withuncert->size[1]) {
            b_index = pulseendtimes_withuncert->size[1] - 1;
            i = pulsestarttimes_withuncert->size[0] *
              pulsestarttimes_withuncert->size[1];
            pulsestarttimes_withuncert->size[0] = 1;
            pulsestarttimes_withuncert->size[1] = pulseendtimes_withuncert->
              size[1];
            emxEnsureCapacity_real_T(pulsestarttimes_withuncert, i);
            pulsestarttimes_withuncert_data = pulsestarttimes_withuncert->data;
            for (i = 0; i <= b_index; i++) {
              pulsestarttimes_withuncert_data[i] = (tref + x *
                pulseendtimes_withuncert_data[i]) - tipj *
                pulsestarttimes_withuncert_data[i];
            }
          } else {
            g_binary_expand_op(pulsestarttimes_withuncert, tref, x,
                               pulseendtimes_withuncert, tipj);
            pulsestarttimes_withuncert_data = pulsestarttimes_withuncert->data;
          }

          x = tip + tipu;
          i = b->size[0] * b->size[1];
          b->size[0] = 1;
          b->size[1] = (int)obj->K;
          emxEnsureCapacity_real_T(b, i);
          b_data = b->data;
          b_index = (int)obj->K;
          for (i = 0; i < b_index; i++) {
            b_data[i] = 1.0;
          }

          if (pulseendtimes_withuncert->size[1] == b->size[1]) {
            b_index = pulseendtimes_withuncert->size[1] - 1;
            i = pulseendtimes_withuncert->size[0] *
              pulseendtimes_withuncert->size[1];
            pulseendtimes_withuncert->size[0] = 1;
            emxEnsureCapacity_real_T(pulseendtimes_withuncert, i);
            pulseendtimes_withuncert_data = pulseendtimes_withuncert->data;
            for (i = 0; i <= b_index; i++) {
              pulseendtimes_withuncert_data[i] = (tref + x *
                pulseendtimes_withuncert_data[i]) + tipj;
            }
          } else {
            f_binary_expand_op(pulseendtimes_withuncert, tref, x, tipj, b);
            pulseendtimes_withuncert_data = pulseendtimes_withuncert->data;
          }
        } else {
          /* First pulse in this segment does not exists in last segment as well because of overlap */
          x = obj->K;
          if (rtIsNaN(x)) {
            i = pulseendtimes_withuncert->size[0] *
              pulseendtimes_withuncert->size[1];
            pulseendtimes_withuncert->size[0] = 1;
            pulseendtimes_withuncert->size[1] = 1;
            emxEnsureCapacity_real_T(pulseendtimes_withuncert, i);
            pulseendtimes_withuncert_data = pulseendtimes_withuncert->data;
            pulseendtimes_withuncert_data[0] = rtNaN;
          } else if (x < 1.0) {
            pulseendtimes_withuncert->size[0] = 1;
            pulseendtimes_withuncert->size[1] = 0;
          } else {
            i = pulseendtimes_withuncert->size[0] *
              pulseendtimes_withuncert->size[1];
            pulseendtimes_withuncert->size[0] = 1;
            pulseendtimes_withuncert->size[1] = (int)(x - 1.0) + 1;
            emxEnsureCapacity_real_T(pulseendtimes_withuncert, i);
            pulseendtimes_withuncert_data = pulseendtimes_withuncert->data;
            b_index = (int)(x - 1.0);
            for (i = 0; i <= b_index; i++) {
              pulseendtimes_withuncert_data[i] = (double)i + 1.0;
            }
          }

          x = tip - tipu;
          i = pulsestarttimes_withuncert->size[0] *
            pulsestarttimes_withuncert->size[1];
          pulsestarttimes_withuncert->size[0] = 1;
          pulsestarttimes_withuncert->size[1] = (int)obj->K;
          emxEnsureCapacity_real_T(pulsestarttimes_withuncert, i);
          pulsestarttimes_withuncert_data = pulsestarttimes_withuncert->data;
          b_index = (int)obj->K;
          for (i = 0; i < b_index; i++) {
            pulsestarttimes_withuncert_data[i] = 1.0;
          }

          if (pulseendtimes_withuncert->size[1] ==
              pulsestarttimes_withuncert->size[1]) {
            b_index = pulseendtimes_withuncert->size[1] - 1;
            i = pulsestarttimes_withuncert->size[0] *
              pulsestarttimes_withuncert->size[1];
            pulsestarttimes_withuncert->size[0] = 1;
            pulsestarttimes_withuncert->size[1] = pulseendtimes_withuncert->
              size[1];
            emxEnsureCapacity_real_T(pulsestarttimes_withuncert, i);
            pulsestarttimes_withuncert_data = pulsestarttimes_withuncert->data;
            for (i = 0; i <= b_index; i++) {
              pulsestarttimes_withuncert_data[i] = (tref + x *
                pulseendtimes_withuncert_data[i]) - tipj *
                pulsestarttimes_withuncert_data[i];
            }
          } else {
            g_binary_expand_op(pulsestarttimes_withuncert, tref, x,
                               pulseendtimes_withuncert, tipj);
            pulsestarttimes_withuncert_data = pulsestarttimes_withuncert->data;
          }

          x = tip + tipu;
          i = b->size[0] * b->size[1];
          b->size[0] = 1;
          b->size[1] = (int)obj->K;
          emxEnsureCapacity_real_T(b, i);
          b_data = b->data;
          b_index = (int)obj->K;
          for (i = 0; i < b_index; i++) {
            b_data[i] = 1.0;
          }

          if (pulseendtimes_withuncert->size[1] == b->size[1]) {
            b_index = pulseendtimes_withuncert->size[1] - 1;
            i = pulseendtimes_withuncert->size[0] *
              pulseendtimes_withuncert->size[1];
            pulseendtimes_withuncert->size[0] = 1;
            emxEnsureCapacity_real_T(pulseendtimes_withuncert, i);
            pulseendtimes_withuncert_data = pulseendtimes_withuncert->data;
            for (i = 0; i <= b_index; i++) {
              pulseendtimes_withuncert_data[i] = (tref + x *
                pulseendtimes_withuncert_data[i]) + tipj;
            }
          } else {
            f_binary_expand_op(pulseendtimes_withuncert, tref, x, tipj, b);
            pulseendtimes_withuncert_data = pulseendtimes_withuncert->data;
          }
        }

        /* pulseendtimes_nom          = pulsestarttimes_nom+tp; */
        /* pulsestarttimes_withuncert = pulsestarttimes_nom-tipu-tipj; */
        /* pulseendtimes_withuncert   = pulsestarttimes_nom+tipu+tipj; */
        /* Check if pulses started after expected minimum start times */
        b_index = obj->ps_pos->pl->size[1];
        c_obj = *obj->ps_pos->pl;
        d_candidatelist = b_index;
        c_obj.size = &d_candidatelist;
        c_obj.numDimensions = 1;
        horzcatStructList(&c_obj, b);
        b_data = b->data;

        /* Check if pulses started before expected maximum start times */
        b_index = obj->ps_pos->pl->size[1];
        c_obj = *obj->ps_pos->pl;
        e_candidatelist = b_index;
        c_obj.size = &e_candidatelist;
        c_obj.numDimensions = 1;
        emxInit_real_T(&r1, 2);
        horzcatStructList(&c_obj, r1);
        r2 = r1->data;

        /* Frequency check. Within +/- 100 Hz of previously */
        /* detected pulses? */
        emxInit_real_T(&r3, 2);
        b_horzcatStructList(obj->ps_pos->pl, r3);
        r4 = r3->data;
        emxInit_real_T(&r5, 2);
        b_horzcatStructList(obj->ps_pre->pl, r5);
        r6 = r5->data;
        emxInit_real_T(&r7, 2);
        b_horzcatStructList(obj->ps_pos->pl, r7);
        r8 = r7->data;
        emxInit_real_T(&r9, 2);
        b_horzcatStructList(obj->ps_pre->pl, r9);
        r10 = r9->data;
        if (r1->size[1] == 1) {
          i = pulseendtimes_withuncert->size[1];
        } else {
          i = r1->size[1];
        }

        if (b->size[1] == 1) {
          i1 = pulsestarttimes_withuncert->size[1];
        } else {
          i1 = b->size[1];
        }

        if (r3->size[1] == 1) {
          b_index = r5->size[1];
        } else {
          b_index = r3->size[1];
        }

        if (r7->size[1] == 1) {
          ip = r9->size[1];
        } else {
          ip = r7->size[1];
        }

        if (r1->size[1] == 1) {
          i2 = pulseendtimes_withuncert->size[1];
        } else {
          i2 = r1->size[1];
        }

        if (i2 == 1) {
          if (b->size[1] == 1) {
            i2 = pulsestarttimes_withuncert->size[1];
          } else {
            i2 = b->size[1];
          }
        } else if (r1->size[1] == 1) {
          i2 = pulseendtimes_withuncert->size[1];
        } else {
          i2 = r1->size[1];
        }

        if (r3->size[1] == 1) {
          i3 = r5->size[1];
        } else {
          i3 = r3->size[1];
        }

        if (i3 == 1) {
          if (r7->size[1] == 1) {
            i3 = r9->size[1];
          } else {
            i3 = r7->size[1];
          }
        } else if (r3->size[1] == 1) {
          i3 = r5->size[1];
        } else {
          i3 = r3->size[1];
        }

        if ((r1->size[1] == pulseendtimes_withuncert->size[1]) && (b->size[1] ==
             pulsestarttimes_withuncert->size[1]) && (i == i1) && (r3->size[1] ==
             r5->size[1]) && (r7->size[1] == r9->size[1]) && (b_index == ip) &&
            (i2 == i3)) {
          i = conflog->size[0] * conflog->size[1];
          conflog->size[0] = 1;
          conflog->size[1] = r1->size[1];
          emxEnsureCapacity_boolean_T(conflog, i);
          conflog_data = conflog->data;
          b_index = r1->size[1];
          for (i = 0; i < b_index; i++) {
            conflog_data[i] = ((r2[i] <= pulseendtimes_withuncert_data[i]) &&
                               (b_data[i] >= pulsestarttimes_withuncert_data[i])
                               && ((r4[i] >= r6[i] - 100.0) && (r8[i] <= r10[i]
              + 100.0)));
          }
        } else {
          e_binary_expand_op(conflog, r1, pulseendtimes_withuncert, b,
                             pulsestarttimes_withuncert, r3, r5, r7, r9);
          conflog_data = conflog->data;
        }

        emxFree_real_T(&b);
        emxFree_real_T(&r9);
        emxFree_real_T(&r7);
        emxFree_real_T(&r5);
        emxFree_real_T(&r3);
        emxFree_real_T(&r1);
        emxFree_real_T(&pulseendtimes_withuncert);
        emxFree_real_T(&pulsestarttimes_withuncert);

        /* [minstartlog', maxstartlog', freqInBand', conflog'] */
        b_index = conflog->size[1];
        b_conflog = *conflog;
        f_candidatelist = b_index;
        b_conflog.size = &f_candidatelist;
        b_conflog.numDimensions = 1;
        if (allOrAny_anonFcn1(&b_conflog)) {
          /*  	Confirmed? */
          /*  		True -> Confirmation = True */
          have_priori_freq_band = true;
        } else {
          /*  		False -> Confirmation = False */
          have_priori_freq_band = false;
        }
      } else {
        /* False -> */
        /* Set confirmation = False */
        have_priori_freq_band = false;
      }

      /*  Confirmation? */
      if (have_priori_freq_band) {
        /* True -> */
        /* Update confirmation property for each pulse */
        i = obj->ps_pos->pl->size[1] - 1;
        for (ip = 0; ip <= i; ip++) {
          /* obj.ps_pos.pl(ip).con_dec = true; */
          i1 = b_candidatelist->size[0] * b_candidatelist->size[1];
          b_candidatelist->size[0] = 1;
          b_candidatelist->size[1] = obj->ps_pos->pl->size[1];
          emxEnsureCapacity_struct_T(b_candidatelist, i1);
          b_candidatelist_data = b_candidatelist->data;
          b_index = obj->ps_pos->pl->size[1];
          for (i1 = 0; i1 < b_index; i1++) {
            emxCopyStruct_struct_T(&b_candidatelist_data[i1], &obj->ps_pos->
              pl->data[i1]);
          }

          b_candidatelist_data[ip].con_dec = conflog_data[ip];
          b_obj = obj->ps_pos;
          i1 = c_candidatelist->size[0] * c_candidatelist->size[1];
          c_candidatelist->size[0] = 1;
          c_candidatelist->size[1] = b_candidatelist->size[1];
          emxEnsureCapacity_struct_T(c_candidatelist, i1);
          candidatelist_data = c_candidatelist->data;
          b_index = b_candidatelist->size[0] * b_candidatelist->size[1] - 1;
          for (i1 = 0; i1 <= b_index; i1++) {
            emxCopyStruct_struct_T(&candidatelist_data[i1],
              &b_candidatelist_data[i1]);
          }

          b_validator_check_size(c_candidatelist, b_candidatelist);
          b_candidatelist_data = b_candidatelist->data;
          i1 = b_obj->pl->size[0] * b_obj->pl->size[1];
          b_obj->pl->size[0] = 1;
          b_obj->pl->size[1] = b_candidatelist->size[1];
          emxEnsureCapacity_struct_T(b_obj->pl, i1);
          b_index = b_candidatelist->size[1];
          for (i1 = 0; i1 < b_index; i1++) {
            emxCopyStruct_struct_T(&b_obj->pl->data[i1],
              &b_candidatelist_data[i1]);
          }
        }

        /*                      %Open focus mode will never get to confirmation, so we */
        /*                      %don't need the 'if' statement here checking the focus */
        /*                      %most like in the discovery case above */
        /*                      %   Calculate & set post. stats (reduced uncertainty) */
        /*                      %obj.update_posteriori(obj.ps_pos.pl)%(Note this records pulse list) */
        /*                      obj.ps_pos.updateposteriori(obj.ps_pre,obj.ps_pos.pl) */
        /* Update mode suggestion for next segment processing */
        /*    Mode -> Tracking */
        b_obj = obj->ps_pos;
        b_obj->mode = 'T';
      } else {
        /* False -> */
        /* Update mode suggestion for next segment processing */
        /* 	Mode -> Discovery */
        b_obj = obj->ps_pos;
        b_obj->mode = 'S';

        /* obj.ps_pos.updateposteriori(obj.ps_pre,[]); %No pulses to update the posteriori */
      }

      emxFree_boolean_T(&conflog);

      /* Set the mode in the pulse and candidate listing for  */
      /* records. This records the mode that was used in the  */
      /* detection of the record pulses. This is useful for  */
      /* debugging.  */
      i = obj->ps_pos->pl->size[1] - 1;
      for (ip = 0; ip <= i; ip++) {
        i1 = b_candidatelist->size[0] * b_candidatelist->size[1];
        b_candidatelist->size[0] = 1;
        b_candidatelist->size[1] = obj->ps_pos->pl->size[1];
        emxEnsureCapacity_struct_T(b_candidatelist, i1);
        b_candidatelist_data = b_candidatelist->data;
        b_index = obj->ps_pos->pl->size[1];
        for (i1 = 0; i1 < b_index; i1++) {
          emxCopyStruct_struct_T(&b_candidatelist_data[i1], &obj->ps_pos->
            pl->data[i1]);
        }

        i1 = b_candidatelist_data[ip].mode->size[0] * b_candidatelist_data[ip].
          mode->size[1];
        b_candidatelist_data[ip].mode->size[0] = 1;
        b_candidatelist_data[ip].mode->size[1] = 1;
        emxEnsureCapacity_char_T(b_candidatelist_data[ip].mode, i1);
        b_candidatelist_data[ip].mode->data[0] = mode;
        b_obj = obj->ps_pos;
        i1 = c_candidatelist->size[0] * c_candidatelist->size[1];
        c_candidatelist->size[0] = 1;
        c_candidatelist->size[1] = b_candidatelist->size[1];
        emxEnsureCapacity_struct_T(c_candidatelist, i1);
        candidatelist_data = c_candidatelist->data;
        b_index = b_candidatelist->size[0] * b_candidatelist->size[1] - 1;
        for (i1 = 0; i1 <= b_index; i1++) {
          emxCopyStruct_struct_T(&candidatelist_data[i1],
            &b_candidatelist_data[i1]);
        }

        b_validator_check_size(c_candidatelist, b_candidatelist);
        b_candidatelist_data = b_candidatelist->data;
        i1 = b_obj->pl->size[0] * b_obj->pl->size[1];
        b_obj->pl->size[0] = 1;
        b_obj->pl->size[1] = b_candidatelist->size[1];
        emxEnsureCapacity_struct_T(b_obj->pl, i1);
        b_index = b_candidatelist->size[1];
        for (i1 = 0; i1 < b_index; i1++) {
          emxCopyStruct_struct_T(&b_obj->pl->data[i1], &b_candidatelist_data[i1]);
        }

        /* 'C'; */
      }

      i = obj->ps_pos->clst->size[0] * obj->ps_pos->clst->size[1] - 1;
      for (ip = 0; ip <= i; ip++) {
        i1 = candidatelist->size[0] * candidatelist->size[1];
        candidatelist->size[0] = obj->ps_pos->clst->size[0];
        candidatelist->size[1] = obj->ps_pos->clst->size[1];
        emxEnsureCapacity_struct_T(candidatelist, i1);
        candidatelist_data = candidatelist->data;
        b_index = obj->ps_pos->clst->size[0] * obj->ps_pos->clst->size[1];
        for (i1 = 0; i1 < b_index; i1++) {
          emxCopyStruct_struct_T(&candidatelist_data[i1], &obj->ps_pos->
            clst->data[i1]);
        }

        i1 = candidatelist_data[ip].mode->size[0] * candidatelist_data[ip].
          mode->size[1];
        candidatelist_data[ip].mode->size[0] = 1;
        candidatelist_data[ip].mode->size[1] = 1;
        emxEnsureCapacity_char_T(candidatelist_data[ip].mode, i1);
        candidatelist_data[ip].mode->data[0] = mode;
        b_obj = obj->ps_pos;
        c_validator_check_size(candidatelist);
        candidatelist_data = candidatelist->data;
        i1 = b_obj->clst->size[0] * b_obj->clst->size[1];
        b_obj->clst->size[0] = candidatelist->size[0];
        b_obj->clst->size[1] = candidatelist->size[1];
        emxEnsureCapacity_struct_T(b_obj->clst, i1);
        b_index = candidatelist->size[0] * candidatelist->size[1];
        for (i1 = 0; i1 < b_index; i1++) {
          emxCopyStruct_struct_T(&b_obj->clst->data[i1], &candidatelist_data[i1]);
        }

        /* 'C'; */
      }
    }
    break;

   case 2:
    /*                 %% TRACKING MODE */
    /* Find all the potential pulses in the dataset */
    waveform_findpulse(obj, time_search_type_data, time_search_type_size,
                       freq_search_type_data, freq_search_type_size,
                       excluded_freq_bands, candidatelist, msk, pk_ind);
    pulseendtimes_withuncert_data = pk_ind->data;
    candidatelist_data = candidatelist->data;
    i = r->size[0];
    r->size[0] = pk_ind->size[0];
    emxEnsureCapacity_boolean_T(r, i);
    conflog_data = r->data;
    b_index = pk_ind->size[0];
    for (i = 0; i < b_index; i++) {
      conflog_data[i] = rtIsNaN(pulseendtimes_withuncert_data[i]);
    }

    b_index = r->size[0];
    for (i = 0; i < b_index; i++) {
      conflog_data[i] = !conflog_data[i];
    }

    if (ifWhileCond(r)) {
      /* Record the detection pulses */
      /* We only use the highest power pulse group for now */
      /* because if we are in confirmation mode, we only allow */
      /* for the selection mode to be 'most' */
      b_obj = obj->ps_pos;
      i = b_candidatelist->size[0] * b_candidatelist->size[1];
      b_candidatelist->size[0] = 1;
      b_candidatelist->size[1] = candidatelist->size[1];
      emxEnsureCapacity_struct_T(b_candidatelist, i);
      b_candidatelist_data = b_candidatelist->data;
      b_index = candidatelist->size[1];
      for (i = 0; i < b_index; i++) {
        emxCopyStruct_struct_T(&b_candidatelist_data[i], &candidatelist_data
          [((int)pulseendtimes_withuncert_data[0] + candidatelist->size[0] * i)
          - 1]);
      }

      b_validator_check_size(b_candidatelist, b_obj->pl);
    } else {
      /* Nothing met the threshold for detection */
      b_obj = obj->ps_pos;
      makepulsestruc(&val.A, &val.P, &val.SNR, &val.yw, &val.t_0, &val.t_f,
                     val.t_next, &val.fp, &val.fstart, &val.fend, val.mode,
                     &val.det_dec, &val.con_dec);
      i = b_obj->pl->size[0] * b_obj->pl->size[1];
      b_obj->pl->size[0] = 1;
      b_obj->pl->size[1] = 1;
      emxEnsureCapacity_struct_T(b_obj->pl, i);
      emxCopyStruct_struct_T(&b_obj->pl->data[0], &val);
    }

    b_obj = obj->ps_pos;
    c_validator_check_size(candidatelist);
    candidatelist_data = candidatelist->data;
    i = b_obj->clst->size[0] * b_obj->clst->size[1];
    b_obj->clst->size[0] = candidatelist->size[0];
    b_obj->clst->size[1] = candidatelist->size[1];
    emxEnsureCapacity_struct_T(b_obj->clst, i);
    b_index = candidatelist->size[0] * candidatelist->size[1];
    for (i = 0; i < b_index; i++) {
      emxCopyStruct_struct_T(&b_obj->clst->data[i], &candidatelist_data[i]);
    }

    b_obj = obj->ps_pos;
    d_validator_check_size(msk);
    conflog_data = msk->data;
    i = b_obj->cmsk->size[0] * b_obj->cmsk->size[1];
    b_obj->cmsk->size[0] = msk->size[0];
    b_obj->cmsk->size[1] = msk->size[1];
    emxEnsureCapacity_boolean_T(b_obj->cmsk, i);
    b_index = msk->size[0] * msk->size[1];
    for (i = 0; i < b_index; i++) {
      b_obj->cmsk->data[i] = conflog_data[i];
    }

    b_obj = obj->ps_pos;
    e_validator_check_size(pk_ind);
    pulseendtimes_withuncert_data = pk_ind->data;
    i = b_obj->cpki->size[0] * b_obj->cpki->size[1];
    b_obj->cpki->size[0] = pk_ind->size[0];
    b_obj->cpki->size[1] = 1;
    emxEnsureCapacity_real_T(b_obj->cpki, i);
    b_index = pk_ind->size[0];
    for (i = 0; i < b_index; i++) {
      b_obj->cpki->data[i] = pulseendtimes_withuncert_data[i];
    }

    /*  Detection? */
    if (ifWhileCond(r)) {
      /* ~isempty(pulselist)%obj.decide(pulselist,PF,decision_table) %Decision on IDed pulses */
      /* True -> */
      /* Update confirmation property for each pulse */
      /* If we are in tracking mode, we have narrowed the time and */
      /* frequeny bounds, so if there is a detection then we are */
      /* confirming the previous projections. */
      i = obj->ps_pos->pl->size[1] - 1;
      for (ip = 0; ip <= i; ip++) {
        i1 = b_candidatelist->size[0] * b_candidatelist->size[1];
        b_candidatelist->size[0] = 1;
        b_candidatelist->size[1] = obj->ps_pos->pl->size[1];
        emxEnsureCapacity_struct_T(b_candidatelist, i1);
        b_candidatelist_data = b_candidatelist->data;
        b_index = obj->ps_pos->pl->size[1];
        for (i1 = 0; i1 < b_index; i1++) {
          emxCopyStruct_struct_T(&b_candidatelist_data[i1], &obj->ps_pos->
            pl->data[i1]);
        }

        b_candidatelist_data[ip].con_dec = true;
        b_obj = obj->ps_pos;
        i1 = c_candidatelist->size[0] * c_candidatelist->size[1];
        c_candidatelist->size[0] = 1;
        c_candidatelist->size[1] = b_candidatelist->size[1];
        emxEnsureCapacity_struct_T(c_candidatelist, i1);
        candidatelist_data = c_candidatelist->data;
        b_index = b_candidatelist->size[0] * b_candidatelist->size[1] - 1;
        for (i1 = 0; i1 <= b_index; i1++) {
          emxCopyStruct_struct_T(&candidatelist_data[i1],
            &b_candidatelist_data[i1]);
        }

        b_validator_check_size(c_candidatelist, b_candidatelist);
        b_candidatelist_data = b_candidatelist->data;
        i1 = b_obj->pl->size[0] * b_obj->pl->size[1];
        b_obj->pl->size[0] = 1;
        b_obj->pl->size[1] = b_candidatelist->size[1];
        emxEnsureCapacity_struct_T(b_obj->pl, i1);
        b_index = b_candidatelist->size[1];
        for (i1 = 0; i1 < b_index; i1++) {
          emxCopyStruct_struct_T(&b_obj->pl->data[i1], &b_candidatelist_data[i1]);
        }
      }

      /*                      %Open focus mode will never get to tracking, so we */
      /*                      %don't need the 'if' statement here checking the focuse */
      /*                      %most like in the discovery case above */
      /*                      %   Calculate & set post. Stats (reduced uncertainty) */
      /*                      %obj.update_posteriori(obj.ps_pos.pl) */
      /*                      obj.ps_pos.updateposteriori(obj.ps_pre,obj.ps_pos.pl) */
      /*    Mode -> Tracking */
      /* Update mode suggestion for next segment processing */
      b_obj = obj->ps_pos;
      b_obj->mode = mode;

      /* 'T'; */
    } else {
      /* False -> */
      /* Update confirmation property for each pulse. Don't need to */
      /* do this since there are no pulses to record a confirmation */
      /* decision on. */
      /* Update mode suggestion for next segment processing */
      /*    Mode -> Discovery */
      b_obj = obj->ps_pos;
      b_obj->mode = 'S';

      /* 'D'; */
      /* obj.ps_pos.updateposteriori(obj.ps_pre,[]);%No pulses to update the posteriori */
    }

    /* Set the mode in the pulse and candidate listing for  */
    /* records. This records the mode that was used in the  */
    /* detection of the record pulses. This is useful for  */
    /* debugging.  */
    i = obj->ps_pos->pl->size[1] - 1;
    for (ip = 0; ip <= i; ip++) {
      i1 = b_candidatelist->size[0] * b_candidatelist->size[1];
      b_candidatelist->size[0] = 1;
      b_candidatelist->size[1] = obj->ps_pos->pl->size[1];
      emxEnsureCapacity_struct_T(b_candidatelist, i1);
      b_candidatelist_data = b_candidatelist->data;
      b_index = obj->ps_pos->pl->size[1];
      for (i1 = 0; i1 < b_index; i1++) {
        emxCopyStruct_struct_T(&b_candidatelist_data[i1], &obj->ps_pos->pl->
          data[i1]);
      }

      i1 = b_candidatelist_data[ip].mode->size[0] * b_candidatelist_data[ip].
        mode->size[1];
      b_candidatelist_data[ip].mode->size[0] = 1;
      b_candidatelist_data[ip].mode->size[1] = 1;
      emxEnsureCapacity_char_T(b_candidatelist_data[ip].mode, i1);
      b_candidatelist_data[ip].mode->data[0] = mode;
      b_obj = obj->ps_pos;
      i1 = c_candidatelist->size[0] * c_candidatelist->size[1];
      c_candidatelist->size[0] = 1;
      c_candidatelist->size[1] = b_candidatelist->size[1];
      emxEnsureCapacity_struct_T(c_candidatelist, i1);
      candidatelist_data = c_candidatelist->data;
      b_index = b_candidatelist->size[0] * b_candidatelist->size[1] - 1;
      for (i1 = 0; i1 <= b_index; i1++) {
        emxCopyStruct_struct_T(&candidatelist_data[i1], &b_candidatelist_data[i1]);
      }

      b_validator_check_size(c_candidatelist, b_candidatelist);
      b_candidatelist_data = b_candidatelist->data;
      i1 = b_obj->pl->size[0] * b_obj->pl->size[1];
      b_obj->pl->size[0] = 1;
      b_obj->pl->size[1] = b_candidatelist->size[1];
      emxEnsureCapacity_struct_T(b_obj->pl, i1);
      b_index = b_candidatelist->size[1];
      for (i1 = 0; i1 < b_index; i1++) {
        emxCopyStruct_struct_T(&b_obj->pl->data[i1], &b_candidatelist_data[i1]);
      }

      /*  'T'; */
    }

    i = obj->ps_pos->clst->size[0] * obj->ps_pos->clst->size[1] - 1;
    for (ip = 0; ip <= i; ip++) {
      i1 = candidatelist->size[0] * candidatelist->size[1];
      candidatelist->size[0] = obj->ps_pos->clst->size[0];
      candidatelist->size[1] = obj->ps_pos->clst->size[1];
      emxEnsureCapacity_struct_T(candidatelist, i1);
      candidatelist_data = candidatelist->data;
      b_index = obj->ps_pos->clst->size[0] * obj->ps_pos->clst->size[1];
      for (i1 = 0; i1 < b_index; i1++) {
        emxCopyStruct_struct_T(&candidatelist_data[i1], &obj->ps_pos->clst->
          data[i1]);
      }

      i1 = candidatelist_data[ip].mode->size[0] * candidatelist_data[ip]
        .mode->size[1];
      candidatelist_data[ip].mode->size[0] = 1;
      candidatelist_data[ip].mode->size[1] = 1;
      emxEnsureCapacity_char_T(candidatelist_data[ip].mode, i1);
      candidatelist_data[ip].mode->data[0] = mode;
      b_obj = obj->ps_pos;
      c_validator_check_size(candidatelist);
      candidatelist_data = candidatelist->data;
      i1 = b_obj->clst->size[0] * b_obj->clst->size[1];
      b_obj->clst->size[0] = candidatelist->size[0];
      b_obj->clst->size[1] = candidatelist->size[1];
      emxEnsureCapacity_struct_T(b_obj->clst, i1);
      b_index = candidatelist->size[0] * candidatelist->size[1];
      for (i1 = 0; i1 < b_index; i1++) {
        emxCopyStruct_struct_T(&b_obj->clst->data[i1], &candidatelist_data[i1]);
      }

      /*  'T'; */
    }
    break;

   default:
    /*                 %% SOMETHING BROKE */
    break;
  }

  emxFree_struct_T(&c_candidatelist);
  emxFree_struct_T(&b_candidatelist);
  emxFree_boolean_T(&r);
  emxFreeStruct_struct_T(&val);
  emxFree_real_T(&pk_ind);
  emxFree_boolean_T(&msk);
  emxFree_struct_T(&candidatelist);
}

/*
 * SETWEIGHTINGMATRIX method sets the W and Wf properties of
 * the waveform. These are the weighting matrix and the
 * frequencys (Wf) at which they are computed.
 * INPUTS:
 *    none
 * OUTPUTS:
 *    none other than setting obj.Wf and obj.W
 * ----------------------------------------------------------
 *
 * Here we build the spectral scaling vector. We make it the same
 * size as the FFT length in the STFT operation, so it has the
 * same frequency resolution.
 * How many frequency bins are there?
 *
 * Arguments    : waveform *obj
 * Return Type  : void
 */
void waveform_setweightingmatrix(waveform *obj)
{
  emxArray_boolean_T *b_output_samps;
  emxArray_creal_T *Xs;
  emxArray_creal_T *b_x;
  emxArray_creal_T *buffer;
  emxArray_creal_T *currDFT;
  emxArray_creal_T *r;
  emxArray_creal_T *s;
  emxArray_creal_T *stackedToeplitzMatrices;
  emxArray_creal_T *x;
  emxArray_int32_T *iidx;
  emxArray_real_T *b_r;
  emxArray_real_T *output_samps;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  emxArray_real_T *w_time_domain;
  emxArray_real_T *x_of_n;
  creal_T *Xs_data;
  creal_T *buffer_data;
  creal_T *currDFT_data;
  creal_T *s_data;
  creal_T *x_data;
  double tmplt_samps[2];
  double y[2];
  double Fs;
  double xtmp_im;
  double xtmp_re;
  double *output_samps_data;
  double *w_time_domain_data;
  double *x_of_n_data;
  int b_i;
  int b_loop_ub;
  int i;
  int i1;
  int i3;
  int k;
  int loop_ub;
  int loop_ub_tmp;
  int md2;
  unsigned int nfft;
  int nw;
  int nx;
  int *iidx_data;
  bool useRadix2;
  bool *b_output_samps_data;
  nx = obj->stft->f->size[0];

  /* Build a pulse time domain template with the same number  */
  /* of samples as frequency bins: */
  /* GETTEMPLATE Generates a time domain template of the the signal template in */
  /* the priori pulsestats object in the waveform passed to the function. The */
  /* returned vector is the template at the waveform's sample rate. The */
  /* caller can request a total number of samples greater than the samples */
  /* required to describe the signal. This is useful if the call will be using */
  /* a DFT on the result and wants a specific number of samples to ensure a */
  /* particular frequency resolutions. */
  /*  */
  /* INPUTS: */
  /*    X       A waveform object with a populated ps_pre property */
  /*    samples The number of sample desired in the output. Must be greater */
  /*            than or equal to ceil(X.ps_pre.t_p*X.Fs) */
  /*  */
  /* OUTPUTS: */
  /*    sig_template    A vector of the signal amplitude over the samples */
  /*                    requested at the sample rate of the input waveform. */
  /*  */
  /* Author: Michael W. Shafer */
  /* Date:   2021-05-21 */
  /*  */
  /* Sort out the samples input, if submitted by the caller */
  /* Generates a the template in the time domain at the sample rate of the */
  /* waveform. */
  xtmp_im = obj->Fs * obj->ps_pre->t_p;
  tmplt_samps[1] = ceil(xtmp_im);
  tmplt_samps[0] = 0.0;
  xtmp_im = obj->Fs * obj->ps_pre->t_p;
  xtmp_im = ceil(xtmp_im);
  xtmp_re = obj->ps_pre->t_p * obj->Fs;
  xtmp_re = ceil(xtmp_re);
  emxInit_real_T(&output_samps, 2);
  linspace(xtmp_im, xtmp_re, output_samps);
  y[0] = obj->ps_pre->tmplt[0];
  y[1] = obj->ps_pre->tmplt[1];
  emxInit_real_T(&w_time_domain, 2);
  i = w_time_domain->size[0] * w_time_domain->size[1];
  w_time_domain->size[0] = 1;
  w_time_domain->size[1] = output_samps->size[1];
  emxEnsureCapacity_real_T(w_time_domain, i);
  w_time_domain_data = w_time_domain->data;
  loop_ub = output_samps->size[1];
  for (i = 0; i < loop_ub; i++) {
    w_time_domain_data[i] = rtNaN;
  }

  useRadix2 = (output_samps->size[1] == 0);
  if (!useRadix2) {
    k = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (k < 2) {
        if (rtIsNaN(tmplt_samps[k])) {
          exitg1 = 1;
        } else {
          k++;
        }
      } else {
        if (tmplt_samps[1] < 0.0) {
          tmplt_samps[0] = tmplt_samps[1];
          tmplt_samps[1] = 0.0;
          y[0] = obj->ps_pre->tmplt[1];
          y[1] = obj->ps_pre->tmplt[0];
        }

        interp1Linear(y, output_samps, w_time_domain, tmplt_samps);
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  /* Generate the extra-zeros needed to pad to get to 'samples' samples */
  nx -= output_samps->size[1];
  i = output_samps->size[0] * output_samps->size[1];
  output_samps->size[0] = 1;
  output_samps->size[1] = nx;
  emxEnsureCapacity_real_T(output_samps, i);
  output_samps_data = output_samps->data;
  for (i = 0; i < nx; i++) {
    output_samps_data[i] = 0.0;
  }

  i = w_time_domain->size[1];
  loop_ub = output_samps->size[1];
  i1 = w_time_domain->size[0] * w_time_domain->size[1];
  w_time_domain->size[1] += output_samps->size[1];
  emxEnsureCapacity_real_T(w_time_domain, i1);
  w_time_domain_data = w_time_domain->data;
  for (i1 = 0; i1 < loop_ub; i1++) {
    w_time_domain_data[i + i1] = 0.0;
  }

  /* Build a rectagular waveform in the time domain with the same number of samples as frequency bins */
  /* t = (0:numel(sig_template)-1)/X.Fs; */
  /* A vector of times associated with the output template. */
  /* Useful for plotting in the time domain. */
  /* Build weighting matrix */
  Fs = obj->Fs;

  /* WEIGHTINGMATRIX Builds the spectral weighting matrix for the incoherent */
  /* summationation algorithm. The matrix is based on the DFT coefficients */
  /* developed from the waveform passed to the function. The function first */
  /* developeds a weighting vectors based on an unaltered waveform, but then */
  /* shifts the waveforms spectral content base fractions of the DFT bin width, */
  /* as defined by the zetas input. These shifted waveforms then have their */
  /* DFT's computed. The original and shifted DFT coefficients are then aligned */
  /* in a matrix. In this way, this weighting matrix allows for the dominant */
  /* frequency in the vector it weights to be between bins. This submatrix is */
  /* then row shifted and concantinated a number of times so that the DFT */
  /* coefficients are shifted across all DFT frequency bins. The outputs are  */
  /* the weighting matrix W and a frequency vector Wf that corresponds to the  */
  /* rows of W. The frequencies, and therefore the rows of the W matrix, use a */
  /* centered frequency definitions defined by the STFT.m algorithm.  */
  /*  */
  /*    Example:   [W,Wf] = weightingmatrix(rand(1,10),1,[0 0.5]) */
  /*   */
  /*    INPUTS: */
  /*    x_of_n      nx1     Vector of discrete data sampled as Fs. Can be 1xn. */
  /*    Fs          1x1     Sampling rate in Hz of the dataset */
  /*    zetas       mx1     A vector of fractions of the DFT frequency bin */
  /*                        width for which to compute and include in the */
  /*                        spectral weighting matrix output. If no interbin */
  /*                        shifting is desired, enter 0. Range of inputs */
  /*                        [0,1). */
  /*    frequencyRangeType  String of either 'centered' or 'twosided'. See */
  /*                        stft.m documentation on details of these frequency */
  /*                        bounds. If 'centered' is selected, the zero */
  /*                        frequency point is near the center of the output */
  /*                        matrix. If 'twosided' is selected, the zero */
  /*                        frequency points is in the upper left corner of the */
  /*                        output W matrix.  */
  /*  */
  /*    OUTPUTS: */
  /*    W           nxnm    A matrix of spectral weighting vectors along each */
  /*                        column. The hermitian of this matrix is designed to */
  /*                        be multiplied by a vector of DFT coefficients. The  */
  /*                        weights held in column p can be thought of as the */
  /*                        matched DFT coefficients if the signal were to have */
  /*                        been shifted by the template by Wf(p).  */
  /*    Wf          nmx1    A matrix of the frequency shifts corresponding to */
  /*                        each column of W  */
  /*  */
  /*  The intended use of the W matrix is to multiply it's hermetian by a FFT  */
  /*  vector, or STFT matrix with frequencies in the rows.  */
  /*            */
  /*  */
  /*    [W^h]*S         or          [W^h]*FFT */
  /*  */
  /*  The outputs of this multiplication will have n*m rows. The rows of the */
  /*  result there for are the "scores" of at frequency associated with that */
  /*  row. The row frequencies are dependent on the zetas. Consider an input */
  /*  series that had frequencies [-100 0 100 200]. If the zeta input was  */
  /*  [0 0.5], weightings for full and half frequencies steps would be  */
  /*  developed.  */
  /*  */
  /*        output freq     input freq */
  /*                            -100    0   100     200 */
  /*                -150    [                           ] */
  /*                -100    [                           ] */
  /*                -50     [                           ] */
  /*                0       [            W^h            ] */
  /*                50      [                           ] */
  /*                100     [                           ] */
  /*                150     [                           ] */
  /*                200     [                           ] */
  /*  */
  /*    The first row of the matrix above would contain the weightings for the */
  /*    -100 0 100 and 200 Hz frequencie bins if the FFT (or STFT time window) */
  /*    had a signal at -150 Hz. Similarly, the second row would contain the  */
  /*    weightings for the -100 0 100 and 200 Hz frequencie bins if the FFT  */
  /*    (or STFT time window) had a signal at -100 Hz.  */
  /*  */
  /* Author: Michael Shafer */
  /* Date:   2020-12-19 */
  /*  */
  /*  Change Log */
  /*  2022-01-12    Updated to include twosided frequency range for output and */
  /*                updated the code associated with generating the unsorted W */
  /*                matrix to increase speed. Added use of makestftFreqVector */
  /*                function.  */
  /*  */
  /* Check the inputs */
  /* Reshape to a column vector, as the algorithm expects */
  emxInit_real_T(&x_of_n, 2);
  if (w_time_domain->size[1] != 1) {
    i = x_of_n->size[0] * x_of_n->size[1];
    x_of_n->size[0] = w_time_domain->size[1];
    x_of_n->size[1] = 1;
    emxEnsureCapacity_real_T(x_of_n, i);
    x_of_n_data = x_of_n->data;
    loop_ub = w_time_domain->size[1];
    for (i = 0; i < loop_ub; i++) {
      x_of_n_data[i] = w_time_domain_data[i];
    }
  } else {
    i = x_of_n->size[0] * x_of_n->size[1];
    x_of_n->size[0] = 1;
    x_of_n->size[1] = 1;
    emxEnsureCapacity_real_T(x_of_n, i);
    x_of_n_data = x_of_n->data;
    x_of_n_data[0] = w_time_domain_data[0];
  }

  nw = x_of_n->size[0];

  /* F_bin_width = Fs/nw; */
  if (x_of_n->size[0] - 1 < 0) {
    output_samps->size[0] = 1;
    output_samps->size[1] = 0;
  } else {
    i = output_samps->size[0] * output_samps->size[1];
    output_samps->size[0] = 1;
    output_samps->size[1] = x_of_n->size[0];
    emxEnsureCapacity_real_T(output_samps, i);
    output_samps_data = output_samps->data;
    loop_ub = x_of_n->size[0] - 1;
    for (i = 0; i <= loop_ub; i++) {
      output_samps_data[i] = i;
    }
  }

  /* Use complex so when implementing in simulink later, it knows this is a */
  /* complex vector. */
  emxInit_creal_T(&s, 2);
  i = s->size[0] * s->size[1];
  s->size[0] = x_of_n->size[0];
  s->size[1] = 2;
  emxEnsureCapacity_creal_T(s, i);
  s_data = s->data;
  loop_ub = x_of_n->size[0] << 1;
  for (i = 0; i < loop_ub; i++) {
    s_data[i].re = 0.0;
    s_data[i].im = 0.0;
  }

  emxInit_creal_T(&Xs, 2);
  i = Xs->size[0] * Xs->size[1];
  Xs->size[0] = x_of_n->size[0];
  Xs->size[1] = 2;
  emxEnsureCapacity_creal_T(Xs, i);
  Xs_data = Xs->data;
  loop_ub = x_of_n->size[0] << 1;
  for (i = 0; i < loop_ub; i++) {
    Xs_data[i].re = 0.0;
    Xs_data[i].im = 0.0;
  }

  /* Develop a vector of frequencies that would result from the centered method */
  /* of the STFT function if it were computed on the x input. This is useful */
  /* for debugging the frequency outputs. */
  /* These are designed to develop the same freqs as the STFT centered method  */
  /* Check the "'FrequencyRange' — STFT frequency range" in the STFT help file */
  /* if mod(nw,2)==0 */
  /*     freqs_orig = ((-nw/2+1):nw/2)*Fs/nw; */
  /* else */
  /*     freqs_orig = (ceil(-nw/2):floor(nw/2))*Fs/nw; */
  /* end */
  /* figure; */
  loop_ub = output_samps->size[1];
  emxInit_creal_T(&currDFT, 2);
  currDFT_data = currDFT->data;
  emxInit_creal_T(&x, 1);
  emxInit_creal_T(&b_x, 2);
  emxInit_real_T(&sintab, 2);
  emxInit_real_T(&sintabinv, 2);
  emxInit_creal_T(&buffer, 2);
  for (b_i = 0; b_i < 2; b_i++) {
    double b_y;
    double t;
    xtmp_im = 0.5 * (double)b_i * 6.2831853071795862;
    i = x->size[0];
    x->size[0] = output_samps->size[1];
    emxEnsureCapacity_creal_T(x, i);
    x_data = x->data;
    for (i = 0; i < loop_ub; i++) {
      t = xtmp_im * output_samps_data[i];
      if (t == 0.0) {
        x_data[i].re = 0.0 / (double)nw;
        x_data[i].im = 0.0;
      } else {
        x_data[i].re = 0.0;
        x_data[i].im = t / (double)nw;
      }
    }

    nx = x->size[0];
    for (k = 0; k < nx; k++) {
      if (x_data[k].im == 0.0) {
        x_data[k].re = exp(x_data[k].re);
        x_data[k].im = 0.0;
      } else if (rtIsInf(x_data[k].im) && rtIsInf(x_data[k].re) && (x_data[k].re
                  < 0.0)) {
        x_data[k].re = 0.0;
        x_data[k].im = 0.0;
      } else {
        xtmp_re = exp(x_data[k].re / 2.0);
        x_data[k].re = xtmp_re * (xtmp_re * cos(x_data[k].im));
        x_data[k].im = xtmp_re * (xtmp_re * sin(x_data[k].im));
      }
    }

    b_loop_ub = x->size[0];
    for (i = 0; i < b_loop_ub; i++) {
      s_data[i + s->size[0] * b_i] = x_data[i];
    }

    if (s->size[0] == x_of_n->size[0]) {
      i = b_x->size[0] * b_x->size[1];
      b_x->size[0] = s->size[0];
      b_x->size[1] = 1;
      emxEnsureCapacity_creal_T(b_x, i);
      x_data = b_x->data;
      b_loop_ub = s->size[0];
      for (i = 0; i < b_loop_ub; i++) {
        x_data[i].re = x_of_n_data[i] * s_data[i + s->size[0] * b_i].re;
        x_data[i].im = x_of_n_data[i] * s_data[i + s->size[0] * b_i].im;
      }
    } else {
      c_binary_expand_op(b_x, s, b_i, x_of_n);
    }

    if (b_x->size[0] == 0) {
      currDFT->size[0] = 0;
      currDFT->size[1] = 1;
    } else {
      useRadix2 = ((b_x->size[0] & (b_x->size[0] - 1)) == 0);
      c_FFTImplementationCallback_get(b_x->size[0], useRadix2, &nx, &b_loop_ub);
      c_FFTImplementationCallback_gen(b_loop_ub, useRadix2, w_time_domain,
        sintab, sintabinv);
      if (useRadix2) {
        e_FFTImplementationCallback_r2b(b_x, b_x->size[0], w_time_domain, sintab,
          currDFT);
        currDFT_data = currDFT->data;
      } else {
        d_FFTImplementationCallback_dob(b_x, nx, b_x->size[0], w_time_domain,
          sintab, sintabinv, currDFT);
        currDFT_data = currDFT->data;
      }
    }

    if (currDFT->size[0] == 0) {
      b_y = 0.0;
    } else {
      b_y = 0.0;
      if (currDFT->size[0] == 1) {
        b_y = rt_hypotd_snf(currDFT_data[0].re, currDFT_data[0].im);
      } else {
        xtmp_re = 3.3121686421112381E-170;
        nx = currDFT->size[0];
        for (k = 0; k < nx; k++) {
          xtmp_im = fabs(currDFT_data[k].re);
          if (xtmp_im > xtmp_re) {
            t = xtmp_re / xtmp_im;
            b_y = b_y * t * t + 1.0;
            xtmp_re = xtmp_im;
          } else {
            t = xtmp_im / xtmp_re;
            b_y += t * t;
          }

          xtmp_im = fabs(currDFT_data[k].im);
          if (xtmp_im > xtmp_re) {
            t = xtmp_re / xtmp_im;
            b_y = b_y * t * t + 1.0;
            xtmp_re = xtmp_im;
          } else {
            t = xtmp_im / xtmp_re;
            b_y += t * t;
          }
        }

        b_y = xtmp_re * sqrt(b_y);
      }
    }

    i = currDFT->size[0] * currDFT->size[1];
    currDFT->size[1] = 1;
    emxEnsureCapacity_creal_T(currDFT, i);
    currDFT_data = currDFT->data;
    b_loop_ub = currDFT->size[0] - 1;
    for (i = 0; i <= b_loop_ub; i++) {
      xtmp_re = currDFT_data[i].re;
      t = currDFT_data[i].im;
      if (t == 0.0) {
        xtmp_im = xtmp_re / b_y;
        xtmp_re = 0.0;
      } else if (xtmp_re == 0.0) {
        xtmp_im = 0.0;
        xtmp_re = t / b_y;
      } else {
        xtmp_im = xtmp_re / b_y;
        xtmp_re = t / b_y;
      }

      currDFT_data[i].re = xtmp_im;
      currDFT_data[i].im = xtmp_re;
    }

    /* FFTSHIFTSTFT Performs a standard fftshift operation but accounts for the */
    /* different frequency range definition in Matlabs STFT function when */
    /* outputing a 'centered' frequency range */
    /*    When calling the STFT function, the default output for frequency is */
    /*    the 'centered' method where frequencies are reported on the range of */
    /*    (-n/2+1:n/2)*Fs/n if the vector is of even length and */
    /*    (ceil(-n/2):floor(n/2))*Fs/n if the vector is of odd length. It seems */
    /*    that Matlab's fftshift function is develped for frequencies in the */
    /*    range of (-n/2:n/2+1)*Fs/n if the vector is of even length. The odd */
    /*    length definition is unaffected. The result is an incorrect shifting of */
    /*    the frequency vector if fftshift is used on f defined by stft's */
    /*    centered method. This function uses the fftshift command for vectors */
    /*    of even length, but shifts the result by 1 to the left to correct for */
    /*    this problem.  */
    /*     */
    /*    If x is a matrix, it is assumed that the matrix is formatted similar to */
    /*    the output of a STFT call, wherein the rows represent the different */
    /*    frequencies and the rows are the time windows. As such, in this case */
    /*    the rows are operated on (shifted).  */
    /*  */
    /* INPUTS: */
    /*    x       nxm     A matrix of real or complex data. If passed a matrix, */
    /*                    the rows should represent frequency bins */
    /* OUTPUT: */
    /*    xout    nxm     A matrix of real or complex shifted data */
    /*  */
    /*  Author: Michael Shafer */
    /*  Date:   2020-12-19 */
    /*  */
    /*  Change log: */
    /*  2022-01-10    Updated to deal with row or column vectors or stft matrices */
    /*  */
    /*  if (numel(sz)~=2) && (min(sz)~=1) */
    /*      error('fftshiftstft only accepts vector inputs.') */
    /*  end */
    /* Passed a matrix or a column vector */
    if (currDFT->size[0] == 0) {
      i = 0;
    } else {
      i = (int)fmod(currDFT->size[0], 2.0);
    }

    if (i != 0.0) {
      fftshift(currDFT);
      currDFT_data = currDFT->data;
    } else {
      fftshift(currDFT);
      currDFT_data = currDFT->data;
      if ((currDFT->size[0] != 0) && (currDFT->size[0] != 1)) {
        b_loop_ub = currDFT->size[0] / 2;
        i = buffer->size[0] * buffer->size[1];
        buffer->size[0] = 1;
        buffer->size[1] = b_loop_ub;
        emxEnsureCapacity_creal_T(buffer, i);
        buffer_data = buffer->data;
        for (i = 0; i < b_loop_ub; i++) {
          buffer_data[i].re = 0.0;
          buffer_data[i].im = 0.0;
        }

        i = currDFT->size[0] - 2;
        buffer_data[0] = currDFT_data[0];
        for (k = 0; k <= i; k++) {
          currDFT_data[k] = currDFT_data[k + 1];
        }

        currDFT_data[currDFT->size[0] - 1] = buffer_data[0];
      }
    }

    b_loop_ub = Xs->size[0];
    for (i = 0; i < b_loop_ub; i++) {
      Xs_data[i + Xs->size[0] * b_i] = currDFT_data[i];
    }

    /*    stem(freqs_orig,abs(Xs(:,i)),'DisplayName',['\zeta =',num2str(zetas(i))]);  */
    /*    hold on */
  }

  emxFree_creal_T(&buffer);
  emxFree_real_T(&sintabinv);
  emxFree_real_T(&sintab);
  emxFree_creal_T(&b_x);
  emxFree_creal_T(&currDFT);
  emxFree_creal_T(&s);

  /* ylabel('|Xs|');xlabel('Frequency');legend('Location',"best"); */
  /* title('DFT of primary frequency shifts of the template') */
  /* New W generation method. ~25% faster on average */
  emxInit_creal_T(&stackedToeplitzMatrices, 2);
  i = stackedToeplitzMatrices->size[0] * stackedToeplitzMatrices->size[1];
  stackedToeplitzMatrices->size[0] = 2 * x_of_n->size[0];
  stackedToeplitzMatrices->size[1] = x_of_n->size[0];
  emxEnsureCapacity_creal_T(stackedToeplitzMatrices, i);
  buffer_data = stackedToeplitzMatrices->data;
  loop_ub = 2 * x_of_n->size[0] * x_of_n->size[0];
  for (i = 0; i < loop_ub; i++) {
    buffer_data[i].re = 0.0;
    buffer_data[i].im = 0.0;
  }

  if (Xs->size[0] < 2) {
    i = 0;
    i1 = 0;
  } else {
    i = 1;
    i1 = Xs->size[0];
  }

  loop_ub_tmp = i1 - i;
  md2 = loop_ub_tmp >> 1;
  i1 = Xs->size[0] - 1;
  emxInit_creal_T(&r, 1);
  for (b_i = 0; b_i < 2; b_i++) {
    int i2;
    if ((unsigned int)nw < 1U) {
      i2 = 0;
    } else {
      i2 = b_i * nw;
    }

    i3 = x->size[0];
    x->size[0] = loop_ub_tmp;
    emxEnsureCapacity_creal_T(x, i3);
    x_data = x->data;
    for (i3 = 0; i3 < loop_ub_tmp; i3++) {
      x_data[i3] = Xs_data[(i + i3) + Xs->size[0] * b_i];
    }

    for (loop_ub = 0; loop_ub < md2; loop_ub++) {
      xtmp_re = x_data[loop_ub].re;
      xtmp_im = x_data[loop_ub].im;
      nx = (loop_ub_tmp - loop_ub) - 1;
      x_data[loop_ub] = x_data[nx];
      x_data[nx].re = xtmp_re;
      x_data[nx].im = xtmp_im;
    }

    i3 = r->size[0];
    r->size[0] = x->size[0] + 1;
    emxEnsureCapacity_creal_T(r, i3);
    s_data = r->data;
    s_data[0] = Xs_data[Xs->size[0] * b_i];
    loop_ub = x->size[0];
    for (i3 = 0; i3 < loop_ub; i3++) {
      s_data[i3 + 1] = x_data[i3];
    }

    i3 = obj->W->size[0] * obj->W->size[1];
    obj->W->size[0] = Xs->size[0];
    obj->W->size[1] = r->size[0];
    emxEnsureCapacity_creal_T(obj->W, i3);
    nx = 0;
    i3 = r->size[0] - 1;
    for (b_loop_ub = 0; b_loop_ub <= i3; b_loop_ub++) {
      k = b_loop_ub;
      for (loop_ub = 0; loop_ub <= i1; loop_ub++) {
        if (loop_ub < b_loop_ub) {
          obj->W->data[nx + loop_ub] = s_data[k];
          k--;
        } else {
          obj->W->data[nx + loop_ub] = Xs_data[k + Xs->size[0] * b_i];
          k++;
        }
      }

      nx = (nx + i1) + 1;
    }

    loop_ub = obj->W->size[1];
    for (i3 = 0; i3 < loop_ub; i3++) {
      b_loop_ub = obj->W->size[0];
      for (nx = 0; nx < b_loop_ub; nx++) {
        buffer_data[(i2 + nx) + stackedToeplitzMatrices->size[0] * i3] = obj->
          W->data[nx + obj->W->size[0] * i3];
      }
    }
  }

  emxFree_creal_T(&r);
  emxFree_creal_T(&x);
  emxFree_creal_T(&Xs);

  /* Reshape in this way will interweave rows of each sub matrix of the stack */
  /* OLD W generation method. Easier to understand, but slower */
  /*  W     = 1i*zeros(nw,numZetas*nw); */
  /*  freqs = zeros(1,numZetas*nw); */
  /*  for i = 1:nw */
  /*      W(:,(i-1)*numZetas+(1:numZetas))=... */
  /*          circshift(Xs,i-1,1); */
  /*  end */
  /* Build a vector of the frequencies */
  /*   tick=1; */
  /*   for i = 1:numZetas:size(W,2) */
  /*       freqs(i:i+(numZetas-1)) = Fs/nw*((tick-1)+zetas); */
  /*       tick = tick+1; */
  /*   end */
  nfft = (unsigned int)x_of_n->size[0] << 1;

  /* MAKESTFTFREQVECTOR Generates the frequency vector based on the frequency */
  /* range specification for Matlab's stft.m 'FrequencyRange' input standard, */
  /*  */
  /*    This function outputs a frequency vector based on the frequency */
  /*    range specification for Matlab's stft.m 'FrequencyRange' input  */
  /*    standard. The options for the frequency ranges are 'centered' */
  /*    (default), 'twosided', and 'onesided'. The sftf.m documentation */
  /*    standard states:  */
  /*        STFT frequency range, specified as 'centered', 'twosided', or  */
  /*        'onesided'. */
  /*  */
  /*        'centered' — Compute a two-sided, centered STFT. If 'FFTLength' is  */
  /*        even, then s is computed over the interval (–π, π] rad/sample. If   */
  /*        'FFTLength' is odd, then s is computed over the interval (–π, π)   */
  /*        rad/sample. If you specify time information, then the intervals are  */
  /*         (–fs, fs/2] cycles/unit time and (–fs, fs/2) cycles/unit time,   */
  /*        respectively, where fs is the effective sample rate. */
  /*  */
  /*        'twosided' — Compute a two-sided STFT over the interval [0, 2π)   */
  /*        rad/sample. If you specify time information, then the interval is   */
  /*        [0, fs) cycles/unit time. */
  /*  */
  /*        'onesided' — Compute a one-sided STFT. If 'FFTLength' is even,   */
  /*        then s is computed over the interval [0, π] rad/sample. If   */
  /*        'FFTLength' is odd, then s is computed over the interval [0, π)   */
  /*        rad/sample. If you specify time information, then the intervals are  */
  /*         [0, fs/2] cycles/unit time and [0, fs/2) cycles/unit time,   */
  /*        respectively, where fs is the effective sample rate. This option is  */
  /*         valid only for real signals. */
  /*  */
  /*    If Fs is not specificed, outputs will be in rad/sample with pi as */
  /*    specified in the stft.m frequency range standard.  */
  /*     */
  /* INPUTS: */
  /*    nfft                 Length of FFT performed on the STFT. */
  /*    frequencyRangeType   String containing 'centered', 'twosided', 'onesided' */
  /*    Fs                   Sample rate of data          */
  /*  */
  /* OUTPUTS: */
  /*    freqs       Vector of frequencies at which the STFT is calculated */
  /*  */
  /* Author:    Michael Shafer */
  /* Date:      2022-01-11 */
  /*  */
  if ((double)nfft - 1.0 < 0.0) {
    output_samps->size[1] = 0;
  } else {
    i = output_samps->size[0] * output_samps->size[1];
    output_samps->size[0] = 1;
    output_samps->size[1] = (int)((double)nfft - 1.0) + 1;
    emxEnsureCapacity_real_T(output_samps, i);
    output_samps_data = output_samps->data;
    loop_ub = (int)((double)nfft - 1.0);
    for (i = 0; i <= loop_ub; i++) {
      output_samps_data[i] = i;
    }
  }

  /* Simulink (coder?) didn't like the new round inputs */
  /* freqs = round(freqs,3); */
  i = output_samps->size[0] * output_samps->size[1];
  output_samps->size[0] = 1;
  emxEnsureCapacity_real_T(output_samps, i);
  output_samps_data = output_samps->data;
  loop_ub = output_samps->size[1] - 1;
  for (i = 0; i <= loop_ub; i++) {
    output_samps_data[i] = output_samps_data[i] * Fs / (double)nfft * 1000.0;
  }

  nx = output_samps->size[1];
  for (k = 0; k < nx; k++) {
    output_samps_data[k] = rt_roundd_snf(output_samps_data[k]);
  }

  i = output_samps->size[0] * output_samps->size[1];
  output_samps->size[0] = 1;
  emxEnsureCapacity_real_T(output_samps, i);
  output_samps_data = output_samps->data;
  loop_ub = output_samps->size[1] - 1;
  for (i = 0; i <= loop_ub; i++) {
    output_samps_data[i] /= 1000.0;
  }

  /* Shift everything so we use a negative frequencies */
  /* A little non-matlab notation to get this to run in simulink. */
  xtmp_im = floor(Fs / 2.0);
  emxInit_boolean_T(&b_output_samps, 2);
  i = b_output_samps->size[0] * b_output_samps->size[1];
  b_output_samps->size[0] = 1;
  b_output_samps->size[1] = output_samps->size[1];
  emxEnsureCapacity_boolean_T(b_output_samps, i);
  b_output_samps_data = b_output_samps->data;
  loop_ub = output_samps->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_output_samps_data[i] = (output_samps_data[i] == xtmp_im);
  }

  int tmp_size[2];
  eml_find(b_output_samps, (int *)&nx, tmp_size);
  emxFree_boolean_T(&b_output_samps);
  xtmp_re = -output_samps_data[output_samps->size[1] - 1] - (Fs -
    output_samps_data[output_samps->size[1] - 1]);
  i = w_time_domain->size[0] * w_time_domain->size[1];
  w_time_domain->size[0] = 1;
  w_time_domain->size[1] = output_samps->size[1] - nx;
  emxEnsureCapacity_real_T(w_time_domain, i);
  w_time_domain_data = w_time_domain->data;
  loop_ub = output_samps->size[1] - nx;
  for (i = 0; i < loop_ub; i++) {
    w_time_domain_data[i] = 1.0;
  }

  /* Here we sort the output to set up to have an ascending order of frequency */
  /* to be similar to the centered frequency list used elsewhere in the */
  /* codebase for the STFT output.  */
  if (nx + w_time_domain->size[1] == output_samps->size[1]) {
    emxInit_real_T(&b_r, 1);
    i = b_r->size[0];
    b_r->size[0] = nx + w_time_domain->size[1];
    emxEnsureCapacity_real_T(b_r, i);
    w_time_domain_data = b_r->data;
    for (i = 0; i < nx; i++) {
      w_time_domain_data[i] = 0.0;
    }

    loop_ub = w_time_domain->size[1];
    for (i = 0; i < loop_ub; i++) {
      w_time_domain_data[i + nx] = xtmp_re;
    }

    i = obj->Wf->size[0];
    obj->Wf->size[0] = b_r->size[0];
    emxEnsureCapacity_real_T(obj->Wf, i);
    loop_ub = b_r->size[0];
    for (i = 0; i < loop_ub; i++) {
      obj->Wf->data[i] = w_time_domain_data[i] + output_samps_data[i];
    }

    emxFree_real_T(&b_r);
  } else {
    d_binary_expand_op(obj, nx, xtmp_re, w_time_domain, output_samps);
  }

  emxFree_real_T(&output_samps);
  emxFree_real_T(&w_time_domain);
  emxInit_int32_T(&iidx, 1);
  b_sort(obj->Wf, iidx);
  iidx_data = iidx->data;
  nx = x_of_n->size[0];
  i = obj->W->size[0] * obj->W->size[1];
  obj->W->size[0] = x_of_n->size[0];
  obj->W->size[1] = iidx->size[0];
  emxEnsureCapacity_creal_T(obj->W, i);
  loop_ub = iidx->size[0];
  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = x_of_n->size[0];
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      obj->W->data[i1 + obj->W->size[0] * i] = buffer_data[i1 + nx *
        (iidx_data[i] - 1)];
    }
  }

  emxFree_creal_T(&stackedToeplitzMatrices);
  if ((x_of_n->size[0] == 1) && (iidx->size[0] == 1)) {
    xtmp_re = obj->W->data[0].re;
    xtmp_im = obj->W->data[0].im;
    i = obj->W->size[0] * obj->W->size[1];
    obj->W->size[0] = 1;
    obj->W->size[1] = 1;
    emxEnsureCapacity_creal_T(obj->W, i);
    obj->W->data[0].re = xtmp_re;
    obj->W->data[0].im = xtmp_im;
  }

  emxFree_int32_T(&iidx);
  emxFree_real_T(&x_of_n);
  nx = 1;
  if (obj->Wf->size[0] != 1) {
    nx = obj->Wf->size[0];
  }

  if (obj->Wf->size[0] == 1) {
    xtmp_re = obj->Wf->data[0];
    i = obj->Wf->size[0];
    obj->Wf->size[0] = nx;
    emxEnsureCapacity_real_T(obj->Wf, i);
    for (i = 0; i < nx; i++) {
      obj->Wf->data[i] = xtmp_re;
    }
  } else {
    i = obj->Wf->size[0];
    obj->Wf->size[0] = nx;
    emxEnsureCapacity_real_T(obj->Wf, i);
  }
}

/*
 * SPECTRO Executes an STFT of x and sets up the wfmstst object
 * for the waveform
 *
 * INPUTS:
 *    obj     The waveform object
 * OUTPUTS:
 *    none
 *
 *             %%
 *
 * Arguments    : b_waveform *obj
 *                wfmstft *iobj_0
 * Return Type  : void
 */
void waveform_spectro(b_waveform *obj, wfmstft *iobj_0)
{
  emxArray_creal32_T *S;
  emxArray_creal_T *in;
  emxArray_real32_T *local_time;
  emxArray_real32_T *r;
  emxArray_real_T *out;
  creal_T *in_data;
  creal32_T *S_data;
  double n_est;
  double *out_data;
  float *local_time_data;
  float *r1;
  int i;
  int inVectorLength;
  int n;

  /* WFMSTFT Constructs and returns an instance of this class */
  /*  */
  /* An waveform object must be passed to this construction method */
  /* so that the constructor has access to the data vector, desired */
  /* overlap fraction, and priori pulse data, which is used to */
  /* develop the window sizes.  */
  /* INPUTS: */
  /*    waveform_obj   A single waveform object with prior */
  /*                   dependent properties set.  */
  /* OUTPUTS: */
  /*    obj             A wfmstft object */
  /*             %% */
  /*  */
  /* The following are variable sized properties. To tell coder */
  /* that they may vary setup as a local variable size variable */
  /* first, then set. */
  /* Instructions on https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html */
  /* maxFs*maxpulsewidth */
  /* Now actually assign them */
  emxInit_creal_T(&in, 2);
  iobj_0->S->size[0] = 0;
  iobj_0->S->size[1] = 0;
  emxInit_real_T(&out, 1);
  iobj_0->t->size[0] = 0;
  iobj_0->f->size[0] = 0;
  iobj_0->psd->size[0] = 0;
  iobj_0->wind->size[0] = 0;
  iobj_0->dt = 0.0;
  iobj_0->T = 0.0;

  /* wind = hann(waveform_obj.n_w,'periodic'); */
  /* wind = tukeywin(waveform_obj.n_w,0.3); */
  n_est = obj->n_w;
  if (n_est == floor(n_est)) {
    n = (int)n_est;
  } else {
    n = (int)rt_roundd_snf(n_est);
  }

  inVectorLength = 1;
  if (n != 1) {
    inVectorLength = n;
  }

  if (n == 1) {
    i = out->size[0];
    out->size[0] = inVectorLength;
    emxEnsureCapacity_real_T(out, i);
    out_data = out->data;
    for (i = 0; i < inVectorLength; i++) {
      out_data[i] = 1.0;
    }
  } else if (n == 0) {
    i = out->size[0];
    out->size[0] = inVectorLength;
    emxEnsureCapacity_real_T(out, i);
    out_data = out->data;
    for (i = 0; i < inVectorLength; i++) {
      out_data[i] = 1.0;
    }
  } else {
    i = out->size[0];
    out->size[0] = inVectorLength;
    emxEnsureCapacity_real_T(out, i);
    out_data = out->data;
    for (i = 0; i < inVectorLength; i++) {
      out_data[i] = 1.0;
    }
  }

  i = iobj_0->wind->size[0];
  iobj_0->wind->size[0] = out->size[0];
  emxEnsureCapacity_real_T(iobj_0->wind, i);
  n = out->size[0];
  for (i = 0; i < n; i++) {
    iobj_0->wind->data[i] = 1.0;
  }

  emxInit_creal32_T(&S, 2);
  emxInit_real32_T(&r, 1);
  emxInit_real32_T(&local_time, 1);
  stft(obj->x, obj->Fs, iobj_0->wind, obj->n_ol, obj->n_w, S, r, local_time);
  local_time_data = local_time->data;
  r1 = r->data;
  S_data = S->data;
  i = out->size[0];
  out->size[0] = r->size[0];
  emxEnsureCapacity_real_T(out, i);
  out_data = out->data;
  n = r->size[0];
  for (i = 0; i < n; i++) {
    out_data[i] = r1[i];
  }

  emxFree_real32_T(&r);
  inVectorLength = 1;
  if (out->size[0] != 1) {
    inVectorLength = out->size[0];
  }

  if (out->size[0] == 1) {
    n_est = out_data[0];
    i = out->size[0];
    out->size[0] = inVectorLength;
    emxEnsureCapacity_real_T(out, i);
    out_data = out->data;
    for (i = 0; i < inVectorLength; i++) {
      out_data[i] = n_est;
    }
  } else {
    i = out->size[0];
    out->size[0] = inVectorLength;
    emxEnsureCapacity_real_T(out, i);
    out_data = out->data;
  }

  i = iobj_0->f->size[0];
  iobj_0->f->size[0] = out->size[0];
  emxEnsureCapacity_real_T(iobj_0->f, i);
  n = out->size[0];
  for (i = 0; i < n; i++) {
    iobj_0->f->data[i] = out_data[i];
  }

  i = in->size[0] * in->size[1];
  in->size[0] = S->size[0];
  in->size[1] = S->size[1];
  emxEnsureCapacity_creal_T(in, i);
  in_data = in->data;
  n = S->size[0] * S->size[1];
  for (i = 0; i < n; i++) {
    in_data[i].re = S_data[i].re;
    in_data[i].im = S_data[i].im;
  }

  emxFree_creal32_T(&S);
  if ((in->size[0] == 1) && (in->size[1] == 1)) {
    double in_im;
    n_est = in_data[0].re;
    in_im = in_data[0].im;
    i = in->size[0] * in->size[1];
    in->size[0] = 1;
    in->size[1] = 1;
    emxEnsureCapacity_creal_T(in, i);
    in_data = in->data;
    in_data[0].re = n_est;
    in_data[0].im = in_im;
  }

  i = iobj_0->S->size[0] * iobj_0->S->size[1];
  iobj_0->S->size[0] = in->size[0];
  iobj_0->S->size[1] = in->size[1];
  emxEnsureCapacity_creal_T(iobj_0->S, i);
  n = in->size[0] * in->size[1];
  for (i = 0; i < n; i++) {
    iobj_0->S->data[i] = in_data[i];
  }

  emxFree_creal_T(&in);

  /*  Incoming x data in waveform is single precision, but sparse matrix multipliation later is only supported for double precision. */
  i = out->size[0];
  out->size[0] = local_time->size[0];
  emxEnsureCapacity_real_T(out, i);
  out_data = out->data;
  n = local_time->size[0];
  for (i = 0; i < n; i++) {
    out_data[i] = local_time_data[i] + obj->t_0;
  }

  emxFree_real32_T(&local_time);
  inVectorLength = 1;
  if (out->size[0] != 1) {
    inVectorLength = out->size[0];
  }

  if (out->size[0] == 1) {
    n_est = out_data[0];
    i = out->size[0];
    out->size[0] = inVectorLength;
    emxEnsureCapacity_real_T(out, i);
    out_data = out->data;
    for (i = 0; i < inVectorLength; i++) {
      out_data[i] = n_est;
    }
  } else {
    i = out->size[0];
    out->size[0] = inVectorLength;
    emxEnsureCapacity_real_T(out, i);
    out_data = out->data;
  }

  i = iobj_0->t->size[0];
  iobj_0->t->size[0] = out->size[0];
  emxEnsureCapacity_real_T(iobj_0->t, i);
  n = out->size[0];
  for (i = 0; i < n; i++) {
    iobj_0->t->data[i] = out_data[i];
  }

  emxFree_real_T(&out);

  /* Convert to global time of waveform. Double cast is needed because if x data in stft is single precision then the output t will be single as well. */
  n_est = 1.0 / obj->Fs;
  iobj_0->dt = n_est;
  n_est = obj->n_w / obj->Fs;
  iobj_0->T = n_est;
  wfmstft_updatepsd(iobj_0);

  /* obj.psd = obj.dt^2/obj.T*mean(abs(obj.S).^2,2);% Sxx = dt^2/T*|xhat(f)|^2  */
  /* Vestigial properties no longer used. Kept in case we want */
  /* to resurect them.  */
  /* obj.wind_per_pulse = floor(waveform_obj.n_w/waveform_obj.n_p); %How many windows are needed to capture a pulse */
  /* obj.stft_steps_per_pulse = floor(waveform_obj.t_ws/waveform_obj.ps_pre.t_p);%How many stft steps are needed to capture a pulse */
  obj->stft = iobj_0;
}

/*
 * WAVEFORM Constructs an instance of this class
 * INPUTS:
 *    x       1xn     Vector of samples
 *    Fs      1x1     Sample frequency (Hz)
 *    t_0     1x1     Time stamp of first element (s)
 *  ps_pre  1x1     Pulse stats object from previous data (priori)
 *    OLF     1x1     Overlap fraction as decimal (0.5 = 50%
 *                    overlap)
 * OUTPUTS:
 *    obj             The waveform object
 *             %%
 *
 * Arguments    : waveform *obj
 *                const creal32_T x[1000]
 *                double Fs
 *                pulsestats *ps_pre
 *                const threshold thresh
 * Return Type  : waveform *
 */
waveform *waveform_waveform(waveform *obj, const creal32_T x[1000], double Fs,
  pulsestats *ps_pre, const threshold thresh)
{
  pulsestats *obj_out;
  waveform *b_obj;
  waveform *c_obj;
  int i;
  b_obj = obj;
  b_obj->x->size[0] = 1;
  b_obj->x->size[1] = 0;
  b_obj->W->size[0] = 0;
  b_obj->W->size[1] = 0;
  b_obj->Wf->size[0] = 0;

  /* Flatten input to row */
  i = b_obj->x->size[0] * b_obj->x->size[1];
  b_obj->x->size[0] = 1;
  b_obj->x->size[1] = 1000;
  emxEnsureCapacity_creal32_T(b_obj->x, i);
  for (i = 0; i < 1000; i++) {
    b_obj->x->data[i] = x[i];
  }

  double b_ps_pre[2];

  /* Data vector */
  b_obj->l = 1000.0;

  /* Elements in the data */
  b_obj->Fs = Fs;

  /* Sample rate */
  b_obj->t_0 = 0.0;

  /* Time stamp of first element */
  b_obj->t_f = 999.0 / Fs;

  /* Time stamp of last element */
  b_obj->t_nextsegstart[0] = 0.0;
  b_obj->t_nextsegstart[1] = 0.0;

  /* This is the time when next */
  /* segment should start to */
  /* ensure sufficient overlap. */
  /* Will need to be updated  */
  /* elsewhere.  */
  b_obj->ps_pre = ps_pre;
  b_obj->OLF = 0.5;

  /* Overlap Fraction for STFT */
  b_obj->K = rtNaN;

  /* Unknown number of pulses. */
  c_obj = b_obj;

  /* WFMSTFT Constructs and returns an instance of this class */
  /*  */
  /* An waveform object must be passed to this construction method */
  /* so that the constructor has access to the data vector, desired */
  /* overlap fraction, and priori pulse data, which is used to */
  /* develop the window sizes.  */
  /* INPUTS: */
  /*    waveform_obj   A single waveform object with prior */
  /*                   dependent properties set.  */
  /* OUTPUTS: */
  /*    obj             A wfmstft object */
  /*             %% */
  /*  */
  /* The following are variable sized properties. To tell coder */
  /* that they may vary setup as a local variable size variable */
  /* first, then set. */
  /* Instructions on https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html */
  /* maxFs*maxpulsewidth */
  /* Now actually assign them */
  b_obj->_pobj1.S->size[0] = 0;
  b_obj->_pobj1.S->size[1] = 0;
  b_obj->_pobj1.t->size[0] = 0;
  b_obj->_pobj1.f->size[0] = 0;
  b_obj->_pobj1.psd->size[0] = 0;
  b_obj->_pobj1.wind->size[0] = 0;
  b_obj->_pobj1.dt = 0.0;
  b_obj->_pobj1.T = 0.0;
  c_obj->stft = &b_obj->_pobj1;

  /* Unknown values but set types */
  b_obj->W->size[0] = 0;
  b_obj->W->size[1] = 0;
  b_obj->Wf->size[0] = 0;

  /* Copy over ps_ */
  /* COPY Creates an exact copy of the pulse stats object as a separate object */
  b_ps_pre[0] = ps_pre->tmplt[0];
  b_ps_pre[1] = ps_pre->tmplt[1];
  obj_out = b_pulsestats_pulsestats(&b_obj->_pobj0, ps_pre->t_p, ps_pre->t_ip,
    ps_pre->t_ipu, ps_pre->t_ipj, ps_pre->fp, ps_pre->fstart, ps_pre->fend,
    b_ps_pre, ps_pre->mode, ps_pre->pl, ps_pre->clst, ps_pre->cmsk, ps_pre->cpki);

  /* ,... */
  /* obj.thresh); */
  b_obj->ps_pos = obj_out;

  /* Current stats are same as previous during construction */
  /* obj.ps_pos = pulsestats();%TESTING FOR CODER - NEEDS TO BE REVERTED BACK TO LAST LINE */
  /* obj.TimeCorr = TemporalCorrelator(10, 0, 0);%Generate a temporalcorrelator object so coder knows the type of the object */
  c_waveform_setprioridependentpr(b_obj, ps_pre);
  emxCopyStruct_threshold(&b_obj->thresh, &thresh);
  return b_obj;
}

/*
 * File trailer for waveform.c
 *
 * [EOF]
 */
