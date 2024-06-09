#include <iostream>
#include <cstring>
using namespace std;

/**
 * 利用桶进行排序
 *  1. 非原地排序算法：空间复杂度为O(n + max{a[i]})
 *  2. 稳定排序算法：解释如下
 *  3. 时间复杂度：O(n),当数组最大值max比数组的个数size大很多时为O(max{a[i]})
 *  4. 局限性：只能给非负整数排序，若排序对象不满足要求，则需对其进行处理
 */
void counting_sort(int a[], int n)
{
    if(n <= 1)  return;

    // 查找数组中最大的值
    int mx = a[0];
    for(int i = 1; i < n; i++)
        if(mx < a[i])
            mx = a[i];
    
    // 申请c数组，保存数组中的不同元素的个数
    int* c = new int[mx + 1];
    memset(c, 0, sizeof(c)); // 初始化为0

    // 计数：计算每个元素的个数，下标为数组a的值
    for(int i = 0; i < n; i++)
        c[a[i]]++;

    // 求前缀和，表示小于等于i的元素个数有c[i]个
    for(int i = 1; i < n; i++)
        c[i] += c[i - 1];

    
    int* r = new int[n];
    // 从后向前遍历
    for(int i = n - 1; i >= 0; i--)
    {
        int idx = c[a[i]] - 1; // a[i]这个元素是第c[a[i]]个，在r中的下标应为idx
        r[idx] = a[i];  // 元素相同时，会将后边的元素放到后边的位置去
        c[a[i]]--;
    }

    // 拷贝给原数组
    memcpy(a, r, n * sizeof(int));

    delete r, c;
}

int main()
{
    int a[] = {6, 6, 5, 4, 3, 3, 2, 2, 1, 0, 0};
    int n = sizeof(a) / sizeof(a[0]);

    counting_sort(a, n);
    
    for(int i = 0; i < n; i++)
        cout << a[i] << ' ';
    cout << endl;
    return 0;
}