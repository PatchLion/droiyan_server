#ifndef PERCENTITEMDELEGATE_H
#define PERCENTITEMDELEGATE_H

#include <QtWidgets>

class CPercentItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit CPercentItemDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
           const QModelIndex &index) const
       {
           QSpinBox *editor = new QSpinBox(parent);
           editor->setMinimum(0);
           editor->setMaximum(1000);
           return editor;
       }
       void setEditorData(QWidget *editor, const QModelIndex &index) const
       {
           int value = index.model()->data(index, Qt::EditRole).toInt();
           QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
           spinBox->setValue(value);
       }
       void setModelData(QWidget *editor, QAbstractItemModel *model,
           const QModelIndex &index) const
       {
           QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
           spinBox->interpretText();
           int value = spinBox->value();
           model->setData(index, value, Qt::EditRole);
       }
       void updateEditorGeometry(QWidget *editor,
           const QStyleOptionViewItem &option, const QModelIndex &index) const
       {
           editor->setGeometry(option.rect);
       }

};

#endif // PERCENTITEMDELEGATE_H
