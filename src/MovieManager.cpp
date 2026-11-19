#include "MovieManager.h"
#include <stdexcept>

//Holds all the information of the list of movies
int MovieManager::addMovie(const std::string& title, const std::string& genre, int releaseYear) {
	Movie movie(nextId_, title, genre, releaseYear,false,0);
	movies_.push_back(movie);
	std::ofstream file;
	try{
		file.open("../../../files/movie.csv", std::ios::out | std::ios::app);
		file<<nextId_<<","<<title<<","<<genre<<","<<releaseYear<<","<<movie.isWatched()<<","<<movie.getRating()<<"\n";
		file.close();
	}
	catch (const std::invalid_argument& e) {}

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
	std::ofstream file;
	try{
		file.open("../../../files/movie.csv", std::ios::out );
			for (const Movie& mov : movies_){
file<<mov.getId()<<","<<mov.getTitle()<<","<<mov.getGenre()<<","<<mov.getReleaseYear()<<","<<mov.isWatched()<<","<<mov.getRating()<<"\n";
}
		file.close();
	}
	catch (const std::invalid_argument& e) {}
	
	return movie.getTitle();
}

//Finds movie and sets watch status
std::string MovieManager::setWatched(int id, bool watched) {
	Movie& movie = findMovie(id);
	movie.setWatched(watched);
	std::ofstream file;
	try{
		file.open("../../../files/movie.csv", std::ios::out);
			for (const Movie& mov : movies_){
file<<mov.getId()<<","<<mov.getTitle()<<","<<mov.getGenre()<<","<<mov.getReleaseYear()<<","<<mov.isWatched()<<","<<mov.getRating()<<"\n";
}
		file.close();
	}
	catch (const std::invalid_argument& e) {}
	
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

void MovieManager::recall(){
	std::ifstream ifile;
	try{
		ifile.open("../../../files/movie.csv", std::ios::in);
		std::vector<std::string> row;
		std::string line,word,temp;
		while(getline(ifile, line)){
			row.clear();
			std::stringstream s(line);
			while(getline(s,word,',')){
				row.push_back(word);
			}
			Movie movie(stoi(row[0]),row[1],row[2],stoi(row[3]),row[4]=="1",stoi(row[5]));
			movies_.push_back(movie);
			nextId_++;
			
			
		}
		ifile.close();
	}
	catch(...){
	
	}

}