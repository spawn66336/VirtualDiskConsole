#ifndef ZP_SEARCHPATH
#define ZP_SEARCHPATH

#include "ZPDependency.h"
#include "Token.h"

namespace LexerSys
{ 
	class SearchPath
	{
	public:
		SearchPath(void);
		SearchPath( const Util::String path );
		SearchPath( const SearchPath& path );
		virtual ~SearchPath(void);

		void Path( const Util::String& path );
		Util::String Path(void) const;
		bool GetFileNameToken( Token& tok );
		bool GetWildCardToken( Token& tok );
		bool IsEmpty(void) const;
		 void Clear(void);
		SearchPath& Append( const SearchPath& path );
		Token& At( const int i );
		const Token& At( const int i ) const;
		int TokenCount(void) const;
		/**
		* @brief 分析当前路径是否为绝对路径
		* @param toks 待分析路径符号列表
		* @return 返回是否为绝对路径
		*/
		 bool IsAbsolutePath( void ) const;
		bool CurrToken( Token& tok ) const;
		bool HasNext(void) const;
		void MoveToFirstToken(void);
		void MoveToNextToken(void);
		void MoveToLastToken(void);
		SearchPath& operator=( const SearchPath& rhs ); 
		SearchPath& operator=( const Util::String& rhs );
	protected:

		/**
		* @brief 从路径名中分析出符号并存入传入的符号链表中 
		*/
		void AnalysisPath( void ); 

	private:
		typedef Util::LinkListT<Token> TokenList;
		Util::String m_path;								///>路径名
		TokenList::Iterator m_curr_tok;				///>当前符号
		TokenList m_path_toks;							///>路径名分解后形成的符号列表
	}; 
}//namespace Util

#endif//ZP_SEARCHPATH