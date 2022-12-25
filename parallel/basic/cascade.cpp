namespace cascade
{

    float sum_raw(const float data[], const int len) // data是原始数据，len为长度。结果通过函数返回
    {
        float sum_res = 0;
        for (int i = 0; i < len; i++)
        {
            sum_res += data[i];
        }
        return sum_res;
    }
    float max_raw(const float data[], const int len) // data是原始数据，len为长度。结果通过函数返回
    {
        float max_temp = data[0];
        for (int i = 0; i < len; i++)
        {
            if (data[i] > max_temp)
                max_temp = data[i];
        }
        return max_temp;
    }

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

    void merge_sort(int *array, int left, int right)
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