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

    // --------  create menubar  -------------------
    QMenu *fileMenu = new QMenu(tr("File"));

    QAction *fileNew = new QAction(tr("New"), this);
    //fileNew->setIcon(QIcon::fromTheme("document-new", this->style()->standardIcon(QStyle::SP_FileIcon))); //TODO test in Windows
    fileNew->setIcon(QIcon::fromTheme("document-new"));
    fileNew->setIconVisibleInMenu(true);
    fileNew->setShortcut(Qt::CTRL+Qt::Key_N);
    connect(fileNew, SIGNAL(activated()), this, SLOT(slotNew()));

    QAction *fileOpen = new QAction(tr("Open"), this);
    //fileOpen->setIcon(QIcon::fromTheme("document-open", this->style()->standardIcon(QStyle::SP_DialogOpenButton))); //TODO test in Windows
    fileOpen->setIcon(QIcon::fromTheme("document-open"));
    fileOpen->setIconVisibleInMenu(true);
    fileOpen->setShortcut(Qt::CTRL+Qt::Key_O);
    connect(fileOpen, SIGNAL(activated()), this, SLOT(slotOpen()));

    QAction *fileSave = new QAction(tr("Save"), this);
    //fileSave->setIcon(QIcon::fromTheme("document-save", this->style()->standardIcon(QStyle::SP_DialogSaveButton))); //TODO test in Windows
    fileSave->setIcon(QIcon::fromTheme("document-save"));
    fileSave->setIconVisibleInMenu(true);
    fileSave->setShortcut(Qt::CTRL+Qt::Key_S);
    connect(fileSave, SIGNAL(activated()), this, SLOT(slotSave()));

    QAction *fileSaveAs = new QAction(tr("Save as..."), this);
    //fileSaveAs->setIcon(QIcon::fromTheme("document-save-as", this->style()->standardIcon(QStyle::))); //TODO test in Windows
    fileSaveAs->setIcon(QIcon::fromTheme("document-save-as"));
    fileSaveAs->setIconVisibleInMenu(true);
    fileSaveAs->setShortcut(Qt::SHIFT+Qt::CTRL+Qt::Key_S);
    connect(fileSaveAs, SIGNAL(activated()), this, SLOT(slotSaveAs()));

    QAction *fileQuit = new QAction(tr("Exit"), this);
    //fileQuit->setIcon(QIcon::fromTheme("application-exit", this->style()->standardIcon(QStyle::))); //TODO test in Windows
    fileQuit->setIcon(QIcon::fromTheme("application-exit"));
    fileQuit->setIconVisibleInMenu(true);
    fileQuit->setShortcut(Qt::CTRL+Qt::Key_Q);
    connect(fileQuit, SIGNAL(activated()), qApp, SLOT(closeAllWindows())); // see closeEvent()

    fileMenu->addAction(fileNew);
    fileMenu->addAction(fileOpen);
    fileMenu->addSeparator();
    fileMenu->addAction(fileSave);
    fileMenu->addAction(fileSaveAs);
    fileMenu->addSeparator();
    fileMenu->addAction(fileQuit);

    // ------------------------------
    QMenu *helpMenu = new QMenu(tr("Help"), this);

    QAction * helpHelp = new QAction(tr("Help"), this);
    //helpHelp->setIcon(QIcon::fromTheme("help-contents", this->style()->standardIcon(QStyle::SP_DialogHelpButton))); //TODO test in Windows
    helpHelp->setIcon(QIcon::fromTheme("help-contents"));
    helpHelp->setIconVisibleInMenu(true);
    helpHelp->setShortcut(Qt::Key_F1);
    connect(helpHelp, SIGNAL(activated()), this, SLOT(slotHelp()));

    QAction * helpAbout = new QAction(tr("About "APP_NAME"..."), this);
    helpAbout->setIcon(QIcon::fromTheme("help-about"));
    helpAbout->setIconVisibleInMenu(true);
    helpMenu->addAction(helpAbout);
    connect(helpAbout, SIGNAL(activated()), this, SLOT(slotAbout()));

    QAction * helpAboutQt = new QAction(tr("About Qt..."), this);
    helpAboutQt->setIcon(QIcon::fromTheme("help-about"));
    helpAboutQt->setIconVisibleInMenu(true);
    helpMenu->addAction(helpAboutQt);
    connect(helpAboutQt, SIGNAL(activated()), qApp, SLOT(aboutQt()));

    helpMenu->addAction(helpHelp);
    helpMenu->addSeparator();
    helpMenu->addAction(helpAbout);
    helpMenu->addAction(helpAboutQt);

    // ------------------------------
    menuBar()->addMenu(fileMenu);
    menuBar()->addSeparator();
    menuBar()->addMenu(helpMenu);

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
    inputPower_dBm = new QDoubleSpinBox(this);
    inputPower_dBm->setMinimum(-9999.99);
    inputPower_dBm->setMaximum(9999.99);
    inputPower_dBm->setValue(-60);
    gbox1->addWidget(inputPower_dBm, 0,1);
    QLabel *Label1 = new QLabel(tr("dBm"), this);
    gbox1->addWidget(Label1, 0,2);

    inputPower_dBm->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QLabel *Label2 = new QLabel(tr("Noise Bandwidth:"), this);
    gbox1->addWidget(Label2, 1,0);
    noiseBand_Hz = new QDoubleSpinBox(this);
    noiseBand_Hz->setMinimum(0);
    noiseBand_Hz->setMaximum(9999999.99);
    noiseBand_Hz->setValue(1000);
    gbox1->addWidget(noiseBand_Hz, 1,1);
    freqUnit = new QComboBox(this);
    freqUnit->addItem(tr("Hz")); // see enum freqUnits
    freqUnit->addItem(tr("kHz"));
    freqUnit->addItem(tr("MHz"));
    freqUnit->addItem(tr("GHz"));
    gbox1->addWidget(freqUnit, 1,2);

    QLabel *Label3 = new QLabel(tr("Min S/N for Demod:"), this);
    gbox1->addWidget(Label3, 2,0);
    minSignalToNoise_dB = new QDoubleSpinBox(this);
    minSignalToNoise_dB->setMinimum(-9999.99);
    minSignalToNoise_dB->setMaximum(9999.99);
    minSignalToNoise_dB->setValue(10);
    gbox1->addWidget(minSignalToNoise_dB, 2,1);
    QLabel *Label4 = new QLabel(tr("dB"), this);
    gbox1->addWidget(Label4, 2,2);

    QLabel *Label5 = new QLabel(tr("Temperature:"), this);
    gbox1->addWidget(Label5, 3,0);
    temperature_K_C = new QDoubleSpinBox(this);
    temperature_K_C->setMinimum(ABS_ZERO);
    temperature_K_C->setMaximum(9999.99);
    temperature_K_C->setValue(25);
    connect(temperature_K_C, SIGNAL(valueChanged(double)), this, SLOT(validateTemperature()));
    gbox1->addWidget(temperature_K_C, 3,1);
    temperatureUnit = new QComboBox(this);
    temperatureUnit->addItem(QString(Qt::Key_degree) +tr("C")); // see enum temperatureUnits
    temperatureUnit->addItem(QString(Qt::Key_degree) +tr("K"));
    temperatureUnit->setCurrentIndex(celsius);
    connect(temperatureUnit, SIGNAL(currentIndexChanged(int)), SLOT(validateTemperature()));
    gbox1->addWidget(temperatureUnit, 3,2);

    QLabel *Label6 = new QLabel(tr("PER-to-RMS ratio:"), this);
    gbox1->addWidget(Label6, 4,0);
    perToRms_dB = new QDoubleSpinBox(this);
    perToRms_dB->setMinimum(-9999.99);
    perToRms_dB->setMaximum(9999.99);
    perToRms_dB->setValue(0);
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
    connect(numberOfStages, SIGNAL(editingFinished()), this, SLOT(setStagesNumberSlot()));
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
    connect(table, SIGNAL(editColumnCount(int)), numberOfStages, SLOT(setValue(int)));
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
    if (qApp->argc() > 1)
        openProjectFile(qApp->arguments().at(1));
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
    settings.setValue("windowsState",this->saveState());
    settings.setValue("pathForSaveProjects",defaultPath);
}

