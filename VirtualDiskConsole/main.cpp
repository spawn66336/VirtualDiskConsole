
#include <iostream>
#include "String.h"
#include "LinkList.h"
#include "Stack.h"
#include "Queue.h" 
#include "Lexer.h"
#include <atlstr.h>
#include "VirtualDiskConsole.h"
#include <conio.h>
#include "FileSystem.h"
 
#pragma warning(disable:4786)



void PrintWelcomeHead(void)
{
	for( int i = 0 ; i < 70 ; i++ )
	{
		std::cout<<"*";
	} 
	std::cout<<std::endl; 
	std::cout<<"*"<<std::endl; 
	std::cout<<"*"<<"          "<<"虚拟磁盘系统"<<std::endl; 
	std::cout<<"*"<<std::endl;  
	for( int i = 0 ; i < 70 ; i++ )
	{
		std::cout<<"*";
	}
	std::cout<<std::endl;
}

void PrintBackspace(void)
{
	std::cout<<'\b';
	std::cout<<' ';
	std::cout<<'\b';
}
int main(void)
{ 
	using namespace Util;
	using namespace std;
	using namespace LexerSys;

	setlocale(LC_ALL,"");

	PrintWelcomeHead();

	VirtualDiskConsole::CreateInstance();
	VirtualDiskConsole::GetInstance()->Init();

	{//预加载命令
		VirtualDiskConsole::GetInstance()->AddCommand("copy C:\\drivers\\win\\camera\\* drivers");
		VirtualDiskConsole::GetInstance()->AddCommand("cd drivers");
	}
	 
	char *pmb = (char *)malloc( MB_CUR_MAX );

	while( 1 )
	{
		Util::String cmd_str;
		wint_t input_c = 0;

		VirtualDiskConsole::GetInstance()->ExecuteCommandQueue();
		VirtualDiskConsole::GetInstance()->PrintPrompt(); 
		 

		//只要用户没有按回车键
		while( ( input_c=  _getwch() ) != 13 )
		{ 

			//若为退格键
			if( input_c == 8 )
			{
				if( cmd_str.Length() )
				{
					cmd_str.PopBack();
					PrintBackspace();
				}
			}else{    
				_putwch( input_c ); 

				int size_convert = 0;
				wctomb_s( &size_convert , pmb , MB_CUR_MAX , input_c );
				for( int i = 0 ; i < size_convert ; i++ )
				{
					cmd_str.Append( pmb[i] );  
				}
			} 
		}
		std::cout<<std::endl;

		if( cmd_str.Length() == 0 )
		{
			continue;;
		} 

		Util::String special_cmd = cmd_str;

		special_cmd.ClearAllWhiteChars();
		special_cmd.ConvertToLowercast();

		if( special_cmd == "exit" )
		{
			std::cout<<"退出系统!"<<std::endl;
			break;
		}else if( special_cmd == "show_volume"){

			double used_size_bytes = static_cast<double>( FileSys::FileSystem::GetInstance()->TotalSize() ) / ( 1024.0f*1024.0f );
			double virtualdisk_capacity =  static_cast<double>( FileSys::FileSystem::GetInstance()->Capacity() ) / ( 1024.0f*1024.0f );

			std::cout<<"已使用空间："<<used_size_bytes<<"MB"<<endl;
			std::cout<<"总空间："<<virtualdisk_capacity<<"MB"<<endl;
			std::cout<<"已使用了："<<( used_size_bytes/virtualdisk_capacity)*100.0f<<"%"<<endl;
			continue;
		}

		VirtualDiskConsole::GetInstance()->ExecuteCommand( cmd_str );
		VirtualDiskConsole::GetInstance()->PrintResult();
	}
	
	free( pmb );
	pmb = NULL;

	VirtualDiskConsole::GetInstance()->Destroy();
	VirtualDiskConsole::DestroyInstance();

	 
}