//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// formatSTFTOutput.cpp
//
// Code generation for function 'formatSTFTOutput'
//

// Include files
#include "formatSTFTOutput.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>
#include <string.h>

// Function Declarations
static int div_s32_sat(int numerator, int denominator);

// Function Definitions
static int div_s32_sat(int numerator, int denominator)
{
  int quotient;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    unsigned int b_denominator;
    unsigned int b_numerator;
    boolean_T quotientNeedsNegation;
    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    if (numerator < 0) {
      b_numerator = ~static_cast<unsigned int>(numerator) + 1U;
    } else {
      b_numerator = static_cast<unsigned int>(numerator);
    }
    if (denominator < 0) {
      b_denominator = ~static_cast<unsigned int>(denominator) + 1U;
    } else {
      b_denominator = static_cast<unsigned int>(denominator);
    }
    b_numerator /= b_denominator;
    if ((!quotientNeedsNegation) && (b_numerator >= 2147483647U)) {
      quotient = MAX_int32_T;
    } else if (quotientNeedsNegation && (b_numerator > 2147483647U)) {
      quotient = MIN_int32_T;
    } else if (quotientNeedsNegation) {
      quotient = -static_cast<int>(b_numerator);
    } else {
      quotient = static_cast<int>(b_numerator);
    }
  }
  return quotient;
}

