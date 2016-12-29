#ifndef Char_h__
#define Char_h__
#include "precompiled.h"
#include <QxOrm_Impl.h>
class QX_DATABASE_DLL_EXPORT CChar
{
public:
	CChar() : charNum(0){}
	virtual ~CChar(){}

public:
	QString account;
	QString char01;
	QString char02;
	QString char03;
	int charNum;
};

QX_REGISTER_PRIMARY_KEY(CChar, QString)
QX_REGISTER_HPP_QX_DATABASE(CChar, qx::trait::no_base_class_defined, 0)

typedef qx_shared_ptr<CChar> char_ptr;
typedef qx::QxCollection<QString, char_ptr> list_char;
#endif // Char_h__
