//
// Generated by dtk
// Translation Unit: d_a_obj_hami3.cpp
//

#include "d/actor/d_a_obj_hami3.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"

/* 00000078-0000012C       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 0000012C-0000026C       .text CreateHeap__Q210daObjHami35Act_cFv */
void daObjHami3::Act_c::CreateHeap() {
    /* Nonmatching */
}

/* 0000026C-00000354       .text Create__Q210daObjHami35Act_cFv */
s32 daObjHami3::Act_c::Create() {
    /* Nonmatching */
}

/* 00000354-00000450       .text Mthd_Create__Q210daObjHami35Act_cFv */
void daObjHami3::Act_c::Mthd_Create() {
    /* Nonmatching */
}

/* 00000450-00000458       .text Delete__Q210daObjHami35Act_cFv */
BOOL daObjHami3::Act_c::Delete() {
    /* Nonmatching */
}

/* 00000458-000004A4       .text Mthd_Delete__Q210daObjHami35Act_cFv */
void daObjHami3::Act_c::Mthd_Delete() {
    /* Nonmatching */
}

/* 000004A4-00000524       .text set_mtx__Q210daObjHami35Act_cFv */
void daObjHami3::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 00000524-00000560       .text init_mtx__Q210daObjHami35Act_cFv */
void daObjHami3::Act_c::init_mtx() {
    /* Nonmatching */
}

/* 00000560-000005DC       .text daObjHami3_close_stop__Q210daObjHami35Act_cFv */
void daObjHami3::Act_c::daObjHami3_close_stop() {
    /* Nonmatching */
}

/* 000005DC-00000688       .text daObjHami3_open_demo_wait__Q210daObjHami35Act_cFv */
void daObjHami3::Act_c::daObjHami3_open_demo_wait() {
    /* Nonmatching */
}

/* 00000688-0000078C       .text daObjHami3_open_demo__Q210daObjHami35Act_cFv */
void daObjHami3::Act_c::daObjHami3_open_demo() {
    /* Nonmatching */
}

/* 0000078C-00000808       .text daObjHami3_open_stop__Q210daObjHami35Act_cFv */
void daObjHami3::Act_c::daObjHami3_open_stop() {
    /* Nonmatching */
}

/* 00000808-00000858       .text daObjHami3_close_demo_wait__Q210daObjHami35Act_cFv */
void daObjHami3::Act_c::daObjHami3_close_demo_wait() {
    /* Nonmatching */
}

/* 00000858-00000934       .text daObjHami3_close_demo__Q210daObjHami35Act_cFv */
void daObjHami3::Act_c::daObjHami3_close_demo() {
    /* Nonmatching */
}

/* 00000934-000009F4       .text Execute__Q210daObjHami35Act_cFPPA3_A4_f */
void daObjHami3::Act_c::Execute(float(**)[3][4]) {
    /* Nonmatching */
}

/* 000009F4-00000A94       .text Draw__Q210daObjHami35Act_cFv */
BOOL daObjHami3::Act_c::Draw() {
    /* Nonmatching */
}

namespace daObjHami3 {
namespace {
/* 00000A94-00000AB4       .text Mthd_Create__Q210daObjHami327@unnamed@d_a_obj_hami3_cpp@FPv */
void Mthd_Create(void*) {
    /* Nonmatching */
}

/* 00000AB4-00000AD4       .text Mthd_Delete__Q210daObjHami327@unnamed@d_a_obj_hami3_cpp@FPv */
void Mthd_Delete(void*) {
    /* Nonmatching */
}

/* 00000AD4-00000AF4       .text Mthd_Execute__Q210daObjHami327@unnamed@d_a_obj_hami3_cpp@FPv */
void Mthd_Execute(void*) {
    /* Nonmatching */
}

/* 00000AF4-00000B20       .text Mthd_Draw__Q210daObjHami327@unnamed@d_a_obj_hami3_cpp@FPv */
void Mthd_Draw(void*) {
    /* Nonmatching */
}

/* 00000B20-00000B4C       .text Mthd_IsDelete__Q210daObjHami327@unnamed@d_a_obj_hami3_cpp@FPv */
void Mthd_IsDelete(void*) {
    /* Nonmatching */
}

static actor_method_class Mthd_Hami3 = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjHami3

actor_process_profile_definition g_profile_Obj_Hami3 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Hami3,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjHami3::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x001A,
    /* Actor SubMtd */ &daObjHami3::Mthd_Hami3,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
