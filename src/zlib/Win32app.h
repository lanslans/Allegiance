//////////////////////////////////////////////////////////////////////////////
//
// Win32 Application
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _Win32App_h_
#define _Win32App_h_

//#include <cstdint>
#include "..\Inc\int_types.h" //BBT
class ExceptionData {
public:
    EXCEPTION_RECORD *ExceptionRecord;
    CONTEXT          *ContextRecord;
};

class Win32App : public IObject {
protected:
    __declspec(dllexport) Win32App();

public:
    __declspec(dllexport) virtual ~Win32App();

    static  void    Exit(int value);

    virtual HRESULT Initialize(const ZString& strCommandLine);
    virtual void    Terminate();
    virtual int     OnException(DWORD code, ExceptionData* pdata);

    virtual void    DebugOutput(const char *psz);
    virtual bool    OnAssert(const char* psz, const char* pszFile, int line, const char* pszModule);
    virtual void    OnAssertBreak();

	//imago 6/10
	virtual bool EnforceFilter(bool bEnforce);

	virtual bool WriteMemory(uint8_t* pTarget, const uint8_t* pSource, uint32_t Size);
	static int GenerateDump(EXCEPTION_POINTERS* pExceptionPointers);
	static LONG __stdcall ExceptionHandler(EXCEPTION_POINTERS* pep);
};

#endif
