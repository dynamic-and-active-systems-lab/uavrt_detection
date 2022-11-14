/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 * File: str2matrix.c
 *
 * MATLAB Coder version            : 5.5
 * C/C++ source code generated on  : 26-Sep-2022 15:37:10
 */

/* Include Files */
#include "str2matrix.h"
#include "find.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "str2double.h"
#include "uavrt_detection_data.h"
#include "uavrt_detection_emxutil.h"
#include "uavrt_detection_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"

/* Function Definitions */
/*
 * STR2MATRIX Converts a string containing a matrix in Matlab notation to a
 * numeric array. Arrays must be no greater than two dimensions. Hard
 * brackets should enclose the array, with semicolons separating rows.
 * Columns can be separated by white space or commas. All rows must have the
 * same number of columns. Note that str2num would produce similar results to
 * this function, but is not supported for code generation.
 *
 * INPUTS:
 *    inputStr    A string containing a matrix. Ex: '[2 3; 5, 6 ;7 ,8 ]'
 * OUTPUS:
 *    outMat      A numeric array of the input matrix.
 *
 *
 * Author:    Michael W. Shafer
 * Date:      2022-02-15
 * --------------------------------------------------------------------------
 *
 * Arguments    : emxArray_char_T *inputStr
 *                emxArray_creal_T *outMat
 * Return Type  : void
 */
