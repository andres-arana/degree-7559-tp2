#ifndef FORM_H_
#define FORM_H_

#include <string>
#include <vector>
#include <map>
#include <iostream>

#define DEFAULT_MIN_LEN 1
#define DEFAULT_MAX_LEN 500

using std::string;

/*
 * Formulario de entrada de datos que va pidiendo al usuario los campos de a uno.
 * Permite configuraciones en el ingreso para cada Field.
 * Los campos se enumeran desde el 0.
 */
class Form {
private:
	typedef struct {
		string name;
		unsigned int minlen;  // cantidad minima de caracteres/numeros
		unsigned int maxlen;  // cantidad maxima de caracteres/numeros
		bool isNumber;  // fuerza que el valor sea un numero
		bool consult;  // se consulta al usuario si desea ingresarlo
		int dependency;  // solo se lo muestra si se ingresó otro Field antes
	} Field;

	std::vector<Field*> fields;
	std::map<int, string> values;

public:
	Form(string fieldList = "");
	~Form();

	void setAttributes(int field, int min, int max,
		bool isNum=false, bool consul=false, int depen=-1);
	void setMinLength(int field, int min);
	void setMaxLength(int field, int max);
	void forceNumericValue(int field, bool isNum);
	void setConsultEntry(int field, bool consult);
	void setEntryDependency(int field, int previousField);

	void setMinLengths(int* minlens);
	void setMaxLengths(int* maxlens);

	void addField(string fieldName);

	/*
	 * Muestra de a uno los campos por pantalla y valida los ingresos.
	 * Se puede pedir que se ingrese un campo específico.
	 */
	void askForData(int field=-1);

	bool wasFieldEntered(int field);

	string getValueAsStr(unsigned int field);
	int getValueAsInt(unsigned int field);
};

#endif /* FORM_H_ */
