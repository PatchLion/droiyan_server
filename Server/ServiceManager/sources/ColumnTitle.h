#if !defined ___COLUMN_TITLE_H
#define ___COLUMN_TITLE_H

#include "StatusConst.h"


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#ifdef _USE_ENGLISH
static const LPTSTR ColumnTitle[]={ "Access Address",    //  0
			  				        "Available ID for registration",       //  1
							        "Log Out",         //  2
							        "Used Time",         //  3
									"Password",         //  4
									"Beginning Date",         //  5
									"Ending Date",         //  6
									"Charge Code",         //  7
									"Ending Code",         //  8
									"Deposit Bank",         //  9
									"Used Period",         // 10
									"Date of receipt",         // 11
									"Reason of suspension",         // 12
									"Registered ID",         // 13
									"User ID",         // 14
									"Depositor",           // 15
									"Login",           // 16
									"Amount of deposit",           // 17
									"Operator",           // 18
									"Date of registration",           // 19
									"Date of termination",           // 20
									"Service",           // 21
 			 						"Number",             // 22
									"Type",             // 23
									"Variety",             // 24
									"Process",             // 25
									"Note",             // 26
									"Firm Name",             // 27
									"Registered Business Number",  // 28
									"Charge",           // 29
									"VAT" };         // 30
#else
static const LPTSTR ColumnTitle[]={ "접속 어드레스",    //  0
			  				        "등록가능ID",       //  1
							        "로그아웃",         //  2
							        "이용시간",         //  3
									"비밀번호",         //  4
									"시작일자",         //  5
									"종료일자",         //  6
									"과금코드",         //  7
									"종료코드",         //  8
									"입금은행",         //  9
									"사용기간",         // 10
									"입금일자",         // 11
									"정지사유",         // 12
									"등록된ID",         // 13
									"사용자ID",         // 14
									"입금자",           // 15
									"로그인",           // 16
									"입금액",           // 17
									"작업자",           // 18
									"등록일",           // 19
									"해제일",           // 20
									"서비스",           // 21
 			 						"번호",             // 22
									"타입",             // 23
									"종류",             // 24
									"처리",             // 25
									"비고",             // 26
									"상호",             // 27
									"사업자 등록번호",  // 28
									"사용료",           // 29
									"부가세" };         // 30
#endif

static const COLUMNINFO LogColumn[] = { { 70, ColumnTitle[21]}     // 서비스
                                       ,{ 90, ColumnTitle[14]}     // 사용자ID
									   ,{120, ColumnTitle[16]}     // 로그인
									   ,{120, ColumnTitle[2] }     // 로그아웃
									   ,{ 60, ColumnTitle[3] }     // 이용시간
									   ,{ 60, ColumnTitle[7] }     // 과금코드
									   ,{ 60, ColumnTitle[8] }     // 종료코드
									   ,{100, ColumnTitle[0] } };  // 접속 어드레스

static const COLUMNINFO SerialColumn[] = { { 50, ColumnTitle[22]}     // 번호
                                          ,{ 80, ColumnTitle[23]}     // 타입
										  ,{ 90, ColumnTitle[4] }     // 비밀번호
										  ,{110, ColumnTitle[5] }     // 시작일자
										  ,{110, ColumnTitle[6] }     // 종료일자
										  ,{ 80, ColumnTitle[1] }     // 등록가능ID
										  ,{ 80, ColumnTitle[13]}     // 등록된ID
										  ,{ 60, ColumnTitle[10]} };  // 사용기간

static const COLUMNINFO BankColumn[] = { { 60, ColumnTitle[22]}     // 번호
                                        ,{120, ColumnTitle[11]}     // 입금일자
										,{ 90, ColumnTitle[15]}     // 입금자
										,{ 90, ColumnTitle[9] }     // 입금은행
										,{ 90, ColumnTitle[17]}     // 입금액
										,{ 90, ColumnTitle[24]}     // 종류
										,{ 90, ColumnTitle[25]}     // 처리
										,{ 90, ColumnTitle[18]}     // 작업자
										,{200, ColumnTitle[26]} };  // 비고

static const COLUMNINFO BadIDColumn[] = { { 90, ColumnTitle[14]}     // 사용자ID
								         ,{120, ColumnTitle[19]}     // 등록일
								         ,{120, ColumnTitle[20]}     // 해제일
								         ,{ 90, ColumnTitle[18]}     // 작업자
								         ,{200, ColumnTitle[12]} };  // 정지사유

static const COLUMNINFO ClientPayColumn[] = { {180, ColumnTitle[27]}     // 상호
											 ,{100, ColumnTitle[28]}     // 사업자 등록번호
											 ,{ 90, ColumnTitle[3] }     // 이용시간
											 ,{200, ColumnTitle[10]}     // 사용기간
											 ,{ 90, ColumnTitle[29]}     // 사용료
											 ,{ 90, ColumnTitle[30]} };  // 부가세

static const COLINFO __ColInfo[] = { { (LPCOLUMNINFO) LogColumn,       8}
						            ,{ (LPCOLUMNINFO) SerialColumn,    8}
						            ,{ (LPCOLUMNINFO) BankColumn,      9}
						            ,{ (LPCOLUMNINFO) BadIDColumn,     5}
									,{ (LPCOLUMNINFO) ClientPayColumn, 6} };


LPCOLINFO ColInfo = (LPCOLINFO) __ColInfo;

#endif // !defined ___COLUMN_TITLE_H