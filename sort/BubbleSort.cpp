#include <iostream>
using namespace std;

/**
 *  1. 原地排序算法：只涉及相邻数据的交换，空间复杂度为O(1)
 *  2. 稳定排序算法：当两个元素相等时，不会交换其位置 
 *  3. 最好时间复杂度O(n)：数据已经有序，只需冒泡一次
 *  4. 最坏时间复杂度O(n^2)：数据是倒序排列，需要冒泡n次
 *  5. 平均时间复杂度O(n^2)：https://time.geekbang.org/column/article/41802
 *         利用 有序对 与 有序度 来证明（不严格）
 * 
 *  大致思路
 *      1. 从头开始，依次操作相邻的两个数据，若为逆序对，则交换
 *      2. 每次冒泡结束后，都会使有序元素个数多1
 *      3. 可以优化，冒泡中若无元素交换，则说明数组已有序，可以提前退出
 */
void bubble_sort(int a[], int n)
{
    // 数组长度为 1 时，无需排序
    if(n <= 1)  return;

    // 进行n次冒泡
    for(int i = 0; i < n; i++)
    {
        // 表示本轮冒泡是否由进行过交换
        bool flag = false;

        // 进行第i次冒泡时，后i位有序
        for(int j = 0; j < n - i - 1; j++)
        {
            // 相等时不会交换
            if(a[j] > a[j + 1]) // 交换操作
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                flag = true;
            }
        }

        // 若进行没有进行过交换，则说明数组以有序，提前退出
        if(!flag)   break;
    }
}

int main()
{
    int a[] = {4, 5, 6, 3, 2, 1};
    int n = sizeof(a) / sizeof(a[0]);

    bubble_sort(a, n);

    for(int i = 0; i < n; i++)
        cout << a[i] << ' ';
    cout << endl;

    return 0;
}