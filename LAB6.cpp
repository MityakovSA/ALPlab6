#include <iostream>
#include <exception>
using namespace std;


template <typename T>
class Matrix
{
	T** _mas;
	int _m;
	int _n;

public:

	Matrix(int m, int n)
	{
		_mas = new T*[m];
		for (int i = 0; i < m; i++)
			_mas[i] = new T[n];
		_m = m;
		_n = n;
	}

	Matrix(T** mas, int m, int n)
	{
		_mas = new T*[m];
		for (int i = 0; i < m; i++)
			_mas[i] = new T[n];
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				_mas[i][j] = mas[i][j];
		_m = m;
		_n = n;
	}

	Matrix(Matrix<T> &M)
	{
		_m = M.getm();
		_n = M.getn();
		T** mas = M.getmas();
		_mas = new T*[_m];
		for (int i = 0; i < _m; i++)
			_mas[i] = new T[_n];
		for (int i = 0; i < _m; i++)
			for (int j = 0; j < _n; j++)
				_mas[i][j] = mas[i][j];
	}

	Matrix<T> operator%(Matrix<T> &M)
	{
		try
		{
			if (_m != M.getm()) throw logic_error("Invalid matrix!");
			int m = _m;
			int n = _n + M.getn();
			T** a = _mas;
			T** b = M.getmas();
			T** c = new T*[m];
			for (int i = 0; i < m; i++)
				c[i] = new T[n];
			for (int i = 0; i < m; i++)
				for (int j = 0; j < n; j++)
				{
					if (j < _n) c[i][j] = a[i][j];
					else c[i][j] = b[i][j - _n];
				}
			Matrix<T> R(c, m, n);
			for (int i = 0; i < m; i++)
				delete[] c[i];
			delete[] c;
			return R;
		}
		catch (exception error)
		{
			cout << error.what() << endl;
		}
	}

	Matrix<T> operator*(Matrix<T> &M)
	{
		try
		{
			if (_n != M.getm()) throw logic_error("Invalid matrix!");
			int m = _m;
			int n = _n;
			int q = M.getn();
			T** a = _mas;
			T** b = M.getmas();
			T** c = new T*[m];
			for (int i = 0; i < m; i++)
				c[i] = new T[q];
			for (int i = 0; i < m; i++)
				for (int j = 0; j < q; j++)
				{
					c[i][j] = 0;
					for (int k = 0; k < n; k++)
						c[i][j] += (a[i][k] * b[k][j]);
				}
			Matrix<T> R(c, m, q);
			for (int i = 0; i < m; i++)
				delete[] c[i];
			delete[] c;
			return R;
		}
		catch (exception error)
		{
			cout << error.what() << endl;
		}
	}

	int getm()
	{
		return _m;
	}

	int getn()
	{
		return _n;
	}

	T** getmas()
	{
		return _mas;
	}

	void print() const
	{
		for (int i = 0; i < _m; i++)
		{
			for (int j = 0; j < _n; j++)
				cout << _mas[i][j] << " ";
			cout << endl;
		}
	}

	//ITERATOR
	struct Iterator
	{
		T** mas_;
		int curi;
		int curj;
		int sizei;
		int sizej;
		Iterator(T** data, int i, int j, int ei, int ej) : mas_(data), curi(i), curj(j), sizei(ei), sizej(ej) {};
		Iterator& operator++()
		{ 
			if ((curi == (sizei - 1)) && (curj == (sizej - 1))) { curj++; return *this; }
			else if (curj == (sizej - 1)) { curi++; curj = 0; return *this; }
			else { curj++; return *this; }
		}
		T& operator*() { return mas_[curi][curj]; }
		T* operator->() { return &(mas_[curi][curj]); }
		bool operator==(const Iterator& other) { return ((curi == other.curi) && (curj == other.curj)); }
		bool operator!=(const Iterator& other) { return !(*this == other); }
	};
	//ITERATOR

	Iterator begin() { return Iterator(_mas, 0, 0, _m, _n); }
	Iterator end() { return Iterator(_mas, (_m - 1), _n, _m, _n); }

	~Matrix()
	{
		for (int i = 0; i < _m; i++)
			delete[] _mas[i];
		delete[] _mas;
	}
};


int main()
{
	Matrix<int>;
	int m, n, q;  // Матрицы MxN и NxQ
	setlocale(LC_ALL, "Russian");

	cout << "Введите количество строк матрицы А: ";
	cin >> m;
	cout << "Введите количество столбцов матрицы А: ";
	cin >> n;

	int** a = new int*[m];
	for (int i = 0; i < m; i++)
		a[i] = new int[n];

	cout << "Количесво строк матрицы В равно количеству столбцов матрицы А!" << endl;
	cout << "Введите количество столбцов матрицы B: ";
	cin >> q;

	int** b = new int*[n];
	for (int i = 0; i < n; i++)
		b[i] = new int[q];

	cout << "Введите матрицу А:" << endl;

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			cin >> a[i][j];
	Matrix<int> A(a, m, n);

	cout << "Введите матрицу B:" << endl;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < q; j++)
			cin >> b[i][j];
	Matrix<int> B(b, n, q);

	cout << endl;
	A.print();
	cout << endl;
	B.print();
	cout << endl;

	Matrix<int> C = (A * B);

	C.print();
	cout << endl;

	Matrix<int> D = (A % B);

	D.print();
	cout << endl;

	for (auto i = D.begin(); i != D.end(); ++i)
		cout << *i;
	cout << endl;

	for (int i = 0; i < m; i++)
		delete[] a[i];
	delete[] a;
	for (int i = 0; i < n; i++)
		delete[] b[i];
	delete[] b;
	system("pause");
	return 0;
}