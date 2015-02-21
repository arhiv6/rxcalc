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
    setWindowTitle(APP_NAME " v" APP_VERSION);
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

    // -------  create main windows widgets --------
    all  = new QGridLayout();
    all->setSpacing(3);

    // assign layout to central widget
    centralWidget->setLayout(all);

    // ...........................................................
    box1 = new QGroupBox(tr("Filter"), this);
    all->addWidget(box1,0,0);

    gbox1 = new QGridLayout();
    gbox1->setSpacing(3);

    box1->setLayout(gbox1);

    QLabel *Label0 = new QLabel(tr("Realization:"), this);
    gbox1->addWidget(Label0, 0,0);
    ComboRealize = new QComboBox(this);
    ComboRealize->addItem("LC ladder (pi type)");
    ComboRealize->addItem("LC ladder (tee type)");
    ComboRealize->addItem("C-coupled transmission lines");
    ComboRealize->addItem("Microstrip end-coupled");
    ComboRealize->addItem("Coupled transmission lines");
    ComboRealize->addItem("Coupled microstrip");
    ComboRealize->addItem("Stepped-impedance");
    ComboRealize->addItem("Stepped-impedance microstrip");
    ComboRealize->addItem("Equation-defined");
    gbox1->addWidget(ComboRealize, 0,1);
    connect(ComboRealize, SIGNAL(activated(int)), SLOT(slotRealizationChanged(int)));
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
