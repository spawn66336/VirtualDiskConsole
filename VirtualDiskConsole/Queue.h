#ifndef ZP_QUEUE
#define ZP_QUEUE

#include "LinkList.h"

namespace Util
{
	template<typename T>
	class QueueT
	{
	public:
		/**
			@brief 默认构造函数
		*/
		QueueT(){}
		/**
			@brief 拷贝构造函数
		*/
		QueueT( const QueueT& q ):m_queue(q.m_queue){}
		/**
			@brief 析构函数
		*/
		~QueueT(){}

		/**
			@brief 将元素 data 入队列
			@param data 要压入的元素
		*/
		inline void Enqueue( const T& data ){ m_queue.PushBack( data ); }

		/**
			@brief 将元素出队列
		*/
		inline void Dequeue( void ){ m_queue.PopFront(); }

		/**
			@brief 返回队列头部的元素
			@return 返回的队列头部元素
		*/
		inline T& Front(void) { return m_queue.Front(); }

		/**
			@brief 返回队列头部的元素
			@return 返回的队列头部元素
		*/
		inline const T& Front(void) const { return m_queue.Front(); }

		/**
			@brief 返回队列大小
			@return 队列元素数
		*/
		inline int Size(void) const { return m_queue.Count(); }

		/**
			@brief 赋值运算符重载
			@return 当前队列引用
		*/
		inline QueueT& operator=( const QueueT& rhs )
		{
			m_queue = rhs.m_queue;
			return *this;
		}
	private:
		LinkListT<T> m_queue;		///>用于队列的链表数据结构
	};
	
}//namespace ZPUTIL


#endif //ZP_QUEUE