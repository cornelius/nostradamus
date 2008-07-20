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
#ifndef CRITERIAVIEW_H
#define CRITERIAVIEW_H

#include <QtGui>

class CriteriaView : public QWidget
{
    Q_OBJECT
  public:
    CriteriaView( QStandardItemModel * );

    void saveCriteria();
    void loadCriteria();

  protected slots:
    void newCriterion();

  private:
    QStandardItemModel *m_model; 

    QLineEdit *m_newCriterionEdit;

    QString m_filename;
};

#endif
