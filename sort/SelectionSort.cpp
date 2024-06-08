#include <iostream>
using namespace std;

/**
 *  1. 原地排序算法：空间复杂度为O(1)
 *  2. 不稳定排序算法：每次都会选则未排序的最小值与前面交换位置，若这两个值相等也会交换
 *  3. 最好与最坏时间复杂度O(n^2)：无论数据如何，都会将两层循环跑满
 *  4. 平均时间复杂度O(n^2)：最好最坏都为O(n^2)
 * 
 * 大致思路：
 *      1. 将数组逻辑上分为两个区间，分别为 已排序 和 待排序
 *      2. 每次选择排序都会选择 待排序 中最小的元素
 *      3. 将其和 原本 待排序 的起始交换位置（现为已排序的末尾）
 */
void selection_sort(int a[], int n)
{
    if(n <= 1)  return;

    for(int i = 0; i < n; i++)
    {   
        int min = i;

        // j就相当于两个区间的分界
        for(int j = i + 1; j < n; j++)
        {
            // 寻找未排序中的最小值
            if(a[j] < a[min])
                min = j;    
        }

        // 交换这两个元素，即使相等，故为不稳定排序
        if(min != i)
        {
            int temp = a[i];
            a[i] = a[min];
            a[min] = temp;
        }
    }
    return;
}

int main()
{
    int a[] = {6, 5, 4 ,3, 2, 1};
    int n = sizeof(a) / sizeof(a[0]);

    selection_sort(a, n);

    for(int i = 0; i < n; i++)
        cout << a[i] << ' ';
    cout << endl;
    return 0;
}