#ifndef ZP_TOKEN
#define ZP_TOKEN

#include "ZPDependency.h"

/**
 * @author zhangpeng
 * @version 1.0
 * @created 06-八月-2013 9:17:33
 */
namespace Lexer_Sys
{ 
	class Token {
	public: 

		enum TokenType
		{
			STRING_TYPE = 1,
			INT_TYPE
		};

		/**
		* @brief 默认构造函数
		*/
		 Token():m_type(STRING_TYPE),m_legal(true){}
		 /**
		 * @brief 拷贝构造函数
		 */
		 Token( const Token& token ):m_type( token.m_type ),m_legal( token.m_legal ),m_name( token.m_name ){}
		 /**
		 * @brief 析构函数
		 */
		 virtual ~Token(){}

		/**
		 * @brief	 获取符号内容
		 * @return 返回内容字符串
		 */
		ZPUTIL::String Name( void ) const { return m_name; }

		/**
		 * @brief	 设置符号内容
		 * @param 要设置的符号内容
		 * @return void
		 */
		void Name( const ZPUTIL::String& name ){ m_name = name; }
		 

		/**
		 *@brief  返回符号类型
		 */
		TokenType Type(){ return m_type; }

		/**
		* @brief 设置标记类型
		*/
		void Type( const TokenType type ){ m_type = type; } 

		/**
		* @brief 返回当前符号是否为合法
		* @return 返回是否合法
		*/
		bool IsLegal( void ) const { return m_legal; }

		/**
		* @brief 设置符号对象是否合法
		* @param 合法与否
		*/
		void SetLegal( const bool legal ){ m_legal = legal; }

		/**
		* @brief 赋值运算符重载
		*/
		Token& operator=( const Token& rhs );

	private:

		TokenType      m_type;			///>符号类型
		bool				   m_legal;			///>该符号是否合法
		ZPUTIL::String m_name;		///>符号内容字符串

	}; //class Token

}//namespace Lexer_Sys
#endif //ZP_TOKEN
