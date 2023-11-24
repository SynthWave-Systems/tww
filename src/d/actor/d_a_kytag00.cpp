//
// Generated by dtk
// Translation Unit: d_a_kytag00.cpp
//

#include "d/actor/d_a_kytag00.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_camera.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_kankyo.h"
#include "d/actor/d_a_player.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"
#include "SSystem/SComponent/c_lib.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JUtility/JUTAssert.h"

/* 00000078-0000024C       .text get_check_pos__FP13kytag00_class */
cXyz get_check_pos(kytag00_class* i_this) {
    /* Nonmatching - regswap */
    cXyz ret;

    camera_class * pCamera = dComIfGp_getCamera(0);
    fopAc_ac_c * pPlayer = dComIfGp_getPlayer(0);

    f32 cameraDist = i_this->getPosition().abs(pCamera->mLookat.mEye);
    f32 playerDist = i_this->getPosition().abs(pPlayer->current.pos);

    if (dComIfGp_event_runCheck() && i_this->mMode == 0) {
        if (cameraDist < playerDist) {
            ret = pCamera->mLookat.mEye;
        } else {
            ret = pPlayer->getPosition();
        }
    } else {
        ret = pPlayer->getPosition();
    }

    return ret;
}

/* 0000024C-000005E4       .text wether_tag_move__FP13kytag00_class */
void wether_tag_move(kytag00_class* i_this) {
    /* Nonmatching */
    cXyz chk_pos = get_check_pos(i_this);
    cXyz chk_pos_xz(chk_pos.x, i_this->getPosition().y, chk_pos.z);
    f32 fade_y = i_this->mInnerFadeY * 100.0f;
    f32 dist_xz = i_this->getPosition().abs(chk_pos_xz);

    if (dist_xz <= i_this->mOuterRadius && (chk_pos.y > (i_this->getPosition().y - fade_y) && chk_pos.y < (i_this->getPosition().y + i_this->mScale.y * 5000.0f + fade_y)) && i_this->mTarget > 0.0f) {
        
    } else {
        if (i_this->mbPselSet) {
            i_this->mbPselSet = false;
            g_env_light.mColpatPrevGather = g_env_light.mColpatWeather;
            g_env_light.mColpatCurrGather = g_env_light.mColpatWeather;
            g_env_light.mColPatBlendGather = 0.0f;
            g_env_light.mColPatModeGather = 1;
        }
    }
}

/* 000005E4-000006A0       .text raincnt_set__Ff */
void raincnt_set(f32 count) {
    s32 newCount = 0;

    if (dKy_checkEventNightStop()) {
        s32 newCount2;
        if (g_env_light.mRainCount > (newCount2 = (count * count * count) * 250.0f))
            newCount = newCount2;
    } else {
        newCount = (count * count * count) * 250.0f;
    }

    if (newCount > g_env_light.mRainCountOrig)
        g_env_light.mRainCount = newCount;
}

/* 000006A0-000006D8       .text raincnt_cut__Fv */
void raincnt_cut() {
    if (!dKy_checkEventNightStop())
        g_env_light.mRainCount = g_env_light.mRainCountOrig;
}

/* 000006D8-00000C0C       .text wether_tag_efect_move__FP13kytag00_class */
void wether_tag_efect_move(kytag00_class* i_this) {
    /* Nonmatching */
}

/* 00000C0C-00000C30       .text daKytag00_Draw__FP13kytag00_class */
BOOL daKytag00_Draw(kytag00_class* i_this) {
    wether_tag_efect_move(i_this);
    return TRUE;
}

/* 00000C30-00000D44       .text daKytag00_Execute__FP13kytag00_class */
BOOL daKytag00_Execute(kytag00_class* i_this) {
    if (!i_this->mbInvert) {
        if (i_this->mSwitchNo != 0xFF && dComIfGs_isSwitch(i_this->mSwitchNo, dComIfGp_roomControl_getStayNo())) {
            cLib_addCalc(&i_this->mTarget, 0.0f, 0.1f, 0.01f, 0.0001f);
        } else {
            cLib_addCalc(&i_this->mTarget, 1.0f, 0.1f, 0.01f, 0.0001f);
        }
    } else {
        if (i_this->mSwitchNo != 0xFF && dComIfGs_isSwitch(i_this->mSwitchNo, dComIfGp_roomControl_getStayNo())) {
            cLib_addCalc(&i_this->mTarget, 1.0f, 0.1f, 0.01f, 0.0001f);
        } else {
            cLib_addCalc(&i_this->mTarget, 0.0f, 0.1f, 0.01f, 0.0001f);
        }
    }

    wether_tag_move(i_this);
    return TRUE;
}

