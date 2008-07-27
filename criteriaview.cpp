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

#include "criteriaview.h"

CriteriaView::CriteriaView( QStandardItemModel *model )
  : m_model( model )
{
  QBoxLayout *topLayout = new QVBoxLayout( this );

  QListView *listView = new QListView;
  topLayout->addWidget( listView );
  
  listView->setModel( m_model );

  QBoxLayout *newLayout = new QHBoxLayout;
  topLayout->addLayout( newLayout );

  m_newCriterionEdit = new QLineEdit;
  newLayout->addWidget( m_newCriterionEdit );
  connect( m_newCriterionEdit, SIGNAL( returnPressed() ), SLOT( newCriterion() ) );
  connect( m_newCriterionEdit, SIGNAL( textChanged( const QString & ) ),
    SLOT( checkNewButton() ) );

  m_newButton = new QPushButton( "Add New Choice");
  newLayout->addWidget( m_newButton );
  connect( m_newButton, SIGNAL( clicked() ), SLOT( newCriterion() ) );
  checkNewButton();
}

void CriteriaView::newCriterion()
{
  QStandardItem *item = new QStandardItem( m_newCriterionEdit->text() );
  m_model->appendRow( item );

  m_newCriterionEdit->setText( QString() );
}

void CriteriaView::checkNewButton()
{
  m_newButton->setEnabled( !m_newCriterionEdit->text().isEmpty() );
}
