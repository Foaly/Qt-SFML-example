////////////////////////////////////////////////////////////
//
// Qt SFML example - Setting up a SFML window inside a Qt window
// Copyright (C) 2016 Maximilian Wagenbach
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#include <QBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QMessageBox>


#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Qt SFML example!");
    m_sfmlWidget.setMinimumSize(400, 400);

    QGroupBox* controlsGroupBox = new QGroupBox("UI Foo");
    controlsGroupBox->setMaximumWidth(200);

    QFormLayout *controlsLayout = new QFormLayout;

    m_wowButton = new QPushButton("Such Button!");
    connect(m_wowButton, SIGNAL (released()), this, SLOT (handleButton()));
    controlsLayout->addRow(m_wowButton);

    controlsGroupBox->setLayout(controlsLayout);

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addWidget(&m_sfmlWidget);
    mainLayout->addWidget(controlsGroupBox);

    QWidget *widget = new QWidget;
    widget->setLayout(mainLayout);
    setCentralWidget(widget);
}

SFMLWidget &MainWindow::getSFMLWidget()
{
    return m_sfmlWidget;
}

void MainWindow::handleButton()
{
    QMessageBox msgBox;
    msgBox.setText("Much wow!");
    msgBox.exec();
}
