#if defined _WIN32 || defined __CYGWIN__
	#ifdef BUILDING_ALCHEMIST
		#ifdef __GNUC__
    		#define DLL_PUBLIC __attribute__ ((dllexport))
		#else
    		#define DLL_PUBLIC __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    	#endif
  	#else
    	#ifdef __GNUC__
      		#define DLL_PUBLIC __attribute__ ((dllimport))
    	#else
      		#define DLL_PUBLIC __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
    	#endif
  	#endif
  	#define DLL_LOCAL
	#define DLL_PROTECTED DLL_PUBLIC
#else
	#if __GNUC__ >= 4
    	#define DLL_PUBLIC __attribute__ ((visibility ("default")))
    	#define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
		#define DLL_PROTECTED
  	#else
    	#define DLL_PUBLIC
    	#define DLL_LOCAL
		#define DLL_PROTECTED
  	#endif
#endif
