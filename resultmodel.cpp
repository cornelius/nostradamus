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

#include "resultmodel.h"

ResultModel::ResultModel( QObject *parent )
  : QAbstractTableModel( parent )
{
}

void ResultModel::clear()
{
  m_results.clear();
  m_resultCounts.clear();
}

void ResultModel::sync()
{
  reset();
}

void ResultModel::addResult( const QString &choice, int ranking )
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

QVariant ResultModel::data(const QModelIndex &index, int role) const
{
  if ( role != Qt::DisplayRole ) {
    return QVariant();
  }

  QList<QString> keys = m_results.keys();

  int col = index.column();
  int row = index.row();
  QString key = keys.value( row );

  switch ( col ) {
    case 0:
      return key;
    case 1:
      return m_results.value( key );
    case 2:
      return m_resultCounts.value( key );
    case 3:
      return m_results.value( key ) / m_resultCounts.value( key );
    default:
      return QVariant();
  }
}

QVariant ResultModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
  if ( role != Qt::DisplayRole ) {
    return QVariant();
  }
  
  if ( orientation == Qt::Vertical ) {
    return QVariant();
  } else {
    switch ( section ) {
      case 0:
        return "Choice";
      case 1:
        return "Ranking";
      case 2:
        return "Rankings";
      case 3:
        return "Result";
      default:
        return "undefined";
    }
  }
}

int ResultModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED( parent );

  return m_results.size();
}

int ResultModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED( parent );

  return 4;
}
