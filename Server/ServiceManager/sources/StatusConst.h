#if !defined ___STATUSCONST_H
#define ___STATUSCONST_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#define PRINT_DEFAULT            0
#define PRINT_BILL_ALL           1
#define PRINT_BILL               2
#define PRINT_TAX                3
#define PRINT_ADDR               4
#define COL_MAX                 11


#if !defined ___COLUMN_TITLE_H
extern LPCOLINFO ColInfo;
#endif // !defined ___COLUMN_TITLE_H


#endif // !defined ___STATUSCONST_H