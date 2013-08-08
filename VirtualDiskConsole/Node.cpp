#include "Node.h"
#include "FileNode.h"
#include "FolderNode.h"
#include "NodeVisitor.h"

namespace FileSys
{ 
	FileSys::Node::Node():
	m_name(), 
	m_lp_parent(NULL)
	{ 
	}

	FileSys::Node::~Node()
	{ 
		this->Destroy();
	}

	Node* FileSys::Node::FindNode( const ZPUTIL::String& name )
	{
		if( this->IsFile() )
		{
			return NULL;
		}

		ZPUTIL::LinkListT<Node*>::Iterator it = m_child_nodes.Begin();
		while( it != m_child_nodes.End() )
		{
			if( (*it)->Name() == name )
			{
				return (*it);
			}
			it.Next();
		}
		return NULL;
	}

	Node* FileSys::Node::CreateNode( const ZPUTIL::String& name , const NodeType type  )
	{
		if( this->IsFile() )
		{
			return NULL;
		}

		Node* lp_node = FindNode( name );

		if( NULL == lp_node )
		{
			switch( type )
			{
			case FILE_NODE:
				ZP_SAFE_NEW( lp_node , FileNode );
				break;
			case FOLDER_NODE:
				ZP_SAFE_NEW( lp_node , FolderNode );
				break;
			default:
				break;
			}

			ZP_ASSERT( NULL != lp_node ); 
			lp_node->Parent( this );
			lp_node->Name( name ); 
			m_child_nodes.PushBack( lp_node );
		} 
		return lp_node;
	}

	bool Node::DeleteNode( const ZPUTIL::String& name  )
	{
		if( this->IsFile() )
		{
			return false;
		}

		ZPUTIL::LinkListT<Node*>::Iterator it = m_child_nodes.Begin();
		while( it != m_child_nodes.End() )
		{
			if( (*it)->Name() == name )
			{
				(*it)->DeleteThis();
				m_child_nodes.Erase( it );
				return true;
			}
			it.Next();
		}
		return false;
	}

	void Node::Destroy( void )
	{ 
		m_lp_parent = NULL;
		if( m_child_nodes.Count() )
		{ 
			ZPUTIL::LinkListT<Node*>::Iterator it = m_child_nodes.Begin();
			while( it != m_child_nodes.End() )
			{
				(*it)->DeleteThis();
				it.Next();
			}
			m_child_nodes.Clear(); 
		}//if( m_child_nodes.Count() )
	}

	void Node::Accept( NodeVisitor* visitor )
	{
		ZP_ASSERT( NULL != visitor );
		visitor->Visit( this );
	} 
}
