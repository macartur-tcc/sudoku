// $Id: Board.cpp 345 2008-06-07 19:28:19Z wimleers $

#include "PositionElement.h"


class PositionElementImpl
{
public:
  PositionElementImpl(const int x, const int y,const char e);

  int  GetX(void) const;
  int  GetY(void) const;
  char GetE(void) const;
  void SetX(int x);
  void SetY(int y);
  void SetE(char e);

private:
  int m_x;
  int m_y;
  char m_e;
};

int
PositionElementImpl::GetX(void) const
{
  return this->m_x;
}
int
PositionElementImpl::GetY(void) const
{
  return this->m_y;
}
char
PositionElementImpl::GetE(void) const
{
  return this->m_e;
}

void
PositionElementImpl::SetX(int x)
{
  this->m_x = x;
}

void
PositionElementImpl::SetY(int y)
{
  this->m_y = y;
}

void
PositionElementImpl::SetE(char e)
{
  this->m_e = e;
}

PositionElementImpl::PositionElementImpl(const int x,const int y,const char e)
  : m_x(x), m_y(y), m_e(e)
{
}

PositionElement::PositionElement(const int x,const int y,const char e)
 : m_impl(new PositionElementImpl(x,y,e))
{
}

PositionElement::PositionElement(const PositionElement& other)
  : m_impl(new PositionElementImpl(other.GetX(),other.GetY(),other.GetE()))
{
}

int
PositionElement::GetX(void) const
{
 return this->m_impl->GetX();
}

int
PositionElement::GetY(void) const
{
 return this->m_impl->GetY();
}

char
PositionElement::GetE(void) const
{
 return this->m_impl->GetE();
}
