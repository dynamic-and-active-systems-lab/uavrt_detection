//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: uavrt_detection.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 18-Mar-2025 09:34:46
//

// Include Files
#include "uavrt_detection.h"
#include "AsyncBuffer.h"
#include "AsyncBufferSysObj.h"
#include "ComplexSingleSamplesUDPReceiver.h"
#include "DetectorConfig.h"
#include "PulseInfoStruct.h"
#include "all.h"
#include "blockedSummation.h"
#include "datetime.h"
#include "diff.h"
#include "eml_int_forloop_overflow_check.h"
#include "feof.h"
#include "fgetl.h"
#include "fileManager.h"
#include "find.h"
#include "fseek.h"
#include "ftell.h"
#include "fwrite.h"
#include "horzcatStructList.h"
#include "ifWhileCond.h"
#include "indexShapeCheck.h"
#include "log10.h"
#include "makepulsestruc.h"
#include "mpower.h"
#include "mustBeInteger.h"
#include "pulsestats.h"
#include "pwd1.h"
#include "ref.h"
#include "rt_nonfinite.h"
#include "sprintf.h"
#include "str2double.h"
#include "str2matrix.h"
#include "strcmp.h"
#include "string1.h"
#include "sum.h"
#include "threshold.h"
#include "tic.h"
#include "toc.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_initialize.h"
#include "uavrt_detection_internal_types.h"
#include "uavrt_detection_rtwutil.h"
#include "uavrt_detection_types.h"
#include "validate_print_arguments.h"
#include "validator_check_size.h"
#include "waveform.h"
#include "waveformcopy.h"
#include "wfmcsvwrite.h"
#include "wfmstft.h"
#include "wgn.h"
#include "coder_array.h"
#include "omp.h"
#include "time.h"
#include "udp.h"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include <string>

// Function Declarations
static void b_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void
interleaveComplexVector(const coder::array<creal32_T, 1U> &complexDataIn,
                        coder::array<float, 1U> &interleaveDataOut);

static void j_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void rtErrorWithMessageID(const char *r, const char *aFcnName,
                                 int aLineNum);

static void
updatebufferreadvariables(const coder::b_captured_var &Config,
                          const coder::c_captured_var &stftOverlapFraction,
                          coder::c_captured_var &overlapSamples,
                          coder::c_captured_var &sampsForKPulses,
                          const pulsestats *ps_input);

static void updateconfig(coder::b_captured_var &Config,
                         coder::captured_var &configPath);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void b_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "fopen(\'all\') is not supported for code generation.";
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
// This function takes a vector of complex values, and interleaves
// the real and complex parts to generate a output vector of 2x the
// number of elements as the number of rows of the input.
//
// Arguments    : const coder::array<creal32_T, 1U> &complexDataIn
//                coder::array<float, 1U> &interleaveDataOut
// Return Type  : void
//
static void
interleaveComplexVector(const coder::array<creal32_T, 1U> &complexDataIn,
                        coder::array<float, 1U> &interleaveDataOut)
{
  coder::array<float, 2U> dataMatrix;
  coder::array<float, 1U> varargin_1;
  coder::array<float, 1U> varargin_2;
  int loop_ub;
  // Enforce column vector
  loop_ub = complexDataIn.size(0);
  varargin_1.set_size(complexDataIn.size(0));
  varargin_2.set_size(complexDataIn.size(0));
  for (int i{0}; i < loop_ub; i++) {
    varargin_1[i] = complexDataIn[i].re;
    varargin_2[i] = complexDataIn[i].im;
  }
  if (varargin_2.size(0) != varargin_1.size(0)) {
    fb_rtErrorWithMessageID(qb_emlrtRTEI.fName, qb_emlrtRTEI.lineNo);
  }
  dataMatrix.set_size(2, complexDataIn.size(0));
  for (int i{0}; i < loop_ub; i++) {
    dataMatrix[2 * i] = varargin_1[i];
    dataMatrix[2 * i + 1] = varargin_2[i];
  }
  loop_ub = dataMatrix.size(1) << 1;
  interleaveDataOut.set_size(loop_ub);
  for (int i{0}; i < loop_ub; i++) {
    interleaveDataOut[i] = dataMatrix[i];
  }
  // Interleave
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void j_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Value must be nonnegative.";
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
// Arguments    : const char *r
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void rtErrorWithMessageID(const char *r, const char *aFcnName,
                                 int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "Value must be less than ") << r) << ".";
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
// This function updates the buffer reading variables as needed by
// the priori information about the pulse statistics. The segment
// lengths depend on the interpulse duration and uncertainty
// parameters.
//
// Arguments    : const coder::b_captured_var &Config
//                const coder::c_captured_var &stftOverlapFraction
//                coder::c_captured_var &overlapSamples
//                coder::c_captured_var &sampsForKPulses
//                const pulsestats *ps_input
// Return Type  : void
//
static void
updatebufferreadvariables(const coder::b_captured_var &Config,
                          const coder::c_captured_var &stftOverlapFraction,
                          coder::c_captured_var &overlapSamples,
                          coder::c_captured_var &sampsForKPulses,
                          const pulsestats *ps_input)
{
  b_waveform X0;
  pulsestats lobj_2;
  double J;
  double M;
  double N;
  double a__2;
  double n_ol;
  unsigned int validatedHoleFilling[3];
  unsigned int u;
  unsigned int u1;
  unsigned int u2;
  // Build an empty waveform just so that we can calculate number
  // of overlapSamples. This is needed for buffer operations
  // THRESHOLD Constructs an instance of this class
  // INPUTS:
  //    pf  probability of false alarm
  //
  // WAVEFORM Constructs an instance of this class
  // INPUTS:
  //    x       1xn     Vector of samples
  //    Fs      1x1     Sample frequency (Hz)
  //    t_0     1x1     Time stamp of first element (s)
  // 	ps_pre  1x1     Pulse stats object from previous data (priori)
  //    OLF     1x1     Overlap fraction as decimal (0.5 = 50%
  //                    overlap)
  // OUTPUTS:
  //    obj             The waveform object
  //             %%
  // Flatten input to row
  // Data vector
  // Elements in the data
  X0.Fs = Config.contents.Fs;
  // Sample rate
  // Time stamp of first element
  // Time stamp of last element
  // This is the time when next
  // segment should start to
  // ensure sufficient overlap.
  // Will need to be updated
  // elsewhere.
  // Overlap Fraction for STFT
  // Unknown number of pulses.
  // WFMSTFT Constructs and returns an instance of this class
  //
  // An waveform object must be passed to this construction method
  // so that the constructor has access to the data vector, desired
  // overlap fraction, and priori pulse data, which is used to
  // develop the window sizes.
  // INPUTS:
  //    waveform_obj   A single waveform object with prior
  //                   dependent properties set.
  // OUTPUTS:
  //    obj             A wfmstft object
  //             %%
  //
  // The following are variable sized properties. To tell coder
  // that they may vary setup as a local variable size variable
  // first, then set.
  // Instructions on
  // https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
  // maxFs*maxpulsewidth
  // Now actually assign them
  // Unknown values but set types
  // Copy over ps_
  // COPY Creates an exact copy of the pulse stats object as a
  // separate object
  lobj_2.b_init(ps_input->t_p, ps_input->t_ip, ps_input->t_ipu, ps_input->t_ipj,
                ps_input->fp, ps_input->fstart, ps_input->fend, ps_input->tmplt,
                ps_input->mode, ps_input->pl, ps_input->clst, ps_input->cmsk,
                ps_input->cpki);
  // ,...
  // obj.thresh);
  // Current stats are same as previous during construction
  // SETPRIORIDEPENDENTVARS updates the properties in the
  // waveform that are dependent on properties in a pulsestats
  // object.
  //
  // INPUTS:
  //    obj     waveform object
  //    ps_obj  a pulse stats object
  // OUTPUTS:
  //    None (This method modifies the waveform object properties)
  //
  //             %%
  // GETPRIORIDEPENDENTVARS returns the properties in the
  // waveform that are dependent on prior pulse data estimates. It
  // depends on the waveform properties list Fs etc, as well as
  // pulse stats like t_ip, etc.
  // INPUTS:  ps_obj  1x1 pulse stats object
  // OUTPUTS:  pulse stats object
  // Samples per pulse
  // Number of elements in STFT window
  // Number of elements overlap in STFT window
  // Number of elements in each step of STFT
  // Time of each step of STFT
  // Samples per pulse
  // Number of elements in STFT window
  // Number of elements overlap in STFT window
  // Number of elements in each step of STFT
  // Time of each step of STFT
  // Samples of interpulse duration
  // Baseline interpulse duration in units of STFT windows
  // Interpulse duration deviation from baselines in units of STFT windows
  // Amount of deviation from the PRI means to search
  // See 2022-07-11 for updates to samples def
  // Don't need the overlap here since the next segment starts at
  // samplesforKpulses+n_ol-n_ol from current sample SETPRIORIDEPENDENTVARS
  // updates the properties in the waveform that are dependent on properties in
  // a pulsestats object.
  //
  // INPUTS:
  //    obj     waveform object
  //    ps_obj  a pulse stats object
  // OUTPUTS:
  //    None (This method modifies the waveform object properties)
  //
  //             %%
  // GETPRIORIDEPENDENTVARS returns the properties in the
  // waveform that are dependent on prior pulse data estimates. It
  // depends on the waveform properties list Fs etc, as well as
  // pulse stats like t_ip, etc.
  // INPUTS:  ps_obj  1x1 pulse stats object
  // OUTPUTS:  pulse stats object
  // Samples per pulse
  // Number of elements in STFT window
  // Number of elements overlap in STFT window
  // Number of elements in each step of STFT
  // Time of each step of STFT
  // Samples per pulse
  // Number of elements in STFT window
  // Number of elements overlap in STFT window
  // Number of elements in each step of STFT
  // Time of each step of STFT
  // Samples of interpulse duration
  // Baseline interpulse duration in units of STFT windows
  // Interpulse duration deviation from baselines in units of STFT windows
  // Amount of deviation from the PRI means to search
  // See 2022-07-11 for updates to samples def
  // Don't need the overlap here since the next segment starts at
  // samplesforKpulses+n_ol-n_ol from current sample GETPRIORIDEPENDENTVARS
  // returns the properties in the waveform that are dependent on prior pulse
  // data estimates. It depends on the waveform properties list Fs etc, as well
  // as pulse stats like t_ip, etc. INPUTS:  ps_obj  1x1 pulse stats object
  // OUTPUTS:  pulse stats object
  a__2 = std::ceil(ps_input->t_p * X0.Fs);
  // Samples per pulse
  // Number of elements in STFT window
  n_ol = std::floor(stftOverlapFraction.contents * a__2);
  // Number of elements overlap in STFT window
  a__2 -= n_ol;
  // Number of elements in each step of STFT
  // Time of each step of STFT
  N = std::floor(std::ceil(ps_input->t_ip * X0.Fs) / a__2);
  M = std::ceil(std::ceil(ps_input->t_ipu * X0.Fs) / a__2);
  J = std::ceil(std::ceil(ps_input->t_ipj * X0.Fs) / a__2);
  overlapSamples.contents = a__2 * (2.0 * (Config.contents.K * M + J));
  // See 2022-07-11 for updates to samples def
  sampsForKPulses.contents =
      a__2 * ((Config.contents.K * (N + M) + J) + 1.0) + n_ol;
  if (N < 4.294967296E+9) {
    if (N >= 0.0) {
      u = static_cast<unsigned int>(N);
    } else {
      u = 0U;
    }
  } else if (N >= 4.294967296E+9) {
    u = MAX_uint32_T;
  } else {
    u = 0U;
  }
  if (M < 4.294967296E+9) {
    if (M >= 0.0) {
      u1 = static_cast<unsigned int>(M);
    } else {
      u1 = 0U;
    }
  } else if (M >= 4.294967296E+9) {
    u1 = MAX_uint32_T;
  } else {
    u1 = 0U;
  }
  if (J < 4.294967296E+9) {
    if (J >= 0.0) {
      u2 = static_cast<unsigned int>(J);
    } else {
      u2 = 0U;
    }
  } else if (J >= 4.294967296E+9) {
    u2 = MAX_uint32_T;
  } else {
    u2 = 0U;
  }
  coder::internal::validate_print_arguments(u, u1, u2, validatedHoleFilling);
  std::printf("Updated buffer read vars -- N: %u, M: %u, J: %u,\n",
              validatedHoleFilling[0], validatedHoleFilling[1],
              validatedHoleFilling[2]);
  std::fflush(stdout);
  a__2 = std::round(sampsForKPulses.contents);
  if (a__2 < 4.294967296E+9) {
    if (a__2 >= 0.0) {
      u = static_cast<unsigned int>(a__2);
    } else {
      u = 0U;
    }
  } else if (a__2 >= 4.294967296E+9) {
    u = MAX_uint32_T;
  } else {
    u = 0U;
  }
  a__2 = std::round(overlapSamples.contents);
  if (a__2 < 4.294967296E+9) {
    if (a__2 >= 0.0) {
      u1 = static_cast<unsigned int>(a__2);
    } else {
      u1 = 0U;
    }
  } else if (a__2 >= 4.294967296E+9) {
    u1 = MAX_uint32_T;
  } else {
    u1 = 0U;
  }
  std::printf(
      "Updated buffer read vars -- sampForKPulses: %u,  overlapSamples: %u,\n",
      u, u1);
  std::fflush(stdout);
}

