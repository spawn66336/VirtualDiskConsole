#ifndef ZP_VECTOR
#define ZP_VECTOR

namespace Util
{
	const int INIT_VECTOR_ELEM_COUNT = 32;
	const int VECTOR_ELEM_COUNT_INC = 16;

	template<typename T>
	class VectorT
	{
	public:
		VectorT();
		VectorT( const VectorT& v );
		~VectorT();

		/**
		* @brief 为需要存的元素调整分配空间
		* @param elem_count 需要存入的元素
		*/
		void Assign( const int elem_count );
		
		/**
		* @brief 在向量尾部附加元素 elem 
		* @param elem 要附加的元素
		*/
		void PushBack( const T elem );

		/**
		* @brief 在向量头部附加元素 elem 
		* @param elem 要附加的元素
		*/
		void PushFront( const T elem );

		/**
		* @brief 在索引位置i处插入元素elem
		* @param i 要插入的索引
		* @param elem 要插入的元素
		*/
		void Insert( const int i , const T elem );

		/**
		* @brief 删除i处的元素
		* @param i 要删除元素的索引
		*/
		void DeleteAt( const int i );

		/**
		* @brief 获取i处的元素
		* @param i 索引
		*/
		T& At( const int i );

		/**
		* @brief 获取i处的元素
		* @param i 索引
		*/
		const T& At( const int i ) const;

		/**
		* @brief 清空向量中的数据
		*/
		void Clear(void);

		/**
		* @brief 向量中存放的元素数
		* @return 返回向量存放的元素数
		*/
		int Count(void) const;

		/**
		* @brief 返回向量能容纳的元素数
		* @return 返回向量能容纳的元素数
		*/
		int Capacity(void) const;

		/**
		* @brief 赋值运算符重载
		*/
		VectorT& operator=( const VectorT& rhs );
		 
	private:

		T* m_buf;			///>向量的数据缓冲区
		int m_count;		///>向量中的元素数
		int m_capacity;	///>向量中的空间能容纳多少元素 
	};

	 
	  
	template<typename T>
	Util::VectorT<T>::VectorT():
	m_buf(NULL),
	m_count(0),
	m_capacity(0)
	{
		Assign( INIT_VECTOR_ELEM_COUNT );
	}

	template<typename T>
	Util::VectorT<T>::VectorT( const VectorT& v ):
	m_buf(NULL),
	m_count(0),
	m_capacity(0)
	{
		this->operator=( v );
	}

	template<typename T>
	Util::VectorT<T>::~VectorT()
	{
		ZP_SAFE_DELETE_BUFFER( m_buf );
		m_count = 0;
		m_capacity = 0;
	}
	
	template<typename T>
	void Util::VectorT<T>::Assign( const int elem_count )
	{
		//若容器内的元素数满足所需要求则不分配
		if( elem_count <= 0 || 
			elem_count <= m_capacity )
		{
			return;
		}

		//计算最终容量
		const int final_capacity = elem_count + VECTOR_ELEM_COUNT_INC;
		T* new_buf = NULL;
		ZP_SAFE_NEW_BUFFER( new_buf , T , final_capacity );
		ZP_ASSERT( NULL != new_buf );

		if( NULL != m_buf )
		{
			for( int i = 0 ; i < m_count ; i++ )
			{
				new_buf[i] = m_buf[i];
			}
			ZP_SAFE_DELETE_BUFFER( m_buf );
		}

		m_buf = new_buf;
		m_capacity = final_capacity;
	}

	template<typename T>
	void Util::VectorT<T>::PushFront( const T elem )
	{
		Assign( Count() + 1 );

		for( int i = m_count ; i > 0 ; i-- )
		{
			m_buf[i] = m_buf[i-1];
		}
		m_buf[0] = elem;
		m_count++;
	}

	template<typename T>
	void Util::VectorT<T>::PushBack( const T elem )
	{
		Assign( Count() + 1 );
		m_buf[ m_count++ ] = elem; 
	}

	template<typename T>
	void Util::VectorT<T>::DeleteAt( const int i )
	{
		if( i < 0 || i >= Count() )
		{
			return;
		}

		for( int j =  i ; j < Count()-1 ; j++ )
		{
			m_buf[j] = m_buf[j+1];
		}
		m_count--;
	}

	template<typename T>
	void Util::VectorT<T>::Insert( const int i , const T elem )
	{
		if( i < 0 || i > Count() )
		{
			return;
		}
		Assign( Count() + 1 );
		for( int j = m_count ; j > i ; j-- )
		{
			m_buf[j] = m_buf[j-1];
		}
		m_buf[i] = elem;
		m_count++;
	}


	template<typename T>
	T& Util::VectorT<T>::At( const int i )
	{
		ZP_ASSERT( i < 0 || i >= m_count );
		return m_buf[i];
	}

	template<typename T>
	const T& Util::VectorT<T>::At( const int i ) const
	{
		ZP_ASSERT( i < 0 || i >= m_count );
		return m_buf[i];
	}


	template<typename T>
	void Util::VectorT<T>::Clear( void )
	{
		m_count = 0;
	}

	template<typename T>
	int Util::VectorT<T>::Capacity( void ) const
	{
		return m_capacity;
	}

	template<typename T>
	int Util::VectorT<T>::Count( void ) const
	{
		return m_count;
	}


	template<typename T>
	VectorT<T>& Util::VectorT<T>::operator=( const VectorT<T>& rhs )
	{
		Assign( rhs.Count() );

		for( int i = 0 ; i < rhs.Count() ; i++ )
		{
			m_buf[i] = rhs.m_buf[i];
		}
		m_count = rhs.m_count;

		return *this;
	}


}//namespace ZPUTIL

#endif //ZP_VECTOR