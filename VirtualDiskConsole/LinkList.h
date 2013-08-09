#ifndef ZP_LINKLIST
#define ZP_LINKLIST

namespace Util
{
	 
	template<typename T>
	class LinkListT
	{
	public:
		 
			class LinkNode
			{
			protected:
				LinkNode(void):
					 m_lp_parent_list( NULL),
					 m_data(),
				     m_lp_prev( NULL ),
				     m_lp_next( NULL )
					 {
						 m_lp_prev = this;
						 m_lp_next = this;
					 }
			public:

				friend class LinkListT;

				/**
					@brief 带参数的构造函数
					@param lp_parent 所在链表
				*/
				LinkNode( LinkListT* lp_parent ):
				  m_lp_parent_list( lp_parent ),
					  m_data(),
					  m_lp_prev( NULL ),
					  m_lp_next( NULL )
				  {
					  m_lp_prev = this;
					  m_lp_next = this;
				  }

				 /**
					@brief 带参数的构造函数
					@param lp_parent 所在链表
					@param data 结点数据
				*/
				LinkNode( LinkListT* lp_parent , const T& data ):
				m_lp_parent_list( lp_parent ),
				m_data( data ),
				m_lp_prev( NULL ),
				m_lp_next( NULL )
				{
					m_lp_prev = this;
					m_lp_next = this;
				}

				~LinkNode(){} 

				inline LinkListT* ParentList(void)  { return m_lp_parent_list; }
				inline const LinkListT* ParentList(void) const { return m_lp_parent_list; }
				inline T& Data(void) { return m_data; }
				inline const T& Data(void) const { return m_data; }
				inline LinkNode* Prev(void) { return m_lp_prev; }
				inline LinkNode* Next(void) { return m_lp_next; }
				inline const LinkNode* Prev(void) const { return m_lp_prev; }
				inline const LinkNode* Next(void) const { return m_lp_next; }
	
				/**
					@brief 从当前结点前插入一个结点
					@param insert_node 指向要插入的结点
					@return 返回当前结点
				*/
				inline LinkNode* InsertFront( LinkNode* insert_node )
				{ 
					insert_node->m_lp_parent_list = this->ParentList();
					insert_node->m_lp_prev = Prev(); 
					insert_node->m_lp_next = this; 
					Prev()->m_lp_next = insert_node;
					m_lp_prev = insert_node;
					return this;
				}

				/**
					@brief 从当前结点后插入一个结点
					@param insert_node 指向要插入的结点
					@return 返回当前结点
				*/
				inline LinkNode* InsertBack( LinkNode* insert_node )
				{
					insert_node->m_lp_parent_list = this->ParentList();
					insert_node->m_lp_prev = this;
					insert_node->m_lp_next = Next();
					Next()->m_lp_prev = insert_node;
					m_lp_next = insert_node;
					return this;
				}

				/**
					@brief 将此结点从链表中摘除 
					@return 返回当前结点
				*/
				inline LinkNode* Remove(void)
				{
					m_lp_parent_list = NULL;
					Prev()->m_lp_next = Next();
					Next()->m_lp_prev = Prev();
					m_lp_prev = this;
					m_lp_next = this;
					return this;
				}

				/**
					@brief 清除自身  
				*/
				inline void DeleteThis(void)
				{
					delete this;
				}

			private:
				LinkListT* m_lp_parent_list;  ///>所在链表
				T m_data;							  ///>数据
				LinkNode* m_lp_prev;      ///>指向前一个结点的指针
				LinkNode* m_lp_next;      ///>指向后一个结点的指针
			};// LinkNode

	public: 

		/**
			@brief 默认构造函数
		*/
		LinkListT():
		  m_lp_head(NULL),
		  m_count(0)
		{
		} 

		 /**
			@brief 拷贝构造函数
		 */
		LinkListT( const LinkListT& list ):
			m_lp_head(NULL),
			m_count(0)
		{
			this->Clone( list );
		}

		 /**
			@brief 析构函数
		 */
		~LinkListT()
		{
			this->Clear();
		}

