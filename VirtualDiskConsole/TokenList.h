#ifndef ZP_TOKENLIST
#define ZP_TOKENLIST

#include "ZPDependency.h"
#include "Token.h"

namespace LexerSys
{ 
	class TokenList
	{
	public:
		TokenList(void);
		~TokenList(void);

		/**
		* @brief 在符号列表尾添加一个符号
		* @param token 要添加的符号
		*/
		void AppendToken( const Token& token );

		/**
		* @brief 在列表的所在位置i处添加符号token 
		* @param token 要添加的符号
		*/
		void InsertToken( const int i , const Token& token );

		/**
		* @brief 删除列表位置i处的符号
		* @param i 要删除符号的位置
		*/
		void DeleteToken( const int i );

		/**
		* @brief 清空符号列表 
		*/
		void Clear( void );

		/**
		* @brief 是否有下一个符号
		*/
		bool HasNext( void ) const; 
		void MoveFirst( void ); 
		void MoveNext( void );

		/**
		* @brief 获得当前符号
		*/
		Token& CurrToken( void );
		const Token& CurrToken( void ) const;
		 
	private:
		Util::LinkListT<Token>::Iterator m_curr_token;	 //当前符号
		Util::LinkListT<Token> m_token_list;				 //符号列表
	};

}//namespace Lexer_Sys

#endif//ZP_TOKENLIST