//
// Generated by dtk
// Translation Unit: JKRAramArchive.cpp
//

#include "JSystem/JKernel/JKRAramArchive.h"
#include "JSystem/JKernel/JKRAram.h"
#include "JSystem/JKernel/JKRAramBlock.h"
#include "JSystem/JKernel/JKRAramHeap.h"
#include "JSystem/JKernel/JKRDecomp.h"
#include "JSystem/JKernel/JKRDvdFile.h"
#include "JSystem/JKernel/JKRDvdRipper.h"
#include "JSystem/JKernel/JKRDvdAramRipper.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "MSL_C/math.h"
#include "MSL_C/string.h"
#include "dolphin/os/OS.h"

/* 802B9FE0-802BA088       .text __ct__14JKRAramArchiveFlQ210JKRArchive15EMountDirection */
JKRAramArchive::JKRAramArchive(s32 entryNumber, JKRArchive::EMountDirection mountDirection) : JKRArchive(entryNumber, MOUNT_ARAM) {
    mMountDirection = mountDirection;

    if (!this->open(entryNumber)) {
        return;
    }

    mVolumeType = 'RARC';
    mVolumeName = mStringTable + mNodes->name_offset;
    JKRFileLoader::sVolumeList.prepend(&mFileLoaderLink);
    mIsMounted = true;
}

/* 802BA088-802BA1C8       .text __dt__14JKRAramArchiveFv */
JKRAramArchive::~JKRAramArchive() {
    if (mIsMounted == true) {
        if (mArcInfoBlock != NULL) {
            SDIFileEntry* entry = mFiles;
            for (int i = 0; i < mArcInfoBlock->num_file_entries; entry++, i++) {
                if (entry->data != NULL) {
                    JKRFreeToHeap(mHeap, entry->data);
                }
            }

            JKRFreeToHeap(mHeap, mArcInfoBlock);
            mArcInfoBlock = NULL;
        }

        if (mExpandedSize != NULL) {
            i_JKRFree(mExpandedSize);
            mExpandedSize = NULL;
        }

        if (mDvdFile != NULL) {
            delete mDvdFile;
        }

        if (mBlock != NULL) {
            delete mBlock;
        }

        JKRFileLoader::sVolumeList.remove(&mFileLoaderLink);
        mIsMounted = false;
    }
}

static void dummy() {
    OSReport(__FILE__);
    OSReport("isMounted()");
    OSReport("Halt");
    OSReport("mMountCount == 1");
}

