#ifndef DBDataManager_h__
#define DBDataManager_h__

#include <QtWidgets>
#include <QtSql>
#include "ui_DBDataManager.h"

class CDBDataManager : public QWidget, public Ui::CDBDataManager
{
    Q_OBJECT
private:
	struct stTableColumnInfo
	{
		stTableColumnInfo()
		{
			isIdentity = false;
			isKey= false;
			isNullAble = false;
		}
		QString columnName;	//字段名
		QString dbType;				//字段类型(数据库)
		bool		isIdentity;			//是否是自增长字段
		bool		isKey;					//是否主键
		bool       isNullAble;			//是否可为空
		QString desc;					//描述
	};
	typedef QList<stTableColumnInfo>  ListTableColumnInfo;
	typedef QMap<QString, ListTableColumnInfo*> MapTableNameToColumns;

public:
	explicit CDBDataManager(QWidget *parent = 0);
	~CDBDataManager();

public:
	static void setServerAddr(const QString& ip);
	static void setDrgameUserAndPWD(const QString& user, const QString& pwd);
	static void setDroiyanUserAndPWD(const QString& user, const QString& pwd);

protected:
	void showEvent(QShowEvent *event);

private:

	void initDBTablesOnTreeWidget();

	void outputTableClassWithData(const QString& outputPath, const QString& name, const ListTableColumnInfo& colInfo);
	
	static bool createDrgameDBConnect(QSqlDatabase& db);
	static bool createDroiyanDBConnect(QSqlDatabase& db);

	static QString dbTypeToQtType(const QString& dbType);
	static bool readTablesColumns(QSqlDatabase& db, MapTableNameToColumns& data);
	static void releaseTableColumnsData(MapTableNameToColumns& data);

protected Q_SLOTS:
	void on_pushButtonExport_clicked(bool checked);
	void on_treeWidgetTabls_itemDoubleClicked(QTreeWidgetItem * item, int column);



private:
	static QString g_serverAddr;
	static QString g_drgameUser;
	static QString g_drgamePWD;
	static QString g_droiyanUser;
	static QString g_droiyanPWD;

	MapTableNameToColumns m_drgameTableColumns;
	MapTableNameToColumns m_droiyanTableColumns;

	QTreeWidgetItem *m_drgameNode;
	QTreeWidgetItem *m_droiyanNode;

	QByteArray m_headTemplate;
	QByteArray m_sourceTemplate;
};
#endif // DBDataManager_h__
