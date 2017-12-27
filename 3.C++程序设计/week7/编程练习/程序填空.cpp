#include <iostream>
using namespace std;

template <class T>
class CArray3D
{
private:
	T ***ptr;
	int size1, size2, size3;
public:
	CArray3D(int s1, int s2, int s3) :size1(s1), size2(s2), size3(s3)
	{
		if (size1 == 0 || size2 == 0 || size3 == 0)
		{
			ptr = NULL;
		}
		else
		{
			ptr = new T**[size1];
			for (int i = 0; i < size1; i++)
			{
				ptr[i] = new T*[size2];
				for (int j = 0; j < size2; j++)
				{
					ptr[i][j] = new T[size3];
				}
			}
		}
	}
	~CArray3D()
	{
		if (ptr)
		{
			for (int i = 0; i < size1; i++)
			{
				for (int j = 0; j < size2; j++)
				{
					delete[] ptr[i][j];
				}
				delete[] ptr[i];
			}
			delete ptr;
		}
	}
	T** operator[](int i) { return ptr[i]; }
};

int main()
{
	CArray3D<int> a(3, 4, 5);
	int No = 0;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 4; ++j)
			for (int k = 0; k < 5; ++k)
				a[i][j][k] = No++;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 4; ++j)
			for (int k = 0; k < 5; ++k)
				cout << a[i][j][k] << ",";
	return 0;
}