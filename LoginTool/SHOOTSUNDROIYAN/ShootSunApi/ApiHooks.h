// ApiHooks.h - constants and structures for ApiHooks

#ifndef _APIHOOKS_
#define _APIHOOKS_ 1


// Core constants and structures

//Return values--------------------------------------
 #define   ErrorAHMin        (0xE1C2F3B1)
 #define   ErrorAHException  (ErrorAHMin+0)
 #define   ErrorAHOpen       (ErrorAHMin+1)
 #define   ErrorAHPrepare    (ErrorAHMin+2)
 #define   ErrorAHTimeOut    (ErrorAHMin+3)
 #define   ErrorAHRemote     (ErrorAHMin+4)
 #define   ErrorAHMax        (ErrorAHMin+4)

 #define   ErrorAMMin        ErrorAHMin
 #define   ErrorAMModule     (ErrorAHMax+1)
 #define   ErrorAMApi        (ErrorAHMax+2)
 #define   ErrorAMMax        (ErrorAHMax+2)

 #define   ErrorAWSuccess    (0xE1C2F3B0)
//---------------------------------------------------


//RCFlags--------------------------------------------
 #define   RC_FL_OWNTIMEOUT  1
 #define   RC_FL_TERMINATE   2
 #define   RC_FL_OWNFREE     4
 #define   RC_FL_UNHIDE9X    8
 #define   RC_FL_DEFSD       16

//RC constants:
 #define   RCBlockStart      0xAC
 #define   RCThreadBodyAlias 0xE1C2F3AF

//ProcFlags------------------------------------------
 #define   RC_PF_DEBUGGED    1
 #define   RC_PF_16TERM      2
 #define   RC_PF_NOOPEN      4
 #define   RC_PF_NATIVE      8
 #define   RC_PF_NOTINITED   16

//RCINFO---------------------------------------------
 typedef   struct _RCINFO {
  DWORD    RCFlags;
  DWORD    ProcFlags;
  LPVOID   (WINAPI *RtlAllocMem)(HANDLE, DWORD);
  BOOL     (WINAPI *RtlFreeMem)(HANDLE, LPVOID);
  HANDLE   hProcess;
  DWORD    ProcessId;
  HANDLE   hThread;
  DWORD    ThreadId;
  LPVOID   ThreadBody;
  LPVOID   ThreadStack;
 } RCINFO, *PRCINFO;


//ModWorks.LoadAndCall flags---------------------------------------
 #define  LAC_PASCAL       0x80000000
 #define  LAC_FASTCALL     0x40000000
 #define  LAC_COMCALL      0x20000000
 #define  LAC_DELPHI       0x10000000

//ModWorks.LoadAndCall constants:
 #define  LACThreadBodyAlias 0xE1C2F3AF
 #define  LACSTKPointer      0xE1C2E700
 #define  LACMEMPointer      0xE1C2DA00
 #define  LACMEMOffset       0x3DC
 #define  LACMEMSize         0xC24
 #define  LACMaxArgs         0x309
//------------------------------------------------------


// ApiWorks constants and structures

//dwFlags-----------------------------------------------
 #define  HOOK_EXPORT      1
 #define  HOOK_BY_NAME     2
 #define  HOOK_BY_ADDRESS  4
 #define  HOOK_HARD        8
 #define  HOOK_LOAD_IMPORT 16
 #define  HOOK_SPECIAL     32
 #define  HOOK_NOT_NT      64
 #define  HOOK_NOT_9X      128
 #define  HOOK_OVERWRITE   256
 #define  HOOK_RAW         512
 #define  HOOK_ALL_SAFE    1024
 #define  HOOK_LOAD_EXPORT 2048

//ModuleExport------------------------------------------
 #define  HOOKS_END        ((LPCSTR)-1)
 #define  HOOKS_DYNAMIC    ((LPCSTR)-2)
//ModuleExport or ModuleImport--------------------------
 #define  MAIN_MODULE      ((LPCSTR)0)
//ModuleImport------------------------------------------
 #define  ALL_MODULES      ((LPCSTR)-1)


