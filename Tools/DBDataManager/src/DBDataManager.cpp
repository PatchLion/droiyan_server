#include "DBDataManager.h"
#include <QtWidgets>
#include <QtCore>


QString CDBDataManager::g_serverAddr = "127.0.0.1";
QString CDBDataManager::g_drgameUser = "drgame";
QString CDBDataManager::g_drgamePWD = "drgame";
QString CDBDataManager::g_droiyanUser = "droiyan";
QString CDBDataManager::g_droiyanPWD = "droiyan";

const char* kHeadTemplateFileName = "TEMPLATE_H";
const char* kSourceTemplateFileName = "TEMPLATE_CPP";
const char* kAllTableInfoFileName = "ALL_TABEL_INFO.sql";

//Key word
const QString kClassName = "$$CLASSNAME$$";
const QString kClassNameLower = "$$CLASSNAMELOWER$$";
const QString kMembers = "$$MEMBERAREA$$";
const QString kImplArea = "$$IMPLAREA$$";
const QString kIdenAnno = "$$IDENANNO$$";	//主键为非自增长

CDBDataManager::CDBDataManager(QWidget *parent /*= 0*/)
	: QWidget(parent)
{
	setupUi(this);

	//tables
	treeWidgetTabls->headerItem()->setHidden(true);
	m_drgameNode = new QTreeWidgetItem(treeWidgetTabls);
	m_drgameNode->setText(0, "drgame");
	m_drgameNode->setCheckState(0, Qt::Unchecked);
	m_drgameNode->setFlags(m_drgameNode->flags() | Qt::ItemIsUserCheckable);

	m_droiyanNode = new QTreeWidgetItem(treeWidgetTabls);
	m_droiyanNode->setText(0, "droiyan");
	m_droiyanNode->setCheckState(0, Qt::Unchecked);
	m_droiyanNode->setFlags(m_drgameNode->flags() | Qt::ItemIsUserCheckable);

	//struct table
	QStringList listHeads;
	listHeads << QString::fromLocal8Bit("列名");
	listHeads << QString::fromLocal8Bit("数据类型");
	listHeads << QString::fromLocal8Bit("自增长");
	listHeads << QString::fromLocal8Bit("主键");
	listHeads << QString::fromLocal8Bit("可为空值");
	tableWidgetStruct->setColumnCount(listHeads.size());
	tableWidgetStruct->setColumnWidth(0, 140);  //设置列宽
	tableWidgetStruct->setColumnWidth(1, 80);  //设置列宽
	tableWidgetStruct->setColumnWidth(2, 45);  //设置列宽
	tableWidgetStruct->setColumnWidth(3, 40);  //设置列宽
	tableWidgetStruct->setColumnWidth(4, 80);  //设置列宽
	tableWidgetStruct->setHorizontalHeaderLabels(listHeads);
	tableWidgetStruct->verticalHeader()->setHidden(true);

	//Head template
	QFile file(kHeadTemplateFileName);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		m_headTemplate = file.readAll();
	}
	else
	{
		qWarning() << "Failed to read head template file!";
	}

	//Source template
	QFile file2(kSourceTemplateFileName);
	if (file2.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		m_sourceTemplate = file2.readAll();
	}
	else
	{
		qWarning() << "Failed to read source template file!";
	}


}

CDBDataManager::~CDBDataManager()
{
	releaseTableColumnsData(m_drgameTableColumns);
	releaseTableColumnsData(m_droiyanTableColumns);
}	

