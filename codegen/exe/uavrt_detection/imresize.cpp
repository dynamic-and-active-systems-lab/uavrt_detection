//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: imresize.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "imresize.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "sub2ind.h"
#include "sum.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Function Declarations
namespace coder {
static void b_resizeAlongDim2D(const array<double, 2U> &in,
                               const array<double, 2U> &weights,
                               const array<int, 2U> &indices, double out_length,
                               array<double, 2U> &out);

static void contributions(int in_length, double out_length, double scale,
                          double kernel_width, array<double, 2U> &weights,
                          array<int, 2U> &indices);

static void resizeAlongDim2D(const array<double, 2U> &in,
                             const array<double, 2U> &weights,
                             const array<int, 2U> &indices, double out_length,
                             array<double, 2U> &out);

} // namespace coder
static void mc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const array<double, 2U> &in
//                const array<double, 2U> &weights
//                const array<int, 2U> &indices
//                double out_length
//                array<double, 2U> &out
// Return Type  : void
//
namespace coder {
static void b_resizeAlongDim2D(const array<double, 2U> &in,
                               const array<double, 2U> &weights,
                               const array<int, 2U> &indices, double out_length,
                               array<double, 2U> &out)
{
  double sumVal1;
  int iv[2];
  int i;
  int i1;
  int k;
  int ndx;
  int outCInd;
  int pixelIndex;
  int ub_loop;
  ub_loop = in.size(0);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        pixelIndex, sumVal1, i, outCInd, iv, ndx, i1, k)

  for (int inRInd = 0; inRInd < ub_loop; inRInd++) {
    if (inRInd + 1 > in.size(0)) {
      gc_rtErrorWithMessageID(ec_emlrtRTEI.fName, ec_emlrtRTEI.lineNo);
    }
    if (in.size(1) < 1) {
      gc_rtErrorWithMessageID(ec_emlrtRTEI.fName, ec_emlrtRTEI.lineNo);
    }
    i = static_cast<int>(out_length);
    for (outCInd = 0; outCInd < i; outCInd++) {
      sumVal1 = 0.0;
      //  Core - second dimension
      iv[0] = (*(int(*)[2])((array<double, 2U> *)&weights)->size())[0];
      iv[1] = (*(int(*)[2])((array<double, 2U> *)&weights)->size())[1];
      ndx = internal::sub2ind(iv, static_cast<double>(outCInd) + 1.0);
      i1 = weights.size(0);
      for (k = 0; k < i1; k++) {
        pixelIndex = (inRInd + (indices[(ndx + k) - 1] - 1) * in.size(0)) + 1;
        sumVal1 += weights[(ndx + k) - 1] * in[pixelIndex - 1];
      }
      out[inRInd + out.size(0) * outCInd] = sumVal1;
    }
  }
}

