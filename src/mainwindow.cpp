#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdexcept>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(size());
    refreshList();

    ui->errorOutput->addItem("Welcome to Showtime!");
    ui->errorOutput->addItem("Please pick from one of the options on the left:");
    ui->errorOutput->addItem("");
    ui->errorOutput->addItem("Add Movie - Type a Title, then Genre, and then a Release Year");
    ui->errorOutput->addItem("Watch Status - Type a Movie ID, then 1 for Set Watched or 2 for Not Watched");
    ui->errorOutput->addItem("Rate Movie - Type the Movies ID and a Rating From 1 to 5");
    ui->errorOutput->addItem("What to Watch? - Type 1 for Highest Rated or 2 for Newest");
    ui->errorOutput->addItem("");
    ui->errorOutput->addItem("Your watchlist is shown on the left.");

    //Add Movie Button
    connect(ui->btnAddMovie, &QPushButton::clicked, this, [this]() {
        whichQuest_ = WhichQuest::AddTitle;
        ui->editInput->setPlaceholderText("Title");
        showMessage("Adding Movie...");
        ui->editInput->setFocus();
        });

    connect(ui->editInput, &QLineEdit::returnPressed, this, &MainWindow::usersInput);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshList() {
    ui->listMovies->clear();

    for (const Movie& mov : manager_.getMovies()) {
        //Movies Main Info
        QString movieline = QString::number(mov.getId()) + ". " + QString::fromStdString(mov.getTitle()) + ", " + QString::fromStdString(mov.getGenre()) + ", " + QString::number(mov.getReleaseYear()) + " |";

        //Watch Status
        if (mov.isWatched()) movieline += "Watched";
        else movieline += "Not Watched";
        movieline += "| ";

        //Rating
        if (mov.getRating() == 0) movieline += "Not Rated";
        else movieline += QString::number(mov.getRating()) + "/5";

        ui->listMovies->addItem(movieline);

    }
}

//ErrorOutput Messenger
void MainWindow::showMessage(const QString& message) {
    ui->errorOutput->addItem(message);
    ui->errorOutput->scrollToBottom();
}

//Users inputs with GUI
void MainWindow::usersInput() {
    QString input = ui->editInput->text();
    ui->editInput->clear();

    switch (whichQuest_) {
    case WhichQuest::None:
        showMessage("Please click a button first!");
        break;

    //Gets movie title input
    case WhichQuest::AddTitle:
        pendingTitle_ = input.toStdString();
        whichQuest_ = WhichQuest::AddGenre;
        ui->editInput->setPlaceholderText("Genre");
        break;

    //Gets movie genre input
    case WhichQuest::AddGenre:
        pendingGenre_ = input.toStdString();
        whichQuest_ = WhichQuest::AddReleaseYear;
        ui->editInput->setPlaceholderText("Release Year");
        break;

    //Gets movie release year
    case WhichQuest::AddReleaseYear:
        bool validYear = false;
        int year = input.toInt(&validYear);

        if (!validYear) {
            showMessage("Please respond with a number!");
            break;
        }

        try {
            int id = manager_.addMovie(pendingTitle_, pendingGenre_, year);
            showMessage("Added movie " + QString::number(id) + " to watchlist!");
            refreshList();
        }
        catch (const std::invalid_argument& e) {
            showMessage(QString("Could not add movie: ") + e.what());
        }

        whichQuest_ = WhichQuest::None;
        ui->editInput->setPlaceholderText("Please click a button!");
    }
}