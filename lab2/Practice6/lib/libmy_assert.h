#define __ASSERT_VOID_CAST (void)
extern char *__progname;
extern void my_assert_fail (const char * __assertion, const char *__file, unsigned int __line, const char *__function);
extern void my_assert(const char *__assertion,const char *__file,int __line);
#ifdef NDEBUG
#define my_assert(expr)(__ASSERT_VOID_CAST(0))
#else
#define my_assert(expr) ((expr) ? __ASSERT_VOID_CAST(0) : my_assert_fail(#expr, __FILE__, __LINE__, __func__))
#endif

