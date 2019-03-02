#include <iostream>
#include <fstream>

using namespace std;

template <class T>

/*插入排序每次选择一个元素K插入到之前已排好序的部分A[1…i]中，
插入过程中K依次由后向前与A[1…i]中的元素进行比较。若发现发现A[x]>=K,
则将K插入到A[x]的后面，插入前需要移动元素,从小到大，稳定性排序 o(n*n)
空间复杂度o(1);
*/
void InsertSort(T R[],int n)
{
	int i,j;
	for(i = 1;i < n;i++)
	{
		T tmp = R[i];
		j = i-1;
		while(j>=0&&R[j]>tmp)
		{
			R[j+1] = R[j];
			j--;
		}

		R[j+1] = tmp;
	}
}

template <class T>

/*：通过无序区中相邻记录关键字间的比较和位置的交换,
使关键字最小的记录如气泡一般逐渐往上“漂浮”直至“水面”。 
*/
void SwapSort(T R[],int n)//冒泡排序
{
	for(int i = 0;i < n ;i++)
	{
		for(int j = n-1; j >i ;j--)
		{
			if(R[j] < R[j-1])
			{
				T tmp = R[j-1];
				R[j-1] = R[j];
				R[j] = tmp;
			}
		}
	}
}

template <class T>

void SelectSort(T R[],int n)
{
	for(int i = 0;i < n;i++)
	{
		int k = i;
		T min= R[i];
		for(int j = i+1;j < n;j++)
		{
			if(R[j] < min)
			{
				min = R[j];
				k = j;
			}
		}
		T tmp;
		tmp = R[i];
		R[i]= min;
		R[k] = tmp;
	}
}

template <class T>
/*在待排序的n个记录中任取一个记录(通常取第一个记录),把该记录放入适当位置后,
	数据序列被此记录划分成两部分。所有关键字比该记录关键字小的记录放置在前一部分,
	所有比它大的记录放置在后一部分,并把该记录排在这两部分的中间(称为该记录归位),
	这个过程称作一趟快速排序
	*/
void QuickSort(T R[],int start ,int end)
{
	if(start > end)
		return;
	int i = start;
	int j = end;

	T basepoint = R[i];
	while(i <j)
	{

		while(j>i&&R[j]>=basepoint)
			j--;
		R[i] = R[j];
		while(i<j&&R[i]<=basepoint)
			i++;
		R[j] = R[i];		
	}
	R[i] = basepoint;
	QuickSort(R,start,i-1);
	QuickSort(R,j+1,end);
}

template <class T>

void Merge(T r[],int start,int middle,int end,T rf[])
{
	int i,j,k;
	i = start;
	j = middle+1;
	k = 0;
	while(i<=middle&&j<=end)
	{
		if(r[i]<r[j])
			rf[k++] = r[i++];
		else
			rf[k++] = r[j++];
	}
	while(i<=middle)
		rf[k++] = r[i++];
	while(j<=end)
		rf[k++] = r[j++];

	for(int i = 0;i < k;i++)
	{
		r[start+i] = rf[i];
	}
}

template <class T>

void MergeSort(T R[],int low ,int high,T tmp[])
{
	if(low<high)
	{
		MergeSort(R,low,(low+high)/2,tmp);
		MergeSort(R,(low+high)/2+1,high,tmp);

		Merge(R,low,(low+high)/2,high,tmp);
	}
}
bool MergeSort(int a[], int n) 
{
	int *p = new int[n];

	if(p == NULL)
		return false;
	else
	{
		MergeSort(a,0,n-1,p);
		
		delete[] p;
		return true;
	}
	
}

//计数排序
void CountSort(int A[],int n)
{
	int *B,*C;
	int max=0;
	for(int i = 0;i<n;i++)
	{
		if(A[i]>max)
			max = A[i];
	}
	C = new int[max+1];
	for(int i = 0;i<=max;i++)
	{
		C[i] = 0;
	}
	B = new int[n+1];
	for(int i = 0;i<=n;i++)
	{
		B[i] = 0;
	}
	for(int i = 0;i < n;i++)
		C[A[i]] = C[A[i]]+1;
	for(int j = 1;j<=max;j++)
		C[j] = C[j-1]+C[j];
	for(int s=n-1;s>=0;s--)
	{
		B[C[A[s]]] = A[s];
		C[A[s]] = C[A[s]] - 1;
	}
	for(int i = 1;i<=n;i++)
	{
		A[i-1] = B[i];
	}
}


//堆排序
template<class T>
void BuildHeap(T *R,int size)//建立堆；
{
	for(int i = (size-1)/2;i>=0;i--)//非叶子节点最大序号为size-1/2，即是最后一个元素的父节点。
	{
		MinHeapAdjust(R,i,size);
	}
}

template<class T>
void MinHeapAdjust(T R[],int i, int size)
{
	int j;
	T tmp;

	tmp = R[i];
	j = 2*i+1;
	while(j<size)
	{
		if(j+1<size&&R[j+1]<R[j])  //在左右孩子中找到最小的
			j++;
		if(R[j]>=tmp)
			break;
		R[i] = R[j];  //把最小的网上移动，替换他的父节点
		i = j;
		j = 2*i +1;
	}
	R[i] = tmp;
}
template<class T>
void MinHeapSort(T R[],int size)
{
	BuildHeap(R,size);
	for(int i = size -1;i>=1;i--)
	{
		swap(R[i],R[0]);
		cout<<R[0];
		MinHeapAdjust(R,0,i);
	}
}

void Maxheepadjust(int a[],int i,int size)
{
	int j = i*2+1; //right child
	int tmp = a[i];
	while(j<size)
	{
		if(j+1<size && a[j+1]>a[j])
			j++;
		if(tmp>a[j])
			break;
		a[i] = a[j];
		i = j;
		j = i*2+1;
	}
	a[i] = tmp;
}