namespace coder {
namespace signal {
namespace internal {
namespace stft {
void formatSTFTOutput(::coder::array<creal32_T, 2U> &S,
                      ::coder::array<double, 1U> &F,
                      const char opts_FreqRange[8], double opts_NumFreqSamples)
{
  static const char b[8]{'c', 'e', 'n', 't', 'e', 'r', 'e', 'd'};
  static const char b_b[8]{'t', 'w', 'o', 's', 'i', 'd', 'e', 'd'};
  array<creal32_T, 2U> buffer;
  int ret;
  ret = memcmp(&opts_FreqRange[0], &b[0], 8);
  if (ret == 0) {
    ret = 0;
  } else {
    ret = memcmp(&opts_FreqRange[0], &b_b[0], 8);
    if (ret == 0) {
      ret = 1;
    } else {
      ret = -1;
    }
  }
  switch (ret) {
  case 0: {
    double p;
    int i;
    if (S.size(0) == 0) {
      p = 0.0;
    } else {
      p = std::fmod(static_cast<double>(S.size(0)), 2.0);
    }
    if (p == 0.0) {
      int vspread;
      p = static_cast<double>(S.size(0)) / 2.0 - 1.0;
      vspread = 1;
      if (S.size(0) != 1) {
        vspread = 0;
      }
      if ((S.size(0) != 0) && (S.size(1) != 0) &&
          ((S.size(0) != 1) || (S.size(1) != 1))) {
        int i2;
        int ib;
        int npages;
        int ns;
        int vlend2;
        boolean_T shiftright;
        if (p < 0.0) {
          ns = static_cast<int>(-p);
          shiftright = false;
        } else {
          ns = static_cast<int>(p);
          shiftright = true;
        }
        if (ns > S.size(vspread)) {
          ns -= div_s32_sat(ns, S.size(vspread)) * S.size(vspread);
        }
        if (ns > (S.size(vspread) >> 1)) {
          ns = S.size(vspread) - ns;
          shiftright = !shiftright;
        }
        if ((S.size(0) == 0) || (S.size(1) == 0)) {
          vlend2 = 0;
        } else {
          ret = S.size(0);
          vlend2 = S.size(1);
          if (ret >= vlend2) {
            vlend2 = ret;
          }
        }
        ret = static_cast<int>(std::floor(static_cast<double>(vlend2) / 2.0));
        buffer.set_size(1, ret);
        for (i = 0; i < ret; i++) {
          buffer[i].re = 0.0F;
          buffer[i].im = 0.0F;
        }
        i = S.size(vspread);
        i2 = S.size(vspread);
        ib = 1;
        for (int k{0}; k < vspread; k++) {
          ib *= S.size(0);
        }
        npages = 1;
        ret = vspread + 2;
        for (int k{ret}; k < 3; k++) {
          npages *= S.size(1);
        }
        vlend2 = ib * S.size(vspread);
        if ((S.size(vspread) > 1) && (ns > 0)) {
          for (int b_i{0}; b_i < npages; b_i++) {
            ret = b_i * vlend2;
            for (vspread = 0; vspread < ib; vspread++) {
              int b_i1;
              b_i1 = ret + vspread;
              if (shiftright) {
                int i1;
                for (int k{0}; k < ns; k++) {
                  buffer[k] = S[b_i1 + ((k + i) - ns) * ib];
                }
                i1 = ns + 1;
                for (int k{i2}; k >= i1; k--) {
                  S[b_i1 + (k - 1) * ib] = S[b_i1 + ((k - ns) - 1) * ib];
                }
                for (int k{0}; k < ns; k++) {
                  S[b_i1 + k * ib] = buffer[k];
                }
              } else {
                int i1;
                for (int k{0}; k < ns; k++) {
                  buffer[k] = S[b_i1 + k * ib];
                }
                i1 = (i - ns) - 1;
                for (int k{0}; k <= i1; k++) {
                  S[b_i1 + k * ib] = S[b_i1 + (k + ns) * ib];
                }
                for (int k{0}; k < ns; k++) {
                  S[b_i1 + ((k + i) - ns) * ib] = buffer[k];
                }
              }
            }
          }
        }
      }
    } else if (S.size(0) > 1) {
      int npages;
      int vlend2;
      int vspread;
      vlend2 = S.size(0) / 2 - 1;
      npages = S.size(1) - 1;
      vspread = S.size(0);
      if ((vlend2 + 1) << 1 == S.size(0)) {
        int i2;
        i2 = 1;
        for (int b_i{0}; b_i <= npages; b_i++) {
          int b_i1;
          int ib;
          b_i1 = i2;
          i2 += vspread;
          ib = b_i1 + vlend2;
          for (int k{0}; k <= vlend2; k++) {
            float xtmp_im;
            float xtmp_re;
            ret = (b_i1 + k) - 1;
            xtmp_re = S[ret].re;
            xtmp_im = S[ret].im;
            i = ib + k;
            S[ret] = S[i];
            S[i].re = xtmp_re;
            S[i].im = xtmp_im;
          }
        }
      } else {
        int i2;
        i2 = 1;
        for (int b_i{0}; b_i <= npages; b_i++) {
          float xtmp_im;
          float xtmp_re;
          int b_i1;
          int ib;
          b_i1 = i2;
          i2 += vspread;
          ib = b_i1 + vlend2;
          xtmp_re = S[ib].re;
          xtmp_im = S[ib].im;
          for (int k{0}; k <= vlend2; k++) {
            int i1;
            i = ib + k;
            i1 = (b_i1 + k) - 1;
            S[i] = S[i1];
            S[i1] = S[i + 1];
          }
          ib = (ib + vlend2) + 1;
          S[ib].re = xtmp_re;
          S[ib].im = xtmp_im;
        }
      }
    }
    if (F.size(0) == 0) {
      p = 0.0;
    } else {
      p = std::fmod(static_cast<double>(F.size(0)), 2.0);
    }
    if (p == 0.0) {
      p = F[static_cast<int>(static_cast<double>(F.size(0)) / 2.0) - 1];
      ret = F.size(0);
      for (i = 0; i < ret; i++) {
        F[i] = F[i] - p;
      }
    } else {
      p = F[static_cast<int>((static_cast<double>(F.size(0)) + 1.0) / 2.0) - 1];
      ret = F.size(0);
      for (i = 0; i < ret; i++) {
        F[i] = F[i] - p;
      }
    }
  } break;
  case 1:
    break;
  default: {
    if (S.size(0) != opts_NumFreqSamples) {
      int vlend2;
      if (opts_NumFreqSamples < 1.0) {
        ret = 0;
      } else {
        ret = static_cast<int>(opts_NumFreqSamples);
      }
      vlend2 = S.size(1) - 1;
      for (int i{0}; i <= vlend2; i++) {
        for (int i1{0}; i1 < ret; i1++) {
          S[i1 + ret * i] = S[i1 + S.size(0) * i];
        }
      }
      S.set_size(ret, vlend2 + 1);
    }
    if (F.size(0) != opts_NumFreqSamples) {
      if (opts_NumFreqSamples < 1.0) {
        ret = 0;
      } else {
        ret = static_cast<int>(opts_NumFreqSamples);
      }
      F.set_size(ret);
    }
  } break;
  }
}

void formatSTFTOutput(::coder::array<creal_T, 3U> &S,
                      ::coder::array<double, 1U> &F,
                      const char opts_FreqRange[8], double opts_NumFreqSamples)
{
  static const char b[8]{'c', 'e', 'n', 't', 'e', 'r', 'e', 'd'};
  static const char b_b[8]{'t', 'w', 'o', 's', 'i', 'd', 'e', 'd'};
  array<creal_T, 2U> buffer;
  int ret;
  ret = memcmp(&opts_FreqRange[0], &b[0], 8);
  if (ret == 0) {
    ret = 0;
  } else {
    ret = memcmp(&opts_FreqRange[0], &b_b[0], 8);
    if (ret == 0) {
      ret = 1;
    } else {
      ret = -1;
    }
  }
  switch (ret) {
  case 0: {
    double xtmp_re;
    int i;
    if (S.size(0) == 0) {
      xtmp_re = 0.0;
    } else {
      xtmp_re = std::fmod(static_cast<double>(S.size(0)), 2.0);
    }
    if (xtmp_re == 0.0) {
      int vlend2;
      xtmp_re = static_cast<double>(S.size(0)) / 2.0 - 1.0;
      vlend2 = 1;
      if (S.size(0) != 1) {
        vlend2 = 0;
      } else if ((S.size(1) == 1) && (S.size(2) != 1)) {
        vlend2 = 2;
      }
      if ((S.size(0) != 0) && (S.size(1) != 0) &&
          ((S.size(0) != 1) || (S.size(1) != 1) || (S.size(2) != 1))) {
        int i2;
        int ib;
        int npages;
        int ns;
        int vspread;
        boolean_T shiftright;
        if (xtmp_re < 0.0) {
          ns = static_cast<int>(-xtmp_re);
          shiftright = false;
        } else {
          ns = static_cast<int>(xtmp_re);
          shiftright = true;
        }
        if (ns > S.size(vlend2)) {
          ns -= div_s32_sat(ns, S.size(vlend2)) * S.size(vlend2);
        }
        if (ns > (S.size(vlend2) >> 1)) {
          ns = S.size(vlend2) - ns;
          shiftright = !shiftright;
        }
        ret = S.size(0);
        if ((S.size(0) > 0) && ((S.size(1) == 0) || (S.size(1) > S.size(0)))) {
          ret = S.size(1);
        }
        if ((ret > 0) && (S.size(2) > ret)) {
          ret = S.size(2);
        }
        ret = static_cast<int>(std::floor(static_cast<double>(ret) / 2.0));
        buffer.set_size(1, ret);
        for (i = 0; i < ret; i++) {
          buffer[i].re = 0.0;
          buffer[i].im = 0.0;
        }
        i = S.size(vlend2);
        i2 = S.size(vlend2);
        ib = 1;
        for (int k{0}; k < vlend2; k++) {
          ib *= S.size(k);
        }
        npages = 1;
        ret = vlend2 + 2;
        for (int k{ret}; k < 4; k++) {
          npages *= S.size(k - 1);
        }
        vspread = ib * S.size(vlend2);
        if ((S.size(vlend2) > 1) && (ns > 0)) {
          for (int b_i{0}; b_i < npages; b_i++) {
            ret = b_i * vspread;
            for (vlend2 = 0; vlend2 < ib; vlend2++) {
              int b_i1;
              b_i1 = ret + vlend2;
              if (shiftright) {
                int i1;
                for (int k{0}; k < ns; k++) {
                  buffer[k] = S[b_i1 + ((k + i) - ns) * ib];
                }
                i1 = ns + 1;
                for (int k{i2}; k >= i1; k--) {
                  S[b_i1 + (k - 1) * ib] = S[b_i1 + ((k - ns) - 1) * ib];
                }
                for (int k{0}; k < ns; k++) {
                  S[b_i1 + k * ib] = buffer[k];
                }
              } else {
                int i1;
                for (int k{0}; k < ns; k++) {
                  buffer[k] = S[b_i1 + k * ib];
                }
                i1 = (i - ns) - 1;
                for (int k{0}; k <= i1; k++) {
                  S[b_i1 + k * ib] = S[b_i1 + (k + ns) * ib];
                }
                for (int k{0}; k < ns; k++) {
                  S[b_i1 + ((k + i) - ns) * ib] = buffer[k];
                }
              }
            }
          }
        }
      }
    } else if (S.size(0) > 1) {
      int npages;
      int vlend2;
      int vspread;
      vlend2 = S.size(0) / 2 - 1;
      npages = S.size(1) * S.size(2) - 1;
      vspread = S.size(0);
      if ((vlend2 + 1) << 1 == S.size(0)) {
        int i2;
        i2 = 1;
        for (int b_i{0}; b_i <= npages; b_i++) {
          int b_i1;
          int ib;
          b_i1 = i2;
          i2 += vspread;
          ib = b_i1 + vlend2;
          for (int k{0}; k <= vlend2; k++) {
            double xtmp_im;
            ret = (b_i1 + k) - 1;
            xtmp_re = S[ret].re;
            xtmp_im = S[ret].im;
            i = ib + k;
            S[ret] = S[i];
            S[i].re = xtmp_re;
            S[i].im = xtmp_im;
          }
        }
      } else {
        int i2;
        i2 = 1;
        for (int b_i{0}; b_i <= npages; b_i++) {
          double xtmp_im;
          int b_i1;
          int ib;
          b_i1 = i2;
          i2 += vspread;
          ib = b_i1 + vlend2;
          xtmp_re = S[ib].re;
          xtmp_im = S[ib].im;
          for (int k{0}; k <= vlend2; k++) {
            int i1;
            i = ib + k;
            i1 = (b_i1 + k) - 1;
            S[i] = S[i1];
            S[i1] = S[i + 1];
          }
          ib = (ib + vlend2) + 1;
          S[ib].re = xtmp_re;
          S[ib].im = xtmp_im;
        }
      }
    }
    if (F.size(0) == 0) {
      xtmp_re = 0.0;
    } else {
      xtmp_re = std::fmod(static_cast<double>(F.size(0)), 2.0);
    }
    if (xtmp_re == 0.0) {
      xtmp_re = F[static_cast<int>(static_cast<double>(F.size(0)) / 2.0) - 1];
      ret = F.size(0);
      for (i = 0; i < ret; i++) {
        F[i] = F[i] - xtmp_re;
      }
    } else {
      xtmp_re =
          F[static_cast<int>((static_cast<double>(F.size(0)) + 1.0) / 2.0) - 1];
      ret = F.size(0);
      for (i = 0; i < ret; i++) {
        F[i] = F[i] - xtmp_re;
      }
    }
  } break;
  case 1:
    break;
  default: {
    if (S.size(0) != opts_NumFreqSamples) {
      int i2;
      int vlend2;
      int vspread;
      if (opts_NumFreqSamples < 1.0) {
        ret = 0;
      } else {
        ret = static_cast<int>(opts_NumFreqSamples);
      }
      vlend2 = S.size(1) - 1;
      vspread = S.size(2) - 1;
      i2 = S.size(1);
      for (int i{0}; i <= vspread; i++) {
        for (int i1{0}; i1 < i2; i1++) {
          for (int ib{0}; ib < ret; ib++) {
            S[(ib + ret * i1) + ret * (vlend2 + 1) * i] =
                S[(ib + S.size(0) * i1) + S.size(0) * S.size(1) * i];
          }
        }
      }
      S.set_size(ret, vlend2 + 1, vspread + 1);
    }
    if (F.size(0) != opts_NumFreqSamples) {
      if (opts_NumFreqSamples < 1.0) {
        ret = 0;
      } else {
        ret = static_cast<int>(opts_NumFreqSamples);
      }
      F.set_size(ret);
    }
  } break;
  }
}

} // namespace stft
} // namespace internal
} // namespace signal
} // namespace coder

// End of code generation (formatSTFTOutput.cpp)
