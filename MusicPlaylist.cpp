#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Interface for songs (DIP, LSP)
class ISong {
public:
    virtual ~ISong() = default;
    virtual string getTitle() const = 0;
    virtual void displayInfo() const = 0;
};

// Abstract Song class implementing ISong
class Song : public ISong {
private:
    string title;
    string artist;
    string album;
    int duration; // in seconds
    string genre;
    static int totalSongs;

public:
    Song() : title("Unknown"), artist("Unknown"), album("Unknown"), duration(0), genre("Unknown") {
        totalSongs++;
        cout << "Default constructor called: Creating a song with default values.\n";
    }

    Song(string title, string artist, string album, int duration, string genre)
        : title(title), artist(artist), album(album), duration(duration), genre(genre) {
        totalSongs++;
        cout << "Parameterized constructor called: Creating a song.\n";
    }

    Song(const Song& other) : title(other.title), artist(other.artist), album(other.album), duration(other.duration), genre(other.genre) {
        totalSongs++;
        cout << "Copy constructor called: Creating a copy of an existing song.\n";
    }

    virtual ~Song() {
        totalSongs--;
        cout << "Destructor called: Deleting a song.\n";
    }

    string getTitle() const override { return title; }
    string getArtist() const { return artist; }
    string getAlbum() const { return album; }
    int getDuration() const { return duration; }
    string getGenre() const { return genre; }

    static int getTotalSongs() { return totalSongs; }

    static void displaySongSummary() {
        cout << "Total number of songs created: " << totalSongs << "\n";
    }

    // Virtual function for display
    void displayInfo() const override {
        cout << "Song - Title: " << title << "\n"
             << "Artist: " << artist << "\n"
             << "Album: " << album << "\n"
             << "Duration: " << duration << " seconds\n"
             << "Genre: " << genre << "\n";
    }
};

// Initialize the static variable
int Song::totalSongs = 0;

// FavoriteSongDecorator (LSP: Adds "favorite" functionality without breaking ISong compatibility)
class FavoriteSongDecorator : public ISong {
private:
    ISong* baseSong; // The base song object being decorated
    bool isFavorite;

public:
    FavoriteSongDecorator(ISong* baseSong, bool favorite = false)
        : baseSong(baseSong), isFavorite(favorite) {}

    ~FavoriteSongDecorator() override {
        delete baseSong; // Ensure proper cleanup of the base song
    }

    string getTitle() const override {
        return baseSong->getTitle();
    }

    void displayInfo() const override {
        baseSong->displayInfo();
        cout << "Favorite: " << (isFavorite ? "Yes" : "No") << "\n";
    }
};

// Playlist class depends on ISong interface (DIP, LSP)
class Playlist {
private:
    string name;
    vector<ISong*> songs;
    static int totalPlaylists;

public:
    Playlist() : name("Untitled Playlist") {
        totalPlaylists++;
        cout << "Default constructor called: Creating an untitled playlist.\n";
    }

    Playlist(string name) : name(name) {
        totalPlaylists++;
        cout << "Parameterized constructor called: Creating a playlist named " << name << ".\n";
    }

    ~Playlist() {
        for (ISong* song : songs) {
            delete song; // Clean up dynamically allocated memory
        }
        totalPlaylists--;
        cout << "Destructor called: Deleting playlist \"" << name << "\".\n";
    }

    void addSong(ISong* song) {
        songs.push_back(song);
    }

    void displayPlaylist() const {
        cout << "Playlist: " << name << "\n";
        for (const auto& song : songs) {
            song->displayInfo(); // Polymorphism through ISong interface
            cout << "---------------------------\n";
        }
    }

    static int getTotalPlaylists() { return totalPlaylists; }
};

// Initialize the static variable
int Playlist::totalPlaylists = 0;

// Main function
int main() {
    // Demonstrate LSP with FavoriteSongDecorator
    ISong* song1 = new Song("Blinding Lights", "The Weeknd", "After Hours", 200, "Synthwave");
    ISong* song2 = new Song("Bohemian Rhapsody", "Queen", "A Night at the Opera", 354, "Rock");

    // Wrap song1 with FavoriteSongDecorator
    ISong* favoriteSong = new FavoriteSongDecorator(song1, true);

    // Create a playlist with ISong dependency
    Playlist* playlist = new Playlist("My Favorites");
    playlist->addSong(favoriteSong); // Adding a decorated song
    playlist->addSong(song2);       // Adding a regular song

    playlist->displayPlaylist();

    // Clean up
    delete playlist;

    cout << "\nAfter cleanup:\n";
    Song::displaySongSummary();
    cout << "Total Playlists Remaining: " << Playlist::getTotalPlaylists() << "\n";

    return 0;
}
