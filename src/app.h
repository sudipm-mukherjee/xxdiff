/******************************************************************************\
 * $Id: app.h 498 2002-02-11 02:25:21Z blais $
 * $Date: 2002-02-10 21:25:21 -0500 (Sun, 10 Feb 2002) $
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
 ******************************************************************************/

#ifndef INCL_XXDIFF_APP
#define INCL_XXDIFF_APP

/*==============================================================================
 * EXTERNAL DECLARATIONS
 *============================================================================*/

#ifndef INCL_XXDIFF_DEFS
#include <defs.h>
#endif

#ifndef INCL_XXDIFF_LINE
#include <line.h>
#endif

#ifndef INCL_XXDIFF_RESOURCES
#include <resources.h>
#endif

#ifndef INCL_XXDIFF_RESPARSER
#include <resParser.h>
#endif

#ifndef INCL_QT_QAPPLICATION
#include <qapplication.h>
#define INCL_QT_QAPPLICATION
#endif

#ifndef INCL_STD_MEMORY
#include <memory>
#define INCL_STD_MEMORY
#endif

#ifndef INCL_STD_LIST
#include <list>
#define INCL_STD_LIST
#endif

/*==============================================================================
 * FORWARD DECLARATIONS
 *============================================================================*/

class QMainWindow;
class QSocketNotifier;
class QToolBar;
class QMessageBox;
class QSplitter;
class QLabel;
class QPopupMenu;

XX_NAMESPACE_BEGIN

/*==============================================================================
 * FORWARD DECLARATIONS
 *============================================================================*/

class XxCmdline;
class XxOverview;
class XxLineNumbers;
class XxText;
class XxMergedFrame;
class XxMergedWindow;
class XxDiffs;
class XxBuffer;
class XxResources;
class XxOptionsDialog;
class XxSearchDialog;
class XxCentralFrame;

/*==============================================================================
 * CLASS XxApp
 *============================================================================*/

// <summary> The main application </summary>

class XxApp : public QApplication {

   Q_OBJECT

public:

   /*----- types and enumerations -----*/

   enum { MAX_MENUIDS = 256 };

   /*----- member functions -----*/

   // Constructor.
   XxApp( int& argc, char** argv, const XxCmdline& );

   // Destructor.
   virtual ~XxApp();

   // See base clas.
   int exec();

   // Returns the number of files.
   uint getNbFiles() const;

   // Returns the file for requested buffer.
   XxBuffer* getBuffer( const XxFno no ) const;

   // Returns an array of the file pointers.
   const std::auto_ptr<XxBuffer>* getBuffers() const;

   // Returns the maximum number of digits for line numbers of all files.
   uint getMaxDigits() const;

   // Returns the resources.
   const XxResources& getResources() const;

   // Returns the diffs.
   XxDiffs* getDiffs() const;

   // Returns the number of lines in the diffs.
   XxDln getNbLines() const;

   // Get/set the cursor line.  Returns the old cursor line.  Value will remain
   // unchanged if an out-of-bounds value is asked for.  Note: may scroll to
   // insure that the current line is visible.
   // <group>
   XxDln setCursorLine( const XxDln lineNo, const bool recenter = false );
   XxDln getCursorLine() const;
   // </group>

   // Make sure that the cursor line is visible between the given boundaries.
   // Return true if the cursor has been moved.
   bool adjustCursor( const int topLine, const int bottomLine );

   // Adjusts line number size.
   void adjustLineNumbers();

   // Returns the main window's size.
   QRect getMainWindowGeometry() const;

   // Returns a reference on the view popup menu.
   QPopupMenu* getViewPopup( const XxLine& line ) const;

   // Returns the return value to send back to caller.
   int getReturnValue() const;

   // Synchronizes the UI menus (toggles) with the resources.
   void synchronizeUI();

   // Changes the tab width.
   void setTabWidth( const int newTabWidth );

   // Get the latest computed value for the longest line.  See
   // computeTextWidth().
   uint getTextWidth() const;

   // Forces recomputation of the text width.
   void invalidateTextWidth();

public slots:

   // Redraws the text widgets.
   void updateWidgets();

   // On a number of line change in diffs.
   void onNbLinesChanged();

   // This gets called in the main thread when the edit is done.
   void editDone();

   // Most menu items.
   // <group>
   void openLeft();
   void openMiddle();
   void openRight();
   void saveAsLeft();
   void saveAsMiddle();
   void saveAsRight();
   void saveAsMerged();
   void saveAs();
   void saveSelectedOnly();
   void editLeft();
   void editMiddle();
   void editRight();
   void quit();
   void search();
   void searchForward();
   void searchBackward();
   void redoDiff();
   void editDiffOptions();
   void editDisplayOptions();
   void diffFilesAtCursor();
   void copyFileLeftToRight();
   void copyFileRightToLeft();
   void removeFileLeft();
   void removeFileRight();
   void nextDifference();
   void previousDifference();
   void nextUnselected();
   void previousUnselected();
   void selectGlobalLeft();
   void selectGlobalMiddle();
   void selectGlobalRight();
   void selectGlobalNeither();
   void selectGlobalUnselect();
   void selectGlobalUnselectedLeft();
   void selectGlobalUnselectedMiddle();
   void selectGlobalUnselectedRight();
   void selectGlobalUnselectedNeither();
   int  selectGlobalMerge();
   void selectRegionLeft();
   void selectRegionMiddle();
   void selectRegionRight();
   void selectRegionNeither();
   void selectRegionUnselect();
   void selectRegionLeftAndNext();
   void selectRegionMiddleAndNext();
   void selectRegionRightAndNext();
   void selectRegionNeitherAndNext();
   void regionSplitSwapJoin();
   void selectLineLeft();
   void selectLineMiddle();
   void selectLineRight();
   void selectLineNeither();
   void selectLineUnselect();
   void tabsAt3();
   void tabsAt4();
   void tabsAt8();
   void ignoreTrailing();
   void ignoreWhitespace();
   void ignoreCase();
   void ignoreBlankLines();
   void hideCarriageReturns();
   void dirDiffRecursive();
   void ignoreFileChanges();
   void qualityNormal();
   void qualityFastest();
   void qualityHighest();
   void toggleShowFilenames();
   void togglePaneMergedView();
   void togglePopupMergedView();
   void toggleToolbar();
   void toggleLineNumbers();
   void toggleVerticalLine();
   void toggleOverview();
   void hordiffTypeNone();
   void hordiffTypeSingle();
   void hordiffTypeMultiple();
   void hordiffTypeUpdate();
   void toggleIgnoreHorizontalWs();
   void toggleFormatClipboardText();
   void ignoreFileNone();
   void ignoreFileLeft();
   void ignoreFileMiddle();
   void ignoreFileRight();
   void helpManPage();
   void helpGenInitFile();
   void helpAbout();
   // </group>

