#ifndef FUZZY_H
#define FUZZY_H

/************************************************
Includes
************************************************/
#define FIS_TYPE float
#define FIS_RESOLUSION 101
#define FIS_MIN -3.4028235E+38
#define FIS_MAX 3.4028235E+38
typedef FIS_TYPE(*_FIS_MF)(FIS_TYPE, FIS_TYPE*);
typedef FIS_TYPE(*_FIS_ARR_OP)(FIS_TYPE, FIS_TYPE);
typedef FIS_TYPE(*_FIS_ARR)(FIS_TYPE*, int, _FIS_ARR_OP);
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

#define fis_gcI 2
#define fis_gcO 1
#define fis_gcR 25

FIS_TYPE g_fisInput[fis_gcI];
FIS_TYPE g_fisOutput[fis_gcO];

/************************************************
Function prototypes
************************************************/
FIS_TYPE fis_trapmf(FIS_TYPE x, FIS_TYPE* p);
FIS_TYPE fis_trimf(FIS_TYPE x, FIS_TYPE* p);
FIS_TYPE fis_min(FIS_TYPE a, FIS_TYPE b);
FIS_TYPE fis_max(FIS_TYPE a, FIS_TYPE b);
FIS_TYPE fis_array_operation(FIS_TYPE *array, int size, _FIS_ARR_OP pfnOp);
FIS_TYPE fis_MF_out(FIS_TYPE** fuzzyRuleSet, FIS_TYPE x, int o);
FIS_TYPE fis_defuzz_centroid(FIS_TYPE** fuzzyRuleSet, int o);
void fis_evaluate();

#endif
