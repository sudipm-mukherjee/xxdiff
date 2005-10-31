/******************************************************************************\
 * $Id: resources.cpp 431 2001-11-30 02:24:05Z  $
 * $Date: 2001-11-29 21:24:05 -0500 (Thu, 29 Nov 2001) $
 *
 * Copyright (C) 1999-2001  Martin Blais <blais@iro.umontreal.ca>
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
 *****************************************************************************/

/*==============================================================================
 * EXTERNAL DECLARATIONS
 *============================================================================*/

#include <app.h> // just for getting the size of the main window
#include <accelUtil.h>
#include <resources.h>
#include <optionsDialog.h>

#include <qcolor.h>
#include <qaccel.h>
#include <qobject.h>
#include <qnamespace.h>
#include <qapplication.h> // to get desktop

#include <iostream>
#include <string.h> // ::strcmp
#include <stdio.h>

XX_NAMESPACE_BEGIN

/*==============================================================================
 * PUBLIC FUNCTIONS
 *============================================================================*/

/*==============================================================================
 * CLASS XxResources
 *============================================================================*/

//------------------------------------------------------------------------------
//
XxResources::XxResources( bool original )
{
   if ( !original ) {
      initialize();
   }
   else {
      initializeOriginalXdiff();
   }
}

//------------------------------------------------------------------------------
//
void XxResources::initialize()
{
   initializeOriginalXdiff();

   _boolOpts[ BOOL_HORIZONTAL_DIFFS ] = true;
   _boolOpts[ BOOL_IGNORE_HORIZONTAL_WS ] = false;
   _boolOpts[ BOOL_FORMAT_CLIPBOARD_TEXT ] = true;

   _showOpts[ SHOW_OVERVIEW ] = true;
   _showOpts[ SHOW_FILENAMES ] = true;
}

