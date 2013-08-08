#include "FolderNode.h"

namespace FileSys
{



FolderNode::FolderNode(void)
{
}


FolderNode::~FolderNode(void)
{
}

void FolderNode::GetFileListOutputString(  Util::String& output , const bool recursive  , const bool folder_only  ) const
{
	Util::String folder_tag_str = "<DIR>"; 
	Util::String file_tag_str = "<FILE>";
	output.Append( Util::StringFormat("%s µÄÄ¿Â¼\n\n" , PathName() ) );
	for( int i = 0 ; i < m_child_nodes.Count() ; i++ )
	{
		Util::String tag_str;
		FileSys::Node* lp_child_node = m_child_nodes.At( i );
		if( lp_child_node->IsFile() )
		{
			if( !folder_only )
			{
				output.Append( Util::StringFormat( "%-10s %-20s\n" , "<FILE>"  ,lp_child_node->Name().Ptr() ) ); 
			} 
		}else{
			output.Append( Util::StringFormat( "%-10s %-20s\n" , "<DIR>"  ,lp_child_node->Name().Ptr() ) ); 
		}  
			
	}

	if( recursive )
	{
		for( int i = 0 ; i < m_child_nodes.Count() ; i++ )
		{ 
			FileSys::Node* lp_child_node = m_child_nodes.At( i ); 
			if( lp_child_node->IsFolder() )
			{
				lp_child_node->GetFileListOutputString( output , recursive );
			}
		}
	}//if( recursive )
}


}//namespace FileSys