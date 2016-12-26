#include "MonsterDropInfoItem.h"
#include "ui_MonsterDropInfoItem.h"

#define COL_COUNT 3

CMonsterDropInfoItem::CMonsterDropInfoItem(QWidget *parent) :
QWidget(parent),
ui(new Ui::CMonsterDropInfoItem)
{
	ui->setupUi(this);

	init();
}
CMonsterDropInfoItem::CMonsterDropInfoItem(const drop_info& dropitem, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CMonsterDropInfoItem)
{
    ui->setupUi(this);

	init();

	initWithData(dropitem);
}

CMonsterDropInfoItem::~CMonsterDropInfoItem()
{
    delete ui;
}

void CMonsterDropInfoItem::initWithData(const drop_info& info)
{
	clear();

	m_dropInfo = info;

	ui->labelMonsterID->setText(QString("%1 - %2").arg(info.code1).arg(info.code2));
	ui->labelMonsterName->setText(QString::fromLocal8Bit(info.name));
	ui->spinBoxCount->setValue(info.n);
	ui->spinBoxMoney->setValue(info.money);
	ui->spinBoxMedicanPercent->setValue(info.DropLeechdom);
	ui->spinBoxItemPercent->setValue(info.DropNovelity);

	for (int i = 0; i < info.n; i++)
	{
		ui->tableWidget->insertRow(i);

		const drop_novelity& item = info.novelity[i];
		QTableWidgetItem* itemName = new QTableWidgetItem(QString::fromLocal8Bit(item.name));
		itemName->setFlags(itemName->flags() & ~Qt::ItemIsEditable);
		itemName->setSizeHint(QSize(60, 20));

		QTableWidgetItem* itemCode = new QTableWidgetItem(QString("%1 - %2").arg(item.code1).arg(item.code2));
		itemCode->setFlags(itemName->flags() & ~Qt::ItemIsEditable);
		itemCode->setSizeHint(QSize(60, 20));

		QTableWidgetItem* itemPercent = new QTableWidgetItem(QString("%1").arg(item.per));
		itemPercent->setSizeHint(QSize(60, 20));

		ui->tableWidget->setItem(i, 0, itemName);
		ui->tableWidget->setItem(i, 1, itemCode);
		ui->tableWidget->setItem(i, 2, itemPercent);
	}
}

void CMonsterDropInfoItem::clear()
{
	ui->tableWidget->setRowCount(0);

	ui->labelMonsterID->clear();
	ui->labelMonsterName->clear();
	ui->spinBoxCount->setValue(0);
	ui->spinBoxMoney->setValue(0);
	ui->spinBoxMedicanPercent->setValue(0);
	ui->spinBoxItemPercent->setValue(0);
}

void CMonsterDropInfoItem::init()
{
	QStringList listHead;
	listHead << QString::fromLocal8Bit("物品名称");
	listHead << QString::fromLocal8Bit("物品代码");
	listHead << QString::fromLocal8Bit("物品几率");
	ui->tableWidget->setColumnCount(listHead.size());
	ui->tableWidget->setHorizontalHeaderLabels(listHead);

	clear();
}
