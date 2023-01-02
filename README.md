# 大作业

## 作业要求

两人一组，利用相关 C++ 需要和加速（sse，多线程）手段，以及通讯技术

1. rpc，命名管道
2. http，socket

等实现函数（浮点数数组求和，求最大值，排序）。处理在两台计算机协作执行，尽可能挖掘两个计算机的潜在算力。

## 实现原理

本项目使用多线程方法和 socket 通讯，实现了在 Windows 主机和 Ubuntu 虚拟机之间的协作并行计算，包括求和、求最大值和排序。

在使用多线程的过程中，创新性地将函数递归和开辟线程结合，节约了多线程在最后汇总计算结果（收割）过程的计算时间。

传统的多线程方法如下图所示：

![500](images/README-traditional-multithread.png)

本项目中为了节约在 ``join()`` 处对大量数据结果汇总时的时间开销，使用了下图的方式：

![500](images/README-our-multithread.png)

即采用了类似二叉树结构的方式，在两个线程完成了它们的局部分布计算以后，从中选择一个线程来对两个结果进行综合，综合的结果作为新的局部分布计算结果，以此类推递归进行，直到最终只剩余一个线程为止，将这个数据传回主线程。

这个思路使用递归可以很简洁地实现，代码如下所示表示了使用多线程进行归并排序的过程。

```cpp
void merge_sort(float *array, int left, int right, int level, int idx_thd)
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
                array, left, mid, level + 1, idx_thd + (1 << level));
            merge_sort(array, mid + 1, right, level + 1, idx_thd);
            thrds[idx_thd + (1 << level)].join();
        }
        merge(array, left, mid, right);
    }
}
```

在代码中实现了：

- 线程的创建
- 线程内部的分布计算
- 对线程结果的汇总

代码的架构如下图所示

![500](images/README-code-multithread.png)

这里对线程的序号分配作简要说明：


