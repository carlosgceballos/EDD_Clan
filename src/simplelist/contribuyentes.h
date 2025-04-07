#ifndef CONTRIBUYENTES_H
#define CONTRIBUYENTES_H

#include <iostream>
#include <string>
using namespace std;

template <class T>
class Contribuyentes {
  private:
    T id;
    T id_beneficiario;
    string nombre;
    int edad;
    string contribucion;
    int grad_cont;
  public:
    Contribuyentes();
    Contribuyentes(T, T, string, int, string, int);
    ~Contribuyentes();

    T getId() const;
    T getBeneficiario() const;
    string getName() const;
    int getEdad() const;
    string getContribucion() const;
    int getGrado() const;

    void setId(int);
    void setBeneficiario(int);
    void setNombre(string);
    void setEdad(int);
    void setContribucion(string);
    void setGrado(int);
    void print() const;
};

template <class T>
Contribuyentes<T>::Contribuyentes() : id(T()), id_beneficiario(T()), nombre(""), edad(0), contribucion(""), grad_cont(0) {}

template <class T>
Contribuyentes<T>::Contribuyentes(T id, T id_beneficiario, string nombre, int edad, string contribucion, int grad_cont) {
  this->id = id;
  this->id_beneficiario = id_beneficiario;
  this->nombre = nombre;
  this->edad = edad;
  this->contribucion = contribucion;
  this->grad_cont = grad_cont;
}

template <class T>
Contribuyentes<T>::~Contribuyentes() {
  this->id = T();
  this->id_beneficiario = T();
  this->nombre = "null";
  this->edad = 0;
  this->contribucion = "";
  this->grad_cont = 0;
}

template <class T>
T Contribuyentes<T>::getId() const {
  return this->id;
}

template <class T>
T Contribuyentes<T>::getBeneficiario() const {
  return this->id_beneficiario;
}

template <class T>
string Contribuyentes<T>::getName() const {
  return this->nombre;
}

template <class T>
int Contribuyentes<T>::getEdad() const {
  return this->edad;
}

template <class T>
string Contribuyentes<T>::getContribucion() const {
  return this->contribucion;
}

template <class T>
int Contribuyentes<T>::getGrado() const {
  return this->grad_cont;
}

template <class T>
void Contribuyentes<T>::setId(int id) {
  this->id = id;
}

template <class T>
void Contribuyentes<T>::setBeneficiario(int id_beneficiario) {
  this->id_beneficiario = id_beneficiario;
}

template <class T>
void Contribuyentes<T>::setNombre(string nombre) {
  this->nombre = nombre;
}

template <class T>
void Contribuyentes<T>::setEdad(int edad) {
  this->edad = edad;
}

template <class T>
void Contribuyentes<T>::setContribucion(string contribucion) {
  this->contribucion = contribucion;
}

template <class T>
void Contribuyentes<T>::setGrado(int grado) {
  this->grad_cont = grado;
}

template <class T>
void Contribuyentes<T>::print() const {
    cout << "ID: " << getId()
         << ", Beneficiario: " << getBeneficiario()
         << ", Nombre: " << getName()
         << ", Edad: " << getEdad()
         << ", Contribucion: " << getContribucion()
         << ", Grado: " << getGrado();
}

#endif 


