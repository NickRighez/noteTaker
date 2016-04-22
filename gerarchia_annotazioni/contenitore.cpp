/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   contenitore.cpp
 * Author: nick
 * 
 * Created on 21 aprile 2016, 16.55
 */

#include "contenitore.h"

contenitore::nodo::nodo(pointer pt,nodo* n): next(n),  dati(pt)
{}


void contenitore::distruzione_profonda(nodo* n)
{
  if(n)
    {
      distruzione_profonda(n->next);
      delete n;
    }
}

contenitore::nodo*& contenitore::raggiungi(const nodo* const n,nodo*& pos)
{
  if(pos)
    {
      if(n)
        {
          if(pos==n)
            return pos;
          else
            return raggiungi(n,pos->next);
        }
      else
        {
          return raggiungi(n,pos->next);
        }
    }
  else
    return pos;
}


contenitore::nodo* contenitore::copia_profonda(nodo* n)
{
  if(n)
    {
      return new nodo(n->dati,copia_profonda(n->next));
    }
  else
    return 0;
}

contenitore::contenitore(): first(0), size(0)
{}

contenitore::~contenitore()
{
  distruzione_profonda(first);
  first=0;
}

contenitore::contenitore(const contenitore& c)
{
  size=c.size;
  first=copia_profonda(c.first);
}

contenitore& contenitore::operator=(const contenitore& c)
{
  if((*this)==c)
    return *this;
  else
    {
      if(first)
        distruzione_profonda(first);
      first=copia_profonda(c.first);
      size=c.size;
    }
  return *this;
}

bool contenitore::isEmpty() const
{
  return first;
}

int contenitore::getSize() const
{
  return size;
}

void contenitore::insert(nAbstrNote* a, iteratore i)
{
  size++;
  nodo*& aux = raggiungi(i.puntato,first);
  if(aux)
    aux=new nodo(pointer(a),aux);
  else
    aux=new nodo(pointer(a),0);
}

contenitore::nodo*& contenitore::last(nodo*& pos)
{
  if(pos)
    {
      if(pos->next)
	return last(pos->next);
      else
	return pos;
    }
  else
    throw(std::logic_error("invocazione di last su contenitore vuoto"));
}

void contenitore::erase(iteratore i)
{
  size--;
  if(i)
    {
      nodo*& aux = raggiungi(i.puntato,first);
      aux=aux->next;
      delete i.puntato;
    }
  else
    {
      nodo*& aux = last(first);
      delete aux;
      aux=0;
    }
}


contenitore::iteratore contenitore::begin() const
{
  return iteratore(first);
}

contenitore::iteratore contenitore::end() const
{
  return iteratore();
}

void contenitore::push_back(nAbstrNote* a)
{
  insert(a,end());
}

void contenitore::push_front(nAbstrNote* a)
{
  insert(a,begin());
}

void contenitore::pop_back()
{
  erase(end());
}

void contenitore::pop_front()
{
  erase(begin());
}

bool contenitore::operator==(const contenitore& c)const
{
  return size==c.size && first == c.first;
}

bool contenitore::operator!=(const contenitore& c)const
{
  return !(size==c.size && first == c.first);
}



///////////////////////////////////////
////////////ITERATORE//////////////////
///////////////////////////////////////


contenitore::iteratore::iteratore( nodo * p):puntato(p)
{}

contenitore::iteratore::iteratore(const iteratore& it):puntato(it.puntato)
{}

contenitore::iteratore::~iteratore(){}

contenitore::iteratore& contenitore::iteratore::operator=(const iteratore& it)
{
  if(puntato!=it.puntato)
    puntato=it.puntato;
  return *this;
}

bool contenitore::iteratore::operator==(const iteratore& it) const
{
  return puntato == it.puntato;
}

bool contenitore::iteratore::operator!=(const iteratore& it) const
{
  return puntato != it.puntato;
}

contenitore::iteratore& contenitore::iteratore::operator++()//prefisso
{
  if(puntato)
    puntato=puntato->next;
  return *this;
}

contenitore::iteratore contenitore::iteratore::operator++(int) //postfisso
{
  if(puntato)
    puntato=puntato->next;
  return *this;
}

nAbstrNote& contenitore::iteratore::operator*() const
{
  return *(puntato->dati);
}

nAbstrNote* contenitore::iteratore::operator->() const
{
  return puntato->dati.get_pointer();
}

nAbstrNote* contenitore::iteratore::get_pointer() const
{
  return puntato->dati.get_pointer();
}

contenitore::iteratore::operator bool() const
{
  return puntato;
}
