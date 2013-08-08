#include "Lexer.h"


Lexer_Sys::Lexer::Lexer():
m_state( UNLOADED_STATE )
{

}

Lexer_Sys::Lexer::~Lexer()
{ 

}

void Lexer_Sys::Lexer::SetString( const ZPUTIL::String& str )
{
	m_state = LOADED_STATE;
	m_str_buf = str;
}

void Lexer_Sys::Lexer::Analysis( void )
{
	m_cmd_head.Clear();
	m_options.Clear();
	m_paths.Clear(); 

	ZPUTIL::String cmd_str = AnalysisCmdHead( m_str_buf );
	cmd_str = AnalysisCmdOptions( cmd_str );
	cmd_str = AnalysisCmdPaths( cmd_str );
	
	m_state = ANALYSISED_STATE;
}

void Lexer_Sys::Lexer::Clear( void )
{ 
	m_cmd_head.Clear();
	m_paths.Clear();
	m_options.Clear(); 
	m_state = UNLOADED_STATE;
}

ZPUTIL::String Lexer_Sys::Lexer::AnalysisCmdHead( const ZPUTIL::String& str )
{
	int i = 0;
	ZPUTIL::String final_str = str;
	final_str.TrimLeft(); 

	m_cmd_head.Type( Token::CMD_TOKEN );

	while( i < str.Length() )
	{
		ZPUTIL::String::XCHAR c = str.At( i );
		if( ZPUTIL::IsAlpha( c ) )
		{
			m_cmd_head.Append( c );
		}else{ 
			break;
		}
		i++;
	} 

	final_str.Delete( 0 , i );
	return final_str;
}

ZPUTIL::String Lexer_Sys::Lexer::AnalysisCmdOptions( const ZPUTIL::String& str )
{
	int i = 0;
	ZPUTIL::String final_str = str;
	final_str.TrimLeft(); 
	Token curr_option;

	while( i < final_str.Length() )
	{ 
		ZPUTIL::String::XCHAR c = final_str.At( i ); 

		//发现选项起始符
		if( c == '/' )
		{ 
				curr_option.Clear();  
				curr_option.Type( Token::OPTION_TOKEN );

				int j = i+1;
				while( j < final_str.Length()  )
				{
						ZPUTIL::String::XCHAR c2 = final_str.At( j );
						//若当前字符不为字母则跳出
						if( !ZPUTIL::IsAlpha( c2 ) )
						{
							break;
						}
						curr_option.Append( c2 );
						j++;
				} //while( j < str.Length() )

				//若参数为空则标记其为非法
				if( curr_option.IsEmpty() )
				{
					curr_option.SetLegal( false );
				}

				//将参数加入参数列表
				m_options.PushBack( curr_option ); 

				//删除此参数
				final_str.Delete( i , j - i );
				continue; 
		} // if ( c == '/')  

		i++;
	}//while( i < final_str.Length() )

	return final_str;
}

ZPUTIL::String Lexer_Sys::Lexer::AnalysisCmdPaths( const ZPUTIL::String& str )
{
	int i = 0;
	ZPUTIL::String final_str = str;
	final_str.TrimLeft(); 

	ZPUTIL::LinkListT<ZPUTIL::String> paths;

	ZPUTIL::String curr_path;

	while(  i < final_str.Length() )
	{
		ZPUTIL::String::XCHAR c =  final_str.At( i );
		//若不为空白符
		if( !ZPUTIL::IsWhiteChar( c ) )
		{
			curr_path.Append( c );
		}else{
			//若字符串不为空
			if( !curr_path.IsEmpty() )
			{
				paths.PushBack( curr_path );
				curr_path.Empty();
			} 
		}
		i++;
	}//while( i < final_str.Length() )

	//当前路径不为空 则加入路径列表中
	if( !curr_path.IsEmpty() )
	{
		paths.PushBack( curr_path );
		curr_path.Empty();
	}

	//将每个路径拆解为符号列表
	ZPUTIL::LinkListT<ZPUTIL::String>::Iterator it = paths.Begin();
	while( it != paths.End() )
	{
		ZPUTIL::LinkListT<Token> tokens;
		AnalysisPath( *it , tokens );
		if( tokens.Count() )
		{
			m_paths.PushBack( tokens );
		}
		it.Next();
	}
	final_str.Empty();
	return final_str;
}

void Lexer_Sys::Lexer::AnalysisPath( const ZPUTIL::String& str , ZPUTIL::LinkListT<Token>& tokens )
{
	ZPUTIL::String str_copy = str;
	str_copy.ClearAllWhiteChars();
	str_copy.ConvertToLowercast();
	 
	int i = 0;
	Token curr_token;
	curr_token.Type( Token::PATH_NODE_TOKEN );
	while( i < str_copy.Length() )
	{
		ZPUTIL::String::XCHAR c = str_copy.At( i );
		//若不是目录分隔符
		if( c != '\\' )
		{ 
			curr_token.Append( c );
		}else{ 

			//若当前符号不为空则加入列表
			if( !curr_token.IsEmpty() )
			{
				if( IsWildCardToken( curr_token ) )
				{
					curr_token.Type( Token::WILDCARD_TOKEN );
				}
				tokens.PushBack( curr_token );
			}
			curr_token.Clear();
			curr_token.Type( Token::PATH_NODE_TOKEN );
		} 
		i++;
	}//while( i < str_copy.Length() )

	//若当前符号不为空则放入列表
	if( !curr_token.IsEmpty() )
	{
		if( IsWildCardToken( curr_token ) )
		{
			curr_token.Type( Token::WILDCARD_TOKEN );
		}
		tokens.PushBack( curr_token );
		curr_token.Clear();
	} 
}


#	if defined( ZP_DEBUG ) 
void Lexer_Sys::Lexer::ShowDebugMessage( void )
{
	std::cout<<"原始字符串: "<<m_str_buf<<std::endl;
	std::cout<<"cmd name: "<<m_cmd_head<<std::endl;

	ZPUTIL::LinkListT<Token>::Iterator it = m_options.Begin();
	std::cout<<"options: ";
	while( it != m_options.End() )
	{
		std::cout<<*it;
		it.Next();
	}//while( it != m_options.End() )
	std::cout<<std::endl;

	int path_count = 1;
	ZPUTIL::LinkListT<ZPUTIL::LinkListT<Token>>::Iterator path_it = m_paths.Begin();
	while( path_it != m_paths.End() )
	{
		std::cout<<"path"<<path_count<<": ";
		ZPUTIL::LinkListT<Token>::Iterator tok_it = (*path_it).Begin();
		while( tok_it != (*path_it).End() )
		{
			std::cout<<*tok_it;
			tok_it.Next();
		}// while( tok_it != (*path_it).End() )
		std::cout<<std::endl;
		path_it.Next();
	} // while( path_it != m_paths.End() )
} 
#endif //if defined( ZP_DEBUG )

 