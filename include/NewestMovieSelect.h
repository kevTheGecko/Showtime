#pragma once
#include "SelectMethod.h"

//Child 2: Selects newest (By Release) unwatched movie
class NewestMovieSelect : public SelectMethod {
public:
	size_t select(const std::vector<Movie>& movies) const override;
};