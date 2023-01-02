#pragma once
#define MAX_THREADS 128
#define DATANUM 128000000
#define HALF_NUM (DATANUM / 2)
#define SUBDATANUM (DATANUM / MAX_THREADS)
#define ADDR_SRV "172.25.100.31"
#define BUF_SIZE 1280
#define ANSWER_SEP 1
#define ITEM_TYPE float

namespace cascade
{
    void sum(ITEM_TYPE* array, int left, int right, ITEM_TYPE* pres);
    void mymax(ITEM_TYPE* array, int left, int right, ITEM_TYPE* pres);
    void merge_sort(ITEM_TYPE* array, int left, int right);
}

namespace parallel
{
    void sum(ITEM_TYPE* array, int left, int right, ITEM_TYPE* pres, int level, int idx_thd);
    void mymax(ITEM_TYPE* array, int left, int right, ITEM_TYPE* pres, int level, int idx_thd);
    void merge(ITEM_TYPE* array, int left, int mid, int right);
    void merge_sort(ITEM_TYPE* array, int left, int right, int level, int idx_thd);
}