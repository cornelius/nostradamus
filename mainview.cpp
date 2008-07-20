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
  : m_filename( "ranking.xml" )
{
  m_choicesModel = new QStandardItemModel;
  m_criteriaModel = new QStandardItemModel;

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

  m_choicesView = new ChoicesView( m_choicesModel );
  m_workAreaLayout->addWidget( m_choicesView );

  m_criteriaView = new CriteriaView( m_criteriaModel );
  m_workAreaLayout->addWidget( m_criteriaView );

  m_ranker = new Ranker;
  m_workAreaLayout->addWidget( m_ranker );
}

void MainView::load()
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

    if ( xml.isStartElement() && xml.name() == "choice" ) {
      QStandardItem *item = new QStandardItem( xml.readElementText() );
      m_choicesModel->appendRow( item );
    }

    if ( xml.isStartElement() && xml.name() == "criterion" ) {
      QStandardItem *item = new QStandardItem( xml.readElementText() );
      m_criteriaModel->appendRow( item );
    }
  }

  if ( xml.hasError() ) {
    QMessageBox::critical( this, tr("Error"),
      tr("Error parsing XML.") );
  }
}

void MainView::save()
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

  xml.writeStartElement( "ranking" );

  xml.writeStartElement( "choices" );
  for( int i = 0; i < m_choicesModel->rowCount(); ++i ) {
    xml.writeTextElement( "choice", m_choicesModel->item( i )->text() );
  }
  xml.writeEndElement();
  
  xml.writeStartElement( "criteria" );
  for( int i = 0; i < m_criteriaModel->rowCount(); ++i ) {
    xml.writeTextElement( "criterion", m_criteriaModel->item( i )->text() );
  }
  xml.writeEndElement();
  
  xml.writeEndDocument();
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