//------------------------------------------------------------------------------
//
void XxResources::initializeOriginalXdiff()
{
   // Just like xdiff.
   _preferredGeometry = QRect( -1, -1, 1200, 600 );
   _maximize = false;

   //---------------------------------------------------------------------------

   // Initialize because this is more handy than specifying empty defaults for
   // all accelerators.
   for ( int ii = 0; ii < ACCEL_LAST; ++ii ) {
      _accelerators[ ii ] = 0;
   }
   
   _accelerators[ ACCEL_EXIT ] = Qt::CTRL | Qt::Key_Q;
                  
   _accelerators[ ACCEL_SEARCH ] = Qt::CTRL | Qt::Key_S;
   _accelerators[ ACCEL_SEARCH_FORWARD ] = Qt::CTRL | Qt::Key_F;
   _accelerators[ ACCEL_SEARCH_BACKWARD ] = Qt::CTRL | Qt::Key_B; 
   _accelerators[ ACCEL_SCROLL_DOWN ] = Qt::CTRL | Qt::Key_V;
   _accelerators[ ACCEL_SCROLL_UP ] = Qt::ALT | Qt::Key_V;
   _accelerators[ ACCEL_CURSOR_DOWN ] = Qt::CTRL | Qt::Key_N;
   _accelerators[ ACCEL_CURSOR_UP ] = Qt::CTRL | Qt::Key_P;
   _accelerators[ ACCEL_CURSOR_TOP ] = Qt::Key_Home;
   _accelerators[ ACCEL_CURSOR_BOTTOM ] = Qt::Key_End;
   _accelerators[ ACCEL_REDO_DIFF ] = Qt::CTRL | Qt::Key_R;
   _accelerators[ ACCEL_NEXT_DIFFERENCE ] = Qt::Key_N;
   _accelerators[ ACCEL_PREVIOUS_DIFFERENCE ] = Qt::Key_P;
   _accelerators[ ACCEL_NEXT_UNSELECTED ] = Qt::Key_B;
   _accelerators[ ACCEL_PREVIOUS_UNSELECTED ] = Qt::Key_O;
   _accelerators[ ACCEL_SELECT_GLOBAL_LEFT ] = Qt::CTRL|Qt::ALT | Qt::Key_H; 
   _accelerators[ ACCEL_SELECT_GLOBAL_MIDDLE ] = Qt::CTRL|Qt::ALT | Qt::Key_J; 
   _accelerators[ ACCEL_SELECT_GLOBAL_RIGHT ] = Qt::CTRL|Qt::ALT | Qt::Key_K; 
   _accelerators[ ACCEL_SELECT_GLOBAL_NEITHER ] = Qt::CTRL|Qt::ALT | Qt::Key_Y;
   _accelerators[ ACCEL_SELECT_GLOBAL_UNSELECT ] = Qt::CTRL|Qt::ALT | Qt::Key_U;
   _accelerators[ ACCEL_SELECT_GLOBAL_MERGE ] = Qt::CTRL|Qt::ALT | Qt::Key_M;
   _accelerators[ ACCEL_SELECT_REGION_LEFT ] = Qt::Key_H; 
   _accelerators[ ACCEL_SELECT_REGION_MIDDLE ] = Qt::Key_J; 
   _accelerators[ ACCEL_SELECT_REGION_RIGHT ] = Qt::Key_K;
   _accelerators[ ACCEL_SELECT_REGION_NEITHER ] = Qt::Key_Y;
   _accelerators[ ACCEL_SELECT_REGION_UNSELECT ] = Qt::Key_U;
   _accelerators[ ACCEL_SELECT_REGION_LEFT_AND_NEXT ] = Qt::CTRL | Qt::Key_H;
   _accelerators[ ACCEL_SELECT_REGION_MIDDLE_AND_NEXT ] = Qt::CTRL | Qt::Key_J;
   _accelerators[ ACCEL_SELECT_REGION_RIGHT_AND_NEXT ] = Qt::CTRL | Qt::Key_K;
   _accelerators[ ACCEL_SELECT_REGION_NEITHER_AND_NEXT ] = Qt::CTRL | Qt::Key_Y;
   _accelerators[ ACCEL_SELECT_REGION_SPLIT_SWAP_JOIN ] = Qt::Key_S;
   _accelerators[ ACCEL_SELECT_LINE_LEFT ] = Qt::SHIFT | Qt::Key_H; 
   _accelerators[ ACCEL_SELECT_LINE_MIDDLE ] = Qt::SHIFT | Qt::Key_J; 
   _accelerators[ ACCEL_SELECT_LINE_RIGHT ] = Qt::SHIFT | Qt::Key_K; 
   _accelerators[ ACCEL_SELECT_LINE_NEITHER ] = Qt::SHIFT | Qt::Key_Y;
   _accelerators[ ACCEL_SELECT_LINE_UNSELECT ] = Qt::SHIFT | Qt::Key_U;
   _accelerators[ ACCEL_TABS_AT_3 ] = Qt::Key_3;
   _accelerators[ ACCEL_TABS_AT_4 ] = Qt::Key_4;
   _accelerators[ ACCEL_TABS_AT_8 ] = Qt::Key_8;
   _accelerators[ ACCEL_MERGED_VIEW ] = Qt::ALT | Qt::Key_Y;
   _accelerators[ ACCEL_TOGGLE_LINE_NUMBERS ] = Qt::ALT | Qt::Key_L;
   _accelerators[ ACCEL_TOGGLE_MARKERS ] = Qt::ALT | Qt::Key_M;
   _accelerators[ ACCEL_TOGGLE_OVERVIEW ] = Qt::ALT | Qt::Key_O;
   _accelerators[ ACCEL_TOGGLE_SHOW_FILENAMES ] = Qt::ALT | Qt::Key_S;
   _accelerators[ ACCEL_TOGGLE_HORIZONTAL_DIFFS ] = Qt::ALT | Qt::Key_W;
   _accelerators[ ACCEL_TOGGLE_FORMAT_CLIPBOARD_TEXT ] = Qt::ALT | Qt::Key_A;
   _accelerators[ ACCEL_HELP_ON_CONTEXT ] = Qt::SHIFT | Qt::Key_F1;
                  
   _accelerators[ ACCEL_MERGED_CLOSE ] = Qt::ALT | Qt::Key_W;

   //---------------------------------------------------------------------------

   // // Use a default font that looks like the one from the default SGI scheme.
   // _fontApp.setFamily( "Helvetica" );
   // _fontApp.setItalic( true ); 
   // _fontApp.setBold( true );

   // Note: using "-*-screen-bold-i-normal--*-100-*-*-*-*-iso8859-1"
   // seems to yield the corresponding font to the SGI font under Linux.

   // Try to set the default font to be as close as possible as that under the
   // original xdiff under SGI.
   //_fontText.setRawName( "*-clean-medium-r-normal-*-14-*" ); // XLFD warning
   _fontText.setRawName( "-*-clean-medium-r-normal-*-*-140-75-75-*-*-*-*" );

   //---------------------------------------------------------------------------

   if ( qApp != 0 ) { // protect setNamedColor() in case we have no display.
      setFbColors( COLOR_SAME             , "grey", "black" );
      setFbColors( COLOR_DIFF_ONE         , "palegoldenrod", "black" );
      setFbColors( COLOR_DIFF_ONE_SUP     , "lemonchiffon3", "black" );
      setFbColors( COLOR_DIFF_ONE_ONLY    , "palegoldenrod", "black" );
      setFbColors( COLOR_DIFF_ONE_NONLY   , "lemonchiffon3", "black" );
      setFbColors( COLOR_DIFF_TWO         , "lightblue2", "black" );
      setFbColors( COLOR_DIFF_TWO_SUP     , "lightblue3", "black" );
      setFbColors( COLOR_DIFF_TWO_ONLY    , "lightblue2",  "black" );
      setFbColors( COLOR_DIFF_TWO_NONLY   , "lightblue3", "black" );
             
      setFbColors( COLOR_DELETE           , "lightblue2", "black" );
      setFbColors( COLOR_DELETE_BLANK     , "grey64", "black" );
             
      setFbColors( COLOR_INSERT           , "darkseagreen2", "black" );
      setFbColors( COLOR_INSERT_BLANK     , "grey64", "black" );
             
      setFbColors( COLOR_DIFF_ALL         , "palegoldenrod", "black" );
      setFbColors( COLOR_DIFF_ALL_SUP     , "lemonchiffon3", "black" );
      setFbColors( COLOR_DIFF_ALL_ONLY    , "palegoldenrod", "black" );
      setFbColors( COLOR_DIFF_ALL_NONLY   , "lemonchiffon3", "black" );
             
      setFbColors( COLOR_DIFFDEL          , "palegoldenrod", "black" );
      setFbColors( COLOR_DIFFDEL_SUP      , "lemonchiffon3", "black" );
      setFbColors( COLOR_DIFFDEL_ONLY     , "palegoldenrod", "black" );
      setFbColors( COLOR_DIFFDEL_NONLY    , "lemonchiffon3", "black" );
      setFbColors( COLOR_DIFFDEL_BLANK    , "grey64", "black" );
             
      setFbColors( COLOR_SELECTED         , "plum", "black" );
      setFbColors( COLOR_SELECTED_SUP     , "thistle", "black" );
             
      setFbColors( COLOR_DELETED          , "lightslategrey", "black" );
      setFbColors( COLOR_DELETED_SUP      , "slategrey", "black" );
             
      setFbColors( COLOR_IGNORED          , "grey70", "grey30" );
             
      setFbColors( COLOR_DIRECTORIES      , "mediumturquoise", "black" );
                                                         
      setFbColors( COLOR_MERGED_UNDECIDED , "lemonchiffon3", "black" );
      setFbColors( COLOR_MERGED_DECIDED_1 , "grey70", "black" );
      setFbColors( COLOR_MERGED_DECIDED_2 , "grey70", "black" );
      setFbColors( COLOR_MERGED_DECIDED_3 , "grey70", "black" );
   }   
             
   _backColors[ COLOR_BACKGROUND ] = QColor( 0x40, 0x61, 0x6a, QColor::Rgb );
   _backColors[ COLOR_CURSOR ] =
      QColor( 0xff, 0xff, 0xff, QColor::Rgb ); // white
   _backColors[ COLOR_VERTICAL_LINE ] = 
      QColor( 0xff, 0x00, 0x00, QColor::Rgb ); // red
   // Note: we don't use the fore colors for these guys.

   //---------------------------------------------------------------------------

   _boolOpts[ BOOL_EXIT_ON_SAME ] = false;
   _boolOpts[ BOOL_HORIZONTAL_DIFFS ] = false;
   _boolOpts[ BOOL_IGNORE_HORIZONTAL_WS ] = true;
   _boolOpts[ BOOL_FORMAT_CLIPBOARD_TEXT ] = false;
   _boolOpts[ BOOL_IGNORE_ERRORS ] = false;
   _boolOpts[ BOOL_WARN_ABOUT_UNSAVED ] = false;
   _boolOpts[ BOOL_DISABLE_CURSOR_DISPLAY ] = false;
   _boolOpts[ BOOL_HIDE_CR ] = false;
   _boolOpts[ BOOL_DIRDIFF_IGNORE_FILE_CHANGES ] = false;
   _boolOpts[ BOOL_DIRDIFF_BUILD_FROM_OUTPUT ] = true;
   _boolOpts[ BOOL_DIRDIFF_RECURSIVE ] = false;
   _boolOpts[ BOOL_USE_INTERNAL_DIFF ] = true;

   //---------------------------------------------------------------------------

   // Defaults just like xdiff, pretty plain.
   _showOpts[ SHOW_TOOLBAR ] = false;
   _showOpts[ SHOW_LINE_NUMBERS ] = false;
   _showOpts[ SHOW_VERTICAL_LINE ] = false;
   _showOpts[ SHOW_OVERVIEW ] = true;
   _showOpts[ SHOW_FILENAMES ] = false;

   //---------------------------------------------------------------------------

   _tabWidth = 8;

   //---------------------------------------------------------------------------

   _commands[ CMD_DIFF_FILES_2 ] = "diff";
   _commands[ CMD_DIFF_FILES_3 ] = "diff3";
   _commands[ CMD_DIFF_DIRECTORIES ] = "diff -q -s";
   _commands[ CMD_DIFF_DIRECTORIES_REC ] = "diff -q -s -r";

   // "cmp -s" barfs on directories.
   const char* editor = getenv( "EDITOR" );
   if ( editor != 0 ) {
      _commands[ CMD_EDIT ].setLatin1( editor );
   }
   else {
      _commands[ CMD_EDIT ] = "vi";
   }

   //---------------------------------------------------------------------------

   _commandSwitch[ CMDSW_FILES_IGNORE_TRAILING ] = "-b";
   _commandSwitch[ CMDSW_FILES_IGNORE_WHITESPACE ] = "-w";
   _commandSwitch[ CMDSW_FILES_IGNORE_CASE ] = "-i";
   _commandSwitch[ CMDSW_FILES_IGNORE_BLANK_LINES ] = "-B";
   _commandSwitch[ CMDSW_FILES_QUALITY_NORMAL ] = "";
   _commandSwitch[ CMDSW_FILES_QUALITY_FASTEST ] = "-d";
   _commandSwitch[ CMDSW_FILES_QUALITY_HIGHEST ] = "-H";
         
   //---------------------------------------------------------------------------

   _overviewFileWidth = 20;
   _overviewSepWidth = 14;
   _verticalLinePos = 80;
   
   //---------------------------------------------------------------------------

   _tags[ TAG_CONFLICT_SEPARATOR ] = ">>>>>>>>>>>>>>>>>>>> File %d";
   _tags[ TAG_CONFLICT_END ] = "<<<<<<<<<<<<<<<<<<<<";
   _tags[ TAG_CONDITIONAL_IF ] = "#if defined( %s )";
   _tags[ TAG_CONDITIONAL_ELSEIF ] = "#elif defined( %s )";
   _tags[ TAG_CONDITIONAL_ELSE ] = "#else";
   _tags[ TAG_CONDITIONAL_ENDIF ] = "#endif";

   //---------------------------------------------------------------------------

   _clipboardFormat = QString("%L: %s");

   _ignoreFile = IGNORE_NONE;
}

