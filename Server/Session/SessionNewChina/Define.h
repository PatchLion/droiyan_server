#ifndef _DEFINE_H_
#define _DEFINE_H_

#define IP_LENGTH 16

#include "CP_IP_MASKTable.h"

typedef CTypedPtrArray <CPtrArray, CCP_IP_MASKTable*>		CP_IP_TableArray;

extern CP_IP_TableArray		g_arCP_IP_Table;


#endif
