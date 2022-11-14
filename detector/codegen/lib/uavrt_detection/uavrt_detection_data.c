/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: uavrt_detection_data.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "uavrt_detection_data.h"
#include "rt_nonfinite.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Variable Definitions */
unsigned int state[625];

dspcodegen_UDPReceiver udpRx;

bool udpRx_not_empty;

double freq;

bool freq_not_empty;

b_dspcodegen_UDPReceiver b_udpRx;

bool b_udpRx_not_empty;

omp_nest_lock_t uavrt_detection_nestLockGlobal;

const char cv[12] = {'u', 'p', 'd', 'a', 't', 'e',
                     'c', 'o', 'n', 'f', 'i', 'g'};

const char cv1[18] = {'f', 'r', 'e', 'q', 'S', 'e', 'a', 'r', 'c',
                      'h', 'H', 'a', 'r', 'd', 'L', 'o', 'c', 'k'};

const bool bv[128] = {
    false, false, false, false, false, false, false, false, false, true,  true,
    true,  true,  true,  false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, true,  true,  true,  true,  true,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false};

const char cv2[128] = {
    '\x00', '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\x07', '\x08',
    '\x09', '\x0a', '\x0b', '\x0c', '\x0d', '\x0e', '\x0f', '\x10', '\x11',
    '\x12', '\x13', '\x14', '\x15', '\x16', '\x17', '\x18', '\x19', '\x1a',
    '\x1b', '\x1c', '\x1d', '\x1e', '\x1f', ' ',    '!',    '\"',   '#',
    '$',    '%',    '&',    '\'',   '(',    ')',    '*',    '+',    ',',
    '-',    '.',    '/',    '0',    '1',    '2',    '3',    '4',    '5',
    '6',    '7',    '8',    '9',    ':',    ';',    '<',    '=',    '>',
    '?',    '@',    'a',    'b',    'c',    'd',    'e',    'f',    'g',
    'h',    'i',    'j',    'k',    'l',    'm',    'n',    'o',    'p',
    'q',    'r',    's',    't',    'u',    'v',    'w',    'x',    'y',
    'z',    '[',    '\\',   ']',    '^',    '_',    '`',    'a',    'b',
    'c',    'd',    'e',    'f',    'g',    'h',    'i',    'j',    'k',
    'l',    'm',    'n',    'o',    'p',    'q',    'r',    's',    't',
    'u',    'v',    'w',    'x',    'y',    'z',    '{',    '|',    '}',
    '~',    '\x7f'};

const char cv3[18] = {'f', 'r', 'e', 'q', 'S', 'e', 'a', 'r', 'c',
                      'h', 'S', 'o', 'f', 't', 'L', 'o', 'c', 'k'};

bool isInitialized_uavrt_detection = false;

/*
 * File trailer for uavrt_detection_data.c
 *
 * [EOF]
 */