void str2matrix(emxArray_char_T *inputStr, emxArray_creal_T *outMat)
{
  emxArray_boolean_T *b_inputStr;
  emxArray_boolean_T *r4;
  emxArray_char_T *c_inputStr;
  emxArray_creal_T *tempRow;
  emxArray_int32_T *commaLocs;
  emxArray_int32_T *r;
  emxArray_int32_T *r2;
  emxArray_int32_T *r6;
  emxArray_real_T *colDividerLocs;
  emxArray_real_T *rowDividerLocs;
  creal_T *outMat_data;
  creal_T *tempRow_data;
  double b_rowDividerLocs;
  double *colDividerLocs_data;
  double *rowDividerLocs_data;
  int b_i;
  int b_j1;
  int c_i;
  unsigned int i;
  int i1;
  int i2;
  int j2;
  int nd2;
  int trueCount;
  int *commaLocs_data;
  int *r1;
  int *r3;
  char xtmp;
  char *c_inputStr_data;
  char *inputStr_data;
  bool done;
  bool *b_inputStr_data;
  bool *r5;
  inputStr_data = inputStr->data;
  /* Strip redundant white space */
  done = false;
  i = 1U;
  while (!done) {
    done = (i + 1U == (unsigned int)inputStr->size[1]);
    if (bv[(unsigned char)inputStr_data[(int)i - 1] & 127] &&
        bv[(unsigned char)inputStr_data[(int)i] & 127]) {
      /* inputStr(i+1) = ''; */
      /* inputStr = inputStr(1:numel(inputStr) ~= i+1); */
      nd2 = (int)i + 1;
      j2 = inputStr->size[1] - 1;
      for (trueCount = nd2; trueCount <= j2; trueCount++) {
        inputStr_data[trueCount - 1] = inputStr_data[trueCount];
      }
      b_i = inputStr->size[0] * inputStr->size[1];
      if (inputStr->size[1] - 1 < 1) {
        inputStr->size[1] = 0;
      } else {
        inputStr->size[1]--;
      }
      emxEnsureCapacity_char_T(inputStr, b_i);
      inputStr_data = inputStr->data;
      i = (unsigned int)((int)i - 1);
    }
    i++;
  }
  /* Strip out white space after [ ; and , characters */
  done = false;
  i = 1U;
  while (!done) {
    done = (i + 1U == (unsigned int)inputStr->size[1]);
    xtmp = inputStr_data[(int)i - 1];
    if ((xtmp == '[') && bv[(unsigned char)inputStr_data[(int)i] & 127]) {
      /* inputStr(i+1) = ''; */
      /* inputStr = inputStr(1:numel(inputStr) ~= i+1); */
      nd2 = (int)i + 1;
      j2 = inputStr->size[1] - 1;
      for (trueCount = nd2; trueCount <= j2; trueCount++) {
        inputStr_data[trueCount - 1] = inputStr_data[trueCount];
      }
      b_i = inputStr->size[0] * inputStr->size[1];
      if (inputStr->size[1] - 1 < 1) {
        inputStr->size[1] = 0;
      } else {
        inputStr->size[1]--;
      }
      emxEnsureCapacity_char_T(inputStr, b_i);
      inputStr_data = inputStr->data;
      i = (unsigned int)((int)i - 1);
    } else if ((xtmp == ',') &&
               bv[(unsigned char)inputStr_data[(int)i] & 127]) {
      /* inputStr(i+1) = ''; */
      /* inputStr = inputStr(1:numel(inputStr) ~= i+1); */
      nd2 = (int)i + 1;
      j2 = inputStr->size[1] - 1;
      for (trueCount = nd2; trueCount <= j2; trueCount++) {
        inputStr_data[trueCount - 1] = inputStr_data[trueCount];
      }
      b_i = inputStr->size[0] * inputStr->size[1];
      if (inputStr->size[1] - 1 < 1) {
        inputStr->size[1] = 0;
      } else {
        inputStr->size[1]--;
      }
      emxEnsureCapacity_char_T(inputStr, b_i);
      inputStr_data = inputStr->data;
      i = (unsigned int)((int)i - 1);
    } else if ((xtmp == ';') &&
               bv[(unsigned char)inputStr_data[(int)i] & 127]) {
      /* inputStr(i+1) = ''; */
      /* inputStr = inputStr(1:numel(inputStr) ~= i+1); */
      nd2 = (int)i + 1;
      j2 = inputStr->size[1] - 1;
      for (trueCount = nd2; trueCount <= j2; trueCount++) {
        inputStr_data[trueCount - 1] = inputStr_data[trueCount];
      }
      b_i = inputStr->size[0] * inputStr->size[1];
      if (inputStr->size[1] - 1 < 1) {
        inputStr->size[1] = 0;
      } else {
        inputStr->size[1]--;
      }
      emxEnsureCapacity_char_T(inputStr, b_i);
      inputStr_data = inputStr->data;
      i = (unsigned int)((int)i - 1);
    }
    i++;
  }
  /* Strip out white space before [ ; and , characters */
  nd2 = inputStr->size[1] >> 1;
  for (b_j1 = 0; b_j1 < nd2; b_j1++) {
    j2 = (inputStr->size[1] - b_j1) - 1;
    xtmp = inputStr_data[b_j1];
    inputStr_data[b_j1] = inputStr_data[j2];
    inputStr_data[j2] = xtmp;
  }
  done = false;
  i = 1U;
  while (!done) {
    done = (i + 1U == (unsigned int)inputStr->size[1]);
    xtmp = inputStr_data[(int)i - 1];
    if ((xtmp == '[') && bv[(unsigned char)inputStr_data[(int)i] & 127]) {
      /* inputStr(i+1) = ''; */
      /* inputStr = inputStr(1:numel(inputStr) ~= i+1); */
      nd2 = (int)i + 1;
      j2 = inputStr->size[1] - 1;
      for (trueCount = nd2; trueCount <= j2; trueCount++) {
        inputStr_data[trueCount - 1] = inputStr_data[trueCount];
      }
      b_i = inputStr->size[0] * inputStr->size[1];
      if (inputStr->size[1] - 1 < 1) {
        inputStr->size[1] = 0;
      } else {
        inputStr->size[1]--;
      }
      emxEnsureCapacity_char_T(inputStr, b_i);
      inputStr_data = inputStr->data;
      i = (unsigned int)((int)i - 1);
    } else if ((xtmp == ',') &&
               bv[(unsigned char)inputStr_data[(int)i] & 127]) {
      /* inputStr(i+1) = ''; */
      /* inputStr = inputStr(1:numel(inputStr) ~= i+1); */
      nd2 = (int)i + 1;
      j2 = inputStr->size[1] - 1;
      for (trueCount = nd2; trueCount <= j2; trueCount++) {
        inputStr_data[trueCount - 1] = inputStr_data[trueCount];
      }
      b_i = inputStr->size[0] * inputStr->size[1];
      if (inputStr->size[1] - 1 < 1) {
        inputStr->size[1] = 0;
      } else {
        inputStr->size[1]--;
      }
      emxEnsureCapacity_char_T(inputStr, b_i);
      inputStr_data = inputStr->data;
      i = (unsigned int)((int)i - 1);
    } else if ((xtmp == ';') &&
               bv[(unsigned char)inputStr_data[(int)i] & 127]) {
      /* inputStr(i+1) = ''; */
      /* inputStr = inputStr(1:numel(inputStr) ~= i+1); */
      nd2 = (int)i + 1;
      j2 = inputStr->size[1] - 1;
      for (trueCount = nd2; trueCount <= j2; trueCount++) {
        inputStr_data[trueCount - 1] = inputStr_data[trueCount];
      }
      b_i = inputStr->size[0] * inputStr->size[1];
      if (inputStr->size[1] - 1 < 1) {
        inputStr->size[1] = 0;
      } else {
        inputStr->size[1]--;
      }
      emxEnsureCapacity_char_T(inputStr, b_i);
      inputStr_data = inputStr->data;
      i = (unsigned int)((int)i - 1);
    }
    i++;
  }
  nd2 = inputStr->size[1] >> 1;
  for (b_j1 = 0; b_j1 < nd2; b_j1++) {
    j2 = (inputStr->size[1] - b_j1) - 1;
    xtmp = inputStr_data[b_j1];
    inputStr_data[b_j1] = inputStr_data[j2];
    inputStr_data[j2] = xtmp;
  }
  /* Replace space with commas for marking columns */
  j2 = inputStr->size[1];
  for (c_i = 0; c_i < j2; c_i++) {
    if (inputStr_data[c_i] == ' ') {
      inputStr_data[c_i] = ',';
    }
  }
  emxInit_boolean_T(&b_inputStr, 2);
  b_i = b_inputStr->size[0] * b_inputStr->size[1];
  b_inputStr->size[0] = 1;
  b_inputStr->size[1] = inputStr->size[1];
  emxEnsureCapacity_boolean_T(b_inputStr, b_i);
  b_inputStr_data = b_inputStr->data;
  b_j1 = inputStr->size[1];
  for (b_i = 0; b_i < b_j1; b_i++) {
    b_inputStr_data[b_i] = (inputStr_data[b_i] == '[');
  }
  emxInit_int32_T(&commaLocs, 2);
  b_eml_find(b_inputStr, commaLocs);
  commaLocs_data = commaLocs->data;
  b_i = b_inputStr->size[0] * b_inputStr->size[1];
  b_inputStr->size[0] = 1;
  b_inputStr->size[1] = inputStr->size[1];
  emxEnsureCapacity_boolean_T(b_inputStr, b_i);
  b_inputStr_data = b_inputStr->data;
  b_j1 = inputStr->size[1];
  for (b_i = 0; b_i < b_j1; b_i++) {
    b_inputStr_data[b_i] = (inputStr_data[b_i] == ';');
  }
  emxInit_int32_T(&r, 2);
  b_eml_find(b_inputStr, r);
  r1 = r->data;
  b_i = b_inputStr->size[0] * b_inputStr->size[1];
  b_inputStr->size[0] = 1;
  b_inputStr->size[1] = inputStr->size[1];
  emxEnsureCapacity_boolean_T(b_inputStr, b_i);
  b_inputStr_data = b_inputStr->data;
  b_j1 = inputStr->size[1];
  for (b_i = 0; b_i < b_j1; b_i++) {
    b_inputStr_data[b_i] = (inputStr_data[b_i] == ']');
  }
  emxInit_int32_T(&r2, 2);
  b_eml_find(b_inputStr, r2);
  r3 = r2->data;
  emxInit_real_T(&rowDividerLocs, 2);
  b_i = rowDividerLocs->size[0] * rowDividerLocs->size[1];
  rowDividerLocs->size[0] = 1;
  rowDividerLocs->size[1] = (commaLocs->size[1] + r->size[1]) + r2->size[1];
  emxEnsureCapacity_real_T(rowDividerLocs, b_i);
  rowDividerLocs_data = rowDividerLocs->data;
  b_j1 = commaLocs->size[1];
  for (b_i = 0; b_i < b_j1; b_i++) {
    rowDividerLocs_data[b_i] = commaLocs_data[b_i];
  }
  b_j1 = r->size[1];
  for (b_i = 0; b_i < b_j1; b_i++) {
    rowDividerLocs_data[b_i + commaLocs->size[1]] = r1[b_i];
  }
  b_j1 = r2->size[1];
  for (b_i = 0; b_i < b_j1; b_i++) {
    rowDividerLocs_data[(b_i + commaLocs->size[1]) + r->size[1]] = r3[b_i];
  }
  emxFree_int32_T(&r2);
  emxFree_int32_T(&r);
  sort(rowDividerLocs);
  rowDividerLocs_data = rowDividerLocs->data;
  b_i = b_inputStr->size[0] * b_inputStr->size[1];
  b_inputStr->size[0] = 1;
  b_inputStr->size[1] = inputStr->size[1];
  emxEnsureCapacity_boolean_T(b_inputStr, b_i);
  b_inputStr_data = b_inputStr->data;
  b_j1 = inputStr->size[1];
  for (b_i = 0; b_i < b_j1; b_i++) {
    b_inputStr_data[b_i] = (inputStr_data[b_i] == ',');
  }
  b_eml_find(b_inputStr, commaLocs);
  commaLocs_data = commaLocs->data;
  /* Check for the number of columns in the first row to preallocate outMat */
  b_i = b_inputStr->size[0] * b_inputStr->size[1];
  b_inputStr->size[0] = 1;
  b_inputStr->size[1] = commaLocs->size[1];
  emxEnsureCapacity_boolean_T(b_inputStr, b_i);
  b_inputStr_data = b_inputStr->data;
  b_rowDividerLocs = rowDividerLocs_data[0];
  b_j1 = commaLocs->size[1];
  for (b_i = 0; b_i < b_j1; b_i++) {
    b_inputStr_data[b_i] = (commaLocs_data[b_i] > b_rowDividerLocs);
  }
  emxInit_boolean_T(&r4, 2);
  b_i = r4->size[0] * r4->size[1];
  r4->size[0] = 1;
  r4->size[1] = commaLocs->size[1];
  emxEnsureCapacity_boolean_T(r4, b_i);
  r5 = r4->data;
  b_rowDividerLocs = rowDividerLocs_data[1];
  b_j1 = commaLocs->size[1];
  for (b_i = 0; b_i < b_j1; b_i++) {
    r5[b_i] = (commaLocs_data[b_i] < b_rowDividerLocs);
  }
  j2 = b_inputStr->size[1];
  trueCount = 1;
  for (c_i = 0; c_i < j2; c_i++) {
    if (b_inputStr_data[c_i] && r5[c_i]) {
      trueCount++;
    }
  }
  b_i = outMat->size[0] * outMat->size[1];
  outMat->size[0] = rowDividerLocs->size[1] - 1;
  outMat->size[1] = trueCount;
  emxEnsureCapacity_creal_T(outMat, b_i);
  outMat_data = outMat->data;
  b_j1 = (rowDividerLocs->size[1] - 1) * trueCount;
  for (b_i = 0; b_i < b_j1; b_i++) {
    outMat_data[b_i].re = 0.0;
    outMat_data[b_i].im = 0.0;
  }
  b_i = rowDividerLocs->size[1];
  emxInit_real_T(&colDividerLocs, 2);
  emxInit_creal_T(&tempRow, 2);
  emxInit_int32_T(&r6, 2);
  emxInit_char_T(&c_inputStr);
  for (c_i = 0; c_i <= b_i - 2; c_i++) {
    double rowDividerLocs_tmp;
    i1 = b_inputStr->size[0] * b_inputStr->size[1];
    b_inputStr->size[0] = 1;
    b_inputStr->size[1] = commaLocs->size[1];
    emxEnsureCapacity_boolean_T(b_inputStr, i1);
    b_inputStr_data = b_inputStr->data;
    b_rowDividerLocs = rowDividerLocs_data[c_i];
    b_j1 = commaLocs->size[1];
    i1 = r4->size[0] * r4->size[1];
    r4->size[0] = 1;
    r4->size[1] = commaLocs->size[1];
    emxEnsureCapacity_boolean_T(r4, i1);
    r5 = r4->data;
    rowDividerLocs_tmp = rowDividerLocs_data[c_i + 1];
    for (i1 = 0; i1 < b_j1; i1++) {
      nd2 = commaLocs_data[i1];
      b_inputStr_data[i1] = (nd2 > b_rowDividerLocs);
      r5[i1] = (nd2 < rowDividerLocs_tmp);
    }
    j2 = b_inputStr->size[1];
    trueCount = 1;
    for (b_j1 = 0; b_j1 < j2; b_j1++) {
      if (b_inputStr_data[b_j1] && r5[b_j1]) {
        trueCount++;
      }
    }
    /* numelCols = numelCommasCurr+1; */
    j2 = b_inputStr->size[1] - 1;
    nd2 = 0;
    for (b_j1 = 0; b_j1 <= j2; b_j1++) {
      if (b_inputStr_data[b_j1] && r5[b_j1]) {
        nd2++;
      }
    }
    i1 = r6->size[0] * r6->size[1];
    r6->size[0] = 1;
    r6->size[1] = nd2;
    emxEnsureCapacity_int32_T(r6, i1);
    r1 = r6->data;
    nd2 = 0;
    for (b_j1 = 0; b_j1 <= j2; b_j1++) {
      if (b_inputStr_data[b_j1] && r5[b_j1]) {
        r1[nd2] = b_j1 + 1;
        nd2++;
      }
    }
    i1 = colDividerLocs->size[0] * colDividerLocs->size[1];
    colDividerLocs->size[0] = 1;
    b_j1 = r6->size[1];
    colDividerLocs->size[1] = r6->size[1] + 2;
    emxEnsureCapacity_real_T(colDividerLocs, i1);
    colDividerLocs_data = colDividerLocs->data;
    colDividerLocs_data[0] = rowDividerLocs_data[c_i];
    for (i1 = 0; i1 < b_j1; i1++) {
      colDividerLocs_data[i1 + 1] = commaLocs_data[r1[i1] - 1];
    }
    colDividerLocs_data[r6->size[1] + 1] = rowDividerLocs_tmp;
    i1 = tempRow->size[0] * tempRow->size[1];
    tempRow->size[0] = 1;
    tempRow->size[1] = trueCount;
    emxEnsureCapacity_creal_T(tempRow, i1);
    tempRow_data = tempRow->data;
    for (i1 = 0; i1 < trueCount; i1++) {
      tempRow_data[i1].re = 0.0;
      tempRow_data[i1].im = 0.0;
    }
    i1 = colDividerLocs->size[1];
    for (trueCount = 0; trueCount <= i1 - 2; trueCount++) {
      b_rowDividerLocs = colDividerLocs_data[trueCount];
      rowDividerLocs_tmp = colDividerLocs_data[trueCount + 1];
      if (b_rowDividerLocs + 1.0 > rowDividerLocs_tmp - 1.0) {
        nd2 = 0;
        i2 = 0;
      } else {
        nd2 = (int)(b_rowDividerLocs + 1.0) - 1;
        i2 = (int)(rowDividerLocs_tmp - 1.0);
      }
      j2 = c_inputStr->size[0] * c_inputStr->size[1];
      c_inputStr->size[0] = 1;
      b_j1 = i2 - nd2;
      c_inputStr->size[1] = b_j1;
      emxEnsureCapacity_char_T(c_inputStr, j2);
      c_inputStr_data = c_inputStr->data;
      for (i2 = 0; i2 < b_j1; i2++) {
        c_inputStr_data[i2] = inputStr_data[nd2 + i2];
      }
      tempRow_data[trueCount] = str2double(c_inputStr);
    }
    b_j1 = tempRow->size[1];
    for (i1 = 0; i1 < b_j1; i1++) {
      outMat_data[c_i + outMat->size[0] * i1] = tempRow_data[i1];
    }
  }
  emxFree_char_T(&c_inputStr);
  emxFree_boolean_T(&b_inputStr);
  emxFree_int32_T(&r6);
  emxFree_boolean_T(&r4);
  emxFree_creal_T(&tempRow);
  emxFree_real_T(&colDividerLocs);
  emxFree_int32_T(&commaLocs);
  emxFree_real_T(&rowDividerLocs);
}

/*
 * File trailer for str2matrix.c
 *
 * [EOF]
 */
