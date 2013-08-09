#include "FileSystem.h"
#include "FolderNode.h"

namespace FileSys
{  
	FileSystem::FileSystem( void ):
	m_lp_root(NULL)
	{
		m_lp_root = new FolderNode;
		m_lp_root->CreateNode("C:" , Node::FOLDER_NODE ); 
	}

	FileSystem::~FileSystem( void )
	{
		m_lp_root->DeleteThis();
		m_lp_root = NULL;
	}

	void FileSystem::Accept( NodeVisitor* visitor )
	{
		ZP_ASSERT( NULL != visitor );

		if( NULL !=  visitor )
		{
			m_lp_root->Accept( visitor );
		}
	}

	void FileSystem::BuildTestFileTree( void )
	{
		Node* lp_drive_node = m_lp_root->FindNode("C:");
		Node* lp_drivers_node = lp_drive_node->CreateNode("Drivers" , Node::FOLDER_NODE );
		Node* lp_Nvidia_node = lp_drive_node->CreateNode("NVIDIA" , Node::FOLDER_NODE );
		Node* lp_PerfLogs_node = lp_drive_node->CreateNode("PerfLogs" , Node::FOLDER_NODE );
		Node* lp_ProgramFiles_node = lp_drive_node->CreateNode("Program Files" , Node::FOLDER_NODE );
		
		lp_drivers_node->CreateNode("1" , Node::FOLDER_NODE );
		lp_drivers_node->CreateNode("2" , Node::FOLDER_NODE );
		lp_drivers_node->CreateNode("Hello World" , Node::FOLDER_NODE ); 
		lp_drivers_node->CreateNode("1.txt" , Node::FILE_NODE );
		lp_drivers_node->CreateNode("3" , Node::FILE_NODE );
	}

	 

}//namespace FileSys