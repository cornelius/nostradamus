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

#include "comparison.h"

Comparison::Comparison()
{
}

void Comparison::setLeft( const QString &left )
{
  m_left = left;
}

QString Comparison::left() const
{
  return m_left;
}

void Comparison::setRight( const QString &right )
{
  m_right = right;
}

QString Comparison::right() const
{
  return m_right;
}

void Comparison::setRanking( int ranking )
{
  m_ranking = ranking;
}

int Comparison::ranking() const
{
  return m_ranking;
}

void Comparison::setUpdatedAt( const QDateTime &dt )
{
  m_updatedAt = dt;
}

QDateTime Comparison::updatedAt() const
{
  return m_updatedAt;
}
