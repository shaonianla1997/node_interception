#include <stddef.h>
#include <stdint.h>
#include "inline_keywords.h" /* For H_INLINE */
#include "keycode.h"
#define MOD_WIN             0x0008

struct _MMSignedPoint
{
	int32_t x;
	int32_t y;
};

typedef struct _MMSignedPoint MMSignedPoint;
typedef struct _MMRect MMRect;
H_INLINE MMSignedPoint MMSignedPointMake(int32_t x, int32_t y)
{
	MMSignedPoint point;
	point.x = x;
	point.y = y;
	return point;
}
#define MMPointZero MMPointMake(0, 0);

enum _MMKeyFlags
{
	MOD_NONE = 0,
	/* These are already defined by the Win32 API */
	/* MOD_ALT = 0,
	MOD_CONTROL = 0,
	MOD_SHIFT = 0, */
	MOD_META = MOD_WIN
};

typedef unsigned int MMKeyFlags;