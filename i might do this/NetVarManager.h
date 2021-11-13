#pragma once
#include "pch.h"


class RecvTable
{
public:

    RecvProp* m_pProps;
    int            m_nProps;
    void* m_pDecoder;
    char* m_pNetTableName;
    bool        m_bInitialized;
    bool        m_bInMainList;
};

class RecvProp
{
public:
    char* m_pVarName;
    void* m_RecvType;
    int                     m_Flags;
    int                     m_StringBufferSize;
    int                     m_bInsideArray;
    const void* m_pExtraData;
    RecvProp* m_pArrayProp;
    void* m_ArrayLengthProxy;
    void* m_ProxyFn;
    void* m_DataTableProxyFn;
    RecvTable* m_pDataTable;
    int                     m_Offset;
    int                     m_ElementStride;
    int                     m_nElements;
    const char* m_pParentArrayPropName;
};

class ClientClass
{
public:
	void*		m_pCreateFn;
	void*			m_pCreateEventFn;	// Only called for event objects.
	const char* m_pNetworkName;
	RecvTable* m_pRecvTable;
	ClientClass* m_pNext;
	int						m_ClassID;	// Managed by the engine.
};

intptr_t GetOffset(RecvTable* table, const char* tablename, const char* netvarname) {
    for (int i = 0; i < table->m_nProps; ++i) {
        RecvProp prop = table->m_pProps[i];

        if (!_stricmp(prop.m_pVarName, netvarname)) {
            return prop.m_Offset;
        }
        if (prop.m_pDataTable) {
            intptr_t offset = GetOffset(prop.m_pDataTable, tablename, netvarname);

        if (offset) {
            return offset + prop.m_Offset;
        }

        }
    }
}