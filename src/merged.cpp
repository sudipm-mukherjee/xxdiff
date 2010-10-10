/* -*- c-file-style: "xxdiff" -*- */
/******************************************************************************\
 * $RCSfile$
 *
 * Copyright (C) 1999-2003  Martin Blais <blais@furius.ca>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 ******************************************************************************/

/*==============================================================================
 * EXTERNAL DECLARATIONS
 *============================================================================*/

#include <merged.h>
#include <text.h>
#include <app.h>
#include <resources.h>
#include <diffs.h>
#include <buffer.h>

#include <q3scrollview.h>
#include <qpainter.h>
#include <qbrush.h>
#include <qpen.h>
#include <qcolor.h>
#include <QMenu>
#include <QMenuBar>
#include <qlayout.h>

#include <qapplication.h>
#include <qclipboard.h>
//Added by qt3to4:
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <math.h>
#include <stdio.h>

XX_NAMESPACE_BEGIN

/*==============================================================================
 * PUBLIC FUNCTIONS
 *============================================================================*/

//------------------------------------------------------------------------------
//
XxMergedFrame::XxMergedFrame( 
   XxApp*      app, 
   QWidget*    parent, 
   const char* name 
) :
   BaseClass( app, parent, name )
{
   QVBoxLayout* vlayout = new QVBoxLayout( this );
   vlayout->setSpacing( 0 );
   vlayout->setMargin( 0 );

   QHBoxLayout* hlayout = new QHBoxLayout( vlayout );
   hlayout->setSpacing( 0 );
   hlayout->setMargin( 0 );
   
   _text = new XxText( _app, this, -1 );

   hlayout->addWidget( _text );
   
   _vscroll[0] = new QScrollBar;
  // _vscroll[0]->setFixedWidth( 20 ); to be removed, at least on OSX
   hlayout->addWidget( _vscroll[0] );

   _hscroll = new QScrollBar( Qt::Horizontal );
   //_hscroll->setFixedHeight( 20 ); to be removed, at least on OSX

   vlayout->addWidget( _hscroll );

   connect( _vscroll[0], SIGNAL(valueChanged(int)),
            this, SLOT(verticalScroll(int)) );
   connect( _hscroll, SIGNAL(valueChanged(int)),
            this, SLOT(horizontalScroll(int)) );

   // Watch cursor changes.
   connect( app, SIGNAL(cursorChanged(int)), this, SLOT(onCursorChanged(int)) );
}

//------------------------------------------------------------------------------
//
void XxMergedFrame::update()
{
   BaseClass::update();
   _text->update();
}

//------------------------------------------------------------------------------
//
QSize XxMergedFrame::computeDisplaySize() const
{
   uint displayWidth = _text->contentsRect().width();
   uint displayHeight = _text->contentsRect().height();
   return QSize( displayWidth, displayHeight );
}

//------------------------------------------------------------------------------
//
uint XxMergedFrame::computeTextLength() const
{
   return _text->computeMergedLines();
}

//------------------------------------------------------------------------------
//
XxDln XxMergedFrame::getNbDisplayLines() const
{
   return _text->computeDisplayLines();
}

//------------------------------------------------------------------------------
//
void XxMergedFrame::onCursorChanged( int cursorLine )
{
   // Scroll to make sure that the display always includes the cursor line.
   if ( cursorLine < getTopLine() ) {
      setTopLine( cursorLine );
   }
   else if ( cursorLine > getBottomLine() ) {
      setBottomLine( cursorLine );
   }
}

/*==============================================================================
 * CLASS XxMergedWindow
 *============================================================================*/

//------------------------------------------------------------------------------
//
XxMergedWindow::XxMergedWindow( 
   XxApp*      app, 
   QWidget*    parent
) :
   BaseClass( parent ),
   _app( app )
{
   const XxResources& resources = app->getResources();

   QkMenu* menu = menuBar()->addMenu( "W&indow" );
   menu->addAction( 
      "Close", this, SLOT(hide()),
      resources.getAccelerator( ACCEL_MERGED_CLOSE )
   );

   _frame = new XxMergedFrame( app, this, "merged_frame" );

   setCentralWidget( _frame );
}

//------------------------------------------------------------------------------
//
void XxMergedWindow::update()
{
   BaseClass::update();
   _frame->update(); // FIXME do we really need this?
}

//------------------------------------------------------------------------------
//
void XxMergedWindow::show()
{
   BaseClass::show();
   // Nop for now.
}

//------------------------------------------------------------------------------
//
void XxMergedWindow::hide()
{
   BaseClass::hide();
   _app->synchronizeUI();
}

XX_NAMESPACE_END
