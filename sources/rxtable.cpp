/*
 * Copyright 2014, 2015 Verkhovin Vyacheslav
 *
 * This file is part of RxCalc.
 *
 * RxCalc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RxCalc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RxCalc. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "rxtable.h"

RxTable::RxTable(QWidget *parent)
    : QTableWidget(parent)
{
    m_sizeAfterDecimalPoint = 2;
    setItemPrototype(new RxTableCell);
    connect(horizontalHeader(), SIGNAL(sectionMoved(int,int,int)), this, SLOT(renameHeaders()));
    horizontalHeader()->setSectionsMovable(true);
    setSelectionMode(QAbstractItemView::NoSelection);
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(slotShowContextMenu(const QPoint &)));

    // --------  create contextmenu  -------------------
    contextMenu = new QMenu();

    actionEnableStage = new QAction(tr("Enable stage"),this);
    actionEnableStage->setIcon(QIcon::fromTheme("dialog-yes", this->style()->standardIcon(QStyle::SP_DialogYesButton)));
    actionEnableStage->setIconVisibleInMenu(true);
    connect(actionEnableStage, SIGNAL(triggered()), this, SLOT(actionSlotEnableStage()));

    actionDisableStage = new QAction(tr("Disable stage"),this);
    actionDisableStage->setIcon(QIcon::fromTheme("dialog-no", this->style()->standardIcon(QStyle::SP_DialogNoButton)));
    actionDisableStage->setIconVisibleInMenu(true);
    connect(actionDisableStage, SIGNAL(triggered()), this, SLOT(actionSlotDisableStage()));

    actionMoveStageLeft = new QAction(tr("Move stage left"),this);
    actionMoveStageLeft->setIcon(QIcon::fromTheme("go-previous", this->style()->standardIcon(QStyle::SP_ArrowLeft)));
    actionMoveStageLeft->setIconVisibleInMenu(true);
    connect(actionMoveStageLeft, SIGNAL(triggered()), this, SLOT(actionSlotMoveStageLeft()));

    actionMoveStageRight = new QAction(tr("Move stage right"),this);
    actionMoveStageRight->setIcon(QIcon::fromTheme("go-next", this->style()->standardIcon(QStyle::SP_ArrowRight)));
    actionMoveStageRight->setIconVisibleInMenu(true);
    connect(actionMoveStageRight, SIGNAL(triggered()), this, SLOT(actionSlotMoveStageRight()));

    QAction *actionAddStage = new QAction(tr("Add stage (left)"),this);
    actionAddStage->setIcon(QIcon::fromTheme("list-add"));
    actionAddStage->setIconVisibleInMenu(true);
    connect(actionAddStage, SIGNAL(triggered()), this, SLOT(actionSlotAddStage()));

    QAction *actionRemoveStage = new QAction(tr("Remove stage"),this);
    actionRemoveStage->setIcon(QIcon::fromTheme("list-remove", this->style()->standardIcon(QStyle::SP_BrowserStop)));
    actionRemoveStage->setIconVisibleInMenu(true);
    connect(actionRemoveStage, SIGNAL(triggered()), this, SLOT(actionSlotRemoveStage()));

    contextMenu->addAction(actionEnableStage);
    contextMenu->addAction(actionDisableStage);
    contextMenu->addSeparator();
    contextMenu->addAction(actionMoveStageLeft);
    contextMenu->addAction(actionMoveStageRight);
    contextMenu->addSeparator();
    contextMenu->addAction(actionAddStage);
    contextMenu->addAction(actionRemoveStage);

    // --------------------------------------------
    stageType = new Type[END_STAGE_TYPE];

    stageType[other].name = tr("Other");
    stageType[other].picture = QPixmap(":/img/other.svg");

    stageType[amplifier].name = tr("Ampl");
    stageType[amplifier].picture = QPixmap(":/img/amplifier.svg");

    stageType[filter].name = tr("Filter");
    stageType[filter].picture = QPixmap(":/img/filter.svg");

    stageType[mixer].name = tr("Mixer");
    stageType[mixer].picture = QPixmap(":/img/mixer.svg");

    stageType[attenuator].name = tr("Atten");
    stageType[attenuator].picture = QPixmap(":/img/attenuator.svg");

    // --------------------------------------------
    rows = new Row[END_ROW_NAMES];

    rows[type].Handlre = tr("Stage type");
    rows[pic].Handlre = tr("Disable/Enable");

    rows[name].Handlre = tr("Stage Name");
    rows[name].writable = true;
    rows[name].defaultValue = tr("Name");

    rows[gain].Handlre = tr("Gain (dB)");
    rows[gain].writable = true;
    rows[gain].defaultValue = "0";

    rows[stageGain].Handlre = tr("System Gain (dB)");
    rows[stageGain].writable = false;

    rows[noiseFigure].Handlre = tr("Noise Figure (dB)");
    rows[noiseFigure].writable = true;
    rows[noiseFigure].defaultValue = "0";

    rows[ip1db].Handlre = tr("Input P1dB (dBm)");
    rows[ip1db].writable = true;
    rows[ip1db].defaultValue = "100";

    rows[op1db].Handlre = tr("Output P1dB (dBm)");
    rows[op1db].writable = true;
    rows[op1db].defaultValue = "100";

    rows[systemNF].Handlre = tr("System NF (dB)");
    rows[systemNF].writable = false;

    rows[oip3].Handlre = tr("Output IP3 (dBm)");
    rows[oip3].writable = true;
    rows[oip3].defaultValue = "100";

    rows[iip3].Handlre = tr("Input IP3 (dBm)");
    rows[iip3].writable = true;
    rows[iip3].defaultValue = "100";

    rows[inputPower].Handlre = tr("Input Power (dBm)");
    rows[inputPower].writable = false;

    rows[outputPower].Handlre = tr("Output Power (dBm)");
    rows[outputPower].writable = false;

    rows[nfStageToNfSystem].Handlre = tr("Stage NF / Full NF");
    rows[nfStageToNfSystem].writable = false;

    rows[systemIIP3].Handlre = tr("System IIP3 (dBm)");
    rows[systemIIP3].writable = false;

    rows[systemOIP3].Handlre = tr("System OIP3 (dBm)");
    rows[systemOIP3].writable = false;

    rows[systemIP1].Handlre = tr("System IP1dB (dBm)");
    rows[systemIP1].writable = false;

    rows[systemOP1].Handlre = tr("System OP1dB (dBm)");
    rows[systemOP1].writable = false;

    rows[ip3StageToIp3System].Handlre = tr("Stage IIP3 / Full IIP3");
    rows[ip3StageToIp3System].writable = false;

    //rows[oip3StageToOp3System].Handlre = tr("Stage OIP3 / Full OIP3");
    //rows[oip3StageToOp3System].writable = false;

    rows[p_backoff].Handlre = tr("Pout backoff (dB)");
    rows[p_backoff].writable = false;

    rows[p_backoff_peak].Handlre = tr("Peak backoff (dB)");
    rows[p_backoff_peak].writable = false;

    // --------------------------------------------
    setRowCount(END_ROW_NAMES);
    QStringList rowList;
    int i=0;
    while(i < END_ROW_NAMES)
    {
        rowList << rows[i].Handlre;
        i++;
    }
    setVerticalHeaderLabels(rowList);

    connect(this, SIGNAL(cellChanged(int,int)), this, SLOT(itemChanged(int, int)));
}

RxTable::~RxTable()
{

}

void RxTable::setSizeAfterDecimalPoint (unsigned int size)
{
    if (size > 0)
        m_sizeAfterDecimalPoint = size;
}

RxTableCell* RxTable::cell(int row, int column) const
{
    return static_cast<RxTableCell *>(item(row, column));
}

void RxTable::setStageCount(int newStageNumber)
{
    int oldStageNumber = columnCount();

    if ((newStageNumber == oldStageNumber)||(newStageNumber < 0))
            return;

    setColumnCount(newStageNumber);

    if (newStageNumber>oldStageNumber)
    {
        for (int column = oldStageNumber; column < newStageNumber; column++)
            createCount(column);
    }
}

void RxTable::update(bool update)
{
    if (update == true)
        connect(this, SIGNAL(cellChanged(int,int)), this, SLOT(itemChanged(int, int)));
    else
        disconnect(this, SIGNAL(cellChanged(int,int)), this, SLOT(itemChanged(int, int)));
}

void RxTable::createCount(int column)
{
    disconnect(this, SIGNAL(cellChanged(int,int)), this, SLOT(itemChanged(int, int)));

    for (int row=0; row<END_ROW_NAMES; row++)
    {
        if (row == pic)
        {
           setRowHeight(row, 92);
           setColumnWidth(column, 92);

            QLabel *label = new QLabel;
            label->setAlignment(Qt::AlignCenter);
            label->setPixmap(stageType[other].picture);
            //label->setScaledContents(true);

            setCellWidget(row, column, label);
            label->installEventFilter(this);
            label->setContextMenuPolicy(Qt::CustomContextMenu);
            connect(label, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(slotShowContextMenu(const QPoint&)));
        }
        else if (row == type)
        {
            setRowHeight(row, 24);
            QComboBox *test = new QComboBox;
            for (int a=0; a<END_STAGE_TYPE; a++)
                test->addItem(stageType[a].name);
            setCellWidget(row, column, test);

            comboboxToImage[test] = column;
            test->setCurrentIndex(other);

            connect(test, SIGNAL(currentIndexChanged(int)), this, SLOT(slotSetPicture(int)));
        }
        else
        {
            setRowHeight(row, 22);
            setItem(row, column, new RxTableCell);
            if (rows[row].writable == true)
            {
                item(row, column)->setText(rows[row].defaultValue);
                item(row, column)->setBackgroundColor(Qt::white);
            }
            else
                item(row, column)->setBackgroundColor(Qt::gray);
        }
    }

    connect(this, SIGNAL(cellChanged(int,int)), this, SLOT(itemChanged(int, int)));
}

void RxTable::slotSetPicture(int types)
{
    QComboBox* comboBox = (QComboBox*)sender();
    int stage=-1;

    for (int i=0; i<columnCount(); i++)
    {
        if (comboBox == cellWidget(type, i))
        {
            stage = i;
            break;
        }
    }

    QLabel *label= (QLabel*)cellWidget(pic, stage);
    label->setPixmap(stageType[types].picture);
}

bool RxTable::eventFilter(QObject *obj, QEvent *event)
{
    if ((event->type() == QEvent::MouseButtonPress))
     {
        QMouseEvent *key = static_cast<QMouseEvent*>(event);

        if ((key->button() == Qt::LeftButton) && ((QString)obj->metaObject()->className() == "QLabel"))
        {
            QLabel *label = (QLabel*)obj;
            label->setEnabled(!label->isEnabled());
        }
    }
    return false;
}

void RxTable::slotShowContextMenu(const QPoint &pos)
{
    QWidget *label;
    label = (QWidget*) sender();

    QTableWidgetItem *item;
    item = itemAt(pos);

    if (!item && !label)
        return;

    int columnNumber = -1;

    if(item) // if column
    {
        columnNumber = column(item);
    }
    else if ((QString)label->metaObject()->className() == "QLabel") // if enabled Label
    {
        for (int i=0; i < columnCount(); i++)
        {
            if (label == cellWidget(pic, i))
            {
                columnNumber = i;
                break;
            }
        }
    }
    else if ((QString)label->metaObject()->className() == "RxTable")  // if disabled Label
    {
        int X = 0;

        for (int i=0; i < columnCount(); i++)
        {
            X = X + columnWidth(i);

            if (pos.x() < X)
            {
                columnNumber = horizontalHeader()->logicalIndex(i);
                break;
            }
        }
    }
    else
        return;

    if (columnNumber == -1)
        return;

    for (int i = 0; i < contextMenu->actions().size(); i++)
        contextMenu->actions().at(i)->setData(QVariant(columnNumber));

    setSelectionMode(QAbstractItemView::MultiSelection);
    selectColumn(columnNumber);
    setSelectionMode(QAbstractItemView::NoSelection);

    if (cellWidget(pic,columnNumber)->isEnabled() == true)
    {
        actionDisableStage->setVisible(true);
        actionEnableStage->setVisible(false);
    }
    else
    {
        actionDisableStage->setVisible(false);
        actionEnableStage->setVisible(true);
    }

    int stage=horizontalHeader()->visualIndex(columnNumber);

    if (stage == 0)
        actionMoveStageLeft->setEnabled(false);
    else
        actionMoveStageLeft->setEnabled(true);

    if (stage == (columnCount()-1))
        actionMoveStageRight->setEnabled(false);
    else
        actionMoveStageRight->setEnabled(true);

    contextMenu->exec(QCursor::pos());
    clearSelection();
}

void RxTable::actionSlotEnableStage()
{
    QAction* action = qobject_cast< QAction* >( sender() );
    int column = action->data().toInt();

    cellWidget(pic,column)->setEnabled(true);
}

void RxTable::actionSlotDisableStage()
{
    QAction* action = qobject_cast< QAction* >( sender() );
    int column = action->data().toInt();

    cellWidget(pic,column)->setEnabled(false);
}

void RxTable::actionSlotMoveStageLeft()
{
    QAction* action = qobject_cast< QAction* >( sender() );
    int column = action->data().toInt();

    int stage=horizontalHeader()->visualIndex(column);

    if (stage == 0)
        return;

    horizontalHeader()->swapSections(stage,stage);
    horizontalHeader()->moveSection(stage, stage-1);

    renameHeaders();
}

void RxTable::actionSlotMoveStageRight()
{
    QAction* action = qobject_cast< QAction* >( sender() );
    int column = action->data().toInt();

    int stage=horizontalHeader()->visualIndex(column);

    if (stage == (columnCount()-1))
        return;

    horizontalHeader()->swapSections(stage,stage);
    horizontalHeader()->moveSection(stage, stage+1);

    renameHeaders();
}

void RxTable::actionSlotAddStage()
{
    QAction* action = qobject_cast< QAction* >( sender() );
    int column = action->data().toInt();

    //disconnect(this, SIGNAL(cellChanged(int,int)), this, SLOT(itemChanged(int, int)));
    insertColumn(column);
    createCount(column);
    //connect(this, SIGNAL(cellChanged(int,int)), this, SLOT(itemChanged(int, int)));

    emit editColumnCount(columnCount());
}

void RxTable::actionSlotRemoveStage()
{
    QAction* action = qobject_cast< QAction* >( sender() );
    int column = action->data().toInt();

    removeColumn(column);
    emit editColumnCount(columnCount());
}

void RxTable::renameHeaders()
{
    // "convert" logical indexes to visual indexes
    QStringList colList;
    for (int c = 0; c < columnCount(); c++)
        colList << QString::number(horizontalHeader()->visualIndex(c) +1);

    setHorizontalHeaderLabels(colList);
}

void RxTable::itemChanged(int row, int column)
{
    if ((row == name) || (rows[row].writable == false) )//|| (item(row, column)->text().isEmpty()))
        return;

    bool toFloat=false;
    float value = item(row, column)->text().toFloat(&toFloat);
    if ((toFloat != true) || ((row == noiseFigure) && (value < 0)))
    {
        item(row, column)->setBackgroundColor(Qt::red);
        return;
    }
    else
        item(row, column)->setBackgroundColor(Qt::white);

    disconnect(this, SIGNAL(cellChanged(int,int)), this, SLOT(itemChanged(int, int)));

    if (row == oip3)
    {
        item(oip3, column)->setBackgroundColor(Qt::white);
        item(iip3, column)->setBackgroundColor(Qt::lightGray);
        item(iip3, column)->setText("");
    }
    else if (row == iip3)
    {
        item(iip3, column)->setBackgroundColor(Qt::white);
        item(oip3, column)->setBackgroundColor(Qt::lightGray);
        item(oip3, column)->setText("");
    }
    else if (row == ip1db)
    {
        item(ip1db, column)->setBackgroundColor(Qt::white);
        item(op1db, column)->setBackgroundColor(Qt::lightGray);
        item(op1db, column)->setText("");
    }
    else if (row == op1db)
    {
        item(op1db, column)->setBackgroundColor(Qt::white);
        item(ip1db, column)->setBackgroundColor(Qt::lightGray);
        item(ip1db, column)->setText("");
    }
    else if (row == gain)
    {
        if (item(ip1db, column)->backgroundColor() == Qt::lightGray)
            item(ip1db, column)->setText("");
        if (item(op1db, column)->backgroundColor() == Qt::lightGray)
            item(op1db, column)->setText("");
        if (item(iip3, column)->backgroundColor() == Qt::lightGray)
            item(iip3, column)->setText("");
        if (item(oip3, column)->backgroundColor() == Qt::lightGray)
            item(oip3, column)->setText("");
    }

    connect(this, SIGNAL(cellChanged(int,int)), this, SLOT(itemChanged(int, int)));
}
