// FavoriteMovies.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

const int ArraySize = 100;
const int READINGERROR = -300;

class FavoriteMovies
{
private:
	int overallcounter;
	string title;
	string genre;
	string favoriteActorwithinMovie;
	string year;
	FavoriteMovies ** movies;
public:
	FavoriteMovies()
	{
		year = "";
		title = "";
		genre = "";
		favoriteActorwithinMovie = "";
	}
	FavoriteMovies(string thetitle, string theyear, string thefavoriteActor, string thegenre) 
	{
		title = thetitle;
		year = theyear;
		favoriteActorwithinMovie = thefavoriteActor;
		genre = thegenre;
	}
	~FavoriteMovies() {  for (int i = 0; i < overallcounter; i++) { delete movies[i]; } }
	

	int saveMovietoFile(ofstream& outfile) { if (outfile.is_open()) { outfile << title << "|" << genre << "|" << year << "|" << favoriteActorwithinMovie << endl; return 0; } else { return -100; } }
	
	void CaptureMovie() {
		cout << "Please input Title -->";
		getline(cin, title);
		cout << "Please input genre of movie?  -->";
		getline(cin, genre);
		cout << "Please input Favorite Actor in movie ";
		getline(cin, favoriteActorwithinMovie);
		cout << "Please input year the movie came out? -->";
		cin >> year;
		cin.ignore();
		cin.clear();
	}

	/*
	string getTitle() { return title; }
	string getYear() { return year; }
	string getFavoriteActor() { return favoriteActorwithinMovie; }
	string getGenre() { return genre; }
	*/
	void displayMovie() { cout << "Title " + title << endl; cout << "Genre " + genre << endl; cout << "Year of Release " + year + "year" << endl; cout << "Favorite Actor in the movie" + favoriteActorwithinMovie << endl; }
};
 class TheList : public FavoriteMovies{
 private:
	 FavoriteMovies ** movies;
	 int sizeofList;
	 int numberofrecords;
	

 public:

	 TheList() :FavoriteMovies() { sizeofList = 0; numberofrecords = 0; }
	
	 void FreeMemory() {
		 for (int i = 0; i < numberofrecords; i++)
		 {
			 delete movies[i];
		 }
		 delete[]movies;
	 }
	 void CaptureMovie() {}
	 void displayMovie() {}
	 int ResizeArray() {

		 FavoriteMovies ** one;
		one = new FavoriteMovies *[sizeofList + ArraySize];
		 sizeofList = sizeofList + ArraySize;
		 for (int i = 0; i < numberofrecords; i++)
		 {
			 one[i] = movies[i];
		 }
		 delete[]movies;
		 movies = one;


		 return 0;
	 }
	 void captureInput() {
		 string answer = "y";
		 cout << "Enter Movie Y/N?" << endl;
		 getline(cin, answer);
		 while (answer == "Y" || answer == "y")
		 {
			 movies[numberofrecords] = new FavoriteMovies();
			 movies[numberofrecords]->CaptureMovie();
			 numberofrecords++;
			 cout << "enter another movie Y/N?" << endl;
			 getline(cin, answer);
		 }
	 }
		 void DisplayListofMovies() {
			 for (int i = 0; i < numberofrecords; i++)
			 {
				 movies[i]->displayMovie();
			 }
		 }
 int saveTheList(string filename) {
	 ofstream output(filename, ios::trunc);
	 if (output)
	 {
		 for (int i = 0; i < numberofrecords; i++)
		 {
			 movies[i]->saveMovietoFile(output);
		 }
		 output.close();

		 return 0;
	 }
	 else
	 {
		 return -200;
	 }
	 //TBD
	 return 0;
 }
 int ReadTheList(string filename) 
 {
	 string atitle, ayear, afavoriteActor, agenre;
	 ifstream infile(filename, ios::in);
	 if (!infile)
	 {
		 cout << "File could not be opened for reading" << endl;
		 return READINGERROR;
	 }


	 while (!infile.eof())
	 {
		 if (numberofrecords == sizeofList)
		 {
			 ResizeArray();
		 }
		 getline(infile, atitle, '|');
		 if (!atitle.empty())
		 {


			 getline(infile, agenre, '|');
			 getline(infile, ayear);
			 getline(infile,afavoriteActor);
			 movies[numberofrecords] = new FavoriteMovies(atitle, ayear, afavoriteActor, agenre);
			 numberofrecords++;
		 }
	 }
	 infile.close();
	 return 0;
 }
 };
	
int main()
{
	string filename = "c:\\users\\mrdar\\desktop\\Example.txt";
	TheList mylist;
	string answer;

	int error = mylist.ReadTheList(filename);
	if (error)
	{
		cout << "Cannot read inventory - continue creating new list? Y/N -->";
		getline(cin, answer);
		if (answer != "Y" && answer != "y")
		{
			return 1;
		}
	}
	mylist.captureInput();
	mylist.saveTheList(filename);
	mylist.DisplayListofMovies();
	mylist.FreeMemory();
	system("PAUSE");
}

