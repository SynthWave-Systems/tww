//
// Generated by dtk
// Translation Unit: c_m3d_g_cyl.cpp
//

#include "SSystem/SComponent/c_m3d_g_cyl.h"
#include "SSystem/SComponent/c_m3d.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "MSL_C/float.h"

#define CHECK_FLOAT_CLASS(line, x) JUT_ASSERT(__FILE__, line, !(((sizeof(x) == sizeof(float)) ? __fpclassifyf((float)(x)) : __fpclassifyd((double)(x)) ) == 1));
#define CHECK_FLOAT_RANGE(line, x) JUT_ASSERT(__FILE__, line, -1.0e32f < x && x < 1.0e32f);
#define CHECK_VEC3_RANGE(line, v) JUT_ASSERT(__FILE__, line, -1.0e32f < v.x && v.x < 1.0e32f && -1.0e32f < v.y && v.y < 1.0e32f && -1.0e32f < v.z && v.z < 1.0e32f)

/* 80251D88-80252020       .text SetC__8cM3dGCylFRC4cXyz */
void cM3dGCyl::SetC(const cXyz& pos) {
    CHECK_FLOAT_CLASS(21, pos.x);
    CHECK_FLOAT_CLASS(22, pos.y);
    CHECK_FLOAT_CLASS(23, pos.z);
    CHECK_VEC3_RANGE(26, pos);
    mCenter = pos;
}

/* 80252020-8025214C       .text SetH__8cM3dGCylFf */
void cM3dGCyl::SetH(f32 h) {
    CHECK_FLOAT_CLASS(36, h);
    CHECK_FLOAT_RANGE(37, h);
    mHeight = h;
}

/* 8025214C-80252278       .text SetR__8cM3dGCylFf */
void cM3dGCyl::SetR(f32 r) {
    CHECK_FLOAT_CLASS(48, r);
    CHECK_FLOAT_RANGE(49, r);
    mRadius = r;
}

/* 80252278-8025229C       .text cross__8cM3dGCylCFPC8cM3dGSphP4cXyz */
bool cM3dGCyl::cross(const cM3dGSph* pOther, cXyz* pOut) const {
    f32 f;
    return cM3d_Cross_CylSph(this, pOther, pOut, &f);
}

/* 8025229C-802522BC       .text cross__8cM3dGCylCFPC8cM3dGCylPf */
bool cM3dGCyl::cross(const cM3dGCyl* pOther, f32* pOut) const {
    return cM3d_Cross_CylCyl(this, pOther, pOut);
}

/* 802522BC-802522DC       .text cross__8cM3dGCylCFPC8cM3dGCylP4cXyz */
bool cM3dGCyl::cross(const cM3dGCyl* pOther, cXyz* pOut) const {
    return cM3d_Cross_CylCyl(this, pOther, pOut);
}

/* 802522DC-80252304       .text cross__8cM3dGCylCFPC8cM3dGSphPf */
bool cM3dGCyl::cross(const cM3dGSph* pOther, f32* pOut) const {
    cXyz xyz;
    return cM3d_Cross_CylSph(this, pOther, &xyz, pOut);
}