		/**
			@brief 返回头结点指针
			@retval NULL 若链表为空
		*/
		inline LinkNode* Head(void){ return m_lp_head; }

		/**
			@brief 返回头结点指针
			@retval NULL 若链表为空
		*/
		inline const LinkNode* Head(void) const{ return m_lp_head; }

		/**
			@brief 返回尾结点指针
			@retval NULL 若链表为空
		*/
		inline LinkNode* Tail(void)
		{
			if( m_lp_head )
			{
				return m_lp_head->Prev();
			}
			return m_lp_head;
		}

		/**
			@brief 返回尾结点指针
			@retval NULL 若链表为空
		*/
		inline const LinkNode* Tail(void) const
		{
			if( m_lp_head )
			{
				return m_lp_head->Prev();
			}
			return m_lp_head;
		} 

		/**
			@brief 返回链表中结点数
			@return 结点数
		*/
		inline int Count(void) const { return m_count; }

		inline T& Front(void)
		{
			ZP_ASSERT( NULL != m_lp_head );
			return m_lp_head->Data();
		}

		inline const T& Front(void) const 
		{
			ZP_ASSERT( NULL != m_lp_head );
			return m_lp_head->Data();
		}

		inline T& Back(void)
		{
			ZP_ASSERT( NULL != Tail() );
			return Tail()->Data();
		}

		inline const T& Back(void) const
		{
			ZP_ASSERT( NULL != Tail() );
			return Tail()->Data();
		}

		/**
			@brief 从前端插入一个以data为数据的结点
			@param data 要插入的数据
		*/
		inline void PushFront( const T& data )
		{
			LinkNode* lp_new_node = new LinkNode( this , data );
			ZP_ASSERT( NULL != lp_new_node );
			
			if( m_lp_head )
			{
				m_lp_head->InsertFront( lp_new_node );
			} 
			m_lp_head = lp_new_node; 
			m_count++;
		}

		/**
			@brief 从后端插入一个以data为数据的结点
			@param data 要插入的数据
		*/
		inline void PushBack( const T& data )
		{
			LinkNode* lp_new_node = new LinkNode( this , data );
			ZP_ASSERT( NULL != lp_new_node );

			if( m_lp_head )
			{
				m_lp_head->InsertFront( lp_new_node );
			}else{
				m_lp_head = lp_new_node;
			}
			m_count++;
		}

		/**
			@brief 销毁头部一个结点
		*/
		inline void PopFront( void )
		{
			if( m_lp_head )
			{
				Erase( m_lp_head );
			}
		}

		/**
			@brief 销毁尾部一个结点
		*/
		inline void PopBack( void )
		{
			if( m_lp_head )
			{
				Erase( m_lp_head->Prev() );
			}
		}
		 

		/**
			@brief 删除掉所指定的结点
			@param node 要删掉的结点(主要此结点必须为该链表上的结点)
			@return 删除结点的下一个结点
		*/
		inline LinkNode* Erase( LinkNode* node )
		{  
			ZP_ASSERT( NULL != node ); 
			//结点所属链表必须为当前链表，当前链表才有权移出
			ZP_ASSERT( node->ParentList() == this );
			
			LinkNode* lp_next_node = NULL; 
			if( m_lp_head == node )
			{//若删除的是头结点
				//若当前链表中不只有一个结点
				if( m_lp_head->Next() != m_lp_head )
				{
					m_lp_head = m_lp_head->Next();
					lp_next_node = m_lp_head;
				}else{
					m_lp_head = NULL; 
				}
			}else{//若删除的不是头结点 
				if( node != Tail() )
				{
					lp_next_node = node->Next();
				} 
			}
			 
			node->Remove()->DeleteThis();
			node = NULL;
			m_count--;

			return lp_next_node;
		}

		/**
		* @brief 获取在i处的元素
		*/
		inline T& At( const int i )
		{
			ZP_ASSERT( i >= 0 || i < Count() );   

			int count = 0;
			LinkNode* p = m_lp_head;
			while( count != i )
			{
				p = p->Next();
				count++;
			}

			return p->Data();
		}

