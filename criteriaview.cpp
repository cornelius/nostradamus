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

#include <QtGui>

CriteriaView::CriteriaView()
  : m_filename("criteria.xml")
{
  QBoxLayout *topLayout = new QVBoxLayout( this );

  m_model = new QStandardItemModel;
  
  QListView *listView = new QListView;
  topLayout->addWidget( listView );
  
  listView->setModel( m_model );

  m_newCriterionEdit = new QLineEdit;
  topLayout->addWidget( m_newCriterionEdit );
  connect( m_newCriterionEdit, SIGNAL( returnPressed() ), SLOT( newCriterion() ) );
}

void CriteriaView::newCriterion()
{
  QStandardItem *item = new QStandardItem( m_newCriterionEdit->text() );
  m_model->appendRow( item );

  m_newCriterionEdit->setText( QString() );
}

void CriteriaView::saveCriteria()
{
  QFile file( m_filename );
  if ( !file.open( QIODevice::WriteOnly ) ) {
    QMessageBox::critical( this, tr("Error"),
      tr("Unable to open file '%1' for writing.").arg( m_filename ) );
    return;
  }

  QXmlStreamWriter xml( &file );
  xml.setAutoFormatting( true );
  
  xml.writeStartDocument();

  xml.writeStartElement( "criteria" );

  for( int i = 0; i < m_model->rowCount(); ++i ) {
    xml.writeTextElement( "criterion", m_model->item( i )->text() );
  }
  
  xml.writeEndDocument();
}

void CriteriaView::loadCriteria()
{
  if ( !QFile::exists( m_filename ) ) {
    QMessageBox::information( this, tr("Information"),
      tr("Starting with new file.") );
    return;
  }

  QFile file( m_filename );
  if ( !file.open( QIODevice::ReadOnly ) ) {
    QMessageBox::critical( this, tr("Error"),
      tr("Unable to open file '%1' for reading.").arg( m_filename ) );
    return;
  }

  QXmlStreamReader xml( &file );

  while ( !xml.atEnd() ) {
    xml.readNext();

    if ( xml.isStartElement() && xml.name() == "criterion" ) {
      QStandardItem *item = new QStandardItem( xml.readElementText() );
      m_model->appendRow( item );
    }
  }

  if ( xml.hasError() ) {
    QMessageBox::critical( this, tr("Error"),
      tr("Error parsing XML.") );
  }
}
