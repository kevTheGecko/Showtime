#pragma once
#include <string>

//Holds all the information of one movie
class Movie {
public:
	//Creates a movie with an ID, title, genre, and release year
	Movie(int id, const std::string& title, const std::string& genre, int releaseYear);

	//Getters
	int getId() const;
	std::string getTitle() const;
	std::string getGenre() const;
	int getReleaseYear() const;
	bool isWatched() const;
	int getRating() const;

	//Setters
	void setWatched(bool watched);
	void setRating(int rating);

private:
	//A movies private data
	int id_;
	std::string title_;
	std::string genre_;
	int releaseYear_;
	bool watched_;
	int rating_;
};