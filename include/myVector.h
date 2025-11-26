#ifndef ESHEADER_H
#define ESHEADER_H

#include <initializer_list>

template <typename T>
class myVector{
	public:
		explicit myVector();
		myVector( std::initializer_list<T> list );
		myVector( const myVector<T> &v );
		explicit myVector( int size );
		myVector( myVector<T> &&v );
		
		void push_back( T elem );
		T pop_back();
		void reserve( int size );
		T at( int pos ) const;
		T& operator[]( int idx );
		myVector<T>& operator=( myVector<T> &v );
		myVector<T>& operator=( myVector<T> &&v );
		const T& operator[]( int idx) const;
		
		int size() const;
		int capacity() const;
		
		~myVector();

	private:
		int n = -1;
		int max_size = 0;
		T *elem = nullptr;
};

#include "../src/myVector.hpp"

#endif