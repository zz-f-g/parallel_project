#include <thread>
#include "data_config.h"

namespace parallel
{
    std::thread thrds[MAX_THREADS];

    void merge(int *array, int left, int mid, int right)
    {
        int i, j, k;
        int n1 = mid - left + 1;
        int n2 = right - mid;

        int *L = new int[n1];
        int *R = new int[n2];

        for (i = 0; i < n1; i++)
        {
            L[i] = array[left + i];
        }
        for (j = 0; j < n2; j++)
        {
            R[j] = array[mid + 1 + j];
        }

        i = 0;
        j = 0;
        k = left;
        while (i < n1 && j < n2)
        {
            if (L[i] <= R[j])
            {
                array[k] = L[i];
                i++;
            }
            else
            {
                array[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1)
        {
            array[k] = L[i];
            i++;
            k++;
        }

        while (j < n2)
        {
            array[k] = R[j];
            j++;
            k++;
        }
        delete[] L;
        delete[] R;
    }

    void merge_sort(int *array, int left, int right, int level, int idx_thd)
    {
        if (left < right)
        {
            int mid = left + (right - left) / 2;
            if ((1 << level) >= MAX_THREADS)
            {
                merge_sort(array, left, mid, level, idx_thd);
                merge_sort(array, mid + 1, right, level, idx_thd);
            }
            else
            {
                int child_idx = idx_thd + (1 << level);
                thrds[idx_thd + (1 << level)] = std::thread(
                    merge_sort,
                    array, left, mid, level + 1, idx_thd + (1 << level)
                );
                merge_sort(array, mid + 1, right, level + 1, idx_thd);
                thrds[idx_thd + (1 << level)].join();
            }
            merge(array, left, mid, right);
        }
    }
}