   // Keyboard accelerators cursor motion callbacks.
   // <group>
   void pageDown(); 
   void pageUp(); 
   void cursorDown(); 
   void cursorUp(); 
   void cursorTop(); 
   void cursorBottom(); 
   // </group>

signals:

   // Signal emitted when the cursor changes line.
   void cursorChanged( int cursorLine );

   // Signal emitted when the size of the displayed text changes.
   void textSizeChanged();

private:

   /*----- friends -----*/

   friend class XxOptionsDialog; // For non-const access to the resources.

   /*----- member functions -----*/

   // Creates a new resources object and parses the rcfile and cmdline
   // resources.
   XxResources* buildResources() const;

   // Reads in a file.
   std::auto_ptr<XxBuffer> readFile( 
      const XxFno    no, 
      const QString& filename,
      const QString& displayFilename,
      bool           isTemporary = false
   );

   // Processes the diff command, be really careful with this.  Returns false if
   // there was an error.
   bool processDiff();

   // Re-does the diff, changing the UI as little as possible.
   void onRedoDiff();

   // Creates the interface.
   // <group>
   void createUI();
   void createOnContextHelp();
   void createMenus();
   QToolBar* createToolbar();
   // </group>

   // Output diff errors.
   void outputDiffErrors( const QString& errors );

   // Compute the number of pixels of the longest line.
   uint computeTextWidth() const;
   
   // Tries to save the selected contents to the specified filename.  If ask is
   // true, ask the user for the filename (and use filename as default value).
   void saveToFile( const QString& filename, const bool ask );

   // Edits the said file, and add signal handler to catch children exit, and
   // notify.
   void editFile( const QString& filename );

   // Reopen file at no and rebuild diffs and update and all.
   void openFile( const XxFno no );

   // Copy file from directory diffs.
   void copyFile( XxFno nnno ) const;

   // Remove file from directory diffs.
   void removeFile( XxFno nnno ) const;

   // Private non-const version of resource access (for dialogs).
   XxResources& getResourcesNC();

   // Implements apply-and-move-to-next algorithm.
   void selectAndNext( XxLine::Selection selection );

   // Check if the selections are all of the specified no.  If so, ask the user
   // to confirm, returns true if we should save.
   bool validateNeedToSave( uint no ) const;

   // Implementation of the ignoreXXX() methods.
   void setFileDiffOptions( XxCommandSwitch );

   // Implementation of the qualityXXX() methods.
   void setQuality( XxQuality );

   // Get the merged filename.
   QString getMergedFilename() const;

   /*----- static member functions -----*/

   // Reads the file arguments, returns the number of files to be read, creates
   // temporary files if necessary (from stdin).
   static uint processFileNames( 
      const XxCmdline& cmdline,
      QString          filenames[3],
      QString          displayFilenames[3],
      bool             created[3],
      bool&            directories
   );

   // SIGCHLD handler for editor.
   static void handlerSIGCHLD( int );

   /*----- static data members -----*/

   static int              _sockfd;
   static QSocketNotifier* _socketNotifier;

   /*----- data members -----*/

   // UI widgets.
   bool                    _isUICreated;
   bool                    _dontShow;
   int                     _returnValue;

   QStyle*                 _style;
   QMainWindow*            _mainWindow;
   QMessageBox*            _diffErrorsMsgBox;
   QSplitter*              _splitter;
   XxMergedFrame*          _paneMergedView;
   XxMergedWindow*         _popupMergedView;
   XxCentralFrame*         _central;
   QPopupMenu*             _viewPopup;
   QPopupMenu*             _optionsMenu;
   QPopupMenu*             _displayMenu;
   QPopupMenu*             _hordiffMenu;
   QPopupMenu*             _windowsMenu;
   int                     _menuids[ MAX_MENUIDS ];
   QWidget*                _overviewArea;
   QLabel*                 _remUnselView;
   XxOverview*             _overview;
   XxSearchDialog*         _searchDialog;
   XxOptionsDialog*        _optionsDialog;
   QToolBar*               _toolbar;
   mutable uint            _textWidth;
   XxDln                   _cursorLine;
                                	
   //
   // Real data.
   //
   int                     _nbFiles;
   std::auto_ptr<XxBuffer> _files[3];
   std::auto_ptr<XxDiffs>  _diffs;
   bool                    _filesAreDirectories;

   XxResources*            _resources;

   // Data from parsing the cmdline.
   const XxCmdline&        _cmdline;

};

XX_NAMESPACE_END

#include <app.inline.h>

#endif