//UnhookApis--------------------------------------------
 #define  WHOLE_AH_CHAIN   (-1)


 typedef struct  _ADDR_CONTENTS {
  DWORD         *ReturnWhere;
  DWORD          ReturnWhat;
 } ADDR_CONTENTS, *PADDR_CONTENTS;

 typedef  struct _API_UNHOOK {
  DWORD          MaxNoAddr;
  DWORD          CurNoAddr;
  PADDR_CONTENTS WhereWhat; 
 } API_UNHOOK, *PAPI_UNHOOK;

 typedef struct  _API_HOOK {
  LPCSTR       ModuleExport;
  LPCSTR       ApiNameOrOrd;
  DWORD        dwFlags;
  LPCVOID      ModuleImport;
  PAPI_UNHOOK  UnhookAddresses;
  LPCVOID      HookAddress;
 } API_HOOK, *PAPI_HOOK;


//Protos--------------------------------------------

#ifdef __TURBOC__
  #ifdef __cplusplus
    #define __EXPORT extern "C" __declspec(dllexport)
  #else
    #define __EXPORT __declspec(dllexport)
  #endif
  #ifdef AH_STATIC_LINKING
    #ifdef __cplusplus
      #define __XTRN194 extern "C"
    #else
      #define __XTRN194 extern
    #endif
    __XTRN194 DWORD __stdcall  _EstablishApiHooksA(PRCINFO pRCI, LPCSTR  lpszDll, DWORD ProcessId, LONG dwMilliseconds);
    __XTRN194 DWORD __stdcall _hEstablishApiHooksA(PRCINFO pRCI, LPCSTR  lpszDll, HANDLE hProcess, LONG dwMilliseconds);
    __XTRN194 DWORD __stdcall  _EstablishApiHooksW(PRCINFO pRCI, LPCWSTR lpszDll, DWORD ProcessId, LONG dwMilliseconds);
    __XTRN194 DWORD __stdcall _hEstablishApiHooksW(PRCINFO pRCI, LPCWSTR lpszDll, HANDLE hProcess, LONG dwMilliseconds);

    __XTRN194 DWORD __stdcall     _IsModuleLoadedA(PRCINFO pRCI, LPCSTR  lpszDll, DWORD ProcessId, LONG dwMilliseconds);
    __XTRN194 DWORD __stdcall    _hIsModuleLoadedA(PRCINFO pRCI, LPCSTR  lpszDll, HANDLE hProcess, LONG dwMilliseconds);
    __XTRN194 DWORD __stdcall     _IsModuleLoadedW(PRCINFO pRCI, LPCWSTR lpszDll, DWORD ProcessId, LONG dwMilliseconds);
    __XTRN194 DWORD __stdcall    _hIsModuleLoadedW(PRCINFO pRCI, LPCWSTR lpszDll, HANDLE hProcess, LONG dwMilliseconds);

    __XTRN194 DWORD __stdcall       _UnloadModuleA(PRCINFO pRCI, LPCSTR  lpszDll, DWORD ProcessId, LONG dwMilliseconds, DWORD HowManyTimes);
    __XTRN194 DWORD __stdcall      _hUnloadModuleA(PRCINFO pRCI, LPCSTR  lpszDll, HANDLE hProcess, LONG dwMilliseconds, DWORD HowManyTimes);
    __XTRN194 DWORD __stdcall       _UnloadModuleW(PRCINFO pRCI, LPCWSTR lpszDll, DWORD ProcessId, LONG dwMilliseconds, DWORD HowManyTimes);
    __XTRN194 DWORD __stdcall      _hUnloadModuleW(PRCINFO pRCI, LPCWSTR lpszDll, HANDLE hProcess, LONG dwMilliseconds, DWORD HowManyTimes);

    __XTRN194 DWORD __stdcall        _LoadAndCallA(PRCINFO pRCI, LPCSTR  lpszDll, DWORD ProcessId, LONG dwMilliseconds, DWORD HowManyTimes, LPCSTR  ApiNameOrOrd, DWORD nArgs, LPVOID pArgs);
    __XTRN194 DWORD __stdcall       _hLoadAndCallA(PRCINFO pRCI, LPCSTR  lpszDll, HANDLE hProcess, LONG dwMilliseconds, DWORD HowManyTimes, LPCSTR  ApiNameOrOrd, DWORD nArgs, LPVOID pArgs);
    __XTRN194 DWORD __stdcall        _LoadAndCallW(PRCINFO pRCI, LPCWSTR lpszDll, DWORD ProcessId, LONG dwMilliseconds, DWORD HowManyTimes, LPCWSTR ApiNameOrOrd, DWORD nArgs, LPVOID pArgs);
    __XTRN194 DWORD __stdcall       _hLoadAndCallW(PRCINFO pRCI, LPCWSTR lpszDll, HANDLE hProcess, LONG dwMilliseconds, DWORD HowManyTimes, LPCWSTR ApiNameOrOrd, DWORD nArgs, LPVOID pArgs);

    __XTRN194 DWORD __stdcall                        _RemoteExecute(PRCINFO pRCI, DWORD ProcessId, LONG dwMilliseconds, LPVOID lpBlock, DWORD BlockSize, LPVOID lpParameter);
    __XTRN194 DWORD __stdcall                       _hRemoteExecute(PRCINFO pRCI, HANDLE hProcess, LONG dwMilliseconds, LPVOID lpBlock, DWORD BlockSize, LPVOID lpParameter);

    __XTRN194 DWORD __stdcall _HookApiA(LPCSTR  ModuleExport, LPCSTR ApiNameOrOrd,  DWORD dwFlags, LPCVOID ModuleImport,  PAPI_UNHOOK ApiUnhook, LPVOID HookAddress, HANDLE ExcludeModules[]);
    __XTRN194 DWORD __stdcall _HookApiW(LPCWSTR ModuleExport, LPCWSTR ApiNameOrOrd, DWORD dwFlags, LPCVOID ModuleImport, PAPI_UNHOOK ApiUnhook, LPVOID HookAddress, HANDLE ExcludeModules[]);

    __XTRN194 DWORD __stdcall _CallOrigFn(LPCSTR ModuleExport, LPCSTR ApiNameOrOrd, DWORD dwFlags, LPCVOID OrigFn, PAPI_UNHOOK ApiUnhook, DWORD nArgs, LPVOID pArgs);

    __XTRN194 PRCINFO __stdcall _GetDefaultRCInfo(VOID);
    __XTRN194 BOOL  __stdcall _UnhookApis(PAPI_HOOK lpAHChain, LONG nAHooks);
    __XTRN194 DWORD __stdcall _GetProcFlags(DWORD ProcessId);
    __XTRN194 DWORD __stdcall _hGetProcFlags(HANDLE hProcess);

    #define  RemoteExecute        _RemoteExecute
    #define  GetDefaultRCInfo     _GetDefaultRCInfo
    #define  UnhookApis           _UnhookApis
    #define  GetProcFlags         _GetProcFlags
    #define  hGetProcFlags        _hGetProcFlags
    #define  CallOrigFn           _CallOrigFn

    #define  EstablishApiHooksA   _EstablishApiHooksA
    #define hEstablishApiHooksA  _hEstablishApiHooksA
    #define  IsModuleLoadedA      _IsModuleLoadedA
    #define hIsModuleLoadedA     _hIsModuleLoadedA
    #define  LoadAndCallA         _LoadAndCallA
    #define hLoadAndCallA        _hLoadAndCallA
    #define  UnloadModuleA        _UnloadModuleA
    #define hUnloadModuleA       _hUnloadModuleA
    #define  HookApiA             _HookApiA
    #define  EstablishApiHooksW   _EstablishApiHooksW
    #define hEstablishApiHooksW  _hEstablishApiHooksW
    #define  IsModuleLoadedW      _IsModuleLoadedW
    #define hIsModuleLoadedW     _hIsModuleLoadedW
    #define  LoadAndCallW         _LoadAndCallW
    #define hLoadAndCallW        _hLoadAndCallW
    #define  UnloadModuleW        _UnloadModuleW
    #define hUnloadModuleW       _hUnloadModuleW
    #define  HookApiW             _HookApiW
 
    #ifdef UNICODE
     #define  EstablishApiHooks   _EstablishApiHooksW
     #define hEstablishApiHooks  _hEstablishApiHooksW
     #define  IsModuleLoaded      _IsModuleLoadedW
     #define hIsModuleLoaded     _hIsModuleLoadedW
     #define  LoadAndCall         _LoadAndCallW
     #define hLoadAndCall        _hLoadAndCallW
     #define  UnloadModule        _UnloadModuleW
     #define hUnloadModule       _hUnloadModuleW
     #define  HookApi             _HookApiW
    #else
     #define  EstablishApiHooks   _EstablishApiHooksA
     #define hEstablishApiHooks  _hEstablishApiHooksA
     #define  IsModuleLoaded      _IsModuleLoadedA
     #define hIsModuleLoaded     _hIsModuleLoadedA
     #define  LoadAndCall         _LoadAndCallA
     #define hLoadAndCall        _hLoadAndCallA
     #define  UnloadModule        _UnloadModuleA
     #define hUnloadModule       _hUnloadModuleA
     #define  HookApi             _HookApiA
    #endif //#ifdef UNICODE
    #pragma comment(lib,"SbApiHooks.lib")
  #else
    #define __NORMAL0Q 1
    #ifdef __cplusplus
      #define __XTRN194  extern "C" __declspec(dllimport)
    #else
      #define __XTRN194  __declspec(dllimport)
    #endif
    #pragma comment(lib,"bApiHooks.lib")
  #endif //#ifdef AH_STATIC_LINKING
