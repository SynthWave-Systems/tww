//
// Generated by dtk
// Translation Unit: d_a_ib.cpp
//

#include "d/actor/d_a_ib.h"
#include "d/d_procname.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "d/d_com_inf_game.h"
#include "d/d_s_play.h"
#include "d/actor/d_a_item.h"
#include "d/d_item.h"
#include "d/d_item_data.h"
#include "m_Do/m_Do_mtx.h"

// Needed for the .data section to match.
static f32 dummy1[3] = {1.0f, 1.0f, 1.0f};
static f32 dummy2[3] = {1.0f, 1.0f, 1.0f};

struct daIball_c__data {
    /* 0x00 */ u8 m00;
    /* 0x01 */ u8 m01;
    /* 0x02 */ u8 m02;
    /* 0x03 */ u8 m03;
    /* 0x04 */ f32 mPlaySpeeds[4];
    /* 0x14 */ f32 mBounceSpeedMult;
    /* 0x18 */ f32 mGravity;
    /* 0x1C */ f32 mYOffset;
    /* 0x20 */ f32 m20;
    /* 0x24 */ f32 m24;
    /* 0x28 */ s16 mMoveDelay;
    /* 0x2C */ f32 mSpeedF;
    /* 0x30 */ f32 mSpeedY;
    /* 0x34 */ f32 mRandSpeedF;
    /* 0x38 */ s16 m38;
    /* 0x3A */ s16 m3A;
};

const daIball_c__data m_data = {
    /* m00              */ 1,
    /* m01              */ 2,
    /* m02              */ 4,
    /* m03              */ 5,
    /* mPlaySpeeds      */ {1.0f, 2.0f, 4.0f, 8.0f},
    /* mBounceSpeedMult */ 0.5f,
    /* mGravity         */ -7.0f,
    /* mYOffset         */ 40.0f,
    /* m20              */ 0.5f,
    /* m24              */ 0.75f,
    /* mMoveDelay       */ 32,
    /* mSpeedF          */ 10.0f,
    /* mSpeedY          */ 53.0f,
    /* mRandSpeedF      */ 4.0f,
    /* m38              */ 80,
    /* m3A              */ 60,
};

/* 800F3228-800F3380       .text setPointLight__9daIball_cFv */
void daIball_c::setPointLight() {
    static const s16 light_color[3][3] = {
        {800, 120, 400},
        {120, 400, 600},
        {600, 600, 200},
    };
    int color_idx;
    f32 frame = mBrkAnm[0].getFrame();
    if (frame >= 0.0f && frame < 45.0f) {
        color_idx = 0;
    } else if (frame >= 45.0f && frame < 90.0f) {
        color_idx = 1;
    } else if (frame >= 90.0f && frame <= 135.0f) {
        color_idx = 2;
    }
    cLib_addCalc2(&mLightFlickerMult, 1.0f + cM_rndF(0.2f), 0.5f, 0.02f);
    mLight.mPos = current.pos;
    mLight.mColor.r = light_color[color_idx][0];
    mLight.mColor.g = light_color[color_idx][1];
    mLight.mColor.b = light_color[color_idx][2];
    s16 power = (80.0f + g_regHIO.mChild[12].mFloatRegs[0]) * mLightFlickerMult;
    mLight.mPower = power;
    mLight.mFluctuation = 250.0f;
}

/* 800F3380-800F3608       .text createDisappearEffect__9daIball_cFii */
void daIball_c::createDisappearEffect(int param_1, int color_idx) {
    cXyz scale;
    scale.setall(1.0f);
    cXyz pos(current.pos);
    pos.y += m_data.mYOffset;
    switch (param_1) {
    case 0:
        dComIfGp_particle_set(0x1C, &pos, NULL, &scale, 0xFF, dPa_control_c::getLifeBallSetColorEcallBack(color_idx));
        dComIfGp_particle_set(0x1D, &pos, NULL, &scale);
        if (color_idx == 2) {
            dComIfGp_particle_set(0x47, &pos);
        }
        fopAcM_seStartCurrent(this, JA_SE_OBJ_CUT_INOCHIDAMA, 0);
        break;
    case 1:
        dComIfGp_particle_set(0x19, &pos, NULL, &scale);
        dComIfGp_particle_set(0x1A, &pos, NULL, &scale);
        dComIfGp_particle_set(0x1B, &pos, NULL, &scale);
        fopAcM_seStartCurrent(this, JA_SE_CM_INOCHIDAMA_BREAK, 0);
        break;
    }
}