		inline const T& At( const int i ) const
		{ 
			ZP_ASSERT( i >= 0 || i < Count() );   

			int count = 0;
			LinkNode* p = m_lp_head;
			while( count != i )
			{
				p = p->Next();
				count++;
			}

			return p->Data();
		}

		/**
			@brief 在位置i处插入数据 data
			@param i 要插入的位置
			@param data 要插入的数据
		*/
		inline void Insert( const int i , const T& data  )
		{
			ZP_ASSERT( i >= 0 || i <= Count() );   

			if( i == 0 )
			{
				PushFront( data );
				return;
			} else if ( i == Count() ) {
				PushBack( data );
				return;
			}

			int c = 0;
			LinkNode* lp_curr_node = m_lp_head;
			while( c != i )
			{
				lp_curr_node = lp_curr_node->Next();
				c++;
			}

			LinkNode* lp_new_node = new LinkNode( this , data );
			lp_curr_node->InsertFront( lp_new_node );  
			m_count++;
		}


		/**
			@brief 删除索引所指定的节点
			@param i 索引
		*/
		inline void DeleteAt( const int i )
		{
			ZP_ASSERT( i >= 0 || i < Count() ); 

			int c = 0;
			LinkNode* lp_del_node = m_lp_head;
			while( c != i )
			{
				lp_del_node = lp_del_node->Next();
				c++;
			}  

			Erase( lp_del_node );
		}
		
		/**
			@brief 返回链表是否为空
			@return 返回链表是否为空
			@retval true 为空
			@retval false 为非空
		*/
		inline bool IsEmpty(void) const { return ( m_count == 0 ); }

		/**
			@brief 清空链表中的所有结点
		*/
		inline void Clear(void)
		{
			if( NULL != Head() )
			{ 
				LinkNode* p = Head();
				LinkNode* end = Head();
				do{
					LinkNode* tmp = p->Next();
					p->DeleteThis();
					p = tmp;
				}while( p != end );

				m_lp_head = NULL;
				m_count = 0; 
			}//if( NULL != Head() )
		}

		/**
			@brief 拷贝另一个链表
			@param list 要拷贝的链表
			@return void
		*/
		inline void Clone( const LinkListT& list )
		{
			this->Clear();

			if( list.IsEmpty() )
			{
				return;
			}

			const LinkNode* p = list.Head();
			const LinkNode* end = list.Head();
			do{ 
				this->PushBack( p->Data() );
				p = p->Next();
			}while( p != end );

			m_count = list.Count();
		}

		/**
		* @brief 在当前链表处附加一个链表
		* @param list 要附加的链表
		*/
		inline LinkListT& Append( const LinkListT& list )
		{
			if( list.IsEmpty() )
			{
				return *this;
			}

			const LinkNode* p = list.Head();
			const LinkNode* end = list.Head();
			do{ 
				this->PushBack( p->Data() );
				p = p->Next();
			}while( p != end );

			return *this;
		}

		/**
			@brief 交换两个链表
			@param list 要交换的链表
			@return void
		*/
		inline void Swap( LinkListT& list )
		{
			LinkNode* lp_head_copy = m_lp_head;
			int count_copy = m_count;

			m_lp_head = list.m_lp_head;
			m_count = list.m_count;

			list.m_lp_head = lp_head_copy;
			list.m_count = count_copy;
		}

		/**
			@brief 赋值运算符重载
		*/
		inline LinkListT& operator=( const LinkListT& rhs )
		{
			this->Clone( rhs );
			return *this;
		}

		//链表迭代器 
		class Iterator
		{
		public:

			friend class LinkListT;

			Iterator():
			  m_list_ref( NULL ),
			  m_lp_curr_node(NULL)
			{ 
			}

			Iterator(  LinkListT* list ):
			  m_list_ref( list ),
			  m_lp_curr_node(NULL)
			{
				m_lp_curr_node = m_list_ref->Head();
			}

			 Iterator( LinkListT* list , LinkNode* node ):
				m_list_ref( list ),
				m_lp_curr_node(node)
			{ 
			}

