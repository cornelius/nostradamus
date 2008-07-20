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

#include "choicesview.h"
#include "ranker.h"
#include "criteriaview.h"

MainView::MainView()
{
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

  navLayout->addStretch( 1 );

  m_workAreaLayout = new QStackedLayout;
  topLayout->addLayout( m_workAreaLayout );

  m_choicesView = new ChoicesView;
  m_workAreaLayout->addWidget( m_choicesView );

  m_criteriaView = new CriteriaView;
  m_workAreaLayout->addWidget( m_criteriaView );

  m_ranker = new Ranker;
  m_workAreaLayout->addWidget( m_ranker );
}

void MainView::load()
{
  m_choicesView->loadChoices();
  m_criteriaView->loadCriteria();
}

void MainView::save()
{
  m_choicesView->saveChoices();
  m_criteriaView->saveCriteria();
}

void MainView::showChoices()
{
  m_workAreaLayout->setCurrentWidget( m_choicesView );
}

void MainView::showRanker()
{
  m_workAreaLayout->setCurrentWidget( m_ranker );
}

void MainView::showCriteria()
{
  m_workAreaLayout->setCurrentWidget( m_criteriaView );
}

