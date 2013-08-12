#ifndef ZP_NODEVISITOR
#define ZP_NODEVISITOR

#include "ZPDependency.h"
#include "Token.h"
#include "SearchPath.h"

namespace FileSys
{
	class Node;

	class NodeVisitor
	{
	public:
	 
		NodeVisitor( void );
		virtual ~NodeVisitor( void ); 

		/**
		* @brief 设置搜索路径
		* @param path 搜索路径
		*/
		virtual void SetPath( const LexerSys::SearchPath& path );

		/**
		* @brief 获得搜索路径的当前符号
		* @return 搜索路径的当前符号
		*/
		virtual LexerSys::Token GetCurrPathToken( void ) const;

		/**
		* @brief 是否还有下一个符号
		*/
		virtual bool HasNextToken( void ) const;

		/**
		* @brief 移动到搜索路径的下一个符号
		*/
		virtual void MoveToNextToken( void );

		/**
		* @brief 获得搜索到的节点
		*/
		virtual Node* GetSearchNode(void);

		/**
		* @brief 获得搜索结果的输出字符串
		*/
		virtual Util::String GetResultOutputString(void) const;

		/**
		* @brief 访问节点
		* @param node 待访问节点
		*/
		virtual void Visit( Node* node ){ }; 

	protected:
		typedef Util::LinkListT<LexerSys::Token> PathToks;
		LexerSys::SearchPath m_path;		///>搜索路径
		Node* m_lp_final_search_node;		///>当前节点
		Util::String m_result_output_str;	///>获得访问结果字符串
	};

}//namespace FileSys

#endif //ZP_NODEVISITOR