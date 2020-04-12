## 函数模板

### 泛型程序设计

- Generic Programming

- 算法实现时不指定**具体**要操作的数据的类型，适用于多种数据结构; 通俗的来说，算法实现一遍，但适用于多种数据结构；

- 大量编写模板，使用模板的程序设计：
  - 函数模板
  - 类模板

- 优势：减少重复代码的编写;

### 函数模板

- 定义

```c++
template<class 类型参数1, class 类型参数2, ...>
返回值类型 模板名(形参表)
{
  	函数体
}
```

- 例：交换函数

```c++
template <class T>
void swap(T &x, T &y)
{
	T tmp = x;
  	a = b;
  	b = tmp;
}
// 编译器会自动生成相应的函数
int main() {
    int n = 1, m = 2;
    Swap(n,m);
    //编译器自动生成void Swap(int &, int &)函数
    double f = 1.2, g =2.3;
    //编译器自动生成void Swap(double &,double &)函数，并进行调用；
    Swap(f,g);
    return 0;
}

```
**Notes:**
- 函数模板中可以有不止一个类型参数，即函数类型不一致。如下面的例子：
  ```cpp
  template<class T1, class T2>//通过定义不同类型的模板
  T2 print(T1 arg1, T2 arg2) {
      cout<<arg1<<" "<<arg2<<endl;
      return arg2; //返回值也是T2类型
  }
  ```
- 函数模板可以重载，只要形参表不同即可。如下面的例子：
  ```cpp
  template<class T1,class T2>
  void print(T1 arg1,T2 arg2) {}
  
  template<class T>
  void print(T arg1, T arg2) {}
  ```

## 编译器匹配函数的顺序

- **Step 1:** 先找参数完全匹配的普通函数(非由模板实例化而得的函数)
- **Step 2:** 再找参数完全匹配的模板函数
- **Step 3:** 再找实参经过自动类型转换后能够匹配的普通函数 
- **Step 4:** 上面的都找不到, 则报错 

下面我们用一个例子来说明，模板调用顺序：
```cpp
template <class T>
T Max(T a, T b) {
    cout<<"Template Max 1"<<endl;
    return 0;
}
template <class T, class T2>
T Max(T a, T2 b) {
    cout<<"Template Max 2"<<endl;
    return 0;
}
double Max(double a,double b) {//普通函数
    cout<<"MyMax"<<endl;
    return 0;
}
int main() {
    int i = 4, j = 5;
    Max(1.2,3.4);//调用Max(double, double)
    Max(i,j);
    // i j 为int类型，没有普通函数能够完全匹配
    //调用第一个T Max(T a,T b)模板生成的函数
    Max(1.2,3);//调用第二个T Max(T a, T2 b)模板生成的函数
    return 0;
}
```

***注意**
赋值兼容原则引起函数模板中类型参数的二义性

```c++
template<class T>
T myFunction(T arg1, T arg2) 
{
  	cout<<arg1<<“   ”<<arg2<<“\n”;
  	return arg1; }
…
myFunction(5, 7);        //ok: replace T with int
myFunction(5.8, 8.4);    //ok: replace T with double
myFunction(5, 8.4);      //error: replace T with int or double? 二义性 
```

对于这种情况，我们可以在函数模板中使用多个类型参数, 可以有效地避免二义性

## Reference
- [1] https://www.coursera.org/learn/cpp-chengxu-sheji/
- [2] https://github.com/chiuchiuuu/programming-and-algorithm