//------------------------------------------------------------------------------
//
XxResources::~XxResources()
{}

//------------------------------------------------------------------------------
//
void XxResources::setPreferredGeometry( const QRect& geometry )
{
   _preferredGeometry = geometry;
   emit changed();
}

//------------------------------------------------------------------------------
//
void XxResources::setMaximize( bool fs )
{
   _maximize = fs;
   emit changed();
}

//------------------------------------------------------------------------------
//
bool XxResources::setAccelerator( XxAccel accel, const QString& val )
{
   int accelval;
   if ( XxAccelUtil::read( val, accelval ) == true ) {
      int iaccel( accel );
      XX_CHECK( iaccel < int(ACCEL_LAST) );
      _accelerators[ iaccel ] = accelval;
      emit changed();
      return true;
   }
   return false; // Parse error for accelerator string.
}

//------------------------------------------------------------------------------
//
bool XxResources::setFontApp( const QString& val )
{
   _fontApp.setRawName( val );
   emit changed();
   return true; // never generates error.
}

//------------------------------------------------------------------------------
//
bool XxResources::setFontApp( const QFont& font )
{
   _fontApp = font;
   emit changed();
   return true; // never generates error.
}

//------------------------------------------------------------------------------
//
bool XxResources::setFontText( const QString& val )
{
   _fontText.setRawName( val );
   emit changed();
   return true; // never generates error.
}

