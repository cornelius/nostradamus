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
#ifndef MAINMODEL_H
#define MAINMODEL_H

#include "choice.h"
#include "comparison.h"

#include <QtGui>

class ResultModel;

class MainModel : public QWidget
{
    Q_OBJECT
  public:
    MainModel();

    void save();
    void load();

    QStandardItemModel *choicesModel() const;
    QStandardItemModel *criteriaModel() const;
    ResultModel *resultModel() const;

    QString firstCriterion() const;

    Choice::Pair randomPair();

    int randomNumber( int max );

    void addComparison( const Comparison & );

    void calculateResult();

    int choicesCount() const;
    int criteriaCount() const;
    int comparisonsCount() const;

  signals:
    void choicesCountChanged( int );
    void criteriaCountChanged( int );
    void comparisonsCountChanged( int );

  protected:
    QString randomChoice();

  protected slots:
    void emitChoicesCountChanged();
    void emitCriteriaCountChanged();

  private:
    QStandardItemModel *m_choicesModel;
    QStandardItemModel *m_criteriaModel;
    ResultModel *m_resultModel;

    Comparison::List m_comparisons;

    QString m_filename;
};

#endif
