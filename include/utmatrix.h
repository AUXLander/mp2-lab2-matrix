// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
	ValType *pVector;
	int Size;       // размер вектора
	int StartIndex; // индекс первого элемента вектора
public:
	TVector(int s = 10, int si = 0);
	TVector(const TVector &v);                // конструктор копирования
	~TVector();
	int GetSize() { return Size; } // размер вектора
	int GetStartIndex() { return StartIndex; } // индекс первого элемента
	ValType& operator[](int pos);             // доступ
	bool operator==(const TVector &v) const;  // сравнение
	bool operator!=(const TVector &v) const;  // сравнение
	TVector& operator=(const TVector &v);     // присваивание

	// скалярные операции
	TVector  operator+(const ValType &val);   // прибавить скаляр
	TVector  operator-(const ValType &val);   // вычесть скаляр
	TVector  operator*(const ValType &val);   // умножить на скаляр

	// векторные операции
	TVector  operator+(const TVector &v);     // сложение
	TVector  operator-(const TVector &v);     // вычитание
	ValType  operator*(const TVector &v);     // скалярное произведение

	// ввод-вывод
	friend istream& operator>>(istream &in, TVector &v)
	{
		for (int i = 0; i < v.Size; i++)
			in >> v.pVector[i];
		return in;
	}
	friend ostream& operator<<(ostream &out, const TVector &v)
	{
		for (int i = 0; i < v.Size; i++)
			out << v.pVector[i] << ' ';
		return out;
	}
};

//Задаем размер, который нужен в матрице и элемент с которого будет отсчет
template <class ValType>
TVector<ValType>::TVector(int s, int si) : Size(s), StartIndex(si) {
	if (s <= 0 || s > MAX_VECTOR_SIZE) {
		throw "Out of range";
	}
	if (StartIndex < 0 || StartIndex >= Size) {
		throw "Wrong indexation";
	}

	Size = Size - StartIndex;
	pVector = new ValType[Size];

	for (size_t i = 0; i < Size; i++) {
		pVector[i] = {};
	}
}

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v) : Size(v.Size), StartIndex(v.StartIndex) {
	pVector = new ValType[Size];

	for (size_t i = 0; i < Size; i++) {
		pVector[i] = v.pVector[i];
	}
}

template <class ValType>
TVector<ValType>::~TVector() {
	delete[] pVector;
}

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos) {
	pos -= StartIndex;

	if (pos < 0 || pos > Size) {
		throw "Wrong indexation";
	}

	return pVector[pos];
}

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const {
	if (Size == v.Size && StartIndex == v.StartIndex) {
		for (size_t i = 0; i < Size; i++) {
			if (pVector[i] != v.pVector[i]) {

				return false;
			}
		}

		return true;
	}

	return false;
}

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const {
	return !(*this == v);
}

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v) {
	if (this->Size != v.Size || this->StartIndex != v.StartIndex) {
		delete[] pVector;

		Size = v.Size;
		StartIndex = v.StartIndex;

		pVector = new ValType[Size];
	}

	for (size_t i = 0; i < Size; i++) {
		pVector[i] = v.pVector[i];
	}

	return  *this;
}

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val) {

	TVector<ValType> temp(Size);

	for (size_t i = 0; i < Size; i++) {
		temp.pVector[i] = pVector[i] + val;
	}

	return temp;
}

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val) {

	TVector<ValType> temp(Size);

	for (size_t i = 0; i < Size; i++) {
		temp.pVector[i] = pVector[i] - val;
	}

	return temp;
}

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val) {

	TVector<ValType> temp(Size);

	for (size_t i = 0; i < Size; i++) {
		temp.pVector[i] = pVector[i] * val;
	}

	return temp;
}

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v) {
	if (Size != v.Size) {
		throw "Incomparable data size";
	}

	TVector<ValType> temp(Size);

	for (size_t i = 0; i < Size; i++) {
		temp.pVector[i] = pVector[i] + v.pVector[i];
	}

	return temp;
}

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v) {
	if (Size != v.Size) {
		throw "Incomparable data size";
	}

	TVector<ValType> temp(Size);

	for (size_t i = 0; i < Size; i++) {
		temp.pVector[i] = pVector[i] - v.pVector[i];
	}

	return temp;
}

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v) {
	if (Size != v.Size) {
		throw "Incomparable data size";
	}

	ValType temp = 0;

	for (size_t i = 0; i < Size; i++) {
		temp += pVector[i] * v.pVector[i];
	}

	return temp;
}


template <class ValType>
class TMatrix : public TVector<TVector<ValType>>{
public:
	TMatrix(int s = 10);
	TMatrix(const TMatrix &mt); // копирование 
	TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа 
	bool operator==(const TMatrix &mt) const; // сравнение 
	bool operator!=(const TMatrix &mt) const; // сравнение 
	TMatrix& operator= (const TMatrix &mt); // присваивание 
	TMatrix operator+ (const TMatrix &mt); // сложение 
	TMatrix operator- (const TMatrix &mt); // вычитание 
	// ввод / вывод 
	friend istream& operator>>(istream &in, TMatrix &mt){
		for (size_t i = 0; i < mt.Size; i++) {
			in >> mt.pVector[i];
		}
		return in;
	}
	friend ostream & operator<<(ostream &out, const TMatrix &mt){
		for (size_t i = mt.Size - 1; i >0 ; i--){
			//out << endl;
			//printf("%d ", t);
			out << mt.pVector[i] << " " << endl;
		}
		out << endl;
		return out;
	}
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s){
	if (s > 0 && s <= MAX_MATRIX_SIZE){

		Size = s;

		for (size_t i = 0; i < s; i++){
			TVector<ValType> temp(s, i);
			pVector[i] = temp;
		}
	}
	else {
		throw "Do not exceed range of definition";
	}
}

template <class ValType> // конструктор копирования 
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt) : TVector<TVector<ValType>>(mt){
	pVector = new TVector<ValType>[mt.Size];

	Size = mt.Size;
	StartIndex = mt.StartIndex;

	for (int i = 0; i < mt.Size; i++) {
		pVector[i] = mt.pVector[i];
	}
}

template <class ValType> // конструктор преобразования типа 
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt) : TVector<TVector<ValType> >(mt){}

template <class ValType> // сравнение 
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const {
	if (Size == mt.Size){
		for (size_t i = 0; i < Size; i++){
			if (pVector[i] != mt.pVector[i]) {

				return false;
			}
		}

		return true;
	}

	return false;
}

template <class ValType> // сравнение 
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const {
	return !(*this == mt);
}

template <class ValType> // присваивание 
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt) {
	if (Size != mt.Size){
		delete[] pVector;
		pVector = new TVector<ValType>[mt.Size];
	}

	Size = mt.Size;
	StartIndex = mt.StartIndex;

	for (size_t i = 0; i < Size; i++){
		pVector[i] = mt.pVector[i];
	}

	return *this;
}

template <class ValType> // сложение 
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt) {
	if (Size == mt.Size){

		TMatrix temp(Size);
		for (size_t i = 0; i < mt.Size; i++){
			temp.pVector[i] = pVector[i] + mt.pVector[i];
		}

		return temp;
	}
	else {
		throw "Vectors size are not equal";
	}
}

template <class ValType> // вычитание 
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt) {
	if (Size == mt.Size){

		TMatrix temp(Size);
		for (size_t i = 0; i < mt.Size; i++){
			temp.pVector[i] = pVector[i] - mt.pVector[i];
		}

		return temp;
	}
	else {
		throw "Vectors size are not equal";
	}
}
#endif