void RxCalcApp::loadSettings()
{
    QSettings settings(APP_NAME, APP_NAME);
    this->restoreGeometry(settings.value("windowGeometry",this->saveGeometry()).toByteArray());
    this->restoreState(settings.value("windowsState",this->saveState()).toByteArray());
    defaultPath = settings.value("pathForSaveProjects",QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation)).toString();
}

void RxCalcApp::slotNew()
{
    openProjectPath = "";
    setWindowTitle(APP_NAME " " APP_VERSION);

    setStagesNumber(0);
    comment->clear();

    inputPower_dBm->setValue(0);
    noiseBand_Hz->setValue(1000);
    freqUnit->setCurrentIndex(0);
    minSignalToNoise_dB->setValue(10);
    temperature_K_C->setValue(25);
    temperatureUnit->setCurrentIndex(0);
    perToRms_dB->setValue(0);
}

void RxCalcApp::slotOpen()
{
    openProjectFile(NULL);
}

void RxCalcApp::openProjectFile(QString fileName)
{
    QFileInfo fileInfo(defaultPath);
    if (fileInfo.isDir() == false)
        defaultPath = QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation);

    // Select file
    if (fileName == NULL)
        fileName = QFileDialog::getOpenFileName(this, tr("Select file"), defaultPath, QString("RxCalc projects (*.rxcp);;All files (*)"));

    // Verify file
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::ReadWrite | QFile::Text))
    {
        QMessageBox::warning(this, APP_NAME, QString(tr("Cannot read file") + " %1:\n%2.").arg(fileName).arg(file.errorString()));
        return;
    }

    // Save default path
    fileInfo.setFile(fileName);
    defaultPath = fileInfo.absolutePath();

    // Open file
    QSettings open(fileName, QSettings::IniFormat);

    if (open.value("program") != APP_NAME)
    {
        QMessageBox::warning(this, APP_NAME, tr("This does not file RxCalc"));
        return;
    }

    //if (open.value("version") != global.appVersion)
    //    QMessageBox::warning(this, global.appName,tr("Failed - other version"));

    openProjectPath = fileInfo.absoluteFilePath();
    setWindowTitle(QString(APP_NAME) + " " + QString(APP_VERSION) + " - " + openProjectPath);

    // Open
    setStagesNumber(0);
    comment->clear();

    inputPower_dBm->setValue(open.value("inputPower").toFloat());
    noiseBand_Hz->setValue(open.value("noiseBand").toFloat());
    freqUnit->setCurrentIndex(open.value("freqmeasure","1").toInt());
    minSignalToNoise_dB->setValue(open.value("minSn").toFloat());
    temperature_K_C->setValue(open.value("temperature").toFloat());
    temperatureUnit->setCurrentIndex(open.value("temperaturemeasure","0").toInt());
    perToRms_dB->setValue(open.value("perToRms").toFloat());
    int stageCount = open.value("stageCount").toInt();
    setStagesNumber(stageCount);
    comment->appendPlainText(open.value("comments").toString());

    for (int stage=0; stage<stageCount; stage++)
    {
        QString satgeSection = "stage_"+QString::number(stage)+"/";
        QComboBox *comboBox= (QComboBox*)table->cellWidget(RxTable::type, stage);
        comboBox->setCurrentIndex(open.value(satgeSection+"type","0").toInt());
        QLabel *label= (QLabel*)table->cellWidget(RxTable::pic, stage);
        label->setEnabled(open.value(satgeSection+"enabled").toBool());
        table->item(RxTable::name, stage)->setText(open.value(satgeSection+"name").toString());
        table->item(RxTable::gain, stage)->setText(open.value(satgeSection+"gain").toString());
        table->item(RxTable::noiseFigure, stage)->setText(open.value(satgeSection+"noiseFigure").toString());
        table->item(RxTable::iip3, stage)->setText(open.value(satgeSection+"iip3").toString());
        table->item(RxTable::oip3, stage)->setText(open.value(satgeSection+"oip3").toString());
        table->item(RxTable::ip1db, stage)->setText(open.value(satgeSection+"iip1").toString());
        table->item(RxTable::oip1db, stage)->setText(open.value(satgeSection+"oip1").toString());
    }
}

