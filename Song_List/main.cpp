#include <iostream>
#include <fstream>
using namespace std;

const int MAX_SONGS = 200;
const int UNKNOWN_YEAR = -1;

const int MAX_TITLE = 100;
const int MAX_AUTHOR = 100;
const int MAX_LYRICS = 5000;

struct Song {
	char title[MAX_TITLE];
	char author[MAX_AUTHOR];
	int year;
	char lyrics[MAX_LYRICS];
};

Song songs[MAX_SONGS];
int song_count = 0;

void safe_input(char* buf, int size)
{
	cin.getline(buf, size);
}

int find_song_index(const char* title, const char* author)
{
	for (int i = 0; i < song_count; i++)
		if (strcmp(songs[i].title, title) == 0 && strcmp(songs[i].author, author) == 0)
			return i;
	return -1;
}

void read_lyrics(char* buffer)
{
	cout << "Enter song text. End with a single '.' on a line" << endl;
	buffer[0] = '\0';
	char line[300];
	while (true)
	{
		safe_input(line, 300);
		if (strcmp(line, ".") == 0) break;
		if (strlen(buffer) + strlen(line) + 2 < MAX_LYRICS)
		{
			strcat(buffer, line);
			strcat(buffer, "\n");
		}
	}
}

void add_song_keyboard()
{
	if (song_count >= MAX_SONGS) { cout << "Catalog is full." << endl; return; }


	Song s;
	cout << "Enter title: "; safe_input(s.title, MAX_TITLE);
	cout << "Enter author: "; safe_input(s.author, MAX_AUTHOR);
	cout << "Enter year (0 if unknown): ";
	char y[20]; 
	safe_input(y, 20);
	int yi = atoi(y);
	s.year = (yi == 0 ? UNKNOWN_YEAR : yi);

	read_lyrics(s.lyrics);

	if (find_song_index(s.title, s.author) != -1) { cout << "Song exists already." << endl; return; }

	songs[song_count++] = s;
	cout << "Added song (keyboard)." << endl;
}

void add_song_file()
{
	if (song_count >= MAX_SONGS) { cout << "Catalog is full." << endl; return; }


	Song s;
	cout << "Enter title: "; safe_input(s.title, MAX_TITLE);
	cout << "Enter author: "; safe_input(s.author, MAX_AUTHOR);
	cout << "Enter year (0 if unknown): ";
	char y[20]; 
	safe_input(y, 20);
	int yi = atoi(y);
	s.year = (yi == 0 ? UNKNOWN_YEAR : yi);


	cout << "Enter filename: ";
	char fname[200]; safe_input(fname, 200);
	ifstream in(fname);
	if (!in) { cout << "File open error." << endl; return; }


	char temp[MAX_LYRICS];
	temp[0] = '\0';
	char line[300];
	while (in.getline(line, 300))
	{
		if (strlen(temp) + strlen(line) + 2 < MAX_LYRICS)
		{
			strcat(temp, line);
			strcat(temp, "\n");
		}
	}
	strcpy(s.lyrics, temp);


	if (find_song_index(s.title, s.author) != -1) { cout << "Song exists already." << endl; return; }


	songs[song_count++] = s;
	cout << "Added song (file)." << endl;
}

void delete_song()
{
	char title[MAX_TITLE], author[MAX_AUTHOR];
	cout << "Enter title: "; safe_input(title, MAX_TITLE);
	cout << "Enter author: "; safe_input(author, MAX_AUTHOR);


	int idx = find_song_index(title, author);
	if (idx == -1) { cout << "Not found." << endl; return; }


	for (int i = idx; i < song_count - 1; i++) songs[i] = songs[i + 1];
	song_count--;
	cout << "Deleted song." << endl;
}

void edit_song()
{
	char title[MAX_TITLE], author[MAX_AUTHOR];
	cout << "Enter title: "; safe_input(title, MAX_TITLE);
	cout << "Enter author: "; safe_input(author, MAX_AUTHOR);


	int idx = find_song_index(title, author);
	if (idx == -1) { cout << "Not found." << endl; return; }


	Song& s = songs[idx];


	char buf[MAX_TITLE];
	cout << "New title (leave empty to keep current): "; safe_input(buf, MAX_TITLE);
	if (strlen(buf) > 0) strcpy(s.title, buf);


	cout << "New author (leave empty to keep current): "; safe_input(buf, MAX_AUTHOR);
	if (strlen(buf) > 0) strcpy(s.author, buf);


	cout << "New year (0=unknown): "; char y[20]; safe_input(y, 20);
	if (strlen(y) > 0) { int yi = atoi(y); s.year = (yi == 0 ? UNKNOWN_YEAR : yi); }


	cout << "Edit lyrics (y/n): "; char c[5]; safe_input(c, 5);
	if (c[0] == 'y' || c[0] == 'Y') read_lyrics(s.lyrics);


	cout << "Edited song." << endl;
}

void display_song()
{
	char title[MAX_TITLE], author[MAX_AUTHOR];
	cout << "Enter title: "; 
	safe_input(title, MAX_TITLE);
	cout << "Enter author: "; 
	safe_input(author, MAX_AUTHOR);

	int idx = find_song_index(title, author);
	if (idx == -1) { cout << "Not found." << endl; return; }

	Song& s = songs[idx];
	cout << "---\nTitle: " << s.title << "\nAuthor: " << s.author << "\nYear: ";
	if (s.year == UNKNOWN_YEAR) cout << "unknown";
	else cout << s.year;
	cout << "\n---\n" << s.lyrics << "\n---" << endl;
}

void save_song_file()
{
	char title[MAX_TITLE], author[MAX_AUTHOR];
	cout << "Enter title: "; 
	safe_input(title, MAX_TITLE);
	cout << "Enter author: "; 
	safe_input(author, MAX_AUTHOR);

	int idx = find_song_index(title, author);
	if (idx == -1) { cout << "Not found." << endl; return; }

	cout << "Filename: "; char fname[200]; safe_input(fname, 200);
	ofstream out(fname);
	if (!out) { cout << "Write error." << endl; return; }

	Song& s = songs[idx];
	out << s.title << "\n" << s.author << "\n";
	if (s.year == UNKNOWN_YEAR) out << "unknown\n";
	else out << s.year << "\n";
	out << s.lyrics;

	cout << "Saved to file." << endl;
}

int main()
{

}