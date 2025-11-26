#ifndef ESHEADER_HPP
#define ESHEADER_HPP

#include "../include/myVector.h"
#include <algorithm>

template <typename T>
myVector<T>::myVector(){
	n = 0;
	max_size = 0;
	elem = new T[ 0 ];
}

template <typename T>
myVector<T>::myVector( std::initializer_list<T> list ){
	max_size = list.size();
	n = max_size;
	elem = new T[ max_size ];
	
	std::copy(list.begin(), list.end(), elem);
}

template <typename T>
myVector<T>::myVector( const myVector<T> &v ){
	n = v.size();
	max_size = v.capacity();
	elem = new T[ max_size ];
	
	std::copy( v.elem, v.elem + max_size, elem);
}

template <typename T>
myVector<T>::myVector( int size ){
	n = 0;
	max_size = size;
	elem = new T[ max_size ];
}

template <typename T>
myVector<T>::myVector( myVector<T> &&v ){
	n = v.size();
	max_size = v.capacity();
	elem = v.elem;
	
	v.elem = nullptr;
	v.max_size = 0;
	v.n = 0;
}

template <typename T>
myVector<T>::~myVector(){
	delete[] elem;
}

template <typename T>
int myVector<T>::size() const{
	return n;
}

template <typename T>
int myVector<T>::capacity() const{
	return max_size;
}


template <typename T>
T myVector<T>::at( int pos ) const{
	if ( pos < n && pos >= 0 ){
		return elem[ pos ];
	}
	
	throw 404;
}

template <typename T>
void myVector<T>::push_back( T val ){
	if( n >= max_size ){
		T *temp = new T[ max_size * 2 ];
		
		for( int i = 0; i < max_size; i ++ ){
			temp[ i ] = elem[ i ];
		}
		
		max_size *= 2;
		
		delete[] elem;
		elem = temp;
	}
	
	elem[ n ] = val;
	n++;
}

template <typename T>
T myVector<T>::pop_back(){
	if( n >= 0 ){
		n --;
		T temp = elem[ n ];
		
		return temp;
	}
	
	throw 404;
}

template <typename T>
void myVector<T>::reserve( int size ){
	if( size > max_size ){
		T *temp = new T[ size ];
		
		for( int i = 0; i < max_size; i ++ ){
			temp[ i ] = elem[ i ];
		}
		
		max_size = size;
		
		delete[] elem;
		elem = temp;
	}
}

template <typename T>
T& myVector<T>::operator[]( int idx ){
	return elem[ idx ];
}

template <typename T>
const T& myVector<T>::operator[]( int idx) const{
	return elem[ idx ];
}

template <typename T>
myVector<T>& myVector<T>::operator=( myVector<T> &v ){
	n = v.size();
	max_size = v.capacity();
	T *temp = new T[ max_size ];
	
	std::copy(v.elem, v.elem + max_size, temp);
	
	delete[] elem;
	elem = temp;
	
	return *this;
}

template <typename T>
myVector<T>& myVector<T>::operator=( myVector<T> &&v ){
	delete[] elem;
	
	elem = v.elem;
	n = v.n;
	max_size = v.max_size;
	
	v.elem = nullptr;
	v.n = 0;
	v.max_size = 0;
	
	return *this;
}


#endif