#else
#define __NORMAL0Q 1
#ifdef _MSC_VER
  #ifdef __cplusplus
    #define __EXPORT extern "C" __declspec(dllexport)
  #else
    #define __EXPORT __declspec(dllexport)
  #endif
  #ifdef AH_STATIC_LINKING
    #ifdef __cplusplus
      #define __XTRN194 extern "C"
    #else
      #define __XTRN194 extern
    #endif
    #pragma comment(lib,"SApiHooks")
  #else
    #ifdef __cplusplus
      #define __XTRN194  extern "C" __declspec(dllimport)
    #else
      #define __XTRN194  __declspec(dllimport)
    #endif
    #pragma comment(lib,"ApiHooks")
  #endif
#else
  #define __XTRN194
  #define __EXPORT
#endif //#ifdef _MSC_VER
#endif //#ifdef __TURBOC__

#ifdef __NORMAL0Q
 __XTRN194 DWORD __stdcall  EstablishApiHooksA(PRCINFO pRCI, LPCSTR  lpszDll, DWORD ProcessId, LONG dwMilliseconds);
 __XTRN194 DWORD __stdcall hEstablishApiHooksA(PRCINFO pRCI, LPCSTR  lpszDll, HANDLE hProcess, LONG dwMilliseconds);
 __XTRN194 DWORD __stdcall  EstablishApiHooksW(PRCINFO pRCI, LPCWSTR lpszDll, DWORD ProcessId, LONG dwMilliseconds);
 __XTRN194 DWORD __stdcall hEstablishApiHooksW(PRCINFO pRCI, LPCWSTR lpszDll, HANDLE hProcess, LONG dwMilliseconds);

 __XTRN194 DWORD __stdcall     IsModuleLoadedA(PRCINFO pRCI, LPCSTR  lpszDll, DWORD ProcessId, LONG dwMilliseconds);
 __XTRN194 DWORD __stdcall    hIsModuleLoadedA(PRCINFO pRCI, LPCSTR  lpszDll, HANDLE hProcess, LONG dwMilliseconds);
 __XTRN194 DWORD __stdcall     IsModuleLoadedW(PRCINFO pRCI, LPCWSTR lpszDll, DWORD ProcessId, LONG dwMilliseconds);
 __XTRN194 DWORD __stdcall    hIsModuleLoadedW(PRCINFO pRCI, LPCWSTR lpszDll, HANDLE hProcess, LONG dwMilliseconds);

 __XTRN194 DWORD __stdcall       UnloadModuleA(PRCINFO pRCI, LPCSTR  lpszDll, DWORD ProcessId, LONG dwMilliseconds, DWORD HowManyTimes);
 __XTRN194 DWORD __stdcall      hUnloadModuleA(PRCINFO pRCI, LPCSTR  lpszDll, HANDLE hProcess, LONG dwMilliseconds, DWORD HowManyTimes);
 __XTRN194 DWORD __stdcall       UnloadModuleW(PRCINFO pRCI, LPCWSTR lpszDll, DWORD ProcessId, LONG dwMilliseconds, DWORD HowManyTimes);
 __XTRN194 DWORD __stdcall      hUnloadModuleW(PRCINFO pRCI, LPCWSTR lpszDll, HANDLE hProcess, LONG dwMilliseconds, DWORD HowManyTimes);

 __XTRN194 DWORD __stdcall        LoadAndCallA(PRCINFO pRCI, LPCSTR  lpszDll, DWORD ProcessId, LONG dwMilliseconds, DWORD HowManyTimes, LPCSTR  ApiNameOrOrd, DWORD nArgs, LPVOID pArgs);
 __XTRN194 DWORD __stdcall       hLoadAndCallA(PRCINFO pRCI, LPCSTR  lpszDll, HANDLE hProcess, LONG dwMilliseconds, DWORD HowManyTimes, LPCSTR  ApiNameOrOrd, DWORD nArgs, LPVOID pArgs);
 __XTRN194 DWORD __stdcall        LoadAndCallW(PRCINFO pRCI, LPCWSTR lpszDll, DWORD ProcessId, LONG dwMilliseconds, DWORD HowManyTimes, LPCWSTR ApiNameOrOrd, DWORD nArgs, LPVOID pArgs);
 __XTRN194 DWORD __stdcall       hLoadAndCallW(PRCINFO pRCI, LPCWSTR lpszDll, HANDLE hProcess, LONG dwMilliseconds, DWORD HowManyTimes, LPCWSTR ApiNameOrOrd, DWORD nArgs, LPVOID pArgs);

 __XTRN194 DWORD __stdcall                        RemoteExecute(PRCINFO pRCI, DWORD ProcessId, LONG dwMilliseconds, LPVOID lpBlock, DWORD BlockSize, LPVOID lpParameter);
 __XTRN194 DWORD __stdcall                       hRemoteExecute(PRCINFO pRCI, HANDLE hProcess, LONG dwMilliseconds, LPVOID lpBlock, DWORD BlockSize, LPVOID lpParameter);

 __XTRN194 DWORD __stdcall HookApiA(LPCSTR  ModuleExport, LPCSTR ApiNameOrOrd,  DWORD dwFlags, LPCVOID ModuleImport,  PAPI_UNHOOK ApiUnhook, LPVOID HookAddress, HANDLE ExcludeModules[]);
 __XTRN194 DWORD __stdcall HookApiW(LPCWSTR ModuleExport, LPCWSTR ApiNameOrOrd, DWORD dwFlags, LPCVOID ModuleImport, PAPI_UNHOOK ApiUnhook, LPVOID HookAddress, HANDLE ExcludeModules[]);

 __XTRN194 DWORD __stdcall CallOrigFn(LPCSTR ModuleExport, LPCSTR ApiNameOrOrd, DWORD dwFlags, LPCVOID OrigFn, PAPI_UNHOOK ApiUnhook, DWORD nArgs, LPVOID pArgs);

 __XTRN194 PRCINFO __stdcall GetDefaultRCInfo(VOID);
 __XTRN194 BOOL  __stdcall UnhookApis(PAPI_HOOK lpAHChain, LONG nAHooks);
 __XTRN194 DWORD __stdcall GetProcFlags(DWORD ProcessId);
 __XTRN194 DWORD __stdcall hGetProcFlags(HANDLE hProcess);

 #ifdef UNICODE
 #define  EstablishApiHooks   EstablishApiHooksW
 #define hEstablishApiHooks  hEstablishApiHooksW
 #define  IsModuleLoaded      IsModuleLoadedW
 #define hIsModuleLoaded     hIsModuleLoadedW
 #define  LoadAndCall         LoadAndCallW
 #define hLoadAndCall        hLoadAndCallW
 #define  UnloadModule        UnloadModuleW
 #define hUnloadModule       hUnloadModuleW
 #define  HookApi             HookApiW
 #else
 #define  EstablishApiHooks   EstablishApiHooksA
 #define hEstablishApiHooks  hEstablishApiHooksA
 #define  IsModuleLoaded      IsModuleLoadedA
 #define hIsModuleLoaded     hIsModuleLoadedA
 #define  LoadAndCall         LoadAndCallA
 #define hLoadAndCall        hLoadAndCallA
 #define  UnloadModule        UnloadModuleA
 #define hUnloadModule       hUnloadModuleA
 #define  HookApi             HookApiA
 #endif
#endif

 #define ORIGFN(HookNo, nArgs, pArgs)\
        (CallOrigFn(ApiHookChain[(HookNo)].ModuleExport,\
                    ApiHookChain[(HookNo)].ApiNameOrOrd,\
                    ApiHookChain[(HookNo)].dwFlags,\
                    ApiHookChain[(HookNo)].ModuleImport,\
                    ApiHookChain[(HookNo)].UnhookAddresses,\
                    (nArgs), (pArgs)))

#endif