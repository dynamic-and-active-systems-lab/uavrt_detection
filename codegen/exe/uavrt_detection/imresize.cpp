//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: imresize.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 20-Feb-2023 17:51:34
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
#include <string.h>
#include <string>

// Function Declarations
namespace coder {
static void b_resizeAlongDim2D(const ::coder::array<double, 2U> &in,
                               const ::coder::array<double, 2U> &weights,
                               const ::coder::array<int, 2U> &indices,
                               double out_length,
                               ::coder::array<double, 2U> &out);

static void contributions(int in_length, double out_length, double scale,
                          double kernel_width,
                          ::coder::array<double, 2U> &weights,
                          ::coder::array<int, 2U> &indices);

static void resizeAlongDim2D(const ::coder::array<double, 2U> &in,
                             const ::coder::array<double, 2U> &weights,
                             const ::coder::array<int, 2U> &indices,
                             double out_length,
                             ::coder::array<double, 2U> &out);

} // namespace coder
static void hc_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &in
//                const ::coder::array<double, 2U> &weights
//                const ::coder::array<int, 2U> &indices
//                double out_length
//                ::coder::array<double, 2U> &out
// Return Type  : void
//
namespace coder {
static void b_resizeAlongDim2D(const ::coder::array<double, 2U> &in,
                               const ::coder::array<double, 2U> &weights,
                               const ::coder::array<int, 2U> &indices,
                               double out_length,
                               ::coder::array<double, 2U> &out)
{
  double sumVal1;
  int iv[2];
  int i;
  int i1;
  int k;
  int ndx;
  int outCInd;
  int pixelIndex;
  int pixelIndex_tmp;
  int ub_loop;
  ub_loop = in.size(0) - 1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    pixelIndex, sumVal1, i, outCInd, iv, ndx, i1, k, pixelIndex_tmp)

