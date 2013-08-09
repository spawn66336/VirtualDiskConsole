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

	while( i < final_str.Length() )
	{
		Util::String::XCHAR c = final_str.At( i );
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

	//从命令字符串中提取出的字符
	Util::LinkListT<Util::String> paths;

	Util::String curr_path;
	bool is_double_quotes = false;
	
	while(  i < final_str.Length() )
	{
				Util::String::XCHAR c =  final_str.At( i );
		  
				if( is_double_quotes )
				{ 
							//若碰到分隔符
							if( c != '"' )
							{ 
								curr_path.Append( c );
							}else{
								//若字符串不为空
								if( !curr_path.IsEmpty() )
								{
									paths.PushBack( curr_path );
									curr_path.Empty();
									is_double_quotes = false;
								} 
							}
				}else{
						if( c == '"' )
						{
							is_double_quotes = true;
							i++;
							continue;
						}

						if( !Util::IsWhiteChar(c) )
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
				}

		i++;
	}//while( i < final_str.Length() )

	//当前路径不为空 则加入路径列表中
	if( !curr_path.IsEmpty() )
	{
		paths.PushBack( curr_path );
		curr_path.Empty();
		is_double_quotes = false;
	}

	//将每个路径拆解为符号列表
	Util::LinkListT<Util::String>::Iterator it = paths.Begin();
	while( it != paths.End() )
	{
		SearchPath path;
		path.Path(*it); 
		if( !path.IsEmpty() )
		{
			m_paths.PushBack( path );
		}
		it.Next();
	}
	final_str.Empty();
	return final_str;
}
  


}//namespace Lexer_Sys



