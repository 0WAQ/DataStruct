#include <iostream>
using namespace std;

int binary_search(int a[], int n, int value)
{
    int l = 0, r = n - 1;
    while(l <= r)
    {
        int mid = l + ((r - l) >> 1);
        if(a[mid] > value)
            r = mid - 1;
        else if(a[mid] < value)
            l = mid + 1;
        else
        {   
            // 确保查找的元素是最后一个
            if(mid == n - 1 || a[mid + 1] != value) return mid;
            else    l = mid + 1;
        }
    }

    return -1;
}