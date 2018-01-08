#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <stack>
#include <cstdio>
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<stack>
using namespace std; 
#define M 5

/* 
 * 标准冒泡排序：嵌套循环比大小。
 */ 

template <typename T>
void BubbleSort(T *array, const int length) {
	if (array == NULL)
		throw invalid_argument("Array must not be empty");
	if (length <= 0)
		return;

	for (int i = 0; i < length - 1; ++i){
		for (int j = 0; j < length - 1 - i; ++j){
			if (array[j] > array[j + 1]){
				T tmp = array[j + 1];
				array[j + 1] = array[j];
				array[j] = tmp;
			}
		}
	}
}

/*
 * 冒泡排序优化1：如果某次内循环没有改变任何数据，则结束。
 */

template <typename T> 
void BubbleSort1(T *array, const int length) { 
	if (array == NULL)
		throw invalid_argument("Array must not be empty"); 
	if (length <= 0) 
		return; 
	bool flag = false; //设置标志位，用来判断内循环是否有数据交换

	for (int i = 0; i < length - 1; ++i){
		for (int j = 0; j < length - 1 - i; ++j){
			if (array[j] > array[j + 1]){
				T tmp = array[j + 1];
				array[j + 1] = array[j];
				array[j] = tmp;
				flag = true;
			}
		}
		if (!flag) return; //如果本次循环没有数据交换，则结束排序
	} 
} 

/*
 *冒泡排序优化2：鸡尾酒排序，一个外循环内跑两个内循环。
 */

template <typename T>
void BubbleSort2(T *array, const int length) {
	if (array == NULL)
		throw invalid_argument("Array must not be empty");
	if (length <= 0)
		return;
	int low = 0;
	int high = length - 1;

	while (high > low)
	{
		for (int i = low; i < high; ++i) //正向冒泡，确定最大值  
		{
			if (array[i] > array[i + 1])
			{
				T temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
			}
		}
		--high;

		for (int j = high; j > low; --j) //反向冒泡，确定最小值  
		{
			if (array[j] < array[j - 1])
			{
				T temp = array[j];
				array[j] = array[j - 1];
				array[j - 1] = temp;
			}
		}
		++low;
	}
}

/* 
 * 插入排序
 */ 

template <typename T> 
void InsertSort(T *array, const int length) {
	if (array == NULL)
		throw invalid_argument("Array must not be empty"); 
	if (length <= 0)
		return; 

	for (int i = 1; i < length; ++i){
		T tmp = array[i]; 
		int j = i - 1;
		while (j >= 0 && array[j] > tmp){ 
			array[j+1] = array[j]; 
			--j; 
		} 
		array[j+1] = tmp; 
	} 
} 

/*
* 插入排序
*/

template <typename T>
void InsertSort(T *array, const int left, const int right) {
	if (array == NULL)
		throw invalid_argument("Array must not be empty");
	if (right - left <= 0)
		return;

	for (int i = left + 1; i < right; ++i){
		T tmp = array[i];
		int j = i - 1;
		while (j >= 0 && array[j] > tmp){
			array[j + 1] = array[j];
			--j;
		}
		array[j + 1] = tmp;
	}
}

/*
 * 希尔排序
 */

template <typename T>
void ShellSort(T *array, const int length) {
	if (array == NULL)
		throw invalid_argument("Array must not be empty");
	if (length <= 0)
		return;
	//gap是设置的步长
	for (int gap = length >> 1; gap > 0; gap >>= 1){
		T tmp;
		for (int i = gap; i < length; ++i){
			tmp = array[i];
			int j = i;//后面要用到j，所以在for循环的外面初始化
			while (j >= gap && tmp < array[j - gap]){
				array[j] = array[j - gap];
				j -= gap
			}
			array[j] = tmp;
		}
	}
}

/* 
 * 快速排序1：
 * 将第一个元素array[left]提出来作pivot，i=left(该索引之前的数比pivot小，初始值为left)，
 * j从left+1开始遍历数组，找到一个比pivot小的数，i+1，如果i和j序列号不等就交换（小值到前）。
 * j到最右端之后，for循环结束，再把pivot与i所指数据做交换，当前pivot就到达了它的最终位置。
 */ 

template <typename T>
void Partion1(T *array, int left, int right){
	if (left >= right)
		return;

	int i = left;
	int j = left + 1;
	T pivot = array[left];						// 取第一个数为基准
	for (; j <= right; ++j){					// 循环直至 j 扫描至 right
		if (array[j] < pivot){					// 如果遇到比基准小的数，i右移一位
			i++;
			if (j != i){						// 如果i与j不重合，则交换他们指向的值
				swap(array[j],array[i]);
			}
		}
	}
	swap(array[left], array[i]);				// 基准值的位置确定
	Partion1(array, left, i - 1);
	Partion1(array, i + 1, right);
}

