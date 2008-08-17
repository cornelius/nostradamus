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

#include "result.h"

#include <QtCore>

Result::Result( const QString &criterion, Comparison::List &comparisons )
  : m_criterion( criterion ), m_comparisons( comparisons )
{
}

void Result::calculate()
{
  m_rankings.clear();
  m_rankingsCounts.clear();

  Result metaResult( "", m_comparisons );
  foreach( Comparison c, m_comparisons ) {
    if ( c.meta() ) {
      metaResult.addResult( c.left(), -c.ranking() );
      metaResult.addResult( c.right(), c.ranking() );
    }
  }
  metaResult.createItemList();
  
  qDebug() << "META RESULT";
  foreach( ResultItem item, metaResult.items() ) {
    qDebug() << item.choice << item.ranking;
  }

  qDebug() << "RESULT";
  foreach( Comparison c, m_comparisons ) {
    if ( !c.meta() ) {
      ResultItem i = metaResult.item( c.criterion() );
      qDebug() << "  " << i.choice << i.ranking <<
        i.normalizedRanking << i.comparisonsCount;
      int weight = i.normalizedRanking + Comparison::maxRanking();
      addResult( c.left(), -c.ranking(), weight );
      addResult( c.right(), c.ranking(), weight );
    }
  }

  createItemList();
}

void Result::addResult( const QString &choice, int ranking, int weight )
{
  int count = 0;

  QMap<QString,int>::Iterator it;

  int weightedRanking = ranking * weight;

  it = m_rankings.find( choice );
  if ( it != m_rankings.end() ) {
    ranking += it.value();
    count = m_rankingsCounts.value( choice );
  }

  it = m_weightedRankings.find( choice );
  if ( it != m_weightedRankings.end() ) {
    weightedRanking = it.value() + ranking * weight;
  }

  m_rankings.insert( choice, ranking );
  m_weightedRankings.insert( choice, weightedRanking );
  m_rankingsCounts.insert( choice, ++count );
}

void Result::createItemList()
{
  m_items.clear();

  QList<QString> choices = m_rankings.keys();

  foreach( QString choice, choices ) {
    ResultItem item;
  
    item.choice = choice;
    item.comparisonsCount = m_rankingsCounts.value( choice );
    item.ranking = m_rankings.value( choice );
    item.normalizedRanking = item.ranking / item.comparisonsCount;
    item.weightedRanking = m_weightedRankings.value( choice );

    m_items.append( item );
  }
}

ResultItem::List Result::items() const
{
  return m_items;
}

ResultItem Result::item( const QString &choice ) const
{
  foreach( ResultItem item, m_items ) {
    if ( item.choice == choice ) return item;
  }
  Q_ASSERT( false );
  return ResultItem();
}
