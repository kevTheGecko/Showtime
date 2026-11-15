#include "Movie.h"
#include <stdexcept>

//How a movie is created, read through, and changed
Movie::Movie(int id, const std::string& title, const std::string& genre, int releaseYear)
    : id_(id), title_(title), genre_(genre), releaseYear_(releaseYear), watched_(false), rating_(0) {
    if (title.empty()) {
        throw std::invalid_argument("Title Cannot be Empty!");
    }
    
    // new added line
    if (releaseYear < 1888 || releaseYear > 2026) {
        throw std::invalid_argument("Not a Valid Year soryy!");
    }
    
}


//Getters: Return movie information
int Movie::getId() const { return id_; }
std::string Movie::getTitle() const { return title_; }
std::string Movie::getGenre() const { return genre_; }
int Movie::getReleaseYear() const { return releaseYear_; }
bool Movie::isWatched() const { return watched_; }
int Movie::getRating() const { return rating_; }

//Changes watch status
void Movie::setWatched(bool watched) {
    watched_ = watched;
}

//Changes rating 1-5
void Movie::setRating(int rating) {
    if (rating < 1 || rating > 5) {
        throw std::invalid_argument("Please pick a number from 1-5!");
    }
    rating_ = rating;
}