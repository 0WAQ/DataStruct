#include <iostream>
using namespace std;

int binary_search(int a[], int n, int value)
{
    int l = 0;
    int r = n - 1;

    while(l <= r)
    {   
        // 防止溢出
        int mid = l + ((r - l) >> 1);
    
        if(a[mid] > value)
            r = mid - 1;
        else if(a[mid] < value)
            l = mid + 1;
        else
        {
            // 确保该mid是第一个,否则继续迭代
            if(mid == 0 || a[mid - 1] != value) return mid;
            else r = mid - 1;
        }
    }

    return -1;
}