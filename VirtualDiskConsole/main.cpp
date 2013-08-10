
#include <iostream>
#include "String.h"
#include "LinkList.h"
#include "Stack.h"
#include "Queue.h" 
#include "Lexer.h"
#include <atlstr.h>
#include "VirtualDiskConsole.h"
#include <conio.h>
 
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


		Util::String exit_test_str = cmd_str;

		exit_test_str.ClearAllWhiteChars();
		exit_test_str.ConvertToLowercast();
		if( exit_test_str == "exit" )
		{
			std::cout<<"退出系统!"<<std::endl;
			break;
		}

		VirtualDiskConsole::GetInstance()->ExecuteCommand( cmd_str );
		VirtualDiskConsole::GetInstance()->PrintResult();
	}
	
	free( pmb );
	pmb = NULL;

	VirtualDiskConsole::GetInstance()->Destroy();
	VirtualDiskConsole::DestroyInstance();

	 
}