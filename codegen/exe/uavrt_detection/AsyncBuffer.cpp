//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: AsyncBuffer.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 12:48:10
//

// Include Files
#include "AsyncBuffer.h"
#include "AsyncBuffercgHelper.h"
#include "colon.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>
#include <cstring>

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
namespace coder {
namespace dsp {
void AsyncBuffer::matlabCodegenDestructor()
{
  if (!matlabCodegenIsDeleted) {
    matlabCodegenIsDeleted = true;
  }
}

//
// Arguments    : void
// Return Type  : void
//
void b_AsyncBuffer::matlabCodegenDestructor()
{
  if (!matlabCodegenIsDeleted) {
    matlabCodegenIsDeleted = true;
  }
}

//
// Arguments    : void
// Return Type  : AsyncBuffer
//
AsyncBuffer::AsyncBuffer()
{
  matlabCodegenIsDeleted = true;
}

//
// Arguments    : void
// Return Type  : b_AsyncBuffer
//
b_AsyncBuffer::b_AsyncBuffer()
{
  matlabCodegenIsDeleted = true;
}

//
// Arguments    : void
// Return Type  : void
//
AsyncBuffer::~AsyncBuffer()
{
  matlabCodegenDestructor();
}

//
// Arguments    : void
// Return Type  : void
//
b_AsyncBuffer::~b_AsyncBuffer()
{
  matlabCodegenDestructor();
}

//
// Arguments    : void
// Return Type  : AsyncBuffer *
//
AsyncBuffer *AsyncBuffer::init()
{
  AsyncBuffer *obj;
  obj = this;
  obj->pBuffer.NumChannels = -1;
  obj->pBuffer.ReadPointer = 1;
  obj->pBuffer.WritePointer = 2;
  obj->pBuffer.isInitialized = 0;
  obj->pBuffer.matlabCodegenIsDeleted = false;
  obj->matlabCodegenIsDeleted = false;
  return obj;
}

//
// Arguments    : double numRows
//                ::coder::array<creal32_T, 1U> &out
// Return Type  : void
//
void b_AsyncBuffer::read(double numRows, ::coder::array<creal32_T, 1U> &out)
{
  internal::b_AsyncBuffercgHelper *obj;
  array<creal32_T, 1U> b_out;
  array<int, 2U> r;
  array<int, 2U> readIdx;
  array<int, 2U> y;
  double d;
  int b_qY;
  int c;
  int i;
  int n;
  int qY;
  int rPtr;
  int wPtr;
  int yk;
  d = std::round(numRows);
  if (d < 2.147483648E+9) {
    if (d >= -2.147483648E+9) {
      i = static_cast<int>(d);
    } else {
      i = MIN_int32_T;
    }
  } else if (d >= 2.147483648E+9) {
    i = MAX_int32_T;
  } else {
    i = 0;
  }
  obj = &pBuffer;
  wPtr = pBuffer.WritePointer;
  qY = 0;
  n = pBuffer.ReadPointer;
  if (n > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr = n + 1;
  }
  if (rPtr > 49621) {
    rPtr = 1;
  }
  if ((rPtr < 0) && (i < MIN_int32_T - rPtr)) {
    b_qY = MIN_int32_T;
  } else if ((rPtr > 0) && (i > MAX_int32_T - rPtr)) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = rPtr + i;
  }
  if (b_qY < -2147483647) {
    b_qY = MIN_int32_T;
  } else {
    b_qY--;
  }
  c = b_qY;
  if (b_qY > 49621) {
    c = b_qY - 49621;
    y.set_size(1, b_qY - 49621);
    y[0] = 1;
    yk = 1;
    for (int k{2}; k <= c; k++) {
      yk++;
      y[k - 1] = yk;
    }
    if (rPtr > 49621) {
      n = 0;
    } else {
      unsigned int u;
      if (rPtr < 0) {
        u = 49621U - static_cast<unsigned int>(rPtr);
      } else {
        u = static_cast<unsigned int>(49621 - rPtr);
      }
      n = static_cast<int>(u) + 1;
    }
    r.set_size(1, n);
    if (n > 0) {
      r[0] = rPtr;
      yk = rPtr;
      for (int k{2}; k <= n; k++) {
        yk++;
        r[k - 1] = yk;
      }
    }
    readIdx.set_size(1, r.size(1) + y.size(1));
    n = r.size(1);
    for (yk = 0; yk < n; yk++) {
      readIdx[yk] = r[yk];
    }
    n = y.size(1);
    for (yk = 0; yk < n; yk++) {
      readIdx[yk + r.size(1)] = y[yk];
    }
    if (rPtr <= wPtr) {
      if (wPtr < -2147434026) {
        qY = MAX_int32_T;
      } else {
        qY = 49621 - wPtr;
      }
      if (qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY++;
      }
      if ((qY < 0) && (b_qY - 49621 < MIN_int32_T - qY)) {
        qY = MIN_int32_T;
      } else if ((qY > 0) && (b_qY - 49621 > MAX_int32_T - qY)) {
        qY = MAX_int32_T;
      } else {
        qY = (qY + b_qY) - 49621;
      }
    } else if (wPtr <= b_qY - 49621) {
      if (wPtr < b_qY + 2147434028) {
        b_qY = MAX_int32_T;
      } else {
        b_qY = (b_qY - wPtr) - 49621;
      }
      if (b_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = b_qY + 1;
      }
    }
  } else {
    if (b_qY < rPtr) {
      n = 0;
    } else {
      n = (b_qY - rPtr) + 1;
    }
    readIdx.set_size(1, n);
    if (n > 0) {
      readIdx[0] = rPtr;
      yk = rPtr;
      for (int k{2}; k <= n; k++) {
        yk++;
        readIdx[k - 1] = yk;
      }
    }
    if ((rPtr <= wPtr) && (wPtr <= b_qY)) {
      if ((b_qY >= 0) && (wPtr < b_qY - MAX_int32_T)) {
        b_qY = MAX_int32_T;
      } else if ((b_qY < 0) && (wPtr > b_qY - MIN_int32_T)) {
        b_qY = MIN_int32_T;
      } else {
        b_qY -= wPtr;
      }
      if (b_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = b_qY + 1;
      }
    }
  }
  b_out.set_size(readIdx.size(1));
  n = readIdx.size(1);
  for (yk = 0; yk < n; yk++) {
    b_out[yk] = obj->Cache[readIdx[yk] - 1];
  }
  if (qY != 0) {
    if ((i >= 0) && (qY < i - MAX_int32_T)) {
      b_qY = MAX_int32_T;
    } else if ((i < 0) && (qY > i - MIN_int32_T)) {
      b_qY = MIN_int32_T;
    } else {
      b_qY = i - qY;
    }
    if (b_qY > 2147483646) {
      b_qY = MAX_int32_T;
    } else {
      b_qY++;
    }
    if (b_qY > i) {
      b_qY = 1;
    }
    for (i = 0; i < qY; i++) {
      yk = (b_qY + i) - 1;
      b_out[yk].re = 0.0F;
      b_out[yk].im = 0.0F;
    }
  }
  out.set_size(b_out.size(0));
  n = b_out.size(0);
  for (i = 0; i < n; i++) {
    out[i] = b_out[i];
  }
  n = pBuffer.WritePointer;
  if (n < -2147483647) {
    b_qY = MIN_int32_T;
  } else {
    b_qY = n - 1;
  }
  n = pBuffer.CumulativeUnderrun;
  if ((n < 0) && (qY < MIN_int32_T - n)) {
    n = MIN_int32_T;
  } else if ((n > 0) && (qY > MAX_int32_T - n)) {
    n = MAX_int32_T;
  } else {
    n += qY;
  }
  pBuffer.CumulativeUnderrun = n;
  if (qY != 0) {
    pBuffer.ReadPointer = b_qY;
  } else {
    pBuffer.ReadPointer = c;
  }
}

//
// Arguments    : double numRows
//                ::coder::array<double, 1U> &out
// Return Type  : void
//
void AsyncBuffer::read(double numRows, ::coder::array<double, 1U> &out)
{
  internal::AsyncBuffercgHelper *obj;
  array<double, 1U> b_out;
  array<int, 2U> r;
  array<int, 2U> readIdx;
  array<int, 2U> y;
  double d;
  int b_qY;
  int c;
  int i;
  int n;
  int qY;
  int rPtr;
  int wPtr;
  int yk;
  d = std::round(numRows);
  if (d < 2.147483648E+9) {
    if (d >= -2.147483648E+9) {
      i = static_cast<int>(d);
    } else {
      i = MIN_int32_T;
    }
  } else if (d >= 2.147483648E+9) {
    i = MAX_int32_T;
  } else {
    i = 0;
  }
  obj = &pBuffer;
  wPtr = pBuffer.WritePointer;
  qY = 0;
  n = pBuffer.ReadPointer;
  if (n > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr = n + 1;
  }
  if (rPtr > 49621) {
    rPtr = 1;
  }
  if ((rPtr < 0) && (i < MIN_int32_T - rPtr)) {
    b_qY = MIN_int32_T;
  } else if ((rPtr > 0) && (i > MAX_int32_T - rPtr)) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = rPtr + i;
  }
  if (b_qY < -2147483647) {
    b_qY = MIN_int32_T;
  } else {
    b_qY--;
  }
  c = b_qY;
  if (b_qY > 49621) {
    c = b_qY - 49621;
    y.set_size(1, b_qY - 49621);
    y[0] = 1;
    yk = 1;
    for (int k{2}; k <= c; k++) {
      yk++;
      y[k - 1] = yk;
    }
    if (rPtr > 49621) {
      n = 0;
    } else {
      unsigned int u;
      if (rPtr < 0) {
        u = 49621U - static_cast<unsigned int>(rPtr);
      } else {
        u = static_cast<unsigned int>(49621 - rPtr);
      }
      n = static_cast<int>(u) + 1;
    }
    r.set_size(1, n);
    if (n > 0) {
      r[0] = rPtr;
      yk = rPtr;
      for (int k{2}; k <= n; k++) {
        yk++;
        r[k - 1] = yk;
      }
    }
    readIdx.set_size(1, r.size(1) + y.size(1));
    n = r.size(1);
    for (yk = 0; yk < n; yk++) {
      readIdx[yk] = r[yk];
    }
    n = y.size(1);
    for (yk = 0; yk < n; yk++) {
      readIdx[yk + r.size(1)] = y[yk];
    }
    if (rPtr <= wPtr) {
      if (wPtr < -2147434026) {
        qY = MAX_int32_T;
      } else {
        qY = 49621 - wPtr;
      }
      if (qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY++;
      }
      if ((qY < 0) && (b_qY - 49621 < MIN_int32_T - qY)) {
        qY = MIN_int32_T;
      } else if ((qY > 0) && (b_qY - 49621 > MAX_int32_T - qY)) {
        qY = MAX_int32_T;
      } else {
        qY = (qY + b_qY) - 49621;
      }
    } else if (wPtr <= b_qY - 49621) {
      if (wPtr < b_qY + 2147434028) {
        b_qY = MAX_int32_T;
      } else {
        b_qY = (b_qY - wPtr) - 49621;
      }
      if (b_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = b_qY + 1;
      }
    }
  } else {
    if (b_qY < rPtr) {
      n = 0;
    } else {
      n = (b_qY - rPtr) + 1;
    }
    readIdx.set_size(1, n);
    if (n > 0) {
      readIdx[0] = rPtr;
      yk = rPtr;
      for (int k{2}; k <= n; k++) {
        yk++;
        readIdx[k - 1] = yk;
      }
    }
    if ((rPtr <= wPtr) && (wPtr <= b_qY)) {
      if ((b_qY >= 0) && (wPtr < b_qY - MAX_int32_T)) {
        b_qY = MAX_int32_T;
      } else if ((b_qY < 0) && (wPtr > b_qY - MIN_int32_T)) {
        b_qY = MIN_int32_T;
      } else {
        b_qY -= wPtr;
      }
      if (b_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = b_qY + 1;
      }
    }
  }
  b_out.set_size(readIdx.size(1));
  n = readIdx.size(1);
  for (yk = 0; yk < n; yk++) {
    b_out[yk] = obj->Cache[readIdx[yk] - 1];
  }
  if (qY != 0) {
    if ((i >= 0) && (qY < i - MAX_int32_T)) {
      b_qY = MAX_int32_T;
    } else if ((i < 0) && (qY > i - MIN_int32_T)) {
      b_qY = MIN_int32_T;
    } else {
      b_qY = i - qY;
    }
    if (b_qY > 2147483646) {
      b_qY = MAX_int32_T;
    } else {
      b_qY++;
    }
    if (b_qY > i) {
      b_qY = 1;
    }
    for (i = 0; i < qY; i++) {
      b_out[(b_qY + i) - 1] = 0.0;
    }
  }
  out.set_size(b_out.size(0));
  n = b_out.size(0);
  for (i = 0; i < n; i++) {
    out[i] = b_out[i];
  }
  n = pBuffer.WritePointer;
  if (n < -2147483647) {
    b_qY = MIN_int32_T;
  } else {
    b_qY = n - 1;
  }
  n = pBuffer.CumulativeUnderrun;
  if ((n < 0) && (qY < MIN_int32_T - n)) {
    n = MIN_int32_T;
  } else if ((n > 0) && (qY > MAX_int32_T - n)) {
    n = MAX_int32_T;
  } else {
    n += qY;
  }
  pBuffer.CumulativeUnderrun = n;
  if (qY != 0) {
    pBuffer.ReadPointer = b_qY;
  } else {
    pBuffer.ReadPointer = c;
  }
}

