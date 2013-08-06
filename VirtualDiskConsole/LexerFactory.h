#ifndef ZP_LEXERFACTORY
#define ZP_LEXERFACTORY

#include "ILexer.h"
#include "Singleton.h"

/**
 * @author zhangpeng
 * @version 1.0
 * @created 06-八月-2013 9:17:33
 */

namespace Lexer_Sys
{ 
		/**
		* @class LexerFactory
		*			解析器工厂，单件类
		*/
		 class LexerFactory : public ZPUTIL::SingletonT<LexerFactory>
		 { 
		 public: 

			 enum LexerType
			 {
				 LEXER_TYPE_COMMAND = 1,
				 LEXER_TYPE_PATH
			 };

			  LexerFactory(){}
			  virtual ~LexerFactory(){}
	 
			/**
			 * @brief 创建解析器实例
			 * @param type
			 * @return 返回创建了的解析器
			 * @retval  NULL 创建失败，没有找到该类型的解析器
			 */
			ILexer* CreateLexer( const LexerType type );

		};//LexerFactory

}//namespace Lexer_Sys

#endif//ZP_LEXERFACTORY