//
// Arguments    : int in_length
//                double out_length
//                double scale
//                double kernel_width
//                array<double, 2U> &weights
//                array<int, 2U> &indices
// Return Type  : void
//
static void contributions(int in_length, double out_length, double scale,
                          double kernel_width, array<double, 2U> &weights,
                          array<int, 2U> &indices)
{
  array<double, 2U> absx;
  array<double, 2U> absx2;
  array<double, 2U> b_x;
  array<double, 2U> y;
  array<double, 1U> u;
  array<double, 1U> x;
  array<int, 2U> aux;
  array<int, 2U> b_indices;
  array<int, 2U> r;
  array<int, 1U> left;
  array<boolean_T, 2U> copyCols;
  double k;
  int acoef;
  int b_csz_idx_0;
  int csz_idx_0;
  int i;
  int loop_ub;
  int loop_ub_tmp;
  int n_tmp_tmp;
  int yk;
  //  Contributions, using pixel indices
  if (scale < 1.0) {
    kernel_width = 4.0 / scale;
  }
  if (std::isnan(out_length)) {
    y.set_size(1, 1);
    y[0] = rtNaN;
  } else if (out_length < 1.0) {
    y.set_size(1, 0);
  } else {
    y.set_size(1, static_cast<int>(out_length - 1.0) + 1);
    loop_ub = static_cast<int>(out_length - 1.0);
    for (i = 0; i <= loop_ub; i++) {
      y[i] = static_cast<double>(i) + 1.0;
    }
  }
  k = 0.5 * (1.0 - 1.0 / scale);
  loop_ub = y.size(1);
  u.set_size(y.size(1));
  for (i = 0; i < loop_ub; i++) {
    u[i] = y[i] / scale + k;
  }
  k = kernel_width / 2.0;
  x.set_size(y.size(1));
  for (i = 0; i < loop_ub; i++) {
    x[i] = u[i] - k;
  }
  if (x.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int b_k{0}; b_k < loop_ub; b_k++) {
    x[b_k] = std::floor(x[b_k]);
  }
  left.set_size(y.size(1));
  for (i = 0; i < loop_ub; i++) {
    left[i] = static_cast<int>(x[i]);
  }
  n_tmp_tmp = static_cast<int>(std::ceil(kernel_width) + 2.0);
  aux.set_size(1, n_tmp_tmp);
  aux[0] = 0;
  yk = 0;
  if (static_cast<int>(std::ceil(kernel_width) + 2.0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int b_k{2}; b_k <= n_tmp_tmp; b_k++) {
    yk++;
    aux[b_k - 1] = yk;
  }
  indices.set_size(y.size(1), n_tmp_tmp);
  if (left.size(0) != 0) {
    acoef = (left.size(0) != 1);
    for (int b_k{0}; b_k < n_tmp_tmp; b_k++) {
      for (int c_k{0}; c_k < loop_ub; c_k++) {
        indices[c_k + indices.size(0) * b_k] = left[acoef * c_k] + aux[b_k];
      }
    }
  }
  absx.set_size(y.size(1), n_tmp_tmp);
  loop_ub_tmp = indices.size(0) * indices.size(1);
  for (i = 0; i < loop_ub_tmp; i++) {
    absx[i] = indices[i];
  }
  if (absx.size(0) == 1) {
    csz_idx_0 = y.size(1);
  } else if (u.size(0) == 1) {
    csz_idx_0 = y.size(1);
  } else if (u.size(0) == absx.size(0)) {
    csz_idx_0 = y.size(1);
  } else {
    t_rtErrorWithMessageID(x_emlrtRTEI.fName, x_emlrtRTEI.lineNo);
  }
  b_x.set_size(csz_idx_0, n_tmp_tmp);
  if (csz_idx_0 != 0) {
    yk = (u.size(0) != 1);
    for (int b_k{0}; b_k < n_tmp_tmp; b_k++) {
      i = b_x.size(0);
      for (int c_k{0}; c_k < i; c_k++) {
        acoef = yk * c_k;
        b_x[c_k + b_x.size(0) * b_k] =
            u[acoef] - absx[acoef + absx.size(0) * b_k];
      }
    }
  }
  if (scale < 1.0) {
    yk = b_x.size(0) * b_x.size(1);
    for (i = 0; i < yk; i++) {
      b_x[i] = scale * b_x[i];
    }
  }
  yk = b_x.size(0) * b_x.size(1);
  absx.set_size(b_x.size(0), b_x.size(1));
  if (yk > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int b_k{0}; b_k < yk; b_k++) {
    absx[b_k] = std::abs(b_x[b_k]);
  }
  absx2.set_size(absx.size(0), absx.size(1));
  yk = absx.size(0) * absx.size(1);
  if (yk > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int b_k{0}; b_k < yk; b_k++) {
    absx2[b_k] = absx[b_k] * absx[b_k];
  }
  weights.set_size(absx.size(0), absx.size(1));
  for (int b_k{0}; b_k < yk; b_k++) {
    weights[b_k] = rt_powd_snf(absx[b_k], 3.0);
  }
  for (i = 0; i < yk; i++) {
    absx2[i] = 2.5 * absx2[i];
  }
  for (i = 0; i < yk; i++) {
    weights[i] = ((1.5 * weights[i] - absx2[i]) + 1.0) *
                     static_cast<double>(absx[i] <= 1.0) +
                 (((-0.5 * weights[i] + absx2[i]) - 4.0 * absx[i]) + 2.0) *
                     static_cast<double>((absx[i] > 1.0) && (absx[i] <= 2.0));
  }
  if (scale < 1.0) {
    for (i = 0; i < yk; i++) {
      weights[i] = scale * weights[i];
    }
  }
  i = weights.size(1);
  absx.set_size(weights.size(0), weights.size(1));
  for (csz_idx_0 = 0; csz_idx_0 < yk; csz_idx_0++) {
    absx[csz_idx_0] = weights[csz_idx_0];
  }
  sum(weights, u);
  if (u.size(0) == 1) {
    b_csz_idx_0 = weights.size(0);
  } else if (weights.size(0) == 1) {
    b_csz_idx_0 = u.size(0);
  } else if (weights.size(0) == u.size(0)) {
    b_csz_idx_0 = weights.size(0);
  } else {
    t_rtErrorWithMessageID(x_emlrtRTEI.fName, x_emlrtRTEI.lineNo);
  }
  weights.set_size(b_csz_idx_0, i);
  if (b_csz_idx_0 != 0) {
    acoef = (absx.size(0) != 1);
    yk = (u.size(0) != 1);
    for (int b_k{0}; b_k < i; b_k++) {
      csz_idx_0 = weights.size(0);
      for (int c_k{0}; c_k < csz_idx_0; c_k++) {
        weights[c_k + weights.size(0) * b_k] =
            absx[acoef * c_k + absx.size(0) * b_k] / u[yk * c_k];
      }
    }
  }
  //  Create the auxiliary matrix:
  yk = in_length << 1;
  aux.set_size(1, yk);
  aux[0] = 1;
  aux[in_length] = in_length;
  if (in_length > 2147483646) {
    check_forloop_overflow_error();
  }
  for (n_tmp_tmp = 2; n_tmp_tmp <= in_length; n_tmp_tmp++) {
    aux[n_tmp_tmp - 1] = aux[n_tmp_tmp - 2] + 1;
    acoef = in_length + n_tmp_tmp;
    aux[acoef - 1] = aux[acoef - 2] - 1;
  }
  //  Mirror the out-of-bounds indices using mod:
  for (n_tmp_tmp = 0; n_tmp_tmp < loop_ub_tmp; n_tmp_tmp++) {
    k = static_cast<double>(indices[n_tmp_tmp]) - 1.0;
    if (yk == 0) {
      if (k == 0.0) {
        k = 0.0;
      }
    } else if (k == 0.0) {
      k = 0.0;
    } else {
      k = std::fmod(k, static_cast<double>(yk));
      if (k == 0.0) {
        k = 0.0;
      } else if (k < 0.0) {
        k += static_cast<double>(yk);
      }
    }
    indices[n_tmp_tmp] = aux[static_cast<int>(k)];
  }
  copyCols.set_size(1, weights.size(1));
  loop_ub_tmp = weights.size(1);
  for (csz_idx_0 = 0; csz_idx_0 < loop_ub_tmp; csz_idx_0++) {
    copyCols[csz_idx_0] = false;
  }
  yk = 0;
  if (weights.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (n_tmp_tmp = 0; n_tmp_tmp < i; n_tmp_tmp++) {
    boolean_T exitg1;
    acoef = yk + weights.size(0);
    csz_idx_0 = yk;
    yk = acoef;
    if ((csz_idx_0 + 1 <= acoef) && (acoef > 2147483646)) {
      check_forloop_overflow_error();
    }
    exitg1 = false;
    while ((!exitg1) && (csz_idx_0 + 1 <= acoef)) {
      if ((weights[csz_idx_0] == 0.0) || std::isnan(weights[csz_idx_0])) {
        csz_idx_0++;
      } else {
        copyCols[n_tmp_tmp] = true;
        exitg1 = true;
      }
    }
  }
  yk = 0;
  for (n_tmp_tmp = 0; n_tmp_tmp < loop_ub_tmp; n_tmp_tmp++) {
    if (copyCols[n_tmp_tmp]) {
      yk++;
    }
  }
  r.set_size(1, yk);
  yk = 0;
  for (n_tmp_tmp = 0; n_tmp_tmp < loop_ub_tmp; n_tmp_tmp++) {
    if (copyCols[n_tmp_tmp]) {
      r[yk] = n_tmp_tmp;
      yk++;
    }
  }
  yk = weights.size(0);
  acoef = r.size(1);
  absx.set_size(r.size(1), weights.size(0));
  for (i = 0; i < yk; i++) {
    for (csz_idx_0 = 0; csz_idx_0 < acoef; csz_idx_0++) {
      absx[csz_idx_0 + absx.size(0) * i] =
          weights[i + weights.size(0) * r[csz_idx_0]];
    }
  }
  weights.set_size(r.size(1), yk);
  loop_ub_tmp = absx.size(0) * absx.size(1);
  for (i = 0; i < loop_ub_tmp; i++) {
    weights[i] = absx[i];
  }
  b_indices.set_size(r.size(1), y.size(1));
  for (i = 0; i < loop_ub; i++) {
    for (csz_idx_0 = 0; csz_idx_0 < acoef; csz_idx_0++) {
      b_indices[csz_idx_0 + b_indices.size(0) * i] =
          indices[i + indices.size(0) * r[csz_idx_0]];
    }
  }
  indices.set_size(r.size(1), y.size(1));
  loop_ub_tmp = b_indices.size(0) * b_indices.size(1);
  for (i = 0; i < loop_ub_tmp; i++) {
    indices[i] = b_indices[i];
  }
}

//
// Arguments    : const array<double, 2U> &in
//                const array<double, 2U> &weights
//                const array<int, 2U> &indices
//                double out_length
//                array<double, 2U> &out
// Return Type  : void
//
static void resizeAlongDim2D(const array<double, 2U> &in,
                             const array<double, 2U> &weights,
                             const array<int, 2U> &indices, double out_length,
                             array<double, 2U> &out)
{
  double sumVal1;
  int iv[2];
  int i;
  int i1;
  int k;
  int ndx;
  int outRInd;
  int ub_loop;
  ub_loop = static_cast<int>(static_cast<double>(in.size(0) * in.size(1)) /
                             static_cast<double>(in.size(0)));
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        sumVal1, i, outRInd, iv, ndx, i1, k)

  for (int inCInd = 0; inCInd < ub_loop; inCInd++) {
    i = static_cast<int>(out_length);
    for (outRInd = 0; outRInd < i; outRInd++) {
      sumVal1 = 0.0;
      iv[0] = (*(int(*)[2])((array<double, 2U> *)&weights)->size())[0];
      iv[1] = (*(int(*)[2])((array<double, 2U> *)&weights)->size())[1];
      ndx = internal::sub2ind(iv, static_cast<double>(outRInd) + 1.0);
      //  Core - first dimension
      i1 = weights.size(0);
      for (k = 0; k < i1; k++) {
        sumVal1 += weights[(ndx + k) - 1] *
                   in[(indices[(ndx + k) - 1] + in.size(0) * inCInd) - 1];
      }
      out[outRInd + out.size(0) * inCInd] = sumVal1;
    }
  }
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
} // namespace coder
static void mc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "OUTPUTSIZE must be a two-element vector of positive values.";
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
// Arguments    : const array<double, 2U> &Ain
//                const double varargin_1[2]
//                array<double, 2U> &Bout
// Return Type  : void
//
namespace coder {
void imresize(const array<double, 2U> &Ain, const double varargin_1[2],
              array<double, 2U> &Bout)
{
  static rtRunTimeErrorInfo rc_emlrtRTEI{
      319,       // lineNo
      "imresize" // fName
  };
  array<double, 2U> out;
  array<double, 2U> weights;
  array<int, 2U> indices;
  double outputSize_idx_0;
  double outputSize_idx_1;
  double scale_idx_0;
  double scale_idx_1;
  int k;
  boolean_T x[2];
  boolean_T exitg1;
  boolean_T y;
  if ((Ain.size(0) == 0) || (Ain.size(1) == 0)) {
    g_rtErrorWithMessageID("input number 1, A,", u_emlrtRTEI.fName,
                           u_emlrtRTEI.lineNo);
  }
  x[0] = (varargin_1[0] <= 0.0);
  x[1] = (varargin_1[1] <= 0.0);
  y = false;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 2)) {
    if (x[k]) {
      y = true;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (y) {
    mc_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
  }
  if (std::isnan(varargin_1[0])) {
    outputSize_idx_0 =
        std::ceil(varargin_1[1] * static_cast<double>(Ain.size(0)) /
                  static_cast<double>(Ain.size(1)));
    outputSize_idx_1 = std::ceil(varargin_1[1]);
    scale_idx_0 = outputSize_idx_1 / static_cast<double>(Ain.size(1));
    scale_idx_1 = outputSize_idx_1 / static_cast<double>(Ain.size(1));
  } else if (std::isnan(varargin_1[1])) {
    outputSize_idx_0 = std::ceil(varargin_1[0]);
    outputSize_idx_1 =
        std::ceil(varargin_1[0] * static_cast<double>(Ain.size(1)) /
                  static_cast<double>(Ain.size(0)));
    scale_idx_0 = outputSize_idx_0 / static_cast<double>(Ain.size(0));
    scale_idx_1 = scale_idx_0;
  } else {
    outputSize_idx_0 = std::ceil(varargin_1[0]);
    outputSize_idx_1 = std::ceil(varargin_1[1]);
    scale_idx_0 = outputSize_idx_0 / static_cast<double>(Ain.size(0));
    scale_idx_1 = outputSize_idx_1 / static_cast<double>(Ain.size(1));
  }
  if (scale_idx_0 <= scale_idx_1) {
    //  Resize first dimension
    contributions(Ain.size(0), outputSize_idx_0, scale_idx_0, 4.0, weights,
                  indices);
    out.set_size(weights.size(1), Ain.size(1));
    resizeAlongDim2D(Ain, weights, indices,
                     static_cast<double>(weights.size(1)), out);
    //  Resize second dimension
    contributions(Ain.size(1), outputSize_idx_1, scale_idx_1, 4.0, weights,
                  indices);
    Bout.set_size(out.size(0), weights.size(1));
    b_resizeAlongDim2D(out, weights, indices,
                       static_cast<double>(weights.size(1)), Bout);
  } else {
    contributions(Ain.size(1), outputSize_idx_1, scale_idx_1, 4.0, weights,
                  indices);
    out.set_size(Ain.size(0), weights.size(1));
    b_resizeAlongDim2D(Ain, weights, indices,
                       static_cast<double>(weights.size(1)), out);
    //  Resize second dimension
    contributions(Ain.size(0), outputSize_idx_0, scale_idx_0, 4.0, weights,
                  indices);
    Bout.set_size(weights.size(1), out.size(1));
    resizeAlongDim2D(out, weights, indices,
                     static_cast<double>(weights.size(1)), Bout);
  }
}

} // namespace coder

//
// File trailer for imresize.cpp
//
// [EOF]
//
