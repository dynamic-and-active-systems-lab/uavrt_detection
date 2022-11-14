/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: fileManager.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "fileManager.h"
#include "rt_nonfinite.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include <stdio.h>

/* Variable Definitions */
static FILE *eml_openfiles[20];

static bool eml_autoflush[20];

/* Function Declarations */
static signed char filedata(void);

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : signed char
 */
static signed char filedata(void)
{
  int k;
  signed char f;
  bool exitg1;
  f = 0;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 20)) {
    if (eml_openfiles[k] == NULL) {
      f = (signed char)(k + 1);
      exitg1 = true;
    } else {
      k++;
    }
  }
  return f;
}

/*
 * Arguments    : const emxArray_char_T *cfilename
 * Return Type  : signed char
 */
signed char b_cfopen(const emxArray_char_T *cfilename)
{
  emxArray_char_T *ccfilename;
  int i;
  const char *cfilename_data;
  signed char fileid;
  signed char j;
  char *ccfilename_data;
  cfilename_data = cfilename->data;
  fileid = -1;
  j = filedata();
  if (j >= 1) {
    FILE *filestar;
    int loop_ub;
    emxInit_char_T(&ccfilename);
    i = ccfilename->size[0] * ccfilename->size[1];
    ccfilename->size[0] = 1;
    ccfilename->size[1] = cfilename->size[1] + 1;
    emxEnsureCapacity_char_T(ccfilename, i);
    ccfilename_data = ccfilename->data;
    loop_ub = cfilename->size[1];
    for (i = 0; i < loop_ub; i++) {
      ccfilename_data[i] = cfilename_data[i];
    }
    ccfilename_data[cfilename->size[1]] = '\x00';
    filestar = fopen(&ccfilename_data[0], "wb");
    emxFree_char_T(&ccfilename);
    if (filestar != NULL) {
      eml_openfiles[j - 1] = filestar;
      eml_autoflush[j - 1] = true;
      i = j + 2;
      if (j + 2 > 127) {
        i = 127;
      }
      fileid = (signed char)i;
    }
  }
  return fileid;
}

/*
 * Arguments    : double fid
 * Return Type  : int
 */
int cfclose(double fid)
{
  FILE *filestar;
  int st;
  signed char b_fileid;
  signed char fileid;
  st = -1;
  fileid = (signed char)fid;
  if (((signed char)fid < 0) || (fid != (signed char)fid)) {
    fileid = -1;
  }
  b_fileid = fileid;
  if (fileid < 0) {
    b_fileid = -1;
  }
  if (b_fileid >= 3) {
    filestar = eml_openfiles[b_fileid - 3];
  } else if (b_fileid == 0) {
    filestar = stdin;
  } else if (b_fileid == 1) {
    filestar = stdout;
  } else if (b_fileid == 2) {
    filestar = stderr;
  } else {
    filestar = NULL;
  }
  if ((filestar != NULL) && (fileid >= 3)) {
    int cst;
    cst = fclose(filestar);
    if (cst == 0) {
      st = 0;
      eml_openfiles[fileid - 3] = NULL;
      eml_autoflush[fileid - 3] = true;
    }
  }
  return st;
}

/*
 * Arguments    : const char cfilename[25]
 * Return Type  : signed char
 */
signed char cfopen(const char cfilename[25])
{
  int i;
  signed char fileid;
  signed char j;
  fileid = -1;
  j = filedata();
  if (j >= 1) {
    FILE *filestar;
    char ccfilename[26];
    for (i = 0; i < 25; i++) {
      ccfilename[i] = cfilename[i];
    }
    ccfilename[25] = '\x00';
    filestar = fopen(&ccfilename[0], "rb");
    if (filestar != NULL) {
      eml_openfiles[j - 1] = filestar;
      eml_autoflush[j - 1] = true;
      i = j + 2;
      if (j + 2 > 127) {
        i = 127;
      }
      fileid = (signed char)i;
    }
  }
  return fileid;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void filedata_init(void)
{
  FILE *a;
  int i;
  a = NULL;
  for (i = 0; i < 20; i++) {
    eml_autoflush[i] = false;
    eml_openfiles[i] = a;
  }
}

/*
 * Arguments    : double fid
 *                FILE* *filestar
 *                bool *autoflush
 * Return Type  : void
 */
void getfilestar(double fid, FILE **filestar, bool *autoflush)
{
  signed char fileid;
  fileid = (signed char)fid;
  if (((signed char)fid < 0) || (fid != (signed char)fid)) {
    fileid = -1;
  }
  if (fileid >= 3) {
    *filestar = eml_openfiles[fileid - 3];
    *autoflush = eml_autoflush[fileid - 3];
  } else if (fileid == 0) {
    *filestar = stdin;
    *autoflush = true;
  } else if (fileid == 1) {
    *filestar = stdout;
    *autoflush = true;
  } else if (fileid == 2) {
    *filestar = stderr;
    *autoflush = true;
  } else {
    *filestar = NULL;
    *autoflush = true;
  }
}

/*
 * File trailer for fileManager.c
 *
 * [EOF]
 */
