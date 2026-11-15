#include "HighestRatedSelect.h"
#include <stdexcept>

//Finds the highest rated movie from unwatched movies
size_t HighestRatedSelect::select(const std::vector<Movie>& movies) const {
	bool found = false;
	size_t best = 0;


	for (size_t i = 0; i < movies.size(); ++i) {
		if (!movies[i].isWatched()) {
			if (!found || movies[i].getRating() > movies[best].getRating()) {
				best = i;
				found = true;
			}
		}
	}

	if (!found) {
		throw std::runtime_error("You Are All Caught Up On Your Films!");
	}
	return best;
}