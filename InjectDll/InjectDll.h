#ifdef INJECTDLL_EXPORTS
#define INJECTDLL_API __declspec(dllexport)
#else
#define INJECTDLL_API __declspec(dllimport)
#endif

// �����Ǵ� InjectDll.dll ������
class INJECTDLL_API CInjectDll {
public:
	CInjectDll(void);
	// TODO: �ڴ�������ķ�����
};

extern INJECTDLL_API int nInjectDll;

INJECTDLL_API int fnInjectDll(void);

INJECTDLL_API bool StartHook();
INJECTDLL_API bool UnHook();