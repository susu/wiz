#ifndef FLYERZ_H
#define FLYERZ_H

#include "drawinterface.hpp"

class Wiz;

class Flyer
{
  public:
    Flyer(int team, Wiz& frame): m_frame(frame),  m_team(team)
    {}
    virtual void Draw() = 0;
    virtual void Move() = 0;
    virtual ~Flyer()
    {}

    int GetTeam() const
    {
      return m_team;
    }

  protected:
    Wiz& m_frame;

  private:
    const int m_team;
};

class DiskShip: public Flyer
{
  public:
    static int shipSize;
    static int bulletLimit;
    static int cooldownInterval;

    DiskShip(Coordinate center, Color color, Wiz& frame, int team = 0): Flyer(team, frame), m_center(center), m_color(color), m_speed(2, 3), m_bulletNum(0), m_ticker(0)
    {}
    virtual void Draw();
    virtual void Move();

  private:
    void Shoot();

    Coordinate  m_center;
    Color       m_color;
    Coordinate  m_speed;

    int         m_bulletNum;
    int         m_ticker;
};

class PulseLaser: public Flyer
{
  public:
    static int pulseLaserSpeed;
    PulseLaser(Coordinate begin, Coordinate end, Color color, Wiz& frame, int team = 0): Flyer(team, frame), m_front(begin), m_back(end), m_speed((m_front - m_back)), m_color(color)
    {
      m_speed = (m_speed * pulseLaserSpeed) / Length(m_speed);
    }
    virtual void Draw();
    virtual void Move();

  private:
    Coordinate  m_front;
    Coordinate  m_back;
    Coordinate  m_speed;
    Color       m_color;
};


#endif // FLYERZ_H