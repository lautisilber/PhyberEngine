#include "phyber/math.h"

using namespace Phyber;

PhyberMat2x2 matrix_rotation_2d(float radians) {
    float c = std::cos(radians);
    float s = std::sin(radians);
    return PhyberMat2x2({
        c, -s,
        s, c
    });
}
