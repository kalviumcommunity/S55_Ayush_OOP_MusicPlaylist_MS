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

public:
    // Constructor
    Song(std::string title, std::string artist, std::string album, int duration, std::string genre) {
        this->title = title;  // Use this pointer to distinguish member variable from parameter
        this->artist = artist;
        this->album = album;
        this->duration = duration;
        this->genre = genre;
    }

    // Getter methods
    std::string getTitle() const { return title; }
    std::string getArtist() const { return artist; }
    std::string getAlbum() const { return album; }
    int getDuration() const { return duration; }
    std::string getGenre() const { return genre; }

    // Method that returns the current object
    Song* getCurrentSong() {
        return this; // Returning the pointer to the current object
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

// Playlist class definition
class Playlist {
private:
    std::string name;
    std::vector<Song> songs;

public:
    // Constructor
    Playlist(std::string name) {
        this->name = name; // Use this pointer to distinguish member variable from parameter
    }

    // Add a song to the playlist
    void addSong(const Song& song) {
        songs.push_back(song);
    }

    // Method that returns the current object
    Playlist* getCurrentPlaylist() {
        return this; // Returning the pointer to the current object
    }

    // Display all songs in the playlist
    void displayPlaylist() const {
        std::cout << "Playlist: " << name << "\n";
        for (const auto& song : songs) {
            song.displayInfo();
            std::cout << "---------------------------\n";
        }
    }
};

// Main function
int main() {
    // Create an array of Song objects
    Song songArray[3] = {
        Song("Shape of You", "Ed Sheeran", "Divide", 233, "Pop"),
        Song("Blinding Lights", "The Weeknd", "After Hours", 200, "Synthwave"),
        Song("Bohemian Rhapsody", "Queen", "A Night at the Opera", 354, "Rock")
    };

    // Create a Playlist object
    Playlist playlist("My Favorite Songs");

    // Add songs to the playlist from the array
    for (int i = 0; i < 3; i++) {
        playlist.addSong(songArray[i]);
    }

    // Display the playlist
    playlist.displayPlaylist();

    // Demonstrating the use of this pointer
    Song* currentSong = songArray[0].getCurrentSong();
    Playlist* currentPlaylist = playlist.getCurrentPlaylist();

    std::cout << "\nUsing 'this' pointer:\n";
    std::cout << "Current Song: " << currentSong->getTitle() << "\n";
    std::cout << "Current Playlist: " << currentPlaylist->getCurrentPlaylist() << "\n";

    return 0;
}