void RxCalcApp::slotSave()
{
    if (openProjectPath == "")
    {
        slotSaveAs();
        return;
    }

    saveProjectAs(openProjectPath);
}

void RxCalcApp::slotSaveAs()
{
    QFileInfo fileInfo(defaultPath);
    if (fileInfo.isDir() == false)
        defaultPath = QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation);

    QString filter;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Select file"), defaultPath, QString("RxCalc project (*.rxcp);;All files (*)"),&filter);

    fileInfo.setFile(fileName);
    if ((fileInfo.suffix() != "rxcp") & (filter.indexOf("(*.rxcp)",0) != -1))
        fileName.append(".rxcp");

    saveProjectAs(fileName);
}

void RxCalcApp::saveProjectAs(QString fileName)
{
    // Verify file
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, APP_NAME, QString(tr("Cannot write file") + "%1:\n%2.").arg(fileName).arg(file.errorString()));
        return;
    }

    // Save default path
    QFileInfo fileInfo(fileName);
    defaultPath = fileInfo.absolutePath();

    openProjectPath = fileInfo.absoluteFilePath();
    setWindowTitle(QString(APP_NAME) + " " + QString(APP_VERSION) + " - " + openProjectPath);

    // Save
    QSettings save(fileName, QSettings::IniFormat);

    save.setValue("program",APP_NAME);
    save.setValue("version",APP_VERSION);
    save.setValue("inputPower",inputPower_dBm->text());
    save.setValue("noiseBand",noiseBand_Hz->text());
    save.setValue("freqmeasure",freqUnit->currentIndex());
    save.setValue("minSn",minSignalToNoise_dB->text());
    save.setValue("temperature",temperature_K_C->text());
    save.setValue("temperaturemeasure",temperatureUnit->currentIndex());
    save.setValue("perToRms",perToRms_dB->text());
    save.setValue("stageCount",numberOfStages->value());
    save.setValue("comments",comment->toPlainText());

    int stage;
    for (int column=0; column<table->columnCount(); column++)
    {
        QString satgeSection = "stage_"+QString::number(column)+"/";

        stage=table->horizontalHeader()->logicalIndex(column);

        QComboBox *comboBox= (QComboBox*)table->cellWidget(RxTable::type, stage);
        save.setValue(satgeSection+"type",comboBox->currentIndex());
        QLabel *label= (QLabel*)table->cellWidget(RxTable::pic, stage);
        save.setValue(satgeSection+"enabled",label->isEnabled());
        save.setValue(satgeSection+"name",table->item(RxTable::name, stage)->text());
        save.setValue(satgeSection+"gain",table->item(RxTable::gain, stage)->text());
        save.setValue(satgeSection+"noiseFigure",table->item(RxTable::noiseFigure, stage)->text());
        save.setValue(satgeSection+"iip3",table->item(RxTable::iip3, stage)->text());
        save.setValue(satgeSection+"oip3",table->item(RxTable::oip3, stage)->text());
        save.setValue(satgeSection+"iip1",table->item(RxTable::ip1db, stage)->text());
        save.setValue(satgeSection+"oip1",table->item(RxTable::oip1db, stage)->text());
    }
}

