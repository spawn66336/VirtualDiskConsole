#ifndef ZP_CONSOLECOMMAND
#define ZP_CONSOLECOMMAND
#include "ZPDependency.h"
#include "Token.h"
#include "Node.h"
#include "SearchPath.h"

namespace CommandSys
{

class ConsoleCommand
{
public:
	ConsoleCommand(void);
	virtual ~ConsoleCommand(void);

	/**
	* @brief 设置当前路径
	* @param curr_path 当前路径字符串
	*/
	void SetCurrPath( const Util::String& curr_path ); 

	/**
	* @brief 设置当前命令用户所输入的参数列表
	* @param params 用户输入的参数列表
	*/
	void SetParamToks( const Util::LinkListT<LexerSys::Token>& params );

	/**
	* @brief 将路径加入命令的路径列表
	* @param path 要加入的路径
	*/
	void AddPath( const LexerSys::SearchPath& path );

	/**
	* @brief 设置当前命令的路径列表
	* @param paths 要设置的路径列表
	*/
	void SetPaths( const Util::LinkListT<LexerSys::SearchPath>& paths );

	/**
	* @brief 判断用户输入的路径中是否有超过限定长度的路径
	*/
	bool IsPathLengthOutOfLimit(void) const;

	/**
	* @brief 执行命令
	* @remark 子类需重写该函数
	*/
	virtual void Execute( void ){} 

	/**
	* @brief 获得结果输出
	*/
	Util::String GetResultOutput( void );

	/**
	* @brief 获得当前路径字符串
	*/
	Util::String GetCurrPath(void);

	virtual void DeleteThis(void){ delete this; }

protected:

	/**
	* @brief 根据当前路径查找文件系统中对应的文件夹节点
	* @return 指向找到的当前路径节点指针
	*/
	FileSys::Node* SearchCurrPathNode(void);

	/**
	* @brief 获得指定路径的文件系统节点
	* @return 指向找到路径节点的指针
	* @retval NULL 查找失败，文件系统中没有该路径所表示的节点
	* @retval not NULL 查找成功
	*/
	FileSys::Node* SearchNodeByPath(  const LexerSys::SearchPath& path );

protected:  
	LexerSys::SearchPath m_curr_path;										///>当前路径
	Util::LinkListT<LexerSys::Token> m_params;							///>参数列表
	Util::LinkListT<LexerSys::SearchPath> m_paths;					///>路径列表
	Util::String m_result_output;													///>输出结果字符串
};

}//namespace CommandSys

#endif//ZP_CONSOLECOMMAND