void CDBDataManager::on_pushButtonExport_clicked(bool checked)
{
	QStringList listDrgameTableName;

	if (m_drgameNode)
	{
		for (int i = 0; i < m_drgameNode->childCount(); i++)
		{
			QTreeWidgetItem* child = m_drgameNode->child(i);
			if (child && Qt::Checked == child->checkState(0))
			{
				listDrgameTableName << child->text(0).trimmed();
			}
		}
	}
	
	QStringList listDroiyanTableName;
	if (m_droiyanNode)
	{
		for (int i = 0; i < m_droiyanNode->childCount(); i++)
		{
			QTreeWidgetItem* child = m_droiyanNode->child(i);
			if (child && Qt::Checked == child->checkState(0))
			{
				listDroiyanTableName << child->text(0).trimmed();
			}
		}
	}

	if (listDrgameTableName.isEmpty() && listDroiyanTableName.isEmpty())
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("没有生成"), QString::fromLocal8Bit("请选择要输出的表"));
	}
	else
	{
		if (!listDrgameTableName.isEmpty())
		{
			const QString drgameDir = "./DB_Classes/drgame/";
			if (!QDir().exists(drgameDir))
			{
				QDir().mkpath(drgameDir);
			}

			for (int i = 0; i < listDrgameTableName.size(); i++)
			{
				const QString name = listDrgameTableName[i];

				MapTableNameToColumns::iterator colItor = m_drgameTableColumns.find(name);

				if (m_drgameTableColumns.end() != colItor)
				{
					outputTableClassWithData(drgameDir, name, *(colItor.value()));
				}
			}

		}


		if (!listDroiyanTableName.isEmpty())
		{
			const QString droiyanDir = "./DB_Classes/droiyan/";
			if (!QDir().exists(droiyanDir))
			{
				QDir().mkpath(droiyanDir);
			}

			for (int i = 0; i < listDroiyanTableName.size(); i++)
			{
				const QString name = listDroiyanTableName[i];

				MapTableNameToColumns::iterator colItor = m_droiyanTableColumns.find(name);

				if (m_droiyanTableColumns.end() != colItor)
				{
					outputTableClassWithData(droiyanDir, name, *(colItor.value()));
				}
			}
		}


		QMessageBox::information(this, QString::fromLocal8Bit("生成完毕"), QString::fromLocal8Bit("所有表的ORM类生成完毕"));
	}
}

void CDBDataManager::initDBTablesOnTreeWidget()
{
	//drgame
	if (m_drgameNode)
	{
		
		MapTableNameToColumns::iterator colItor = m_drgameTableColumns.begin();
		for (colItor; m_drgameTableColumns.end() != colItor; colItor++)
		{
			QTreeWidgetItem* node = new QTreeWidgetItem(m_drgameNode);
			node->setText(0, colItor.key());
			node->setCheckState(0, Qt::Unchecked);
			node->setFlags(node->flags() | Qt::ItemIsUserCheckable);
		}
		
		m_drgameNode->setExpanded(true);
	}

	//droiyan
	if (m_droiyanNode)
	{
		MapTableNameToColumns::iterator colItor = m_droiyanTableColumns.begin();
		for (colItor; m_droiyanTableColumns.end() != colItor; colItor++)
		{
			QTreeWidgetItem* node = new QTreeWidgetItem(m_droiyanNode);
			node->setText(0, colItor.key());
			node->setCheckState(0, Qt::Unchecked);
			node->setFlags(node->flags() | Qt::ItemIsUserCheckable);
		}

		m_droiyanNode->setExpanded(true);
	}
}

void CDBDataManager::setServerAddr(const QString& ip)
{
	g_serverAddr = ip;
}

void CDBDataManager::setDrgameUserAndPWD(const QString& user, const QString& pwd)
{
	g_drgameUser = user; 
	g_drgamePWD = pwd;
}

void CDBDataManager::setDroiyanUserAndPWD(const QString& user, const QString& pwd)
{
	g_droiyanUser = user;
	g_droiyanPWD = pwd;
}


bool CDBDataManager::createDrgameDBConnect(QSqlDatabase& db)
{
	db = QSqlDatabase::addDatabase("QODBC");
	const QString drgameDN = QString::fromLocal8Bit("DRIVER={SQL SERVER};SERVER=%1;DATABASE=drgame;UID=%2;PWD=%3;")
		.arg(g_serverAddr).arg(g_drgameUser).arg(g_drgamePWD);
	db.setDatabaseName(drgameDN);
	db.setHostName(g_serverAddr);
	db.setUserName(g_drgameUser);
	db.setPassword(g_drgamePWD);
	if (!db.open())
	{
		qWarning() << "Cannot open database [drgame]: " << db.lastError().databaseText();
		return false;
	}
	else
	{
		qDebug() << "Connect to Database [drgame] Success!";
		return true;
	}
}

bool CDBDataManager::createDroiyanDBConnect(QSqlDatabase& db)
{
	db = QSqlDatabase::addDatabase("QODBC");
	const QString droiyanDN = QString::fromLocal8Bit("DRIVER={SQL SERVER};SERVER=%1;DATABASE=droiyan;UID=%2;PWD=%3;")
		.arg(g_serverAddr).arg(g_droiyanUser).arg(g_droiyanPWD);
	db.setDatabaseName(droiyanDN);
	db.setHostName(g_serverAddr);
	db.setUserName(g_droiyanUser);
	db.setPassword(g_droiyanPWD);
	if (!db.open())
	{
		qWarning() << "Cannot open database [droiyan]: " << db.lastError().databaseText();
		return false;
	}
	else
	{
		qDebug() << "Connect to Database [droiyan] Success!";
		return true;
	}
}

