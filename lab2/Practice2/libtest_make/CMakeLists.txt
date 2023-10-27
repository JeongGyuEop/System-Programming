INCLUDE_DIRECTORIES (lib)
ADD_EXECUTABLE (main main.c)
ADD_LIBRARY (libtest STATIC lib/lib_operation.c lib/lib_operation.h)
TARGET_LINK_LIBRARIES (main PUBLIC libtest)
