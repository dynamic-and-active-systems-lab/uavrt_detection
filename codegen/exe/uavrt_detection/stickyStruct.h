//
// Trial License - for use to evaluate programs for possible purchase as
// an end-user only.
// File: stickyStruct.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 22-Oct-2022 15:24:58
//

#ifndef STICKYSTRUCT_H
#define STICKYSTRUCT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace internal {
class stickyStruct {
public:
  double value;
};

class b_stickyStruct {
public:
  stickyStruct next;
};

class c_stickyStruct {
public:
  b_stickyStruct next;
};

class d_stickyStruct {
public:
  c_stickyStruct next;
};

class e_stickyStruct {
public:
  d_stickyStruct next;
};

class f_stickyStruct {
public:
  e_stickyStruct next;
};

class g_stickyStruct {
public:
  f_stickyStruct next;
};

class h_stickyStruct {
public:
  double value;
  g_stickyStruct next;
};

class i_stickyStruct {
public:
  h_stickyStruct next;
};

class j_stickyStruct {
public:
  array<float, 1U> value;
  i_stickyStruct next;
};

class k_stickyStruct {
public:
  array<double, 1U> value;
  i_stickyStruct next;
};

class l_stickyStruct {
public:
  double value;
  k_stickyStruct next;
};

class m_stickyStruct {
public:
  double value;
  l_stickyStruct next;
};

class n_stickyStruct {
public:
  double value;
  m_stickyStruct next;
};

class o_stickyStruct {
public:
  n_stickyStruct next;
};

class p_stickyStruct {
public:
  o_stickyStruct next;
};

class q_stickyStruct {
public:
  p_stickyStruct next;
};

class r_stickyStruct {
public:
  q_stickyStruct next;
};

class s_stickyStruct {
public:
  r_stickyStruct next;
};

} // namespace internal
} // namespace coder

#endif
//
// File trailer for stickyStruct.h
//
// [EOF]
//