//
// Add code here to update the variables within the function that are
// part of the configuration file. Will first need to load the correct
// file and
//
//
// Arguments    : coder::b_captured_var &Config
//                coder::captured_var &configPath
// Return Type  : void
//
static void updateconfig(coder::b_captured_var &Config,
                         coder::captured_var &configPath)
{
  static rtBoundsCheckInfo ab_emlrtBCI{
      124,                         // lineNo
      "rawLine",                   // aName
      "DetectorConfig/setFromFile" // fName
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      155,                         // lineNo
      "sepByte",                   // aName
      "DetectorConfig/setFromFile" // fName
  };
  static rtBoundsCheckInfo cb_emlrtBCI{
      159,                         // lineNo
      "lineStr",                   // aName
      "DetectorConfig/setFromFile" // fName
  };
  static rtBoundsCheckInfo db_emlrtBCI{
      162,                         // lineNo
      "tabLocs",                   // aName
      "DetectorConfig/setFromFile" // fName
  };
  static rtBoundsCheckInfo eb_emlrtBCI{
      163,                         // lineNo
      "colonLocation",             // aName
      "DetectorConfig/setFromFile" // fName
  };
  static rtBoundsCheckInfo fb_emlrtBCI{
      202,                         // lineNo
      "sepByte",                   // aName
      "DetectorConfig/setFromFile" // fName
  };
  static rtBoundsCheckInfo gb_emlrtBCI{
      164,                         // lineNo
      "lineStr",                   // aName
      "DetectorConfig/setFromFile" // fName
  };
  static rtBoundsCheckInfo hb_emlrtBCI{
      164,                         // lineNo
      "lineStr",                   // aName
      "DetectorConfig/setFromFile" // fName
  };
  static rtBoundsCheckInfo ib_emlrtBCI{
      163,                         // lineNo
      "lineStr",                   // aName
      "DetectorConfig/setFromFile" // fName
  };
  static rtBoundsCheckInfo jb_emlrtBCI{
      163,                         // lineNo
      "lineStr",                   // aName
      "DetectorConfig/setFromFile" // fName
  };
  static rtBoundsCheckInfo kb_emlrtBCI{
      204,                         // lineNo
      "sepByte",                   // aName
      "DetectorConfig/setFromFile" // fName
  };
  static rtRunTimeErrorInfo rc_emlrtRTEI{
      38,     // lineNo
      "fopen" // fName
  };
  static rtRunTimeErrorInfo sc_emlrtRTEI{
      11,                 // lineNo
      "mustBeNonnegative" // fName
  };
  DetectorConfig r;
  coder::array<creal_T, 2U> r1;
  coder::array<double, 2U> sepByte;
  coder::array<double, 2U> val;
  coder::array<int, 2U> match_out;
  coder::array<int, 2U> matches;
  coder::array<unsigned int, 2U> tabLocs;
  coder::array<char, 2U> configType;
  coder::array<char, 2U> configValStr;
  coder::array<char, 2U> lineStr;
  coder::array<boolean_T, 2U> b_lineStr;
  double configNum;
  double d;
  int b_i;
  int fid;
  int i;
  int ii_data;
  int loop_ub;
  int match_idx;
  boolean_T done;
  r.init();
  loop_ub = configPath.contents.size(1);
  lineStr.set_size(1, loop_ub);
  match_idx = configPath.contents.size(1);
  for (i = 0; i < match_idx; i++) {
    lineStr[i] = configPath.contents[i];
  }
  // fillFromFile Replaces the properties of the instance passed to
  // it with the values specified in the configuration file passed
  // to the function. If multiple entries exist in the config file,
  // use the 'entry' argument to specify which entry to use (1-n).
  // If entry is not specified, the method will use the last entry
  // in the config file.
  //
  // INPUTS:
  //    filePath        String of full path to config file,
  //                    including the file name and extension
  //
  //    entry           Scalar number (1-n) of which entry to use.
  //                    Method will use the last entry if entry is
  //                    not provided. Alternatively, enter -1 to
  //                    use last entry.
  //
  // OUTPUTS:
  //    none (method modifies the properties of the instance)
  //
  if (coder::internal::b_strcmp(lineStr)) {
    b_rtErrorWithMessageID(rc_emlrtRTEI.fName, rc_emlrtRTEI.lineNo);
  } else {
    signed char fileid;
    fileid = coder::internal::cfopen(lineStr, "rb");
    fid = fileid;
  }
  if (fid == -1) {
    configType.set_size(1, lineStr.size(1) + 1);
    for (i = 0; i < loop_ub; i++) {
      configType[i] = lineStr[i];
    }
    configType[loop_ub] = '\x00';
    std::printf("UAV-RT: Error opening configurationfile file with error. "
                "Attempted to find config file at the location %s:\n",
                &configType[0]);
    std::fflush(stdout);
  }
  configNum = 0.0;
  done = false;
  // coder.varsize('sepLine')
  sepByte.set_size(1, 1);
  sepByte[0] = 0.0;
  // First figure out where the separator lines are
  while (!done) {
    // currByte = ftell(fid);
    coder::fgetl(static_cast<double>(fid), lineStr);
    if (lineStr.size(1) < 1) {
      rtDynamicBoundsError(1, 1, lineStr.size(1), ab_emlrtBCI);
    }
    if (lineStr[0] == '#') {
      // && lineNum~=1
      if (configNum == 0.0) {
        sepByte.set_size(1, 1);
        d = coder::b_ftell(static_cast<double>(fid));
        sepByte[0] = d;
      } else {
        // sepByte(configNum) = ftell(fid);
        d = coder::b_ftell(static_cast<double>(fid));
        i = sepByte.size(1);
        sepByte.set_size(1, sepByte.size(1) + 1);
        sepByte[i] = d;
        // Modified for Coder compatibility
      }
      configNum++;
    }
    done = (coder::b_feof(static_cast<double>(fid)) == 1.0);
  }
  // sepByte(configNum) = ftell(fid);
  d = coder::b_ftell(static_cast<double>(fid));
  i = sepByte.size(1);
  b_i = sepByte.size(1) + 1;
  sepByte.set_size(1, sepByte.size(1) + 1);
  sepByte[i] = d;
  // Modified for Coder compatibility
  // Jump to the line for the entry requested
  if ((static_cast<int>(configNum) < 1) ||
      (static_cast<int>(configNum) > b_i)) {
    rtDynamicBoundsError(static_cast<int>(configNum), 1, b_i, bb_emlrtBCI);
  }
  coder::b_fseek(static_cast<double>(fid),
                 sepByte[static_cast<int>(configNum) - 1]);
  done = false;
  int exitg1;
  do {
    exitg1 = 0;
    if (!done) {
      coder::fgetl(static_cast<double>(fid), lineStr);
      loop_ub = lineStr.size(1);
      if (lineStr.size(1) < 1) {
        rtDynamicBoundsError(1, 1, lineStr.size(1), cb_emlrtBCI);
      }
      if (lineStr[0] != '#') {
        int ii_size[2];
        b_lineStr.set_size(1, lineStr.size(1));
        for (i = 0; i < loop_ub; i++) {
          b_lineStr[i] = (lineStr[i] == ':');
        }
        coder::eml_find(b_lineStr, (int *)&ii_data, ii_size);
        // note regexp is not supported for code generation
        if (lineStr.size(1) == 0) {
          tabLocs.set_size(1, 0);
        } else {
          matches.set_size(1, lineStr.size(1));
          match_idx = 0;
          if (lineStr.size(1) > 2147483646) {
            coder::check_forloop_overflow_error();
          }
          for (i = 0; i < loop_ub; i++) {
            if (lineStr[i] == '\t') {
              matches[match_idx] = i + 1;
              match_idx++;
            }
          }
          match_out.set_size(1, match_idx);
          if (match_idx > 2147483646) {
            coder::check_forloop_overflow_error();
          }
          for (i = 0; i < match_idx; i++) {
            match_out[i] = matches[i];
          }
          loop_ub = match_out.size(1);
          tabLocs.set_size(1, match_out.size(1));
          for (i = 0; i < loop_ub; i++) {
            tabLocs[i] = static_cast<unsigned int>(match_out[i]);
          }
        }
        // Thanks to
        // https://www.mathworks.com/matlabcentral/answers/529668-how-do-i-detect-a-tab-character-in-a-line-of-text-read-by-fgetl
        if (tabLocs.size(1) < 1) {
          rtDynamicBoundsError(1, 1, tabLocs.size(1), db_emlrtBCI);
        }
        // note regexp is not supported for code generation
        if (ii_size[1] < 1) {
          rtDynamicBoundsError(1, 1, ii_size[1], eb_emlrtBCI);
        }
        if (static_cast<double>(ii_data) - 1.0 < 1.0) {
          loop_ub = 0;
        } else {
          if (lineStr.size(1) < 1) {
            rtDynamicBoundsError(1, 1, lineStr.size(1), ib_emlrtBCI);
          }
          if ((ii_data - 1 < 1) || (ii_data - 1 > lineStr.size(1))) {
            rtDynamicBoundsError(ii_data - 1, 1, lineStr.size(1), jb_emlrtBCI);
          }
          loop_ub = ii_data - 1;
        }
        configType.set_size(1, loop_ub);
        for (i = 0; i < loop_ub; i++) {
          configType[i] = lineStr[i];
        }
        if (tabLocs[0] + 1U > static_cast<unsigned int>(lineStr.size(1))) {
          i = 0;
          match_idx = 0;
        } else {
          i = static_cast<int>(tabLocs[0] + 1U);
          if ((i < 1) || (i > lineStr.size(1))) {
            rtDynamicBoundsError(i, 1, lineStr.size(1), gb_emlrtBCI);
          }
          i--;
          if (lineStr.size(1) < 1) {
            rtDynamicBoundsError(lineStr.size(1), 1, lineStr.size(1),
                                 hb_emlrtBCI);
          }
          match_idx = lineStr.size(1);
        }
        loop_ub = match_idx - i;
        configValStr.set_size(1, loop_ub);
        for (match_idx = 0; match_idx < loop_ub; match_idx++) {
          configValStr[match_idx] = lineStr[i + match_idx];
        }
        if (coder::internal::c_strcmp(configType)) {
          creal_T x;
          unsigned int in;
          x = coder::internal::str2double(configValStr);
          d = std::round(x.re);
          if (d < 4.294967296E+9) {
            if (d >= 0.0) {
              in = static_cast<unsigned int>(d);
            } else {
              in = 0U;
            }
          } else if (d >= 4.294967296E+9) {
            in = MAX_uint32_T;
          } else {
            in = 0U;
          }
          r.ID = in;
          if (in <= 0U) {
            h_rtErrorWithMessageID(j_emlrtRTEI.fName, j_emlrtRTEI.lineNo);
          }
          coder::mustBeInteger(static_cast<double>(in));
        } else if (coder::internal::d_strcmp(configType)) {
          creal_T x;
          x = coder::internal::str2double(configValStr);
          if (!(x.re >= 0.0)) {
            j_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
          }
          r.channelCenterFreqMHz = x.re;
        } else if (!coder::internal::e_strcmp(configType)) {
          if (coder::internal::f_strcmp(configType)) {
            creal_T x;
            unsigned short b_in;
            x = coder::internal::str2double(configValStr);
            d = std::round(x.re);
            if (d < 65536.0) {
              if (d >= 0.0) {
                b_in = static_cast<unsigned short>(d);
              } else {
                b_in = 0U;
              }
            } else if (d >= 65536.0) {
              b_in = MAX_uint16_T;
            } else {
              b_in = 0U;
            }
            r.portData = b_in;
            if (b_in <= 0) {
              h_rtErrorWithMessageID(j_emlrtRTEI.fName, j_emlrtRTEI.lineNo);
            }
            coder::mustBeInteger(static_cast<double>(b_in));
          } else if (coder::internal::g_strcmp(configType)) {
            creal_T x;
            x = coder::internal::str2double(configValStr);
            if (!(x.re > 0.0)) {
              h_rtErrorWithMessageID(j_emlrtRTEI.fName, j_emlrtRTEI.lineNo);
            }
            r.Fs = x.re;
          } else if (coder::internal::h_strcmp(configType)) {
            creal_T x;
            x = coder::internal::str2double(configValStr);
            r.tagFreqMHz = x.re;
          } else if (coder::internal::i_strcmp(configType)) {
            creal_T x;
            x = coder::internal::str2double(configValStr);
            if (!(x.re > 0.0)) {
              h_rtErrorWithMessageID(j_emlrtRTEI.fName, j_emlrtRTEI.lineNo);
            }
            r.tp = x.re;
          } else if (coder::internal::j_strcmp(configType)) {
            creal_T x;
            x = coder::internal::str2double(configValStr);
            if (!(x.re > 0.0)) {
              h_rtErrorWithMessageID(j_emlrtRTEI.fName, j_emlrtRTEI.lineNo);
            }
            r.tip = x.re;
          } else if (coder::internal::k_strcmp(configType)) {
            creal_T x;
            x = coder::internal::str2double(configValStr);
            if (!(x.re >= 0.0)) {
              j_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
            }
            r.tipu = x.re;
          } else if (coder::internal::l_strcmp(configType)) {
            creal_T x;
            x = coder::internal::str2double(configValStr);
            if (!(x.re >= 0.0)) {
              j_rtErrorWithMessageID(sc_emlrtRTEI.fName, sc_emlrtRTEI.lineNo);
            }
            r.tipj = x.re;
          } else if (coder::internal::m_strcmp(configType)) {
            creal_T x;
            unsigned char c_in;
            x = coder::internal::str2double(configValStr);
            d = std::round(x.re);
            if (d < 256.0) {
              if (d >= 0.0) {
                c_in = static_cast<unsigned char>(d);
              } else {
                c_in = 0U;
              }
            } else if (d >= 256.0) {
              c_in = MAX_uint8_T;
            } else {
              c_in = 0U;
            }
            r.K = c_in;
            if (c_in <= 0) {
              h_rtErrorWithMessageID(j_emlrtRTEI.fName, j_emlrtRTEI.lineNo);
            }
            coder::mustBeInteger(static_cast<double>(c_in));
          } else if (!coder::internal::n_strcmp(configType)) {
            if (coder::internal::o_strcmp(configType)) {
              str2matrix(configValStr, r1);
              val.set_size(r1.size(0), r1.size(1));
              match_idx = r1.size(0) * r1.size(1);
              for (i = 0; i < match_idx; i++) {
                val[i] = r1[i].re;
              }
              coder::internal::validator_check_size(val, r.excldFreqs);
            } else if (coder::internal::p_strcmp(configType)) {
              creal_T x;
              x = coder::internal::str2double(configValStr);
              if (!(x.re > 0.0)) {
                h_rtErrorWithMessageID(j_emlrtRTEI.fName, j_emlrtRTEI.lineNo);
              }
              if (!(x.re < 1.0)) {
                rtErrorWithMessageID("1", n_emlrtRTEI.fName,
                                     n_emlrtRTEI.lineNo);
              }
              r.falseAlarmProb = x.re;
            } else if (!coder::internal::q_strcmp(configType)) {
              if (coder::internal::r_strcmp(configType)) {
                r.logPath.Value.set_size(1, loop_ub);
                for (match_idx = 0; match_idx < loop_ub; match_idx++) {
                  r.logPath.Value[match_idx] = lineStr[i + match_idx];
                }
              } else if (coder::internal::s_strcmp(configType)) {
                creal_T x;
                unsigned int in;
                x = coder::internal::str2double(configValStr);
                d = std::round(x.re);
                if (d < 4.294967296E+9) {
                  if (d >= 0.0) {
                    in = static_cast<unsigned int>(d);
                  } else {
                    in = 0U;
                  }
                } else if (d >= 4.294967296E+9) {
                  in = MAX_uint32_T;
                } else {
                  in = 0U;
                }
                r.startIndex = in;
                coder::mustBeInteger(static_cast<double>(in));
              }
            }
          }
        }
        // Stop when we have finished reading this entry.
        if (coder::b_feof(static_cast<double>(fid)) == 1.0) {
          done = true;
        } else {
          if ((static_cast<int>(static_cast<unsigned int>(configNum) + 1U) <
               1) ||
              (static_cast<int>(static_cast<unsigned int>(configNum) + 1U) >
               b_i)) {
            rtDynamicBoundsError(
                static_cast<int>(static_cast<unsigned int>(configNum) + 1U), 1,
                b_i, fb_emlrtBCI);
          }
          if (coder::b_ftell(static_cast<double>(fid)) ==
              sepByte[static_cast<int>(static_cast<unsigned int>(configNum))]) {
            done = true;
          }
        }
      } else if (coder::b_feof(static_cast<double>(fid)) == 1.0) {
        done = true;
      } else {
        if ((static_cast<int>(static_cast<unsigned int>(configNum) + 1U) < 1) ||
            (static_cast<int>(static_cast<unsigned int>(configNum) + 1U) >
             b_i)) {
          rtDynamicBoundsError(
              static_cast<int>(static_cast<unsigned int>(configNum) + 1U), 1,
              b_i, kb_emlrtBCI);
        }
        if (coder::b_ftell(static_cast<double>(fid)) ==
            sepByte[static_cast<int>(static_cast<unsigned int>(configNum))]) {
          done = true;
        }
      }
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);
  coder::internal::cfclose(static_cast<double>(fid));
  Config.contents = r;
  // Do we update the tip and tipu or use the ones that were adapted from
  // the previous detections? Probably just use the file. The supervisor
  // will have access to the detected pulses and can update these values if
  // it sees fit.
}

//
// Arguments    : const coder::array<char, 2U> &configPath
//                const coder::array<char, 2U> &thresholdCachePath
// Return Type  : void
//
void uavrt_detection(const coder::array<char, 2U> &configPath,
                     const coder::array<char, 2U> &thresholdCachePath)
{
  static coder::dsp::AsyncBuffer asyncDataBuff;
  static coder::dsp::b_AsyncBuffer asyncTimeBuff;
  static coder::dsp::c_AsyncBuffer asyncWriteBuff;
  static rtBoundsCheckInfo ab_emlrtBCI{
      302,              // lineNo
      "timeVector",     // aName
      "uavrt_detection" // fName
  };
  static rtBoundsCheckInfo bb_emlrtBCI{
      317,              // lineNo
      "t",              // aName
      "uavrt_detection" // fName
  };
  static rtBoundsCheckInfo cb_emlrtBCI{
      416,              // lineNo
      "X.x",            // aName
      "uavrt_detection" // fName
  };
  static rtBoundsCheckInfo db_emlrtBCI{
      421,              // lineNo
      "X.x",            // aName
      "uavrt_detection" // fName
  };
  static rtBoundsCheckInfo eb_emlrtBCI{
      427,              // lineNo
      "X.x",            // aName
      "uavrt_detection" // fName
  };
  static rtBoundsCheckInfo fb_emlrtBCI{
      432,              // lineNo
      "X.x",            // aName
      "uavrt_detection" // fName
  };
  static rtBoundsCheckInfo gb_emlrtBCI{
      515,              // lineNo
      "X.ps_pos.pl",    // aName
      "uavrt_detection" // fName
  };
  static rtBoundsCheckInfo hb_emlrtBCI{
      520,               // lineNo
      "ps_pre_struc.pl", // aName
      "uavrt_detection"  // fName
  };
  static rtBoundsCheckInfo ib_emlrtBCI{
      526,              // lineNo
      "pulsesToSkip",   // aName
      "uavrt_detection" // fName
  };
  static rtBoundsCheckInfo jb_emlrtBCI{
      555,              // lineNo
      "X.ps_pos.pl",    // aName
      "uavrt_detection" // fName
  };
  static rtBoundsCheckInfo kb_emlrtBCI{
      571,              // lineNo
      "pulsesToSkip",   // aName
      "uavrt_detection" // fName
  };
  static rtDoubleCheckInfo q_emlrtDCI{
      247,              // lineNo
      "uavrt_detection" // fName
  };
  static rtDoubleCheckInfo r_emlrtDCI{
      247,              // lineNo
      "uavrt_detection" // fName
  };
  ComplexSingleSamplesUDPReceiver udpReceiver;
  PulseInfoStruct pulseInfoStruct;
  b_waveform X;
  coder::b_captured_var Config;
  coder::c_captured_var overlapSamples;
  coder::c_captured_var sampsForKPulses;
  coder::c_captured_var stftOverlapFraction;
  coder::captured_var b_configPath;
  coder::datetime b_this;
  pulsestats lobj_12[4];
  pulsestats lobj_21[2];
  pulsestats lobj_16;
  pulsestats lobj_17;
  pulsestats lobj_18;
  pulsestats *pulseStatsPriori;
  threshold _in;
  waveform b_X;
  waveform lobj_13;
  waveform lobj_20;
  waveform *Xhold;
  wfmstft lobj_19[3];
  wfmstft lobj_11;
  wfmstft lobj_14;
  wfmstft lobj_15;
  coder::array<c_struct_T, 2U> ps_pre_struc_clst;
  coder::array<c_struct_T, 2U> ps_pre_struc_pl;
  coder::array<c_struct_T, 1U> c_X;
  coder::array<creal32_T, 2U> iqDataToWrite;
  coder::array<creal32_T, 1U> b_iqDataToWrite;
  coder::array<creal32_T, 1U> c_iqDataToWrite;
  coder::array<creal32_T, 1U> dataWriterBuffData;
  coder::array<creal32_T, 1U> x;
  coder::array<cuint8_T, 1U> r;
  coder::array<double, 2U> b_varargin_1;
  coder::array<double, 2U> b_x;
  coder::array<double, 2U> ps_pre_struc_cpki;
  coder::array<double, 1U> b_timeVector;
  coder::array<double, 1U> d_varargin_1;
  coder::array<double, 1U> t;
  coder::array<double, 1U> timeVector;
  coder::array<float, 1U> r1;
  coder::array<char, 2U> currDir;
  coder::array<char, 2U> varargin_1;
  coder::array<char, 2U> waveformRecordPath;
  coder::array<boolean_T, 2U> ps_pre_struc_cmsk;
  coder::array<boolean_T, 2U> pulsesToSkip;
  coder::array<boolean_T, 2U> r3;
  coder::array<boolean_T, 1U> r2;
  c_struct_T detectorPulse;
  c_struct_T pulseStatsPriori_tmp;
  creal_T dcv[1000];
  creal32_T dataReceived_data[1024];
  creal32_T b_dataReceived_data[1023];
  creal32_T exampleData[1000];
  double doublesBuffer[12];
  double ps_pre_struc_tmplt[2];
  double d;
  double d1;
  double d2;
  double dataWriterSamples;
  double expectedNextTimeStamp;
  double framesReceived;
  double groupSeqCounter;
  double previousPulseTime;
  double ps_pre_struc_fend;
  double ps_pre_struc_fp;
  double ps_pre_struc_fstart;
  double ps_pre_struc_t_ip;
  double ps_pre_struc_t_ipj;
  double ps_pre_struc_t_ipu;
  double ps_pre_struc_t_p;
  double segmentsProcessed;
  double startTime;
  double trackedCount;
  int iv[2];
  int b_currDir;
  int dataWriterFileID;
  int i;
  int i1;
  int loop_ub;
  int loop_ub_tmp;
  unsigned int u1;
  unsigned short u2;
  signed char fileid;
  char mode;
  char suggestedMode;
  boolean_T cleanBuffer;
  boolean_T configUpdatedFlag;
  boolean_T fLock;
  boolean_T resetBuffersFlag;
  boolean_T staleDataFlag;
  if (!isInitialized_uavrt_detection) {
    uavrt_detection_initialize();
  }
  asyncDataBuff.pBuffer.matlabCodegenIsDeleted = true;
  asyncDataBuff.matlabCodegenIsDeleted = true;
  asyncTimeBuff.pBuffer.matlabCodegenIsDeleted = true;
  asyncTimeBuff.matlabCodegenIsDeleted = true;
  asyncWriteBuff.pBuffer.matlabCodegenIsDeleted = true;
  asyncWriteBuff.matlabCodegenIsDeleted = true;
  loop_ub = configPath.size(1);
  b_configPath.contents.set_size(1, configPath.size(1));
  for (i = 0; i < loop_ub; i++) {
    b_configPath.contents[i] = configPath[i];
  }
  //  configPath            - Fully qualified path to detect config file
  //  thresholdCachePath    - Fully qualified path to where the threshold cache
  //  files are stored.
  //                          If not specified thresholds will be re-generated.
  // Needed for usleep function in generated code
  loop_ub = thresholdCachePath.size(1);
  globalThresholdCachePath.set_size(1, thresholdCachePath.size(1));
  for (i = 0; i < loop_ub; i++) {
    globalThresholdCachePath[i] = thresholdCachePath[i];
  }
  Config.contents.init();
  // Build empty config object
  updateconfig(Config, b_configPath);
  // Update (fill) the configuration
  configUpdatedFlag = true;
  coder::pwd(currDir);
  //  %Attempts at catching a failed getcwd() call
  //  % Get current working directory
  //  if coder.target('MATLAB')
  //        currDir = pwd;
  //  else
  //       coder.cinclude('unistd.h');
  //       nullVal = coder.opaque('char*', 'NULL', 'HeaderFile', 'stdio.h');
  //       retVal = nullVal;
  //       bufferTemplate = repmat('c', 1, 200);
  //       untokenizedDir = coder.nullcopy(bufferTemplate);
  //       retVal = coder.ceval('getcwd', coder.ref(untokenizedDir), 200);
  //       if retVal == nullVal
  //           % Do some error handling here
  //           currDir = 'current_working_directory_error';
  //       else
  //           currDir = strtok(untokenizedDir, char(0));
  //       end
  //  end
  varargin_1.set_size(1, currDir.size(1) + 1);
  loop_ub_tmp = currDir.size(1);
  for (i = 0; i < loop_ub_tmp; i++) {
    varargin_1[i] = currDir[i];
  }
  varargin_1[currDir.size(1)] = '\x00';
  std::printf("Curr Directory is: %s\n", &varargin_1[0]);
  std::fflush(stdout);
  std::printf("ROS2 setup disabled\n");
  std::fflush(stdout);
  pulseStatsPriori_tmp.A = makepulsestruc(
      pulseStatsPriori_tmp.t_next, pulseStatsPriori_tmp.mode,
      pulseStatsPriori_tmp.P, pulseStatsPriori_tmp.SNR, pulseStatsPriori_tmp.yw,
      pulseStatsPriori_tmp.t_0, pulseStatsPriori_tmp.t_f,
      pulseStatsPriori_tmp.fp, pulseStatsPriori_tmp.fstart,
      pulseStatsPriori_tmp.fend, pulseStatsPriori_tmp.det_dec,
      pulseStatsPriori_tmp.con_dec);
  pulseStatsPriori = lobj_21[1].init(
      Config.contents.tp, Config.contents.tip, Config.contents.tipu,
      Config.contents.tipj, pulseStatsPriori_tmp, pulseStatsPriori_tmp);
  //  % tp, tip, tipu
  //  % tipj, fp, fstart, fend, tmplt, mode
  //   % pl ,clst
  //  cmsk ,cpki)
  stftOverlapFraction.contents = 0.5;
  // Initialize and then set these variable needed for buffer reads
  overlapSamples.contents = 0.0;
  sampsForKPulses.contents = 0.0;
  updatebufferreadvariables(Config, stftOverlapFraction, overlapSamples,
                            sampsForKPulses, pulseStatsPriori);
  // 1024 plus a time stamp.
  std::printf("Startup set 1 complete. \n");
  std::fflush(stdout);
  //  Prepare data writing buffer
  //  Calculating the max size that would ever be needed for the buffer
  //  maxK    = 6;
  //  maxFs   = 912000/2;
  //  maxtp   = 0.04;
  //  maxtip  = 2;
  //  maxtipu = 0.1;
  //  maxpulseStatsPriori = pulsestats(maxtp,maxtip,maxtipu,[],[],[],[1
  //  1],pulse); Xmax = waveform([], maxFs, 0, maxpulseStatsPriori,
  //  stftOverlapFraction);
  //  [~,~,~,maxn_ws,~,~,maxN,maxM] = Xmax.getprioridependentprops(Xmax.ps_pre);
  //  sampsForMaxPulses = maxK*maxn_ws*(maxN+maxM+1+1);
  asyncDataBuff.init();
  asyncTimeBuff.init();
  std::printf("Startup set 2 complete. \n");
  std::fflush(stdout);
  // Write interval in seconds. 2.5*60*4000*32/8 should work out the 2.4Mb of
  // data at 4ksps.
  dataWriterSamples = std::ceil(10.0 / (1024.0 / Config.contents.Fs)) * 1025.0;
  asyncWriteBuff.init();
  // 600650 is the result of the nominal settings of ceil(150/(1024/4000)*1025.
  asyncWriteBuff.write();
  // Write to give Code the type. Read to remove data.
  asyncWriteBuff.read();
  d = std::round(Config.contents.ID);
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
  d1 = std::round(Config.contents.startIndex);
  if (d1 < 2.147483648E+9) {
    if (d1 >= -2.147483648E+9) {
      i1 = static_cast<int>(d1);
    } else {
      i1 = MIN_int32_T;
    }
  } else if (d1 >= 2.147483648E+9) {
    i1 = MAX_int32_T;
  } else {
    i1 = 0;
  }
  coder::b_sprintf(i, i1, currDir);
  // dataWriterFileID    =
  // fopen(fullfile(Config.logPath,dataRecordFilename),'w');%Use this after
  // upgrade to R2023b that supports full file
  varargin_1.set_size(
      1, (Config.contents.logPath.Value.size(1) + currDir.size(1)) + 1);
  loop_ub_tmp = Config.contents.logPath.Value.size(1);
  for (i = 0; i < loop_ub_tmp; i++) {
    varargin_1[i] = Config.contents.logPath.Value[i];
  }
  varargin_1[Config.contents.logPath.Value.size(1)] = '/';
  loop_ub = currDir.size(1);
  for (i = 0; i < loop_ub; i++) {
    varargin_1[(i + Config.contents.logPath.Value.size(1)) + 1] = currDir[i];
  }
  fileid = coder::internal::cfopen(varargin_1, "wb");
  dataWriterFileID = fileid;
  if (fileid == -1) {
    std::printf(
        "UAV-RT: Error opening/creating data record file with error:\n");
    std::fflush(stdout);
  }
  std::printf("Startup set 3 complete. \n");
  std::fflush(stdout);
  // Define a pulsestats structure that isn't an object.
  // This is needed for the loop, as Matlab coder has problems seeing
  // that the pulsestats handle object is set for all execution paths.
  // Holding all these properties in a structure rather than the
  // pulsestats object addressed this problem.
  // Needed to let coder know that some of these will be varying in size
  // https://www.mathworks.com/help/simulink/ug/how-working-with-matlab-classes-is-different-for-code-generation.html
  mode = 'D';
  // dims 0 if fixed, 1 if variable
  std::printf("Startup set 4 complete. \n");
  std::fflush(stdout);
  ps_pre_struc_t_p = 0.0;
  ps_pre_struc_t_ip = 0.0;
  ps_pre_struc_t_ipu = 0.0;
  ps_pre_struc_t_ipj = 0.0;
  ps_pre_struc_fp = 0.0;
  ps_pre_struc_fstart = 0.0;
  ps_pre_struc_fend = 0.0;
  ps_pre_struc_tmplt[0] = 1.0;
  ps_pre_struc_tmplt[1] = 1.0;
  ps_pre_struc_pl.set_size(1, 1);
  ps_pre_struc_pl[0] = pulseStatsPriori_tmp;
  detectorPulse.A = makepulsestruc(
      detectorPulse.t_next, detectorPulse.mode, detectorPulse.P,
      detectorPulse.SNR, detectorPulse.yw, detectorPulse.t_0, detectorPulse.t_f,
      detectorPulse.fp, detectorPulse.fstart, detectorPulse.fend,
      detectorPulse.det_dec, detectorPulse.con_dec);
  ps_pre_struc_clst.set_size(1, 1);
  ps_pre_struc_clst[0] = detectorPulse;
  ps_pre_struc_cmsk.set_size(1, 1);
  ps_pre_struc_cmsk[0] = false;
  ps_pre_struc_cpki.set_size(1, 1);
  ps_pre_struc_cpki[0] = rtNaN;
  b_currDir = udpSenderSetup(50000.0);
  pulseInfoStruct.udpSender = b_currDir;
  if (b_currDir <= 0) {
    rtErrorWithMessageID(emlrtRTEI.fName, emlrtRTEI.lineNo);
  }
  //  The specified frame size must exactly match the size of udp packets sent
  //  out by the channelizer.
  udpReceiver.init(Config.contents.portData);
  std::printf("Startup set 5 complete. \n");
  std::fflush(stdout);
  //  Preallocate X and Xhold so that coder knows the data types.
  coder::wgn(dcv);
  for (i = 0; i < 1000; i++) {
    exampleData[i].re = static_cast<float>(dcv[i].re);
    exampleData[i].im = static_cast<float>(dcv[i].im);
  }
  _in.init(Config.contents.falseAlarmProb);
  Xhold = lobj_20.init(exampleData, Config.contents.Fs, pulseStatsPriori, _in);
  // THRESHOLD Constructs an instance of this class
  // INPUTS:
  //    pf  probability of false alarm
  //
  X.init(exampleData, Config.contents.Fs, pulseStatsPriori, lobj_21[0],
         lobj_19[2]);
  Xhold->spectro(lobj_19[1]);
  X.spectro(lobj_19[0]);
  std::printf("Startup set 6 complete. \n");
  std::fflush(stdout);
  // Initialize loop variables
  resetBuffersFlag = true;
  framesReceived = 0.0;
  segmentsProcessed = 0.0;
  suggestedMode = 'S';
  fLock = false;
  staleDataFlag = true;
  // Force buffer  flush on start
  cleanBuffer = true;
  trackedCount = 0.0;
  b_this.init();
  startTime = std::round(b_this.data.re / 1000.0 * 1.0E+6) / 1.0E+6;
  // sysClockElapsedTime = 0;
  previousPulseTime = 0.0;
  iqDataToWrite.set_size(0, 0);
  groupSeqCounter = 0.0;
  std::printf("Startup set 7 complete. Starting processing... \n");
  std::fflush(stdout);
  expectedNextTimeStamp = 0.0;
  iv[0] = 1;
  iv[1] = 1023;
  while (1) {
    double missingSamples;
    double timeDiff;
    double timeStamp;
    int pulseCount;
    unsigned int timeStampNanoSec;
    unsigned int timeStampSec;
    if (resetBuffersFlag) {
      asyncDataBuff.reset();
      asyncTimeBuff.reset();
      asyncWriteBuff.reset();
      resetBuffersFlag = false;
      cleanBuffer = true;
    }
    //             %% Get data
    udpReceiver.receive(dataReceived_data);
    //             %% Flush UDP buffer if data in the buffer is stale.
    if (staleDataFlag) {
      std::printf("********STALE DATA FLAG: %u**************\n", 1U);
      std::fflush(stdout);
      std::printf("********CLEARING UDP DATA BUFFER*********\n");
      std::fflush(stdout);
      udpReceiverClear(udpReceiver.udpReceiver);
      staleDataFlag = false;
      std::printf("********RESETTING TIMES******************\n");
      std::fflush(stdout);
      // startTime = round(posixtime(datetime('now'))*1000000)/1000000;
      framesReceived = 0.0;
      b_this.init();
      startTime = std::round(b_this.data.re / 1000.0 * 1.0E+6) / 1.0E+6;
      coder::tic();
    }
    //             %% Wait for new data if none ready, else put data in buffers
    std::memcpy((void *)&timeStampSec, (void *)&dataReceived_data[0].re,
                (unsigned int)((size_t)1 * sizeof(unsigned int)));
    std::memcpy((void *)&timeStampNanoSec, (void *)&dataReceived_data[0].im,
                (unsigned int)((size_t)1 * sizeof(unsigned int)));
    timeStamp = static_cast<double>(timeStampSec) +
                1.0E-9 * static_cast<double>(timeStampNanoSec);
    coder::internal::indexShapeCheck(1024, iv);
    if (framesReceived == 0.0) {
      iqDataToWrite.set_size(1023, 1);
      for (i = 0; i < 1023; i++) {
        iqDataToWrite[i] = dataReceived_data[i + 1];
      }
    } else {
      timeDiff = timeStamp - expectedNextTimeStamp;
      d2 = Config.contents.tp / 2.0;
      if (std::abs(timeDiff) < d2) {
        iqDataToWrite.set_size(1023, 1);
        for (i = 0; i < 1023; i++) {
          iqDataToWrite[i] = dataReceived_data[i + 1];
        }
      } else if ((timeDiff >= d2) && (timeDiff < Config.contents.tip)) {
        unsigned long u;
        // missed samples but not a whole lot
        missingSamples = std::round(timeDiff * Config.contents.Fs);
        if (missingSamples < 1.8446744073709552E+19) {
          if (missingSamples >= 0.0) {
            u = static_cast<unsigned long>(missingSamples);
          } else {
            u = 0UL;
          }
        } else if (missingSamples >= 1.8446744073709552E+19) {
          u = MAX_uint64_T;
        } else {
          u = 0UL;
        }
        std::printf(
            "Missing samples detected. Filling with zeros for %lu samples.", u);
        std::fflush(stdout);
        if (!(missingSamples >= 0.0)) {
          rtNonNegativeError(missingSamples, q_emlrtDCI);
        }
        if (missingSamples != static_cast<int>(missingSamples)) {
          rtIntegerError(missingSamples, r_emlrtDCI);
        }
        loop_ub = static_cast<int>(missingSamples);
        r.set_size(static_cast<int>(missingSamples));
        for (i = 0; i < loop_ub; i++) {
          r[i].re = 0U;
          r[i].im = 0U;
        }
        b_currDir = static_cast<int>(missingSamples) + 1023;
        c_iqDataToWrite.set_size(b_currDir);
        for (i = 0; i < loop_ub; i++) {
          c_iqDataToWrite[i].re = 0.0F;
          c_iqDataToWrite[i].im = static_cast<signed char>(r[i].im);
        }
        for (i = 0; i < 1023; i++) {
          c_iqDataToWrite[i + static_cast<int>(missingSamples)] =
              dataReceived_data[i + 1];
        }
        iqDataToWrite.set_size(b_currDir, 1);
        for (i = 0; i < b_currDir; i++) {
          iqDataToWrite[i] = c_iqDataToWrite[i];
        }
      } else if (((timeDiff >= d2) && (timeDiff >= Config.contents.tip)) ||
                 (timeDiff < -Config.contents.tp / 2.0)) {
        //  %missed a lot of samples. Reset buffers
        // predictions is ahead of recently received packet. Shouldn't ever
        // happen. If it is, reset the incoming data
        staleDataFlag = true;
        resetBuffersFlag = true;
        suggestedMode = 'S';
        iqDataToWrite.set_size(0, 1);
      }
    }
    pulseCount = iqDataToWrite.size(0) * iqDataToWrite.size(1);
    b_currDir = pulseCount - 1;
    if (pulseCount - 1 < 0) {
      b_varargin_1.set_size(1, 0);
    } else {
      b_varargin_1.set_size(1, pulseCount);
      for (i = 0; i <= b_currDir; i++) {
        b_varargin_1[i] = i;
      }
    }
    timeDiff = 1.0 / Config.contents.Fs;
    loop_ub = b_varargin_1.size(1);
    timeVector.set_size(b_varargin_1.size(1));
    for (i = 0; i < loop_ub; i++) {
      timeVector[i] = timeStamp + timeDiff * b_varargin_1[i];
    }
    expectedNextTimeStamp = timeStamp + timeDiff * 1023.0;
    framesReceived++;
    // Write out data and time.
    b_iqDataToWrite = iqDataToWrite.reshape(pulseCount);
    asyncDataBuff.write(b_iqDataToWrite);
    asyncTimeBuff.write(timeVector);
    std::copy(&dataReceived_data[1], &dataReceived_data[1024],
              &b_dataReceived_data[0]);
    asyncWriteBuff.write(b_dataReceived_data);
    if (asyncWriteBuff.get_NumUnreadSamples() >= dataWriterSamples) {
      asyncWriteBuff.read(dataWriterBuffData);
      if (dataWriterFileID != -1) {
        interleaveComplexVector(dataWriterBuffData, r1);
        coder::b_fwrite(static_cast<double>(dataWriterFileID), r1);
      }
    }
    //                 %% Process data if there is enough in the buffers
    if (asyncDataBuff.get_NumUnreadSamples() >=
        sampsForKPulses.contents + overlapSamples.contents) {
      double processingStartToc;
      d2 = std::round(sampsForKPulses.contents);
      if (d2 < 4.294967296E+9) {
        if (d2 >= 0.0) {
          timeStampSec = static_cast<unsigned int>(d2);
        } else {
          timeStampSec = 0U;
        }
      } else if (d2 >= 4.294967296E+9) {
        timeStampSec = MAX_uint32_T;
      } else {
        timeStampSec = 0U;
      }
      d2 = std::round(overlapSamples.contents);
      if (d2 < 4.294967296E+9) {
        if (d2 >= 0.0) {
          timeStampNanoSec = static_cast<unsigned int>(d2);
        } else {
          timeStampNanoSec = 0U;
        }
      } else if (d2 >= 4.294967296E+9) {
        timeStampNanoSec = MAX_uint32_T;
      } else {
        timeStampNanoSec = 0U;
      }
      std::printf("++++++++++BUFFER FULL, PROCESSING SEGMENT -- "
                  "sampsForKPulses: %u, overlapSamples: %u,\n",
                  timeStampSec, timeStampNanoSec);
      std::fflush(stdout);
      missingSamples = coder::toc();
      processingStartToc = missingSamples;
      if (cleanBuffer) {
        // Overlap reads back into the buffer, but there
        // isn't anything back there on the first segment.
        // Using an overlap will fill the output with
        // overlapSamples of zeros at beginning
        // of x if you specify overlap here. Don't want that
        // so specify zero overlap for first read after
        // cleaning buffer
        asyncDataBuff.read(sampsForKPulses.contents, x);
        asyncTimeBuff.read(sampsForKPulses.contents, t);
        cleanBuffer = false;
      } else {
        asyncDataBuff.read(sampsForKPulses.contents, overlapSamples.contents,
                           x);
        asyncTimeBuff.read(sampsForKPulses.contents, overlapSamples.contents,
                           t);
      }
      if (loop_ub < 1) {
        rtDynamicBoundsError(loop_ub, 1, loop_ub, ab_emlrtBCI);
      }
      b_this.init();
      std::printf("Sample elapsed seconds: %f \t Posix elapsed seconds: %f \n",
                  timeVector[timeVector.size(0) - 1] - startTime,
                  std::round(b_this.data.re / 1000.0 * 1.0E+6) / 1.0E+6 -
                      startTime);
      std::fflush(stdout);
      // Check the timestamps in the buffer for gaps larger
      // than the max interpulse uncertainty. If there are
      // enough dropped packets such that the time is shifted
      // by more than the interpulse uncertainty, then the
      // detection will likely fail or produces bad results. In
      // this case. Skip the processing and clear the buffer.
      coder::diff(t, timeVector);
      loop_ub = timeVector.size(0);
      b_timeVector.set_size(timeVector.size(0));
      for (i = 0; i < loop_ub; i++) {
        b_timeVector[i] = timeVector[i] - timeDiff;
      }
      missingSamples = coder::sum(b_timeVector);
      if ((Config.contents.K > 1.0) &&
          (missingSamples > Config.contents.tipu + Config.contents.tipj)) {
        std::printf("Significant time differences found in timestamp record. "
                    "Skipping processing and clearing buffers.\n");
        std::fflush(stdout);
        resetBuffersFlag = true;
        staleDataFlag = true;
      } else {
        float validatedHoleFilling_idx_0;
        unsigned int validatedHoleFilling[3];
        int j;
        int nPulseList_tmp;
        unsigned int varargin_3;
        char c_varargin_1[2];
        if (t.size(0) < 1) {
          rtDynamicBoundsError(1, 1, t.size(0), bb_emlrtBCI);
        }
        std::printf("Running...Building priori and waveform. \n");
        std::fflush(stdout);
        // Set the priori info
        if (configUpdatedFlag) {
          // Initialize states for operational modes
          fLock = false;
          //  switch Config.opMode
          missingSamples =
              1.0E-5 * std::abs(Config.contents.tagFreqMHz -
                                Config.contents.channelCenterFreqMHz);
          timeStamp = std::ceil(Config.contents.Fs / 2.0);
          pulseStatsPriori = lobj_17.init(
              Config.contents.tp, Config.contents.tip, Config.contents.tipu,
              Config.contents.tipj, missingSamples, missingSamples - timeStamp,
              missingSamples + timeStamp, pulseStatsPriori_tmp,
              pulseStatsPriori_tmp);
          configUpdatedFlag = false;
        } else {
          pulseStatsPriori = lobj_18.c_init(
              ps_pre_struc_t_p, ps_pre_struc_t_ip, ps_pre_struc_t_ipu,
              ps_pre_struc_t_ipj, ps_pre_struc_fp, ps_pre_struc_fstart,
              ps_pre_struc_fend, ps_pre_struc_tmplt, (char *)&mode,
              ps_pre_struc_pl, ps_pre_struc_clst, ps_pre_struc_cmsk,
              ps_pre_struc_cpki);
        }
        missingSamples = pulseStatsPriori->fstart;
        timeStamp = pulseStatsPriori->fend;
        std::printf("ps_pre.fstart and ps.pre.fend before making waveform X: "
                    "\t %f \t to \t %f. \n",
                    missingSamples, timeStamp);
        std::fflush(stdout);
        // (1) is for coder so it knows it is a scalar
        //                         %% PRIMARY PROCESSING BLOCK
        // Prep waveform for processing/detection
        _in.init(Config.contents.falseAlarmProb);
        b_X.init(x, Config.contents.Fs, t[0], pulseStatsPriori, _in, lobj_16,
                 lobj_15);
        b_X.K = Config.contents.K;
        d2 = std::round(b_X.N);
        if (d2 < 4.294967296E+9) {
          if (d2 >= 0.0) {
            timeStampSec = static_cast<unsigned int>(d2);
          } else {
            timeStampSec = 0U;
          }
        } else if (d2 >= 4.294967296E+9) {
          timeStampSec = MAX_uint32_T;
        } else {
          timeStampSec = 0U;
        }
        d2 = std::round(b_X.M);
        if (d2 < 4.294967296E+9) {
          if (d2 >= 0.0) {
            timeStampNanoSec = static_cast<unsigned int>(d2);
          } else {
            timeStampNanoSec = 0U;
          }
        } else if (d2 >= 4.294967296E+9) {
          timeStampNanoSec = MAX_uint32_T;
        } else {
          timeStampNanoSec = 0U;
        }
        d2 = std::round(b_X.J);
        if (d2 < 4.294967296E+9) {
          if (d2 >= 0.0) {
            varargin_3 = static_cast<unsigned int>(d2);
          } else {
            varargin_3 = 0U;
          }
        } else if (d2 >= 4.294967296E+9) {
          varargin_3 = MAX_uint32_T;
        } else {
          varargin_3 = 0U;
        }
        coder::internal::validate_print_arguments(
            timeStampSec, timeStampNanoSec, varargin_3, validatedHoleFilling);
        std::printf("Current interpulse params || N: %u, M: %u, J: %u,\n",
                    validatedHoleFilling[0], validatedHoleFilling[1],
                    validatedHoleFilling[2]);
        std::fflush(stdout);
        b_X.setprioridependentprops(b_X.ps_pre);
        timeStampSec = static_cast<unsigned int>(b_X.x.size(1));
        std::printf("Samples in waveform: %u \n", timeStampSec);
        std::fflush(stdout);
        missingSamples = coder::toc();
        std::printf("Computing STFT...");
        std::fflush(stdout);
        b_X.spectro(lobj_14);
        missingSamples = coder::toc() - missingSamples;
        std::printf("complete. Elapsed time: %f seconds \n", missingSamples);
        std::fflush(stdout);
        std::printf("Building weighting matrix...");
        std::fflush(stdout);
        missingSamples = coder::toc();
        b_X.setweightingmatrix();
        missingSamples = coder::toc() - missingSamples;
        std::printf("complete. Elapsed time: %f seconds \n", missingSamples);
        std::fflush(stdout);
        if (suggestedMode == 'S') {
          b_currDir = 0;
        } else if (suggestedMode == 'C') {
          b_currDir = 1;
        } else if (suggestedMode == 'T') {
          b_currDir = 2;
        } else {
          b_currDir = -1;
        }
        switch (b_currDir) {
        case 0:
          if (fLock) {
            mode = 'I';
          } else {
            mode = 'D';
          }
          break;
        case 1:
          mode = 'C';
          break;
        case 2:
          mode = 'T';
          trackedCount++;
          break;
        default:
          std::printf("UAV-RT: Unsupported mode requested. Defaulting to "
                      "Discovery (D) mode.");
          std::fflush(stdout);
          mode = 'D';
          break;
        }
        missingSamples = coder::toc();
        if (segmentsProcessed == 0.0) {
          std::printf("Building thresholds...\n");
          std::fflush(stdout);
          _in = b_X.thresh;
          _in.makenewthreshold(b_X);
          b_X.thresh = _in;
        } else {
          std::printf("Setting thresholds from previous waveform...\n");
          std::fflush(stdout);
          // Setting the threshold takes too long to run in
          // real time if any of the dependent variables
          // change so we can't use.
          // X.thresh = X.thresh.setthreshold(X,Xhold);
          // We also don't want to simply hold the same
          // threshold from the last waveform:
          // X.thresh = Xhold.thresh;
          // We will hold the mu and sigma parameters
          // contant (Xhold.thresh1W will be the same as
          // the last segment, but we  update the
          // thresholds as the noise values change.
          _in = Xhold->thresh;
          _in.setthreshprops(Xhold->thresh.thresh1W, b_X);
          b_X.thresh = _in;
        }
        missingSamples = coder::toc() - missingSamples;
        std::printf(
            " \n \t Threshold setting complete. Elapsed time: %f seconds \n",
            missingSamples);
        std::fflush(stdout);
        timeStampSec = static_cast<unsigned int>(b_X.stft->S.size(1));
        std::printf("Time windows in S: %u \n", timeStampSec);
        std::fflush(stdout);
        missingSamples = coder::toc();
        if (d < 4.294967296E+9) {
          if (d >= 0.0) {
            timeStampSec = static_cast<unsigned int>(d);
          } else {
            timeStampSec = 0U;
          }
        } else if (d >= 4.294967296E+9) {
          timeStampSec = MAX_uint32_T;
        } else {
          timeStampSec = 0U;
        }
        doublesBuffer[0] = timeStampSec;
        std::memset(&doublesBuffer[1], 0, 11U * sizeof(double));
        //  % self.frequency_hz ...
        //  % self.start_time_seconds ...
        //  % self.predict_next_start_seconds ...
        //  % self.snr ...
        //  % self.stft_score ...
        //  % self.group_seq_counter ...
        //  % self.group_ind ...
        //  % self.group_snr ...
        //  % self.detection_status ...
        //  % self.confirmed_status ...
        //  % self.noise_psd ...
        udpSenderSendDoubles(pulseInfoStruct.udpSender, &doublesBuffer[0], 12U);
        c_varargin_1[0] = mode;
        c_varargin_1[1] = '\x00';
        std::printf("BEGINNING PROCESSING IN %s MODE \n", &c_varargin_1[0]);
        std::fflush(stdout);
        std::printf("====================================\n");
        std::fflush(stdout);
        std::printf(
            "First 5 entries of the real data block being processed are:\n");
        std::fflush(stdout);
        for (b_currDir = 0; b_currDir < 5; b_currDir++) {
          i = b_X.x.size(1);
          if (b_currDir + 1 > i) {
            rtDynamicBoundsError(b_currDir + 1, 1, i, cb_emlrtBCI);
          }
          validatedHoleFilling_idx_0 = b_X.x[b_currDir].re;
          std::printf("%.8f,", validatedHoleFilling_idx_0);
          std::fflush(stdout);
        }
        std::printf("\n");
        std::fflush(stdout);
        std::printf("First 5 entries of the imaginary data block being "
                    "processed are:\n");
        std::fflush(stdout);
        for (b_currDir = 0; b_currDir < 5; b_currDir++) {
          i = b_X.x.size(1);
          if (b_currDir + 1 > i) {
            rtDynamicBoundsError(b_currDir + 1, 1, i, db_emlrtBCI);
          }
          validatedHoleFilling_idx_0 = b_X.x[b_currDir].im;
          std::printf("%.8f,", validatedHoleFilling_idx_0);
          std::fflush(stdout);
        }
        std::printf("\n");
        std::fflush(stdout);
        std::printf(
            "Last 5 entries of the real data block being processed are:\n");
        std::fflush(stdout);
        i = b_X.x.size(1) - 5;
        i1 = b_X.x.size(1);
        i1 -= i;
        for (b_currDir = 0; b_currDir <= i1; b_currDir++) {
          j = b_X.x.size(1);
          pulseCount = i + b_currDir;
          if ((pulseCount < 1) || (pulseCount > j)) {
            rtDynamicBoundsError(pulseCount, 1, j, eb_emlrtBCI);
          }
          validatedHoleFilling_idx_0 = b_X.x[pulseCount - 1].re;
          std::printf("%.8f,", validatedHoleFilling_idx_0);
          std::fflush(stdout);
        }
        std::printf("\n");
        std::fflush(stdout);
        std::printf("Last 5 entries of the imaginary data block being "
                    "processed are:\n");
        std::fflush(stdout);
        i = b_X.x.size(1) - 5;
        i1 = b_X.x.size(1);
        i1 -= i;
        for (b_currDir = 0; b_currDir <= i1; b_currDir++) {
          j = b_X.x.size(1);
          pulseCount = i + b_currDir;
          if ((pulseCount < 1) || (pulseCount > j)) {
            rtDynamicBoundsError(pulseCount, 1, j, fb_emlrtBCI);
          }
          validatedHoleFilling_idx_0 = b_X.x[pulseCount - 1].im;
          std::printf("%.8f,", validatedHoleFilling_idx_0);
          std::fflush(stdout);
        }
        std::printf("\n");
        std::fflush(stdout);
        b_X.process(mode, Config.contents.excldFreqs);
        missingSamples = coder::toc() - missingSamples;
        std::printf("complete. Elapsed time: %f seconds \n", missingSamples);
        std::fflush(stdout);
        missingSamples = b_X.ps_pre->fstart;
        timeStamp = b_X.ps_pre->fend;
        std::printf("ps_pre.fstart and ps_pre.fend after PROCESS step : \t %f "
                    "\t to \t %f.\n",
                    missingSamples, timeStamp);
        std::fflush(stdout);
        // (1) is for coder so it knows it is a scalar
        missingSamples = b_X.ps_pos->fstart;
        timeStamp = b_X.ps_pos->fend;
        std::printf("ps_pos.fstart and ps_pos.fend after PROCESS step : \t %f "
                    "\t to \t %f.\n",
                    missingSamples, timeStamp);
        std::fflush(stdout);
        // (1) is for coder so it knows it is a scalar
        timeDiff = coder::toc() - processingStartToc;
        std::printf("TOTAL PULSE PROCESSING TIME: %f seconds \n", timeDiff);
        std::fflush(stdout);
        //                         %% PREP FOR NEXT LOOP
        // Latch/Release the frequency lock and setup the
        // suggested mode
        suggestedMode = b_X.ps_pos->mode;
        coder::internal::d_horzcatStructList(b_X.ps_pos->pl, pulsesToSkip);
        coder::all(pulsesToSkip, r2);
        if (coder::internal::ifWhileCond(r2)) {
          // Check if all were confirmed
          fLock = true;
        } else {
          fLock = false;
        }
        // Decide when/how the priori is updated for the next
        // segment's processing.
        if (coder::internal::ifWhileCond(r2)) {
          // Now checking for confirmation during search mode as well&
          // (strcmp(mode,'C') || strcmp(mode,'T'))
          ps_pre_struc_pl.set_size(1, b_X.ps_pos->pl.size(1));
          loop_ub = b_X.ps_pos->pl.size(0) * b_X.ps_pos->pl.size(1) - 1;
          for (i = 0; i <= loop_ub; i++) {
            ps_pre_struc_pl[i] = b_X.ps_pos->pl[i];
          }
          b_X.ps_pos->updateposteriori(b_X.ps_pre, ps_pre_struc_pl);
          if (trackedCount > 5.0) {
            trackedCount = 0.0;
            ps_pre_struc_pl.set_size(1, b_X.ps_pos->pl.size(1));
            loop_ub = b_X.ps_pos->pl.size(0) * b_X.ps_pos->pl.size(1) - 1;
            for (i = 0; i <= loop_ub; i++) {
              ps_pre_struc_pl[i] = b_X.ps_pos->pl[i];
            }
            b_X.ps_pos->b_updateposteriori(b_X.ps_pre, ps_pre_struc_pl);
          }
        }
        missingSamples = b_X.ps_pre->fstart;
        timeStamp = b_X.ps_pre->fend;
        std::printf("ps_pre.fstart and ps_pre.fend after PRIORI UPDATE step : "
                    "\t %f \t to \t %f.\n",
                    missingSamples, timeStamp);
        std::fflush(stdout);
        // (1) is for coder so it knows it is a scalar
        missingSamples = b_X.ps_pos->fstart;
        timeStamp = b_X.ps_pos->fend;
        std::printf("ps_pos.fstart and ps_pos.fend after PRIORI UPDATE step : "
                    "\t %f \t to \t %f.\n",
                    missingSamples, timeStamp);
        std::fflush(stdout);
        // (1) is for coder so it knows it is a scalar
        // Check lagging processing
        if ((segmentsProcessed != 0.0) && (Config.contents.K > 1.0) &&
            (timeDiff > 0.9 * sampsForKPulses.contents / Config.contents.Fs)) {
          // Config.K = Config.K - 1;
          d2 = std::round(Config.contents.K - 1.0);
          if (d2 < 4.294967296E+9) {
            timeStampSec = static_cast<unsigned int>(d2);
          } else {
            timeStampSec = MAX_uint32_T;
          }
          std::printf("WARNING!!! PROCESSING TIME TOOK LONGER THAN WAVEFORM "
                      "LENGTH. STREAMING NOT POSSIBLE. TRY REDUCING NUMBER OF "
                      "PULSES CONSIDERED BY"
                      " 1 TO K = %u \n",
                      timeStampSec);
          std::fflush(stdout);
          std::printf("Resetting all internal data buffers and udp buffers to "
                      "clear potential stale data. \n");
          std::fflush(stdout);
          resetBuffersFlag = true;
          staleDataFlag = true;
          suggestedMode = 'S';
        }
        segmentsProcessed++;
        // tic
        missingSamples = coder::toc();
        // Prepare priori for next segment
        std::printf("Updating priori...\n");
        std::fflush(stdout);
        ps_pre_struc_t_p = b_X.ps_pos->t_p;
        ps_pre_struc_t_ip = b_X.ps_pos->t_ip;
        ps_pre_struc_t_ipu = b_X.ps_pos->t_ipu;
        ps_pre_struc_t_ipj = b_X.ps_pos->t_ipj;
        ps_pre_struc_fp = b_X.ps_pos->fp;
        ps_pre_struc_fstart = b_X.ps_pos->fstart;
        ps_pre_struc_fend = b_X.ps_pos->fend;
        ps_pre_struc_tmplt[0] = b_X.ps_pos->tmplt[0];
        ps_pre_struc_tmplt[1] = b_X.ps_pos->tmplt[1];
        mode = b_X.ps_pos->mode;
        i = b_X.ps_pos->pl.size(1);
        ps_pre_struc_pl.set_size(1, i);
        loop_ub = b_X.ps_pos->pl.size(1);
        for (i1 = 0; i1 < loop_ub; i1++) {
          ps_pre_struc_pl[i1] = b_X.ps_pos->pl[i1];
        }
        ps_pre_struc_clst.set_size(b_X.ps_pos->clst.size(0),
                                   b_X.ps_pos->clst.size(1));
        loop_ub = b_X.ps_pos->clst.size(0) * b_X.ps_pos->clst.size(1);
        for (i1 = 0; i1 < loop_ub; i1++) {
          ps_pre_struc_clst[i1] = b_X.ps_pos->clst[i1];
        }
        ps_pre_struc_cmsk.set_size(b_X.ps_pos->cmsk.size(0),
                                   b_X.ps_pos->cmsk.size(1));
        loop_ub = b_X.ps_pos->cmsk.size(0) * b_X.ps_pos->cmsk.size(1);
        for (i1 = 0; i1 < loop_ub; i1++) {
          ps_pre_struc_cmsk[i1] = b_X.ps_pos->cmsk[i1];
        }
        ps_pre_struc_cpki.set_size(b_X.ps_pos->cpki.size(0),
                                   b_X.ps_pos->cpki.size(1));
        loop_ub = b_X.ps_pos->cpki.size(0) * b_X.ps_pos->cpki.size(1);
        for (i1 = 0; i1 < loop_ub; i1++) {
          ps_pre_struc_cpki[i1] = b_X.ps_pos->cpki[i1];
        }
        updatebufferreadvariables(Config, stftOverlapFraction, overlapSamples,
                                  sampsForKPulses, b_X.ps_pos);
        missingSamples = coder::toc() - missingSamples;
        std::printf("complete. Elapsed time: %f seconds \n", missingSamples);
        std::fflush(stdout);
        Xhold = waveformcopy(b_X, lobj_11, lobj_12[0], lobj_13);
        nPulseList_tmp = b_X.ps_pos->pl.size(1);
        pulsesToSkip.set_size(1, nPulseList_tmp);
        for (i1 = 0; i1 < nPulseList_tmp; i1++) {
          pulsesToSkip[i1] = false;
        }
        // Report pulses and check for repeat detections
        i1 = b_X.ps_pos->cpki.size(0);
        j = b_X.ps_pos->cpki.size(1);
        b_x.set_size(i1, j);
        loop_ub = b_X.ps_pos->cpki.size(0) * b_X.ps_pos->cpki.size(1);
        for (pulseCount = 0; pulseCount < loop_ub; pulseCount++) {
          b_x[pulseCount] = b_X.ps_pos->cpki[pulseCount];
        }
        r3.set_size(i1, j);
        b_currDir = b_x.size(0) * b_x.size(1);
        for (i1 = 0; i1 < b_currDir; i1++) {
          r3[i1] = !std::isnan(b_x[i1]);
        }
        if (coder::internal::b_ifWhileCond(r3)) {
          for (j = 0; j < nPulseList_tmp; j++) {
            i1 = b_X.ps_pos->pl.size(1);
            if (j + 1 > i1) {
              rtDynamicBoundsError(j + 1, 1, i1, gb_emlrtBCI);
            }
            missingSamples = b_X.ps_pos->pl[j].t_0;
            if (j + 1 > i) {
              rtDynamicBoundsError(j + 1, 1, i, hb_emlrtBCI);
            }
            std::printf("Pulse at %f Hz detected. SNR: %f \n \t Confirmation "
                        "status: %u \n\t Interpulse time    : %f \n",
                        Config.contents.channelCenterFreqMHz +
                            ps_pre_struc_pl[j].fp * 1.0E-6,
                        ps_pre_struc_pl[j].SNR,
                        static_cast<unsigned int>(ps_pre_struc_pl[j].con_dec),
                        missingSamples - previousPulseTime);
            std::fflush(stdout);
            if (missingSamples - previousPulseTime < 0.1 * b_X.ps_pre->t_ip) {
              // Overlap occasionally will redetect the same pulse
              std::printf("(\t ^---This likely a repeat of a previously "
                          "detected pulse. Will not be transmitted. \n");
              std::fflush(stdout);
              if (j + 1 > nPulseList_tmp) {
                rtDynamicBoundsError(j + 1, 1, nPulseList_tmp, ib_emlrtBCI);
              }
              pulsesToSkip[j] = true;
            } else {
              previousPulseTime = missingSamples;
            }
          }
        } else {
          std::printf("No pulses detected \n");
          std::fflush(stdout);
        }
        pulseCount = 0;
        i = b_X.ps_pos->cpki.size(0);
        i1 = b_X.ps_pos->cpki.size(1);
        b_x.set_size(i, i1);
        loop_ub = b_X.ps_pos->cpki.size(0) * b_X.ps_pos->cpki.size(1);
        for (j = 0; j < loop_ub; j++) {
          b_x[j] = b_X.ps_pos->cpki[j];
        }
        r3.set_size(i, i1);
        b_currDir = b_x.size(0) * b_x.size(1);
        for (i = 0; i < b_currDir; i++) {
          r3[i] = !std::isnan(b_x[i]);
        }
        if (coder::internal::b_ifWhileCond(r3)) {
          std::printf("Transmitting pulse messages.  ");
          std::fflush(stdout);
          if (nPulseList_tmp - 1 >= 0) {
            if (d < 4.294967296E+9) {
              if (d >= 0.0) {
                u1 = static_cast<unsigned int>(d);
              } else {
                u1 = 0U;
              }
            } else if (d >= 4.294967296E+9) {
              u1 = MAX_uint32_T;
            } else {
              u1 = 0U;
            }
            if (groupSeqCounter < 65536.0) {
              u2 = static_cast<unsigned short>(groupSeqCounter);
            } else {
              u2 = MAX_uint16_T;
            }
          }
          for (j = 0; j < nPulseList_tmp; j++) {
            double a;
            unsigned short u3;
            b_currDir = b_X.ps_pos->pl.size(1);
            c_X = b_X.ps_pos->pl.reshape(b_currDir);
            coder::internal::c_horzcatStructList(c_X, b_varargin_1);
            // Average SNR in dB
            b_varargin_1.set_size(1, b_varargin_1.size(1));
            loop_ub = b_varargin_1.size(1) - 1;
            for (i = 0; i <= loop_ub; i++) {
              missingSamples = b_varargin_1[i] / 10.0;
              b_varargin_1[i] = rt_powd_snf(10.0, missingSamples);
            }
            b_currDir = b_varargin_1.size(1);
            d_varargin_1 = b_varargin_1.reshape(b_currDir);
            d2 = coder::blockedSummation(d_varargin_1, b_varargin_1.size(1)) /
                 static_cast<double>(b_varargin_1.size(1));
            coder::b_log10(d2);
            missingSamples = 10.0 * d2;
            // 10log10 can produce complex results and group_snr required a real
            // value. Otherwise coder will generate type errors
            // 10*log10(mean(10.^([X.ps_pos.clst(X.ps_pos.cpki(j),:).SNR]/10)));%Average
            // SNR in dB
            //  Publish pulses to UDP
            i = b_X.ps_pos->pl.size(1);
            if (j + 1 > i) {
              rtDynamicBoundsError(j + 1, 1, i, jb_emlrtBCI);
            }
            detectorPulse = b_X.ps_pos->pl[j];
            timeDiff = b_X.stft->dt;
            timeStamp = b_X.stft->T;
            a = 1.0 + coder::mpower(10.0, detectorPulse.SNR / 10.0);
            // See Notebook Entry 2023-07-07 for derivation
            if (j + 1 > nPulseList_tmp) {
              rtDynamicBoundsError(j + 1, 1, nPulseList_tmp, kb_emlrtBCI);
            }
            if (!pulsesToSkip[j]) {
              //  UDP Send
              if (d < 4.294967296E+9) {
                if (d >= 0.0) {
                  timeStampSec = static_cast<unsigned int>(d);
                } else {
                  timeStampSec = 0U;
                }
              } else if (d >= 4.294967296E+9) {
                timeStampSec = MAX_uint32_T;
              } else {
                timeStampSec = 0U;
              }
              doublesBuffer[0] = timeStampSec;
              d2 = std::round(Config.contents.channelCenterFreqMHz * 1.0E+6 +
                              detectorPulse.fp);
              if (d2 < 4.294967296E+9) {
                if (d2 >= 0.0) {
                  timeStampSec = static_cast<unsigned int>(d2);
                } else {
                  timeStampSec = 0U;
                }
              } else if (d2 >= 4.294967296E+9) {
                timeStampSec = MAX_uint32_T;
              } else {
                timeStampSec = 0U;
              }
              doublesBuffer[1] = timeStampSec;
              doublesBuffer[2] = detectorPulse.t_0;
              doublesBuffer[3] = detectorPulse.t_next[0];
              doublesBuffer[4] = detectorPulse.SNR;
              doublesBuffer[5] = detectorPulse.yw;
              if (groupSeqCounter < 65536.0) {
                u3 = static_cast<unsigned short>(groupSeqCounter);
              } else {
                u3 = MAX_uint16_T;
              }
              doublesBuffer[6] = u3;
              if (static_cast<unsigned int>(j) + 1U < 65536U) {
                u3 = static_cast<unsigned short>(static_cast<double>(j) + 1.0);
              } else {
                u3 = MAX_uint16_T;
              }
              doublesBuffer[7] = u3;
              doublesBuffer[8] = missingSamples;
              doublesBuffer[9] = detectorPulse.det_dec;
              doublesBuffer[10] = detectorPulse.con_dec;
              doublesBuffer[11] = detectorPulse.yw * (timeDiff * timeDiff) /
                                  timeStamp * (1.0 / a);
              udpSenderSendDoubles(pulseInfoStruct.udpSender, &doublesBuffer[0],
                                   12U);
              //  ROS send
              std::printf("(Skipping ROS2 Pulse send)");
              std::fflush(stdout);
              pulseCount++;
            }
            std::printf("EXPECTED GCS ENTRY:\n");
            std::fflush(stdout);
            // PRINTPULSEINFOSTRUC Prints the pulse struct to the terminal
            //
            // INPUTS:
            //    pulseInfoStruct A pulse structure generated by
            //    makepulsestruc.m
            //
            // OUTPUTS:
            //    none other than prints to terminal
            //
            // --------------------------------------------------------------------------
            // uint32(Config.ID);
            //  uint32((Config.channelCenterFreqMHz * 1e6) + detectorPulse.fp);
            //  detectorPulse.t_0;
            // detectorPulse.t_next(1);
            //  detectorPulse.SNR;
            // real(detectorPulse.yw);
            // groupSeqCounter;
            // uint16(j);
            // groupSNR;
            // real(detectorPulse.yw ) * dt^2 / T * (1 +
            // 10^(detectorPulse.SNR/10))^(-1); %See Notebook Entry 2023-07-07
            // for derivation
            //  uint8(detectorPulse.det_dec);
            // uint8(detectorPulse.con_dec);
            d2 = std::round(Config.contents.channelCenterFreqMHz * 1.0E+6 +
                            detectorPulse.fp);
            if (d2 < 4.294967296E+9) {
              if (d2 >= 0.0) {
                timeStampSec = static_cast<unsigned int>(d2);
              } else {
                timeStampSec = 0U;
              }
            } else if (d2 >= 4.294967296E+9) {
              timeStampSec = MAX_uint32_T;
            } else {
              timeStampSec = 0U;
            }
            if (static_cast<unsigned int>(j) + 1U < 65536U) {
              u3 = static_cast<unsigned short>(static_cast<double>(j) + 1.0);
            } else {
              u3 = MAX_uint16_T;
            }
            std::printf("%u, %u, %.3f, %.3f, %g, %g, %u, %u, %g, %g, %u, %u\n",
                        u1, timeStampSec, detectorPulse.t_0,
                        detectorPulse.t_next[0], detectorPulse.SNR,
                        detectorPulse.yw, u2, u3, missingSamples,
                        detectorPulse.yw * (timeDiff * timeDiff) / timeStamp *
                            (1.0 / a),
                        static_cast<unsigned char>(detectorPulse.det_dec),
                        static_cast<unsigned char>(detectorPulse.con_dec));
            std::fflush(stdout);
          }
          groupSeqCounter++;
          std::printf("complete. Transmitted %u pulse(s).\n",
                      static_cast<unsigned int>(pulseCount));
          std::fflush(stdout);
        } else {
          std::printf("\n");
          std::fflush(stdout);
        }
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
        if (d1 < 2.147483648E+9) {
          if (d1 >= -2.147483648E+9) {
            i1 = static_cast<int>(d1);
          } else {
            i1 = MIN_int32_T;
          }
        } else if (d1 >= 2.147483648E+9) {
          i1 = MAX_int32_T;
        } else {
          i1 = 0;
        }
        coder::c_sprintf(i, i1, currDir);
        // waveformRecordPath =fullfile(Config.logPath,spectroFileName);%Use
        // this after upgrade to R2023b that supports full file
        loop_ub = (Config.contents.logPath.Value.size(1) + currDir.size(1)) + 1;
        waveformRecordPath.set_size(1, loop_ub);
        for (i = 0; i < loop_ub_tmp; i++) {
          waveformRecordPath[i] = Config.contents.logPath.Value[i];
        }
        waveformRecordPath[loop_ub_tmp] = '/';
        b_currDir = currDir.size(1);
        for (i = 0; i < b_currDir; i++) {
          waveformRecordPath[(i + Config.contents.logPath.Value.size(1)) + 1] =
              currDir[i];
        }
        varargin_1.set_size(1, waveformRecordPath.size(1) + 1);
        for (i = 0; i < loop_ub; i++) {
          varargin_1[i] = waveformRecordPath[i];
        }
        varargin_1[loop_ub] = '\x00';
        std::printf("Writing waveform record csv file: %s\n", &varargin_1[0]);
        std::fflush(stdout);
        wfmcsvwrite(b_X, Config.contents.channelCenterFreqMHz,
                    waveformRecordPath);
        std::printf("...complete.\n");
        std::fflush(stdout);
      }
      b_this.init();
      missingSamples =
          std::round(b_this.data.re / 1000.0 * 1.0E+6) / 1.0E+6 - startTime;
      timeStamp = coder::toc();
      std::printf("tocElapsed - clockElapsed = %0.6f  **************** \n",
                  timeStamp - missingSamples);
      std::fflush(stdout);
      timeStamp = coder::toc() - processingStartToc;
      std::printf("TOTAL SEGMENT PROCESSING TIME: %f seconds \n", timeStamp);
      std::fflush(stdout);
    }
  }
}

//
// File trailer for uavrt_detection.cpp
//
// [EOF]
//
