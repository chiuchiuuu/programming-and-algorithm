# Week5

## 继承和派生

###  定义

继承：在定义一个新的类B时，如果该类与某个已有的类A相似(指的是B拥有A的全部特点)， 那么就可以把A作为一个**基类**，而把B作为基类的一个**派生类**(也称**子类**)。 

- 派生类是通过对基类进行修改和扩充得到的。在派生类中，可以扩充新的成员变量 和成员函数。 
- 派生类一经定义后，可以独立使用，不依赖于基类。 
- 派生类拥有基类的全部成员函数和成员变 量，不论是private、protected、public 。 
- 在派生类的各个成员函数中，不能访问基类中的private成员。 

例：以学生为基类，派生出研究生，大学生，中学生这些子类。

```c++
class 派生类名: public 基类名
{
	...
};
```

### 派生类对象的内存空间

派生类对象的体积，等于基类对象的体积，再加上派生类对象自己的成员变量的体积。在派生类对象中，包含着基类对象，而且基类对象的存储位置位于派生类对象新增的成员变量之前。 



## 继承关系和复合关系

类之间三种关系：

- 无关系
- 继承关系
- 符合关系

### 继承：“是”关系

- 基类 A，B是基类A的派生类。 
- 逻辑上要求：“一个B对象也是一个A对象”。 

### 复合：”有“关系

- 类C中“有”成员变量k，k是类D的对象，则C和D是复合关系 
- 一般逻辑上要求：“D对象是C对象的固有属性或组成部分”。 

例一：”圆“类包含”点“类，这是圆和点就是复合关系

```c++
class Circle
{
  	double radius;
  	Point center;
};
```

例二：人狗关系！最好的写法是互相指向

```c++
class Master;

class Dog
{
	Master *pm;
};
class Master
{
  	Dog *dogs[10];
}
```



## 基类/派生类同名成员

基类和派生类可以有同名成员函数也可以有同名成员变量。派生类的同名成员会覆盖基类的同名成员，但可以通过域作用符：`::` 来访问。

一般来说，基类和派生类不定义同名成员变量 



## protected访问范围说明符

基类的private成员: 可以被下列函数访问：

- 基类的成员函数 
- 基类的友员函数 

基类的public成员: 可以被下列函数访问：

- 基类的成员函数
- 基类的友员函数
- 派生类的成员函数
- 派生类的友元函数
- 其他函数

基类的protected成员: 可以被下列函数访问：

- 基类成员函数
- 基类友元函数
- **派生类的成员函数**

例：

```c++
class  Father 
{
private: 
	int nPrivate;     //私有成员
public:  
	int nPublic;       //公有成员
protected:
	int nProtected;   // 保护成员
}; 

class Son : public Father 
{
	void AccessFather () 
	{
		nPublic = 1; // ok;
		nPrivate = 1;  // wrong
		nProtected = 1; // OK, 访问从基类继承的protected成员
		Son f;
		f.nProtected = 1; //wrong, f不是当前对象
	}
}; 

int main() 
{
	Father f;
	Son s; f.nPublic = 1;   // Ok
	s.nPublic = 1;  // Ok
	f.nProtected = 1;  // error
	f.nPrivate = 1;     // error
	s.nProtected = 1;  //error
	s.nPrivate = 1;   // error
	return 0;
} 
```



## 派生类的构造函数

派生类对象包含基类对象 

执行派生类构造函数之前, 先执行基类的构造函数 

### 初始化参数列表

```c++
构造函数名（形参表）：基类名（基类构造函数实参表）
{
	...
}
```

### 调用基类构造函数的两种方式 

显式：

- 初始化参数列表
- `derived::derived(arg_derived-list):base(arg_base-list) `

隐式：

-  派生类的构造函数中省略基类构造函数时，派生类的构造函数自动调用基类的默认构造函数

### 调用顺序

创建派生类的对象 时, 执行派生类的构造函数之前：

- 调用基类的构造函数：初始化派生类对象中从基类继承的成员
- 调用成员对象类的构造函数：初始化派生类对象中成员对象

执行完派生类的析构函数后: 

- 调用成员对象类的析构函数 
- 调用基类的析构函数 

**析构函数的调用顺序与构造函数的调用顺序相反**

```c++
class Base
{
public:
	int n;
	Base(int i) :n(i)
	{
		cout << "Base " << n << " constructed" << endl;
	}   
	~Base()
	{
		cout << "Base " << n << " destructed" << endl;
	}
};

class Derived :public Base
{
public:
	Derived(int i) :Base(i)
	{
		cout << "Derived constructed" << endl;
	}
	~Derived()
	{
		cout << "Derived destructed" << endl;
	}
};

int main()
{
	Derived Obj(3);
	return 0;
}

// 输出
// Base 3 constructed
// Derived constructed
// Derived destructed
// Base 3 destructed
```



## public继承的赋值兼容规则

```c++
class base {};
class derived : public base {};
base b;
derived d;
```

- 派生类的对象可以赋值给基类对象：`b = d;`
- 派生类对象可以初始化基类引用：`base &br = d;`
- 派生类对象的地址可以赋值给基类指针：`base *pb = &d;`



## 直接基类和间接基类

在声明派生类时，只需要列出它的直接基类，派生类沿着类的层次自动向上继承它的间接基类