#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include "MovieManager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    enum class WhichQuest {
        None, 
        AddTitle, 
        AddGenre, 
        AddReleaseYear, 
        GetsMovieID, 
        WatchStatus, 
        RateMovie, 
        WhatToWatch
    };

    Ui::MainWindow *ui;
    MovieManager manager_;
    WhichQuest whichQuest_ = WhichQuest::None;
    WhichQuest usesMovieId_ = WhichQuest::None;

    std::string pendingTitle_;
    std::string pendingGenre_;
    int pendingID_ = 0;

    void refreshList();
    void usersInput();
    void showMessage(const QString& msg);
};

#endif // MAINWINDOW_H