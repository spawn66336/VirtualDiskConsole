#include "Lexer.h"

namespace LexerSys
{



LexerSys::Lexer::Lexer():
m_state( UNLOADED_STATE )
{

}

LexerSys::Lexer::~Lexer()
{ 

}

void LexerSys::Lexer::SetString( const Util::String& str )
{
	m_state = LOADED_STATE;
	m_str_buf = str;
}

void LexerSys::Lexer::Analysis( void )
{
	m_cmd_head.Clear();
	m_options.Clear();
	m_paths.Clear(); 

	Util::String cmd_str = AnalysisCmdHead( m_str_buf );
	cmd_str = AnalysisCmdOptions( cmd_str );
	cmd_str = AnalysisCmdPaths( cmd_str );
	
	m_state = ANALYSISED_STATE;
}

void LexerSys::Lexer::Clear( void )
{ 
	m_cmd_head.Clear();
	m_paths.Clear();
	m_options.Clear(); 
	m_state = UNLOADED_STATE;
}

Util::String LexerSys::Lexer::AnalysisCmdHead( const Util::String& str )
{
	int i = 0;
	Util::String final_str = str;
	final_str.TrimLeft(); 

	m_cmd_head.Type( Token::CMD_TOKEN );

	while( i < str.Length() )
	{
		Util::String::XCHAR c = str.At( i );
		if( Util::IsAlpha( c ) )
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

Util::String LexerSys::Lexer::AnalysisCmdOptions( const Util::String& str )
{
	int i = 0;
	Util::String final_str = str;
	final_str.TrimLeft(); 
	Token curr_option;

	while( i < final_str.Length() )
	{ 
		Util::String::XCHAR c = final_str.At( i ); 

		//发现选项起始符
		if( c == '/' )
		{ 
				curr_option.Clear();  
				curr_option.Type( Token::OPTION_TOKEN );

				int j = i+1;
				while( j < final_str.Length()  )
				{
						Util::String::XCHAR c2 = final_str.At( j );
						//若当前字符不为字母则跳出
						if( !Util::IsAlpha( c2 ) )
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

Util::String LexerSys::Lexer::AnalysisCmdPaths( const Util::String& str )
{
	int i = 0;
	Util::String final_str = str;
	final_str.TrimLeft(); 

	Util::LinkListT<Util::String> paths;

	Util::String curr_path;

	while(  i < final_str.Length() )
	{
		Util::String::XCHAR c =  final_str.At( i );
		//若不为空白符
		if( !Util::IsWhiteChar( c ) )
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
	Util::LinkListT<Util::String>::Iterator it = paths.Begin();
	while( it != paths.End() )
	{
		Util::LinkListT<Token> tokens;
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

void LexerSys::AnalysisPath( const Util::String& str , Util::LinkListT<Token>& tokens )
{
	Util::String str_copy = str;
	str_copy.ClearAllWhiteChars();
	str_copy.ConvertToLowercast();

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
				if( IsWildCardToken( curr_token ) )
				{
					curr_token.Type( Token::WILDCARD_TOKEN );
				}else if( IsDriveToken( curr_token ) ){
					curr_token.Type( Token::DRIVE_TOKEN );
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
		}else if( IsDriveToken( curr_token ) ){
			curr_token.Type( Token::DRIVE_TOKEN );
		}
		tokens.PushBack( curr_token );
		curr_token.Clear();
	} 
}


bool IsAbsolutePath( const Util::LinkListT<Token>& toks )
{
	if( toks.Count() )
	{
		
		if( toks.At(0).Type() == Token::DRIVE_TOKEN  )
		{
			return true;
		}
	}
	return false;
}



#	if defined( ZP_DEBUG ) 
void LexerSys::Lexer::ShowDebugMessage( void )
{
	std::cout<<"原始字符串: "<<m_str_buf<<std::endl;
	std::cout<<"cmd name: "<<m_cmd_head<<std::endl;

	Util::LinkListT<Token>::Iterator it = m_options.Begin();
	std::cout<<"options: ";
	while( it != m_options.End() )
	{
		std::cout<<*it;
		it.Next();
	}//while( it != m_options.End() )
	std::cout<<std::endl;

	int path_count = 1;
	Util::LinkListT<Util::LinkListT<Token>>::Iterator path_it = m_paths.Begin();
	while( path_it != m_paths.End() )
	{
		std::cout<<"path"<<path_count<<": ";
		Util::LinkListT<Token>::Iterator tok_it = (*path_it).Begin();
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

}//namespace Lexer_Sys



