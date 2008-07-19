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

#include "choicesview.h"

#include <QtGui>

ChoicesView::ChoicesView()
{
  QBoxLayout *topLayout = new QVBoxLayout( this );

  m_model = new QStandardItemModel;
  
  QStandardItem *item = new QStandardItem("Eins");
  m_model->setItem(0,0,item);
  
  item = new QStandardItem("Zwei");
  m_model->setItem(1,0,item);

  QListView *listView = new QListView;
  topLayout->addWidget( listView );
  
  listView->setModel( m_model );

  m_newChoiceEdit = new QLineEdit;
  topLayout->addWidget( m_newChoiceEdit );
  connect( m_newChoiceEdit, SIGNAL( returnPressed() ), SLOT( newChoice() ) );
}

void ChoicesView::newChoice()
{
  QStandardItem *item = new QStandardItem( m_newChoiceEdit->text() );
  m_model->appendRow( item );

  m_newChoiceEdit->setText( QString() );
}
