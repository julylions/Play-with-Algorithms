#include <iostream>
#include <cassert>
#include <ctime>

using namespace std;

// 二分查找法, 在有序数组arr中, 查找target
// 如果找到target, 返回第一个target相应的索引index
// 如果没有找到target, 返回比target小的最大值相应的索引, 如果这个最大值有多个, 返回最大索引
// 如果这个target比整个数组的最小元素值还要小, 则不存在这个target的floor值, 返回-1
/*
最大的问题在于，当arr[mid] < target的时候，此时arr[mid]有可能就是我们要求的floor值。
比如数组[..., 1, 3, ...]，target=2；当arr[mid]指向1的时候，此时1就是这个数组对于2的floor值。
但是你的逻辑依然让l=mid+1，相当于错过了这个值。应该让l=mid，也就是让l留在这里，然后继续观察看会不会有更合适的值。

当我们让l=mid的时候，会有一个很微妙的问题：当l=a，r=a+1这种情况的时候，由于下取整，mid计算出来仍然是a==l，
此时我们的程序会进入一个死循环（随便找一个例子打印出循环每次的l，r和mid调试试试看：））。
要打破这个死循环，我们需要在l=a, r=a+1这种情况下，计算出的mid是r的值，这样可以执行r=mid-1，进而在下次while循环里退出。
所以在floor中，我们计算mid的方式是使用上取整，即mid=(l+r+1)/2。为了防止溢出，我的代码写成mid = l + (r-l+1)/2。

这样计算出的arr[l]，将是比target小的最大的元素。之后我们来看arr[l+1]是不是target，如果是，我们的floor值取l+1的位置，
否则就是l的位置。这是根据floor的定义来的。当然，在有些情况，我们可能就是想求出比target小的最大元素（即使arr中含有target），
那么这一步就可以免掉了。
*/
template<typename T>
int floor(T arr[], int n, T target){

    assert( n >= 0 );

    // 寻找比target小的最大索引
    int l = -1, r = n-1;
    while( l < r ){
        // 使用向上取整避免死循环
        int mid = l + (r-l+1)/2;
        if( arr[mid] >= target )
            r = mid - 1;
        else
            l = mid;
    }

    assert( l == r );

    // 如果该索引+1就是target本身, 该索引+1即为返回值
    if( l + 1 < n && arr[l+1] == target )
        return l + 1;

    // 否则, 该索引即为返回值
    return l;
}


// 二分查找法, 在有序数组arr中, 查找target
// 如果找到target, 返回最后一个target相应的索引index
// 如果没有找到target, 返回比target大的最小值相应的索引, 如果这个最小值有多个, 返回最小的索引
// 如果这个target比整个数组的最大元素值还要大, 则不存在这个target的ceil值, 返回整个数组元素个数n
template<typename T>
int ceil(T arr[], int n, T target){

    assert( n >= 0 );

    // 寻找比target大的最小索引值
    int l = 0, r = n;
    while( l < r ){
        // 使用普通的向下取整即可避免死循环
        int mid = l + (r-l)/2;
        if( arr[mid] <= target )
            l = mid + 1;
        else // arr[mid] > target
            r = mid;
    }

    assert( l == r );

    // 如果该索引-1就是target本身, 该索引+1即为返回值
    if( r - 1 >= 0 && arr[r-1] == target )
        return r-1;

    // 否则, 该索引即为返回值
    return r;
}


// 测试我们用二分查找法实现的floor和ceil两个函数
// 请仔细观察在我们的测试用例中，有若干的重复元素，对于这些重复元素，floor和ceil计算结果的区别：）
int main(){

    int a[] = {1, 1, 1, 2, 2, 2, 2, 2, 4, 4, 5, 5, 5, 6, 6, 6};
    int n = sizeof(a)/sizeof(int);
    for( int i = 0 ; i <= 8 ; i ++ ){

        int floorIndex = floor(a, n, i);
        cout<<"the floor index of "<<i<<" is "<<floorIndex<<".";
        if( floorIndex >= 0 && floorIndex < n )
            cout<<"The value is "<<a[floorIndex]<<".";
        cout<<endl;

        int ceilIndex = ceil(a, sizeof(a)/sizeof(int), i);
        cout<<"the ceil index of "<<i<<" is "<<ceilIndex<<".";
        if( ceilIndex >= 0 && ceilIndex < n )
            cout<<"The value is "<<a[ceilIndex]<<".";
        cout<<endl;

        cout<<endl;
    }

    return 0;
}