/* 800F3608-800F3658       .text itemParamSet_CB__FPv */
static BOOL itemParamSet_CB(void* i_actor) {
    daItem_c* item = static_cast<daItem_c*>(i_actor);
    if (item && !isEmono(item->getItemNo())) {
        item->setItemTimerForIball(3*30, 2*30);
    }
    return TRUE;
}

// This is a fake inline, not present in the demo debug map.
// However, it's possible an inline similar to this was added to the final release.
// The kiosk demo calls dSv_memBit_c::isVisitedRoom(int) instead of dSv_memBit_c::isSwitch(int) here,
// so it's plausible they also added this inline while they were modifying that code.
inline BOOL isItemBit(u8 itemNo, s8 itemBitNo, s8 roomNo) {
    if (itemNo == BLUE_JELLY) { // Blue Chu Jelly uses itemBitNo as if it was a switch.
        return dComIfGs_isSaveSwitch(0xE, itemBitNo);
    } else {
        return dComIfGs_isItem(itemBitNo, roomNo);
    }
}

/* 800F3658-800F3994       .text createItem__9daIball_cFv */
BOOL daIball_c::createItem() {
    // Fakematch: itemBitNo and itemTableIdx should really be separate variables as they aren't
    // related, but we need r27 to be used for both of them in order for the regalloc to match.
    int itemBitNo = daIball_prm::getAdId(this);
    int itemTableIdx = itemBitNo;
    u32 items[8];
    
    items[0] = dComIfGp_CharTbl()->GetInf(dComIfGp_CharTbl()->mIndex_ITEM0, itemTableIdx);
    items[1] = dComIfGp_CharTbl()->GetInf(dComIfGp_CharTbl()->mIndex_ITEM1, itemTableIdx);
    items[2] = dComIfGp_CharTbl()->GetInf(dComIfGp_CharTbl()->mIndex_ITEM2, itemTableIdx);
    items[3] = dComIfGp_CharTbl()->GetInf(dComIfGp_CharTbl()->mIndex_ITEM3, itemTableIdx);
    items[4] = dComIfGp_CharTbl()->GetInf(dComIfGp_CharTbl()->mIndex_ITEM4, itemTableIdx);
    items[5] = dComIfGp_CharTbl()->GetInf(dComIfGp_CharTbl()->mIndex_ITEM5, itemTableIdx);
    items[6] = dComIfGp_CharTbl()->GetInf(dComIfGp_CharTbl()->mIndex_ITEM6, itemTableIdx);
    items[7] = dComIfGp_CharTbl()->GetInf(dComIfGp_CharTbl()->mIndex_ITEM7, itemTableIdx);
    
    for (int i = 0; i < 8; i++) {
        itemBitNo = -1;
        if (isLimitedItem(items[i])) {
            itemBitNo = daIball_prm::getItemBitNo(this);
            if (itemBitNo == 0x1F || itemBitNo == 0xFF || itemBitNo == -1 || isItemBit(items[i], itemBitNo, current.roomNo)) {
                itemBitNo = -1;
                items[i] = YELLOW_RUPEE;
            }
        } else if (isNonSavedEmono(items[i])) {
            if (daIball_prm::getItemBitNo(this) != 0) {
                items[i] = YELLOW_RUPEE;
            }
            itemBitNo = -1;
        }
        
        cXyz scale = cXyz::Zero;
        csXyz angle = csXyz::Zero;
        
        f32 speed_f = 1.0f;
        if (cM_rndFX(1.0f) < 0.0f) {
            speed_f = -1.0f;
        }
        speed_f = speed_f*m_data.mSpeedF + cM_rndFX(m_data.mRandSpeedF);
        
        angle.y = (s16)cM_rndF((f32)0x7FFF);
        
        items[i] = getItemNoByLife(items[i]);
        
        s8 roomNo = current.roomNo;
        fopAcM_fastCreateItem(
            &current.pos, items[i], roomNo, &angle, &scale,
            speed_f, m_data.mSpeedY + cM_rndF(10.0f), -6.0f, itemBitNo, itemParamSet_CB
        );
    }
    
    dead();
    
    return TRUE;
}