//------------------------------------------------------------------------------
//
bool XxResources::setFontText( const QFont& font )
{
   _fontText = font;
   emit changed();
   return true; // never generates error.
}

//------------------------------------------------------------------------------
//
void XxResources::setCommand( XxCommand cmdId, const QString& t ) 
{
   _commands[ int(cmdId) ] = t;
   emit changed();
}

//------------------------------------------------------------------------------
//
void XxResources::setCommandSwitch(
   XxCommandSwitch   cmdId,
   const QString& val
)
{
   _commandSwitch[ int(cmdId) ] = val;
   emit changed();
}

//------------------------------------------------------------------------------
//
bool XxResources::isCommandSwitch(
   XxCommand       cmdId,
   XxCommandSwitch optId
) const
{
   QString cmd = getCommand( cmdId );
   QString opt = getCommandSwitch( optId );
   return XxOptionsDialog::isInCommand( cmd, opt );
}

//------------------------------------------------------------------------------
//
void XxResources::setCommandSwitch( 
   XxCommand       cmdId,
   XxCommandSwitch optId,
   bool            setit
)
{
   QString cmd = getCommand( cmdId );
   QString opt = getCommandSwitch( optId );

   if ( setit == true ) {
      XxOptionsDialog::addToCommand( cmd, opt );
   }
   else {
      XxOptionsDialog::removeFromCommand( cmd, opt );
   }

   setCommand( cmdId, cmd );
}

