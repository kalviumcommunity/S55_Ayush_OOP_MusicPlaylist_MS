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
    Song(std::string t, std::string a, std::string al, int d, std::string g)
        : title(t), artist(a), album(al), duration(d), genre(g) {}

    // Getter methods
    std::string getTitle() const { return title; }
    std::string getArtist() const { return artist; }
    std::string getAlbum() const { return album; }
    int getDuration() const { return duration; }
    std::string getGenre() const { return genre; }

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
    Playlist(std::string n) : name(n) {}

    // Add a song to the playlist
    void addSong(const Song& song) {
        songs.push_back(song);
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
    // Create Song objects
    Song song1("Shape of You", "Ed Sheeran", "Divide", 233, "Pop");
    Song song2("Blinding Lights", "The Weeknd", "After Hours", 200, "Synthwave");

    // Create a Playlist object
    Playlist playlist("My Favorite Songs");

    // Add songs to the playlist
    playlist.addSong(song1);
    playlist.addSong(song2);

    // Display the playlist
    playlist.displayPlaylist();

    return 0;
}
