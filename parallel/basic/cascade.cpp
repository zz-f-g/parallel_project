#include <cmath>
namespace cascade
{
    void sum(float *array, int left, int right, float *pres)
    {
        *pres = 0;
        for (int i = left; i <= right; i++)
        {
            *pres += log(sqrt(array[i]));
        }
    }

    void mymax(float *array, int left, int right, float *pres)
    {
        *pres = 0;
        for (int i = left; i <= right; i++)
        {
            if (*pres < array[i])
                *pres = array[i];
        }
    }

    void merge(float *array, int left, int mid, int right)
    {
        int i, j, k;
        int n1 = mid - left + 1;
        int n2 = right - mid;

        float *L = new float[n1];
        float *R = new float[n2];

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

    void merge_sort(float *array, int left, int right)
    {
        if (left < right)
        {
            int mid = left + (right - left) / 2;
            merge_sort(array, left, mid);
            merge_sort(array, mid + 1, right);

            merge(array, left, mid, right);
        }
    }
}
