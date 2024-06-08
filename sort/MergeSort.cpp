#include <iostream>
#include <cstring>
using namespace std;

/**
 *  1. 非原地排序算法：空间复杂度尾O(n)
 *  2. 稳定排序算法：在合并两子数组时，当两个元素相等时，只要保证 l ~ r 中的在前即可
 *  3. 最好、最坏、平均时间复杂度均为O(nlogn)：与数组的有序程度无关
 * 
 *  思路：先分治，递到最小，然后再返回合并的过程中进行比较排序（先处理小，再处理大）
 */

// 合并函数
void merge(int a[], int l, int mid, int r)
{
    int* tmp = new int[r - l + 1];
    int i = l, j = mid + 1, k = 0;

    // 将a[l ~ mid] 与 a[mid + 1 ~ r]比较并copy到tmp数组
    while(i <= mid && j <= r) {
        if(a[i] <= a[j])    // 相等时将 l ~ mid 中的元素放在前即可做到稳定
            tmp[k++] = a[i++];
        else
            tmp[k++] = a[j++];
    }

    // 将剩余数据拷贝到tmp中
    while(i <= mid) tmp[k++] = a[i++];
    while(j <= r) tmp[k++] = a[j++];

    memcpy(a + l, tmp, (r - l + 1) * sizeof(int));
    delete tmp;
}

// 归并排序
void merge_sort(int a[], int l, int r)
{
    if(l >= r) return;

    // 分治
    int mid = (l + r) >> 1;
    merge_sort(a, l, mid);
    merge_sort(a, mid + 1, r);

    // 合并
    merge(a, l, mid, r);
}

int main()
{
    int a[] = {6, 5, 4, 3, 2, 1};
    int n = sizeof(a) / sizeof(a[0]);

    merge_sort(a, 0, n - 1);

    for(int i = 0; i < n; i++)
        cout << a[i] << ' ';
    cout << endl;
    return 0;
}