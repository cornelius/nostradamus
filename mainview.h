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
#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QtGui>

class ChoicesView;
class CriteriaView;
class FirstCriterionInput;
class CriteriaChooser;
class Ranker;
class ResultView;
class MainModel;

class MainView : public QWidget
{
    Q_OBJECT
  public:
    MainView();

    void save();
    void load();

  protected slots:
    void showChoices();
    void showRanker();
    void showCriteria();
    void showResult();

    void setRankingCriterion( const QString &criterion );
    
  private:
    MainModel *m_mainModel;
  
    ChoicesView *m_choicesView;
    CriteriaView *m_criteriaView;
    FirstCriterionInput *m_firstCriterionInput;
    CriteriaChooser *m_criteriaChooser;
    Ranker *m_ranker;
    ResultView *m_resultView;
    
    QStackedLayout *m_workAreaLayout;
};

#endif
