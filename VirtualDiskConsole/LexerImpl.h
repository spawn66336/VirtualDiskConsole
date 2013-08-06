#ifndef ZP_LEXERIMPL
#define ZP_LEXERIMPL

#include "ILexer.h"

/**
 * @author zhangpeng
 * @version 1.0
 * @created 06-八月-2013 9:17:33
 */


namespace Lexer_Sys
{ 
		 class LexerImpl : public  ILexer 
		 { 
		 public: 
			 LexerImpl():m_state(STATE_UNLOAD){}
			 virtual ~LexerImpl(){}
	  
			 virtual void SetString( const ZPUTIL::String str){ m_state = STATE_LOADED; m_str_buf = str; } 
			 virtual void Analysis(){ m_state = STATE_ANALYSISED; }
			 virtual void Clear(void); 
			 virtual const ZPUTIL::LinkListT<Token>& GetTokenList() const;

		 private: 

			 enum LexerState
			 {
				 STATE_UNLOAD = 0,
				 STATE_LOADED ,
				 STATE_ANALYSISED
			 };

			 LexerState m_state;								 ///>内部状态
			 ZPUTIL::String m_str_buf;						 ///>待分析的字符串
			 ZPUTIL::LinkListT<Token> m_tokens;   ///>最终分析出的符号

		};// class LexerImpl

}//Lexer_Sys

#endif //ZP_LEXERIMPL