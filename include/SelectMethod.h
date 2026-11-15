#pragma once
#include "Movie.h"
#include <vector>

//Abstract Base Class
class SelectMethod {
public:
	virtual ~SelectMethod() = default;
	virtual size_t select(const std::vector<Movie>& movies) const = 0;
};