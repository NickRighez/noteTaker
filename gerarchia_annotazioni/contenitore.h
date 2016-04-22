/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   contenitore.h
 * Author: nick
 *
 * Created on 21 aprile 2016, 16.55
 */

#ifndef CONTENITORE_H
#define CONTENITORE_H

#include <stdexcept>
#include <boost/shared_ptr.hpp>
#include <string>


class nAbstrNote;
class contenitore
{
  typedef boost::shared_ptr<nAbstrNote> pointer;
  friend class iteratore;
 private:
  class nodo
  {
  public:
    nodo(pointer,nodo* n = 0);
    nodo* next;
    pointer dati;
  };
  nodo* first;
  int size;
  static void distruzione_profonda(nodo*);
  static nodo* copia_profonda(nodo*);
  nodo*& raggiungi(const nodo* const n, nodo*& pos/* = first*/);
nodo*& last( nodo*& pos);
 public:
  class iteratore // puntatore a/da contenitore per segnalare l'invalidamento
  {
    friend class contenitore;
  private:
    nodo* puntato;
  public:
    iteratore(nodo* p=0);
    iteratore(const iteratore&); // mettere privato
    ~iteratore();
    iteratore& operator=(const iteratore&); //mettere privato
    bool operator==(const iteratore&) const;
    bool operator!=(const iteratore&) const;
    iteratore& operator++();//prefisso
    iteratore operator++(int); //postfisso
    nAbstrNote& operator*() const;
    nAbstrNote* operator->() const;
    nAbstrNote* get_pointer() const;
    operator bool() const;
  };
  ///////////////////////////////////////
  contenitore();
  ~contenitore();
  contenitore(const contenitore&);
  contenitore& operator=(const contenitore&);

  bool isEmpty() const;
  int getSize() const;
  void insert(nAbstrNote*, iteratore);
  void erase(iteratore);
  iteratore begin() const;
  iteratore end() const;
  void push_back(nAbstrNote*);
  void push_front(nAbstrNote*);
  void pop_back();
  void pop_front();
  bool operator==(const contenitore&)const;
  bool operator!=(const contenitore&)const;
};


#endif /* CONTENITORE_H */

