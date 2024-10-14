#include <iostream>
#include <string>
#include <vector>

// Song class definition
class Song {
private:
    std::string title;
    std::string artist;
    std::string album;
    int duration; // in seconds
    std::string genre;

    // Static variable to keep track of the total number of songs
    static int totalSongs;

public:
    // Default Constructor
    Song() : title("Unknown"), artist("Unknown"), album("Unknown"), duration(0), genre("Unknown") {
        totalSongs++; // Increment totalSongs whenever a new Song is created
        std::cout << "Default constructor called: Creating a song with default values.\n";
    }

    // Parameterized Constructor
    Song(std::string title, std::string artist, std::string album, int duration, std::string genre) {
        this->title = title;
        this->artist = artist;
        this->album = album;
        this->duration = duration;
        this->genre = genre;
        totalSongs++; // Increment totalSongs whenever a new Song is created
        std::cout << "Parameterized constructor called: Creating a song.\n";
    }

    // Copy Constructor
    Song(const Song& other) {
        this->title = other.title;
        this->artist = other.artist;
        this->album = other.album;
        this->duration = other.duration;
        this->genre = other.genre;
        totalSongs++;
        std::cout << "Copy constructor called: Creating a copy of an existing song.\n";
    }

    // Destructor
    ~Song() {
        totalSongs--; // Decrement totalSongs when a Song is destroyed
        std::cout << "Destructor called: Deleting a song.\n";
    }

    // Accessors (Getters)
    std::string getTitle() const { return title; }
    std::string getArtist() const { return artist; }
    std::string getAlbum() const { return album; }
    int getDuration() const { return duration; }
    std::string getGenre() const { return genre; }

    // Mutators (Setters)
    void setTitle(const std::string& newTitle) { title = newTitle; }
    void setArtist(const std::string& newArtist) { artist = newArtist; }
    void setAlbum(const std::string& newAlbum) { album = newAlbum; }
    void setDuration(int newDuration) { duration = newDuration; }
    void setGenre(const std::string& newGenre) { genre = newGenre; }

    // Static method to get the total number of songs
    static int getTotalSongs() {
        return totalSongs;
    }

    // Static method to display a summary of songs
    static void displaySongSummary() {
        std::cout << "Total number of songs created: " << totalSongs << "\n";
    }

    // Display song details
    void displayInfo() const {
        std::cout << "Title: " << title << "\n"
                  << "Artist: " << artist << "\n"
                  << "Album: " << album << "\n"
                  << "Duration: " << duration << " seconds\n"
                  << "Genre: " << genre << "\n";
    }
};

// Initialize the static variable
int Song::totalSongs = 0;

// Playlist class definition
class Playlist {
private:
    std::string name;
    std::vector<Song*> songs;

    // Static variable to keep track of the total number of playlists
    static int totalPlaylists;

public:
    // Default Constructor
    Playlist() : name("Untitled Playlist") {
        totalPlaylists++;
        std::cout << "Default constructor called: Creating an untitled playlist.\n";
    }

    // Parameterized Constructor
    Playlist(std::string name) {
        this->name = name;
        totalPlaylists++;
        std::cout << "Parameterized constructor called: Creating a playlist named " << name << ".\n";
    }

    // Destructor to clean up dynamically allocated songs
    ~Playlist() {
        for (Song* song : songs) {
            delete song; // Free each Song object
        }
        totalPlaylists--; // Decrement totalPlaylists when a Playlist is destroyed
        std::cout << "Destructor called: Deleting playlist \"" << name << "\".\n";
    }

    // Accessor (Getter)
    std::string getName() const { return name; }

    // Mutator (Setter)
    void setName(const std::string& newName) { name = newName; }

    // Add a song to the playlist
    void addSong(Song* song) {
        songs.push_back(song);
    }

    // Static method to get the total number of playlists
    static int getTotalPlaylists() {
        return totalPlaylists;
    }

    // Display all songs in the playlist
    void displayPlaylist() const {
        std::cout << "Playlist: " << name << "\n";
        for (const auto& song : songs) {
            song->displayInfo();
            std::cout << "---------------------------\n";
        }
    }
};

// Initialize the static variable
int Playlist::totalPlaylists = 0;

// Main function
int main() {
    // Demonstrating the use of different constructors

    // Default constructor
    Song* defaultSong = new Song();  // Creates a song with default values

    // Parameterized constructor
    Song* paramSong = new Song("Shape of You", "Ed Sheeran", "Divide", 233, "Pop");

    // Copy constructor
    Song* copySong = new Song(*paramSong);  // Creates a copy of 'paramSong'

    // Display song info
    defaultSong->displayInfo();
    paramSong->displayInfo();
    copySong->displayInfo();

    // Playlist creation using parameterized constructor
    Playlist* playlist = new Playlist("My Favorite Songs");
    
    // Adding songs to the playlist
    playlist->addSong(paramSong);
    playlist->addSong(copySong);

    // Display playlist
    playlist->displayPlaylist();

    // Demonstrating the use of destructors
    delete defaultSong;
    delete playlist; // Will also clean up dynamically allocated songs in the playlist

    std::cout << "\nAfter cleanup:\n";
    Song::displaySongSummary();
    std::cout << "Total Playlists Remaining: " << Playlist::getTotalPlaylists() << "\n";

    return 0;
}
