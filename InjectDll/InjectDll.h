#ifdef INJECTDLL_EXPORTS
#define INJECTDLL_API __declspec(dllexport)
#else
#define INJECTDLL_API __declspec(dllimport)
#endif

// 此类是从 InjectDll.dll 导出的
class INJECTDLL_API CInjectDll {
public:
	CInjectDll(void);
	// TODO: 在此添加您的方法。
};

extern INJECTDLL_API int nInjectDll;

INJECTDLL_API int fnInjectDll(void);

INJECTDLL_API bool StartHook();
INJECTDLL_API bool UnHook();