//
// Arguments    : double numRows
//                double overlap
//                ::coder::array<creal32_T, 1U> &out
// Return Type  : void
//
void b_AsyncBuffer::read(double numRows, double overlap,
                         ::coder::array<creal32_T, 1U> &out)
{
  array<creal32_T, 1U> b_out;
  array<int, 2U> r;
  array<int, 2U> readIdx;
  array<int, 2U> y;
  double d;
  int b_qY;
  int c;
  int c_qY;
  int n;
  int numRowsCast;
  int qY;
  int rPtr;
  int wPtr_tmp;
  int yk;
  d = std::round(numRows);
  if (d < 2.147483648E+9) {
    if (d >= -2.147483648E+9) {
      numRowsCast = static_cast<int>(d);
    } else {
      numRowsCast = MIN_int32_T;
    }
  } else if (d >= 2.147483648E+9) {
    numRowsCast = MAX_int32_T;
  } else {
    numRowsCast = 0;
  }
  d = std::round(overlap);
  if (d < 2.147483648E+9) {
    if (d >= -2.147483648E+9) {
      n = static_cast<int>(d);
    } else {
      n = MIN_int32_T;
    }
  } else if (d >= 2.147483648E+9) {
    n = MAX_int32_T;
  } else {
    n = 0;
  }
  wPtr_tmp = pBuffer.WritePointer;
  qY = 0;
  b_qY = 0;
  yk = pBuffer.ReadPointer;
  if (yk > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr = yk + 1;
  }
  if (rPtr > 49621) {
    rPtr = 1;
  }
  if (n == 0) {
    if ((rPtr < 0) && (numRowsCast < MIN_int32_T - rPtr)) {
      c_qY = MIN_int32_T;
    } else if ((rPtr > 0) && (numRowsCast > MAX_int32_T - rPtr)) {
      c_qY = MAX_int32_T;
    } else {
      c_qY = rPtr + numRowsCast;
    }
    if (c_qY < -2147483647) {
      c_qY = MIN_int32_T;
    } else {
      c_qY--;
    }
    c = c_qY;
    if (c_qY > 49621) {
      c = c_qY - 49621;
      y.set_size(1, c_qY - 49621);
      y[0] = 1;
      yk = 1;
      for (int k{2}; k <= c; k++) {
        yk++;
        y[k - 1] = yk;
      }
      eml_integer_colon_dispatcher(rPtr, r);
      readIdx.set_size(1, r.size(1) + y.size(1));
      n = r.size(1);
      for (yk = 0; yk < n; yk++) {
        readIdx[yk] = r[yk];
      }
      n = y.size(1);
      for (yk = 0; yk < n; yk++) {
        readIdx[yk + r.size(1)] = y[yk];
      }
      if (rPtr <= wPtr_tmp) {
        if (wPtr_tmp < -2147434026) {
          qY = MAX_int32_T;
        } else {
          qY = 49621 - wPtr_tmp;
        }
        if (qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY++;
        }
        if ((qY < 0) && (c_qY - 49621 < MIN_int32_T - qY)) {
          qY = MIN_int32_T;
        } else if ((qY > 0) && (c_qY - 49621 > MAX_int32_T - qY)) {
          qY = MAX_int32_T;
        } else {
          qY = (qY + c_qY) - 49621;
        }
      } else if (wPtr_tmp <= c_qY - 49621) {
        if (wPtr_tmp < c_qY + 2147434028) {
          c_qY = MAX_int32_T;
        } else {
          c_qY = (c_qY - wPtr_tmp) - 49621;
        }
        if (c_qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY = c_qY + 1;
        }
      }
    } else {
      if (c_qY < rPtr) {
        n = 0;
      } else {
        n = (c_qY - rPtr) + 1;
      }
      readIdx.set_size(1, n);
      if (n > 0) {
        readIdx[0] = rPtr;
        yk = rPtr;
        for (int k{2}; k <= n; k++) {
          yk++;
          readIdx[k - 1] = yk;
        }
      }
      if ((rPtr <= wPtr_tmp) && (wPtr_tmp <= c_qY)) {
        if ((c_qY >= 0) && (wPtr_tmp < c_qY - MAX_int32_T)) {
          c_qY = MAX_int32_T;
        } else if ((c_qY < 0) && (wPtr_tmp > c_qY - MIN_int32_T)) {
          c_qY = MIN_int32_T;
        } else {
          c_qY -= wPtr_tmp;
        }
        if (c_qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY = c_qY + 1;
        }
      }
    }
  } else {
    int qY_tmp;
    if ((rPtr >= 0) && (n < rPtr - MAX_int32_T)) {
      qY_tmp = MAX_int32_T;
      c_qY = MAX_int32_T;
    } else if ((rPtr < 0) && (n > rPtr - MIN_int32_T)) {
      qY_tmp = MIN_int32_T;
      c_qY = MIN_int32_T;
    } else {
      qY_tmp = rPtr - n;
      c_qY = qY_tmp;
    }
    if ((c_qY < 0) && (numRowsCast < MIN_int32_T - c_qY)) {
      c_qY = MIN_int32_T;
    } else if ((c_qY > 0) && (numRowsCast > MAX_int32_T - c_qY)) {
      c_qY = MAX_int32_T;
    } else {
      c_qY += numRowsCast;
    }
    if (c_qY < -2147483647) {
      c_qY = MIN_int32_T;
    } else {
      c_qY--;
    }
    c = c_qY;
    if (qY_tmp < 1) {
      if (c_qY < 1) {
        n = 0;
      } else {
        n = c_qY;
      }
      y.set_size(1, n);
      if (n > 0) {
        y[0] = 1;
        yk = 1;
        for (int k{2}; k <= n; k++) {
          yk++;
          y[k - 1] = yk;
        }
      }
      eml_integer_colon_dispatcher(qY_tmp + 49621, r);
      readIdx.set_size(1, r.size(1) + y.size(1));
      n = r.size(1);
      for (yk = 0; yk < n; yk++) {
        readIdx[yk] = r[yk];
      }
      n = y.size(1);
      for (yk = 0; yk < n; yk++) {
        readIdx[yk + r.size(1)] = y[yk];
      }
      if ((rPtr <= wPtr_tmp) && (wPtr_tmp <= c_qY)) {
        if ((c_qY >= 0) && (wPtr_tmp < c_qY - MAX_int32_T)) {
          c_qY = MAX_int32_T;
        } else if ((c_qY < 0) && (wPtr_tmp > c_qY - MIN_int32_T)) {
          c_qY = MIN_int32_T;
        } else {
          c_qY -= wPtr_tmp;
        }
        if (c_qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY = c_qY + 1;
        }
      } else if (wPtr_tmp < rPtr) {
        if (qY_tmp + 49621 < -2147434026) {
          c_qY = MAX_int32_T;
        } else {
          c_qY = -qY_tmp;
        }
        if (c_qY > 2147483646) {
          c_qY = MAX_int32_T;
        } else {
          c_qY++;
        }
        if ((c_qY < 0) && (wPtr_tmp < MIN_int32_T - c_qY)) {
          b_qY = MIN_int32_T;
        } else if ((c_qY > 0) && (wPtr_tmp > MAX_int32_T - c_qY)) {
          b_qY = MAX_int32_T;
        } else {
          b_qY = c_qY + wPtr_tmp;
        }
      } else if (wPtr_tmp > qY_tmp + 49621) {
        if ((wPtr_tmp >= 0) && (qY_tmp + 49621 < wPtr_tmp - MAX_int32_T)) {
          c_qY = MAX_int32_T;
        } else if ((wPtr_tmp < 0) &&
                   (qY_tmp + 49621 > wPtr_tmp - MIN_int32_T)) {
          c_qY = MIN_int32_T;
        } else {
          c_qY = (wPtr_tmp - qY_tmp) - 49621;
        }
        if (c_qY > 2147483646) {
          b_qY = MAX_int32_T;
        } else {
          b_qY = c_qY + 1;
        }
      }
    } else if (c_qY > 49621) {
      c = c_qY - 49621;
      y.set_size(1, c_qY - 49621);
      y[0] = 1;
      yk = 1;
      for (int k{2}; k <= c; k++) {
        yk++;
        y[k - 1] = yk;
      }
      eml_integer_colon_dispatcher(qY_tmp, r);
      readIdx.set_size(1, r.size(1) + y.size(1));
      n = r.size(1);
      for (yk = 0; yk < n; yk++) {
        readIdx[yk] = r[yk];
      }
      n = y.size(1);
      for (yk = 0; yk < n; yk++) {
        readIdx[yk + r.size(1)] = y[yk];
      }
      if (rPtr <= wPtr_tmp) {
        if (wPtr_tmp < -2147434026) {
          qY = MAX_int32_T;
        } else {
          qY = 49621 - wPtr_tmp;
        }
        if (qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY++;
        }
        if ((qY < 0) && (c_qY - 49621 < MIN_int32_T - qY)) {
          qY = MIN_int32_T;
        } else if ((qY > 0) && (c_qY - 49621 > MAX_int32_T - qY)) {
          qY = MAX_int32_T;
        } else {
          qY = (qY + c_qY) - 49621;
        }
      } else if (wPtr_tmp <= c_qY - 49621) {
        if (wPtr_tmp < c_qY + 2147434028) {
          c_qY = MAX_int32_T;
        } else {
          c_qY = (c_qY - wPtr_tmp) - 49621;
        }
        if (c_qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY = c_qY + 1;
        }
      } else if ((qY_tmp < wPtr_tmp) && (wPtr_tmp < rPtr)) {
        b_qY = (wPtr_tmp - qY_tmp) + 1;
      }
    } else {
      if (c_qY < qY_tmp) {
        n = 0;
      } else {
        n = (c_qY - qY_tmp) + 1;
      }
      readIdx.set_size(1, n);
      if (n > 0) {
        readIdx[0] = qY_tmp;
        yk = qY_tmp;
        for (int k{2}; k <= n; k++) {
          yk++;
          readIdx[k - 1] = yk;
        }
      }
      if ((rPtr <= wPtr_tmp) && (wPtr_tmp <= c_qY)) {
        if ((c_qY >= 0) && (wPtr_tmp < c_qY - MAX_int32_T)) {
          c_qY = MAX_int32_T;
        } else if ((c_qY < 0) && (wPtr_tmp > c_qY - MIN_int32_T)) {
          c_qY = MIN_int32_T;
        } else {
          c_qY -= wPtr_tmp;
        }
        if (c_qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY = c_qY + 1;
        }
      } else if ((qY_tmp <= wPtr_tmp) && (wPtr_tmp < rPtr)) {
        b_qY = (wPtr_tmp - qY_tmp) + 1;
      }
    }
  }
  b_out.set_size(readIdx.size(1));
  n = readIdx.size(1);
  for (yk = 0; yk < n; yk++) {
    b_out[yk] = pBuffer.Cache[readIdx[yk] - 1];
  }
  if (qY != 0) {
    if ((numRowsCast >= 0) && (qY < numRowsCast - MAX_int32_T)) {
      c_qY = MAX_int32_T;
    } else if ((numRowsCast < 0) && (qY > numRowsCast - MIN_int32_T)) {
      c_qY = MIN_int32_T;
    } else {
      c_qY = numRowsCast - qY;
    }
    if (c_qY > 2147483646) {
      c_qY = MAX_int32_T;
    } else {
      c_qY++;
    }
    if (c_qY > numRowsCast) {
      c_qY = 1;
    }
    for (yk = 0; yk < qY; yk++) {
      n = (c_qY + yk) - 1;
      b_out[n].re = 0.0F;
      b_out[n].im = 0.0F;
    }
  } else if (b_qY != 0) {
    if (b_qY == numRowsCast) {
      b_out.set_size(b_qY);
      for (yk = 0; yk < b_qY; yk++) {
        b_out[yk].re = 0.0F;
        b_out[yk].im = 0.0F;
      }
    } else {
      for (yk = 0; yk < b_qY; yk++) {
        b_out[yk].re = 0.0F;
        b_out[yk].im = 0.0F;
      }
    }
  }
  out.set_size(b_out.size(0));
  n = b_out.size(0);
  for (yk = 0; yk < n; yk++) {
    out[yk] = b_out[yk];
  }
  if (wPtr_tmp < -2147483647) {
    c_qY = MIN_int32_T;
  } else {
    c_qY = wPtr_tmp - 1;
  }
  yk = pBuffer.CumulativeUnderrun;
  if ((yk < 0) && (qY < MIN_int32_T - yk)) {
    b_qY = MIN_int32_T;
  } else if ((yk > 0) && (qY > MAX_int32_T - yk)) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = yk + qY;
  }
  pBuffer.CumulativeUnderrun = b_qY;
  if (qY != 0) {
    pBuffer.ReadPointer = c_qY;
  } else {
    pBuffer.ReadPointer = c;
  }
}

