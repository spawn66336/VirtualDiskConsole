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

	void Token::Clear( void )
	{
		m_type = NULL_TOKEN; 
		m_legal = true; 
		m_name.Empty();
	}

	void Token::Append( const ZPUTIL::String::XCHAR c )
	{
		m_name.Append( c );
	}

	void Token::Append( const ZPUTIL::String& str )
	{
		m_name.Append( str );
	}

	bool IsWildCardToken( const Token& tok )
	{

		ZPUTIL::String tokname =  tok.Name(); 

		if( tokname.IsEmpty() )
		{
			return false;
		}

		if( tokname.At(0) == '*' )
		{
			return true;
		}

		return false;
	}

}//namespace Lexer_Sys