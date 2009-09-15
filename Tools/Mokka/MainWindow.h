/* 
 * The Biomechanical ToolKit
 * Copyright (c) 2009, Arnaud Barré
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *     * Redistributions of source code must retain the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *     * Neither the name(s) of the copyright holders nor the names
 *       of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written
 *       permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef MainWindow_h
#define MainWindow_h

#include "ui_MainWindow.h"
#include "Metadata.h"

#include <QTimer>
#include <QUndoStack>

#include <btkProcessObject.h>
#include <btkVTKAxesWidget.h>

#include <map>

#include <vtkObject.h>
#include <vtkRenderer.h>
#include <vtkMapperCollection.h>
#include <vtkEventQtSlotConnect.h>

class vtkStreamingDemandDrivenPipelineCollection;
class vtkProcessMap;

class MainWindow : public QMainWindow, public Ui::MainWindow
{
  Q_OBJECT
  
public:
  MainWindow(QWidget* parent = 0);
  ~MainWindow();

  void initialize();

protected:
    void closeEvent(QCloseEvent* event);
    bool eventFilter(QObject* obj, QEvent* event);

private Q_SLOTS:
  // Qt
  void about();
  void editMetadata();
  void openRecentFile();
  void clearRecentFiles();
  void openFile();
  void closeFile();
  void changePlaybackParameters();
  void changeGroundOrientation();
  void updateDisplay(int frame);
  void updateActiveEvent(int frame);
  void updateMarkerRadiusSpinBox(int v);
  void toggleTimer();
  void displayPreviousFrame();
  void displayNextFrame();
  void toggleMarkersVisibilityButtons();
  void showSelectedMarkers();
  void hideSelectedMarkers();
  void showAllMarkers();
  void hideAllMarkers();
  void updateMarkerVisibility(QTableWidgetItem* item);
  void updateMarkerRadius(double r);
  void updateMarkerColor();
  void displayMarkerProperties();
  void toggleMarkerProperties();
  void displayEventInformations();
  void toggleEventInformations();
  void updateEventsButtonsState();
  void showEvent();
  void circleSelectedMarkers();
  void markersDockLocationChanged(Qt::DockWidgetArea area);
  void eventsDockLocationChanged(Qt::DockWidgetArea area);
  // Qt / VTK
  void updateDisplayedMarkersList(vtkObject* caller, unsigned long vtk_event, void* client_data, void* call_data);
  void selectPickedMarker(vtkObject* caller, unsigned long vtk_event, void* client_data, void* call_data);
  void selectPickedMarkers(vtkObject* caller, unsigned long vtk_event, void* client_data, void* call_data);

private:
  void loadFile(const QString& filename);
  void readSettings(); 
  void writeSettings();
  void updateRecentFileActions();
  void setCurrentFile(const QString& rFilename);
  bool isOkToContinue();
  void displayPreviousFrame(int step);
  void displayNextFrame(int step);
  
  int m_FirstFrame;
  std::map<int, btk::ProcessObject::Pointer> m_BTKProc;
  vtkProcessMap* mp_VTKProc;
  Metadata* mp_MetadataDlg;
  btk::VTKAxesWidget* mp_AxesWidget;
  vtkRenderer* mp_Renderer;
  vtkMapperCollection* mp_Mappers;
  vtkStreamingDemandDrivenPipelineCollection* mp_Syncro;
  vtkEventQtSlotConnect* mp_EventQtSlotConnections;
  int m_PlaybackStep;
  int m_PlaybackDelay;

  QActionGroup* mp_PlaybackSpeedActionGroup;
  QActionGroup* mp_GroundOrientationActionGroup;
  QString m_LastDirectory;
  QTimer* mp_Timer;
  enum { maxRecentFiles = 10 };
  QStringList m_RecentFiles;
  QAction* mp_ActionRecentFiles[maxRecentFiles];
  QAction* mp_ActionSeparatorRecentFiles;
  QUndoStack* mp_UndoStack;
  QIcon* mp_PlayIcon;
  QIcon* mp_PauseIcon;
  QIcon* mp_DownArrow;
  QIcon* mp_RightArrow;
};
#endif // MainWindow_h