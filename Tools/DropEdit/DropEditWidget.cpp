#include "DropEditWidget.h"
#include "ui_DropEditWidget.h"
#include <QtCore>
#include "Functions.h"

CDropEditWidget::CDropEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CDropEditWidget)
{
    ui->setupUi(this);

	initDropInfos();

	updateDropInfoListOnUI();
}

CDropEditWidget::~CDropEditWidget()
{
    delete ui;
}

void CDropEditWidget::initDropInfos()
{
	MapKey monsterKeyMap;
	MapKey itemKeyMap;

	m_listDropInfo.clear();

	const QString root_path = QApplication::applicationDirPath() + "/drop";

	QDir dir(root_path);
	QFileInfoList filelist = dir.entryInfoList(QDir::Files);

	Q_FOREACH(QFileInfo fileinfo, filelist)
	{
		qDebug() << "Read drop file: " << fileinfo.fileName();

		drop_info dropInfo;
		bool suc = DropEdit::getDropInfoFromINIFile(fileinfo.absoluteFilePath(), dropInfo);

		if (!suc)
		{
			qWarning() << "Failed to read drop file: " << fileinfo.baseName();
		}
		else
		{
			refreshMonsterAndItemKeyMap(dropInfo, monsterKeyMap, itemKeyMap);
			m_listDropInfo << dropInfo;
		}
	}

	qDebug() << "Read finished, total: " << m_listDropInfo.size();

	outputMapKeyToFile(QApplication::applicationDirPath() + "/MonsterKeyMap.ini", monsterKeyMap);
	outputMapKeyToFile(QApplication::applicationDirPath() + "/ItemMap.ini", itemKeyMap);

}

void CDropEditWidget::updateDropInfoListOnUI()
{
	/*ui->treeWidget->clear();

	ui->treeWidget->setWindowTitle("Drops");

	char name[64]; //怪物名称
	byte code1;//怪物种类
	byte code2;
	int money;//掉钱数量
	int DropLeechdom;//掉药品几率
	int DropNovelity;//掉物品几率
	int n; //物品种类数量

	//设定头项名称	
	QStringList listHead;
	listHead << QString::fromLocal8Bit("怪物名称");
	listHead << QString::fromLocal8Bit("怪物代码");
	listHead << QString::fromLocal8Bit("掉落金钱");
	listHead << QString::fromLocal8Bit("药品(几率)");
	listHead << QString::fromLocal8Bit("物品(几率)");
	listHead << QString::fromLocal8Bit("物品数量");
	listHead << QString::fromLocal8Bit("物品名称");
	listHead << QString::fromLocal8Bit("物品代码");
	listHead << QString::fromLocal8Bit("掉落几率");
	ui->treeWidget->setHeaderLabels(listHead);
	//设定各个项  
	QTreeWidgetItem* A = new QTreeWidgetItem(QStringList() << "A");
	A->setIcon(0, QIcon("images/data.png"));
	A->setCheckState(0, Qt::Checked);
	QTreeWidgetItem* B = new QTreeWidgetItem(QStringList() << "B");
	B->setIcon(0, QIcon("images/decision.png"));
	B->setCheckState(0, Qt::Checked);
	QTreeWidgetItem* C = new QTreeWidgetItem(QStringList() << "C");
	C->setIcon(0, QIcon("images/process.png"));
	C->setCheckState(0, Qt::Checked);
	treeWidget->addTopLevelItem(A);
	treeWidget->addTopLevelItem(B);
	treeWidget->addTopLevelItem(C);*/
}

bool CDropEditWidget::refreshMonsterAndItemKeyMap(const drop_info& dropinfo, MapKey& monsterMap, MapKey& itemMap)
{
	const QString monsterName = QString::fromLocal8Bit(dropinfo.name);
	if (monsterName.isEmpty())
	{
		return false;
	}
	//monster
	MapKey::iterator mItor = monsterMap.find(monsterName);
	const QString monsterKey = QString("%1 - %2").arg(dropinfo.code1).arg(dropinfo.code2);
	if (monsterMap.end() == mItor)
	{
		monsterMap.insert(monsterName, QStringList() << monsterKey);
	}
	else
	{
		if (!mItor.value().contains(monsterKey))
		{
			mItor.value() << monsterKey;
		}
	}

	for (int i = 0; i < dropinfo.n; i++)
	{
		const drop_novelity& item = dropinfo.novelity[i];
		const QString itemName = QString::fromLocal8Bit(item.name);
		if (itemName.isEmpty())
		{
			continue;
		}
		MapKey::iterator iItor = itemMap.find(itemName);
		const QString itemKey = QString("%1 - %2").arg(item.code1).arg(item.code2);
		if (itemMap.end() == iItor)
		{
			itemMap.insert(itemName, QStringList() << itemKey);
		}
		else
		{	
			if (!iItor.value().contains(itemKey))
			{
				iItor.value() << itemKey;
			}
			
		}
	}

	return true;
}

bool CDropEditWidget::outputMapKeyToFile(const QString& filepath, const MapKey& mapKey)
{
	QFile file(filepath);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
	{
		return false;
	}
	QTextStream stream(&file);
	MapKey::const_iterator keyItor = mapKey.begin();
	for (keyItor; mapKey.end() != keyItor; keyItor++)
	{
		QString line;
		if (keyItor.value().size() != 1)
		{
			line = "#" + line;
		}
		line += keyItor.key() + "=" + keyItor.value().join("|");
		stream << line << "\n";
	}

	return true;
}
