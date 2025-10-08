#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<algorithm>
using namespace std;

void displayLargeQuote(const string& quote) {
	cout << "\n============================================\n";
	cout << "		" << quote << "\n";
	cout << "==============================================\n";
}

void showQuotes(const vector<string>& quotes) {
	vector<string> selected = quotes;
	random_shuffle(selected.begin(), selected.end());
	
	for(int i = 0; i < 3; ++i) {
		displayLargeQuote(selected[i]);
	}
}

int main() {
	srand(static_cast<unsigned int>(time(0)));
	
	vector<string> moods = {"Happy", "Sad", "Angry", "Stressed", "Inspired"};
	vector<vector<string>> moodQuotes(5);
	
	moodQuotes[0] = {
		"Smile, it\'s a beautiful day!",
		"Happiness is contagious.",
		"Enjoy the little things.",
		"Laughter is the best medicine.",
		"Life is good",
		"Spread joy everywhere you go.",
		"Let your smile change the world.",
		"Be happy for this moment.",
		"Sunshine is free, enjoy it.",
		"A good mood is a good day.",
		"Choose joy.",
		"Good vibes only.",
		"Happiness starts with you.",
		"Enjoy today!",
		"Positive mind, positive life.",
		"Let happiness in.",
		"Keep shining.",
		"Dance like nobody's watching.",
		"You radiate positivity.",
		"Stay golden!"
	};
	
	moodQuotes[1] = {
		"It\'s okay to not be okay.",
		"This too shall pass.",
		"Feel what you need to feel.",
		"Sadness is part of life.",
		"You\'re not alone.",
		"Let it out.",
		"Tears are healing.",
		"Courage is in facing the pain.",
		"Rest, and try again tomorrow.",
		"Even the darkest night ends.",
		"Be kind to yourself.",
		"Your feelings matter.",
		"Healing takes time.",
		"Pain is temporary.",
		"You\'re stronger than you think.",
		"Hold on, better days are coming.",
		"Keep breathing.",
		"Rain brings growth.",
		"You are loved.",
		"Stay gentle with yourself."
	};
	
	moodQuotes[2] = {
		"Anger is valid. Channel it.",
		"Take a breath before you act.",
		"You are in control.",
		"Let it go, for your peace.",
		"Anger is a signal, not a master.",
		"Pause, then respond.",
		"Dont\'t let it consume you.",
		"Even storms run out of rain.",
		"Redirect your fire.",
		"It's okay to feel this.",
		"Stay grounded.",
		"Speak, don\'t shout.",
		"Let your words build, not break.",
		"Control the flame.",
		"Take a walk. Breathe.",
		"Respond with wisdom.",
		"Cool head, calm heart.",
		"Master the moment.",
		"Turn rage into resolve.",
		"Your peace is worth it."
	};
	
	moodQuotes[3] = {
		"Breathe in, breathe out.",
		"You are enough.",
		"Take things one step at a time.",
		"Stress is temporary.",
		"Pause and reset.",
		"It\'s okay to slow down.",
		"Let go of what you can't control.",
		"Your mind needs rest too.",
		"Don\'t overthink.",
		"Relax. You\'ve got this.",
		"Focus on what matters.",
		"Peace begins with you.",
		"Small steps are progress.",
		"This feeling will pass.",
		"Be still.",
		"Clear your mind.",
		"You are doing your best.",
		"Calm is power.",
		"Rest is productive.",
		"Your well-being matters."
	};
	
	moodQuotes[4] = {
		"You can do anything.",
		"Believe in yourself.",
		"Stay strong and keep going.",
		"Your journey is yours.",
		"Dream big, act bigger.",
		"Push forward.",
		"Greatness takes time.",
		"Fuel your fire.",
		"You are capable.",
		"Today is a new start.",
		"Turn vision into action.",
		"Every step counts.",
		"Keep climbing.",
		"Don\'t stop now.",
		"Inspire others by being you.",
		"You\'ve got the power.",
		"Be fearless.",
		"Your potential is endless.",
		"Never settle.",
		"Rise and shine!"
	};
	
	int choice;
	char input;
	
	do {
		system("cls");
		cout << "How are you feeling today?\n";
		for(int i = 0; i < moods.size(); ++i) {
			cout << i + 1 << ". " << moods[i] << "\n";
		}
		
		cout << "Enter the number of your mood: ";
		cin >> choice;
		
		if(choice >= 1 && choice <= 5) {
			cout << "\nHere are 3 quotes for when you're feeling" << moods[choice - 1] << ":\n";
			showQuotes(moodQuotes[choice - 1]);
		} else {
			cout << "Invalid choice. Please run the program again.\n";
		}
		cout << "Do you want more? (Y/N): ";
		cin >> input;
	}while(input == 'y' || input == 'Y');
	
	return 0;
}