/*
 * 快速排序2：
 * 将第一个元素array[left]提出来作pivot，i = left+1从左向右遍历找到一个比pivot大的数停止，
 * 然后等待j从右往左遍历找到一个pivot小的数，两者交换，然后继续寻找直到i=j，for循环结束。
 * 之后我们需要做判断，如果pivot比i所指数据大就交换两者，否则i回退一步（因为开始忽略了首元素）。
 */

template <typename T>
void Partion2(T *array, int left, int right) {
	if (left >= right)
		return;

	int i = left + 1;
	int j = right;
	T pivot = array[left];						// 取第一个数为基准
	while (i < j){								// 循环直至 i,j 相遇
		while (i < j && array[j] >= pivot)		// j向左遍历，直到找到比pivot小的值
			--j;
		while (i < j && array[i] < pivot)		// i向右遍历，直到找到比pivot大的值
			++i;
		if (i < j)								// 如果i < j，就交换刚才找到的那两个值
			swap(array[j], array[i]);
	}
		
	if (array[i] <= array[left])				// 这里一定要做判断再决定是否交换
		swap(array[i], array[left]);
		
	else										// 如果不交换，说明left是最小，但i是不是第二小不确定，所以需要下次判断
		--i;
	Partion2(array, left, i - 1);
	Partion2(array, i + 1, right);
}

/*
 * 快速排序3：
 * 将第一个元素array[left]提出来作pivot，然后从j = right向前搜索第一个比pivot小的元素假设为array[k]，
 * 该元素放在array[left]的位置。因为array[left]已经保存pivot覆盖也没关系，于是array[k]又可以被覆盖了，
 * 从前往后搜索比pivot大的元素放到array[k]。一直进行下去直到i=j。
 */

template <typename T> 
void Partion3(T *array, int left, int right) {
	if (left >= right)
		return;

	int i = left;
	int j = right;
	T pivot = array[left];						// 取第一个数为基准
	while (i < j){								// 循环直至 i,j 相遇
		while (i < j && array[j] >= pivot)
			--j; 
		if (i < j)
			array[i++] = array[j];				// 从右向左扫描，将比基准小的数填到左边
		while (i < j && array[i] < pivot)
			++i; 
		if (i < j)
			array[j--] = array[i];				// 从左向右扫描，将比基准大的数填到右边
	} 
	array[i] = pivot;							// 将基准数填回
	Partion3(array, left, i - 1);
	Partion3(array, i + 1, right);
}

/*
* 快速排序3优化1：
* 当排序的子序列小于预定的值M时，采用插入排序
*/

template <typename T>
void PartionInsert(T *array, int left, int right) {
	if (left >= right)
		return;

	if (right - left <= M)
		InsertSort(array, left, right);
	else{
		int i = left;
		int j = right;
		T pivot = array[left];					// 取第一个数为基准
		while (i < j){							// 循环直至 i,j 相遇
			while (i < j && array[j] >= pivot)
				--j;
			if (i < j)
				array[i++] = array[j];			// 从右向左扫描，将比基准小的数填到左边
			while (i < j && array[i] < pivot)
				++i;
			if (i < j)
				array[j--] = array[i];			// 从左向右扫描，将比基准大的数填到右边
		}
		array[i] = pivot;						// 将基准数填回
		PartionInsert(array, left, i - 1);
		PartionInsert(array, i + 1, right);
	}
}

//产生随机数
template <typename T>
void Random(T *array, int left, int right)
{
	int size = right - left + 1;
	int i = left + rand() % size;
	swap(array[i], array[left]);
}

//取中位数移至left
template <typename T>
void Median(T *array, int left, int right)
{
	int mid = left + ((right - left )>> 1);
	int minIndex = right;

	if (array[minIndex] > array[mid])
		minIndex = mid;
	if (array[minIndex] > array[left])
		minIndex = left;
	if (minIndex != right)						//三个判断，把最小值移到最右侧
		swap(array[minIndex], array[right]);
	if (array[mid] < array[left])				//那么剩下的两个数，最小的那个就是中位数了
		swap(array[left], array[mid]);
}

/*
* 快速排序3优化2：
* 取随机数或者三值取中作为基准值
*/