void RxCalcApp::slotHelp()
{
    //TODO
}

void RxCalcApp::slotAbout()
{
    QMessageBox::about(this, tr("About " APP_NAME),
        APP_NAME + tr(" version ") + APP_VERSION + "<br>" +
        tr("Copyright (C)")+" 2014-2015 " + tr("by Verkhovin Vyacheslav") +

        "<br><br><a href='http://github.com/arhiv6/rxcalc'>http://github.com/arhiv6/rxcalc</a>" //
        "<br><a href='http://sourceforge.net/projects/rxcalc'>http://sourceforge.net/projects/rxcalc</a><br><br>" +

        tr("RxCalc is a calculator for the analysis of multi-stage receiver. The software can calculate " //
        "cascaded and system parameters: gain, noise, sensitivity, input and output IP1 and IP3, noise " //
        "floor, spur-free dynamic range, MDS, SNR, and others.") + "<br><br>" +

        tr("This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; " //
        "without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. " //
        "See the GNU General Public License for more details.") +
        " <a href='http://www.gnu.org/licenses/gpl.html'>http://www.gnu.org/licenses/gpl.html</a>");
}

void RxCalcApp::validateTemperature()
{
//    if (temperatureUnit->currentIndex() == celsius)
//        temperature_K_C->setMinimum(ABS_ZERO);
//    else if (temperatureUnit->currentIndex() == kelvin)
//        temperature_K_C->setMinimum(0);

    if ((temperatureUnit->currentIndex() == celsius) && (temperature_K_C->value() <= ABS_ZERO))
        temperature_K_C->setStyleSheet("background-color:red;");
    else if ((temperatureUnit->currentIndex() == kelvin) && (temperature_K_C->value() <= 0))
        temperature_K_C->setStyleSheet("background-color:red;");
    else
        temperature_K_C->setStyleSheet("");
}

void RxCalcApp::setStagesNumberSlot()
{
    table->setStageCount(numberOfStages->value());
}

void RxCalcApp::setStagesNumber(int number)
{
    numberOfStages->setValue(number);
    table->setStageCount(number);
}

