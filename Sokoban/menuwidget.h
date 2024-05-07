// menuwidget.h
#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>

class MenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MenuWidget(QWidget *parent = nullptr);

signals:
    void playButtonClicked();

private:
    QPushButton *playButton;

private slots:
    void onPlayButtonClicked();
};

#endif // MENUWIDGET_H
