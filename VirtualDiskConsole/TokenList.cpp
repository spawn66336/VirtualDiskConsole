#include "TokenList.h"

namespace Lexer_Sys
{  
	TokenList::TokenList(void)
	{

	} 

	TokenList::~TokenList(void)
	{

	}

	void TokenList::AppendToken( const Token& token )
	{
		m_token_list.PushBack( token );
		m_curr_token = m_token_list.Begin();
	}

	void TokenList::InsertToken( const int i , const Token& token )
	{
		m_token_list.Insert( i , token );
		m_curr_token = m_token_list.Begin();
	}

	void TokenList::DeleteToken( const int i )
	{
		m_token_list.DeleteAt( i );
		m_curr_token = m_token_list.Begin();
	}

	bool Lexer_Sys::TokenList::HasNext( void ) const
	{
		return m_curr_token.HasNext();
	}

	void Lexer_Sys::TokenList::MoveFirst( void )
	{
		m_curr_token.MoveFirst();
	}

	void Lexer_Sys::TokenList::MoveNext( void )
	{
		m_curr_token.Next();
	}

	Token& Lexer_Sys::TokenList::CurrToken( void )
	{
		return *m_curr_token;
	}

	const Token& Lexer_Sys::TokenList::CurrToken( void ) const
	{
		return *m_curr_token;
	}

}// Lexer_Sys