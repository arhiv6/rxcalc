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

#include "rxcalc.h"

RxCalcApp::RxCalcApp()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // set application icon
    setWindowIcon(QPixmap(":/img/rxcalc.png"));
    setWindowTitle(APP_NAME " " APP_VERSION);
/*
    // --------  create menubar  -------------------
    QMenu *fileMenu = new QMenu(tr("&File"));

    QAction * fileQuit = new QAction(tr("E&xit"), this);
    fileQuit->setShortcut(Qt::CTRL+Qt::Key_Q);
    connect(fileQuit, SIGNAL(activated()), SLOT(slotQuit()));

    fileMenu->addAction(fileQuit);

    QMenu *helpMenu = new QMenu(tr("&Help"), this);
    QAction * helpHelp = new QAction(tr("Help..."), this);
    helpHelp->setShortcut(Qt::Key_F1);
    connect(helpHelp, SIGNAL(activated()), SLOT(slotHelpIntro()));

    QAction * helpAbout = new QAction(tr("&About QucsFilter..."), this);
    helpMenu->addAction(helpAbout);
    connect(helpAbout, SIGNAL(activated()), SLOT(slotHelpAbout()));

    QAction * helpAboutQt = new QAction(tr("About Qt..."), this);
    helpMenu->addAction(helpAboutQt);
    connect(helpAboutQt, SIGNAL(activated()), SLOT(slotHelpAboutQt()));

    helpMenu->addAction(helpHelp);
    helpMenu->addSeparator();
    helpMenu->addAction(helpAbout);
    helpMenu->addAction(helpAboutQt);

    menuBar()->addMenu(fileMenu);
    menuBar()->addSeparator();
    menuBar()->addMenu(helpMenu);
*/
    // -------  create main windows widgets --------
    QVBoxLayout *all  = new QVBoxLayout();
    QGridLayout *top  = new QGridLayout();
    QHBoxLayout *bot  = new QHBoxLayout();
    all->setSpacing(3);
    top->setSpacing(3);
    bot->setSpacing(3);

    // assign layout to central widget
    centralWidget->setLayout(all);

    // ...........................................................
    all->addLayout(top, 0);
    QGroupBox *box1 = new QGroupBox(tr("System Parametrs"), this);
    box1->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    top->addWidget(box1,0,0,-1,1);

    QGridLayout *gbox1 = new QGridLayout();
    gbox1->setVerticalSpacing(0);
    gbox1->setHorizontalSpacing(3);

    box1->setLayout(gbox1);

    QLabel *Label0 = new QLabel(tr("Input Power:"), this);
    gbox1->addWidget(Label0, 0,0);
    inputPower_dBm = new QLineEdit("-60", this);
    connect(inputPower_dBm, SIGNAL(editingFinished()), SLOT(validate()));
    gbox1->addWidget(inputPower_dBm, 0,1);
    QLabel *Label1 = new QLabel(tr("dBm"), this);
    gbox1->addWidget(Label1, 0,2);

    inputPower_dBm->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QLabel *Label2 = new QLabel(tr("Noise Bandwidth:"), this);
    gbox1->addWidget(Label2, 1,0);
    noiseBand_Hz = new QLineEdit("1000", this);
    connect(noiseBand_Hz, SIGNAL(editingFinished()), SLOT(validate()));
    gbox1->addWidget(noiseBand_Hz, 1,1);
    freqUnit = new QComboBox(this);
    freqUnit->addItem(tr("Hz")); // see enum freqUnits
    freqUnit->addItem(tr("kHz"));
    freqUnit->addItem(tr("MHz"));
    freqUnit->addItem(tr("GHz"));
    gbox1->addWidget(freqUnit, 1,2);

    QLabel *Label3 = new QLabel(tr("Min S/N for Demod:"), this);
    gbox1->addWidget(Label3, 2,0);
    minSignalToNoise_dB = new QLineEdit("-60", this);
    connect(minSignalToNoise_dB, SIGNAL(editingFinished()), SLOT(validate()));
    gbox1->addWidget(minSignalToNoise_dB, 2,1);
    QLabel *Label4 = new QLabel(tr("dB"), this);
    gbox1->addWidget(Label4, 2,2);

    QLabel *Label5 = new QLabel(tr("Temperature:"), this);
    gbox1->addWidget(Label5, 3,0);
    temperature_K_C = new QLineEdit("25", this);
    connect(temperature_K_C, SIGNAL(editingFinished()), SLOT(validate()));
    gbox1->addWidget(temperature_K_C, 3,1);
    temperatureUnit = new QComboBox(this);
    temperatureUnit->addItem(QString(Qt::Key_degree) +tr("C")); // see enum temperatureUnits
    temperatureUnit->addItem(QString(Qt::Key_degree) +tr("K"));
    connect(temperatureUnit, SIGNAL(currentIndexChanged(int)), SLOT(validate()));
    gbox1->addWidget(temperatureUnit, 3,2);

    QLabel *Label6 = new QLabel(tr("PER-to-RMS ratio:"), this);
    gbox1->addWidget(Label6, 4,0);
    perToRms_dB = new QLineEdit("0", this);
    connect(perToRms_dB, SIGNAL(editingFinished()), SLOT(validate()));
    gbox1->addWidget(perToRms_dB, 4,1);
    QLabel *Label7 = new QLabel(tr("dB"), this);
    gbox1->addWidget(Label7, 4,2);

    // ...........................................................
    QSpacerItem *spacer4 = new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);
    top->addItem(spacer4, 0, 1, -1, 1);

    // ...........................................................
    QLabel *Label50 = new QLabel(tr("Number of Stages:"), this);
    top->addWidget(Label50, 2, 2, 1, 1);

    // ...........................................................
    numberOfStages = new QSpinBox(this);
    numberOfStages->setMinimum(0);
    connect(numberOfStages, SIGNAL(editingFinished()), SLOT(setStagesNumber()));
    top->addWidget(numberOfStages, 2, 3, 1, 1);

    // ...........................................................
    QPushButton *calcButton = new QPushButton(tr("Calculate"), this);
    connect(calcButton, SIGNAL(clicked()), SLOT(clickOnCalcButton()));
    top->addWidget(calcButton, 4, 2, 1, 2);

    // ...........................................................
    QSpacerItem *spacer3 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    top->addItem(spacer3, 5, 2, 1, 2);

    // ...........................................................
    QSpacerItem *spacer6 = new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);
    top->addItem(spacer6, 0, 4, -1, 1);

    // ...........................................................
    QLabel *Label51 = new QLabel(tr("Comments of the project:"), this);
    top->addWidget(Label51, 0, 5, 1, 1);

    // ...........................................................
    comment = new QPlainTextEdit(this);
    comment->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);
    top->addWidget(comment, 1, 5, -1, 1);

    // ...........................................................
    table = new RxTable(this);
    table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    all->addWidget(table, 1);

    // ...........................................................
    all->addLayout(bot, 2);
    QGroupBox *box2 = new QGroupBox(tr("System Analysis"), this);
    box2->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    bot->addWidget(box2,0);

    QGridLayout *gbox2 = new QGridLayout();
    gbox2->setVerticalSpacing(0);
    gbox2->setHorizontalSpacing(3);

    box2->setLayout(gbox2);

    QLabel *Label8 = new QLabel(tr("Gain:"), this);
    gbox2->addWidget(Label8, 0,0);
    gain_dB = new QLineEdit("", this);
    gain_dB->setReadOnly(true);
    gbox2->addWidget(gain_dB, 0,1);
    QLabel *Label9 = new QLabel(tr("dB"), this);
    gbox2->addWidget(Label9, 0,2);

    gain_dB->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QLabel *Label10 = new QLabel(tr("Noise Figure:"), this);
    gbox2->addWidget(Label10, 1,0);
    noiseFigure_dB = new QLineEdit("", this);
    noiseFigure_dB->setReadOnly(true);
    gbox2->addWidget(noiseFigure_dB, 1,1);
    QLabel *Label11 = new QLabel(tr("dB"), this);
    gbox2->addWidget(Label11, 1,2);

    QLabel *Label12 = new QLabel(tr("Input IP3:"), this);
    gbox2->addWidget(Label12, 2,0);
    inputIP3_dBm = new QLineEdit("", this);
    inputIP3_dBm->setReadOnly(true);
    gbox2->addWidget(inputIP3_dBm, 2,1);
    QLabel *Label13 = new QLabel(tr("dBm"), this);
    gbox2->addWidget(Label13, 2,2);

    QLabel *Label14 = new QLabel(tr("Output IP3:"), this);
    gbox2->addWidget(Label14, 3,0);
    outputIP3_dBm = new QLineEdit("", this);
    outputIP3_dBm->setReadOnly(true);
    gbox2->addWidget(outputIP3_dBm, 3,1);
    QLabel *Label15 = new QLabel(tr("dBm"), this);
    gbox2->addWidget(Label15, 3,2);

    QLabel *Label16 = new QLabel(tr("Input P1dB:"), this);
    gbox2->addWidget(Label16, 4,0);
    inputP1dB_dBm = new QLineEdit("", this);
    inputP1dB_dBm->setReadOnly(true);
    gbox2->addWidget(inputP1dB_dBm, 4,1);
    QLabel *Label17 = new QLabel(tr("dBm"), this);
    gbox2->addWidget(Label17, 4,2);

    QLabel *Label18 = new QLabel(tr("Output P1dB:"), this);
    gbox2->addWidget(Label18, 5,0);
    outputP1dB_dBm = new QLineEdit("", this);
    outputP1dB_dBm->setReadOnly(true);
    gbox2->addWidget(outputP1dB_dBm, 5,1);
    QLabel *Label19 = new QLabel(tr("dBm"), this);
    gbox2->addWidget(Label19, 5,2);

    QLabel *Label20 = new QLabel(tr("Output power:"), this);
    gbox2->addWidget(Label20, 6,0);
    outpupPower_dBm = new QLineEdit("", this);
    outpupPower_dBm->setReadOnly(true);
    gbox2->addWidget(outpupPower_dBm, 6,1);
    QLabel *Label21 = new QLabel(tr("dBm"), this);
    gbox2->addWidget(Label21, 6,2);

    // ...........................................................
    QGroupBox *box3 = new QGroupBox(tr("Noise Analysis"), this);
    box3->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    bot->addWidget(box3,1);

    QGridLayout *gbox3 = new QGridLayout();
    gbox3->setVerticalSpacing(0);
    gbox3->setHorizontalSpacing(3);

    box3->setLayout(gbox3);

    QLabel *Label22 = new QLabel(tr("Noise Floor:"), this);
    gbox3->addWidget(Label22, 0,0);
    noiseFloor_dBmHz = new QLineEdit("", this);
    noiseFloor_dBmHz->setReadOnly(true);
    gbox3->addWidget(noiseFloor_dBmHz, 0,1);
    QLabel *Label23 = new QLabel(tr("dBm/Hz"), this);
    gbox3->addWidget(Label23, 0,2);

    noiseFloor_dBmHz->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QLabel *Label24 = new QLabel(tr("Output NSD:"), this);
    gbox3->addWidget(Label24, 1,0);
    outputNSD_dBmHz = new QLineEdit("", this);
    outputNSD_dBmHz->setReadOnly(true);
    gbox3->addWidget(outputNSD_dBmHz, 1,1);
    QLabel *Label25 = new QLabel(tr("dBm/Hz"), this);
    gbox3->addWidget(Label25, 1,2);

    QLabel *Label26 = new QLabel(tr("Output Noise Floor:"), this);
    gbox3->addWidget(Label26, 2,0);
    outputNoiseFloor_dBm = new QLineEdit("", this);
    outputNoiseFloor_dBm->setReadOnly(true);
    gbox3->addWidget(outputNoiseFloor_dBm, 2,1);
    QLabel *Label27 = new QLabel(tr("dBm"), this);
    gbox3->addWidget(Label27, 2,2);

    QLabel *Label28 = new QLabel(tr("SNR:"), this);
    gbox3->addWidget(Label28, 3,0);
    snr_dB = new QLineEdit("", this);
    snr_dB->setReadOnly(true);
    gbox3->addWidget(snr_dB, 3,1);
    QLabel *Label29 = new QLabel(tr("dB"), this);
    gbox3->addWidget(Label29, 3,2);

    QLabel *Label30 = new QLabel(tr("MDS:"), this);
    gbox3->addWidget(Label30, 4,0);
    mds_dBm = new QLineEdit("", this);
    mds_dBm->setReadOnly(true);
    gbox3->addWidget(mds_dBm, 4,1);
    QLabel *Label31 = new QLabel(tr("dBm"), this);
    gbox3->addWidget(Label31, 4,2);

    QLabel *Label32 = new QLabel(tr("Sensivity:"), this);
    gbox3->addWidget(Label32, 5,0);
    sensivity_dBm = new QLineEdit("", this);
    sensivity_dBm->setReadOnly(true);
    gbox3->addWidget(sensivity_dBm, 5,1);
    QLabel *Label33 = new QLabel(tr("dBm"), this);
    gbox3->addWidget(Label33, 5,2);

    QLabel *Label34 = new QLabel(tr("Noise Temperature:"), this);
    gbox3->addWidget(Label34, 6,0);
    noiseTemperature_K = new QLineEdit("", this);
    noiseTemperature_K->setReadOnly(true);
    gbox3->addWidget(noiseTemperature_K, 6,1);
    QLabel *Label35 = new QLabel(QString(Qt::Key_degree)+tr("K"), this);
    gbox3->addWidget(Label35, 6,2);

    // ...........................................................
    QGroupBox *box4 = new QGroupBox(tr("Dynamic Analysis"), this);
    box4->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    bot->addWidget(box4,2);

    QGridLayout *gbox4 = new QGridLayout();
    gbox4->setVerticalSpacing(0);
    gbox4->setHorizontalSpacing(3);

    box4->setLayout(gbox4);

    QLabel *Label36 = new QLabel(tr("Output IM Level:"), this);
    gbox4->addWidget(Label36, 0,0);
    outpuiIMlevel_dBm = new QLineEdit("", this);
    outpuiIMlevel_dBm->setReadOnly(true);
    gbox4->addWidget(outpuiIMlevel_dBm, 0,1);
    QLabel *Label37 = new QLabel(tr("dBm"), this);
    gbox4->addWidget(Label37, 0,2);

    outpuiIMlevel_dBm->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QLabel *Label38 = new QLabel(tr("Output IM Level:"), this);
    gbox4->addWidget(Label38, 1,0);
    outpuiIMlevel_dBc = new QLineEdit("", this);
    outpuiIMlevel_dBc->setReadOnly(true);
    gbox4->addWidget(outpuiIMlevel_dBc, 1,1);
    QLabel *Label39 = new QLabel(tr("dBc"), this);
    gbox4->addWidget(Label39, 1,2);

    QLabel *Label40 = new QLabel(tr("Input IM Level:"), this);
    gbox4->addWidget(Label40, 2,0);
    inpuiIMlevel_dBm = new QLineEdit("", this);
    inpuiIMlevel_dBm->setReadOnly(true);
    gbox4->addWidget(inpuiIMlevel_dBm, 2,1);
    QLabel *Label41 = new QLabel(tr("dBm"), this);
    gbox4->addWidget(Label41, 2,2);

    QLabel *Label42 = new QLabel(tr("Input IM Level:"), this);
    gbox4->addWidget(Label42, 3,0);
    inpuiIMlevel_dBc = new QLineEdit("", this);
    inpuiIMlevel_dBc->setReadOnly(true);
    gbox4->addWidget(inpuiIMlevel_dBc, 3,1);
    QLabel *Label43 = new QLabel(tr("dBc"), this);
    gbox4->addWidget(Label43, 3,2);

    QLabel *Label44 = new QLabel(tr("IMD:"), this);
    gbox4->addWidget(Label44, 4,0);
    imd_dB = new QLineEdit("", this);
    imd_dB->setReadOnly(true);
    gbox4->addWidget(imd_dB, 4,1);
    QLabel *Label45 = new QLabel(tr("dB"), this);
    gbox4->addWidget(Label45, 4,2);

    QLabel *Label46 = new QLabel(tr("SFDR:"), this);
    gbox4->addWidget(Label46, 5,0);
    sfdr_dB = new QLineEdit("", this);
    sfdr_dB->setReadOnly(true);
    gbox4->addWidget(sfdr_dB, 5,1);
    QLabel *Label47 = new QLabel(tr("dB"), this);
    gbox4->addWidget(Label47, 5,2);

    QLabel *Label48 = new QLabel(tr("ILDR:"), this);
    gbox4->addWidget(Label48, 6,0);
    ildr_dB = new QLineEdit("", this);
    ildr_dB->setReadOnly(true);
    gbox4->addWidget(ildr_dB, 6,1);
    QLabel *Label49 = new QLabel(tr("dB"), this);
    gbox4->addWidget(Label49, 6,2);

    // ...........................................................
    QSpacerItem *spacer2=new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    bot->insertSpacerItem(3, spacer2);

    // -------  finally set initial state  --------
    loadSettings();
}

