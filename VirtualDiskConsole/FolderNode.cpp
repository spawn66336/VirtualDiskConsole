#include "FolderNode.h"

namespace FileSys
{



FolderNode::FolderNode(void)
{
}


FolderNode::~FolderNode(void)
{
}


DWORD FolderNode::CalcTotalSize( void )
{
	DWORD size = 0;
	Util::LinkListT<Node*>::Iterator it = m_child_nodes.Begin();
	while( it != m_child_nodes.End() )
	{
		size += (*it)->CalcTotalSize();
		it.Next();
	}
	return size;
}


void FolderNode::GetFileListOutputString(  Util::String& output , const bool recursive  , const bool folder_only  ) const
{ 
	int file_count = 0;
	int folder_count = 0;
	output.Append( Util::StringFormat("%s 的目录\n\n" , PathName() ) );

	if( !IsRoot() && !( Parent()->IsRoot() ) )
	{
		output.Append( Util::StringFormat( "%-10s %-20s\n" , "<DIR>"  , ".") );
		output.Append( Util::StringFormat( "%-10s %-20s\n" , "<DIR>"  , "..") );
	}

	for( int i = 0 ; i < m_child_nodes.Count() ; i++ )
	{
		Util::String tag_str;
		FileSys::Node* lp_child_node = m_child_nodes.At( i );
		if( lp_child_node->IsFile() )
		{
			file_count++;
			if( !folder_only )
			{
				output.Append( Util::StringFormat( "%-10s%10d  %-20s\n" , "<FILE>" , lp_child_node->Size()  ,lp_child_node->Name().Ptr() ) ); 
			} 
		}else{
			folder_count++;
			output.Append( Util::StringFormat( "%-10s%-10s  %-20s\n" , "<DIR>" ,""  ,lp_child_node->Name().Ptr() ) ); 
		}   
	}
	output.Append( Util::StringFormat( "%10d个文件\n"  , file_count ) );
	output.Append( Util::StringFormat( "%10d个目录\n"  , folder_count ) );

	if( recursive )
	{
		for( int i = 0 ; i < m_child_nodes.Count() ; i++ )
		{ 
			FileSys::Node* lp_child_node = m_child_nodes.At( i ); 
			if( lp_child_node->IsFolder() )
			{
				lp_child_node->GetFileListOutputString( output , recursive , folder_only );
			}
		}
	}//if( recursive )
}


}//namespace FileSys