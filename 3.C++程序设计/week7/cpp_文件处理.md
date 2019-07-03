# Week7：文件操作和模板

## 文件操作

顺序文件：一个有限字符构成的顺序字符流 

文件流**类**：用于文件操作

- `ifstream`:读取数据
- `ofsteam`:写入数据
- `fstream`：读写数据

使用用/创建文件的基本流程

- 打开文件
  - 通过制定文件名，建立文件和文件流对象的关联
  - 指明文件的使用方式
- 读写文件
  - 利用读/写指针进行相应位置的操作
- 关闭文件

### 打开文件

- 初始化对象时打开
- 初始化后用`open`函数打开

```c++
#include <fstream>
ofstream outFile("clients.dat", ios::out | ios::binary)；
//ofstream时fstream中定义的类
//outFile时自定义的ofstream类的对象
//xx.dat是将要建立的文件的文件名
//ios::xxx 打开并建立文件的选项


ofstream fout;
fout.open("test.out", ios::out | ios::binary);
//第二种建立顺序文件的方法：先创建ofstream对象，再用open函数打开
```

打开选项

- `ios::out` ：输出到文件，删除原有内容 
- `ios::app`：输出到文件，保留原有内容，新加入的内容总是在尾部添加 
- `ios::binary`：以二进制文件格式打开文件

文件名：

- 绝对路径
- 相对路径
- 如果没有交代路径信息，就是在当前文件下找文件

判断打开是否成功

```c++
if (!fout)
{
  	cerr << "File open error!!" << endl;
}
```

### 文件的读写指针

- 对于输入文件，有一个读指针
- 对于输出文件，有一个写指针
- 对于输入输出文件，有一个读写指针 

读/写指针用于标识文件操作的当前位置,   该指针在哪里，读写操作就在哪里进行 。

相关函数：

- `tellp()`, `seekp()`
- `tellg()`, `seekg()`

```c++
//写指针
ofstream fout("a1.out", ios::app);
long location = fout.tellp();    //取得写指针的位置 
location = 10L;                  // 可为负值。10L是因为location是一个long型变量
fout.seekp(location);            // 将写指针移动到第10个字节处。seek postion
fout.seekp(location, ios::beg);  // 从头数location。
fout.seekp(location, ios::cur);  // 从当前位置数location
fout.seekp(location, ios::end);  // 从尾部数location
```

```c++
//读指针
ifstream  fin(“a1.in”,ios::in);
long location = fin.tellg();      //取得读指针的位置
location = 10L; 
fin.seekg(location);              //将读指针移动到第10个字  
fin.seekg(location, ios::beg);    //从头数location
fin.seekg(location, ios::cur);    //从当前位置数location 
fin.seekg(location, ios::end);    //从尾部数location 
```

### 二进制文件读写

二进制文件读写是直接读写二进制数据，如果直接拿记事本来看，结果未必正确。

```c++
int x=10;
fout.seekp(20, ios::beg);//从beginning开始的20个字节开始写起
fout.write((const char *)(&x), sizeof(int)); 
//写入x
fin.seekg(0, ios::beg);
fin.read((char *)(&x), sizeof(int)); 
```

### 例子：二进制文件读写
#### 二进制文件写入
```cpp
#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
class CStudent {
public:
	char szName[20];
	int nScore;
};
int main() {
	CStudent s;
	ofstream OutFile("students.dat",ios::out | ios::binary);
	//注意写入形式为二进制形式
		while (cin >> s.szName >> s.nScore) {
			if (stricmp(s.szName, "exit") == 0)
				break;//名字为exit则结束
			OutFile.write((char *) &s, sizeof(s));
			//写入的对象是s的引用
		}
	OutFile.close();
	return 0;
}
```
**Note:**
文本文件/二进制文件打开文件的区别：
-   在Unix与Linux下，二者一致，没有区别；
-   在Windows下，文本文件是以`"\r\n"`作为换行符
    - 读出时，系统会将`0x0d0a`只读入`0x0a`(`0x`代表二进制)
    - 写入时，对于`0x0a`系统会自动写入`0x0d`

#### 二进制文件读出
```cpp
#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
class CStudent {
public:
	char szName[20];
	int nScore;
};
int main() {
	CStudent s;
	ifstream inFile("studen.dat", ios::in | ios::binary);
	if (!inFile) {//判断文件是否打开成功
		cout << "error" << endl;
		return 0;
	}
	while (inFile.read((char *) &s, sizeof(s)))
	{
		int nReadedBytes = inFile.gcount();//读取了多少字节
		cout << s.szName << " " << s.nScore << endl;
	}
	inFile.close();
	return 0;
}
````
#### 二进制文件读写
```cpp
#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
class CStudent {
public:
	char szName[20];
	int nScore;
};
int main() {
	CStudent s;
    fstream iofile("students.dat",ios::in | ios::out | ios::binary);
    if (!inFile) {//判断文件是否打开成功
		cout << "error" << endl;
		return 0;
	}
    iofile.seekp(2*sizeof(s),ios::beg);
    iofile.write("Mike",strlen("Mike")+1);
    iofile.seekg(0,ios::beg);
    while (inFile.read((char *) &s, sizeof(s)))
	{
		cout << s.szName << " " << s.nScore << endl;
	}
    iofile.close();
    return 0;
}
```

#### 文件拷贝示例程序

```c++
#include <iostream>
#include <fstream>
using namespace std;
//用法示例：
//mycopy src.dat dest.dat
//如果dest.dat原来就有，则被覆盖

int main(int argc, char *argv[])
//命令行参数的使用
{
	if (argc != 3)
	{
		cerr << "File name missing!" << endl;
		return 1;
	}
	ifstream inFile(argv[1], ios::binary | ios::in);//打开文件用于读取
	if (!inFile)
	{
		cout << "inFile open error!" << endl;
		return 2;
	}

	ofstream outFile(argv[2], ios::binary | ios::out);
	if (!outFile)
	{
		cout << "outFile open error!" << endl;
        inFile.close();
		return 3;
	}

	char c;
	while (inFile.get(c))
	{
		outFile.put(c);
	}
	outFile.close();
	inFile.close();
	return 0;
}
```
## Reference
- [1] https://www.coursera.org/learn/cpp-chengxu-sheji/
- [2] https://github.com/chiuchiuuu/programming-and-algorithm