//------------------------------------------------------------------------------
//
void XxResources::toggleCommandSwitch( 
   XxCommand       cmdId,
   XxCommandSwitch optId
)
{
   QString cmd = getCommand( cmdId );
   QString opt = getCommandSwitch( optId );

   if ( ! XxOptionsDialog::isInCommand( cmd, opt ) ) {
      XxOptionsDialog::addToCommand( cmd, opt );
   }
   else {
      XxOptionsDialog::removeFromCommand( cmd, opt );
   }

   setCommand( cmdId, cmd );
}

//------------------------------------------------------------------------------
//
XxQuality XxResources::getQuality( const QString& command ) const
{
   switch ( XxOptionsDialog::isInCommand( 
      command,
      getCommandSwitch( CMDSW_FILES_QUALITY_NORMAL ),
      getCommandSwitch( CMDSW_FILES_QUALITY_FASTEST ),
      getCommandSwitch( CMDSW_FILES_QUALITY_HIGHEST )
   ) ) {
      case 1: return QUALITY_NORMAL;
      case 2: return QUALITY_FASTEST;
      case 3: return QUALITY_HIGHEST;
   }

   // In other cases, just return normal, whatever.  The user can definitely
   // push it around, but there's no reason to barf for this little fluff.
   return QUALITY_NORMAL;
}

