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

#include "firstcriterioninput.h"

#include <QBoxLayout>
#include <QLabel>

FirstCriterionInput::FirstCriterionInput( MainModel *model )
  : m_model( model )
{
  QBoxLayout *topLayout = new QVBoxLayout( this );

  topLayout->addStretch( 1 );

  QLabel *label = new QLabel( "Enter a criterion:" );
  topLayout->addWidget( label );

  QBoxLayout *newLayout = new QHBoxLayout;
  topLayout->addLayout( newLayout );

  m_newCriterionEdit = new QLineEdit;
  newLayout->addWidget( m_newCriterionEdit );
  connect( m_newCriterionEdit, SIGNAL( returnPressed() ), SLOT( newCriterion() ) );
  connect( m_newCriterionEdit, SIGNAL( textChanged( const QString & ) ),
    SLOT( checkNewButton() ) );

  m_newButton = new QPushButton( "Add New Criterion");
  newLayout->addWidget( m_newButton );
  connect( m_newButton, SIGNAL( clicked() ), SLOT( newCriterion() ) );
  checkNewButton();

  topLayout->addStretch( 1 );
}

void FirstCriterionInput::newCriterion()
{
  m_model->addCriterion( m_newCriterionEdit->text() );

  emit criterionEntered();
}

void FirstCriterionInput::checkNewButton()
{
  m_newButton->setEnabled( !m_newCriterionEdit->text().isEmpty() );
}