RxCalcApp::~RxCalcApp()
{

}

void RxCalcApp::closeEvent(QCloseEvent* Event)
{
    saveSettings();
    Event->accept();
}

void RxCalcApp::saveSettings()
{
    QSettings settings(APP_NAME, APP_NAME);
    settings.setValue("windowGeometry",this->saveGeometry());
}

void RxCalcApp::loadSettings()
{
    QSettings settings(APP_NAME, APP_NAME);
    this->restoreGeometry(settings.value("windowGeometry",this->saveGeometry()).toByteArray());
}

void RxCalcApp::validate()
{
    QLineEdit *sender;
    bool toFloat;

    if ((QComboBox *)QObject::sender() == temperatureUnit)
        sender = temperature_K_C;
    else
         sender = (QLineEdit *)QObject::sender();

    float num = sender->text().toFloat(&toFloat);
    if (toFloat == false)
    {
        sender->setStyleSheet("background-color:red;");
        return;
    }
    else
        sender->setStyleSheet("");

    if (sender == noiseBand_Hz)
    {
        if (num <= 0)
            sender->setStyleSheet("background-color:red;");
        else
            sender->setStyleSheet("");
    }
    else if (sender == temperature_K_C)
    {
        if ((temperatureUnit->currentIndex() == celsius) && (num <= ABS_ZERO))
            sender->setStyleSheet("background-color:red;");
        else if ((temperatureUnit->currentIndex() == kelvin) && (num <= 0))
            sender->setStyleSheet("background-color:red;");
        else
            sender->setStyleSheet("");
    }
}

void RxCalcApp::setStagesNumber()
{
    int newStageNumber = numberOfStages->value();
    int oldStageNumber = table->columnCount();

    if (newStageNumber == oldStageNumber)
        return;

    table->setColumnCount(newStageNumber);

    if (newStageNumber>oldStageNumber)
    {   // create new column
        for (int i = oldStageNumber; i < newStageNumber; i++)
        {
            //createCount(i);
        }
    }
}

void RxCalcApp::clickOnCalcButton()
{

}
