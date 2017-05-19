//
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
//----------------------------------------------------------
// CompileResult.h - CompileResult contains the stuff generated by a compilation
//----------------------------------------------------------
#ifndef _CompileResult
#define _CompileResult

#include "runtimedetails.h"
#include "lightweightmap.h"

class CompileResult
{
public:
#pragma pack(push, 1)
    struct Agnostic_RecordRelocation
    {
        DWORDLONG location;
        DWORDLONG target;
        DWORD     fRelocType;
        DWORD     slotNum;
        DWORD     addlDelta;
    };
    struct Capture_AllocMemDetails
    {
        ULONG              hotCodeSize;
        ULONG              coldCodeSize;
        ULONG              roDataSize;
        ULONG              xcptnsCount;
        CorJitAllocMemFlag flag;
        void*              hotCodeBlock;
        void*              coldCodeBlock;
        void*              roDataBlock;
    };
    struct allocGCInfoDetails
    {
        size_t size;
        void*  retval;
    };
    struct Agnostic_AddressMap
    {
        DWORDLONG Address;
        DWORD     size;
    };
    struct Agnostic_AllocGCInfo
    {
        DWORDLONG size;
        DWORD     retval_offset;
    };
    struct Agnostic_AllocMemDetails
    {
        DWORD     hotCodeSize;
        DWORD     coldCodeSize;
        DWORD     roDataSize;
        DWORD     xcptnsCount;
        DWORD     flag;
        DWORD     hotCodeBlock_offset;
        DWORD     coldCodeBlock_offset;
        DWORD     roDataBlock_offset;
        DWORDLONG hotCodeBlock;
        DWORDLONG coldCodeBlock;
        DWORDLONG roDataBlock;
    };
    struct Agnostic_AllocUnwindInfo
    {
        DWORDLONG pHotCode;
        DWORDLONG pColdCode;
        DWORD     startOffset;
        DWORD     endOffset;
        DWORD     unwindSize;
        DWORD     pUnwindBlock_index;
        DWORD     funcKind;
    };
    struct Agnostic_CompileMethodResults
    {
        DWORDLONG nativeEntry;
        DWORD     nativeSizeOfCode;
        DWORD     CorJitResult;
    };
    struct Agnostic_ReportInliningDecision
    {
        DWORDLONG inlinerHnd;
        DWORDLONG inlineeHnd;
        DWORD     inlineResult;
        DWORD     reason_offset;
    };
    struct Agnostic_ReportTailCallDecision
    {
        DWORDLONG callerHnd;
        DWORDLONG calleeHnd;
        DWORD     fIsTailPrefix;
        DWORD     tailCallResult;
        DWORD     reason_index;
    };
    struct Agnostic_ReserveUnwindInfo
    {
        DWORD isFunclet;
        DWORD isColdCode;
        DWORD unwindSize;
    };
    struct Agnostic_SetBoundaries
    {
        DWORDLONG ftn;
        DWORD     cMap;
        DWORD     pMap_offset;
    };
    struct Agnostic_SetVars
    {
        DWORDLONG ftn;
        DWORD     cVars;
        DWORD     vars_offset;
    };
    struct Agnostic_CORINFO_EH_CLAUSE2
    {
        DWORD Flags;
        DWORD TryOffset;
        DWORD TryLength;
        DWORD HandlerOffset;
        DWORD HandlerLength;
        DWORD ClassToken; // one view of symetric union
    };
    struct Agnostic_AllocBBProfileBuffer
    {
        DWORD count;
        DWORD profileBuffer_index;
        DWORD result;
    };
    struct Agnostic_CORINFO_SIG_INFO2
    {
        DWORD     callConv;
        DWORDLONG retTypeClass;
        DWORDLONG retTypeSigClass;
        DWORD     retType;
        DWORD     flags;
        DWORD     numArgs;
        DWORD     sigInst_classInstCount;
        DWORD     sigInst_classInst_Index;
        DWORD     sigInst_methInstCount;
        DWORD     sigInst_methInst_Index;
        DWORDLONG args;
        DWORD     pSig;
        DWORD     cbSig;
        DWORDLONG scope;
        DWORD     token;
    };
    struct Agnostic_RecordCallSite
    {
        Agnostic_CORINFO_SIG_INFO2 callSig;
        DWORDLONG                  methodHandle;
    };
#pragma pack(pop)

