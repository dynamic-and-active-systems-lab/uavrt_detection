//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: imresize.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 20-Oct-2022 20:46:49
//

// Include Files
#include "imresize.h"
#include "rt_nonfinite.h"
#include "sum.h"
#include "uavrt_detection_rtwutil.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>

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
  int i;
  int i1;
  int k;
  int linearInds;
  int outCInd;
  int pixelIndex;
  int pixelIndex_tmp;
  int ub_loop;
  ub_loop = in.size(0) - 1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    pixelIndex, linearInds, sumVal1, i, outCInd, i1, k, pixelIndex_tmp)

  for (int inRInd = 0; inRInd <= ub_loop; inRInd++) {
    i = static_cast<int>(out_length);
    for (outCInd = 0; outCInd < i; outCInd++) {
      sumVal1 = 0.0;
      //  Core - second dimension
      i1 = weights.size(0);
      linearInds = weights.size(0) * outCInd + 1;
      for (k = 0; k < i1; k++) {
        pixelIndex_tmp = (linearInds + k) - 1;
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
  int c_k;
  int i;
  int nx;
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
  for (b_k = 0; b_k < nx; b_k++) {
    x[b_k] = std::floor(x[b_k]);
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
  for (b_k = 2; b_k <= nx; b_k++) {
    yk++;
    aux[b_k - 1] = yk;
  }
  indices.set_size(left.size(0), aux.size(1));
  if (left.size(0) != 0) {
    i = aux.size(1) - 1;
    nx = (left.size(0) != 1);
    for (b_k = 0; b_k <= i; b_k++) {
      b_i = indices.size(0) - 1;
      for (c_k = 0; c_k <= b_i; c_k++) {
        indices[c_k + indices.size(0) * b_k] = left[nx * c_k] + aux[b_k];
      }
    }
  }
  absx.set_size(indices.size(0), indices.size(1));
  yk = indices.size(0) * indices.size(1);
  for (i = 0; i < yk; i++) {
    absx[i] = indices[i];
  }
  nx = absx.size(0);
  yk = u.size(0);
  if (nx <= yk) {
    yk = nx;
  }
  if (absx.size(0) == 1) {
    yk = u.size(0);
  } else if (u.size(0) == 1) {
    yk = absx.size(0);
  } else if (u.size(0) == absx.size(0)) {
    yk = u.size(0);
  }
  b_x.set_size(yk, absx.size(1));
  nx = absx.size(0);
  yk = u.size(0);
  if (nx <= yk) {
    yk = nx;
  }
  if (absx.size(0) == 1) {
    yk = u.size(0);
  } else if (u.size(0) == 1) {
    yk = absx.size(0);
  } else if (u.size(0) == absx.size(0)) {
    yk = u.size(0);
  }
  if (yk != 0) {
    i = absx.size(1) - 1;
    nx = (u.size(0) != 1);
    yk = (absx.size(0) != 1);
    for (b_k = 0; b_k <= i; b_k++) {
      b_i = b_x.size(0) - 1;
      for (c_k = 0; c_k <= b_i; c_k++) {
        b_x[c_k + b_x.size(0) * b_k] =
            u[nx * c_k] - absx[yk * c_k + absx.size(0) * b_k];
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
  for (b_k = 0; b_k < nx; b_k++) {
    absx[b_k] = std::abs(b_x[b_k]);
  }
  absx2.set_size(absx.size(0), absx.size(1));
  nx = absx.size(0) * absx.size(1);
  for (b_k = 0; b_k < nx; b_k++) {
    absx2[b_k] = absx[b_k] * absx[b_k];
  }
  weights.set_size(absx.size(0), absx.size(1));
  nx = absx.size(0) * absx.size(1);
  for (b_k = 0; b_k < nx; b_k++) {
    weights[b_k] = rt_powd_snf(absx[b_k], 3.0);
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
  nx = u.size(0);
  yk = weights.size(0);
  if (nx <= yk) {
    yk = nx;
  }
  if (u.size(0) == 1) {
    nx = weights.size(0);
  } else if (weights.size(0) == 1) {
    nx = u.size(0);
  } else if (weights.size(0) == u.size(0)) {
    nx = weights.size(0);
  } else {
    nx = yk;
  }
  yk = weights.size(1);
  weights.set_size(nx, yk);
  if (nx != 0) {
    i = yk - 1;
    nx = (absx.size(0) != 1);
    yk = (u.size(0) != 1);
    for (b_k = 0; b_k <= i; b_k++) {
      b_i = weights.size(0) - 1;
      for (c_k = 0; c_k <= b_i; c_k++) {
        weights[c_k + weights.size(0) * b_k] =
            absx[nx * c_k + absx.size(0) * b_k] / u[yk * c_k];
      }
    }
  }
  //  Create the auxiliary matrix:
  yk = in_length << 1;
  aux.set_size(1, yk);
  aux[0] = 1;
  aux[in_length] = in_length;
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
  for (b_i = 0; b_i < nx; b_i++) {
    boolean_T exitg1;
    c_k = yk + weights.size(0);
    b_k = yk;
    yk += weights.size(0);
    exitg1 = false;
    while ((!exitg1) && (b_k + 1 <= c_k)) {
      if ((weights[b_k] == 0.0) || std::isnan(weights[b_k])) {
        b_k++;
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
  nx = weights.size(0);
  absx.set_size(r.size(1), weights.size(0));
  for (i = 0; i < nx; i++) {
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
  nx = indices.size(0);
  b_indices.set_size(r1.size(1), indices.size(0));
  for (i = 0; i < nx; i++) {
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
  int i;
  int i1;
  int k;
  int linearInds;
  int outRInd;
  int sumVal1_tmp;
  int ub_loop;
  ub_loop = static_cast<int>(static_cast<double>(in.size(0) * in.size(1)) /
                             static_cast<double>(in.size(0))) -
            1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    linearInds, sumVal1, i, outRInd, i1, k, sumVal1_tmp)

  for (int inCInd = 0; inCInd <= ub_loop; inCInd++) {
    i = static_cast<int>(out_length);
    for (outRInd = 0; outRInd < i; outRInd++) {
      sumVal1 = 0.0;
      i1 = weights.size(0);
      linearInds = weights.size(0) * outRInd + 1;
      //  Core - first dimension
      for (k = 0; k < i1; k++) {
        sumVal1_tmp = (linearInds + k) - 1;
        sumVal1 += weights[sumVal1_tmp] *
                   in[(indices[sumVal1_tmp] + in.size(0) * inCInd) - 1];
      }
      out[outRInd + out.size(0) * inCInd] = sumVal1;
    }
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &Ain
//                const double varargin_1[2]
//                ::coder::array<double, 2U> &Bout
// Return Type  : void
//
void imresize(const ::coder::array<double, 2U> &Ain, const double varargin_1[2],
              ::coder::array<double, 2U> &Bout)
{
  array<double, 2U> out;
  array<double, 2U> weights;
  array<int, 2U> indices;
  double outputSize_idx_0;
  double outputSize_idx_1;
  double scale_idx_0;
  double scale_idx_1;
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