			Iterator( const Iterator& it ):
				m_list_ref( it.m_list_ref ),
				m_lp_curr_node( it.m_lp_curr_node )
			{ 
			}
            
			~Iterator(){ m_list_ref = NULL; m_lp_curr_node = NULL; }

			/**
				@brief 将迭代器重置为链表首
			*/
			void MoveFirst( void ){ m_lp_curr_node = m_list_ref->Head(); }

			/**
			* @brief 将迭代器移动到最后一个元素
			*/
			void MoveLast( void ){ m_lp_curr_node = m_list_ref->Tail(); }

			/**
				@brief 是否还有下一个元素
				@retval true 还有下一个元素
				@retval false 没有下一个元素
			*/
			bool HasNext( void ) const { return  ( NULL != m_lp_curr_node ); }

			/**
				@brief 返回当前元素，并移动到下一个元素
				@return 当前元素值
			*/
			T& Next( void )
			{
				ZP_ASSERT( m_list_ref );
				ZP_ASSERT( m_lp_curr_node );

				LinkNode* lp_ret_node = m_lp_curr_node;
				if( m_lp_curr_node->Next() == m_list_ref->Head() )
				{
					m_lp_curr_node = NULL;
				}else{
					m_lp_curr_node = m_lp_curr_node->Next();
				}
				return lp_ret_node->Data();
			}

			T& Data(void) { return m_lp_curr_node->Data(); }

			const T& Data(void) const { return m_lp_curr_node->Data(); }

			T& operator*()
			{
				ZP_ASSERT( m_list_ref );
				ZP_ASSERT( m_lp_curr_node );
				return m_lp_curr_node->Data();
			}

			const T& operator*() const
			{
				ZP_ASSERT( m_list_ref );
				ZP_ASSERT( m_lp_curr_node );
				return m_lp_curr_node->Data();
			}

			bool operator==( const Iterator& rhs )
			{
				return ( m_list_ref == rhs.m_list_ref ) 
					&& ( m_lp_curr_node == rhs.m_lp_curr_node );
			}

			bool operator != ( const Iterator& rhs )
			{
				return !( this->operator==( rhs ) );
			}

			Iterator& operator = ( const Iterator& rhs )
			{
				m_list_ref = rhs.m_list_ref;
				m_lp_curr_node = rhs.m_lp_curr_node;
				return *this;
			} 

		protected:
			
			/**
				@brief 返回迭代器指代的当前结点
				@return 当前结点指针
				@remark 仅供内部调用
			*/
			inline LinkNode* CurrNode(void) const { return m_lp_curr_node; }
			/**
				@brief 设置当前迭代器结点指针
				@param node 要设置的结点指针
				@return void 
				@remark 仅供内部调用
			*/
			inline void CurrNode( LinkNode* node ) { m_lp_curr_node = node; }

		private:
			LinkListT* m_list_ref;					///>指向链表的引用
			LinkNode* m_lp_curr_node;		///>指向迭代器所指代的当前链表结点
		};
		
		/**
			@brief 返回指向链表起始迭代器
			@return 指向链表起始的迭代器
			*/
			inline Iterator Begin(void)
			{
				return Iterator( this );
			}

		/**
			@brief 返回指向链表结尾的迭代器
			@return 指向链表结尾的迭代器
		*/
		inline Iterator End(void)
		{
			Iterator it(this);
			it.CurrNode( NULL );
			return it;
		}

		/**
			@brief 删除迭代器所指向结点
			@param 要删除的迭代器
			@return 删除当前迭代器所指结点的下一个结点
		*/
		inline Iterator Erase( Iterator& it )
		{
			ZP_ASSERT( this == it.m_list_ref );
			ZP_ASSERT( NULL !=  it.m_lp_curr_node );
			return Iterator( this , this->Erase( it.m_lp_curr_node ) );
		}

	private: 
		LinkNode* m_lp_head;				///> 链表头指针
		int m_count;								///> 链表中的结点数
	};

}// namespace ZPUTIL

#endif //ZP_LINKLIST