#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab13_oop.h"

class lab13_oop : public QMainWindow
{
    Q_OBJECT

public:
    lab13_oop(QWidget *parent = nullptr);
    ~lab13_oop();

private:
    Ui::lab13_oopClass ui;
};
