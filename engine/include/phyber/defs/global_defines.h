#ifndef PHYBER_ENGINE_GLOBAL_DEFINES_H
#define PHYBER_ENGINE_GLOBAL_DEFINES_H

#include <stdint.h>

typedef uint32_t color_precision_t;
#define COLOR_MASK_RED   ((color_precision_t)(0xFF000000))
#define COLOR_MASK_GREEN ((color_precision_t)(0x00FF0000))
#define COLOR_MASK_BLUE  ((color_precision_t)(0x0000FF00))
#define COLOR_MASK_ALPHA ((color_precision_t)(0x000000FF))
#define COLOR_GET_RED(c)   (((c) & COLOR_MASK_RED) >> 24)
#define COLOR_GET_GREEN(c) (((c) & COLOR_MASK_GREEN) >> 16)
#define COLOR_GET_BLUE(c)  (((c) & COLOR_MASK_BLUE) >> 8)
#define COLOR_GET_ALPHA(c)  (((c) & COLOR_MASK_ALPHA))

typedef int8_t z_buffer_precision_t;

#endif /* PHYBER_ENGINE_GLOBAL_DEFINES_H */
