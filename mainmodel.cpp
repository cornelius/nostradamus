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

#include <QMessageBox>

MainModel::MainModel()
{
  m_choicesModel = new QStandardItemModel;
  connect( m_choicesModel, SIGNAL( rowsRemoved( const QModelIndex &, int,
    int ) ),
    SLOT( emitChoicesCountChanged() ) );
  connect( m_choicesModel, SIGNAL( rowsInserted( const QModelIndex &, int,
    int ) ),
    SLOT( emitChoicesCountChanged() ) );

  m_criteriaModel = new CriteriaModel( this );
  connect( m_criteriaModel, SIGNAL( rowsRemoved( const QModelIndex &, int,
    int ) ),
    SLOT( emitCriteriaCountChanged() ) );
  connect( m_criteriaModel, SIGNAL( rowsInserted( const QModelIndex &, int,
    int ) ),
    SLOT( emitCriteriaCountChanged() ) );

  m_resultModel = new ResultModel;
}

QStandardItemModel *MainModel::choicesModel() const
{
  return m_choicesModel;
}

CriteriaModel *MainModel::criteriaModel() const
{
  return m_criteriaModel;
}

ResultModel *MainModel::resultModel() const
{
  return m_resultModel;
}

void MainModel::clear()
{
  m_choicesModel->clear();
  m_criteriaModel->clear();
  m_resultModel->clear();

  m_criteria.clear();
  m_comparisons.clear();
}

bool MainModel::load(const QString &filename)
{
  if ( !QFile::exists( filename ) ) {
    QMessageBox::information( this, tr("Information"),
      tr("Starting with new file.") );
    return false;
  }

  QFile file( filename );
  if ( !file.open( QIODevice::ReadOnly ) ) {
    QMessageBox::critical( this, tr("Error"),
      tr("Unable to open file '%1' for reading.").arg( filename ) );
    return false;
  }

  clear();

  QXmlStreamReader xml( &file );

  while ( !xml.atEnd() ) {
    xml.readNext();

    if ( xml.isStartElement() && xml.name() == "choice" ) {
      QStandardItem *item = new QStandardItem( xml.readElementText() );
      m_choicesModel->appendRow( item );
    }

    if ( xml.isStartElement() && xml.name() == "criterion" ) {
      m_criteria.append( xml.readElementText() );
    }
    
    if ( xml.isStartElement() && xml.name() == "comparison" ) {

      Comparison c;  

      c.setMeta( xml.attributes().value( "meta" ) == "true" );
      
      while( !xml.atEnd() ) {
        xml.readNext();
        
        if ( xml.isEndElement() && xml.name() == "comparison" ) break;

        if ( xml.isStartElement() ) {
          if ( xml.name() == "criterion" ) {
            c.setCriterion( xml.readElementText() );
          } else if ( xml.name() == "left" ) {
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

  return true;
}

bool MainModel::save(const QString &filename)
{
  QFile file( filename );
  if ( !file.open( QIODevice::WriteOnly ) ) {
    QMessageBox::critical( this, tr("Error"),
      tr("Unable to open file '%1' for writing.").arg( filename ) );
    return false;
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
  for( int i = 0; i < criteriaCount(); ++i ) {
    xml.writeTextElement( "criterion", m_criteria[ i ] );
  }
  xml.writeEndElement();

  xml.writeStartElement( "comparisons" );
  foreach( Comparison c, m_comparisons ) {
    xml.writeStartElement( "comparison" );
    xml.writeAttribute( "meta", c.meta() ? "true" : "false" );

    xml.writeTextElement( "criterion", c.criterion() );
    xml.writeTextElement( "left", c.left() );
    xml.writeTextElement( "right", c.right() );
    xml.writeTextElement( "ranking", QString::number( c.ranking() ) );
    xml.writeTextElement( "updated_at", c.updatedAt().toString() );

    xml.writeEndElement();
  }
  xml.writeEndElement();
  
  xml.writeEndDocument();

  return true;
}

QString MainModel::firstCriterion() const
{
  if ( criteriaCount() < 1 ) {
    return QString();
  } else {
    return m_criteria[ 0 ];
  }
}

void MainModel::addCriterion( const QString &c )
{
  m_criteria.append( c );
  m_criteriaModel->addCriterion( c );
}

Choice::Pair MainModel::randomPair( QAbstractItemModel *model )
{
  if ( model->rowCount() < 2 ) {
    return qMakePair( QString(), QString() );
  }

  QString left = randomChoice( model );

  QString right;
  do {
    right = randomChoice( model );
  } while ( left == right );
  
  return qMakePair( left, right );
}

QString MainModel::randomChoice( QAbstractItemModel *model )
{
  if ( model->rowCount() == 0 ) return QString();

  QModelIndex index = model->index( randomNumber( model->rowCount() - 1 ), 0 );

  QString result = index.data().toString();
  
  return result;
}

int MainModel::randomNumber( int max )
{
  return ( max + 1 ) * ( rand() / ( RAND_MAX + 1.0 ) );
}

void MainModel::addComparison( const Comparison &comparison )
{
  m_comparisons.append( comparison );
  
  emit comparisonsCountChanged( comparisonsCount() );
}

void MainModel::calculateResult()
{
  Result *result = new Result( "", m_comparisons );

  result->calculate();

  m_resultModel->setResult( result );
}

int MainModel::choicesCount() const
{
  return m_choicesModel->rowCount();
}

int MainModel::criteriaCount() const
{
  return m_criteria.count();
}

int MainModel::comparisonsCount( const QString &criterion ) const
{
  if ( criterion.isEmpty() )
    return m_comparisons.count();

  int count = 0;
  foreach( Comparison c, m_comparisons ) {
    if ( c.criterion() == criterion ) ++count;
  }
  return count;
}

void MainModel::emitChoicesCountChanged()
{
  emit choicesCountChanged( choicesCount() );
}

void MainModel::emitCriteriaCountChanged()
{
  emit criteriaCountChanged( criteriaCount() );
}

QStringList MainModel::criteria() const
{
  return m_criteria;
}
