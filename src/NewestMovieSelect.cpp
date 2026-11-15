#include "NewestMovieSelect.h"
#include <vector>
#include <stdexcept>

//Finds the newest movie from unwatched movies
size_t NewestMovieSelect::select(const std::vector<Movie>& movies) const {
	bool found = false;
	size_t newest = 0;


	for (size_t i = 0; i < movies.size(); ++i) {
		if (!movies[i].isWatched()) {
			if (!found || movies[i].getReleaseYear() > movies[newest].getReleaseYear()) {
				newest = i;
				found = true;
			}
		}
	}

	if (!found) {
		throw std::runtime_error("You Are All Caught Up On Your Films!");
	}
	return newest;
}