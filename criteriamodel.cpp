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

#include "criteriamodel.h"

#include "mainmodel.h"

CriteriaModel::CriteriaModel( MainModel *model, QObject *parent )
  : QAbstractTableModel( parent ), m_mainModel( model )
{
}

void CriteriaModel::addCriterion(const QString &c)
{
  beginInsertRows(QModelIndex(), rowCount(), rowCount());
  endInsertRows();
}

QVariant CriteriaModel::data(const QModelIndex &index, int role) const
{
  if ( role != Qt::DisplayRole ) {
    return QVariant();
  }

  int col = index.column();
  int row = index.row();

  switch ( col ) {
    case 0:
      return m_mainModel->criteria()[ row ];
    case 1:
      return m_mainModel->comparisonsCount( m_mainModel->criteria()[ row ]);
    default:
      return QVariant();
  }
}

QVariant CriteriaModel::headerData(int section, Qt::Orientation orientation,
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
        return "Criterion";
      case 1:
        return "Comparisons";
      default:
        return "undefined";
    }
  }
}

int CriteriaModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED( parent );

  return m_mainModel->criteriaCount();
}

int CriteriaModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED( parent );

  return 2;
}
