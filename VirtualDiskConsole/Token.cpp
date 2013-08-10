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
		m_type = UNKNOWN_TOKEN; 
		m_subtype = NULL_TOKEN;
		m_legal = true; 
		m_name.Empty();
	}

	void Token::Append( const Util::String::XCHAR c )
	{
		m_name.Append( c );
		m_name.TrimLeft();
		//m_name.ConvertToLowercast();
	}

	void Token::Append( const Util::String& str )
	{
		m_name.Append( str );
		m_name.TrimLeft();
		//m_name.ConvertToLowercast();
	}

	void Token::Analysis( void )
	{ 
		if( m_name.IsEmpty() )
		{
			m_subtype = NULL_TOKEN;
		}else if( m_name.Length() == 2 ){ 
			if( Util::IsAlpha( m_name.At(0) )  && m_name.At(1) == ':' )
			{
				m_subtype = DRIVE_TOKEN;
			}
		}else if( -1 != m_name.Find("*" , 0 ) ){
			m_subtype = WILDCARD_TOKEN; 
		}else if( -1 != m_name.Find("." , 0 ) ){
			m_subtype = FILE_NODE_TOKEN;
		}else{
			m_subtype = FOLDER_NODE_TOKEN;
		} 
	}

	Util::String Token::ExtractFileName( void ) const
	{
		int i = m_name.Find('.' , 0 );
		if( i != -1 )
		{
			return m_name.SubString( 0 , i );
		}
		return m_name;
	}

	Util::String Token::ExtractFileExtName( void ) const
	{
		if( SubType() != WILDCARD_TOKEN ||
			SubType() != FILE_NODE_TOKEN )
		{
			return Util::String();
		}

		int i = m_name.Find('.' , 0 );
		if( i != -1 )
		{
			return m_name.SubString( i+1 , m_name.Length()-i-1); 
		}
		return Util::String();
	}

  

 
}//namespace Lexer_Sys