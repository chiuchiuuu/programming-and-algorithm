# 字符串

## 逻辑结构

零个或多个字符组成的有限序列，数据元素为单个字符的线性表。

- 串名
- 定界符
- 串值

## 存储结构

通常采用顺序存取。

串的长度的表示方式：

- 用一个变量。存储在表头或表尾。
- 用特殊字符作为字符串的终结符，通常为`'\0'`

## 基本操作

- 求长：`strlen()`
- 拼接：`strcat()`
- 复制：`strcpy()`
- 比较：`strcmp()`

## 模式匹配

在字符串S中寻找子串T的过程称为模式匹配，T称为模式。

### 朴素算法

暴力搜索

```c++
// 匹配子串，返回下标
int BF(char s[], char t[])
{
	int i = 0, j = 0;
	while (s[i] && t[j])
	{
		if (s[i] == t[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}

	if (t[j] == '\0')
		return i - j;
	else
		return -1;
}

// 利用C++的字符串类
int FindPat(string S, string P, int startIndex)
{
	for (int i = startIndex; i <= S.length() - P.length(); i++)
		if (S.substr(i, P.length()) == P)
			return i;
	return -1;
}
```

### KMP算法

核心思想：主串不进行回溯

### 思考题

1. 长度为n的字符串的子串数目：$\dfrac{n(n+1)}{2} + 1$
2. ​