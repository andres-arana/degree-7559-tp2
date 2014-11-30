#include "Form.h"
#include "Menu.h"
#include "Utils.h"

using std::cout;
using std::cin;
using std::endl;
using std::getline;

Form::Form(string fieldList) {
	std::vector<string> names;
	Utils::split(fieldList, ",", &names);
	for(unsigned int i=0; i<names.size(); i++) {
		addField(names[i]);
	}
}

Form::~Form() {
	while(!fields.empty()) {
		delete fields.back();
		fields.pop_back();
	}
}

void Form::setAttributes(int field, int min, int max,
		bool isNum, bool consul, int depen) {
	setMinLength(field, min);
	setMaxLength(field, max);
	forceNumericValue(field, isNum);
	setConsultEntry(field, consul);
	setEntryDependency(field, depen);
}

void Form::setMinLength(int field, int min) {
	fields[field]->minlen=min;
}

void Form::setMaxLength(int field, int max) {
	fields[field]->maxlen=max;
}

void Form::forceNumericValue(int field, bool isNum) {
	fields[field]->isNumber=isNum;
}

void Form::setConsultEntry(int field, bool consul) {
	fields[field]->consult=consul;
}

void Form::setEntryDependency(int field, int previousField) {
	fields[field]->dependency=previousField;
}

void Form::setMinLengths(int* minlens) {
	for(unsigned int i=0; i<fields.size(); i++)
		setMinLength(i, minlens[i]);
}

void Form::setMaxLengths(int* maxlens) {
	for(unsigned int i=0; i<fields.size(); i++)
		setMaxLength(i, maxlens[i]);
}

void Form::addField(string fieldName) {
	Field* field = new Field;
	field->name = fieldName;
	field->minlen = DEFAULT_MIN_LEN;
	field->maxlen = DEFAULT_MAX_LEN;
	field->isNumber = false;
	field->consult = false;
	field->dependency = -1;
	fields.push_back(field);
}

void Form::askForData(int field) {
	if(field<0)
		cout << "Please fill the form fields below:" << endl << endl;

	unsigned int i;
	for(i=(field<0)?0:field; i<((field<0)?fields.size():field+1); i++) {
		if(fields[i]->dependency >= 0)
			if(!wasFieldEntered(fields[i]->dependency)) {
				values[i] = "";
				continue;
			}

		if(fields[i]->consult) {
			if(!Menu::askForConfirmation("Do you wish to enter "+(fields[i]->name)+"?")) {
				values[i] = "";
				continue;
			}
		}

		cout << fields[i]->name << ":" << endl;

		string value;
		bool reEnter;
		do {
			value.clear();
			getline(cin, value);
			reEnter = false;
			if(fields[i]->isNumber && !Utils::isANumber(value)) {
				reEnter = true;
				cout << "Numeric value expected, please try again" << endl;
			}
			if(value.length() < fields[i]->minlen || value.length() > fields[i]->maxlen) {
				reEnter = true;
				cout << "Field size is not valid, please try again" << endl;
			}
		} while(reEnter);

		values[i] = value;
	}
}

bool Form::wasFieldEntered(int field) {
	if((unsigned) field <= values.size())
		return !values[field].empty();
	return false;
}

string Form::getValueAsStr(unsigned int field) {
	return values[field];
}

int Form::getValueAsInt(unsigned int field) {
	return Utils::stringToInt(values[field]);
}
