#ifndef ZP_STRING_UTIL
#define ZP_STRING_UTIL

#include "ZPDependency.h"

#		ifdef ZP_UNICODE
#			define String  StringW
#		else
#			define String  StringA
#		endif 

	namespace ZPUTIL
	{
		 const int INIT_STRING_LENGTH = 16;	 
		 const int STRING_LEN_INC = 1;

		 /**
			@brief 计算字符串str字符长度
			@return 返回字符串长度
		 */
		 template<typename T>
		inline int StrLenT( const T* str )
		 {
			 if( NULL == str )
			 {
				 return 0;
			 }

			 const T* p = str;
			 int str_len = 0;
			 while( 0 != (*p) )
			 { 
				 str_len++; 
				 p++; 
			 }
			 return str_len;
		 }

		 /**
			@brief 所指定字符是否为空白字符
			@param c 所要检测的字符
			@return 返回是否为空白字符
			@retval true 是空白字符
			@retval false 不是空白字符
		 */
		 template<typename T>
		 inline bool IsWhiteChar( const T c )
		 {
			 if(  c == 0x09 
				 || c == 0x0A
				 || c == 0x0D
				 || c == 0x20
				 )
			 {
				 return true;
			 }
			 return false;
		 }

		 /**
			@brief 所指定字符是否为英文字符
			@param c 所要检测的字符
			@return 返回是否为英文字符
			@retval true 是英文字符
			@retval false 不是英文字符
		 */
		 template<typename T>
		 inline bool IsAlpha( const T c )
		 {
			 if(  
				  ( c >= 'A' && c <= 'Z' ) ||
				  ( c >= 'a' && c <= 'z' )
				 )
			 {
				 return true;
			 }
			 return false;
		 }

		template<typename T>
		class StringT
		{
		public:

			typedef T XCHAR;

			/**
				@brief 默认构造函数
			*/
			StringT():
			  m_str_buf(NULL),
			  m_len(0),
			  m_capacity(0)
			{
				Assign( INIT_STRING_LENGTH );
			}
			
			
			StringT( const T* str ):
				m_str_buf(NULL),
				m_len(0),
				m_capacity(0)
			{
				this->operator=( str );
			}
			  
			/**
				@brief 拷贝构造函数
			*/
			StringT( const StringT& str ):
			m_str_buf(NULL),
			m_len(0),
			m_capacity(0)
			{
				this->operator=( str );
			}

			/**
				@brief 析构函数
			*/
			~StringT()
			{
				this->Destroy();
			}

			/**
				@brief 根据所需字符串长度调整缓冲区大小
				@param len 要申请的字符串空间大小，此函数会根据申请大小再多加上一部分空间以避免频繁的申请
				@return void
			*/
			inline void Assign( const int len )
			{
				//若所申请的字符串长度空间非法或
				//申请长度缓冲区大小已经满足则直接
				//返回
				if(  len < m_capacity )
				{
					return;
				}
				
				T* lp_old_buf = m_str_buf;
				if( len >= m_capacity )
				{
					m_str_buf = NULL;
					m_capacity = len+STRING_LEN_INC; 
					ZP_SAFE_NEW_BUFFER( m_str_buf , T , m_capacity );
					memset( m_str_buf , 0 , sizeof(T)*m_capacity );
				}

				if( NULL != lp_old_buf )
				{
					memcpy( m_str_buf , lp_old_buf , sizeof(T)*m_len );
					ZP_SAFE_DELETE_BUFFER( lp_old_buf );
				}
			}

			/**
				@brief 返回字符串长度
				@return 返回字符串长度
			*/
			inline int Length(void) const { return m_len; }
			/**
				@brief 返回字符串缓冲区所能容纳的字符数
				@return 返回字符串缓冲区所能容纳的字符数
			*/
			inline int Capacity(void) const { return m_capacity; }

			/**
				@brief 返回当前字符串是否为空
				@return bool
				@retval false 当字符串不为空时
				@retval true 当字符串为空时
			*/
			inline bool IsEmpty(void) const { return ( 0 == m_len ); }

			/**
				@brief 返回索引处的字符
				@param i 索引值( 必须在 0 到 Length() 之间 )
				@return T& 
			*/
			inline T& At( const int i ) 
			{
				ZP_ASSERT( i >= 0 && i < Length() );
				return m_str_buf[i];
			}

			/**
				@brief 返回索引处的字符
				@param i 索引值( 必须在 0 到 Length() 之间 )
				@return const T& 
			*/
			inline const T& At( const int i ) const 
			{
				ZP_ASSERT( i >= 0 && i < Length() );
				return m_str_buf[i];
			}
			 

			/**
				@brief 删除字符串中指定范围内的子字符串
				@param i 索引值指定从什么地方开始删除 ( 必须在 0 <= i < Length() 之间 )
				@param len 从 i 处往后包括第i个字节删除多长的字符串
				@return int 返回删除后的新串的字符数
			*/
			inline int Delete( const int i , const int len )
			{
				if( i < 0 || i >= Length() )
				{
					return Length();
				}

				if( len <= 0 )
				{
					return Length();
				}

				if( len <= Length() - i )
				{
					T* p = &m_str_buf[i];
					T* q = &m_str_buf[i+len];
					while( *(p++) = *(q++) ){} 
					m_len -= len;
				} 
				return Length();
			}

			/**
				@brief 在 i 处之前插入 str 字符串
				@param str 要插入的字符串
				@param i 索引值( 必须在 0 <= i <= Length() 之间 ) 
				@return StringT& 返回插入后的字符串
			*/
			inline StringT& Insert( const StringT& str , const int i )
			{
				if( i < 0 || i > Length() )
				{
					return *this;
				}

				if( str.IsEmpty() )
				{
					return *this;
				} 

				Assign( Length() + str.Length() );
				
				int pos = Length();
				int offset = str.Length();
				
				while( pos > i-1 )
				{
					m_str_buf[pos+offset] = m_str_buf[pos];
					pos--;
				}

				memcpy( &m_str_buf[i] , str.m_str_buf , sizeof(T)*str.Length() );
				m_len += str.Length();
				m_str_buf[m_len] = 0;
				return *this;
			}

			/**
				@brief 传入字符串与当前字符串比较
				@param str 传入字符串
				@param lowercast 是否转换至小写比较(当此至为true时为大小写不敏感默认为false)
				@return 比较结果
				@retval -1 当前字符串小于传入字符串
				@retval 0   当前字符串等于传入字符串
				@retval 1   当前字符串大于传入字符串
			*/
			inline int Compare( const StringT& str , const bool lowercast = false ) const
			{
				//若两个字符串都为空 则判定两个字符串相等
				if( this->IsEmpty() && str.IsEmpty() )
					return 0;
				//一个为空一个不为空情形
				if( this->IsEmpty() )
				{
					return -1;
				}else if( str.IsEmpty() ){
					return 1;
				}

				//若两个字符串都不为空
				const T* p = m_str_buf;
				const T* q = str.m_str_buf;
				int ret = 0;
				while( 1 )
				{
					T c1 = *p;
					T c2 = *q;

					//是否执行大小写不敏感比较
					if( lowercast )
					{ //若字符为大写则转换为小写再进行比较
							if( (*p) >= 'A' && (*p) <= 'Z' )
							{
								c1 += 0x20;
							}
							if( (*q) >= 'A' && (*q) <= 'Z' )
							{
								c2 += 0x20;
							} 
					}

					if( ( ret = ( c1 - c2 ) ) || !c2 )
					{
						break;
					}

					p++;
					q++;
				}

				if( ret < 0 ) 
				{
					return -1;
				}else if( ret > 0 ){
					return 1;
				}
				return ret;
			}

			/**
				@brief 传入字符串与当前字符串比较（忽略大小写）
				@param str 传入字符串 
				@return 比较结果
				@retval -1 当前字符串小于传入字符串
				@retval 0   当前字符串等于传入字符串
				@retval 1   当前字符串大于传入字符串
			*/
			inline int ICmp( const StringT& str ) const
			{
				return Compare( str , true );
			}

			/**
				@brief 找到本字符串中 start_pos位置处开始第一次出现c字符的位置
				@param c 要查找的字符
				@param start_pos 开始查找的位置（以0开始的索引值）
				@return int
				@retval -1 未找到所指定字符串
				@retval 0 ~ Length()-1 本字符串中含有c并返回第一个字符的位置
			*/
			inline int Find( const T c , const int start_pos )
			{ 
				//start_pos 位置越界，则直接返回查找失败
				if( start_pos < 0 || start_pos >= Length() )
				{
					return -1;
				}

				int pos = start_pos; 
				while( 1 <= ( this->Length() - pos ) )
				{ 
					if( c == At( pos ) )
					{
						return pos;
					}
					pos++;
				}//while

				return -1;
			}


			/**
				@brief 找到本字符串中 start_pos位置处开始第一次出现str的位置
				@param str 要查找的字符串
				@param start_pos 开始查找的位置（以0开始的索引值）
				@return int
				@retval -1 未找到所指定字符串
				@retval 0 ~ Length()-1 本字符串中含有str并返回第一个字符的位置
			*/
			inline int Find( const StringT& str , const int start_pos )
			{
				//若字符串为空则直接返回
				if( str.IsEmpty() )
				{
					return -1;
				} 

				//start_pos 位置越界，则直接返回查找失败
				if( start_pos < 0 || start_pos >= Length() )
				{
					return -1;
				}

				int pos = start_pos;

				while( str.Length() <= ( this->Length() - pos ) )
				{
					int pos_copy = pos;
					int find_str_offset = 0;

					while( 
						find_str_offset < str.Length() 
						&& ( str.At(find_str_offset) == At(pos) ) 
						)
					{
						find_str_offset++;
						pos++;
					}
					
					if( find_str_offset < str.Length() )
					{
						pos = pos_copy+1;
					}else{ //已在当前字符串中找到所指定字符串
						pos = pos_copy;
						return pos;
					} 
				}// while

				//未找到要找的字符串
				return -1;
			} 


			/**
				@brief 找到本字符串中 start_pos位置处开始第一次出现str的位置
				@param str 要查找的字符串
				@param start_pos 开始查找的位置（以0开始的索引值）
				@return int
				@retval -1 未找到所指定字符串
				@retval 0 ~ Length()-1 本字符串中含有str并返回第一个字符的位置
			*/
			inline int Find( const T* str , const int start_pos  )
			{
				return this->Find( StringT( str ) , start_pos );
			} 

			/**
				@brief 返回本字符串 从第i个字符开始的长达len的子字符串
				@param i 子串在当前字符串的起始位置( 以0开始的索引 )
				@param len  要提取的子串长度
				@return StringT 子字符串 
				@retval 空串				  当截取子串失败时返回
				@retval 正常的字符串  截取子串成功时返回
			*/
			inline StringT SubString( const int i , const int len ) const
			{
				StringT ret;

				//长度参数有误则返回空串
				if( len <= 0 )
				{
					return ret;
				}

				//所起始位置范围错误则返回空串
				if( i < 0 || i >= Length() )
				{
					return ret;
				}

				//子串截取超出范围则返回空串
				if( i + len > Length() )
				{
					return ret;
				}

				ret.Assign( len );
				memcpy( 
					reinterpret_cast<void*>( ret.m_str_buf ) , 
					reinterpret_cast<void*>( &m_str_buf[i] ) , 
					sizeof(T)*len 
					); 
				ret.m_str_buf[len] = 0;
				ret.m_len = len;

				return ret;
			}

			/**
				@brief 返回字符串缓冲区指针
			*/
			inline T* Ptr(void){ return m_str_buf; }
			/**
				@brief 返回字符串缓冲区指针
			*/
			inline const T* Ptr(void) const { return m_str_buf; }
			 

			/**
				@brief 清空字符串
				@return void 
			*/
			inline void Empty(void) 
			{ 
				m_len = 0;
				if( NULL != m_str_buf )
				{
					m_str_buf[0] = 0;
				}
			}

			/**
			* @brief 将字符串从大写转换为小写
			* @return void
			*/
			inline void ConvertToLowercast( void )
			{
				//若为空则直接返回
				if( IsEmpty() )
				{
					return;
				}

				for( int i = 0 ; i < m_len ; i++ )
				{
					if( ( m_str_buf[i] >= 'A' && m_str_buf[i] <= 'Z' ) )
					{
						m_str_buf[i] += 0x20;
					}
				}  
			}


			/**
				@brief 在字符串尾部附加字符串
				@param str 要附加在当前字符串末尾的字符串
				@return String& 附加后的字符串引用
			*/
			inline StringT& Append( const StringT& str  )
			{
				if( str.IsEmpty() )
				{
					return *this;
				}

				Assign( Length() + str.Length() ); 
				memcpy( 
								reinterpret_cast<void*>( &m_str_buf[m_len] ) , 
								reinterpret_cast<void*>( str.m_str_buf ) ,
								sizeof(T)*str.Length() 
							);
				m_len += str.Length();
				m_str_buf[m_len] = 0;
				return *this;
			}

			/**
				@brief 在字符串尾部附加字符
				@param c 要附加在当前字符串末尾的字符
				@return String&	附加后的字符串引用
			*/
			inline StringT& Append( const T c  )
			{ 
				Assign( Length() + 1 ); 
				m_str_buf[m_len] = c; 
				m_str_buf[m_len+1] = 0;
				m_len ++; 
				return *this;
			} 

			/**
				@brief 清除左侧与右侧的所有空白字符 
				@return String&	清除后的当前字符串
			*/
			inline StringT& Trim(void)
			{
				return TrimLeft().TrimRight();
			}

			/**
				@brief 清除左侧所有空格 
				@return String&	清除后的当前字符串
			*/
			inline StringT& TrimLeft(void)
			{
				if( IsEmpty() )
				{
					return *this;
				}

				int start_pos = 0;
				int len = 0;
				while( 
					IsWhiteChar( m_str_buf[len] )
					)
				{
					len++;
				}

				if( len > 0 )
				{
					Delete( start_pos , len );
				}
				return *this;
			}

			/**
				@brief 清除右侧所有空格 
				@return String&	清除后的所有字符串
			*/
			inline StringT& TrimRight(void)
			{
				if( IsEmpty() )
				{
					return *this;
				}

				int start_pos = Length()-1;
				int len = 0;

				while(  
					IsWhiteChar( m_str_buf[start_pos] ) 
					)
				{
					start_pos--;
					len++;
				}

				if( len > 0 )
				{
					Delete( start_pos+1 , len );
				}
				return *this;
			} 

			/**
				@brief 清除字符串中的所有空白字符
				@return String&	清除后的当前字符串
			*/
			inline StringT& ClearAllWhiteChars(void)
			{
				if( IsEmpty() )
				{
					return *this;
				}

				int final_pos = 0;  
				for( int pos = 0 ; pos < Length() ; pos++ )
				{
					 if(  !IsWhiteChar( m_str_buf[pos] )  )
					 {
						 m_str_buf[final_pos++] = m_str_buf[pos]; 
					 }
				}

				m_str_buf[final_pos] = 0;
				m_len = final_pos;
				return *this;
			}
			
			/**
				@brief 替换字符串中的以start_pos 起始处往后所有的str字符串，将其替换为replace_str
				@param str 要查找替换的字符串
				@param replace_str 替换的字符串
				@param start_pos 搜索点
				@return String& 最终替换完成的字符串
			*/
			inline StringT& Replace( const StringT& str , const StringT& replace_str , const int start_pos )
			{
				if( IsEmpty() )
				{
					return *this;
				}

				if( str.IsEmpty() )
				{
					return *this;
				}

				int pos = start_pos; 
				while( -1 != ( pos = Find( str , pos ) ) )
				{
					 Delete( pos , str.Length() );
					 Insert( replace_str , pos );
					 pos += replace_str.Length();
				}

				return *this;
			}

			/**
				@brief 销毁字符串  
			*/
			inline void Destroy(void)
			{
				ZP_SAFE_DELETE_BUFFER( m_str_buf );
				m_len = 0;
				m_capacity = 0;
			}
			 
			/**
				@brief 判断相等运算符重载
			*/
			inline bool operator==( const StringT& rhs ) const
			{
				return ( this->Compare( rhs ) == 0 );
			} 

			/**
				@brief 判断不相等运算符重载
			*/
			inline bool operator!=( const StringT& rhs ) const
			{
				return !( this->operator==( rhs ) );
			}

			/**
				@brief +=运算符重载，在当前字符串末尾附加字符串
			*/
			inline StringT& operator+=( const StringT& rhs )
			{
				return this->Append( rhs );
			} 

			/**
				@brief +=运算符重载，在当前字符串末尾附加字符串
			*/
			inline StringT& operator+=( const T* rhs )
			{
				return this->Append( StringT( rhs ) );
			}

			/**
				@brief +=运算符重载，在当前字符串末尾附加字符
			*/
			inline StringT& operator+=( const T c )
			{
				return this->Append( c );
			}

			/**
				@brief 重载赋值运算符
			*/
			inline StringT& operator=( const StringT& rhs )
			{
				if( rhs.IsEmpty() )
				{
					this->Destroy();
					return *this;
				}

				Assign( rhs.Length() );
				memcpy( m_str_buf , rhs.m_str_buf , sizeof(T)*rhs.Length() );
				m_len = rhs.Length();
				m_str_buf[m_len] = 0;
				return *this;
			}

			/**
				@brief 重载赋值运算符
			*/
			inline StringT& operator=( const T* rhs )
			{
				if( NULL == rhs )
				{
					return *this;
				}
				 
				int str_len = StrLenT( rhs ); 
				if( str_len == 0 )
				{ 
					this->Destroy();
					return *this;
				}

				Assign( str_len );
				memcpy( m_str_buf , rhs , sizeof(T)*str_len );
				m_len = str_len;
				m_str_buf[m_len] = 0;
				return *this;
			}

			/**
				@brief 加法运算符重载
			*/
			inline StringT operator+( const StringT& rhs ) const 
			{
				StringT rs = *this;
				rs += rhs;
				return rs;
			}

		private:
			T* m_str_buf;	///>字符串缓冲区
			int m_len;			///>字符串长度（以字符数为单位）
			int m_capacity;	///>字符串缓冲区容量（以字符数为单位）
		}; 

		template<typename T>
		std::ostream& operator<<( std::ostream& o , const StringT<T>& str )
		{
			if( NULL != str.Ptr() )
			{
				o<<str.Ptr();
			}
			return o;
		}

		typedef StringT<char> StringA;	///>		短字符版字符串
		typedef StringT<wchar_t> StringW;	///> 宽字符版字符串



	}//namespace ZPUTIL

#endif //ZP_STRING_UTIL

