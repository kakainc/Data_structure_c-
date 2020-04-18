#include <iostream>
#include <vector>

using namespace std;

void bubble_sort(vector<int>&);
void select_sort(vector<int>&);
void insert_sort(vector<int>&);
void shell_sort(vector<int>&);
void quick_sort(vector<int>&, int, int);
void merge_sort(vector<int>&);
void heap_sort(vector<int>&);
void radix_sort(vector<int>&, int, int);
int main() {
    std::cout << "Hello, World!" << std::endl;
    vector<int> arr = {10, 8, 29, 2, 4, 35, 40, 6};
    bubble_sort(arr);
    select_sort(arr);
    insert_sort(arr);
    shell_sort(arr);
    quick_sort(arr, 0, 6);
    merge_sort(arr);
    heap_sort(arr);
    radix_sort(arr, 2, 10);
    for(int i : arr){
        cout << i << endl;
    }
    return 0;

}
/**跳跃式排序都不稳定***/
/**不稳定排序：选择排序，希尔排序，快速排序，堆排序***/
/**非原地排序：归并排序，基数排序***/
/***********************************/

void bubble_sort(vector<int>& arr){
    int len = arr.size();
    bool flag = true;
    for(int i=0; i<len && flag; i++){
        flag = false;
        for(int j=0; j<len-i-1; j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j], arr[j+1]);
                flag = true;
            }
        }
    }
}
/**冒泡排序：时间复杂度n**2，最好n，最坏n**2，空间复杂度1，原地排序，稳定排序***/

void select_sort(vector<int> &arr){
    int len = arr.size();
    for(int i=0; i<len; i++){
        int min = i;
        for(int j=i+1; j<len; j++){
            if(arr[min] > arr[j]){
                min = j;
            }
        }
        if(min != i){
            swap(arr[i], arr[min]);
        }
    }
}
/**选择排序：时间复杂度内**2，最好n**2，最坏n**2，空间复杂度1，原地排序，不稳定排序***/

void insert_sort(vector<int> &arr){
    int len = arr.size();
    for(int i=0; i<len-1; i++){
        for(int j=i+1; j>0; j--){
            if(arr[j]<arr[j-1]){
                swap(arr[j], arr[j-1]);
            }else{
                break;
            }
        }
    }
}
/**插入排序：时间复杂度n**2，最好n，最坏n**2，空间复杂度1，原地排序，稳定排序***/

void shell_sort(vector<int> &arr){
    int len = arr.size();
    int incre = len/2;
    while(incre>=1){
        for(int k=0; k<incre; k++){
            for(int i=k+incre; i<len; i+=incre){       // 开始插入排序
                for(int j=i; j>k; j-=incre){
                    if(arr[j]<arr[j-incre]){
                        swap(arr[j], arr[j-incre]);
                    }else{
                        break;
                    }
                }
            }
        }
        incre/=2;
    }
}
/**希尔排序：时间复杂度nlogn，最好nlog2n，最坏nlog2n，空间复杂度1，原地排序，不稳定排序***/

void quick_sort(vector<int> &arr, int l, int h){
    if(l>=h)
        return;
    int i=l, j=h, key=arr[l];
    while(i<j){
        while(i<j && arr[j]>=key){
            j--;
        }
        if(i<j){
            arr[i]=arr[j];
            i++;
        }
        while(i<j && arr[i]<key){
            i++;
        }
        if(i<j){
            arr[j]=arr[i];
            j--;
        }
    }
    arr[i]=key;
    quick_sort(arr, l, i-1);
    quick_sort(arr,i+1, h);
}
/**快速排序：时间复杂度nlogn，最好nlogn，最坏n**2，空间复杂度logn，原地排序，不稳定排序***/

void merge(vector<int>&arr, vector<int> &tem, int s, int m, int e){
    int i=s, z=m, j=m+1, n=e, k=0;
    while(i<=z && j<=n){
        if(arr[i]<=arr[j]){
            tem[k]=arr[i];
            k++;
            i++;
        }else{
            tem[k]=arr[j];
            k++;
            j++;
        }
    }
    while(i<=m){
        tem[k]=arr[i];
        k++;
        i++;
    }
    while(j<=n){
        tem[k]=arr[j];
        k++;
        j++;
    }
    for(int t=0; t<k; t++){
        arr[s+t]=tem[t];
    }
}

void merge_s(vector<int>&arr, vector<int> &tem, int s, int e){
    int m;
    m = (s+e)/2;
    if(s<e) {
        merge_s(arr, tem, s, m);
        merge_s(arr, tem, m + 1, e);
        merge(arr, tem, s, m, e);
    }
}

void merge_sort(vector<int> &arr){
    vector<int> tem(arr.size());
    int len = arr.size();
    merge_s(arr, tem, 0, len-1);
}
/**归并排序：时间复杂度nlogn，最好nlogn，最坏nlogn，空间复杂度n，非原地排序，稳定排序***/

void maxheap_change(vector<int> &arr, int f, int n){
    int j=2*f+1;
    while(j<n){
        if(j+1<n && arr[j+1]>arr[j]){
            j++;
        }
        if(arr[f]>arr[j])
            break;

        swap(arr[f], arr[j]);
        f=j;
        j=2*f+1;
    }
}
void heap_sort(vector<int> &arr){
    int len = arr.size();
    for(int i=(len-1)/2; i>=0; i--){
        maxheap_change(arr, i, len);
    }
    for(int j=len-1; j>0; j--){
        swap(arr[j], arr[0]);
        maxheap_change(arr, 0, j);
    }
}
/**堆排序：时间复杂度nlogn，最好nlogn，最坏nlogn，空间复杂度1，原地排序，不稳定排序***/

void radix_sort(vector<int> &arr, int k, int r){
    int len = arr.size();
    vector<int> carr = arr;
    for(int i=0, tok=1; i<k; i++, tok*=r){
        vector<int> tem(r, 0);
        for(int j=0; j<len; j++){
            tem[(arr[j]/tok)%r]++;
        }
        for(int m=1; m<r; m++){
            tem[m]+=tem[m-1];
        }
        for(int n=len-1; n>=0; n--){
            tem[(arr[n]/tok)%r]--;
            carr[tem[(arr[n]/tok)%r]]=arr[n];
        }
        for(int c=0; c<len; c++){
            arr[c]=carr[c];
        }
    }
}
/**基数排序：时间复杂度n*k，最好n*k，最坏n*k，空间复杂度n+k，非原地排序，稳定排序***/