/* 800F3994-800F3A48       .text dead__9daIball_cFv */
BOOL daIball_c::dead() {
    int color_idx;
    f32 frame = mBrkAnm[0].getFrame();
    if (frame >= 0.0f && frame < 45.0f) {
        color_idx = 0;
    } else if (frame >= 45.0f && frame < 90.0f) {
        color_idx = 1;
    } else if (frame >= 90.0f && frame <= 135.0f) {
        color_idx = 2;
    }
    createDisappearEffect(0, color_idx);
    fopAcM_delete(this);
    return TRUE;
}

/* 800F3A48-800F3E78       .text checkGeo__9daIball_cFv */
void daIball_c::checkGeo() {
    static ModeFunc mode_proc[] = {
        &mode_wait,
        &mode_water,
    };
    
    mPrevSpeedY = speed.y;
    if (mTimer > m_data.mMoveDelay) {
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
    }
    mAcch.CrrPos(*dComIfG_Bgsp());
    
    (this->*mode_proc[mMode])();
    
    dBgS_ObjGndChk_Yogan gnd_chk;
    cXyz pos(current.pos.x, next.pos.y + 30.0f + m_data.mYOffset, current.pos.z);
    gnd_chk.SetPos(&pos);
    f32 groundY = dComIfG_Bgsp()->GroundCross(&gnd_chk);
    f32 groundH = mAcch.GetGroundH();
    if (groundY != -1000000000.0f) {
        f32 dist_off_gnd = groundY - groundH;
        if ((dist_off_gnd < 20.0f && groundY > current.pos.y) || (dist_off_gnd >= 20.0f && groundY > current.pos.y + 20.0f)) {
            fopAcM_seStartCurrent(this, JA_SE_OBJ_FALL_MAGMA_S, 0);
            cXyz particle_scale;
            particle_scale.setall(0.25f);
            cXyz particle_pos(current.pos);
            particle_pos.y = groundY;
            dComIfGp_particle_set(0x80D5, &particle_pos, NULL, &particle_scale);
            fopAcM_delete(this);
        }
    }
}

/* 800F3E78-800F3EB0       .text mode_wait_init__9daIball_cFv */
void daIball_c::mode_wait_init() {
    mRippleCb.end();
    mMode = MODE_WAIT;
}

/* 800F3EB0-800F3F6C       .text mode_wait__9daIball_cFv */
void daIball_c::mode_wait() {
    if (mAcch.ChkGroundLanding()) {
        mPrevSpeedY *= m_data.mBounceSpeedMult;
        if (mPrevSpeedY > mGravity - 0.5f) {
            speedF = 0.0f;
        } else {
            speed.set(0.0f, -mPrevSpeedY, 0.0f);
        }
    }
    
    f32 seaHeight = mAcch.GetSeaHeight();
    if (seaHeight > current.pos.y && seaHeight != -1000000000.0f) {
        mode_water_init();
        current.pos.y = seaHeight;
    }
}

/* 800F3F6C-800F3FE8       .text mode_water_init__9daIball_cFv */
void daIball_c::mode_water_init() {
    dComIfGp_particle_setShipTail(0x33, &current.pos, NULL, &mScale, 0xFF, &mRippleCb);
    mRippleCb.setRate(0.0f);
    mMode = MODE_WATER;
}

/* 800F3FE8-800F4054       .text mode_water__9daIball_cFv */
void daIball_c::mode_water() {
    f32 seaHeight = mAcch.GetSeaHeight();
    if (seaHeight == -1000000000.0f || seaHeight < current.pos.y) {
        mode_wait_init();
    }
    if (seaHeight != -1000000000.0f) {
        current.pos.y = seaHeight;
    }
}

/* 800F4054-800F418C       .text animControl__9daIball_cFv */
void daIball_c::animControl() {
    BOOL isEventRun = FALSE;
    if (dComIfGp_event_runCheck()) {
        isEventRun = TRUE;
    }
    
    mBrkAnm[0].setPlaySpeed(m_data.mPlaySpeeds[mPlaySpeedIdx]);
    mBrkAnm[0].play();
    BOOL isLoop = mBrkAnm[0].isLoop();
    mBrkAnm[1].setPlaySpeed(1.0f);
    mBrkAnm[1].play();
    mBtkAnm.setPlaySpeed(1.0f);
    mBtkAnm.play();
    mBckAnm.play();
    
    if (!isEventRun) {
        f32 frame = mBrkAnm[0].getFrame();
        f32 prevFrame = frame - mBrkAnm[0].getPlaySpeed();
        if (isLoop ||
            (frame >= 45.0f && prevFrame < 45.0f) ||
            (frame >= 90.0f && prevFrame < 90.0f))
        {
            fopAcM_seStartCurrent(this, JA_SE_CM_INOCHIDAMA_BLINK, 0);
        }
    }
}

