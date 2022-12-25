#pragma once
#define MAX_THREADS 128
#define DATANUM 128000
#define SUBDATANUM (DATANUM / MAX_THREADS)

namespace cascade
{
    void merge_sort(int *array, int left, int right);
}

namespace parallel
{
    void merge_sort(int *array, int left, int right, int level, int idx_thd);
}
