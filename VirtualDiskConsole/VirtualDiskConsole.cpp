#include "VirtualDiskConsole.h"
#include "ConsoleCommandFactory.h"
#include "ConsoleCommand.h"
#include "FileSystem.h"
 
VirtualDiskConsole::VirtualDiskConsole(void)
{
	m_curr_path = "C:\\";
}
 
VirtualDiskConsole::~VirtualDiskConsole(void)
{
}

Util::String VirtualDiskConsole::GetCurrPath( void ) const
{
	return m_curr_path;
}

void VirtualDiskConsole::ExecuteCommand( const Util::String& cmd )
{
	CommandSys::ConsoleCommand* lp_cmd = 
		CommandSys::ConsoleCommandFactory::GetInstance()->CreateCommand( m_curr_path , cmd );

	if( NULL != lp_cmd )
	{
		lp_cmd->Execute();
		m_curr_path = lp_cmd->GetCurrPath();
		m_result_output = lp_cmd->GetResultOutput();
		lp_cmd->DeleteThis();
		lp_cmd = NULL;
	}else{
		std::cout<<"不是内部命令!"<<std::endl;
	} 
}

void VirtualDiskConsole::AddCommand( const Util::String& cmd )
{
	m_cmd_queue.Enqueue( cmd );
}

void VirtualDiskConsole::ExecuteCommandQueue( void )
{
	int cmd_count = 0;
	while( m_cmd_queue.Size() )
	{
		cmd_count++;
		std::cout<<m_cmd_queue.Front()<<std::endl;
		ExecuteCommand( m_cmd_queue.Front() );
		m_cmd_queue.Dequeue();
	}

	if( cmd_count )
	{
		std::cout<<"总共执行了"<<cmd_count<<"个命令!"<<std::endl;
	}
}

void VirtualDiskConsole::Init( void )
{
	FileSys::FileSystem::CreateInstance();
	CommandSys::ConsoleCommandFactory::CreateInstance();

	//创建实验用目录树
	FileSys::FileSystem::GetInstance()->BuildTestFileTree();
}

void VirtualDiskConsole::Destroy( void )
{
	CommandSys::ConsoleCommandFactory::DestroyInstance();
	FileSys::FileSystem::DestroyInstance();
}

void VirtualDiskConsole::PrintResult( void )
{
	std::cout<<m_result_output<<std::endl;
	m_result_output.Empty();
}

void VirtualDiskConsole::PrintPrompt( void )
{
	std::cout<<m_curr_path<<">";
}


