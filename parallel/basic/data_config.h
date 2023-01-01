#pragma once
#define MAX_THREADS 128
#define DATANUM 12800000
#define SUBDATANUM (DATANUM / MAX_THREADS)

namespace cascade
{
    void sum(float *array, int left, int right, float *pres);
    void mymax(float *array, int left, int right, float *pres);
    void merge_sort(float *array, int left, int right);
}

namespace parallel
{
    void sum(float *array, int left, int right, float *pres, int level, int idx_thd);
    void mymax(float *array, int left, int right, float *pres, int level, int idx_thd);
    void merge_sort(float *array, int left, int right, int level, int idx_thd);
}