//
// Arguments    : double numRows
//                double overlap
//                ::coder::array<double, 1U> &out
// Return Type  : void
//
void AsyncBuffer::read(double numRows, double overlap,
                       ::coder::array<double, 1U> &out)
{
  array<double, 1U> b_out;
  array<int, 2U> r;
  array<int, 2U> readIdx;
  array<int, 2U> y;
  double d;
  int b_qY;
  int c;
  int c_qY;
  int n;
  int numRowsCast;
  int qY;
  int rPtr;
  int wPtr_tmp;
  int yk;
  d = std::round(numRows);
  if (d < 2.147483648E+9) {
    if (d >= -2.147483648E+9) {
      numRowsCast = static_cast<int>(d);
    } else {
      numRowsCast = MIN_int32_T;
    }
  } else if (d >= 2.147483648E+9) {
    numRowsCast = MAX_int32_T;
  } else {
    numRowsCast = 0;
  }
  d = std::round(overlap);
  if (d < 2.147483648E+9) {
    if (d >= -2.147483648E+9) {
      n = static_cast<int>(d);
    } else {
      n = MIN_int32_T;
    }
  } else if (d >= 2.147483648E+9) {
    n = MAX_int32_T;
  } else {
    n = 0;
  }
  wPtr_tmp = pBuffer.WritePointer;
  qY = 0;
  b_qY = 0;
  yk = pBuffer.ReadPointer;
  if (yk > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr = yk + 1;
  }
  if (rPtr > 49621) {
    rPtr = 1;
  }
  if (n == 0) {
    if ((rPtr < 0) && (numRowsCast < MIN_int32_T - rPtr)) {
      c_qY = MIN_int32_T;
    } else if ((rPtr > 0) && (numRowsCast > MAX_int32_T - rPtr)) {
      c_qY = MAX_int32_T;
    } else {
      c_qY = rPtr + numRowsCast;
    }
    if (c_qY < -2147483647) {
      c_qY = MIN_int32_T;
    } else {
      c_qY--;
    }
    c = c_qY;
    if (c_qY > 49621) {
      c = c_qY - 49621;
      y.set_size(1, c_qY - 49621);
      y[0] = 1;
      yk = 1;
      for (int k{2}; k <= c; k++) {
        yk++;
        y[k - 1] = yk;
      }
      eml_integer_colon_dispatcher(rPtr, r);
      readIdx.set_size(1, r.size(1) + y.size(1));
      n = r.size(1);
      for (yk = 0; yk < n; yk++) {
        readIdx[yk] = r[yk];
      }
      n = y.size(1);
      for (yk = 0; yk < n; yk++) {
        readIdx[yk + r.size(1)] = y[yk];
      }
      if (rPtr <= wPtr_tmp) {
        if (wPtr_tmp < -2147434026) {
          qY = MAX_int32_T;
        } else {
          qY = 49621 - wPtr_tmp;
        }
        if (qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY++;
        }
        if ((qY < 0) && (c_qY - 49621 < MIN_int32_T - qY)) {
          qY = MIN_int32_T;
        } else if ((qY > 0) && (c_qY - 49621 > MAX_int32_T - qY)) {
          qY = MAX_int32_T;
        } else {
          qY = (qY + c_qY) - 49621;
        }
      } else if (wPtr_tmp <= c_qY - 49621) {
        if (wPtr_tmp < c_qY + 2147434028) {
          c_qY = MAX_int32_T;
        } else {
          c_qY = (c_qY - wPtr_tmp) - 49621;
        }
        if (c_qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY = c_qY + 1;
        }
      }
    } else {
      if (c_qY < rPtr) {
        n = 0;
      } else {
        n = (c_qY - rPtr) + 1;
      }
      readIdx.set_size(1, n);
      if (n > 0) {
        readIdx[0] = rPtr;
        yk = rPtr;
        for (int k{2}; k <= n; k++) {
          yk++;
          readIdx[k - 1] = yk;
        }
      }
      if ((rPtr <= wPtr_tmp) && (wPtr_tmp <= c_qY)) {
        if ((c_qY >= 0) && (wPtr_tmp < c_qY - MAX_int32_T)) {
          c_qY = MAX_int32_T;
        } else if ((c_qY < 0) && (wPtr_tmp > c_qY - MIN_int32_T)) {
          c_qY = MIN_int32_T;
        } else {
          c_qY -= wPtr_tmp;
        }
        if (c_qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY = c_qY + 1;
        }
      }
    }
  } else {
    int qY_tmp;
    if ((rPtr >= 0) && (n < rPtr - MAX_int32_T)) {
      qY_tmp = MAX_int32_T;
      c_qY = MAX_int32_T;
    } else if ((rPtr < 0) && (n > rPtr - MIN_int32_T)) {
      qY_tmp = MIN_int32_T;
      c_qY = MIN_int32_T;
    } else {
      qY_tmp = rPtr - n;
      c_qY = qY_tmp;
    }
    if ((c_qY < 0) && (numRowsCast < MIN_int32_T - c_qY)) {
      c_qY = MIN_int32_T;
    } else if ((c_qY > 0) && (numRowsCast > MAX_int32_T - c_qY)) {
      c_qY = MAX_int32_T;
    } else {
      c_qY += numRowsCast;
    }
    if (c_qY < -2147483647) {
      c_qY = MIN_int32_T;
    } else {
      c_qY--;
    }
    c = c_qY;
    if (qY_tmp < 1) {
      if (c_qY < 1) {
        n = 0;
      } else {
        n = c_qY;
      }
      y.set_size(1, n);
      if (n > 0) {
        y[0] = 1;
        yk = 1;
        for (int k{2}; k <= n; k++) {
          yk++;
          y[k - 1] = yk;
        }
      }
      eml_integer_colon_dispatcher(qY_tmp + 49621, r);
      readIdx.set_size(1, r.size(1) + y.size(1));
      n = r.size(1);
      for (yk = 0; yk < n; yk++) {
        readIdx[yk] = r[yk];
      }
      n = y.size(1);
      for (yk = 0; yk < n; yk++) {
        readIdx[yk + r.size(1)] = y[yk];
      }
      if ((rPtr <= wPtr_tmp) && (wPtr_tmp <= c_qY)) {
        if ((c_qY >= 0) && (wPtr_tmp < c_qY - MAX_int32_T)) {
          c_qY = MAX_int32_T;
        } else if ((c_qY < 0) && (wPtr_tmp > c_qY - MIN_int32_T)) {
          c_qY = MIN_int32_T;
        } else {
          c_qY -= wPtr_tmp;
        }
        if (c_qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY = c_qY + 1;
        }
      } else if (wPtr_tmp < rPtr) {
        if (qY_tmp + 49621 < -2147434026) {
          c_qY = MAX_int32_T;
        } else {
          c_qY = -qY_tmp;
        }
        if (c_qY > 2147483646) {
          c_qY = MAX_int32_T;
        } else {
          c_qY++;
        }
        if ((c_qY < 0) && (wPtr_tmp < MIN_int32_T - c_qY)) {
          b_qY = MIN_int32_T;
        } else if ((c_qY > 0) && (wPtr_tmp > MAX_int32_T - c_qY)) {
          b_qY = MAX_int32_T;
        } else {
          b_qY = c_qY + wPtr_tmp;
        }
      } else if (wPtr_tmp > qY_tmp + 49621) {
        if ((wPtr_tmp >= 0) && (qY_tmp + 49621 < wPtr_tmp - MAX_int32_T)) {
          c_qY = MAX_int32_T;
        } else if ((wPtr_tmp < 0) &&
                   (qY_tmp + 49621 > wPtr_tmp - MIN_int32_T)) {
          c_qY = MIN_int32_T;
        } else {
          c_qY = (wPtr_tmp - qY_tmp) - 49621;
        }
        if (c_qY > 2147483646) {
          b_qY = MAX_int32_T;
        } else {
          b_qY = c_qY + 1;
        }
      }
    } else if (c_qY > 49621) {
      c = c_qY - 49621;
      y.set_size(1, c_qY - 49621);
      y[0] = 1;
      yk = 1;
      for (int k{2}; k <= c; k++) {
        yk++;
        y[k - 1] = yk;
      }
      eml_integer_colon_dispatcher(qY_tmp, r);
      readIdx.set_size(1, r.size(1) + y.size(1));
      n = r.size(1);
      for (yk = 0; yk < n; yk++) {
        readIdx[yk] = r[yk];
      }
      n = y.size(1);
      for (yk = 0; yk < n; yk++) {
        readIdx[yk + r.size(1)] = y[yk];
      }
      if (rPtr <= wPtr_tmp) {
        if (wPtr_tmp < -2147434026) {
          qY = MAX_int32_T;
        } else {
          qY = 49621 - wPtr_tmp;
        }
        if (qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY++;
        }
        if ((qY < 0) && (c_qY - 49621 < MIN_int32_T - qY)) {
          qY = MIN_int32_T;
        } else if ((qY > 0) && (c_qY - 49621 > MAX_int32_T - qY)) {
          qY = MAX_int32_T;
        } else {
          qY = (qY + c_qY) - 49621;
        }
      } else if (wPtr_tmp <= c_qY - 49621) {
        if (wPtr_tmp < c_qY + 2147434028) {
          c_qY = MAX_int32_T;
        } else {
          c_qY = (c_qY - wPtr_tmp) - 49621;
        }
        if (c_qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY = c_qY + 1;
        }
      } else if ((qY_tmp < wPtr_tmp) && (wPtr_tmp < rPtr)) {
        b_qY = (wPtr_tmp - qY_tmp) + 1;
      }
    } else {
      if (c_qY < qY_tmp) {
        n = 0;
      } else {
        n = (c_qY - qY_tmp) + 1;
      }
      readIdx.set_size(1, n);
      if (n > 0) {
        readIdx[0] = qY_tmp;
        yk = qY_tmp;
        for (int k{2}; k <= n; k++) {
          yk++;
          readIdx[k - 1] = yk;
        }
      }
      if ((rPtr <= wPtr_tmp) && (wPtr_tmp <= c_qY)) {
        if ((c_qY >= 0) && (wPtr_tmp < c_qY - MAX_int32_T)) {
          c_qY = MAX_int32_T;
        } else if ((c_qY < 0) && (wPtr_tmp > c_qY - MIN_int32_T)) {
          c_qY = MIN_int32_T;
        } else {
          c_qY -= wPtr_tmp;
        }
        if (c_qY > 2147483646) {
          qY = MAX_int32_T;
        } else {
          qY = c_qY + 1;
        }
      } else if ((qY_tmp <= wPtr_tmp) && (wPtr_tmp < rPtr)) {
        b_qY = (wPtr_tmp - qY_tmp) + 1;
      }
    }
  }
  b_out.set_size(readIdx.size(1));
  n = readIdx.size(1);
  for (yk = 0; yk < n; yk++) {
    b_out[yk] = pBuffer.Cache[readIdx[yk] - 1];
  }
  if (qY != 0) {
    if ((numRowsCast >= 0) && (qY < numRowsCast - MAX_int32_T)) {
      c_qY = MAX_int32_T;
    } else if ((numRowsCast < 0) && (qY > numRowsCast - MIN_int32_T)) {
      c_qY = MIN_int32_T;
    } else {
      c_qY = numRowsCast - qY;
    }
    if (c_qY > 2147483646) {
      c_qY = MAX_int32_T;
    } else {
      c_qY++;
    }
    if (c_qY > numRowsCast) {
      c_qY = 1;
    }
    for (yk = 0; yk < qY; yk++) {
      b_out[(c_qY + yk) - 1] = 0.0;
    }
  } else if (b_qY != 0) {
    if (b_qY == numRowsCast) {
      b_out.set_size(b_qY);
      for (yk = 0; yk < b_qY; yk++) {
        b_out[yk] = 0.0;
      }
    } else {
      for (yk = 0; yk < b_qY; yk++) {
        b_out[yk] = 0.0;
      }
    }
  }
  out.set_size(b_out.size(0));
  n = b_out.size(0);
  for (yk = 0; yk < n; yk++) {
    out[yk] = b_out[yk];
  }
  if (wPtr_tmp < -2147483647) {
    c_qY = MIN_int32_T;
  } else {
    c_qY = wPtr_tmp - 1;
  }
  yk = pBuffer.CumulativeUnderrun;
  if ((yk < 0) && (qY < MIN_int32_T - yk)) {
    b_qY = MIN_int32_T;
  } else if ((yk > 0) && (qY > MAX_int32_T - yk)) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = yk + qY;
  }
  pBuffer.CumulativeUnderrun = b_qY;
  if (qY != 0) {
    pBuffer.ReadPointer = c_qY;
  } else {
    pBuffer.ReadPointer = c;
  }
}

