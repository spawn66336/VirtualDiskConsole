#include "SearchPath.h"

namespace LexerSys
{



SearchPath::SearchPath(void)
{
}

SearchPath::SearchPath( const SearchPath& path ):
m_path( path.m_path ),
m_path_toks( path.m_path_toks )
{
	m_curr_tok = m_path_toks.Begin();
} 

SearchPath::SearchPath( const Util::String path )
{
	Path( path );
}

SearchPath::~SearchPath(void)
{
}

void SearchPath::Path( const Util::String& path )
{
	m_path = path;
	AnalysisPath();
	m_curr_tok = m_path_toks.Begin();
}

Util::String SearchPath::Path( void ) const
{
	return m_path;
}

Token& SearchPath::At( const int i )
{
	return m_path_toks.At( i );
}

const Token& SearchPath::At( const int i ) const
{
	return m_path_toks.At( i );
}
  
bool SearchPath::CurrToken( Token& tok ) const
{
	if( m_curr_tok.HasNext() )
	{
		tok = *m_curr_tok;
		return true;
	}
	return false;
}

int SearchPath::TokenCount( void ) const
{
	return m_path_toks.Count();
}

bool SearchPath::HasNext( void ) const
{
	return m_curr_tok.HasNext();
}

void SearchPath::MoveToFirstToken( void )
{
	m_curr_tok.MoveFirst();
}

void SearchPath::MoveToNextToken( void )
{
	m_curr_tok.Next();
}

void SearchPath::MoveToLastToken( void )
{
	m_curr_tok.MoveLast();
}


SearchPath& SearchPath::operator=( const SearchPath& rhs )
{
	m_path = rhs.m_path;
	m_path_toks = rhs.m_path_toks;
	m_curr_tok = m_path_toks.Begin();
	return *this;
}

SearchPath& SearchPath::operator=( const Util::String& rhs )
{
	this->Path( rhs );
	return *this;
}

bool SearchPath::IsLengthOutOfLimit( void ) const
{
	return m_path.Length() >= 256 ;
}


void SearchPath::AnalysisPath( void )
{
	m_path_toks.Clear();

	Util::String str_copy = m_path;
	//str_copy.ClearAllWhiteChars();
	//str_copy.ConvertToLowercast();

	int i = 0;
	Token curr_token;
	curr_token.Type( Token::PATH_NODE_TOKEN );
	while( i < str_copy.Length() )
	{
		Util::String::XCHAR c = str_copy.At( i );
		//若不是目录分隔符
		if( c != '\\' && c != '"' && c != '“' )
		{ 
			curr_token.Append( c );
		}else{ 

			//若当前符号不为空则加入列表
			if( !curr_token.IsEmpty() )
			{
				curr_token.Analysis(); 
				m_path_toks.PushBack( curr_token );
			}
			curr_token.Clear();
			curr_token.Type( Token::PATH_NODE_TOKEN );
		} 
		i++;
	}//while( i < str_copy.Length() )

	//若当前符号不为空则放入列表
	if( !curr_token.IsEmpty() )
	{
		curr_token.Analysis(); 
		m_path_toks.PushBack( curr_token );
		curr_token.Clear();
	} 
}

bool SearchPath::IsAbsolutePath( void ) const
{
	if( m_path_toks.Count() )
	{ 
		if( m_path_toks.At(0).SubType()== Token::DRIVE_TOKEN  )
		{
			return true;
		}
	}
	return false;
}

bool SearchPath::IsEmpty( void ) const
{
	return m_path_toks.Count() == 0;
}

SearchPath& SearchPath::Append( const SearchPath& path )
{
	m_path += '\\';
	m_path += path.Path();
	m_path_toks.Append( path.m_path_toks );
	return *this;
}

void SearchPath::Clear( void )
{
	m_path.Empty();
	m_path_toks.Clear();
	m_curr_tok = m_path_toks.Begin();
}

bool SearchPath::GetFileNameToken( Token& tok ) 
{
	Util::LinkListT<Token>::Iterator it = m_path_toks.Begin();
	while( it != m_path_toks.End() )
	{
		if( (*it).SubType() == Token::FILE_NODE_TOKEN )
		{
			tok = (*it);
			return true;
		}
		it.Next();
	}
	return false;
}

bool SearchPath::GetWildCardToken( Token& tok ) 
{
	Util::LinkListT<Token>::Iterator it = m_path_toks.Begin();
	while( it != m_path_toks.End() )
	{
		if( (*it).SubType() == Token::WILDCARD_TOKEN )
		{
			tok = (*it);
			return true;
		}
		it.Next();
	}
	return false;
}



}//namespace LexerSys