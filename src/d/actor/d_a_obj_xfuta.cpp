//
// Generated by dtk
// Translation Unit: d_a_obj_xfuta.cpp
//

#include "d/actor/d_a_obj_xfuta.h"
#include "d/d_procname.h"

/* 00000078-0000009C       .text solidHeapCB__Q210daObjXfuta5Act_cFP10fopAc_ac_c */
void daObjXfuta::Act_c::solidHeapCB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 0000009C-0000015C       .text create_heap__Q210daObjXfuta5Act_cFv */
void daObjXfuta::Act_c::create_heap() {
    /* Nonmatching */
}

/* 0000015C-00000214       .text _create__Q210daObjXfuta5Act_cFv */
s32 daObjXfuta::Act_c::_create() {
    /* Nonmatching */
}

/* 00000214-00000244       .text _delete__Q210daObjXfuta5Act_cFv */
BOOL daObjXfuta::Act_c::_delete() {
    /* Nonmatching */
}

/* 00000244-000002F0       .text set_mtx__Q210daObjXfuta5Act_cFv */
void daObjXfuta::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 000002F0-00000338       .text _execute__Q210daObjXfuta5Act_cFv */
BOOL daObjXfuta::Act_c::_execute() {
    /* Nonmatching */
}

/* 00000338-0000040C       .text _draw__Q210daObjXfuta5Act_cFv */
BOOL daObjXfuta::Act_c::_draw() {
    /* Nonmatching */
}

namespace daObjXfuta {
namespace {
/* 0000040C-0000042C       .text Mthd_Create__Q210daObjXfuta27@unnamed@d_a_obj_xfuta_cpp@FPv */
void Mthd_Create(void*) {
    /* Nonmatching */
}

/* 0000042C-00000450       .text Mthd_Delete__Q210daObjXfuta27@unnamed@d_a_obj_xfuta_cpp@FPv */
void Mthd_Delete(void*) {
    /* Nonmatching */
}

/* 00000450-00000474       .text Mthd_Execute__Q210daObjXfuta27@unnamed@d_a_obj_xfuta_cpp@FPv */
void Mthd_Execute(void*) {
    /* Nonmatching */
}

/* 00000474-00000498       .text Mthd_Draw__Q210daObjXfuta27@unnamed@d_a_obj_xfuta_cpp@FPv */
void Mthd_Draw(void*) {
    /* Nonmatching */
}

/* 00000498-000004A0       .text Mthd_IsDelete__Q210daObjXfuta27@unnamed@d_a_obj_xfuta_cpp@FPv */
void Mthd_IsDelete(void*) {
    /* Nonmatching */
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjXfuta

actor_process_profile_definition g_profile_Obj_Xfuta = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Xfuta,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjXfuta::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x003D,
    /* Actor SubMtd */ &daObjXfuta::Mthd_Table,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