/* 802BA1C8-802BA4EC       .text open__14JKRAramArchiveFl */
bool JKRAramArchive::open(s32 entryNum) {
    mArcInfoBlock = NULL;
    mNodes = NULL;
    mFiles = NULL;
    mStringTable = NULL;
    mBlock = NULL;

    mDvdFile = new (JKRGetSystemHeap(), mMountDirection == MOUNT_DIRECTION_HEAD ? 4 : -4) JKRDvdFile(entryNum);
    if (mDvdFile == NULL) {
        mMountMode = 0;
        return 0;
    }

    // NOTE: a different struct is used here for sure, unfortunately i can't get any hits on this address, so gonna leave it like this for now
    SArcHeader *mem = (SArcHeader *)JKRAllocFromSysHeap(32, -32);
    if (mem == NULL)  {
        mMountMode = 0;
    } else {
        JKRDvdToMainRam(entryNum, (u8 *)mem, EXPAND_SWITCH_UNKNOWN1, 32, NULL, JKRDvdRipper::ALLOC_DIRECTION_FORWARD, 0, &mCompression);
        int alignment = mMountDirection == MOUNT_DIRECTION_HEAD ? 32 : -32;
        u32 alignedSize = ALIGN_NEXT(mem->file_data_offset, 32);
        mArcInfoBlock = (SArcDataInfo *)JKRAllocFromHeap(mHeap, alignedSize, alignment);
        if (mArcInfoBlock == NULL) {
            mMountMode = 0;
        } else {
            JKRDvdToMainRam(entryNum, (u8 *)mArcInfoBlock, EXPAND_SWITCH_UNKNOWN1, alignedSize, NULL, JKRDvdRipper::ALLOC_DIRECTION_FORWARD, 32, NULL);

            mNodes = (SDIDirEntry *)((u8 *)mArcInfoBlock + mArcInfoBlock->node_offset);
            mFiles = (SDIFileEntry *)((u8 *)mArcInfoBlock + mArcInfoBlock->file_entry_offset);
            mStringTable = (char *)((u8 *)mArcInfoBlock + mArcInfoBlock->string_table_offset);
            mExpandedSize = NULL;

            u8 compressedFiles = 0; // maybe a check for if the last file is compressed?

            SDIFileEntry *fileEntry = mFiles;
            for (int i = 0; i < mArcInfoBlock->num_file_entries; i++) {
                u8 flag = fileEntry->type_flags_and_name_offset >> 24;
                if ((flag & 1))
                {
                    compressedFiles |= (flag & JKRARCHIVE_ATTR_COMPRESSION);
                }
                fileEntry++;
            }

            if (compressedFiles != 0) {
                mExpandedSize = (s32 *)JKRAllocFromHeap(mHeap, mArcInfoBlock->num_file_entries << 2, abs(alignment));
                if (mExpandedSize == NULL) {
                    i_JKRFree(mArcInfoBlock);
                    mMountMode = 0;
                    goto cleanup;
                }
                memset(mExpandedSize, 0, mArcInfoBlock->num_file_entries << 2);
            }

            u32 aramSize = ALIGN_NEXT(mem->file_data_length, 32);
            mBlock = (JKRAramBlock*) JKRAllocFromAram(aramSize, mMountDirection == MOUNT_DIRECTION_HEAD ? JKRAramHeap::HEAD : JKRAramHeap::TAIL);
            if(mBlock == NULL) {
                if (mArcInfoBlock) {
                    i_JKRFree(mArcInfoBlock);
                }
                if(mExpandedSize) {
                    i_JKRFree(mExpandedSize);
                }
                mMountMode = 0;
            }
            else {
                JKRDvdToAram(entryNum, mBlock->getAddress(), EXPAND_SWITCH_UNKNOWN1, mem->header_length + mem->file_data_offset, 0);
            }
        }
    }
cleanup:
    if (mem != NULL) {
        JKRFreeToSysHeap(mem);
    }
    if (mMountMode == 0) {
        OSReport(":::[%s: %d] Cannot alloc memory\n", __FILE__, 400);
        if (mDvdFile != NULL) {
            delete mDvdFile;
        }
        return false;
    }
    return true;
}

/* 802BA4EC-802BA640       .text fetchResource__14JKRAramArchiveFPQ210JKRArchive12SDIFileEntryPUl */
void* JKRAramArchive::fetchResource(SDIFileEntry* pEntry, u32* pOutSize) {
    JUT_ASSERT(427, isMounted());
    u32 outSize;
    u8* outBuf;
    if (pOutSize == NULL) {
        pOutSize = &outSize;
    }

    JKRCompression compression = JKRConvertAttrToCompressionType(pEntry->getFlags());
    if (pEntry->data == NULL) {
        u32 size = JKRAramArchive::fetchResource_subroutine(
            pEntry->data_offset + mBlock->getAddress(), pEntry->data_size, mHeap, compression,
            &outBuf);

        *pOutSize = size;
        if (size == NULL) {
            return NULL;
        }

        pEntry->data = outBuf;
        if (compression == COMPRESSION_YAZ0) {
            this->setExpandSize(pEntry, *pOutSize);
        }
    } else {
        if (compression == COMPRESSION_YAZ0) {
            *pOutSize = this->getExpandSize(pEntry);
        } else {
            *pOutSize = pEntry->data_size;
        }
    }

    return pEntry->data;
}

/* 802BA640-802BA788       .text fetchResource__14JKRAramArchiveFPvUlPQ210JKRArchive12SDIFileEntryPUl */
void* JKRAramArchive::fetchResource(void* buffer, u32 bufferSize, SDIFileEntry* pEntry, u32* resourceSize) {
    /* Nonmatching */
    JUT_ASSERT(500, isMounted());
    u32 size = pEntry->data_size;
    if (size > bufferSize) {
        size = bufferSize;
    }
    JKRCompression compression = JKRConvertAttrToCompressionType(pEntry->getFlags());
    if (pEntry->data == NULL) {
        // can't get it to store the result in r28
        bufferSize &= ~(0x20 - 1);
        size = JKRAramArchive::fetchResource_subroutine(pEntry->data_offset + mBlock->getAddress(),
                                                        size, (u8*)buffer, bufferSize, compression);
    } else {
        if (compression == COMPRESSION_YAZ0) {
            u32 expandSize = this->getExpandSize(pEntry);
            if (expandSize != NULL) {
                size = expandSize;
            }
        }
        if (size > bufferSize) {
            size = bufferSize;
        }
        JKRHeap::copyMemory(buffer, pEntry->data, size);
    }
    if (resourceSize != NULL) {
        *resourceSize = size;
    }
    return buffer;
}

