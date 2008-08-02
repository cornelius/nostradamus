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

#include "ranker.h"

#include "rankingarea.h"

Ranker::Ranker( MainModel *mainModel )
  : m_mainModel( mainModel )
{
  QBoxLayout *topLayout = new QVBoxLayout( this );

  topLayout->addStretch( 1 );

  m_questionLabel = new QLabel;
  m_questionLabel->setAlignment( Qt::AlignHCenter );
  topLayout->addWidget( m_questionLabel );

  QBoxLayout *choicesLayout = new QHBoxLayout;
  topLayout->addLayout( choicesLayout );

  m_leftLabel = new QLabel( "Left" );
  choicesLayout->addWidget( m_leftLabel );

  choicesLayout->addStretch( 1 );

  m_rightLabel = new QLabel( "Right" );
  choicesLayout->addWidget( m_rightLabel );

  QFrame *rankingArea = new RankingArea;
  topLayout->addWidget( rankingArea );
  connect( rankingArea, SIGNAL( ranked( int ) ), SLOT( slotRanked( int ) ) );

  topLayout->addStretch( 1 );
}

void Ranker::startRanking( QStandardItemModel *model, const QString &criterion )
{
  m_choicesModel = model;
  m_questionLabel->setText( criterion );

  newComparison();
}

void Ranker::newComparison()
{
  Choice::Pair pair = m_mainModel->randomPair( m_choicesModel );

  m_leftLabel->setText( pair.first );
  m_rightLabel->setText( pair.second );
}

void Ranker::slotRanked( int ranking )
{
  Comparison c;
  
  if ( m_choicesModel == m_mainModel->criteriaModel() ) c.setMeta( true );

  c.setCriterion( m_questionLabel->text() );
  
  c.setLeft( m_leftLabel->text() );
  c.setRight( m_rightLabel->text() );
  
  c.setRanking( ranking );

  c.setUpdatedAt( QDateTime::currentDateTime() );

  m_mainModel->addComparison( c );

  newComparison();
}
