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
  topLayout->addWidget( m_questionLabel );

  QBoxLayout *choicesLayout = new QHBoxLayout;
  topLayout->addLayout( choicesLayout );

  QLabel *label = new QLabel( "Left" );
  choicesLayout->addWidget( label );

  choicesLayout->addStretch( 1 );

  label = new QLabel( "Right" );
  choicesLayout->addWidget( label );

  QFrame *rankingArea = new RankingArea;
  topLayout->addWidget( rankingArea );
  connect( rankingArea, SIGNAL( ranked( int ) ), SLOT( slotRanked( int ) ) );

  topLayout->addStretch( 1 );
}

void Ranker::startRanking()
{
  m_questionLabel->setText( m_mainModel->firstQuestion() );
}

void Ranker::slotRanked( int ranking )
{
  qDebug() << "SLOT RANKED:" << ranking;
}
