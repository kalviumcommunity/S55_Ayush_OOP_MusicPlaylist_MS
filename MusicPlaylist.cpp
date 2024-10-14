#include <iostream>
#include <string>
#include <vector>

// Song class definition
class Song {
private:
    // Private members that should not be accessed directly
    std::string title;
    std::string artist;
    std::string album;
    int duration; // in seconds
    std::string genre;

    // Static variable to keep track of the total number of songs (internal detail)
    static int totalSongs;

public:
    // Constructor (public interface for creating a Song object)
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

    // Accessors (public interface to access private members)
    std::string getTitle() const { return title; }
    std::string getArtist() const { return artist; }
    std::string getAlbum() const { return album; }
    int getDuration() const { return duration; }
    std::string getGenre() const { return genre; }

    // Mutators (public interface to modify private members)
    void setTitle(const std::string& newTitle) { title = newTitle; }
    void setArtist(const std::string& newArtist) { artist = newArtist; }
    void setAlbum(const std::string& newAlbum) { album = newAlbum; }
    void setDuration(int newDuration) { duration = newDuration; }
    void setGenre(const std::string& newGenre) { genre = newGenre; }

    // Static method to get the total number of songs (abstracts the total count)
    static int getTotalSongs() {
        return totalSongs;
    }

    // Static method to display a summary of songs (abstracts song details)
    static void displaySongSummary() {
        std::cout << "Total number of songs created: " << totalSongs << "\n";
    }

    // Public method to display song details
    void displayInfo() const {
        std::cout << "Title: " << title << "\n"
                  << "Artist: " << artist << "\n"
                  << "Album: " << album << "\n"
                  << "Duration: " << duration << " seconds\n"
                  << "Genre: " << genre << "\n";
    }
};

// Initialize the static variable (internal detail, not exposed to users)
int Song::totalSongs = 0;

// Playlist class definition
class Playlist {
private:
    std::string name;           // Private member for playlist name (hidden)
    std::vector<Song*> songs;   // Private vector holding songs (hidden)

    // Static variable to keep track of the total number of playlists (internal detail)
    static int totalPlaylists;

protected:
    // Protected method to display a message (used only internally in derived classes)
    void displayProtectedMessage() const {
        std::cout << "This is a protected message for Playlist.\n";
    }

public:
    // Constructor (public interface for creating a Playlist object)
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

    // Accessor (public interface to access private members)
    std::string getName() const { return name; }

    // Mutator (public interface to modify private members)
    void setName(const std::string& newName) { name = newName; }

    // Public method to add a song to the playlist
    void addSong(Song* song) {
        songs.push_back(song);
    }

    // Static method to get the total number of playlists (abstracts playlist count)
    static int getTotalPlaylists() {
        return totalPlaylists;
    }

    // Public method to display all songs in the playlist
    void displayPlaylist() const {
        std::cout << "Playlist: " << name << "\n";
        for (const auto& song : songs) {
            song->displayInfo();
            std::cout << "---------------------------\n";
        }
    }
};

// Initialize the static variable (internal detail, not exposed to users)
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

    // Demonstrate abstraction with mutator methods (setting values through public interfaces)
    songArray[0]->setTitle("Perfect");
    songArray[1]->setDuration(210);
    playlist->setName("Chill Vibes");

    // Display the updated playlist (abstracting internal details from the user)
    playlist->displayPlaylist();

    // Demonstrating the use of static variables and static member functions
    Song::displaySongSummary();
    std::cout << "Total Playlists Created: " << Playlist::getTotalPlaylists() << "\n";

    // Clean up dynamically allocated memory
    delete playlist;

    // The Playlist destructor will delete each Song in the playlist, so no need to delete songs individually
    std::cout << "\nAfter cleanup:\n";
    Song::displaySongSummary();
    std::cout << "Total Playlists Remaining: " << Playlist::getTotalPlaylists() << "\n";

    return 0;
}
