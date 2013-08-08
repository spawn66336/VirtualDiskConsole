#ifndef ZP_LEXER
#define ZP_LEXER

#include "ZPDependency.h"
#include "Token.h"

/**
 * @author zhangpeng
 * @version 1.0
 * @created 06-八月-2013 9:17:33
 */

namespace LexerSys
{ 
		 class Lexer 
		 { 
		 public:   

			 enum LexerState{
				 LOADED_STATE = 1,
				 UNLOADED_STATE ,
				 ANALYSISED_STATE
			 };

			 Lexer();
			 virtual ~Lexer();

			 /**
			 * @brief 设置需要分析的字符串 
			 * @param str 需要分析的字符串
			 */
			virtual void SetString(  const Util::String& str ); 
			
			/**
			* @brief 获得命令头
			* @return 命令头符号
			*/
			virtual Token& GetCommandToken( void )  { return m_cmd_head; }

			/**
			* @brief 获得命令选项
			* @return 命令选项列表
			*/
			virtual Util::LinkListT<Token>& GetCommandOptions( void )  { return m_options; }

			/**
			* @brief 获得命令路径列表
			* @return 获得命令路径列表
			*/
			virtual Util::LinkListT<Util::LinkListT<Token>>& GetCommandPaths( void )  { return m_paths; }

			/**
			 * @brief 分析所设置的字符串，从中分析出各种token
			 */
			virtual void Analysis( void );

			/**
			 * @brief 清空解析器内容供下次再次分析
			 */
			virtual void Clear( void );


#	if defined( ZP_DEBUG )
			/**
			* @brief 显示Debug信息
			*/
			void ShowDebugMessage( void );
#endif

		 protected:
			 
			 /**
			 * @brief 从要分析的字符串中提取命令头
			 * @remark 仅供内部调用函数
			 */
			 Util::String AnalysisCmdHead( const Util::String& str );

			 /**
			 * @brief 从要分析的字符串中提取命令选项
			 * @remark 仅供内部调用函数
			 */
			 Util::String  AnalysisCmdOptions( const Util::String& str );

			 /**
			 * @brief 从要分析的字符串中提取命令路径
			 * @remark 仅供内部调用函数
			 */
			 Util::String  AnalysisCmdPaths( const Util::String& str );
			  
		 private: 

			 LexerState m_state;												///>解析器状态
			 Util::String m_str_buf;											///>待解析字符串
			 Token m_cmd_head;											///>命令头
			 Util::LinkListT<Token> m_options;						///>命令选项
			 Util::LinkListT< Util::LinkListT<Token> > m_paths;  ///>路径名列表

		};//class Lexer 

		/**
		* @brief 从路径名中分析出符号并存入传入的符号链表中
		* @param str 待分析路径名
		* @param tokens 分析出的符号
		*/
		 extern void AnalysisPath( const Util::String& str , Util::LinkListT<Token>& tokens );

		 /**
		* @brief 分析当前路径是否为绝对路径
		* @param toks 待分析路径符号列表
		* @return 返回是否为绝对路径
		*/
		 extern bool IsAbsolutePath( const Util::LinkListT<Token>& toks );

}//namespace Lexer_Sys
 
#endif//ZP_LEXER