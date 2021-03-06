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
#ifndef RESULT_H
#define RESULT_H

#include "comparison.h"

#include <QString>
#include <QMap>

struct ResultItem
{
  typedef QList<ResultItem> List;

  QString choice;
  int ranking;
  int comparisonsCount;
  int normalizedRanking;
  int weightedRanking;
};

class Result
{
  public:
    Result( const QString &criterion, Comparison::List & );

    void calculate();

    ResultItem::List items() const;
    ResultItem item( const QString &choice ) const;

    int ranking( const QString &choice );

  protected:
    void createItemList();
    void addResult( const QString &choice, int ranking, int weight = 1 );
    
  private:
    QString m_criterion;
    Comparison::List m_comparisons;
  
    QMap<QString,int> m_rankings;
    QMap<QString,int> m_weightedRankings;
    QMap<QString,int> m_rankingsCounts;

    ResultItem::List m_items;
};

#endif
