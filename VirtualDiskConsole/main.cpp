
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

	PrintWelcomeHead();

	VirtualDiskConsole::CreateInstance();
	VirtualDiskConsole::GetInstance()->Init();

	while( 1 )
	{
		Util::String cmd_str;
		int input_c = 0;

		VirtualDiskConsole::GetInstance()->PrintPrompt(); 
		//只要用户没有按回车键
		while( ( input_c=  _getch() ) != 13 )
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
				_putch( input_c );
				cmd_str.Append( static_cast<char>( input_c ) );
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

	VirtualDiskConsole::GetInstance()->Destroy();
	VirtualDiskConsole::DestroyInstance();

	 
}