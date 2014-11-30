#include "util/app.h"
#include "raii/signal.h"

#include <iostream>
#include "menu/Menu.h"
#include "menu/Form.h"

using namespace std;

class client : public util::app {
  public:
    explicit client() :
      app("CLIENT") {}

  protected:
    virtual void do_run() override {
		Menu mainMenu;
		mainMenu.setTitle("Main menu");
		mainMenu.addOption("Register person");
		mainMenu.addOption("Consult address");
		mainMenu.addOption("Consult telephone number");
		mainMenu.setQuitOption("Quit");

		mainMenu.setSuccessMessage(1, "A new person has been successfully registered!");
		mainMenu.setSuccessMessage(2, "The corresponding address is:");
		mainMenu.setSuccessMessage(3, "The corresponding telephone number is:");
		mainMenu.setFailureMessage(1, "Error: could not register new person");
		mainMenu.setFailureMessage(2, "Error: could not match any address with the specified name");
		mainMenu.setFailureMessage(3, "Error: could not match any telephone number with the specified name");

		Form registration;
		registration.addField("Name");
		registration.addField("Address");
		registration.addField("Telephone number");

		Form nameForm;
		nameForm.addField("Name");

		int choice = 0;
		while(!mainMenu.quited()) {
			choice = mainMenu.showOptions();

			switch(choice) {
				case 1: {
					registration.askForData();
					string name = registration.getValueAsStr(0);
					string addr = registration.getValueAsStr(1);
					string tel = registration.getValueAsStr(2);

					bool result = registerPerson(name, addr, tel);

					mainMenu.showResultMessage(result);
					break;
				}
				case 2: {
					nameForm.askForData();
					string name = registration.getValueAsStr(0);

					string addr = consultAddress(name);

					if(mainMenu.showResultMessage(addr.length() > 0))
						cout << addr << endl;
					break;
				}
				case 3: {
					nameForm.askForData();
					string name = registration.getValueAsStr(0);

					string tel = consultTelephoneNumb(name);

					if(mainMenu.showResultMessage(tel.length() > 0))
						cout << tel << endl;
					break;
				}
			}
		}
    }

  private:
    bool registerPerson(string name, string addr, string tel) {

    	return true;
    }

    string consultAddress(string name) {

    	return "Riobamba 1234";
    }

    string consultTelephoneNumb(string name) {

    	return "1234-5678";
    }
};

DEFINE_MAIN(client);

