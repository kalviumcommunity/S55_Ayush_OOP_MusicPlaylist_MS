#include <iostream>
#include <string>
#include <vector>

// Song class definition (Base class)
class Song {
private:
    std::string title;
    std::string artist;
    std::string album;
    int duration; // in seconds
    std::string genre;
    static int totalSongs;

public:
    // Constructors
    Song() : title("Unknown"), artist("Unknown"), album("Unknown"), duration(0), genre("Unknown") {
        totalSongs++;
        std::cout << "Default constructor called: Creating a song with default values.\n";
    }
    
    Song(std::string title, std::string artist, std::string album, int duration, std::string genre) {
        this->title = title;
        this->artist = artist;
        this->album = album;
        this->duration = duration;
        this->genre = genre;
        totalSongs++;
        std::cout << "Parameterized constructor called: Creating a song.\n";
    }

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
        totalSongs--;
        std::cout << "Destructor called: Deleting a song.\n";
    }

    // Getters and Setters
    std::string getTitle() const { return title; }
    std::string getArtist() const { return artist; }
    std::string getAlbum() const { return album; }
    int getDuration() const { return duration; }
    std::string getGenre() const { return genre; }

    void setTitle(const std::string& newTitle) { title = newTitle; }
    void setArtist(const std::string& newArtist) { artist = newArtist; }
    void setAlbum(const std::string& newAlbum) { album = newAlbum; }
    void setDuration(int newDuration) { duration = newDuration; }
    void setGenre(const std::string& newGenre) { genre = newGenre; }

    // Static methods
    static int getTotalSongs() {
        return totalSongs;
    }

    static void displaySongSummary() {
        std::cout << "Total number of songs created: " << totalSongs << "\n";
    }

    // Display song info
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

// Derived class for Single Inheritance
class SpecialSong : public Song {
private:
    bool isFavorite;

public:
    // Constructor to initialize both Song and SpecialSong properties
    SpecialSong(std::string title, std::string artist, std::string album, int duration, std::string genre, bool favorite)
        : Song(title, artist, album, duration, genre), isFavorite(favorite) {
        std::cout << "SpecialSong constructor called.\n";
    }

    // Method to display special song details
    void displaySpecialInfo() const {
        displayInfo();
        std::cout << "Favorite: " << (isFavorite ? "Yes" : "No") << "\n";
    }
};

// Playlist class definition (Base class)
class Playlist {
private:
    std::string name;
    std::vector<Song*> songs;
    static int totalPlaylists;

public:
    // Constructors
    Playlist() : name("Untitled Playlist") {
        totalPlaylists++;
        std::cout << "Default constructor called: Creating an untitled playlist.\n";
    }
    
    Playlist(std::string name) {
        this->name = name;
        totalPlaylists++;
        std::cout << "Parameterized constructor called: Creating a playlist named " << name << ".\n";
    }

    ~Playlist() {
        for (Song* song : songs) {
            delete song;
        }
        totalPlaylists--;
        std::cout << "Destructor called: Deleting playlist \"" << name << "\".\n";
    }

    // Methods
    std::string getName() const { return name; }
    void setName(const std::string& newName) { name = newName; }

    void addSong(Song* song) {
        songs.push_back(song);
    }

    static int getTotalPlaylists() {
        return totalPlaylists;
    }

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

// Multilevel Inheritance
class PremiumPlaylist : public Playlist {
private:
    bool isPremium;

public:
    PremiumPlaylist(std::string name, bool premium) : Playlist(name), isPremium(premium) {
        std::cout << "PremiumPlaylist constructor called.\n";
    }

    void displayPremiumStatus() const {
        std::cout << "Premium Status: " << (isPremium ? "Yes" : "No") << "\n";
    }
};

// Derived class from PremiumPlaylist
class VIPPlaylist : public PremiumPlaylist {
private:
    std::string exclusiveContent;

public:
    VIPPlaylist(std::string name, bool premium, std::string content) 
        : PremiumPlaylist(name, premium), exclusiveContent(content) {
        std::cout << "VIPPlaylist constructor called.\n";
    }

    void displayVIPInfo() const {
        displayPlaylist();
        displayPremiumStatus();
        std::cout << "Exclusive Content: " << exclusiveContent << "\n";
    }
};

// Main function
int main() {
    // Demonstrating single inheritance (SpecialSong class)
    SpecialSong* specialSong = new SpecialSong("Blinding Lights", "The Weeknd", "After Hours", 200, "Synthwave", true);
    specialSong->displaySpecialInfo();

    // Demonstrating multilevel inheritance (VIPPlaylist class)
    VIPPlaylist* vipPlaylist = new VIPPlaylist("Exclusive Hits", true, "VIP Concert Footage");
    vipPlaylist->addSong(new Song("Bohemian Rhapsody", "Queen", "A Night at the Opera", 354, "Rock"));
    vipPlaylist->displayVIPInfo();

    // Clean up memory
    delete specialSong;
    delete vipPlaylist;

    std::cout << "\nAfter cleanup:\n";
    Song::displaySongSummary();
    std::cout << "Total Playlists Remaining: " << Playlist::getTotalPlaylists() << "\n";

    return 0;
}
