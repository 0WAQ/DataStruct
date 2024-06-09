#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

/**
 * 思路：将n个数据有序地划分到m个桶中，分别对桶内的数据排序，最后合并
 * 用途：外部排序中
 * 
 *  1. 非原地排序算法：空间复杂度为O(n)
 *  2. 非稳定排序算法：每个桶内使用了快排，所以不稳定
 *  3. 最好时间复杂度O(n)：有n个数据，m个桶，每个桶有k = n / m个数据，每个桶使用快排，O(klogk)
 *                  每个桶的时间复杂度为O(mklogk) = O( nlog(n / m) )，
 *                  当m接近n时，log(n / m)很小，复杂度为O(n)
 *  4. 最坏时间复杂度O(nlogn)：极端情况下，数据被划分到一个桶内，退化为O(nlogn)
 */

struct barrel
{
    int node[10]; // 桶的容量为10
    int cnt; // 桶中元素个数
};

void bucket_sort(int a[], int n)
{
    // 寻找数组中的最大、最小值
    int mx = a[0], mi = a[0];
    for(int i = 1; i < n; i++)
        if(mx < a[i])
            mx = a[i];
        else if(mi > a[i])
            mi = a[i];

    
    // 按照最大、最小值，划分为num个桶
    int num = (mx - mi + 1) / 10 + 1;
    // num个桶
    struct barrel* pBarrel = new barrel[num];
    memset(pBarrel, 0, sizeof(barrel) * num);

    // 将数组划分给num个桶
    for(int i = 0; i < n; i++)
    {   
        // 划分给第k个桶
        int k = (a[i] - mi + 1) / 10;
        // 第k个桶内的数据+1
        (pBarrel + k)->node[(pBarrel + k)->cnt++] = a[i];
    }

    int pos = 0;
    for(int i = 0; i < num; i++)
    {
        if((pBarrel + i)->cnt != 0)
        {
            // 对每个桶内的数据进行快排
            sort((pBarrel + i)->node, (pBarrel + i)->node + (pBarrel + i)->cnt);

            // 将桶内的数据拷贝给数组a
            for(int j = 0; j < (pBarrel + i)->cnt; j++)
                a[pos++] = (pBarrel + i)->node[j];
        }
    }
    
    delete pBarrel;
}

int main()
{
    int a[] = {5, 4, 40, 2, 80, 70, 16, 44, 52, 60, 30, 10, 55, 117, 41, 100, 89, 99, 97, 48};
    int n = sizeof(a) / sizeof(a[0]);

    bucket_sort(a, n);

    for(int i = 0; i < n; i++)
        cout << a[i] << ' ';
    cout << endl;
    return 0;
}