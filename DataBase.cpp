#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
using namespace std;

struct Person {
	std::string name;
	std::string surname;
	std::string city;
	bool sex;
	int age;
	int visits;
};

bool sex(std::string tmp) {
	if (tmp == "Male") {
		return true;
	} else {
		return false;
	}
}

std::string xes(bool tmp) {
	if (tmp == true ) {
		return "Male";
	} else {
		return "Female";
	}
}

template<typename T> // Class will be patterned, because we work with different data type. //
class Node { // Making node of list. //
public:
	Node *address;
	T data;

	Node (T data = T(), Node *address = nullptr) {
		this -> data = data;
		this -> address = address;
	}
};


template<typename T>
class List {
public:
    List();
	~List();

	Node <T> *first;
	int size;

	// List size. //
	int get_size() {
		return size;
	}

	// Add the element at the end of the list. //
	void add_element(T data);

	// Search the element by the index. //
	T& find_index(int index);

	// Delete the first element.  //
	void delete_first();

	// Delete all elements. //
	void clear();

	// Add the first element. //
	void add_first(T data);

	// Add the element by the index. //
	void add_index(T data, int index);

	// Delete the element by the index. //
	void delete_index(int index);

	// Delete last element. //
	void delete_last();

};


template <typename T>
List<T>::List() {
	size = 0;
	first = nullptr;
}


template <typename T>
List<T>::~List()
{
	clear();
}


template<typename T>
void List<T>::add_element(T data) {
	if (first == nullptr) {
		first = new Node<T>(data);
	} else {
		Node<T> *element = this -> first;
		while (element -> address != nullptr) {
			element = element -> address;
		}
		element -> address = new Node<T>(data);
	}

	size++;
}


template<typename T>
T & List<T>::find_index(const int index) {
	int counter = 0;
	Node<T> *element = this -> first;

	while (element != nullptr) {
		if (counter == index) {
			return element -> data;
		}
		element = element -> address;
		counter++;
	}

}


template<typename T>
void List<T>::delete_first() {
	Node<T> *element = first;
	first = first -> address;
	delete element;

	size--;
}


template<typename T>
void List<T>::clear() {
	while (size > 0) {
		delete_first();
	}
}


template<typename T>
void List<T>::add_first(T data) {
	first = new Node<T>(data, first);

	size++;
}


template<typename T>
void List<T>::add_index(T data, int index) {
	if (index == 0) {
		add_first(data);
	} else {
		Node<T> *element = this -> first;
		for (int i = 0; i < index - 1; i++) {
			element = element -> address;
		}
		Node<T> *newNode = new Node<T>(data, element -> address);
		element -> address = newNode;

		size++;
	}
}


template<typename T>
void List<T>::delete_index(int index) {
	if (index == 0) {
		delete_first();
	} else {
		Node<T> *element = this -> first;
		for (int i = 0; i < index - 1; i++) {
			element = element -> address;
		}
		Node<T> *deleteNode = element -> address;
		element -> address = deleteNode -> address;

		delete deleteNode;

		size--;
	}

}


template<typename T>
void List<T>::delete_last() {
	delete_index(size - 1);
}

class DataBase { // Making the base of patients. //
public:
	List<Person> patients;

	    // Read the information about patients from the file, and transfer it to the program. //
		void read_file();

		int get_size_P();
		void add_element_P();
		void add_first_P();
		void add_index_P();
		void delete_index_P();
		void delete_first_P();
		void delete_last_P();
		void clear_P();
        void find_index_P(int Id);
};