template <typename T>
void PartionSecond(T *array, int left, int right) {
	if (left >= right)
		return;

//	Random(array, left, right);					// 优化2-1：取随机数至最左端（基准值）
	Median(array, left, right);					// 优化2-2：取中位数至最左端（基准值）
	int i = left;
	int j = right;
	T pivot = array[left];						// 取第一个数为基准
	while (i < j){								// 循环直至 i,j 相遇
		while (i < j && array[j] >= pivot)
			--j;
		if (i < j)
			array[i++] = array[j];				// 从右向左扫描，将比基准小的数填到左边
		while (i < j && array[i] < pivot)
			++i;
		if (i < j)
			array[j--] = array[i];				// 从左向右扫描，将比基准大的数填到右边
	}
	array[i] = pivot;							// 将基准数填回
	PartionSecond(array, left, i - 1);
	PartionSecond(array, i + 1, right);
}

/*
* 快速排序3优化3：
* 重复数据比较多的话，可以分为小于等于大于三段
*/

template <typename T>
void PartionThird(T *array, int left, int right) {
	if (left >= right)
		return;

	int less = left;
	int greater = right;
	int it = left;
	T pivot = array[left];						// 取第一个数为基准
	while (it <= greater){						// 循环直至it和greater相遇
		if (array[it] == pivot)					// 如果等于pivot，it右移
			++it;
		else if (array[it] < pivot){			// 如果小于pivot，扔左边，it和less右移
			swap(array[less], array[it]);
			++it;
			++less;
		}
		else{									// 如果大于pivot，扔右边，greater左移
			swap(array[greater], array[it]);
			--greater;
		}
	}
	PartionThird(array, left, less - 1);
	PartionThird(array, greater + 1, right);
}

/*
 * 快速排序主体函数（递归）
 */

template <typename T> 
void QuickSort(T *array, const int length) { 
	if (array == NULL)
		throw invalid_argument("Array must not be empty"); 
	if (length <= 0) 
		return; 

	Partion1(array, 0, length - 1);
//  Partion2(array, 0, length - 1);
//  Partion3(array, 0, length - 1);
//	PartionInsert(array, 0, length - 1);
//	PartionSecond(array, 0, length - 1);
//	PartionThird(array, 0, length - 1);
}

/*
 * 快速排序迭代实现
 */

template<typename T>
void QuickSortIteration(T *array, const int length) {

	stack<pair<int, int>> trace;
	trace.push(make_pair(0, length - 1));		// 将数组首尾压栈

	while (!trace.empty()) {
		auto top = trace.top();					// 将栈顶元素保存下来
		trace.pop();							// 弹出栈顶

		int i = top.first;						// 取出首尾地址
		int j = top.second;

		T pivot = array[i];						// 取第一个数为基准

		while (i < j) {							// 循环直至 i,j 相遇
			while (i < j && array[j] >= pivot)
				--j;
			if (i < j)
				array[i++] = array[j];			// 从右向左扫描，将比基准小的数填到左边
			while (i < j && array[i] < pivot)
				++i;
			if (i < j)
				array[j--] = array[i];			// 从左向右扫描，将比基准大的数填到右边
		}

		array[i] = pivot;						// 将基准数填回

		if (i > top.first) trace.push(make_pair(top.first, i - 1));
		if (j < top.second) trace.push(make_pair(j + 1, top.second));
	}
}

/*
*直接选择排序
*/

template <typename T>
void SelectSort(T *array, const int length) {
	if (array == NULL)
		throw invalid_argument("Array must not be empty");
	if (length <= 0)
		return;

	for (int i = 0; i < length - 1; ++i){
		int min = i;
		for (int j = i + 1; j < length; ++j)
			if (array[j] < array[min])
				min = j;
		if (min != i){
			T tmp = array[i];
			array[i] = array[min];
			array[min] = tmp;
		}
	}
}

/*
* 堆排序递归版
*/

template <typename T>
void MaxHeapifyRecursive(T *array, int i, int heapSize) {
	int sonl = 2 * i + 1;
	int sonr = 2 * i + 2;
	int dad = i;
	if (sonl <= heapSize && array[sonl]>array[i]){					//如果左子结点大于父结点，则父结点指向子结点
		dad = sonl;
	}
	if (sonr <= heapSize && array[sonr]>array[dad]){				//如果右子结点大于父结点，则父结点指向子结点
		dad = sonr;
	}
	if (dad != i){													//如果dad != i则说明父结点不是最大值，交换后递归执行MaxHeapifyRecursive
		swap(array[i], array[dad]);
		MaxHeapifyRecursive(array, dad, heapSize);
	}
}

/*
* 堆排序迭代版
*/

