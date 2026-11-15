#include "MovieMenu.h"
#include "ui_MovieMenu.h"
#include <QMessageBox>
#include <stdexcept>
#include <string>

MovieMenu::MovieMenu(MovieManager& sharedManager, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MovieMenu)
    , manager_(sharedManager)
{
    ui->setupUi(this);

    // --- CONNECT THE ADD BUTTON (TASK 1) ---
    connect(ui->addButton, &QPushButton::clicked, [this]() {
        // 1. Read input values from the GUI text fields
        QString titleStr = ui->titleLineEdit->text();
        QString genreStr = ui->genreLineEdit->text();
        
        bool yearOk = false;
        int yearVal = ui->yearLineEdit->text().toInt(&yearOk);

        // 2. Validate that the year is a valid number before calling backend
        if (!yearOk) {
            QMessageBox::warning(this, "Invalid Input", "Release Year must be a valid number!");
            return;
        }

        // 3. Call your exact backend logic function and handle exceptions
        try {
            int id = manager_.addMovie(titleStr.toStdString(), genreStr.toStdString(), yearVal);
            
            // Show success popup window
            QMessageBox::information(this, "Success!", "Added your movie with ID number " + QString::number(id) + " to the watchlist!");
            
            // Clear input fields for the next movie
            ui->titleLineEdit->clear();
            ui->genreLineEdit->clear();
            ui->yearLineEdit->clear();
        }
        catch (const std::invalid_argument& e) {
            // Catches validation errors from your Movie class constructor (e.g., empty titles)
            QMessageBox::warning(this, "Could Not Add Movie", e.what());
        }
    });
}

MovieMenu::~MovieMenu() {
    delete ui;
}