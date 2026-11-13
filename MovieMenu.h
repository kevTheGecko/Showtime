#pragma once

#include <QWidget>
#include "MovieManager.h" // Your backend manager

namespace Ui {
class MovieMenu;
}

class MovieMenu : public QWidget {
    Q_OBJECT

public:
    // Constructor receives your shared MovieManager object
    explicit MovieMenu(MovieManager& sharedManager, QWidget *parent = nullptr);
    ~MovieMenu();

private:
    Ui::MovieMenu *ui;
    MovieManager& manager_; // Reference to your backend
};