template <typename T>
void MaxHeapifyIteration(T *array, int left, int right) {
	//建立父结点指针和子结点指针
	int dad = left;
	int son = dad * 2 + 1;
	while (son <= right) {											//若子结点指针在范围内才做比较
		if (son + 1 <= right && array[son] < array[son + 1])		//先比较两个子结点的大小，选择最大的
			son++;
		if (array[dad] > array[son])								//如果父结点大于子结点代表调整完毕，直接跳出循环
			return;
		else {														//否则交换父子内容在继续子结点和孙结点的比较
			swap(array[dad], array[son]);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}

template <typename T>
void HeapSort(T *array, const int length) {
	if (array == NULL)
		throw invalid_argument("Array must not be empty");
	if (length <= 0)
		return;

	//初始化，i从最后一个父结点开始调整
	for (int i = length / 2 - 1; i >= 0; --i){
		//构建最大堆 
		//		MaxHeapifyRecursive(array, i, length - 1);
		MaxHeapifyIteration(array, i, length - 1);
	}
	//先将第一个元素和已经排好的元素前一位做交换，再从新调整（刚调整的元素之前的元素），直到排序完毕
	for (int i = length - 1; i >= 0; --i){
		swap(array[0], array[i]);
		//		MaxHeapifyRecursive(array, 0, i - 1);
		MaxHeapifyIteration(array, 0, i - 1);
	}
}

/*
 * 归并排序递归版
 */ 

template <typename T>
void Merge(T *array, T *reg, int left, int mid, int right) {
	int left1 = left, right1 = mid;
	int left2 = mid + 1, right2 = right;
	int k = left;
	while (left1 <= right1 && left2 <= right2)
		reg[k++] = array[left1] < array[left2] ? array[left1++] : array[left2++];
	while (left1 <= right1)
		reg[k++] = array[left1++];
	while (left2 <= right2)
		reg[k++] = array[left2++];
	for (k = left; k <= right; k++)
		array[k] = reg[k];
}

template <typename T> 
void MergeSortRecursive(T *array, T *reg, int left, int right) {
	if (left >= right)
		return;
	int mid = left + ((right - left) >> 1);
	MergeSortRecursive(array, reg, left, mid);		//左序列排序
	MergeSortRecursive(array, reg, mid + 1, right);	//右序列排序
	Merge(array, reg, left, mid, right);			//合并左右序列
} 

template <typename T> 
void MergeSort(T *array, const int length) { 
	if (array == NULL)
		throw invalid_argument("Array must not be empty"); 
	if (length <= 0) 
		return; 
	T* reg = (T*)malloc(sizeof(T) * length);

	if (reg == NULL)
	{
		fputs("Error: out of memory\n", stderr);
		abort();
	}
	MergeSortRecursive(array, reg, 0, length - 1);
	delete[] reg;
} 

/*
* 归并排序迭代版
*/

template<typename T> 
void MergeSortIteration(T *array, const int length) {
	if (array == NULL)
		throw invalid_argument("Array must not be empty");
	if (length <= 0)
		return;

	T* regA = array;
	T* regB = (T*)malloc(sizeof(T) * length);

	if (regB == NULL)
    {
        fputs("Error: out of memory\n", stderr);
        abort();
    }
	for (int seg = 1; seg < length; seg += seg) {												//步长，每次翻倍
		for (int left = 0; left < length; left += seg + seg) {
			int low = left, mid = min(left + seg, length), high = min(left + seg + seg, length);//因为可能会超出length
			int k = low;
			int left1 = low, right1 = mid;
			int left2 = mid, right2 = high;
			while (left1 < right1 && left2 < right2)											//这里的表达式没有等号，都是左闭右开区间
				regB[k++] = regA[left1] < regA[left2] ? regA[left1++] : regA[left2++];
			while (left1 < right1)
				regB[k++] = regA[left1++];
			while (left2 < right2)
				regB[k++] = regA[left2++];
		}
		T* temp = regA;																			//优化：交换辅助数组与原始数组的角色
		regA = regB;
		regB = temp;
	}
	if (regA != array) {																		//如果regA != array，则说明现在regA是辅助数组
		for (int i = 0; i < length; i++)														//所以需要拷贝数据到regB，也就是array。
			regB[i] = regA[i];
		regB = regA;																			//regB重新指向辅助数组
	}
	delete[] regB;
}

int main() { 
	int arr[] = {2,4,6,8,9,7,5,3,1};
	int len = sizeof(arr) / sizeof(*arr);
	//double arr[] = {4.5, 2.3,6.7, 3.5, 1.1};
	//const int len = sizeof(arr) / sizeof(arr[0]);
	BubbleSort(arr, len);
	//BubbleSort1(arr, len);
	//BubbleSort2(arr, len);
	//InsertSort(arr, len);
	//ShellSort(arr, len);	
	//QuickSort(arr, len);
	//QuickSortIteration(arr, len);
	//SelectSort(arr, len);	
	//HeapSort(arr, len);		
	//MergeSort(arr, len); 
	//MergeSortIteration(arr, len);
	//double类型不可以
	for(auto v : arr){
		cout << v << " ";
	} cout << endl;
}