//------------------------------------------------------------------------------
//
void XxResources::setQuality( QString& command, XxQuality quality ) const
{
   QString opt1 = getCommandSwitch( CMDSW_FILES_QUALITY_NORMAL );
   QString opt2 = getCommandSwitch( CMDSW_FILES_QUALITY_FASTEST );
   QString opt3 = getCommandSwitch( CMDSW_FILES_QUALITY_HIGHEST );

   switch ( quality ) {
      case QUALITY_NORMAL: {
         XxOptionsDialog::setOneOfInCommand( command, opt1, opt2, opt3 );
      } break;
      case QUALITY_FASTEST: {
         XxOptionsDialog::setOneOfInCommand( command, opt2, opt1, opt3 );
      } break;
      case QUALITY_HIGHEST: {
         XxOptionsDialog::setOneOfInCommand( command, opt3, opt1, opt2 );
      } break;
   }
}

//------------------------------------------------------------------------------
//
void XxResources::setTag( XxTag tagId, const QString& tag )
{
   _tags[ int(tagId) ] = tag;
   emit changed();
}

//------------------------------------------------------------------------------
//
void XxResources::setColor(
   const XxColor  colorType,
   const bool     fore,
   const QString& colorstr
)
{
   if ( qApp != 0 ) { // protect setNamedColor() in case we have no display.
      if ( fore ) {
         _foreColors[ int(colorType) ].setNamedColor( colorstr );
      }
      else {
         _backColors[ int(colorType) ].setNamedColor( colorstr );
      }
   }
   emit changed();
}

//------------------------------------------------------------------------------
//
void XxResources::setColor(
   const XxColor colorType,
   const bool    fore,
   const QColor& color
)
{
   if ( fore ) {
      _foreColors[ int(colorType) ] = color;
   }
   else {
      _backColors[ int(colorType) ] = color;
   }
   emit changed();
}

//------------------------------------------------------------------------------
//
void XxResources::setBoolOpt( const XxBoolOpt opt, const bool value )
{
   XX_ASSERT( 0 <= opt && opt < BOOL_LAST );
   _boolOpts[ int(opt) ] = value;

   emit changed();
}

//------------------------------------------------------------------------------
//
bool XxResources::toggleBoolOpt( const XxBoolOpt opt )
{
   int ibool = int(opt);
   _boolOpts[ ibool ] = ! _boolOpts[ ibool ];
   emit changed();
   return _boolOpts[ ibool ];
}

//------------------------------------------------------------------------------
//
void XxResources::setShowOpt( const XxShowOpt opt, const bool value )
{
   _showOpts[ int(opt) ] = value;
   emit changed();
}

//------------------------------------------------------------------------------
//
bool XxResources::toggleShowOpt( const XxShowOpt opt )
{
   int ibool = int(opt);
   _showOpts[ ibool ] = ! _showOpts[ ibool ];
   emit changed();
   return _showOpts[ ibool ];
}

//------------------------------------------------------------------------------
//
void XxResources::setTabWidth( uint tabWidth )
{
   _tabWidth = tabWidth;
   emit changed();
}

//------------------------------------------------------------------------------
//
void XxResources::setOverviewFileWidth( uint w )
{
   _overviewFileWidth = w;
   emit changed();
}

//------------------------------------------------------------------------------
//
void XxResources::setOverviewSepWidth( uint w )
{
   _overviewSepWidth = w;
   emit changed();
}

//------------------------------------------------------------------------------
//
void XxResources::setVerticalLinePos( uint vlinePos )
{
   _verticalLinePos = vlinePos;
   emit changed();
}

//------------------------------------------------------------------------------
//
void XxResources::setClipboardFormat( const QString& format )
{
   _clipboardFormat = format;
   emit changed();
}

//------------------------------------------------------------------------------
//
void XxResources::setIgnoreFile( XxIgnoreFile ignoreFile )
{
   _ignoreFile = ignoreFile;
   emit changed();
}

//------------------------------------------------------------------------------
//
bool XxResources::compareFonts( const QFont& f1, const QFont& f2 )
{
   if ( f1.rawMode() || f2.rawMode() ) {
      return f1.rawName() == f2.rawName();
   }
   return f1 == f2;
}

XX_NAMESPACE_END

