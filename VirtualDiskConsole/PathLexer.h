#ifndef ZP_PATHLEXER
#define ZP_PATHLEXER

#include "LexerImpl.h"

/**
 * @author zhangpeng
 * @version 1.0
 * @created 06-°ËÔÂ-2013 9:17:33
 */

namespace Lexer_Sys
{
	 class PathLexer : public LexerImpl 
	 {
	 public: 
		 PathLexer(){}
		 virtual ~PathLexer(){}

		 virtual void Analysis( void );

	 };//class PathLexer
}//namespace Lexer_Sys
#endif //ZP_PATHLEXER