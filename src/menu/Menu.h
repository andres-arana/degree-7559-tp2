#ifndef MENU_H_
#define MENU_H_

#include <string>
#include <vector>
#include <map>
#include <iostream>

using std::string;

/*
 * Menú que muestra opciones enumeradas desde la 1 en adelante.
 * Permite desplegar messages de success o failure para cada opción elegida.
 */
class Menu {
private:
	std::vector<string> options;
	std::map<int,string> messages;
	std::map<int,string> subtitles;
	string title;
	string quit;
	int lastOpSelected;  // ultima opción elegida por el usuario

public:
	Menu(string options = "");
	~Menu();

	void setTitle(string title);
	void setQuitOption(string quit);
	void setSuccessMessage(int option, string success);
	void setFailureMessage(int option, string failure);
	void addInterleavedSubtitle(string subtitle, int option=0);

	void addOption(string option);
	void eraseOption(int option);
	void modifyOption(int option, string name);

	/*
	 * Muestra las options por pantalla y espera que el usuario
	 * elija una option correcta.
	 * maxOpAtOnce: permite elegir la cantidad maxima de options a
	 * mostrar al mismo tiempo (=0 muestra todas).
	 */
	int showOptions();
	bool showResultMessage(bool eval, int option=0);
	bool quited();

	int getNumber(string option);
	int getOptionsCount();

	static char getInputChar(bool ignore = true);
	static bool askForConfirmation(string msj);
	static void pressEnterToContinue(string msj);
};

#endif /* MENU_H_ */
