#ifndef _OVERRIDE_COM_UTIL_CLOCK_H
#define _OVERRIDE_COM_UTIL_CLOCK_H

/* 本物を include */
#include "../../../../prod/include/com_util/clock/clock.h"

/* モックにすげ替え */
#define _IN_OVERRIDE_HEADER_COM_UTIL_CLOCK_H
#include <com_util/clock/mock_clock.h>
#undef _IN_OVERRIDE_HEADER_COM_UTIL_CLOCK_H

#endif /* _OVERRIDE_COM_UTIL_CLOCK_H */
