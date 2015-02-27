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

#ifndef RXTABLE_H
#define RXTABLE_H

#include "rxtablecell.h"

#include <QTableWidget>
#include <QLabel>
#include <QComboBox>

class RxTable : public QTableWidget
{
public:
    RxTable(QWidget *parent = 0);
    ~RxTable();
    void setSizeAfterDecimalPoint (unsigned int size);
    RxTableCell *cell(int row, int column) const;
    void setStageCount(int newStageNumber);
    enum rowNames {
        type,
        //input freq
        //df_gain
        //df_noise
        pic,
        name,
        //z_in,
        //z_out,
        gain,
        //volt_gain,
        noiseFigure,
        iip3,
        oip3,
        ip1db,
        oip1db,
        stageGain,
        systemNF,
        systemIIP3,
        systemOIP3,
        //corr_gain
        //corr_noise
        inputPower,
        outputPower,
        //voltage,
        //current,
        //power
        nfStageToNfSystem,
        //nf_gain
        ip3StageToIp3System,
        //oip3StageToOp3System,
        p_backoff,
        p_backoff_peak,
        END_ROW_NAMES
    };
    typedef struct
    {
        QString Handlre;
        bool writable;
        QString defaultValue;
    } Row;
    Row *rows;

    enum stageTypes {
        other,
        amplifier,
        filter,
        mixer,
        attenuator,
        END_STAGE_TYPE
    };
    typedef struct
    {
        QString name;
        QPixmap picture;
    } Type;
    Type *stageType;

    QMap<QComboBox*,int> comboboxToImage;

private:
    unsigned int m_sizeAfterDecimalPoint;

};

#endif // RXTABLE_H