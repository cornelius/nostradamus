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

Result::Result( const QString &criterion, Comparison::List &comparisons )
  : m_criterion( criterion ), m_comparisons( comparisons )
{
}

void Result::calculate()
{
  m_results.clear();
  m_resultCounts.clear();

  foreach( Comparison c, m_comparisons ) {
    if ( !c.meta() ) {
      addResult( c.left(), -c.ranking() );
      addResult( c.right(), c.ranking() );
    }
  }

  createItemList();
}

void Result::addResult( const QString &choice, int ranking )
{
  int count = 0;

  QMap<QString,int>::Iterator it;
  it = m_results.find( choice );
  if ( it != m_results.end() ) {
    ranking += it.value();
    count = m_resultCounts.value( choice );
  }
  m_results.insert( choice, ranking );
  m_resultCounts.insert( choice, ++count );
}

void Result::createItemList()
{
  m_items.clear();

  QList<QString> choices = m_results.keys();

  foreach( QString choice, choices ) {
    ResultItem item;
  
    item.choice = choice;
    item.count = m_resultCounts.value( choice );
    item.result = m_results.value( choice );
    item.weightedResult = item.result / item.count;

    m_items.append( item );
  }
}

ResultItem::List Result::items() const
{
  return m_items;
} 
