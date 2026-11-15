#include "MovieManager.h"
#include <stdexcept>

//Holds all the information of the list of movies
int MovieManager::addMovie(const std::string& title, const std::string& genre, int releaseYear) {
	Movie movie(nextId_, title, genre, releaseYear);
	movies_.push_back(movie);
	nextId_++;
	return movie.getId();
}

//Asks the select method to choose what to watch next
std::string MovieManager::selectMovie(const SelectMethod& method) const {
	size_t position = method.select(movies_);
	return movies_.at(position).getTitle();
}

//Finds movie and sets the rating
std::string MovieManager::rateMovie(int id, int rating) {
	Movie& movie = findMovie(id);
	movie.setRating(rating);
	return movie.getTitle();
}

//Finds movie and sets watch status
std::string MovieManager::setWatched(int id, bool watched) {
	Movie& movie = findMovie(id);
	movie.setWatched(watched);
	return movie.getTitle();
}

//Returns the list of movies
const std::vector<Movie>& MovieManager::getMovies() const {
	return movies_;
}

//Searches the list of movies with an id
Movie& MovieManager::findMovie(int id) {
	for (Movie& mov : movies_) {
		if (mov.getId() == id) {
			return mov;
		}
	}
	throw std::out_of_range("A Movie With ID " + std::to_string(id) + " Does Not Exist!");
}