//
// Arguments    : const creal32_T in_data[]
// Return Type  : void
//
void b_AsyncBuffer::write(const creal32_T in_data[])
{
  array<int, 2U> bc;
  array<int, 2U> r1;
  array<int, 2U> y;
  array<unsigned short, 1U> r;
  int b_qY;
  int c;
  int n;
  int qY;
  int rPtr;
  int wPtr;
  int yk;
  if (pBuffer.isInitialized != 1) {
    pBuffer.isInitialized = 1;
    pBuffer.NumChannels = 1;
    pBuffer.AsyncBuffercgHelper_isInitialized = true;
    pBuffer.isSetupComplete = true;
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    std::memset(&pBuffer.Cache[0], 0, 49621U * sizeof(creal32_T));
  }
  wPtr = pBuffer.WritePointer;
  rPtr = pBuffer.ReadPointer;
  qY = 0;
  if (wPtr > 2147482623) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = wPtr + 1024;
  }
  c = b_qY - 1;
  if (b_qY - 1 > 49621) {
    c = b_qY - 49622;
    y.set_size(1, b_qY - 49622);
    y[0] = 1;
    yk = 1;
    for (int k{2}; k <= c; k++) {
      yk++;
      y[k - 1] = yk;
    }
    if (wPtr > 49621) {
      n = 0;
    } else {
      unsigned int u;
      if (wPtr < 0) {
        u = 49621U - static_cast<unsigned int>(wPtr);
      } else {
        u = static_cast<unsigned int>(49621 - wPtr);
      }
      n = static_cast<int>(u) + 1;
    }
    r1.set_size(1, n);
    if (n > 0) {
      r1[0] = wPtr;
      yk = wPtr;
      for (int k{2}; k <= n; k++) {
        yk++;
        r1[k - 1] = yk;
      }
    }
    bc.set_size(1, r1.size(1) + y.size(1));
    n = r1.size(1);
    for (yk = 0; yk < n; yk++) {
      bc[yk] = r1[yk];
    }
    n = y.size(1);
    for (yk = 0; yk < n; yk++) {
      bc[yk + r1.size(1)] = y[yk];
    }
    if (wPtr <= rPtr) {
      if (rPtr < -2147434026) {
        qY = MAX_int32_T;
      } else {
        qY = 49621 - rPtr;
      }
      if (qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY++;
      }
      if ((qY < 0) && (b_qY - 49622 < MIN_int32_T - qY)) {
        qY = MIN_int32_T;
      } else if ((qY > 0) && (b_qY - 49622 > MAX_int32_T - qY)) {
        qY = MAX_int32_T;
      } else {
        qY = (qY + b_qY) - 49622;
      }
    } else if (rPtr <= b_qY - 49622) {
      if (rPtr < b_qY + 2147434027) {
        b_qY = MAX_int32_T;
      } else {
        b_qY = (b_qY - rPtr) - 49622;
      }
      if (b_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = b_qY + 1;
      }
    }
  } else {
    if (b_qY - 1 < wPtr) {
      n = 0;
    } else {
      n = b_qY - wPtr;
    }
    bc.set_size(1, n);
    if (n > 0) {
      bc[0] = wPtr;
      yk = wPtr;
      for (int k{2}; k <= n; k++) {
        yk++;
        bc[k - 1] = yk;
      }
    }
    if ((wPtr <= rPtr) && (rPtr <= b_qY - 1)) {
      if ((b_qY - 1 >= 0) && (rPtr < b_qY + MIN_int32_T)) {
        b_qY = MAX_int32_T;
      } else if ((b_qY - 1 < 0) && (rPtr > b_qY + MAX_int32_T)) {
        b_qY = MIN_int32_T;
      } else {
        b_qY = (b_qY - rPtr) - 1;
      }
      if (b_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = b_qY + 1;
      }
    }
  }
  r.set_size(bc.size(1));
  n = bc.size(1);
  for (yk = 0; yk < n; yk++) {
    r[yk] =
        static_cast<unsigned short>(static_cast<unsigned short>(bc[yk]) - 1U);
  }
  for (yk = 0; yk < 1024; yk++) {
    pBuffer.Cache[r[yk]] = in_data[yk];
  }
  if (c + 1 > 49621) {
    wPtr = 1;
  } else {
    wPtr = c + 1;
  }
  if (qY != 0) {
    rPtr = wPtr;
  }
  n = pBuffer.CumulativeOverrun;
  if ((n < 0) && (qY < MIN_int32_T - n)) {
    b_qY = MIN_int32_T;
  } else if ((n > 0) && (qY > MAX_int32_T - n)) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = n + qY;
  }
  pBuffer.CumulativeOverrun = b_qY;
  pBuffer.WritePointer = wPtr;
  pBuffer.ReadPointer = rPtr;
}

