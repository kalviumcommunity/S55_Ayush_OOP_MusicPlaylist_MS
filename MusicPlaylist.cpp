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
    // Constructor
    Song(std::string title, std::string artist, std::string album, int duration, std::string genre) {
        this->title = title;
        this->artist = artist;
        this->album = album;
        this->duration = duration;
        this->genre = genre;
        totalSongs++; // Increment totalSongs whenever a new Song is created
    }

    // Destructor
    ~Song() {
        totalSongs--; // Decrement totalSongs when a Song is destroyed
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

    // Static method to get the total number of songs
    static int getTotalSongs() {
        return totalSongs;
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
    // Constructor
    Playlist(std::string name) {
        this->name = name;
        totalPlaylists++; // Increment totalPlaylists whenever a new Playlist is created
    }

    // Destructor to clean up dynamically allocated songs
    ~Playlist() {
        for (Song* song : songs) {
            delete song; // Free each Song object
        }
        totalPlaylists--; // Decrement totalPlaylists when a Playlist is destroyed
    }

    // Add a song to the playlist
    void addSong(Song* song) {
        songs.push_back(song);
    }

    // Method that returns the current object
    Playlist* getCurrentPlaylist() {
        return this; // Returning the pointer to the current object
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
    // Create an array of Song pointers, dynamically allocated
    Song* songArray[3];
    songArray[0] = new Song("Shape of You", "Ed Sheeran", "Divide", 233, "Pop");
    songArray[1] = new Song("Blinding Lights", "The Weeknd", "After Hours", 200, "Synthwave");
    songArray[2] = new Song("Bohemian Rhapsody", "Queen", "A Night at the Opera", 354, "Rock");

    // Create a Playlist object dynamically
    Playlist* playlist = new Playlist("My Favorite Songs");

    // Add songs to the playlist from the array
    for (int i = 0; i < 3; i++) {
        playlist->addSong(songArray[i]);
    }

    // Display the playlist
    playlist->displayPlaylist();

    // Demonstrating the use of static variables and the this pointer
    std::cout << "\nTotal Songs Created: " << Song::getTotalSongs() << "\n";
    std::cout << "Total Playlists Created: " << Playlist::getTotalPlaylists() << "\n";

    // Clean up dynamically allocated memory
    delete playlist;

    // The Playlist destructor will delete each Song in the playlist, so no need to delete songs individually
    std::cout << "\nAfter cleanup:\n";
    std::cout << "Total Songs Remaining: " << Song::getTotalSongs() << "\n";
    std::cout << "Total Playlists Remaining: " << Playlist::getTotalPlaylists() << "\n";

    return 0;
}