void CDBDataManager::on_treeWidgetTabls_itemDoubleClicked(QTreeWidgetItem * item, int column)
{
	tableWidgetStruct->setRowCount(0);

	if (item->parent())
	{

		MapTableNameToColumns::iterator colItor;

		const QString name = item->text(0);
		if (item->parent() == m_drgameNode)
		{
			qDebug() <<"table " << name << " in [drgame] clicked!";
			colItor = m_drgameTableColumns.find(name);

			if (m_drgameTableColumns.end() == colItor)
			{
				qWarning() << "Can not find table " << name << " data";
				return;
			}
		}
		else if (item->parent() == m_droiyanNode)
		{
			qDebug() << "table " << name << " in [droiyan] clicked!";
			colItor = m_droiyanTableColumns.find(name);

			if (m_droiyanTableColumns.end() == colItor)
			{
				qWarning() << "Can not find table " << name << " data";
				return;
			}
		}

		for (int i = 0; i < colItor.value()->size(); i++)
		{
			const stTableColumnInfo& colInfo = colItor.value()->at(i);
			QString name = colInfo.columnName;
			QString type = colInfo.dbType;
			bool isIdentity = colInfo.isIdentity;
			bool isKey = colInfo.isKey;
			bool isnullable = colInfo.isNullAble;
			if (!name.isEmpty() && !type.isEmpty())
			{
				tableWidgetStruct->insertRow(i);
				QTableWidgetItem* nameItem = new QTableWidgetItem(name);
				nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
				tableWidgetStruct->setItem(i, 0, nameItem);

				QTableWidgetItem* typeItem = new QTableWidgetItem(type);
				typeItem->setFlags(typeItem->flags() & ~Qt::ItemIsEditable);
				tableWidgetStruct->setItem(i, 1, typeItem);

				QTableWidgetItem* idItem = new QTableWidgetItem(isIdentity ? QString::fromLocal8Bit("√"): "");
				idItem->setTextAlignment(Qt::AlignCenter);
				idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
				tableWidgetStruct->setItem(i, 2, idItem);

				QTableWidgetItem* keyItem = new QTableWidgetItem(isKey ? QString::fromLocal8Bit("√") : "");
				keyItem->setFlags(keyItem->flags() & ~Qt::ItemIsEditable);
				keyItem->setTextAlignment(Qt::AlignCenter);
				tableWidgetStruct->setItem(i, 3, keyItem);

				QTableWidgetItem* nullableItem = new QTableWidgetItem(isnullable ? QString::fromLocal8Bit("√") : "");
				nullableItem->setFlags(nullableItem->flags() & ~Qt::ItemIsEditable);
				nullableItem->setTextAlignment(Qt::AlignCenter);
				tableWidgetStruct->setItem(i, 4, nullableItem);
			}
		}
	}
}


