#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Abstract Song class definition (Base class with a pure virtual function)
class Song {
private:
    string title;
    string artist;
    string album;
    int duration; // in seconds
    string genre;
    static int totalSongs;

public:
    // Constructor Overloading: Default, Parameterized, and Copy Constructors
    Song() : title("Unknown"), artist("Unknown"), album("Unknown"), duration(0), genre("Unknown") {
        totalSongs++;
        cout << "Default constructor called: Creating a song with default values.\n";
    }

    Song(string title, string artist, string album, int duration, string genre) {
        this->title = title;
        this->artist = artist;
        this->album = album;
        this->duration = duration;
        this->genre = genre;
        totalSongs++;
        cout << "Parameterized constructor called: Creating a song.\n";
    }

    Song(const Song& other) {
        this->title = other.title;
        this->artist = other.artist;
        this->album = other.album;
        this->duration = other.duration;
        this->genre = other.genre;
        totalSongs++;
        cout << "Copy constructor called: Creating a copy of an existing song.\n";
    }

    // Destructor
    virtual ~Song() {
        totalSongs--;
        cout << "Destructor called: Deleting a song.\n";
    }

    // Getters
    string getTitle() const { return title; }
    string getArtist() const { return artist; }
    string getAlbum() const { return album; }
    int getDuration() const { return duration; }
    string getGenre() const { return genre; }

    // Static methods
    static int getTotalSongs() {
        return totalSongs;
    }

    static void displaySongSummary() {
        cout << "Total number of songs created: " << totalSongs << "\n";
    }

    // Pure virtual function, making Song an abstract class
    virtual void displayInfo() const = 0; // Pure virtual function to be implemented by derived classes
};

// Initialize the static variable
int Song::totalSongs = 0;

// New class to handle displaying song details (SRP)
class SongDisplayer {
public:
    static void display(const Song& song) {
        cout << "Song - Title: " << song.getTitle() << "\n"
             << "Artist: " << song.getArtist() << "\n"
             << "Album: " << song.getAlbum() << "\n"
             << "Duration: " << song.getDuration() << " seconds\n"
             << "Genre: " << song.getGenre() << "\n";
    }
};

// Derived class for Single Inheritance (Concrete class)
class SpecialSong : public Song {
private:
    bool isFavorite;

public:
    // Constructor to initialize both Song and SpecialSong properties
    SpecialSong(string title, string artist, string album, int duration, string genre, bool favorite)
        : Song(title, artist, album, duration, genre), isFavorite(favorite) {
        cout << "SpecialSong constructor called.\n";
    }

    // Override the pure virtual function to display song details
    void displayInfo() const override {
        SongDisplayer::display(*this);
        cout << "Favorite: " << (isFavorite ? "Yes" : "No") << "\n";
    }
};

// Playlist class definition (Base class)
class Playlist {
private:
    string name;
    vector<Song*> songs;
    static int totalPlaylists;

public:
    // Constructor Overloading: Default and Parameterized
    Playlist() : name("Untitled Playlist") {
        totalPlaylists++;
        cout << "Default constructor called: Creating an untitled playlist.\n";
    }

    Playlist(string name) {
        this->name = name;
        totalPlaylists++;
        cout << "Parameterized constructor called: Creating a playlist named " << name << ".\n";
    }

    ~Playlist() {
        for (Song* song : songs) {
            delete song;
        }
        totalPlaylists--;
        cout << "Destructor called: Deleting playlist \"" << name << "\".\n";
    }

    // Function Overloading: addSong() overloaded with two versions
    void addSong(Song* song) {
        songs.push_back(song);
    }

    // Overloaded addSong to take song details and create the Song object internally
    void addSong(string title, string artist, string album, int duration, string genre) {
        Song* newSong = new SpecialSong(title, artist, album, duration, genre, false);
        songs.push_back(newSong);
    }

    // Methods
    string getName() const { return name; }
    void setName(const string& newName) { name = newName; }

    static int getTotalPlaylists() {
        return totalPlaylists;
    }

    void displayPlaylist() const {
        cout << "Playlist: " << name << "\n";
        for (const auto& song : songs) {
            song->displayInfo(); // Polymorphism: Calling overridden displayInfo
            cout << "---------------------------\n";
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
    PremiumPlaylist(string name, bool premium) : Playlist(name), isPremium(premium) {
        cout << "PremiumPlaylist constructor called.\n";
    }

    void displayPremiumStatus() const {
        cout << "Premium Status: " << (isPremium ? "Yes" : "No") << "\n";
    }
};

// Derived class from PremiumPlaylist
class VIPPlaylist : public PremiumPlaylist {
private:
    string exclusiveContent;

public:
    VIPPlaylist(string name, bool premium, string content) 
        : PremiumPlaylist(name, premium), exclusiveContent(content) {
        cout << "VIPPlaylist constructor called.\n";
    }

    void displayVIPInfo() const {
        displayPlaylist();
        displayPremiumStatus();
        cout << "Exclusive Content: " << exclusiveContent << "\n";
    }
};

// Main function
int main() {
    // Demonstrating single inheritance (SpecialSong class with virtual function)
    SpecialSong* specialSong = new SpecialSong("Blinding Lights", "The Weeknd", "After Hours", 200, "Synthwave", true);
    specialSong->displayInfo();

    // Demonstrating function overloading and virtual function (Playlist and Song)
    VIPPlaylist* vipPlaylist = new VIPPlaylist("Exclusive Hits", true, "VIP Concert Footage");

    // Using function overload with Song pointer
    vipPlaylist->addSong(new SpecialSong("Bohemian Rhapsody", "Queen", "A Night at the Opera", 354, "Rock", false));
    
    // Using function overload with song details directly
    vipPlaylist->addSong("Hotel California", "Eagles", "Hotel California", 391, "Rock");
    
    vipPlaylist->displayVIPInfo();

    // Clean up memory
    delete specialSong;
    delete vipPlaylist;

    cout << "\nAfter cleanup:\n";
    Song::displaySongSummary();
    cout << "Total Playlists Remaining: " << Playlist::getTotalPlaylists() << "\n";

    return 0;
}