    CompileResult();
    ~CompileResult();

    bool IsEmpty();

    void AddCall(const char* name);
    unsigned int CallLog_GetCount();
    bool CallLog_Contains(const char* str);
    void dmpCallLog(DWORD key, DWORD value);

    void dumpToConsole();

    HANDLE getCodeHeap();

    void recAssert(const char* buff);
    void dmpAssertLog(DWORD key, DWORD value);
    const char* repAssert();

    void recAllocMem(ULONG              hotCodeSize,
                     ULONG              coldCodeSize,
                     ULONG              roDataSize,
                     ULONG              xcptnsCount,
                     CorJitAllocMemFlag flag,
                     void**             hotCodeBlock,
                     void**             coldCodeBlock,
                     void**             roDataBlock);
    void recAllocMemCapture();
    void dmpAllocMem(DWORD key, const Agnostic_AllocMemDetails& value);
    void repAllocMem(ULONG*              hotCodeSize,
                     ULONG*              coldCodeSize,
                     ULONG*              roDataSize,
                     ULONG*              xcptnsCount,
                     CorJitAllocMemFlag* flag,
                     unsigned char**     hotCodeBlock,
                     unsigned char**     coldCodeBlock,
                     unsigned char**     roDataBlock,
                     void**              orig_hotCodeBlock,
                     void**              orig_coldCodeBlock,
                     void**              orig_roDataBlock);

    void recSetBoundaries(CORINFO_METHOD_HANDLE ftn, ULONG32 cMap, ICorDebugInfo::OffsetMapping* pMap);
    void dmpSetBoundaries(DWORD key, const Agnostic_SetBoundaries& value);
    bool repSetBoundaries(CORINFO_METHOD_HANDLE* ftn, ULONG32* cMap, ICorDebugInfo::OffsetMapping** pMap);

    void recSetVars(CORINFO_METHOD_HANDLE ftn, ULONG32 cVars, ICorDebugInfo::NativeVarInfo* vars);
    void dmpSetVars(DWORD key, const Agnostic_SetVars& value);
    bool repSetVars(CORINFO_METHOD_HANDLE* ftn, ULONG32* cVars, ICorDebugInfo::NativeVarInfo** vars);

    void recAllocGCInfo(size_t size, void* retval);
    void recAllocGCInfoCapture();
    void dmpAllocGCInfo(DWORD key, const Agnostic_AllocGCInfo& value);
    void repAllocGCInfo(size_t* size, void** retval);

    void recCompileMethod(BYTE** nativeEntry, ULONG* nativeSizeOfCode, CorJitResult result);
    void dmpCompileMethod(DWORD key, const Agnostic_CompileMethodResults& value);
    void repCompileMethod(BYTE** nativeEntry, ULONG* nativeSizeOfCode, CorJitResult* result);

    void recMessageLog(const char* fmt, ...);
    void dmpMessageLog(DWORD key, DWORD value);

    void recClassMustBeLoadedBeforeCodeIsRun(CORINFO_CLASS_HANDLE cls);
    void dmpClassMustBeLoadedBeforeCodeIsRun(DWORD key, DWORDLONG value);

    void recReportInliningDecision(CORINFO_METHOD_HANDLE inlinerHnd,
                                   CORINFO_METHOD_HANDLE inlineeHnd,
                                   CorInfoInline         inlineResult,
                                   const char*           reason);
    void dmpReportInliningDecision(DWORD key, const Agnostic_ReportInliningDecision& value);
    CorInfoInline repReportInliningDecision(CORINFO_METHOD_HANDLE inlinerHnd, CORINFO_METHOD_HANDLE inlineeHnd);

    void recSetEHcount(unsigned cEH);
    void dmpSetEHcount(DWORD key, DWORD value);
    ULONG repSetEHcount();

    void recSetEHinfo(unsigned EHnumber, const CORINFO_EH_CLAUSE* clause);
    void dmpSetEHinfo(DWORD key, const Agnostic_CORINFO_EH_CLAUSE2& value);
    void repSetEHinfo(unsigned EHnumber,
                      ULONG*   flags,
                      ULONG*   tryOffset,
                      ULONG*   tryLength,
                      ULONG*   handlerOffset,
                      ULONG*   handlerLength,
                      ULONG*   classToken);