void CDBDataManager::outputTableClassWithData(const QString& outputPath, const QString& name, const ListTableColumnInfo& colInfo)
{
	QByteArray headTemp = m_headTemplate;
	QByteArray sourceTemp = m_sourceTemplate;

	headTemp = headTemp.replace(kClassName, name.toLocal8Bit());
	headTemp = headTemp.replace(kClassNameLower, name.toLower().toLocal8Bit());

	sourceTemp = sourceTemp.replace(kClassName, name.toLocal8Bit());

	const QString headFilePath = outputPath + "/" + name + ".h";
	const QString sourceFilePath = outputPath + "/" + name + ".cpp";
	QFile headFile(headFilePath);
	if(headFile.exists())	headFile.remove();
	QFile sourceFile(sourceFilePath);
	if (sourceFile.exists()) sourceFile.remove();

	//replace memer
	QString members;
	QString implmembers;
	bool haveID = false;
	for (int i = 0; i < colInfo.size(); i++)
	{
		const stTableColumnInfo& col = colInfo[i];
		members += dbTypeToQtType(col.dbType) + " " + col.columnName + ";\n";

		if (col.isIdentity)
		{
			haveID = true;
		}

		/*
		t.id(&CUser::id, "userid");
		t.data(&CUser::name, "name");
		t.data(&CUser::sex, "sex");
		t.fct_0<int>(&CUser::age, "age");
		*/

		if (!col.isIdentity)
		{
			if (col.isKey)
			{
				implmembers += QString("t.id(&%1::%2, \"%3\");\n").arg(name).arg(col.columnName).arg(col.columnName);
			}
			else 
			{
				implmembers += QString("t.data(&%1::%2, \"%3\");\n").arg(name).arg(col.columnName).arg(col.columnName);
			}
		}
	
	}

	headTemp = headTemp.replace(kIdenAnno, haveID ? "//" : "");
	
	headTemp = headTemp.replace(kMembers, members.toLocal8Bit());
	sourceTemp = sourceTemp.replace(kImplArea, implmembers.toLocal8Bit());

	QFile newHeadFile(headFilePath);
	if (newHeadFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
	{
		newHeadFile.write(headTemp);
		newHeadFile.close();
	}
	else
	{
		qWarning() << "Failed to open file: " << headFilePath;
	}

	QFile newSourceFile(sourceFilePath);
	if (newSourceFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
	{
		newSourceFile.write(sourceTemp);
		newSourceFile.close();
	}
	else
	{
		qWarning() << "Failed to open file: " << sourceFilePath;
	}
}

QString CDBDataManager::dbTypeToQtType(const QString& dbType)
{
	const QString temp = dbType.trimmed().toLower();
	if ("int" == temp)	return "int";
	if ("varchar" == temp || "nvarchar" == temp)	return "QString";
	if ("smallint" == temp)	return "short";
	if ("varbinary" == temp || "image" == temp)	 return "QByteArray";
	if ("tinyint" == temp)	return "short";
	if ("smalldatetime" == temp || "datetime" == temp)	return "QDateTime";


	return "UNKNOWN_TYPE";
}

bool CDBDataManager::readTablesColumns(QSqlDatabase& db, CDBDataManager::MapTableNameToColumns& data)
{
	releaseTableColumnsData(data);

	QFile file(kAllTableInfoFileName);
	if (file.open(QIODevice::ReadOnly))
	{
		QByteArray temp = file.readAll();
		QSqlQuery query = db.exec(QString::fromLocal8Bit(temp));

		if (query.isValid())
		{
			qWarning() << "readTablesColumns error: " << query.lastError().text();
			return false;
		}

		ListTableColumnInfo *currentListCol = 0;
		while (query.next())
		{
			const QString tableName = query.value(0).toString().trimmed();
			if (!tableName.isEmpty())
			{
				currentListCol = new ListTableColumnInfo;
				data.insert(tableName, currentListCol);
			}

			stTableColumnInfo tableColInfo;
			tableColInfo.columnName = query.value(3).toString();
			tableColInfo.isIdentity = !query.value(4).toString().trimmed().isEmpty();
			tableColInfo.isKey = !query.value(5).toString().trimmed().isEmpty();
			tableColInfo.dbType = query.value(6).toString().trimmed().toLower();
			tableColInfo.isNullAble = !query.value(10).toString().trimmed().isEmpty();
			tableColInfo.desc = query.value(12).toString();

			currentListCol->push_back(tableColInfo);
		}

		return true;
	}
	else
	{
		qWarning() << "Failed to read \"" << kAllTableInfoFileName << "\"";
		return false;
	}
}

void CDBDataManager::releaseTableColumnsData(MapTableNameToColumns& data)
{
	MapTableNameToColumns::iterator colItor = data.begin();
	for (colItor; data.end() != colItor; colItor++)
	{
		if (colItor.value())
		{
			delete colItor.value();
		}
	}
	data.clear();
}

void CDBDataManager::showEvent(QShowEvent *event)
{
	QSqlDatabase drgameDB;
	if (createDrgameDBConnect(drgameDB))
	{
		readTablesColumns(drgameDB, m_drgameTableColumns);
	}

	QSqlDatabase droiyanDB;
	if (createDroiyanDBConnect(droiyanDB))
	{
		readTablesColumns(droiyanDB, m_droiyanTableColumns);
	}

	if (m_drgameTableColumns.isEmpty())
	{
		qWarning() << "Failed to read [drgame] columns!";
	}

	if (m_droiyanTableColumns.isEmpty())
	{
		qWarning() << "Failed to read [droiyan] columns!";
	}

	initDBTablesOnTreeWidget();
}


