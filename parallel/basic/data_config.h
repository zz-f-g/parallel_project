#pragma once
#define MAX_THREADS 128
#define DATANUM 128000000
#define SUBDATANUM (DATANUM / MAX_THREADS)

namespace cascade
{
    template <typename T>
    void merge_sort(T *array, int left, int right);
}

namespace parallel
{
    template <typename T>
    void merge_sort(T *array, int left, int right, int level, int idx_thd);
}
