#ifndef ZP_VIRTUALDISKCONSOLE
#define ZP_VIRTUALDISKCONSOLE

#include "ZPDependency.h"

class VirtualDiskConsole : public Util::SingletonT<VirtualDiskConsole>
{
public:
	VirtualDiskConsole(void);
	virtual ~VirtualDiskConsole(void);

	void Init(void);
	void Destroy(void);
	Util::String GetCurrPath( void ) const;
	void ExecuteCommand( const Util::String& cmd );
	void AddCommand( const Util::String& cmd );
	void ExecuteCommandQueue( void );
	void PrintResult(void);
	void PrintPrompt(void);

private: 
	Util::String m_curr_path;
	Util::QueueT<Util::String> m_cmd_queue; 
	Util::String m_result_output;
};

#endif