/* 00000D44-00000D4C       .text daKytag00_IsDelete__FP13kytag00_class */
BOOL daKytag00_IsDelete(kytag00_class* i_this) {
    return TRUE;
}

/* 00000D4C-00000D64       .text daKytag00_Delete__FP13kytag00_class */
BOOL daKytag00_Delete(kytag00_class* i_this) {
    g_env_light.mMoyaCount = 0;
    return TRUE;
}

/* 00000D64-00000F8C       .text daKytag00_Create__FP10fopAc_ac_c */
s32 daKytag00_Create(fopAc_ac_c* i_ac) {
    kytag00_class * i_this = (kytag00_class *)i_ac;

    fopAcM_SetupActor(i_this, kytag00_class);

    i_this->field_0x296 = 0;
    i_this->mPselIdx = (fopAcM_GetParam(i_this) >> 0) & 0xFF;
    i_this->mEfMode = (fopAcM_GetParam(i_this) >> 8) & 0xFF;
    i_this->mThickness = (fopAcM_GetParam(i_this) >> 16) & 0xFF;
    i_this->mInnerFadeY = (fopAcM_GetParam(i_this) >> 24) & 0xFF;
    i_this->mSwitchNo = (i_this->current.angle.x >> 0) & 0xFF;
    i_this->mbInvert = (i_this->current.angle.x >> 8) & 0xFF;
    i_this->mMode = (i_this->current.angle.z >> 0) & 0xFF;

    if (!i_this->mbInvert) {
        if (i_this->mSwitchNo != 0xFF && dComIfGs_isSwitch(i_this->mSwitchNo, dComIfGp_roomControl_getStayNo())) {
            i_this->mTarget = 0.0f;
        } else {
            i_this->mTarget = 1.0f;
        }
    } else {
        if (i_this->mSwitchNo != 0xFF && dComIfGs_isSwitch(i_this->mSwitchNo, dComIfGp_roomControl_getStayNo())) {
            i_this->mTarget = 1.0f;
        } else {
            i_this->mTarget = 0.0f;
        }
    }

    if (i_this->mThickness == 0xFF)
        i_this->mThickness = 10;

    if (i_this->mInnerFadeY == 0xFF)
        i_this->mInnerFadeY = 10;

    if (i_this->mMode == 0) {
        i_this->mInnerRadius = i_this->mScale.x * 5000.0f;
        i_this->mOuterRadius = i_this->mScale.x * 5000.0f + i_this->mThickness * 100.0f;
    } else {
        i_this->mInnerRadius = i_this->mScale.x * 500.0f;
        i_this->mOuterRadius = i_this->mScale.x * 500.0f + i_this->mThickness * 10.0f;
    }

    i_this->mbEfSet = false;
    i_this->mbPselSet = false;
    g_env_light.mMoyaCount = 0;
    wether_tag_efect_move(i_this);
    return cPhs_COMPLEATE_e;
}

actor_method_class l_daKytag00_Method = {
    (process_method_func)daKytag00_Create,
    (process_method_func)daKytag00_Delete,
    (process_method_func)daKytag00_Execute,
    (process_method_func)daKytag00_IsDelete,
    (process_method_func)daKytag00_Draw,
};

actor_process_profile_definition g_profile_KYTAG00 = {
    fpcLy_CURRENT_e,
    7,
    fpcPi_CURRENT_e,
    PROC_KYTAG00,
    &g_fpcLf_Method.mBase,
    sizeof(kytag00_class),
    0,
    0,
    &g_fopAc_Method.base,
    0xA0,
    &l_daKytag00_Method,
    fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    fopAc_ACTOR_e,
    fopAc_CULLBOX_0_e,
};