    void recSetMethodAttribs(CORINFO_METHOD_HANDLE ftn, CorInfoMethodRuntimeFlags attribs);
    void dmpSetMethodAttribs(DWORDLONG key, DWORD value);
    CorInfoMethodRuntimeFlags repSetMethodAttribs(CORINFO_METHOD_HANDLE ftn);

    void recMethodMustBeLoadedBeforeCodeIsRun(CORINFO_METHOD_HANDLE method);
    void dmpMethodMustBeLoadedBeforeCodeIsRun(DWORD key, DWORDLONG value);

    void recReportTailCallDecision(CORINFO_METHOD_HANDLE callerHnd,
                                   CORINFO_METHOD_HANDLE calleeHnd,
                                   bool                  fIsTailPrefix,
                                   CorInfoTailCall       tailCallResult,
                                   const char*           reason);
    void dmpReportTailCallDecision(DWORD key, const Agnostic_ReportTailCallDecision& value);

    void recReportFatalError(CorJitResult result);
    void dmpReportFatalError(DWORD key, DWORD value);

    void recRecordRelocation(void* location, void* target, WORD fRelocType, WORD slotNum, INT32 addlDelta);
    void dmpRecordRelocation(DWORD key, const Agnostic_RecordRelocation& value);
    void repRecordRelocation(void* location, void* target, WORD fRelocType, WORD slotNum, INT32 addlDelta);
    void applyRelocs(unsigned char* block1, ULONG blocksize1, void* originalAddr);

    void recProcessName(const char* name);
    void dmpProcessName(DWORD key, DWORD value);
    const char* repProcessName();

    void recAddressMap(void* original_address, void* replay_address, unsigned int size);
    void dmpAddressMap(DWORDLONG key, const Agnostic_AddressMap& value);
    void* repAddressMap(void* replay_address);
    void* searchAddressMap(void* replay_address);

    void recReserveUnwindInfo(BOOL isFunclet, BOOL isColdCode, ULONG unwindSize);
    void dmpReserveUnwindInfo(DWORD key, const Agnostic_ReserveUnwindInfo& value);

    void recAllocUnwindInfo(BYTE*          pHotCode,
                            BYTE*          pColdCode,
                            ULONG          startOffset,
                            ULONG          endOffset,
                            ULONG          unwindSize,
                            BYTE*          pUnwindBlock,
                            CorJitFuncKind funcKind);
    void dmpAllocUnwindInfo(DWORD key, const Agnostic_AllocUnwindInfo& value);

    void recAllocBBProfileBuffer(ULONG count, ICorJitInfo::ProfileBuffer** profileBuffer, HRESULT result);
    void dmpAllocBBProfileBuffer(DWORD key, const Agnostic_AllocBBProfileBuffer& value);
    HRESULT repAllocBBProfileBuffer(ULONG count, ICorJitInfo::ProfileBuffer** profileBuffer);

    void recRecordCallSite(ULONG instrOffset, CORINFO_SIG_INFO* callSig, CORINFO_METHOD_HANDLE methodHandle);
    void dmpRecordCallSite(DWORD key, const Agnostic_RecordCallSite& value);
    void repRecordCallSite(ULONG instrOffset, CORINFO_SIG_INFO* callSig, CORINFO_METHOD_HANDLE methodHandle);
    bool fndRecordCallSiteSigInfo(ULONG instrOffset, CORINFO_SIG_INFO* pCallSig);
    bool fndRecordCallSiteMethodHandle(ULONG instrOffset, CORINFO_METHOD_HANDLE* pMethodHandle);

    DOUBLE    secondsToCompile;
    ULONGLONG clockCyclesToCompile;

#define LWM(map, key, value) LightWeightMap<key, value>* map;
#define DENSELWM(map, value) DenseLightWeightMap<value>* map;
#include "crlwmlist.h"

    // not persisted to disk.
public:
    LightWeightMap<DWORDLONG, DWORD>* CallTargetTypes;

private:
    HANDLE                  codeHeap;
    Capture_AllocMemDetails allocMemDets;
    allocGCInfoDetails      allocGCInfoDets;
};
#endif