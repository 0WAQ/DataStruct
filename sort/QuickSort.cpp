#include <iostream>
using namespace std;

/**
 *  1. 原地排序算法：空间复杂度为O(1)
 *  2. 稳定排序算法：解释如代码注释
 *  3. 最好时间复杂度O(nlogn)：每次选择的pivot都大概是数据的最中心
 *  4. 最坏时间复杂度O(n^2)：每次选择的pivot都是左右端点，那就需要进行n次分区操作，
 *                              每次分区中都需要扫描大约 n / 2 个元素
 *  5. 平均时间复杂度O(nlogn)：后面的章节再补！！！
 * 
 *  思路：每次先对区间进行一个大致的排序，然后再分治递归处理小区间
 */

// 选枢点，将区间中比枢点小的元素放在左边
int partition(int a[], int l, int r)
{
    int i = l; // i将区间分为两部分，左右分别为 已处理 和 未处理 区间

    // i是下一个比枢点小的元素应该换到的位置
    for(int j = l; j < r; j++)  // j遍历区间，将比枢点小的元素刚到i的位置上
    {
        // 当第一个相同元素x为i时，且下一个比枢点小的元素z在第二个相同元素y的后面，此时x与z会交换，不稳定
        if(a[j] < a[r]) // 选a[r]为pivot
        {
            swap(a[i], a[j]); // 交换
            i++; // 下一个点的位置+1
        }
    }
    // 遍历完后，所有比枢点小的元素都在i的左边，
    swap(a[i], a[r]);
    return i;
}

void quick_sort(int a[], int l, int r)
{
    if(l >= r)  return;

    // 分区
    int p = partition(a, l, r);
    
    // 分治
    quick_sort(a, l, p - 1);
    quick_sort(a, p + 1, r);
}

int main()
{
    int a[] = {6, 5, 4, 3, 2, 1};
    int n = sizeof(a) / sizeof(a[0]);

    quick_sort(a, 0, n - 1);
    
    for(int i = 0; i < n; i++)
        cout << a[i] << ' ';
    cout << endl;
    return 0;
}