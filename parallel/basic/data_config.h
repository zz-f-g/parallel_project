#pragma once
#define MAX_THREADS 128
#define DATANUM 128000000
#define SUBDATANUM (DATANUM / MAX_THREADS)
#define ADDR_SRV "192.168.173.76"
#define BUF_SIZE 1280
#define ANSWER_SEP 10

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