void RxCalcApp::clickOnCalcButton()
{
    QList<Stage*> *stageList;
    stageList= new QList<Stage*> ();
    for (int i=0; i<table->columnCount(); i++ )
    {
        Stage* st = new Stage();
        st->setEnabled((QLabel*)table->cellWidget(RxTable::pic, i)->isEnabled());
        st->setPowerGain(table->item(RxTable::gain, i)->text().toFloat());
        st->setNoiseFigure(table->item(RxTable::noiseFigure, i)->text().toFloat());
        st->setOip3(table->item(RxTable::oip3, i)->text().toFloat());
        st->setIip3(table->item(RxTable::iip3, i)->text().toFloat());
        st->setOp1db(table->item(RxTable::oip1db, i)->text().toFloat());
        st->setIp1db(table->item(RxTable::ip1db, i)->text().toFloat());

        stageList->append(st);
    }

    System *system = new System(stageList);
    system->setInputPower(inputPower_dBm->value());
    system->setMinSignalToNoise(minSignalToNoise_dB->value());
    system->setPeakToRatio(perToRms_dB->value());
    if (temperatureUnit->currentIndex() == celsius)
        system->setTemperature_C(temperature_K_C->value());
    else if (temperatureUnit->currentIndex() == kelvin)
        system->setTemperature_K(temperature_K_C->value());
    system->setNoiseBand(noiseBand_Hz->value()*pow(10.0, 3*freqUnit->currentIndex()));

    system->solve();

    //-----------------------------------------

    gain_dB->setText(rounding(system->sys1.sysPowerGain));
    noiseFigure_dB->setText(rounding(system->sys1.sysNoiseFigure));
    inputIP3_dBm->setText(rounding(system->sys1.sysIip3));
    outputIP3_dBm->setText(rounding(system->sys1.sysOip3));
    inputP1dB_dBm->setText(rounding(system->sys1.sysIp1db));
    outputP1dB_dBm->setText(rounding(system->sys1.sysOp1db));
    outpupPower_dBm->setText(rounding(system->sys1.sysOutputPower));
    noiseFloor_dBmHz->setText(rounding(system->sys1.sysNoiseFloor_dbmHz));
    outputNSD_dBmHz->setText(rounding(system->sys1.sysOutputNsd_dbmHz));
    outputNoiseFloor_dBm->setText(rounding(system->sys1.sysNoiseFloor_dbm));
    snr_dB->setText(rounding(system->sys1.snr));
    mds_dBm->setText(rounding(system->sys1.mds));
    sensivity_dBm->setText(rounding(system->sys1.sensivity));
    noiseTemperature_K->setText(rounding(system->sys1.noiseTemperature));
    outpuiIMlevel_dBm->setText(rounding(system->sys1.outputImLevel_dBm));   // ?
    outpuiIMlevel_dBc->setText(rounding(system->sys1.outputImLevel_dBc));  // ?
    inpuiIMlevel_dBm->setText(rounding(system->sys1.inputImLevel_dBm));
    inpuiIMlevel_dBc->setText(rounding(system->sys1.inputImLevel_dBc));
    imd_dB->setText(rounding(system->sys1.imd));
    sfdr_dB->setText(rounding(system->sys1.sfdr));

    for (int i=0; i<table->columnCount(); i++ )
    {
        table->cell(RxTable::stageGain, i)->setFloat(stageList->at(i)->sys.powerGain);
        table->cell(RxTable::systemNF, i)->setFloat(stageList->at(i)->sys.noiseFigure);
        table->cell(RxTable::systemIIP3, i)->setFloat(stageList->at(i)->sys.iip3);
        table->cell(RxTable::systemOIP3, i)->setFloat(stageList->at(i)->sys.oip3);
        table->cell(RxTable::inputPower, i)->setFloat(stageList->at(i)->sys.inputPower);
        table->cell(RxTable::outputPower, i)->setFloat(stageList->at(i)->sys.outputPower);
        table->cell(RxTable::nfStageToNfSystem, i)->setFloat(stageList->at(i)->sys.noiseFigureToSystemNoiseFigure);
        table->cell(RxTable::ip3StageToIp3System, i)->setFloat(stageList->at(i)->sys.stageIip3ToSystemIip3);
        table->cell(RxTable::p_backoff, i)->setFloat(stageList->at(i)->sys.powerOutBackoff);
        table->cell(RxTable::p_backoff_peak, i)->setFloat(stageList->at(i)->sys.peakPowerOutBackoff);
    }
}

QString RxCalcApp::rounding (float input)
{
    float tmp=qRound(input*1000.0);
    return QString::number(tmp/1000.0);
}
