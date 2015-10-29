// $Id: PositionElement.h 297 2008-05-30 20:16:20Z wimleers $


/**
 * PositionElement Class definition.
 * This class holds a position on the board and an element associated with it.
 *
 * @file PositionElement.h
 * @author Bram Bonne
 */


#ifndef POSITIONELEMENT_H
#define POSITIONELEMENT_H

class PositionElementImpl;
class PositionElement {
public:
    PositionElement(const int x,const  int y, const char e);
    PositionElement(const PositionElement& other);
    int GetX(void) const;
    int GetY(void) const;
    char GetE(void) const;

private:
    PositionElementImpl * m_impl;
};

#endif
