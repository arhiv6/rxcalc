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
    //horizontalHeader()->setMovable(true);
    setSelectionMode(QAbstractItemView::NoSelection);

    // --------------------------------------------
    stageType = new Type[END_STAGE_TYPE];

    stageType[other].name = "Other";
    stageType[other].picture = QPixmap(":/img/other.svg");

    stageType[amplifier].name = "Ampl";
    stageType[amplifier].picture = QPixmap(":/img/amplifier.svg");

    stageType[filter].name = "Filter";
    stageType[filter].picture = QPixmap(":/img/filter.svg");

    stageType[mixer].name = "Mix";
    stageType[mixer].picture = QPixmap(":/img/mixer.svg");

    stageType[attenuator].name = "Atten";
    stageType[attenuator].picture = QPixmap(":/img/attenuator.svg");

    // --------------------------------------------
    rows = new Row[END_ROW_NAMES];

    rows[type].Handlre = "Stage type";
    rows[pic].Handlre = "Disable/Enable";

    rows[name].Handlre = "Stage Name";
    rows[name].writable = true;
    rows[name].defaultValue = "name";

    rows[gain].Handlre = "Gain (dB)";
    rows[gain].writable = true;
    rows[gain].defaultValue = "0";

    rows[stageGain].Handlre = "System Gain (dB)";
    rows[stageGain].writable = false;

    rows[noiseFigure].Handlre = "Noise Figure (dB)";
    rows[noiseFigure].writable = true;
    rows[noiseFigure].defaultValue = "0";

    rows[ip1db].Handlre = "IP1dB (dBm)";
    rows[ip1db].writable = true;
    rows[ip1db].defaultValue = "100";

    rows[oip1db].Handlre = "OP1dB (dBm)";
    rows[oip1db].writable = true;
    rows[oip1db].defaultValue = "100";

    rows[systemNF].Handlre = "System Noise Figure (dB)";
    rows[systemNF].writable = false;

    rows[oip3].Handlre = "OIP3 (dBm)";
    rows[oip3].writable = true;
    rows[oip3].defaultValue = "100";

    rows[iip3].Handlre = "IIP3 (dBm)";
    rows[iip3].writable = true;
    rows[iip3].defaultValue = "100";

    rows[inputPower].Handlre = "Input Power (dBm)";
    rows[inputPower].writable = false;

    rows[outputPower].Handlre = "Output Power (dBm)";
    rows[outputPower].writable = false;

    rows[nfStageToNfSystem].Handlre = "Stage NF / Full NF";
    rows[nfStageToNfSystem].writable = false;

    rows[systemIIP3].Handlre = "System IIP3";
    rows[systemIIP3].writable = false;

    rows[systemOIP3].Handlre = "System OIP3";
    rows[systemOIP3].writable = false;

    rows[ip3StageToIp3System].Handlre = "Stage IIP3 / Full IIP3";
    rows[ip3StageToIp3System].writable = false;

    //rows[oip3StageToOp3System].Handlre = "Stage OIP3 / Full OIP3";
    //rows[oip3StageToOp3System].writable = false;

    rows[p_backoff].Handlre = "Pout backoff";
    rows[p_backoff].writable = false;

    rows[p_backoff_peak].Handlre = "Peak backoff";
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

void RxTable::setStageCount( int newStageNumber)
{
    int oldStageNumber = columnCount();

    if ((newStageNumber == oldStageNumber)||(newStageNumber < 0))
            return;


    setColumnCount(newStageNumber);


    if (newStageNumber>oldStageNumber)
    {
        for (int column = oldStageNumber; column < newStageNumber; column++)
        {
            for (int row=0; row<END_ROW_NAMES; row++)
            {
                if (row == pic)
                {
                   setRowHeight(row, 100);
                   setColumnWidth(column, 100);

                    QLabel *label = new QLabel;
                    label->setAlignment(Qt::AlignCenter);
                    label->setPixmap(stageType[other].picture);
                    //label->setScaledContents(true);

                    setCellWidget(row, column, label);
                    label->installEventFilter(this);
                    label->setContextMenuPolicy(Qt::CustomContextMenu);
                    //connect(label, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(slotShowContextMenu(const QPoint &)));
                }
                else if (row == type)
                {
                    QComboBox *test = new QComboBox;
                    for (int a=0; a<END_STAGE_TYPE; a++)
                        test->addItem(stageType[a].name);
                    setCellWidget(row, column, test);

                    comboboxToImage[test] = column;
                    test->setCurrentIndex(other);

                   // connect(test, SIGNAL(currentIndexChanged(int)), this, SLOT(setPicture(int)));
                }
                else
                {
                    setItem(row, column, new RxTableCell);
                    if (rows[row].writable == true)
                        item(row, column)->setText(rows[row].defaultValue);
                    else
                        item(row, column)->setBackgroundColor(Qt::gray);
                }
            }
        }
    }
   //
}