//
// Arguments    : const double in_data[]
// Return Type  : void
//
void AsyncBuffer::write(const double in_data[])
{
  array<int, 2U> bc;
  array<int, 2U> r1;
  array<int, 2U> y;
  array<unsigned short, 1U> r;
  int b_qY;
  int c;
  int n;
  int qY;
  int rPtr;
  int wPtr;
  int yk;
  if (pBuffer.isInitialized != 1) {
    pBuffer.isInitialized = 1;
    pBuffer.NumChannels = 1;
    pBuffer.AsyncBuffercgHelper_isInitialized = true;
    pBuffer.isSetupComplete = true;
    pBuffer.ReadPointer = 1;
    pBuffer.WritePointer = 2;
    pBuffer.CumulativeOverrun = 0;
    pBuffer.CumulativeUnderrun = 0;
    std::memset(&pBuffer.Cache[0], 0, 49621U * sizeof(double));
  }
  wPtr = pBuffer.WritePointer;
  rPtr = pBuffer.ReadPointer;
  qY = 0;
  if (wPtr > 2147482623) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = wPtr + 1024;
  }
  c = b_qY - 1;
  if (b_qY - 1 > 49621) {
    c = b_qY - 49622;
    y.set_size(1, b_qY - 49622);
    y[0] = 1;
    yk = 1;
    for (int k{2}; k <= c; k++) {
      yk++;
      y[k - 1] = yk;
    }
    if (wPtr > 49621) {
      n = 0;
    } else {
      unsigned int u;
      if (wPtr < 0) {
        u = 49621U - static_cast<unsigned int>(wPtr);
      } else {
        u = static_cast<unsigned int>(49621 - wPtr);
      }
      n = static_cast<int>(u) + 1;
    }
    r1.set_size(1, n);
    if (n > 0) {
      r1[0] = wPtr;
      yk = wPtr;
      for (int k{2}; k <= n; k++) {
        yk++;
        r1[k - 1] = yk;
      }
    }
    bc.set_size(1, r1.size(1) + y.size(1));
    n = r1.size(1);
    for (yk = 0; yk < n; yk++) {
      bc[yk] = r1[yk];
    }
    n = y.size(1);
    for (yk = 0; yk < n; yk++) {
      bc[yk + r1.size(1)] = y[yk];
    }
    if (wPtr <= rPtr) {
      if (rPtr < -2147434026) {
        qY = MAX_int32_T;
      } else {
        qY = 49621 - rPtr;
      }
      if (qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY++;
      }
      if ((qY < 0) && (b_qY - 49622 < MIN_int32_T - qY)) {
        qY = MIN_int32_T;
      } else if ((qY > 0) && (b_qY - 49622 > MAX_int32_T - qY)) {
        qY = MAX_int32_T;
      } else {
        qY = (qY + b_qY) - 49622;
      }
    } else if (rPtr <= b_qY - 49622) {
      if (rPtr < b_qY + 2147434027) {
        b_qY = MAX_int32_T;
      } else {
        b_qY = (b_qY - rPtr) - 49622;
      }
      if (b_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = b_qY + 1;
      }
    }
  } else {
    if (b_qY - 1 < wPtr) {
      n = 0;
    } else {
      n = b_qY - wPtr;
    }
    bc.set_size(1, n);
    if (n > 0) {
      bc[0] = wPtr;
      yk = wPtr;
      for (int k{2}; k <= n; k++) {
        yk++;
        bc[k - 1] = yk;
      }
    }
    if ((wPtr <= rPtr) && (rPtr <= b_qY - 1)) {
      if ((b_qY - 1 >= 0) && (rPtr < b_qY + MIN_int32_T)) {
        b_qY = MAX_int32_T;
      } else if ((b_qY - 1 < 0) && (rPtr > b_qY + MAX_int32_T)) {
        b_qY = MIN_int32_T;
      } else {
        b_qY = (b_qY - rPtr) - 1;
      }
      if (b_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = b_qY + 1;
      }
    }
  }
  r.set_size(bc.size(1));
  n = bc.size(1);
  for (yk = 0; yk < n; yk++) {
    r[yk] =
        static_cast<unsigned short>(static_cast<unsigned short>(bc[yk]) - 1U);
  }
  for (yk = 0; yk < 1024; yk++) {
    pBuffer.Cache[r[yk]] = in_data[yk];
  }
  if (c + 1 > 49621) {
    wPtr = 1;
  } else {
    wPtr = c + 1;
  }
  if (qY != 0) {
    rPtr = wPtr;
  }
  n = pBuffer.CumulativeOverrun;
  if ((n < 0) && (qY < MIN_int32_T - n)) {
    b_qY = MIN_int32_T;
  } else if ((n > 0) && (qY > MAX_int32_T - n)) {
    b_qY = MAX_int32_T;
  } else {
    b_qY = n + qY;
  }
  pBuffer.CumulativeOverrun = b_qY;
  pBuffer.WritePointer = wPtr;
  pBuffer.ReadPointer = rPtr;
}

} // namespace dsp
} // namespace coder

//
// File trailer for AsyncBuffer.cpp
//
// [EOF]
//
