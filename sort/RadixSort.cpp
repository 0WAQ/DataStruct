#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

/**
 * 使用场景：要求数据可以被划分成高、低位，且位之间有递进关系
 * 局限性：当数据不等长时，要补上（或前或后，要看具体情况）最大或者最小的位，
 *          底层排序必须是稳定的，否则会破坏之前排序的结果
 * 
 * 对于每一位排序，可以使用计数排序或者桶排序
 * 
 *  1. 非原地排序算法：因为需要使用桶或者计数排序
 *  2. 稳定排序算法：底层是稳定的
 *  3. 时间复杂度O(n)：假设数据有k位，那么需要调用k次O(n)
 */

// 
#define NUM_OF_POS(a, pval) ((a) / pval) % 10

// 利用计数排序
void radix_sort(int a[], int n, int num_cnt) // num_cnt：最大位数
{
    // 计数，最大值是9
    int cnt[10] = {0}; 
    int flag = 0;

    int* pres = new int[n];

    // 最大10位数
    for(int i = 0; i < num_cnt; i++)
    {
        // clear
        memset(cnt, 0, sizeof(cnt));

        // 求当前的基数, 是第几位
        int pval = pow(10, i);

        // 获取数组的每个元素基位的位
        for(int j = 0; j < n; j++)
        {
            // 若位数不够pval 或者 该位本身就为0，那么idx = 0
            int idx = NUM_OF_POS(a[j], pval);
            cnt[idx]++; // 计数
        }

        // 当前位为0的个数有9个，其余位最多只能有一个
        if(cnt[0] == 9) // 相当于有一个元素比其它元素多一位（甚至多位）
            flag++;     // 也有可能是有九个数据的某位为0，一个不为0

        if(flag >= 2)
            break;

        // 求前缀和
        for(int j = 1; j < 10; j++)
            cnt[j] += cnt[j - 1];

        // 从后向前遍历，为了稳定性
        for(int j = n - 1; j >= 0; j--)
        {   
            // 获取基数
            int idx = NUM_OF_POS(a[j], pval);
            pres[cnt[idx] - 1] = a[j];
            cnt[idx]--;
        }

        memcpy(a, pres, sizeof(pres));
    }
    delete pres;
}

int main()
{
    int a[] = {123, 12341, 1232134, 124, 236, 128, 1112313129, 98, 9, 8989};
    int n = sizeof(a) / sizeof(a[0]);

    radix_sort(a, n, 10);

    for(int i = 0; i < n; i++)
        cout << a[i] << ' ';
    cout << endl;
    return 0;
}