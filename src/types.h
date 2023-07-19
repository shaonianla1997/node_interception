
#include <stddef.h>
#include <stdint.h>
#include "inline_keywords.h" /* For H_INLINE */

struct _MMSignedPoint {
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