/* 800F418C-800F4250       .text damage__9daIball_cFv */
void daIball_c::damage() {
    if (mCyl.ChkTgHit()) {
        cCcD_Obj* hitObj = mCyl.GetTgHitObj();
        if (hitObj) {
            u32 atType = hitObj->GetAtType();
            if (atType & AT_TYPE_SWORD || atType & AT_TYPE_BOKO_STICK ||
                atType & AT_TYPE_MACHETE || atType & AT_TYPE_SKULL_HAMMER ||
                atType & AT_TYPE_UNK2000000 || atType & AT_TYPE_STALFOS_MACE ||
                atType & AT_TYPE_DARKNUT_SWORD || atType & AT_TYPE_UNK8000 ||
                atType & AT_TYPE_BOOMERANG || atType & AT_TYPE_NORMAL_ARROW ||
                atType & AT_TYPE_FIRE_ARROW || atType & AT_TYPE_ICE_ARROW ||
                atType & AT_TYPE_LIGHT_ARROW || atType & AT_TYPE_MOBLIN_SPEAR)
            {
                createItem();
            }
        }
    }
}

/* 800F4250-800F42E8       .text set_mtx__9daIball_cFv */
void daIball_c::set_mtx() {
    mpModel->setBaseScale(mScale);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y + m_data.mYOffset, current.pos.z);
    mDoMtx_stack_c::XYZrotM(current.angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

// TODO: This is a hack. I have no idea why this one variable needs to go in .data instead of .sdata.
#ifndef __INTELLISENSE__
__declspec(section ".data")
#endif
char daIball_c::m_arcname[] = "Always";

dCcD_SrcCyl daIball_c::m_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt Type     */ 0,
        /* SrcObjAt Atp      */ 0,
        /* SrcObjAt SPrm     */ 0,
        /* SrcObjTg Type     */ ~(AT_TYPE_LIGHT),
        /* SrcObjTg SPrm     */ 0x09,
        /* SrcObjCo SPrm     */ 0x79,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt GFlag   */ 0x04,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg GFlag   */ 0x04,
        /* SrcGObjCo GFlag   */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 30.0f,
        /* Height */ 80.0f,
    },
};

/* 800F42E8-800F441C       .text CreateInit__9daIball_cFv */
void daIball_c::CreateInit() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(m_cyl_src);
    mCyl.SetStts(&mStts);
    mAcchCir.SetWall(30.0f, 30.0f);
    mAcch.Set(&current.pos, &next.pos, this, 1, &mAcchCir, &speed, NULL, NULL);
    mAcch.OnSeaCheckOn();
    mAcch.OnSeaWaterHeight();
    
    mbPlayedSe = false;
    mGravity = m_data.mGravity;
    mMode = MODE_WAIT;
    current.pos.y -= m_data.mYOffset;
    
    mBckAnm.entry(mpModel->getModelData());
    
    set_mtx();
    
    mpModel->calc();
    dKy_plight_set(&mLight);
    setPointLight();
    
    mLightFlickerMult = 1.0f;
    regist(this);
}

/* 800F441C-800F4544       .text _daIball_draw__9daIball_cFv */
BOOL daIball_c::_daIball_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &mTevStr);
    g_env_light.setLightTevColorType(mpModel, &mTevStr);
    
    for (int i = 0; i < (int)ARRAY_SIZE(mBrkAnm); i++) {
        mBrkAnm[i].entry(mpModel->getModelData());
    }
    mBtkAnm.entry(mpModel->getModelData());
    mBckAnm.entry(mpModel->getModelData());
    
    dComIfGd_setListMaskOff();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
    
    dComIfGd_setSimpleShadow2(
        &current.pos, mAcch.GetGroundH(), 30.0f, mAcch.m_gnd,
        0, 1.0f, dDlst_shadowControl_c::getSimpleTex()
    );
    
    return TRUE;
}

/* 800F4544-800F4634       .text _daIball_execute__9daIball_cFv */
BOOL daIball_c::_daIball_execute() {
    mEyePos = current.pos;
    mEyePos.y = current.pos.y + 45.0f;
    
    mTimer++;
    
    setPointLight();
    
    if (!mbPlayedSe) {
        fopAcM_seStartCurrent(this, JA_SE_CM_INOCHIDAMA, 0);
        mbPlayedSe = true;
    }
    
    checkGeo();
    animControl();
    damage();
    set_mtx();
    
    mCyl.SetC(current.pos);
    dComIfG_Ccsp()->Set(&mCyl);
    
    return TRUE;
}

