## string类

`string`类是一个模板类，它的定义如下：

```cpp
typedef basic_string<char> string;
```

使用string类要包含头文件 `<string>`

 string对象的初始化: 

- ` string s1("Hello");    // 一个参数的构造函数 `
- `string s2(8, ‘x’);`  
  `// 两个参数的构造函数;8代表字符出现的次数`
- ` string month = “March”; `
- 不提供以字符和整数为参数的构造函数 ，故而下述初始化方法均为错误调用：
```cpp
string error1 = 'c';
string error2('u');
string error3 = 22;
string error4(8);
```
当我们需要把一个字符赋值给`string`对象时，可以调用赋值函数，而非构造函数：
```cpp
string s;
s = 'p';
```
### 使用`string`类时的一些注意事项：
- 构造的string太长而无法表达会抛出`length_error`异常 

- string 对象的长度用成员函数 `length()` 读取；
```cpp
string s("hello");
cout<<s.length()<<endl;
```
- string 支持流读取运算符
```cpp
string stringObject;
cin>>stringObject;
```
- string 支持 `getline` 函数：
```cpp
string s;
getline(cin, s);
```
### string的复制与连接
#### 复制
- 用`=`复制：
```cpp
string s1("cat"),s2;
s2 = s1;
```
- 用`assign()`成员函数进行部分复制：

```cpp
string s1("Karlsruhe"), s3;
s3.assign(s1, 1, 3);   
//从s1 中下标为1的字符开始复制3个字符给s3 
```
- 单个字符的复制：
```cpp
s2[5] = s1[5] = 'a';
```
- 逐个访问string对象中的字符：
```cpp
string s1("Hello");
for(int i = 0;i<s1.length();i++){
	cout<<s1.at(i)<<endl;
}
```
 其中，成员函数`at()`会检查范围，如果超出范围，会抛出`out_of_range`异常，而**下标运算符**  `[]`不做范围检查。


#### 连接

- 用`+`运算符连接字符串：
```cpp
string s1("good"),s2("morning!");
s1 += s2;
cout<<S1;
```
- 用成员函数`append(str, begin, size)`连接字符串：
```cpp
string s1("good"),s2("morning!");
s1.append(s2);
s2.append(s1,3,s1.size());
//下标为3开始, s1.size()个字符
//如果字符串内没有足够字符, 则复制到字符串最后一个字符 
```


### 比较`String`

- 用关系运算符比较大小
   - ==,>,>=...
   - 返回值为`bool`类型，成立为`True`
    ```cpp
	string s1("hello"),s2("hell");
	bool b = (s1==s2);
    ```
- 利用成员函数`compare()`

```cpp
string s1("hello"), s2("hello"), s3("hell");
int f1 = s1.compare(s2);
int f2 = s1.compare(s3);
int f3 = s3.compare(s1);
int f4 = s1.compare(1, 2, s3, 0, 3);         //s1 1-2; s3 0-3
int f5 = s1.compare(0, s1.size(), s3);      //s1 0-end
cout << f1 << endl << f2 << endl << f3 << endl;
cout << f4 << endl << f5 << endl; 

输出
0    // hello == hello
1    // hello > hell
-1   // hell < hello
-1   // el < hell
1    // hello > hell 
```

### 子串 `substr(begin, size)`
```cpp
string s1("hello world"),s2;
s2 = s1.substr(4,5);
//下标4开始，5个字符
cout<<s2<<endl;
//输出：o wor
```

### 交换

`swap()`

### 寻找字符

- `find(str, begin)`：从`begin`开始，从前往后找`str`第一次出现的地方
- `rfind()`：从后往前找，但注意此时返回的下标仍是`str`第一个字符开始的位置

找到则返回下标，否则返回 `string::npos`（`string`中定义的静态常量）

- `find_first_of(str1)`：从前向后查找`str1`中任何一个字符第一次出现的地方
- `find_last_of(str1)`:查找`str1`中任何一个字符最后一次出现的地方
- `find_first_not_of(str1)`:查找不在`str1`中的字母第一次出现的地方
- `find_last_not_of()`

### 替换`string`中的字符

- `erase(index)` 去掉下标`index`**以及之后**的字符
- `replace(begin, size, str)`：从`begin`开始的`size`个字符替换为`str`
- `replace(begin,size,str,str_begin,str_size)`:从`begin`开始的`size`个字符，被替换为`str`中下标`begin`开始的`size`个字符

### 插入

- `insert(index, str, begin, size)`：从`str`从`begin`开始的`size`个字符插入到`index`

### 转换char*

- `c_str()`:将普通的`string`对象转换为`char*`
```cpp
string s1("hello world");
printf("%s\n",s1.c_str());
//s1.c_str()返回传统的`const char*`类型字符串
//且该字符串增添'\0'结尾
```
- `data()`：`const char *p = str.data()`
- `copy()`

### 其他特性

- 成员函数 `capacity()` ：返回无需增加内存即可存放的字符数
- 成员函数 `maximum_size()` ：返回string对象可存放的最大字符数
- 成员函数 `length()` 和 `size()`：相同返回字符串的大小/长度
- 成员函数 `empty()` ：返回string对象是否为空
- 成员函数 `resize()` ：改变string对象的长度

## Reference
- [1] https://www.coursera.org/learn/cpp-chengxu-sheji/
- [2] https://github.com/chiuchiuuu/programming-and-algorithm