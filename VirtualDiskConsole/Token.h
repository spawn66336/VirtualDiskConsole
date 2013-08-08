#ifndef ZP_TOKEN
#define ZP_TOKEN

#include "ZPDependency.h"

/**
 * @author zhangpeng
 * @version 1.0
 * @created 06-八月-2013 9:17:33
 */
namespace LexerSys
{ 
	class Token {
	public:  

		enum TokenType
		{
			NULL_TOKEN,
			CMD_TOKEN,
			OPTION_TOKEN,
			PATH_NODE_TOKEN,
			WILDCARD_TOKEN
		};

		/**
		* @brief 默认构造函数
		*/
		 Token():m_type(NULL_TOKEN),m_legal(true){}

		 /**
		 * @brief 拷贝构造函数
		 */
		 Token( const Token& token ):m_type( token.m_type ),m_name( token.m_name ),m_legal( token.m_legal ){}

		 /**
		 * @brief 析构函数
		 */
		 virtual ~Token(){}

		/**
		 * @brief	 获取符号内容
		 * @return 返回内容字符串
		 */
		Util::String Name( void ) const { return m_name; }

		/**
		 * @brief	 设置符号内容
		 * @param 要设置的符号内容
		 * @return void
		 */
		void Name( const Util::String& name ){ m_name = name; }
		 

		/**
		 *@brief  返回符号类型
		 */
		TokenType Type( void ){ return m_type; }

		/**
		* @brief 返回符号类型
		*/
		const TokenType Type( void ) const { return m_type; }

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
		* @brief 返回当前符号是否为空
		* @return 当前符号是否为空
		* @retval true 为空
		* @retval false 不为空
		*/
		bool IsEmpty( void ) const { return m_name.IsEmpty(); }

		/**
		* @brief 设置符号对象是否合法
		* @param 合法与否
		*/
		void SetLegal( const bool legal ){ m_legal = legal; }

		/**
		* @brief 在标记结尾处附加一个字符
		* @param c 要附加的字符
		*/
		void Append( const Util::String::XCHAR c  );

		/**
		* @brief 在标记结尾处添加一个字符串
		* @param str 要附加的字符串
		*/
		void Append( const Util::String& str );

		/**
		* @brief 将该符号清空
		*/
		void Clear(void);

		/**
		* @brief 赋值运算符重载
		*/
		Token& operator=( const Token& rhs );


		friend std::ostream& operator<<( std::ostream& o , const Token& tok );
		

	private:

		TokenType      m_type;			///>符号类型
		bool				   m_legal;			///>该符号是否合法
		Util::String m_name;		///>符号内容字符串

	}; //class Token

	std::ostream& operator<<( std::ostream& o , const Token& tok );

/**
* @brief 查看当前标记是否为通配符
*/
extern	bool IsWildCardToken( const Token& tok );

}//namespace Lexer_Sys
#endif //ZP_TOKEN
