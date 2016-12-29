#include "Char.h"

QX_REGISTER_CPP_QX_DATABASE(CChar)

namespace qx {
	template <> void register_class(QxClass<CChar> & t)
	{
		t.setName("CHARS");

		t.id(&CChar::account, "strAccount");
		t.data(&CChar::char01, "strChar01");
		t.data(&CChar::char02, "strChar02");
		t.data(&CChar::char03, "strChar03");

		t.fct_0<int>(&CChar::charNum, "sCharNum");
	}
}
