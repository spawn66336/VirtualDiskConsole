#ifndef ZP_SEARCHPATH
#define ZP_SEARCHPATH

#include "ZPDependency.h"
#include "Token.h"

namespace LexerSys
{ 

	//路径字符长度的最大限制
	const int PATH_LENGTH_LIMIT = 256;

	class SearchPath
	{
	public:

		/**
		* @brief 默认构造函数
		*/
		SearchPath(void);
		/**
		* @brief 带参数的构造函数
		* @param path 要设置的路径字符串
		*/
		SearchPath( const Util::String path );
		/**
		* @brief 拷贝构造函数
		*/
		SearchPath( const SearchPath& path );
		/**
		* @brief 析构函数
		*/
		virtual ~SearchPath(void);

		/**
		* @brief 设置路径
		* @param path 路径字符串
		* @remark 该命令会将路径字符串分解为独立的符号。
		*/
		void Path( const Util::String& path );

		/**
		* @brief 返回路径名
		*/
		Util::String Path( void ) const;

		/**
		* @brief 查看路径是否超过长度限制
		*/
		bool IsLengthOutOfLimit( void ) const;

		/**
		* @brief 返回路径中的文件名符号
		*/
		bool GetFileNameToken( Token& tok );

		/**
		* @brief 返回路径名中的通配符
		*/
		bool GetWildCardToken( Token& tok );
		/**
		* @brief 查看当前路径是否为空
		*/
		bool IsEmpty( void ) const;

		/**
		* @brief 清空路径
		*/
		 void Clear( void );

		 /**
		 * @brief 附加路径到此路径末尾
		 * @param path 要附加的路径
		 * @return 返回当前路径引用
		 */
		SearchPath& Append( const SearchPath& path );

		/**
		* @brief 返回所在位置i处的符号
		* @param i 位置索引
		* @return 所在位置的符号
		*/
		Token& At( const int i );

		/**
		* @brief 返回所在位置i处的符号
		* @param i 位置索引
		* @return 所在位置的符号
		*/
		const Token& At( const int i ) const;

		/**
		* @brief 当前路径的符号数量
		* @return 当前路径所包含的符号数
		*/
		int TokenCount( void ) const;

		/**
		* @brief 分析当前路径是否为绝对路径
		* @param toks 待分析路径符号列表
		* @return 返回是否为绝对路径
		*/
		 bool IsAbsolutePath( void ) const;

		 /**
		 * @brief 遍历该路径各符号结点时的当前符号
		 * @param 获取的当前符号
		 * @return 获取是否成功
		 * @retval true 获取成功
		 * @retval false 获取失败
		 */
		bool CurrToken( Token& tok ) const;

		/**
		* @brief 是否含有下一个符号
		*/
		bool HasNext(void) const;

		/**
		* @brief 将当前符号位置移动到符号列表首
		*/
		void MoveToFirstToken(void);

		/**
		* @brief 将当前符号位置移动到下一个符号位置
		*/
		void MoveToNextToken(void);

		/**
		* @brief 将当前符号位置移动到最后一个符号位置
		*/
		void MoveToLastToken(void);

		/**
		* @brief 赋值运算符重载
		*/
		SearchPath& operator=( const SearchPath& rhs ); 

		/**
		* @brief 赋值运算符重载
		*/
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