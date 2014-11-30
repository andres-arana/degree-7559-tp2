#include <limits>
#include "Menu.h"
#include "Utils.h"

using std::cout;
using std::cin;
using std::endl;

Menu::Menu(string options) {
	if(!options.empty())
		Utils::split(options, ",", &(this->options));
	lastOpSelected = 0;
	title.clear();
	quit.clear();
}

Menu::~Menu() {
}

void Menu::setTitle(string title) {
	this->title=title;
}

void Menu::setQuitOption(string quit) {
	this->quit=quit;
}

void Menu::setSuccessMessage(int option, string success) {
	messages[(option-1)*2] = success;
}

void Menu::setFailureMessage(int option, string failure) {
	messages[(option-1)*2+1] = failure;
}

void Menu::addInterleavedSubtitle(string subtitle, int option) {
	if(option)
		subtitles[option-1] = subtitle;
	else
		subtitles[getOptionsCount()] = subtitle;
}

void Menu::addOption(string option) {
	options.push_back(option);
}

void Menu::eraseOption(int option) {
	options.erase(options.begin()+option-1);
}

void Menu::modifyOption(int option, string name) {
	options[option-1]=name;
}

int Menu::showOptions() {
	if(!options.empty()) {
		if(lastOpSelected == 0)
			system("clear");

		if(!title.empty())
			cout << endl << "- "+title+" -" << endl << endl;

		for(unsigned int i=0; i<options.size(); i++) {
			if(!subtitles[i].empty())
				cout << subtitles[i] << endl;
			cout << i+1 << ") "+options[i] << endl;
		}

		if(!quit.empty())
			cout << options.size()+1 << ") "+quit << endl;

		string choice;
		while(1) {
			choice.clear();
			getline(cin, choice);
			if(Utils::isANumber(choice)) {
				unsigned int chosen = Utils::stringToInt(choice);
				bool rightOp = chosen > 0 && chosen <= options.size();
				bool quitOp = chosen == options.size()+1 && !quit.empty();
				if(rightOp || quitOp) {
					system("clear");
					break;
				}
			}
			cout << "The chosen option does not exist, please try again" << endl;
		}

		lastOpSelected = Utils::stringToInt(choice);
		return lastOpSelected;
	}
	return 0;
}

bool Menu::quited() {
	return lastOpSelected > (int) options.size();
}

bool Menu::showResultMessage(bool eval, int op) {
	int option = op?op:lastOpSelected;
	if(eval)
		cout << messages[(option-1)*2] << endl;
	else
		cout << messages[(option-1)*2+1] << endl;
	return eval;
}

int Menu::getNumber(string option) {
	for(unsigned int i=0; i<options.size(); i++)
		if(options[i] == option)
			return i+1;
	return 0;
}

int Menu::getOptionsCount() {
	return options.size();
}

char Menu::getInputChar(bool ignore) {
	char input = cin.get();
	if(ignore)  // toma el primer char ingresado e ignora el resto
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return input;
}

bool Menu::askForConfirmation(string msj) {
	char choice = 0;
	cout << msj << " (y/n)" << endl;
	while(choice != 'y' && choice != 'n') {
		choice = getInputChar();
	}
	return choice == 'y';
}

void Menu::pressEnterToContinue(string msj) {
	cout << msj << endl;
	while(getInputChar(false) != '\n');
}
