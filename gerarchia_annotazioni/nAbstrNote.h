/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   nAbstrNote.h
 * Author: nick
 *
 * Created on 21 aprile 2016, 14.50
 */

#ifndef NABSTRNOTE_H
#define NABSTRNOTE_H

#include <map>
#include <set>
#include <string>
#include <boost/scoped_ptr.hpp>
//////
#include <list>
class nAbstrNote;
typedef std::list<nAbstrNote*> contenitore;

class nAbstrNote {
public:
    nAbstrNote(nAbstrNote* p =0);
    nAbstrNote(const nAbstrNote& orig);
    virtual ~nAbstrNote();
    
    void addTag(const QString&);
    void delTag(const QString&);
    QStringList listTags() const;
    QStringList listMyOwnTags() const;
    static QStringList listAllTags();

    void setTitle(const QString&);
    QString getTitle() const;
    virtual int numFigli() const;
    //iteratore????
private:
    //tag system
    static boost::scoped_ptr< std::map<std::string,int> > archivioTag_all;
    boost::scoped_ptr< std::set<std::string> > archivioTag_curr;
    
    //composizione (composite pattern, ref Gof)
    nAbstrNote * parent;
    contenitore* figli;
    QString titolo;

};

#endif /* NABSTRNOTE_H */

