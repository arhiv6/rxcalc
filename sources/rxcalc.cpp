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
    QGridLayout *all  = new QGridLayout();
    all->setSpacing(3);

    // assign layout to central widget
    centralWidget->setLayout(all);

    // ...........................................................
    QGroupBox *box1 = new QGroupBox(tr("System Parametrs"), this);
    all->addWidget(box1,0,0);

    QGridLayout *gbox1 = new QGridLayout();
    gbox1->setVerticalSpacing(0);
    gbox1->setHorizontalSpacing(3);

    box1->setLayout(gbox1);

    QLabel *Label0 = new QLabel(tr("Input Power:"), this);
    gbox1->addWidget(Label0, 0,0);
    inputPower = new QLineEdit("-60", this);
    connect(inputPower, SIGNAL(editingFinished()), SLOT(validate()));
    gbox1->addWidget(inputPower, 0,1);
    QLabel *Label1 = new QLabel(tr("dBm"), this);
    gbox1->addWidget(Label1, 0,2);

    QLabel *Label2 = new QLabel(tr("Noise Bandwidth:"), this);
    gbox1->addWidget(Label2, 1,0);
    noiseBand = new QLineEdit("1000", this);
    connect(noiseBand, SIGNAL(editingFinished()), SLOT(validate()));
    gbox1->addWidget(noiseBand, 1,1);
    freqUnit = new QComboBox(this);
    freqUnit->addItem(tr("Hz"));
    freqUnit->addItem(tr("kHz"));
    freqUnit->addItem(tr("MHz"));
    freqUnit->addItem(tr("GHz"));
    gbox1->addWidget(freqUnit, 1,2);

    QLabel *Label3 = new QLabel(tr("Min S/N for Demod:"), this);
    gbox1->addWidget(Label3, 2,0);
    minSn = new QLineEdit("-60", this);
    connect(minSn, SIGNAL(editingFinished()), SLOT(validate()));
    gbox1->addWidget(minSn, 2,1);
    QLabel *Label4 = new QLabel(tr("dB"), this);
    gbox1->addWidget(Label4, 2,2);

    QLabel *Label5 = new QLabel(tr("Temperature:"), this);
    gbox1->addWidget(Label5, 3,0);
    temperature = new QLineEdit("25", this);
    connect(temperature, SIGNAL(editingFinished()), SLOT(validate()));
    gbox1->addWidget(temperature, 3,1);
    temperatureUnit = new QComboBox(this);
    temperatureUnit->addItem(QString(Qt::Key_degree) +"C"); // see enum temperatureUnits
    temperatureUnit->addItem(QString(Qt::Key_degree) +"K");
    connect(temperatureUnit, SIGNAL(currentIndexChanged(int)), SLOT(validate()));
    gbox1->addWidget(temperatureUnit, 3,2);

    QLabel *Label6 = new QLabel(tr("PER-to-RMS ratio:"), this);
    gbox1->addWidget(Label6, 4,0);
    perToRms = new QLineEdit("0", this);
    connect(perToRms, SIGNAL(editingFinished()), SLOT(validate()));
    gbox1->addWidget(perToRms, 4,1);
    QLabel *Label7 = new QLabel(tr("dB"), this);
    gbox1->addWidget(Label7, 4,2);

    // ...........................................................
    table = new QTableWidget(this);
    //table->horizontalHeader()->setMovable(true);
    table->setSelectionMode(QAbstractItemView::NoSelection);
    all->addWidget(table, 1, 0, 1, -1);

    // ...........................................................
    QGroupBox *box2 = new QGroupBox(tr("System Analysis"), this);
    all->addWidget(box2,2,0);

    QGridLayout *gbox2 = new QGridLayout();
    gbox1->setVerticalSpacing(0);
    gbox1->setHorizontalSpacing(3);

    box2->setLayout(gbox2);
/*
    QLabel *Label3 = new QLabel(tr("Relative permittivity:"), this);
    gbox2->addWidget(Label3, 0,0);
    ComboEr = new QComboBox(this);
    ComboEr->setEditable(true);
    ComboEr->lineEdit()->setValidator(DoubleVal);
    connect(ComboEr, SIGNAL(activated(const QString&)), SLOT(slotTakeEr(const QString&)));
    gbox2->addWidget(ComboEr, 0,1);

    const char **p = List_er;
    while(*(++p))
    ComboEr->addItem(*p);  // put material properties into combobox
    ComboEr->lineEdit()->setText("9.8");

    QLabel *Label4 = new QLabel(tr("Substrate height:"), this);
    gbox2->addWidget(Label4, 1,0);
    EditHeight = new QLineEdit("1.0", this);
    EditHeight->setValidator(DoubleVal);
    gbox2->addWidget(EditHeight, 1,1);
    QLabel *Label5 = new QLabel("mm", this);
    gbox2->addWidget(Label5, 1,2);

    QLabel *Label6 = new QLabel(tr("metal thickness:"), this);
    gbox2->addWidget(Label6, 2,0);
    EditThickness = new QLineEdit("12.5", this);
    EditThickness->setValidator(DoubleVal);
    gbox2->addWidget(EditThickness, 2,1);
    QLabel *Label7 = new QLabel("um", this);
    gbox2->addWidget(Label7, 2,2);

    QLabel *Label8 = new QLabel(tr("minimum width:"), this);
    gbox2->addWidget(Label8, 3,0);
    EditMinWidth = new QLineEdit("0.4", this);
    EditMinWidth->setValidator(DoubleVal);
    gbox2->addWidget(EditMinWidth, 3,1);
    QLabel *Label9 = new QLabel("mm", this);
    gbox2->addWidget(Label9, 3,2);

    QLabel *Label10 = new QLabel(tr("maximum width:"), this);
    gbox2->addWidget(Label10, 4,0);
    EditMaxWidth = new QLineEdit("5.0", this);
    EditMaxWidth->setValidator(DoubleVal);
    gbox2->addWidget(EditMaxWidth, 4,1);
    QLabel *Label11 = new QLabel("mm", this);
    gbox2->addWidget(Label11, 4,2);

    QSpacerItem *mySpacer=new QSpacerItem(1,1, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gbox2->addItem(mySpacer, 5, 0, 1, -1);

    // ...........................................................
    QPushButton *ButtonGo = new QPushButton(tr("Calculate and put into Clipboard"), this);
    connect(ButtonGo, SIGNAL(clicked()), SLOT(slotCalculate()));
    all->addWidget(ButtonGo, 1, 0, 1, -1);

    LabelResult = new QLabel(this);
    ResultState = 100;
    slotShowResult();
    LabelResult->setAlignment(Qt::AlignHCenter);
    all->addWidget(LabelResult, 2, 0, 1, -1);

    // -------  finally set initial state  --------
    slotTypeChanged(0);
    slotClassChanged(0);
    */
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
        sender = temperature;
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

    if (sender == noiseBand)
    {
        if (num <= 0)
            sender->setStyleSheet("background-color:red;");
        else
            sender->setStyleSheet("");
    }
    else if (sender == temperature)
    {
        if ((temperatureUnit->currentIndex() == celsius) && (num <= ABS_ZERO))
            sender->setStyleSheet("background-color:red;");
        else if ((temperatureUnit->currentIndex() == kelvin) && (num <= 0))
            sender->setStyleSheet("background-color:red;");
        else
            sender->setStyleSheet("");
    }
}