void DataBase::read_file() {
	std::ifstream file("patients.txt");
	if (file.is_open()) {
		cout << "File is open." << endl;

		std::string line;
		while (getline(file, line)) {
			std::istringstream iss(line);
			Node<Person> person;
			std::string line1;
			int i = 0;

			while (getline(iss, line1, '\t')) {
				switch (i) {
					case 0:
						person.data.name = line1;
                        break;

				    case 1:
					    person.data.surname = line1;
						break;

					case 2:
						person.data.city = line1;
						break;

					case 3:
						person.data.sex = sex(line1);
						break;

					case 4:
						person.data.age = atoi(line1.c_str());
						break;

					case 5:
						person.data.visits = atoi(line1.c_str());
						break;

					default:
						std::cout << "404 not found." << std::endl;
						system("pause");
						break;
					 }

			    patients.add_element(person.data);
							i++;
					}
			}

		} else {
			cout << "Could not open file." << endl;
		}

}


int DataBase::get_size_P() {
	return patients.get_size();
}


void DataBase::add_element_P() {
	Node<Person> person;
	std::string tmp;
	std::cout << "Please, enter the name, surname, city, sex, age, number of visits";
	std::cin >> person.data.name >> person.data.surname >> person.data.city >> tmp >> person.data.age >> person.data.visits;
	person.data.sex = sex(tmp);
	patients.add_element(person.data);
}


void DataBase::add_first_P() {
	Node<Person> person;
	std::string tmp;
	std::cout << "Please, enter the name, surname, city, sex, age, number of visits";
	std::cin >> person.data.name >> person.data.surname >> person.data.city >> tmp >> person.data.age >> person.data.visits;
	person.data.sex = sex(tmp);
	patients.add_first(person.data);
}


void DataBase::add_index_P() {
	int Id = 0;
	Node<Person> person;
	std::string tmp;
	std::cout << "Please, enter the name, surname, city, sex, age, number of visits";
	std::cin >> person.data.name >> person.data.surname >> person.data.city >> tmp >> person.data.age >> person.data.visits >> Id;
	person.data.sex = sex(tmp);
	patients.add_index(person.data, Id);
}


void DataBase::delete_index_P() {
	int Id = 0;
	std::cout << "Enter the Id of patient.";
	std::cin >> Id;
	patients.delete_index(Id);
}


void DataBase::delete_first_P() {
	patients.delete_first();
}


void DataBase::delete_last_P() {
	patients.delete_last();
}


void DataBase::clear_P() {
	patients.clear();
}


void DataBase::find_index_P(int Id) {
	Person& person = patients.find_index(Id);
	std::cout << person.name << " " << person.surname << " " << person.city << " " << xes(person.sex) << " " << person.age << " " << person.visits << " " << std::endl;
}


void connection() {
	DataBase element;
	for (;;) {

		int numeral = 0;
		std::cout << "Press 1 to add patients from the file." << std::endl;
		std::cout << "Press 2 to add a patient to the end of list." << std::endl;
		std::cout << "Press 3 to add a patient at list by the index." << std::endl;
		std::cout << "Press 4 to delete all patients." << std::endl;
		std::cout << "Press 5 to delete last patient." << std::endl;
		std::cout << "Press 6 to delete a patient by the index." << std::endl;
		std::cout << "Press 7 to get info about a patient." << std::endl;
		std::cout << "Press 8 to get the size of list." << std::endl;
		std::cin >> numeral;

		int id = 0;
		switch (numeral) {

		case 1:
			element.read_file();
			system("pause");
			break;

		case 2:
			element.add_element_P();
			system("pause");
			break;

		case 3:
			element.add_index_P();
			system("pause");
			break;

		case 4:
			element.clear_P();
			system("pause");
			break;

		case 5:
			element.delete_last_P();
			system("pause");
			break;

		case 6:
			element.delete_index_P();
			system("pause");
			break;

		case 7:
			std::cout << "Please, enter the Id" << std::endl;
			std::cin >> id;
			element.find_index_P(id);
			system("pause");
			break;

		case 8:
			std::cout << element.get_size_P();
			system("pause");
			break;

		default:
			std::cout << "404 not found." << std::endl;
			system("pause");
			break;

		}

	}

}

int main() {
	connection();
	return 0;
}



