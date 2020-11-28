#include "startpanel.h"
#include <QGraphicsItemGroup>
#include "qdebug.h"
#include "QHBoxLayout"


StartPanel::StartPanel()
{
//    startPanelUI.addItem(&sampleBackground);
//    sampleBackground.setPixmap(QPixmap(":test_map"));
//    QHBoxLayout *testLayout = new QHBoxLayout;
//    testLayout->addWidget(&sampleButton);
//    sampleButton.setIcon(QIcon(QPixmap(":test_character")));
//    QPushButton *button2 = new QPushButton("SFH");
//    button2->setMinimumSize(50, 50);
//    testLayout->addWidget(button2);
//    testLayout->setSpacing(50);
//    QWidget *window = new QWidget;
//    window->setLayout(testLayout);
//    startPanelUI.addWidget(window)->setPos(100,200);
        addItem(&sampleBackground);
        sampleBackground.setPixmap(QPixmap(":test_map"));
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->setSpacing(25);
        buttonLayout->addWidget(&startButton);
        buttonLayout->addWidget(&endButton);
        //buttonLayout->direction(0);



}

QGraphicsScene *StartPanel::getScene()
{
    return this;
}

QPushButton *StartPanel::getButtonStart()
{
    return &startButton;
}

QPushButton *StartPanel::getButtonQuit()
{
    return &endButton;
}

void StartPanel::initializeButton(QPushButton *button)
{
    button->setMinimumSize(50, 100);
    button->setMaximumSize(100,200);
    button->setText("SAMPLE");
}

void StartPanel::testFunc()
{
    qDebug()<<"PRESSSSSSSSSSSABLE";
}
