#ifndef ZP_ILEXER
#define ZP_ILEXER

#include "ZPDependency.h"
#include "Token.h"

/**
 * @author zhangpeng
 * @version 1.0
 * @created 06-八月-2013 9:17:33
 */

namespace Lexer_Sys
{ 
		 class ILexer 
		 { 
		 public:   
			 ILexer(){} 
			 virtual ~ILexer(){}

			 /**
			 * @brief 设置需要分析的字符串 
			 * @param str 需要分析的字符串
			 */
			virtual void SetString(  const ZPUTIL::String& str ) = 0;

			/**
			 * @brief 分析所设置的字符串，从中分析处各种token
			 */
			virtual void Analysis( void ) = 0;

			/**
			 * @brief 清空解析器内容供下次再次分析
			 */
			virtual void Clear( void ) = 0;

			/**
			 * @brief  获得分析完毕后得到的符号列表
			 */
			virtual const ZPUTIL::LinkListT<Token>& GetTokenList( void ) const  = 0; 


		};//class ILexer 

}//namespace Lexer_Sys
 
#endif//ZP_ILEXER