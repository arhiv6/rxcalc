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

#ifndef STAGE_H
#define STAGE_H

#include <QString>

class Stage
{
public:
    Stage();
    ~Stage();
    void setName(QString name);
    QString name();
    void setEnabled(bool enabled);
    bool enabled();
    void setPowerGain(float powerGain);
    float powerGain();
    void setNoiseFigure(float noiseFigure);
    float noiseFigure();
    void setOip3(float oip3);
    float oip3();
    void setOp1db(float op1db);
    float op1db();
    void setIip3(float iip3);
    float iip3();
    void setIp1db(float ip1db);
    float ip1db();

private:
    QString m_name;
    bool m_enabled;
    float m_powerGain;
    float m_noiseFigure;
    float m_oip3;
    float m_op1db;
    float m_iip3;
    float m_ip1db;
    bool m_iip3Priority;
    bool m_ip1dbPriority;
};

#endif // STAGE_H
