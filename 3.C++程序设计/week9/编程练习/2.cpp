template<class T>
class CMyistream_iterator
{
private:
	T content;
	istream &is;
public:
	CMyistream_iterator(istream &i):is(i)
	{
		i >> content;
	}
	T operator*()
	{
		return content;
	}
	void operator++(int)
	{
		is >> content;
	}
};