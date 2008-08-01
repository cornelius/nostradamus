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

#include "mainview.h"

#include "mainmodel.h"
#include "choicesview.h"
#include "ranker.h"
#include "criteriaview.h"
#include "resultview.h"
#include "criteriachooser.h"
#include "firstcriterioninput.h"

MainView::MainView()
{
  m_mainModel = new MainModel;

  QBoxLayout *topLayout = new QHBoxLayout;
  setLayout( topLayout );

  QBoxLayout *navLayout = new QVBoxLayout;
  topLayout->addLayout( navLayout );
  
  QPushButton *button = new QPushButton( "Choices" );
  navLayout->addWidget( button );
  connect( button, SIGNAL( clicked() ), SLOT( showChoices() ) );
  
  button = new QPushButton( "Criteria" );
  navLayout->addWidget( button );
  connect( button, SIGNAL( clicked() ), SLOT( showCriteria() ) );

  button = new QPushButton( "Rank" );
  navLayout->addWidget( button );
  connect( button, SIGNAL( clicked() ), SLOT( showRanker() ) );

  button = new QPushButton( "Result" );
  navLayout->addWidget( button );
  connect( button, SIGNAL( clicked() ), SLOT( showResult() ) );

  navLayout->addStretch( 1 );

  m_workAreaLayout = new QStackedLayout;
  topLayout->addLayout( m_workAreaLayout );

  m_choicesView = new ChoicesView( m_mainModel->choicesModel() );
  m_workAreaLayout->addWidget( m_choicesView );

  m_criteriaView = new CriteriaView( m_mainModel->criteriaModel() );
  m_workAreaLayout->addWidget( m_criteriaView );

  m_firstCriterionInput = new FirstCriterionInput(
    m_mainModel->criteriaModel() );
  m_workAreaLayout->addWidget( m_firstCriterionInput );
  connect( m_firstCriterionInput, SIGNAL( criterionEntered() ),
    SLOT( showRanker() ) );

  m_criteriaChooser = new CriteriaChooser( m_mainModel->criteriaModel() );
  m_workAreaLayout->addWidget( m_criteriaChooser );
  connect( m_criteriaChooser, SIGNAL( itemChosen( const QString & ) ),
    SLOT( setRankingCriterion( const QString & ) ) );

  m_ranker = new Ranker( m_mainModel );
  m_workAreaLayout->addWidget( m_ranker );

  m_resultView = new ResultView( m_mainModel->resultModel() );
  m_workAreaLayout->addWidget( m_resultView );
}

void MainView::load()
{
  m_mainModel->load();
}

void MainView::save()
{
  m_mainModel->save();
}

void MainView::showChoices()
{
  m_workAreaLayout->setCurrentWidget( m_choicesView );
}

void MainView::showCriteria()
{
  m_workAreaLayout->setCurrentWidget( m_criteriaView );
}

void MainView::showRanker()
{
  if ( m_mainModel->criteriaCount() == 0 ) {
    m_workAreaLayout->setCurrentWidget( m_firstCriterionInput );
  } else if ( m_mainModel->criteriaCount() > 1 ) {
    m_workAreaLayout->setCurrentWidget( m_criteriaChooser );
  } else {
    m_workAreaLayout->setCurrentWidget( m_ranker );
    m_ranker->startRanking( m_mainModel->firstCriterion() );
  }
}

void MainView::showResult()
{
  m_workAreaLayout->setCurrentWidget( m_resultView );
  m_mainModel->calculateResult();
}

void MainView::setRankingCriterion( const QString &criterion )
{
  m_workAreaLayout->setCurrentWidget( m_ranker );
  m_ranker->startRanking( criterion );
}
