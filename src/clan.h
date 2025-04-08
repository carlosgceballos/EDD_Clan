#include "node.h"
#include <string>
#include <iostream>

template<class T>
class Clan{
  private:
  T Id;
  string Name;
  string last_Name;
  char gender;
  int age;
  T Id_Father;
  bool is_dead;
  bool was_chief;
  bool is_chief;
  
  public:
  Clan();
  Clan(T, string, string, char, int, T, bool, bool, bool);
  ~Clan();
  T getID();
  string getName();
  string getLastName();
  char getGender();
  int getAge();
  T getId_Father();
  bool getAlive();
  bool getStory();
  bool getRol();
  void setId(T);
  void setID_Fath(T);
  void setName(string);
  void setLastName(string);
  void setGender(char);
  void setAge(int);
  void setIsDead(bool);
  void setWasChief(bool);
  void setIsChief(bool);
  void print();
  

};

using namespace std;

template<class T> 
Clan<T>::Clan():Id(T()), Name(""), last_Name(""), gender('\0'), age(0), Id_Father(T()), is_dead(false), was_chief(false), is_chief(false){

}

template<class T>
Clan<T>::Clan(T Id, string Name, string last_Name, char gender, int age, T Id_Father, bool is_dead, bool was_chief, bool is_chief){
  this->Id=Id;
  this->Name=Name;
  this->last_Name=last_Name;
  this->gender=gender;
  this->age=age;
  this->Id_Father=Id_Father;
  this->is_dead=is_dead;
  this->was_chief=was_chief;
  this->is_chief=is_chief;
}

template<class T>
Clan<T>::~Clan(){
  this->Id="";
  this->Name="null";
  this->last_Name="null";
  this->gender='n';
  this->age=0;
  this->Id_Father="";
  this->is_dead=0;
  this->was_chief=0;
  this->is_chief=0;
}

template<class T>
T Clan<T>::getID(){
  return this->Id;
}

template<class T>
T Clan<T>::getId_Father(){
  return this->Id_Father;
}

template <class T>
string Clan<T>::getName(){
  return this->Name;
}

template <class T>
string Clan<T>::getLastName(){
  return this->last_Name;
}

template <class T>
char Clan<T>::getGender(){
  return this->gender;
}

template <class T>
int Clan<T>::getAge(){
  return this->age;
}

template <class T>
bool Clan<T>::getAlive(){
  return this->is_dead;
}

template <class T>
bool Clan<T>::getStory(){
  return this->was_chief;
}

template <class T>
bool Clan<T>::getRol(){
  return this->is_chief;
}

template<class T>
void Clan<T>::setId(T id){
  this->Id=id;
}

template<class T>
void Clan<T>::setID_Fath(T Id_Fath){
  this->Id_Father=Id_Fath;
}

template <class T>
void Clan<T>::setName(string name){
  this->Name=name;
}

template <class T>
void Clan<T>::setLastName(string last_name){
  this->last_Name=last_name;
}

template <class T>
void Clan<T>::setGender(char gender){
  this->gender=gender;
}

template <class T>
void Clan<T>::setAge(int age){
  this->age=age;
}

template <class T>
void Clan<T>::setIsDead(bool is_dead){
  this->is_dead=is_dead;
}

template <class T>
void Clan<T>::setWasChief(bool was_chief){
  this->was_chief=was_chief;
}

template <class T>
void Clan<T>::setIsChief(bool is_chief){
  this->is_chief=is_chief;
}

template<class T>
void Clan<T>::print(){
cout << "ID: " << Id << endl;
cout << "Nombre: " << Name<< endl;
cout << "Apellido: " << last_Name<< endl;
cout << "Genero: " << gender << endl;
cout << "Edad: " << age << endl;
cout << "ID del Padre: " << Id_Father << endl;
cout << "Esta muerto: " << is_dead << endl;
cout << "Fue jefe: " << was_chief << endl;
cout << "Es jefe: " << is_chief << endl<<endl;
}