/* 802BA788-802BA894       .text fetchResource_subroutine__14JKRAramArchiveFUlUlPUcUli */
u32 JKRAramArchive::fetchResource_subroutine(u32 srcAram, u32 srcLength, u8* dst, u32 dstLength, int compression) {
    JUT_ASSERT(613, ( srcAram & 0x1f ) == 0);
    u32 outLen;
    u32 srcSize = ALIGN_NEXT(srcLength, 0x20);
    u32 dstSize = ALIGN_PREV(dstLength, 0x20);

    switch (compression) {
    case COMPRESSION_NONE:
        if (srcSize > dstSize) {
            srcSize = dstSize;
        }
        JKRAramToMainRam(srcAram, dst, srcSize, EXPAND_SWITCH_UNKNOWN0, dstSize, NULL, -1, &outLen);
        return outLen;
    case COMPRESSION_YAY0:
    case COMPRESSION_YAZ0:
        JKRAramToMainRam(srcAram, dst, srcSize, EXPAND_SWITCH_UNKNOWN1, dstSize, NULL, -1, &outLen);
        return outLen;
    default:
        OSPanic(__FILE__, 640, ":::??? bad sequence\n");
        return 0;
    }
}

/* 802BA894-802BAA48       .text fetchResource_subroutine__14JKRAramArchiveFUlUlP7JKRHeapiPPUc */
u32 JKRAramArchive::fetchResource_subroutine(u32 entryNum, u32 length, JKRHeap* pHeap, int compression, u8** out) {
    u32 alignedLen = ALIGN_NEXT(length, 0x20);

    u8* buffer;
    switch (compression) {
    case COMPRESSION_NONE:
        {
            buffer = (u8*)(JKRAllocFromHeap(pHeap, alignedLen, 0x20));
            JUT_ASSERT(662, buffer != 0);
            JKRAramToMainRam(entryNum, buffer, alignedLen, EXPAND_SWITCH_UNKNOWN0, alignedLen, NULL, -1, NULL);
            *out = buffer;
            return length;
        }
    case COMPRESSION_YAY0:
    case COMPRESSION_YAZ0:
        {
            u8 headerBuf[0x40];
            u8* alignHeader = (u8*)ALIGN_NEXT((s32)&headerBuf[0], sizeof(SArcHeader));
            JKRAramToMainRam(entryNum, alignHeader, sizeof(SArcHeader), EXPAND_SWITCH_UNKNOWN0, 0, NULL, -1, NULL);
            u32 decompressedLen = ALIGN_NEXT(JKRDecompExpandSize(alignHeader), sizeof(SArcHeader));
            buffer = (u8*)(JKRAllocFromHeap(pHeap, decompressedLen, sizeof(SArcHeader)));
            JUT_ASSERT(688, buffer);
            u32 readLen;
            JKRAramToMainRam(entryNum, buffer, alignedLen, EXPAND_SWITCH_UNKNOWN1, decompressedLen, pHeap, -1, &readLen);
            *out = buffer;
            return readLen;
        }
    default:
        OSPanic(__FILE__, 698, ":::??? bad sequence\n");
        return 0;
    }
}

/* 802BAA48-802BAB74       .text getExpandedResSize__14JKRAramArchiveCFPCv */
u32 JKRAramArchive::getExpandedResSize(const void* ptr) const {
    if (mExpandedSize == NULL) {
        return this->getResSize(ptr);
    }

    JKRArchive::SDIFileEntry* entry = this->findPtrResource(ptr);
    if (entry == NULL) {
        return 0xFFFFFFFF;
    }

    if (entry->getCompressFlag() == 0) {
        return this->getResSize(ptr);
    }

    u32 expandSize = this->getExpandSize(entry);
    if (expandSize != 0) {
        return expandSize;
    }

    u8 tmpBuf[0x40];
    u8* buf = (u8*)ALIGN_PREV((s32)&tmpBuf[0x1F], 0x20);
    JKRAramToMainRam(entry->data_offset + mBlock->getAddress(), buf, 0x20,
                     EXPAND_SWITCH_UNKNOWN0, 0, NULL, -1, NULL);
    expandSize = JKRDecompExpandSize(buf);
    // ??? casting away const?
    ((JKRArchive*)this)->setExpandSize(entry, expandSize);
    return expandSize;
}

/* 802BAB74-802BABD4       .text __dt__7JKRFileFv */
//JKRFile::~JKRFile() {}
