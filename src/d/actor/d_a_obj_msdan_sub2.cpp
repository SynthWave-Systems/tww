//
// Generated by dtk
// Translation Unit: d_a_obj_msdan_sub2.cpp
//

#include "d/actor/d_a_obj_msdan_sub2.h"
#include "d/d_procname.h"

/* 00000078-0000012C       .text CreateHeap__Q214daObjMsdanSub25Act_cFv */
void daObjMsdanSub2::Act_c::CreateHeap() {
    /* Nonmatching */
}

/* 0000012C-000002E4       .text Create__Q214daObjMsdanSub25Act_cFv */
s32 daObjMsdanSub2::Act_c::Create() {
    /* Nonmatching */
}

/* 000002E4-00000454       .text Mthd_Create__Q214daObjMsdanSub25Act_cFv */
void daObjMsdanSub2::Act_c::Mthd_Create() {
    /* Nonmatching */
}

/* 00000454-0000045C       .text Delete__Q214daObjMsdanSub25Act_cFv */
BOOL daObjMsdanSub2::Act_c::Delete() {
    /* Nonmatching */
}

/* 0000045C-000004A8       .text Mthd_Delete__Q214daObjMsdanSub25Act_cFv */
void daObjMsdanSub2::Act_c::Mthd_Delete() {
    /* Nonmatching */
}

/* 000004A8-00000528       .text set_mtx__Q214daObjMsdanSub25Act_cFv */
void daObjMsdanSub2::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 00000528-00000598       .text init_mtx__Q214daObjMsdanSub25Act_cFv */
void daObjMsdanSub2::Act_c::init_mtx() {
    /* Nonmatching */
}

/* 00000598-0000090C       .text Execute__Q214daObjMsdanSub25Act_cFPPA3_A4_f */
void daObjMsdanSub2::Act_c::Execute(float(**)[3][4]) {
    /* Nonmatching */
}

/* 0000090C-000009AC       .text Draw__Q214daObjMsdanSub25Act_cFv */
BOOL daObjMsdanSub2::Act_c::Draw() {
    /* Nonmatching */
}

namespace daObjMsdanSub2 {
namespace {
/* 000009AC-000009CC       .text Mthd_Create__Q214daObjMsdanSub232@unnamed@d_a_obj_msdan_sub2_cpp@FPv */
void Mthd_Create(void*) {
    /* Nonmatching */
}

/* 000009CC-000009EC       .text Mthd_Delete__Q214daObjMsdanSub232@unnamed@d_a_obj_msdan_sub2_cpp@FPv */
void Mthd_Delete(void*) {
    /* Nonmatching */
}

/* 000009EC-00000A0C       .text Mthd_Execute__Q214daObjMsdanSub232@unnamed@d_a_obj_msdan_sub2_cpp@FPv */
void Mthd_Execute(void*) {
    /* Nonmatching */
}

/* 00000A0C-00000A38       .text Mthd_Draw__Q214daObjMsdanSub232@unnamed@d_a_obj_msdan_sub2_cpp@FPv */
void Mthd_Draw(void*) {
    /* Nonmatching */
}

/* 00000A38-00000A64       .text Mthd_IsDelete__Q214daObjMsdanSub232@unnamed@d_a_obj_msdan_sub2_cpp@FPv */
void Mthd_IsDelete(void*) {
    /* Nonmatching */
}

static actor_method_class Mthd_MsdanSub2 = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjMsdanSub2

actor_process_profile_definition g_profile_Obj_MsdanSub2 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_MsdanSub2,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjMsdanSub2::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x003B,
    /* Actor SubMtd */ &daObjMsdanSub2::Mthd_MsdanSub2,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
