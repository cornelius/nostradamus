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

#include "mainmodel.h"

#include "resultmodel.h"

MainModel::MainModel()
  : m_filename( "ranking.xml" )
{
  m_choicesModel = new QStandardItemModel;
  m_criteriaModel = new QStandardItemModel;
  m_resultModel = new ResultModel;
}

QStandardItemModel *MainModel::choicesModel() const
{
  return m_choicesModel;
}

QStandardItemModel *MainModel::criteriaModel() const
{
  return m_criteriaModel;
}

ResultModel *MainModel::resultModel() const
{
  return m_resultModel;
}

void MainModel::load()
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
    
    if ( xml.isStartElement() && xml.name() == "comparison" ) {

      Comparison c;  
      
      while( !xml.atEnd() ) {
        xml.readNext();
        
        if ( xml.isEndElement() && xml.name() == "comparison" ) break;

        if ( xml.isStartElement() ) {
          if ( xml.name() == "left" ) {
            c.setLeft( xml.readElementText() );
          } else if ( xml.name() == "right" ) {
            c.setRight( xml.readElementText() );
          } else if ( xml.name() == "ranking" ) {
            c.setRanking( xml.readElementText().toInt() );
          } else if ( xml.name() == "updated_at" ) {
            c.setUpdatedAt( QDateTime::fromString( xml.readElementText() ) );
          }
        }
      }
      
      addComparison( c );
    }
  }

  if ( xml.hasError() ) {
    QMessageBox::critical( this, tr("Error"),
      tr("Error parsing XML.") );
  }
}

void MainModel::save()
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

  xml.writeStartElement( "comparisons" );
  foreach( Comparison c, m_comparisons ) {
    xml.writeStartElement( "comparison" );
    xml.writeTextElement( "left", c.left() );
    xml.writeTextElement( "right", c.right() );
    xml.writeTextElement( "ranking", QString::number( c.ranking() ) );
    xml.writeTextElement( "updated_at", c.updatedAt().toString() );
    xml.writeEndElement();
  }
  xml.writeEndElement();
  
  xml.writeEndDocument();
}

QString MainModel::firstQuestion() const
{
  if ( m_criteriaModel->rowCount() < 1 ) {
    return QString();
  } else {
    return m_criteriaModel->item( 0 )->text();
  }
}

Choice::Pair MainModel::randomPair()
{
  QString left = randomChoice();

  QString right;
  do {
    right = randomChoice();
  } while ( left == right );
  
  return qMakePair( left, right );
}

QString MainModel::randomChoice()
{
  int index = randomNumber( m_choicesModel->rowCount() - 1 );
  return m_choicesModel->item( index )->text();
}

int MainModel::randomNumber( int max )
{
  return ( max + 1 ) * ( rand() / ( RAND_MAX + 1.0 ) );
}

void MainModel::addComparison( const Comparison &comparison )
{
  m_comparisons.append( comparison );
}

void MainModel::calculateResult()
{
  m_resultModel->clear();
  
  foreach( Comparison c, m_comparisons ) {
    m_resultModel->addResult( c.left(), -c.ranking() );
    m_resultModel->addResult( c.right(), c.ranking() );
  }

  m_resultModel->sync();
}
