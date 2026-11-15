#pragma once
#include "SelectMethod.h"

//Child 1: Selects highest rated unwatched movie
class HighestRatedSelect : public SelectMethod {
public: 
	size_t select(const std::vector<Movie>& movies) const override;
};