/* 800F4634-800F4678       .text _daIball_delete__9daIball_cFv */
BOOL daIball_c::_daIball_delete() {
    mRippleCb.end();
    dKy_plight_cut(&mLight);
    remove(this);
    return TRUE;
}

/* 800F4678-800F4698       .text CheckCreateHeap__FP10fopAc_ac_c */
static void CheckCreateHeap(fopAc_ac_c* i_this) {
    static_cast<daIball_c*>(i_this)->CreateHeap();
}

/* 800F4698-800F4870       .text _daIball_create__9daIball_cFv */
s32 daIball_c::_daIball_create() {
    fopAcM_SetupActor(this, daIball_c);
    
    if (!fopAcM_entrySolidHeap(this, (heapCallbackFunc)CheckCreateHeap, 0x3500)) {
        return cPhs_ERROR_e;
    }
    
    CreateInit();
    
    return cPhs_COMPLEATE_e;
}

/* 800F489C-800F4B40       .text CreateHeap__9daIball_cFv */
BOOL daIball_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, ALWAYS_BDL_IB);
    JUT_ASSERT(1135, modelData != 0);
    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000222);
    if (!mpModel) { return FALSE; }
    
    J3DAnmTransform* pbck = (J3DAnmTransform*)dComIfG_getObjectRes(m_arcname, ALWAYS_BCK_START);
    JUT_ASSERT(1152, pbck != 0);
    int ret = mBckAnm.init(modelData, pbck, 1, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, 0, -1, false);
    if (!ret) { return FALSE; }
    
    J3DAnmTextureSRTKey* pbtk = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes(m_arcname, ALWAYS_BTK_IB);
    JUT_ASSERT(1164, pbtk != 0);
    ret = mBtkAnm.init(modelData, pbtk, 1, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, false, 0);
    if (!ret) { return FALSE; }
    
    int brkIds[ARRAY_SIZE(mBrkAnm)] = {
        ALWAYS_BRK_IB_01,
        ALWAYS_BRK_IB_02,
    };
    J3DAnmTevRegKey* pbrk;
    for (int i = 0; i < (int)ARRAY_SIZE(mBrkAnm); i++) {
        pbrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(m_arcname, brkIds[i]);
        JUT_ASSERT(1182, pbrk != 0);
        ret = mBrkAnm[i].init(modelData, pbrk, 1, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, false, 0);
        if (!ret) { return FALSE; }
    }
    
    return TRUE;
}

/* 800F4B40-800F4B60       .text daIball_Create__FP10fopAc_ac_c */
static s32 daIball_Create(fopAc_ac_c* i_this) {
    return static_cast<daIball_c*>(i_this)->_daIball_create();
}

/* 800F4B60-800F4B80       .text daIball_Draw__FP9daIball_c */
static BOOL daIball_Draw(daIball_c* i_this) {
    return i_this->_daIball_draw();
}

/* 800F4B80-800F4BA0       .text daIball_Delete__FP9daIball_c */
static BOOL daIball_Delete(daIball_c* i_this) {
    return i_this->_daIball_delete();
}

/* 800F4BA0-800F4BA8       .text daIball_IsDelete__FP9daIball_c */
static BOOL daIball_IsDelete(daIball_c* i_this) {
    return TRUE;
}

/* 800F4BA8-800F4BC8       .text daIball_Execute__FP9daIball_c */
static BOOL daIball_Execute(daIball_c* i_this) {
    return i_this->_daIball_execute();
}

actor_method_class l_daIball_Method = {
    (process_method_func)daIball_Create,
    (process_method_func)daIball_Delete,
    (process_method_func)daIball_Execute,
    (process_method_func)daIball_IsDelete,
    (process_method_func)daIball_Draw,
};

actor_process_profile_definition g_profile_Iball = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 7,
    /* ListPrio     */ fpcLy_CURRENT_e,
    /* ProcName     */ PROC_Iball,
    /* Proc SubMtd  */ &g_fpcLf_Method.mBase,
    /* Size         */ sizeof(daIball_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x0187,
    /* Actor SubMtd */ &l_daIball_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
