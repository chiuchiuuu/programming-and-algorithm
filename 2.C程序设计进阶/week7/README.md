# Week7 结构体与链表

## 结构体

### 结构体与结构体变量

- 定义
- 赋值

### 结构体变量与函数

结构体变量做函数参数和返回值是pass by value，与普通变量特性相同。

### 结构体变量与指针

```c++
struct student
{
	int id_num;
  	char name[10];
};

int main()
{
  	student mike = {};
  	student *one = &mike;
  	cout << (*one).id_num << endl;
  	cout << one->id_num << endl; // 两种方式等价
}
```

`->`：指向运算符

### 总结

结构体数据类型的特性与普通数据类型的特性是一致的。

## 链表

### 链表的定义

链表是一种非常常用的数据结构

- 链表头：指向第一个链表节点的指针
- 链表结点：链表中的每一个元素，包括：
  - 当前节点的数据
  - 下一个节点的地址
- 链表尾：不再指向其他结点的结点，存放地址为`NULL`

动态申请内存空间

- `int *pint = new int(1024);` `delete pint`
- `int *pia new int[4];` `delete [] pia;`

动态建立链表节点

```c++
struct student
{
  	int id;
  	student *next;
}

student *create()
{
  	student *head, *temp;
  	int num, n = 0;
  	head = new student;
  	temp = head;
  	cin >> num;
  	while (num != -1)
    {
      	n++;
      	temp->id = num;
      	temp->next = new student;
      	temp = temp->next;
      	cin >> num;
    }
  	if (n == 0)
    {
		head = NULL;
    }
  	else
    {
      	temp->next = NULL;
    }
  	return head;
}
```

### 链表的操作

遍历

```c++
int main()
{
  	student *pointer = create();
  	while (pointer->next != NULL)
    {
		cout << pointer->id << endl;
		pointer = pointer->next;
    }
  	return 0;
}
```

删除

- 第一个结点

```c++
temp = head;
head = head->next;
delete temp;
```

- 中间结点

```c++
// 两个指针，follow和temp
follow->next = temp->next;
delete temp;
```

```c++
student *delete(student *head, int id)
{
	student *temp, *follow;
  	temp = head;
  	if (head == NULL)
    {
		return head;
    }
  	if (head->id == id) // 第一个节点
    {
		head = head->next;
      	delete temp;
      	return head;
    }
  	while (temp != NULL && temp->id != id)
    {
		follow = temp;
		temp = temp->next;
    }
  	if (temp == NULL)  
    {
		cout << "Not found" << endl;
    }
  	else
    {
		follow->next = temp->next; // 中间结点
		delete temp;
    }
  	return head;
}
```

插入

```c++
student *insert(studen *head, int id)
{
	student *temp, *follow, *insert;
  	temp = head;
  	insert = new student;
  	insert->id = id;
  	insert->next = NULL;
  	if (head == NULL)
    {
      	head = insert;
      	return head;
    }
  	while ((temp-> next != NULL) && (temp->id < id))
    {
		follow = temp;
		temp = temp->next;
    }
  	if (temp == head)
    {
		insert->next = head;
		head = insert;
    }
    else
    {
		if(temp->next == NULL)
		{
			temp->next = insert;
		}
		else
		{
			follow->next = insert;
			insert->next = temp;
		}
	}
	return head;
}
```

### 双向链表

两个指针`ahead` 和 `next`

其余操作类似单向链表。

## 面向对象

计算机程序的理解：现实世界的解决方案在计算机系统中的映射