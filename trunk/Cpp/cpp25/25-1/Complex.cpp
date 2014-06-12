
template <class T>
Complex<T> Complex<T>::operator+(const Complex<T>& z)
{
	Complex<T> tmp;
	tmp.mR = mR + z.mR;
	tmp.mI = mI + z.mI;

	return tmp;
}

template <class T>
Complex<T> Complex<T>::operator-(const Complex<T>& z)
{
	Complex<T> tmp;
	tmp.mR = mR - z.mR;
	tmp.mI = mI - z.mI;

	return tmp;
}

template <class T>
Complex<T> Complex<T>::operator*(const Complex<T>& z)
{
	Complex<T> tmp;
	tmp.mR = mR*z.mR - mI*z.mI;
	tmp.mI = mR*z.mI + mI*z.mR;

	return tmp;
}

template <class T>
Complex<T> Complex<T>::operator/(const Complex<T>& z)
{
	if (!z.mR  && !z.mI) exit(1);

	Complex<T> tmp;
	T denominator = (squared(z.mR) + squared(z.mI));
	tmp.mR = (mR*z.mR + mI*z.mI) / denominator;
	tmp.mI = (mI*z.mR - mR*z.mI) / denominator;

	return tmp;
}

template <class T>
bool Complex<T>::operator==(const Complex<T>& z) const
{
	if (mR == z.mR && mI == z.mI) return true;

	return false;
}

template <class T>
Complex<T> pow(const Complex<T>& z, const int exponent)
{
	Complex<T> product;
	if (exponent == 0)
	{
		product.mR = 1;
		product.mI = 0;

		return product;
	}

	product = z;
	for (auto i = 1; i < exponent; ++i)
	{
		product = product*z;
	}

	return product;
}