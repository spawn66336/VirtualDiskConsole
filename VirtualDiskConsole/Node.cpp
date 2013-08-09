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

	Util::String Node::PathName( void ) const
	{
		if( IsRoot() || Parent()->IsRoot() )
		{
			return m_name;
		}
		 
		return Parent()->PathName() + "\\" +  m_name;
	}

	Node* FileSys::Node::FindNode( const Util::String& name )
	{
		if( this->IsFile() )
		{
			return NULL;
		}

		Util::LinkListT<Node*>::Iterator it = m_child_nodes.Begin();
		while( it != m_child_nodes.End() )
		{
			if( 0 == (*it)->Name().ICmp(name) )
			{
				return (*it);
			}
			it.Next();
		}
		return NULL;
	}


	bool Node::IsAncestor( Node* node )
	{
		Node* lp_parent_node = Parent();
		while(
				NULL != lp_parent_node &&
			   lp_parent_node != node 
			   )
		{
			lp_parent_node = lp_parent_node->Parent();
		}

		if( lp_parent_node )
		{
			return true;
		}
		return false;
	}


	Node* FileSys::Node::CreateNode( const Util::String& name , const NodeType type  )
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

	bool Node::DeleteNode( const Util::String& name  )
	{
		if( this->IsFile() )
		{
			return false;
		}

		Util::LinkListT<Node*>::Iterator it = m_child_nodes.Begin();
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


	void Node::DeleteNodeByType( const NodeType type )
	{
		if( this->IsFile() )
		{
			return;
		}

		Util::LinkListT<Node*>::Iterator it = m_child_nodes.Begin();
		while( it != m_child_nodes.End() )
		{
			switch( type )
			{
			case FILE_NODE:
				if( (*it)->IsFile() )
				{
					(*it)->DeleteThis(); 
					it = m_child_nodes.Erase( it ); 
					continue;
				}
				break;
			case FOLDER_NODE:
				if( (*it)->IsFolder() )
				{
					(*it)->DeleteThis();
					it = m_child_nodes.Erase( it ); 
					continue;
				}
				break;
			default:
				break;
			} 

			it.Next();
		}//while( it != m_child_nodes.End() )
	}

	void Node::Destroy( void )
	{ 
		m_lp_parent = NULL;
		if( m_child_nodes.Count() )
		{ 
			Util::LinkListT<Node*>::Iterator it = m_child_nodes.Begin();
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

	void Node::GetFileListOutputString(  Util::String& output , const bool recursive  , const bool folder_only  ) const
	{

	}
	 



}
