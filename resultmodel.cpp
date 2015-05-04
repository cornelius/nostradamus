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
  : QAbstractTableModel( parent ), m_result( 0 )
{
}

ResultModel::~ResultModel()
{
  delete m_result;
}

void ResultModel::setResult( Result *result )
{
  beginResetModel();
  delete m_result;
  endResetModel();

  m_result = result;
}

QVariant ResultModel::data(const QModelIndex &index, int role) const
{
  if ( role != Qt::DisplayRole || !m_result ) {
    return QVariant();
  }

  ResultItem::List items = m_result->items();

  int col = index.column();
  int row = index.row();
  ResultItem item = items[ row ];

  switch ( col ) {
    case 0:
      return item.choice;
    case 1:
      return item.comparisonsCount;
    case 2:
      return item.ranking;
    case 3:
      return item.normalizedRanking;
    case 4:
      return item.weightedRanking;
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
        return "Rankings";
      case 2:
        return "Ranking";
      case 3:
        return "Normalized";
      case 4:
        return "Weighted";
      default:
        return "undefined";
    }
  }
}

int ResultModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED( parent );

  if ( !m_result ) return 0;

  return m_result->items().size();
}

int ResultModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED( parent );

  return 5;
}
