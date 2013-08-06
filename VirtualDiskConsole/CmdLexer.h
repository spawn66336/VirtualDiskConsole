#ifndef ZP_CMDLEXER
#define ZP_CMDLEXER

#include "LexerImpl.h"

/**
 * @author zhangpeng
 * @version 1.0
 * @created 06-°ËÔÂ-2013 9:17:33
 */

namespace Lexer_Sys
{ 
		class CmdLexer : public LexerImpl 
		{
		public:
			CmdLexer(){}
			virtual ~CmdLexer(){}

			virtual void Analysis( void );

		};// class CmdLexer 

}//namespace Lexer_Sys

#endif //ZP_CMDLEXER