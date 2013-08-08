#ifndef ZP_STACK
#define ZP_STACK

#include "LinkList.h"

namespace Util
{ 
	template<typename T>
	class StackT
	{
	public:
		/**
			@brief 默认构造函数
		*/
		StackT(void){}
		/**
			@brief 拷贝构造函数
		*/
		StackT( const StackT& stack ):m_stack(stack.m_stack){}
		/**
			@brief 析构函数
		*/
		~StackT(){}
		 
		/**
			@brief 将元素data入栈
			@param data 要入栈元素
		*/
		inline void Push( const T& data ){ m_stack.PushFront( data ); }
		/**
			@brief 将栈顶元素出栈
		*/
		inline void Pop(void){ m_stack.PopFront();  }
		/**
			@brief 返回栈元素数
			@return 栈元素数
		*/
		inline int    Size(void) const { return m_stack.Count(); }
		/**
			@brief 栈是否为空
			@retval true 栈为空栈
			@retval false 栈为非空
		*/
		inline bool  IsEmpty(void) const { return m_stack.IsEmpty(); }
		/**
			@brief 返回栈顶元素
			@return 栈顶元素
		*/
		inline T& Front(void){ return m_stack.Front(); }

		/**
			@brief 返回栈顶元素
			@return 栈顶元素
		*/
		inline const T& Front(void) const { return m_stack.Front(); }

		/**
			@brief 赋值运算符重载 
		*/
		inline StackT& operator=( const StackT& stack )
		{
			m_stack = stack.m_stack;
			return *this;
		}

	private:
		LinkListT<T> m_stack;	///>用于栈的链表数据结构
	};

}//namespace ZPUTIL

#endif //ZP_STACK