  for (int inRInd = 0; inRInd <= ub_loop; inRInd++) {
    if (inRInd + 1 > in.size(0)) {
      bc_rtErrorWithMessageID(lc_emlrtRTEI.fName, lc_emlrtRTEI.lineNo);
    }
    if (in.size(1) < 1) {
      bc_rtErrorWithMessageID(lc_emlrtRTEI.fName, lc_emlrtRTEI.lineNo);
    }
    i = static_cast<int>(out_length);
    for (outCInd = 0; outCInd < i; outCInd++) {
      sumVal1 = 0.0;
      //  Core - second dimension
      iv[0] = (*(int(*)[2])((::coder::array<double, 2U> *)&weights)->size())[0];
      iv[1] = (*(int(*)[2])((::coder::array<double, 2U> *)&weights)->size())[1];
      ndx = eml_sub2ind(iv, static_cast<double>(outCInd) + 1.0);
      i1 = weights.size(0);
      for (k = 0; k < i1; k++) {
        pixelIndex_tmp = (ndx + k) - 1;
        pixelIndex = (inRInd + (indices[pixelIndex_tmp] - 1) * in.size(0)) + 1;
        sumVal1 += weights[pixelIndex_tmp] * in[pixelIndex - 1];
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
//                ::coder::array<double, 2U> &weights
//                ::coder::array<int, 2U> &indices
// Return Type  : void
//
static void contributions(int in_length, double out_length, double scale,
                          double kernel_width,
                          ::coder::array<double, 2U> &weights,
                          ::coder::array<int, 2U> &indices)
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
  array<int, 2U> r1;
  array<int, 1U> left;
  array<boolean_T, 2U> copyCols;
  double k;
  int b_i;
  int b_k;
  int csz_idx_0;
  int i;
  int i1;
  int nx;
  int yk;
  boolean_T iscompatible;
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
    yk = static_cast<int>(out_length - 1.0);
    for (i = 0; i <= yk; i++) {
      y[i] = static_cast<double>(i) + 1.0;
    }
  }
  k = 0.5 * (1.0 - 1.0 / scale);
  u.set_size(y.size(1));
  yk = y.size(1);
  for (i = 0; i < yk; i++) {
    u[i] = y[i] / scale + k;
  }
  k = kernel_width / 2.0;
  x.set_size(u.size(0));
  yk = u.size(0);
  for (i = 0; i < yk; i++) {
    x[i] = u[i] - k;
  }
  nx = x.size(0);
  if (x.size(0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (i1 = 0; i1 < nx; i1++) {
    x[i1] = std::floor(x[i1]);
  }
  left.set_size(x.size(0));
  yk = x.size(0);
  for (i = 0; i < yk; i++) {
    left[i] = static_cast<int>(x[i]);
  }
  nx = static_cast<int>(std::ceil(kernel_width) + 2.0);
  aux.set_size(1, nx);
  aux[0] = 0;
  yk = 0;
  if (static_cast<int>(std::ceil(kernel_width) + 2.0) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (i1 = 2; i1 <= nx; i1++) {
    yk++;
    aux[i1 - 1] = yk;
  }
  indices.set_size(left.size(0), aux.size(1));
  if (left.size(0) != 0) {
    i = aux.size(1) - 1;
    yk = (left.size(0) != 1);
    for (i1 = 0; i1 <= i; i1++) {
      b_i = indices.size(0) - 1;
      for (b_k = 0; b_k <= b_i; b_k++) {
        indices[b_k + indices.size(0) * i1] = left[yk * b_k] + aux[i1];
      }
    }
  }
  absx.set_size(indices.size(0), indices.size(1));
  yk = indices.size(0) * indices.size(1);
  for (i = 0; i < yk; i++) {
    absx[i] = indices[i];
  }
  if (absx.size(0) == 1) {
    csz_idx_0 = u.size(0);
  } else if (u.size(0) == 1) {
    csz_idx_0 = absx.size(0);
  } else if (u.size(0) == absx.size(0)) {
    csz_idx_0 = u.size(0);
  } else {
    u_rtErrorWithMessageID(jb_emlrtRTEI.fName, jb_emlrtRTEI.lineNo);
  }
  b_x.set_size(csz_idx_0, absx.size(1));
  if (csz_idx_0 != 0) {
    i = absx.size(1) - 1;
    yk = (u.size(0) != 1);
    nx = (absx.size(0) != 1);
    for (i1 = 0; i1 <= i; i1++) {
      b_i = b_x.size(0) - 1;
      for (b_k = 0; b_k <= b_i; b_k++) {
        b_x[b_k + b_x.size(0) * i1] =
            u[yk * b_k] - absx[nx * b_k + absx.size(0) * i1];
      }
    }
  }
  if (scale < 1.0) {
    yk = b_x.size(0) * b_x.size(1);
    for (i = 0; i < yk; i++) {
      b_x[i] = scale * b_x[i];
    }
  }
  nx = b_x.size(0) * b_x.size(1);
  absx.set_size(b_x.size(0), b_x.size(1));
  if (nx > 2147483646) {
    check_forloop_overflow_error();
  }
  for (i1 = 0; i1 < nx; i1++) {
    absx[i1] = std::abs(b_x[i1]);
  }
  absx2.set_size(absx.size(0), absx.size(1));
  nx = absx.size(0) * absx.size(1);
  if (nx > 2147483646) {
    check_forloop_overflow_error();
  }
  for (i1 = 0; i1 < nx; i1++) {
    absx2[i1] = absx[i1] * absx[i1];
  }
  weights.set_size(absx.size(0), absx.size(1));
  nx = absx.size(0) * absx.size(1);
  if (nx > 2147483646) {
    check_forloop_overflow_error();
  }
  for (i1 = 0; i1 < nx; i1++) {
    weights[i1] = rt_powd_snf(absx[i1], 3.0);
  }
  yk = absx2.size(0) * absx2.size(1);
  for (i = 0; i < yk; i++) {
    absx2[i] = 2.5 * absx2[i];
  }
  yk = weights.size(0) * weights.size(1);
  for (i = 0; i < yk; i++) {
    weights[i] = ((1.5 * weights[i] - absx2[i]) + 1.0) *
                     static_cast<double>(absx[i] <= 1.0) +
                 (((-0.5 * weights[i] + absx2[i]) - 4.0 * absx[i]) + 2.0) *
                     static_cast<double>((absx[i] > 1.0) && (absx[i] <= 2.0));
  }
  if (scale < 1.0) {
    yk = weights.size(0) * weights.size(1);
    for (i = 0; i < yk; i++) {
      weights[i] = scale * weights[i];
    }
  }
  absx.set_size(weights.size(0), weights.size(1));
  yk = weights.size(0) * weights.size(1);
  for (i = 0; i < yk; i++) {
    absx[i] = weights[i];
  }
  sum(weights, u);
  iscompatible = true;
  if (u.size(0) == 1) {
    csz_idx_0 = weights.size(0);
  } else if (weights.size(0) == 1) {
    csz_idx_0 = u.size(0);
  } else if (weights.size(0) == u.size(0)) {
    csz_idx_0 = weights.size(0);
  } else {
    iscompatible = false;
    nx = u.size(0);
    csz_idx_0 = weights.size(0);
    if (nx <= csz_idx_0) {
      csz_idx_0 = nx;
    }
  }
  nx = weights.size(1);
  if (!iscompatible) {
    u_rtErrorWithMessageID(jb_emlrtRTEI.fName, jb_emlrtRTEI.lineNo);
  }
  weights.set_size(csz_idx_0, nx);
  if (csz_idx_0 != 0) {
    i = nx - 1;
    yk = (absx.size(0) != 1);
    nx = (u.size(0) != 1);
    for (i1 = 0; i1 <= i; i1++) {
      b_i = weights.size(0) - 1;
      for (b_k = 0; b_k <= b_i; b_k++) {
        weights[b_k + weights.size(0) * i1] =
            absx[yk * b_k + absx.size(0) * i1] / u[nx * b_k];
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
  for (b_i = 2; b_i <= in_length; b_i++) {
    aux[b_i - 1] = aux[b_i - 2] + 1;
    nx = in_length + b_i;
    aux[nx - 1] = aux[nx - 2] - 1;
  }
  //  Mirror the out-of-bounds indices using mod:
  i = indices.size(0) * indices.size(1);
  for (b_i = 0; b_i < i; b_i++) {
    k = static_cast<double>(indices[b_i]) - 1.0;
    if (yk == 0) {
      if (static_cast<double>(indices[b_i]) - 1.0 == 0.0) {
        k = 0.0;
      }
    } else if (static_cast<double>(indices[b_i]) - 1.0 == 0.0) {
      k = 0.0;
    } else {
      k = std::fmod(static_cast<double>(indices[b_i]) - 1.0,
                    static_cast<double>(yk));
      if (k == 0.0) {
        k = 0.0;
      } else if (static_cast<double>(indices[b_i]) - 1.0 < 0.0) {
        k += static_cast<double>(yk);
      }
    }
    indices[b_i] = aux[static_cast<int>(k)];
  }
  copyCols.set_size(1, weights.size(1));
  yk = weights.size(1);
  for (i = 0; i < yk; i++) {
    copyCols[i] = false;
  }
  nx = weights.size(1);
  yk = 0;
  if (weights.size(1) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (b_i = 0; b_i < nx; b_i++) {
    boolean_T exitg1;
    b_k = yk + weights.size(0);
    i1 = yk;
    yk += weights.size(0);
    if ((i1 + 1 <= b_k) && (b_k > 2147483646)) {
      check_forloop_overflow_error();
    }
    exitg1 = false;
    while ((!exitg1) && (i1 + 1 <= b_k)) {
      if ((weights[i1] == 0.0) || std::isnan(weights[i1])) {
        i1++;
      } else {
        copyCols[b_i] = true;
        exitg1 = true;
      }
    }
  }
  yk = copyCols.size(1) - 1;
  nx = 0;
  for (b_i = 0; b_i <= yk; b_i++) {
    if (copyCols[b_i]) {
      nx++;
    }
  }
  r.set_size(1, nx);
  nx = 0;
  for (b_i = 0; b_i <= yk; b_i++) {
    if (copyCols[b_i]) {
      r[nx] = b_i + 1;
      nx++;
    }
  }
  nx = weights.size(0) - 1;
  absx.set_size(r.size(1), weights.size(0));
  for (i = 0; i <= nx; i++) {
    yk = r.size(1);
    for (b_i = 0; b_i < yk; b_i++) {
      absx[b_i + absx.size(0) * i] =
          weights[i + weights.size(0) * (r[b_i] - 1)];
    }
  }
  weights.set_size(absx.size(0), absx.size(1));
  yk = absx.size(0) * absx.size(1);
  for (i = 0; i < yk; i++) {
    weights[i] = absx[i];
  }
  yk = copyCols.size(1) - 1;
  nx = 0;
  for (b_i = 0; b_i <= yk; b_i++) {
    if (copyCols[b_i]) {
      nx++;
    }
  }
  r1.set_size(1, nx);
  nx = 0;
  for (b_i = 0; b_i <= yk; b_i++) {
    if (copyCols[b_i]) {
      r1[nx] = b_i + 1;
      nx++;
    }
  }
  nx = indices.size(0) - 1;
  b_indices.set_size(r1.size(1), indices.size(0));
  for (i = 0; i <= nx; i++) {
    yk = r1.size(1);
    for (b_i = 0; b_i < yk; b_i++) {
      b_indices[b_i + b_indices.size(0) * i] =
          indices[i + indices.size(0) * (r1[b_i] - 1)];
    }
  }
  indices.set_size(b_indices.size(0), b_indices.size(1));
  yk = b_indices.size(0) * b_indices.size(1);
  for (i = 0; i < yk; i++) {
    indices[i] = b_indices[i];
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &in
//                const ::coder::array<double, 2U> &weights
//                const ::coder::array<int, 2U> &indices
//                double out_length
//                ::coder::array<double, 2U> &out
// Return Type  : void
//
static void resizeAlongDim2D(const ::coder::array<double, 2U> &in,
                             const ::coder::array<double, 2U> &weights,
                             const ::coder::array<int, 2U> &indices,
                             double out_length, ::coder::array<double, 2U> &out)
{
  double sumVal1;
  int iv[2];
  int i;
  int i1;
  int k;
  int ndx;
  int outRInd;
  int sumVal1_tmp;
  int ub_loop;
  ub_loop = static_cast<int>(static_cast<double>(in.size(0) * in.size(1)) /
                             static_cast<double>(in.size(0))) -
            1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    sumVal1, i, outRInd, iv, ndx, i1, k, sumVal1_tmp)

  for (int inCInd = 0; inCInd <= ub_loop; inCInd++) {
    i = static_cast<int>(out_length);
    for (outRInd = 0; outRInd < i; outRInd++) {
      sumVal1 = 0.0;
      iv[0] = (*(int(*)[2])((::coder::array<double, 2U> *)&weights)->size())[0];
      iv[1] = (*(int(*)[2])((::coder::array<double, 2U> *)&weights)->size())[1];
      ndx = eml_sub2ind(iv, static_cast<double>(outRInd) + 1.0);
      //  Core - first dimension
      i1 = weights.size(0);
      for (k = 0; k < i1; k++) {
        sumVal1_tmp = (ndx + k) - 1;
        sumVal1 += weights[sumVal1_tmp] *
                   in[(indices[sumVal1_tmp] + in.size(0) * inCInd) - 1];
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
static void hc_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
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
// Arguments    : const ::coder::array<double, 2U> &Ain
//                const double varargin_1[2]
//                ::coder::array<double, 2U> &Bout
// Return Type  : void
//
namespace coder {
void imresize(const ::coder::array<double, 2U> &Ain, const double varargin_1[2],
              ::coder::array<double, 2U> &Bout)
{
  static rtRunTimeErrorInfo tc_emlrtRTEI{
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
    i_rtErrorWithMessageID("input number 1, A,", fb_emlrtRTEI.fName,
                           fb_emlrtRTEI.lineNo);
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
    hc_rtErrorWithMessageID(tc_emlrtRTEI.fName, tc_emlrtRTEI.lineNo);
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
    scale_idx_1 = outputSize_idx_0 / static_cast<double>(Ain.size(0));
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
