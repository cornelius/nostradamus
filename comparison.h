/*
  This file is part of Nostradamus.

  Copyright (c) 2008 Cornelius Schumacher <schumacher@kde.org>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
  USA.
*/
#ifndef COMPARISON_H
#define COMPARISON_H

#include <QPair>
#include <QList>
#include <QString>
#include <QDateTime>

class Comparison
{
  public:
    typedef QList<Comparison> List;
  
    Comparison();
    
    void setLeft( const QString & );
    QString left() const;

    void setRight( const QString & );
    QString right() const;

    void setRanking( int );
    int ranking() const;

    void setUpdatedAt( const QDateTime & );
    QDateTime updatedAt() const;
    
  private:
    QString m_left;
    QString m_right;
    
    int m_ranking;

    QDateTime m_updatedAt;
};

#endif
