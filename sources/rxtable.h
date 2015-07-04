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
#include <QHeaderView>
#include <QLabel>
#include <QComboBox>
#include <QMouseEvent>
#include <QMenu>
#include <QVariant>

class RxTable : public QTableWidget
{
    Q_OBJECT

public:
    RxTable(QWidget *parent = 0);
    ~RxTable();
    void setSizeAfterDecimalPoint (unsigned int size);
    RxTableCell *cell(int row, int column) const;
    void setStageCount(int newStageNumber);
    void update(bool update);

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
        op1db,
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
    QMenu *contextMenu;
    QAction *actionEnableStage;
    QAction *actionDisableStage;
    QAction *actionMoveStageLeft;
    QAction *actionMoveStageRight;

private slots:
    void createCount(int column);
    void slotSetPicture(int types);
    bool eventFilter(QObject *obj, QEvent *event);
    void slotShowContextMenu(const QPoint &pos);
    void actionSlotEnableStage();
    void actionSlotDisableStage();
    void actionSlotMoveStageLeft();
    void actionSlotMoveStageRight();
    void actionSlotAddStage();
    void actionSlotRemoveStage();
    void renameHeaders();
    void itemChanged(int row, int column);

signals:
    void editColumnCount(int value);    
};

#endif // RXTABLE_H
