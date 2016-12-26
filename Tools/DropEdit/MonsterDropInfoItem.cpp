#include "MonsterDropInfoItem.h"
#include "ui_MonsterDropInfoItem.h"

CMonsterDropInfoItem::CMonsterDropInfoItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CMonsterDropInfoItem)
{
    ui->setupUi(this);
}

CMonsterDropInfoItem::~CMonsterDropInfoItem()
{
    delete ui;
}
