// menuwidget.cpp
#include "menuwidget.h"

MenuWidget::MenuWidget(QWidget *parent) : QWidget(parent)
{
    playButton = new QPushButton("Играть", this);
    connect(playButton, &QPushButton::clicked, this, &MenuWidget::onPlayButtonClicked);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(playButton);
    layout->addStretch();
    setLayout(layout);
}

void MenuWidget::onPlayButtonClicked()
{
    emit playButtonClicked();
}
