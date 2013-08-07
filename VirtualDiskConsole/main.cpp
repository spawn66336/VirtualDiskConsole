
#include <iostream>
#include "String.h"
#include "LinkList.h"
#include "Stack.h"
#include "Queue.h" 
#include "Lexer.h"

bool String_Compare_Test(void)
{ 
	bool pass = true;

	ZPUTIL::StringA str1 = "hello world";
	ZPUTIL::StringA str2 = "hello world";
	ZPUTIL::StringA str3 = "Hello World";

	if( !( str1 == str2 ) )
	{
		pass = false;
	}

	if( str1 == str3 )
	{
		pass =false;
	}

	if( str1.Compare( str3 ) == 0 )
	{
		pass = false;
	}

	if( str1.Compare( str3 , true ) != 0 )
	{
		pass =false;
	}

	return pass; 
}

bool String_Find_Test(void)
{
	ZPUTIL::StringA str = "hello world"; 
	ZPUTIL::StringA str1 = "#nihao#";
	ZPUTIL::StringA str2 = "#dajiahao#";
	ZPUTIL::StringA final_str = str + str1 + str2;

	std::vector<ZPUTIL::StringA> find_strs;
	std::vector<int> start_points;

	find_strs.push_back("dajia");
	start_points.push_back(3);

	find_strs.push_back("da_jia");
	start_points.push_back(3);

	find_strs.push_back("dajia");
	start_points.push_back(31);

	find_strs.push_back("dajia");
	start_points.push_back(32);

	find_strs.push_back("");
	start_points.push_back(32);
	 
	for( int i = 0 ; i < find_strs.size() ; i++ )
	{
		std::cout<<"查找"<<find_strs.at(i)<<"在"<<start_points.at(i)<<"处"<<": "<<final_str.Find( find_strs.at(i) , start_points.at(i) )<<std::endl; 
	}

	return true;
}

void StringTest(void)
{
	ZPUTIL::StringA str = "hello world";
	std::cout<<str<<std::endl;
	str += "_hello world";
	std::cout<<str<<std::endl;
	ZPUTIL::StringA str1 = "#nihao#";
	ZPUTIL::StringA str2 = "#dajiahao#";
	ZPUTIL::StringA final_str = str + str1 + str2;
	std::cout<<final_str<<std::endl; 

	if( String_Compare_Test() )
	{
		std::cout<<"字符串比较测试通过!"<<std::endl;
	}else{
		std::cout<<"字符串比较测试失败!"<<std::endl;
	}

	String_Find_Test();

	final_str.Insert( "#insert#" , 0 );
	std::cout<<final_str<<std::endl;
	final_str.Insert( "#insert#" , final_str.Length() );
	std::cout<<final_str<<std::endl;
	final_str.Insert( "#insert#" , 10 );
	std::cout<<final_str<<std::endl;
	final_str.Insert( "#insert#" , -1 );
	std::cout<<final_str<<std::endl;
	final_str.Insert( "#insert#" , final_str.Length()+1 );
	std::cout<<final_str<<std::endl;
	final_str.Insert( "" , 3 );
	std::cout<<final_str<<std::endl;
	final_str.Insert( "" , 0 );
	std::cout<<final_str<<std::endl;
	final_str.Insert( "" ,  final_str.Length()+1 );
	std::cout<<final_str<<std::endl;

	final_str.Delete( 0 , strlen("#insert#") );
	std::cout<<final_str<<std::endl;

	final_str.Replace("#insert#" , "#replace#" , 0 );
	std::cout<<final_str<<std::endl;
	final_str.Replace("#" ,"@@" , 0 );
	std::cout<<final_str<<std::endl;
	final_str.Replace("@@" ,"" , 0 );
	std::cout<<final_str<<std::endl;
	final_str.Replace("" ,"%%" , 0 );
	std::cout<<final_str<<std::endl;

	ZPUTIL::StringA str_include_spaces = "		hello world   ";
	str_include_spaces.Trim();
	std::cout<<str_include_spaces<<std::endl;
	ZPUTIL::StringA str_total_spaces = "					       \n ";
	str_total_spaces.Trim();
	std::cout<<str_total_spaces;
	ZPUTIL::StringA str_include_spaces2 = "		h e ll o w o r l d     ";
	str_include_spaces2.ClearAllWhiteChars();
	std::cout<<str_include_spaces2<<std::endl;
	str_total_spaces = "					       \n ";
	str_total_spaces.ClearAllWhiteChars();
	std::cout<<str_total_spaces<<std::endl;

}

int main(void)
{ 
	using namespace ZPUTIL;
	using namespace std;
	using namespace Lexer_Sys;

	Lexer lex;
	lex.SetString(L"cd /ad  /s /s C:\\abs\\ C:\\a/bs\\final.txt D:\\cdbsadf bcsdf\\*.*\\*.txt");
	lex.Analysis();
	lex.Clear();



	//LinkListT<int> ints;
	//for( int i = 1 ; i <= 100 ; i++ )
	//{
	//	//ints.PushBack( i );
	//	ints.PushFront( i );
	//}

	//LinkListT<int>::Iterator it = ints.Begin();
	//while( it.HasNext() )
	//{
	//	cout<<it.Next()<<endl;
	//}

	//ints.Clear();

	//ints.PushBack( 1 );
	//ints.PushBack( 2 );
	//ints.PushBack( 3 );

	//it = ints.Begin();
	//while( it != ints.End() )
	//{
	//	it = ints.Erase( it );
	//}


	
}