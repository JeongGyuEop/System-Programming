INCLUDE_DIRECTORIES (lib)
ADD_EXECUTABLE ( strerror_use strerror_use.c )
ADD_LIBRARY ( my_perror STATIC lib/libmy_perror.c )
TARGET_LINK_LIBRARIES ( strerror_use PUBLIC my_perror )
