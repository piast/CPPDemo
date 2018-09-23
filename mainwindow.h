#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "GraphicsView.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //QGraphicsView* getGraphicsView();


#endif // MAINWINDOW_H
