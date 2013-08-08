#include "Token.h"

namespace LexerSys
{  

	Token& LexerSys::Token::operator=( const Token& rhs )
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

	void Token::Append( const Util::String::XCHAR c )
	{
		m_name.Append( c );
		m_name.ConvertToLowercast();
	}

	void Token::Append( const Util::String& str )
	{
		m_name.Append( str );
		m_name.ConvertToLowercast();
	}

	bool IsWildCardToken( const Token& tok )
	{

		Util::String tokname =  tok.Name(); 

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

	std::ostream& operator<<( std::ostream& o , const Token& tok )
	{
		Util::String type_name;
		switch( tok.Type() )
		{
		case Token::NULL_TOKEN:
			type_name = "NULL";
			break;
		case Token::CMD_TOKEN:
			type_name = "CMD";
			break;
		case Token::OPTION_TOKEN:
			type_name = "OPT";
			break;
		case Token::PATH_NODE_TOKEN:
			type_name = "PATH";
			break;
		case Token::WILDCARD_TOKEN:
			type_name = "WILDCARD";
			break;
		default:
			type_name = "DEF";
			break;
		}

		o<<" ( "<<tok.Name()<<" "<<type_name<<" ) ";

		return o;
	}

}//namespace Lexer_Sys