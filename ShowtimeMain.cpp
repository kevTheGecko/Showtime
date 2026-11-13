#include <iostream>
#include <string>
#include <stdexcept>
#include "MovieManager.h"
#include "HighestRatedSelect.h"
#include "NewestMovieSelect.h"

//Prints all the movies in a list
void showMovies(const MovieManager& manager) {
    if (manager.getMovies().size() == 0) {
        std::cout << "No Movies in Watchlist!\n\n";
        return;
    }

    for (const Movie& mov : manager.getMovies()) {
        std::cout << mov.getId() << " " << mov.getTitle() << " " << mov.getGenre() << " " << mov.getReleaseYear() << " |";

        //Used to print Watch Status
        if (mov.isWatched()) {
            std::cout << "Watched";
        }
        else std::cout << "Not Watched";
        std::cout << "| ";

        //Used to print Rating
        if (mov.getRating() == 0) {
            std::cout << "Not Rated";
        }
        else std::cout << mov.getRating() << "/5";

        std::cout << "\n";
    }
}


// Task 1 GUI Event Handler mapping: onAddClicked

void onAddClicked(MovieManager& manager, const std::string& title, const std::string& genre, int year) {
    try {
        int id = manager.addMovie(title, genre, year);
        std::cout << "Added your movie with ID number " << id << " to the watchlist!\n\n";
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Could not add movie: " << e.what() << "\n\n";
    }
}

//Runs the Program
int main() {
    MovieManager manager;
    int choice = -1;

    while (choice != 0) {
        std::cout << "\n******Welcome to Showtime!******\nPlease respond with a number from one of the options below:\n\n1. Add Movie\n2. View Watchlist\n3. Set Watch Status\n4. Rate a Movie\n5. What To Watch?\n0. Quit\n\n";
        
        if (!(std::cin >> choice)) {
            std::cout << "Please respond with a number, Showtime closing...\n";
            return 1;
        }

        //Asks the user to create a movie (Title, Genre, Release)
        if (choice == 1) {
            std::string title, genre;
            int year;

            std::cout << "Title: ";
            std::cin.ignore();
            std::getline(std::cin, title);
            std::cout << "Genre: ";
            std::getline(std::cin, genre);
            std::cout << "Release Year: ";

            if (!(std::cin >> year)) {
                std::cout << "Please respond with a number, Showtime closing...\n";
                return 1;
            }

            // Calls the event handler function 
            onAddClicked(manager, title, genre, year);

        }

        //Prints all the movies user added to their watchlist
        else if (choice == 2) {
            std::cout << "\n******It's Showtime******\n";
            showMovies(manager);
            std::cout << "*************************\n\n";
        }

        //Lets the user set the watched status of a movie
        else if (choice == 3) {
            int id, status;
            std::cout << "Movie ID: ";
            if (!(std::cin >> id)) {
                std::cout << "Please respond with a number, Showtime closing...\n";
                return 1;
            }

            //User sets the watched status of a movie
            std::cout << "1 = Watched\n2 = Not Watched\nStatus: ";
            if (!(std::cin >> status)) {
                std::cout << "Please respond with a number, Showtime closing...\n";
                return 1;
            }
            if (status != 1 && status != 2) {
                std::cout << "Please pick 1 or 2. Nothing was changed.\n";
            }
            else {
                try {
                    std::string title = manager.setWatched(id, status == 1);
                    if (status == 1) std::cout << "Updated " << title << " to Watched.\n";
                    else std::cout << "Updated " << title << " to Not Watched.\n";
                }
                catch (const std::out_of_range& e) {
                    std::cout << "Could not update movie: " << e.what() << "\n";
                }
            }
        }

        //Lets the user rate their movies
        else if (choice == 4) {
            int id, rating;
            std::cout << "Movie ID: ";
            if (!(std::cin >> id)) {
                std::cout << "Please respond with a number, Showtime closing...\n";
                return 1;
            }

            //User sets the rating of a movie
            std::cout << "Rating (1-5): ";
            if (!(std::cin >> rating)) {
                std::cout << "Please respond with a number, Showtime closing...\n";
                return 1;
            }
            try {
                std::string title = manager.rateMovie(id, rating);
                std::cout << "Rated " << title << " " << rating << "/5\n";
            }
            catch (const std::out_of_range& e) {
                std::cout << "Could not rate movie: " << e.what() << "\n";
            }
            catch (const std::invalid_argument& e) {
                std::cout << "Could not rate movie: " << e.what() << "\n";
            }
        }

        //Selects a movie for the user to watch (Newest/Highest Rated)
        else if (choice == 5) {
            int style;
            std::cout << "1. Highest Rated Movie\n2. Newest Movie\nWhich would you like: ";
            if (!(std::cin >> style)) {
                std::cout << "Please respond with a number, Showtime closing...\n";
                return 1;
            }
            try {
                if (style == 1) {
                    HighestRatedSelect highestRated;
                    std::cout << "Your chosen movie is " << manager.selectMovie(highestRated) << "\n";
                }
                else if (style == 2) {
                    NewestMovieSelect newestMovie;
                    std::cout << "Your chosen movie is: " << manager.selectMovie(newestMovie) << "\n";
                }
                else std::cout << "Please pick 1 or 2!\n";
            }
            catch (const std::runtime_error& e) {
                std::cout << "\nCould not pick a movie: " << e.what() << "\n";
            }
        }
        //Makes sure a valid option is given
        else if (choice != 0) {
            std::cout << "Please pick from the options given...\n\n";
        }

    }

    std::cout << "Enjoy Your Movie!\n";
    return 0;
}
