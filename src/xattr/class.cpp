#include "class.h"

int setcxa(const char *path, const char value, int flags)
{
    return setxattr(path, _CXA_USER_PREFIX, &value, 1, flags);
}

int getcxa(const char *path, char *value)
{
    return getxattr(path, _CXA_USER_PREFIX, value, 1);
}