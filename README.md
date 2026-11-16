# Showtime
Showtime allows movie fans to document their movies. Users of the program are able to add movies to their watchlist where they can set the movies watch status and give the movies a rating from 1 to 5.
The user is also able to ask the program what movie to watch next! 

**Team Code-Masters:** Kevin, Joseph, Kaiya

**Intended Users:** Anyone who is a fan of movies!

# Program Functionality
1. Add Movie - User types in Title, Genre, Release Date (A movie is create, given an ID, and added to the list)
2. Watchlist - A display that shows the list of movies at all times
3. Set Watch Status - User types ID of their selected movie then type 1/2 to set the watch status (Selected movies watch status is updated to users option)
4. Rate a Movie - User types ID of their selected movie then type a rating from 1 to 5 (Selected movies rating is updated to users option)
5. What To Watch? - User types 1/2 to select a movie by the highest rating or by the newest release (Finds an unwatched movie based off users option)

# Install Gudie
**Windows:**
1. Make sure you have Visual Studio 2022 or newer installed
2. Make sure you have Qt 6 installed

   - In the installer, choose QT version MSVC 64-bit

3. Build and Run Solution:

   - Clone the Repo
   - In VS, File -> Open -> "Showtime" folder
   - Wait until output states "CMake Generation Finished"
   - Choose Showtime.exe as the startup
   - Build and then run

**Mac:**
1. Install the tools once: ```xcode-select --install``` and ```brew install cmake qt```
2. In the Showtime Folder run:
```
cmake -S . -B build -DCMAKE_PREFIX_PATH="$(brew --prefix qt)"
cmake --build build
./build/Showtime
```

# How To Use?
**The program has 4 buttons to choose from:**
1. **Add Movie**
   
   - After clicking, in the input box type the Title and hit enter
   - Then type the Genre and hit enter
   - And finally type the Release Year and hit enter (Must be between 1 and 2026)

2. **Watch Status**

   - After clicking, type the ID of your movie in the input box
   - Then type 1 (Watched) or 2 (Not Watched) into the input box

3. **Rate Movie**

   - After clicking, type the ID of your movie in the input box
   - Then type a number from 1 to 5 into the input box

4. **What to Watch?**

   - N/A


# Code Explained
**Movie.h/.cpp** - Creates a movie (ID, Title, Genre, Release Year, WatchStatus, Rating), constructor and setters check validity

**MovieManager.h/.cpp** - Holds list of movies and verifies them. Functions (add, find by ID, rate, set watch status, select movie to watch)

**SelectMethod.h** - Abstract base class, virtual function "select"

**HighestRatedSelect.h/.cpp** - Child class, selects the highest rated movies (not watched)

**NewestMovieSelect.h/.cpp** - Child class, selects the newest released movies (not watched)

**mainwindow.h/.cpp** - The GUI, it connects the buttons and text inputs to the MovieManager, refreshes and shows updated list of movies at all times, and also displays error outputs

**mainwindow.ui** - The actual menu used by the user built using QT Designer

**ShowtimeMain.cpp** - Starts the Program


# Assistance Used
A mixture of youtube and AI was used to explain how to make Windows and Mac cross compatible using CMake because teammates had different operating systems making it difficult to work together. It was also used to cross reference the program against the rubric so nothing on the rubric was left missing (Didn't add anything itself only told what was missing). AI alongside with Youtube videos were also used to further explain how QT works and some of QT's important functionalities, they also explained how to connect QT to the Visual Studio workspace. (https://doc.qt.io) Was used for further QT explanations.
