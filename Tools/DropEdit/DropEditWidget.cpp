#include "DropEditWidget.h"
#include "ui_DropEditWidget.h"
#include <QtCore>
#include <QtWidgets>
#include "Functions.h"
#include "MonsterDropInfoItem.h"

#define INDEX_TEXT(index, total) QString("%1 / %2").arg(index + 1).arg(total)

CDropEditWidget::CDropEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CDropEditWidget)
{
    ui->setupUi(this);

	onIndexChanged();
}

CDropEditWidget::~CDropEditWidget()
{
    delete ui;
}

void CDropEditWidget::initDropInfos(const QString& rootDir)
{
	MapKey monsterKeyMap;
	MapKey itemKeyMap;

	ui->widgetMonsterDrop->clear();
	m_listDropInfo.clear();
	ui->listWidget->clear();

	const QString root_path = rootDir;

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
			stDropInfo temp(dropInfo);
			temp.originFile = fileinfo.absoluteFilePath();
			m_listDropInfo << temp;

			ui->listWidget->addItem(QString::fromLocal8Bit(dropInfo.name));
		}

		
	}

	qDebug() << "Read finished, total: " << m_listDropInfo.size();

	outputMapKeyToFile(QApplication::applicationDirPath() + "/MonsterKeyMap.ini", monsterKeyMap);
	outputMapKeyToFile(QApplication::applicationDirPath() + "/ItemMap.ini", itemKeyMap);

}

void CDropEditWidget::updateDropInfoListOnUI()
{
	m_currentIndex = 0;

	onIndexChanged();
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

void CDropEditWidget::onIndexChanged()
{
	if (m_listDropInfo.isEmpty())
	{
		ui->labelIndex->setText(INDEX_TEXT(-1, 0));
		ui->pushButtonNext->setEnabled(false);
		ui->pushButtonPer->setEnabled(false);
		ui->labelCurrentFileName->clear();
	}
	else
	{
		ui->labelIndex->setText(INDEX_TEXT(m_currentIndex, m_listDropInfo.size()));
		if (m_currentIndex <= 0)
		{
			ui->pushButtonPer->setEnabled(false);
		}
		else
		{
			ui->pushButtonPer->setEnabled(true);
		}
		if (m_currentIndex >= (m_listDropInfo.size() - 1))
		{
			ui->pushButtonNext->setEnabled(false);
		}
		else
		{
			ui->pushButtonNext->setEnabled(true);
		}

		if (m_currentIndex >= 0 && m_currentIndex < m_listDropInfo.size())
		{
			ui->widgetMonsterDrop->initWithData(m_listDropInfo[m_currentIndex]);
		}

		ui->labelCurrentFileName->setText(QFileInfo(m_listDropInfo[m_currentIndex].originFile).fileName());
	}
}

void CDropEditWidget::on_pushButtonNext_clicked(bool checked)
{
	if (m_currentIndex < (m_listDropInfo.size() - 1))
	{
		m_currentIndex++;
	}
	onIndexChanged();
}

void CDropEditWidget::on_pushButtonPre_clicked(bool checked)
{
	if (m_currentIndex > 0)
	{
		m_currentIndex--;
	}
	onIndexChanged();
}

void CDropEditWidget::on_listWidget_currentRowChanged(int currentRow)
{
	m_currentIndex = currentRow;
	onIndexChanged();
}

void CDropEditWidget::on_pushButtonSelect_clicked(bool checked)
{
	const QString root_dir = QFileDialog::getExistingDirectory(this, "Drop Root Directory", QApplication::applicationDirPath());

	if (!root_dir.isEmpty())
	{
		initDropInfos(root_dir);

		updateDropInfoListOnUI();

		ui->labelRootPath->setText(root_dir);
	}
}
