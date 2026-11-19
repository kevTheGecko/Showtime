#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "HighestRatedSelect.h"
#include "NewestMovieSelect.h"
#include <stdexcept>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(size());
    manager_.recall();
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
    ui->listMovies->addItem("ID. Title, Genre, ReleaseYear |WatchStatus| Rating");

    //Add Movie Button
    connect(ui->btnAddMovie, &QPushButton::clicked, this, [this]() {
        whichQuest_ = WhichQuest::AddTitle;
        ui->editInput->setPlaceholderText("Title");
        showMessage("Adding Movie...");
        ui->editInput->setFocus();
        });
    //Watch Status Button
    connect(ui->btnWatchStatus, &QPushButton::clicked, this, [this]() {
        whichQuest_ = WhichQuest::GetsMovieID;
        usesMovieId_ = WhichQuest::WatchStatus;
        ui->editInput->setPlaceholderText("Movies ID");
        showMessage("Changing Watch Status...");
        ui->editInput->setFocus();
        });
    //Rate Movie Button
    connect(ui->btnRateMovie, &QPushButton::clicked, this, [this]() {
        whichQuest_ = WhichQuest::GetsMovieID;
        usesMovieId_ = WhichQuest::RateMovie;
        ui->editInput->setPlaceholderText("Movies ID");
        showMessage("Changing Movie Rating...");
        ui->editInput->setFocus();
        });

    //What to Watch Button
    connect(ui->btnWhatToWatch, &QPushButton::clicked, this, [this]() {
        whichQuest_ = WhichQuest::WhatToWatch;
        ui->editInput->setPlaceholderText("1 for Highest Rated, 2 for Newest");
        showMessage("Select recommendation method...");
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
    case WhichQuest::AddReleaseYear: {
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
        break;
        }
    
    //Gets MovieId
    case WhichQuest::GetsMovieID: {
        bool validId = false;
        int id = input.toInt(&validId);
        
        if (!validId) {
            showMessage("Please respond with a number!");
            break;
        }
        pendingID_ = id;
        whichQuest_ = usesMovieId_;

        //Watch Status Placeholder text
        if (usesMovieId_ == WhichQuest::WatchStatus) {
            ui->editInput->setPlaceholderText("1 = Watched, 2 = Not Watched");
        }

        if (usesMovieId_ == WhichQuest::RateMovie) {
            ui->editInput->setPlaceholderText("Rate the movie 1-5");
        }
        break;
    }

    //Gets/updates movie watch status
    case WhichQuest::WatchStatus: {
        int status = input.toInt();

        if (status != 1 && status != 2) {
            showMessage("Please pick 1 or 2!");
            break;
        }

        try {
            std::string title = manager_.setWatched(pendingID_, status == 1);
            if (status == 1) showMessage("Updated " + QString::fromStdString(title) + " to Watched.");
            else showMessage("Updated " + QString::fromStdString(title) + " to Not Watched.");
            refreshList();
        }
        catch (const std::out_of_range& e) {
            showMessage(QString("Could not update movie: ") + e.what());
        }

        whichQuest_ = WhichQuest::None;
        ui->editInput->setPlaceholderText("Please click a button!");
        break;
    }

    //Rate Movie
    case WhichQuest::RateMovie: {
        bool validRating = false;
        int rating = input.toInt(&validRating);

        if (!validRating) {
            showMessage("Please respond with a number!");
            break;
        }

        try {
            std::string title = manager_.rateMovie(pendingID_, rating);
            showMessage("Rated " + QString::fromStdString(title) + " " + QString::number(rating) + "/5");
            refreshList();
        }
        catch (const std::out_of_range& e) {
            showMessage(QString("Could not rate movie: ") + e.what());
        }
        catch (const std::invalid_argument& e) {
            showMessage(QString("Could not rate movie: ") + e.what());
        }

        whichQuest_ = WhichQuest::None;
        ui->editInput->setPlaceholderText("Please click a button!");
        break;
    }

    //What to Watch Selection
    case WhichQuest::WhatToWatch: {
        bool validChoice = false;
        int choice = input.toInt(&validChoice);

        if (!validChoice || (choice != 1 && choice != 2)) {
            showMessage("Please pick 1 (Highest Rated) or 2 (Newest)!");
            break;
        }

        try {
            std::string recommendedTitle;
            if (choice == 1) {
                HighestRatedSelect selector;
                recommendedTitle = manager_.selectMovie(selector);
                showMessage("Selected Highest Rated movie.");
            } else {
                NewestMovieSelect selector;
                recommendedTitle = manager_.selectMovie(selector);
                showMessage("Selected Newest movie.");
            }

            ui->movieResultOutput->setText("Movie Chosen: " + QString::fromStdString(recommendedTitle));
        }
        catch (const std::runtime_error& e) {
            showMessage(e.what());
        }

        whichQuest_ = WhichQuest::None;
        ui->editInput->setPlaceholderText("Please click a button!");
        break;
    }
    }
}