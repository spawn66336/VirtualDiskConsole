#include "Token.h"

namespace Lexer_Sys
{ 
	Token& Lexer_Sys::Token::operator=( const Token& rhs )
	{
		m_type = rhs.m_type;
		m_name = rhs.m_name;
		m_legal = rhs.m_legal;
		return *this;
	}
	 
}//namespace Lexer_Sys