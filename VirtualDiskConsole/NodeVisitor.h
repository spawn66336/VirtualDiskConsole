#ifndef ZP_NODEVISITOR
#define ZP_NODEVISITOR

#include "ZPDependency.h"
#include "Token.h"

namespace FileSys
{
	class Node;

	class NodeVisitor
	{
	public:
	 
		NodeVisitor( void );
		virtual ~NodeVisitor( void ); 

		virtual void SetPathToks( const Util::LinkListT<LexerSys::Token>& toks );

		virtual LexerSys::Token GetCurrPathToken( void ) const;

		virtual bool HasNextToken( void ) const;

		virtual void MoveToNextToken( void );

		virtual Node* GetSearchNode(void);

		virtual void Visit( Node* node ){ }; 

	protected:
		typedef Util::LinkListT<LexerSys::Token> PathToks;
		PathToks::Iterator m_curr_tok;		///>路径当前符号
		PathToks m_path_toks;					///>路径符号列表
		Node* m_lp_final_search_node;						///>当前节点
	};

}//namespace FileSys

#endif //ZP_NODEVISITOR