///////////////////////////////////////////////////////////////////////////////
///
///	\file    wxNcVisFrame.h
///	\author  Paul Ullrich
///	\version June 27, 2022
///

#ifndef _WXNCVISFRAME_H_
#define _WXNCVISFRAME_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "wxImagePanel.h"
#include "ColorMap.h"
#include "GridDataSampler.h"

#include <map>
#include <vector>

////////////////////////////////////////////////////////////////////////////////

class wxNcVisExportDialog;
class wxGridBagSizer;

////////////////////////////////////////////////////////////////////////////////

///	<summary>
///		A class that manages the NcVis app frame.
///	</summary>
class wxNcVisFrame : public wxFrame {

public:
	///	<summary>
	///		Maximum number of dimensions per variable.
	///	</summary>
	static const int NcVarMaximumDimensions = 5;

public:
	///	<summary>
	///		Sampler options available.
	///	</summary>
	enum GridDataSamplerOption {
		GridDataSamplerOption_First = 0,
		GridDataSamplerOption_QuadTree = 0,
		GridDataSamplerOption_CubedSphereQuadTree = 1,
		GridDataSamplerOption_KDTree = 2,
		GridDataSamplerOption_Last = 2
	};

public:
	///	<summary>
	///		Constructor.
	///	</summary>
	wxNcVisFrame(
		const wxString & title,
		const wxPoint & pos,
		const wxSize & size,
		const wxString & wxstrNcVisResourceDir,
		const std::map<wxString, wxString> & mapOptions,
		const std::vector<wxString> & vecFilenames
	);

	///	<summary>
	///		Initialize the GridDataSampler.
	///	</summary>
	void InitializeGridDataSampler();

	///	<summary>
	///		Open the specified files.
	///	</summary>
	void OpenFiles(
		const std::vector<wxString> & strFilenames
	);

	///	<summary>
	///		Initialize the wxNcVisFrame.
	///	</summary>
	void InitializeWindow();

	///	<summary>
	///		Get the verbosity flag.
	///	</summary>
	bool IsVerbose() const {
		return m_fVerbose;
	}

	///	<summary>
	///		Get the NcVis resource directory.
	///	</summary>
	const wxString & GetResourceDir() const {
		return m_wxstrNcVisResourceDir;
	}

	///	<summary>
	///		Get the color map library.
	///	</summary>
	const ColorMapLibrary & GetColorMapLibrary() const {
		return m_colormaplib;
	}

	///	<summary>
	///		Load data from the active variable.
	///	</summary>
	void LoadData();

	///	<summary>
	///		Get a pointer to the data.
	///	</summary>
	const std::vector<float> & GetData() const {
		return m_data;
	}

	///	<summary>
	///		Check if the data has a missing value.
	///	</summary>
	bool DataHasMissingValue() const {
		return m_fDataHasMissingValue;
	}

	///	<summary>
	///		Get the missing value for the data.
	///	</summary>
	float GetMissingValueFloat() const {
		return m_dMissingValueFloat;
	}

	///	<summary>
	///		Map an array of sample coordinates in 1D to indices in
	///		the dimension variable of the active variable.
	///	</summary>
	void MapSampleCoords1DFromActiveVar(
		const std::vector<double> & dSample,
		long lDim,
		std::vector<int> & veccoordmap
	);

	///	<summary>
	///		Sample the data.
	///	</summary>
	void SampleData(
		const std::vector<double> & dSampleX,
		const std::vector<double> & dSampleY,
		std::vector<int> & imagemap
	);

	///	<summary>
	///		Set the bounds displayed.
	///	</summary>
	void SetDisplayedBounds(
		double dX0,
		double dX1,
		double dY0,
		double dY1
	);

	///	<summary>
	///		Reset the bounds using dimension data.
	///	</summary>
	void ResetBounds(
		int iDim = (-1),
		bool fRedraw = false
	);

	///	<summary>
	///		Update the data range displayed in the controls.
	///	</summary>
	void SetDisplayedDataRange(
		float dDataMin,
		float dDataMax
	);

	///	<summary>
	///		Set the data range using the min/max of visible data.
	///	</summary>
	void SetDataRangeByMinMax(
		bool fRedraw = false
	);

	///	<summary>
	///		Set the dimension value displayed.
	///	</summary>
	void SetDisplayedDimensionValue(
		long lDim,
		long lValue
	);

	///	<summary>
	///		Get the dimension value displayed.
	///	</summary>
	long GetDisplayedDimensionValue(
		long lDim
	);

	///	<summary>
	///		Set the status message.
	///	</summary>
	void SetStatusMessage(
		const wxString & strMessage,
		bool fIncludeVersion
	);

private:
	///	<summary>
	///		Callback triggered when Exit is selected in the menu.
	///	</summary>
	void OnExit(wxCommandEvent & event);

	///	<summary>
	///		Callback triggered when About is selected in the menu.
	///	</summary>
	void OnAbout(wxCommandEvent & event);

	///	<summary>
	///		Callback triggered when the window is closed.
	///	</summary>
	void OnClose(wxCloseEvent & event);

	///	<summary>
	///		Callback triggered when the data transform button is pressed.
	///	</summary>
	void OnDataTransClicked(wxCommandEvent & event);

	///	<summary>
	///		Callback triggered when the export button is pressed.
	///	</summary>
	void OnExportClicked(wxCommandEvent & event);

	///	<summary>
	///		Generate dimension controls for a given variable.
	///	</summary>
	void GenerateDimensionControls();

	///	<summary>
	///		Callback triggered when a new variable has been selected for rendering.
	///	</summary>
	void OnVariableSelected(wxCommandEvent & event);

	///	<summary>
	///		Callback triggered when the bounds of the domain have been edited.
	///	</summary>
	void OnBoundsChanged(wxCommandEvent & event);

	///	<summary>
	///		Callback triggered when the range has been edited.
	///	</summary>
	void OnRangeChanged(wxCommandEvent & event);

	///	<summary>
	///		Callback triggered when the range reset min/max button is pressed.
	///	</summary>
	void OnRangeResetMinMax(wxCommandEvent & event);

	///	<summary>
	///		Callback triggered when the dimension timer is triggered.
	///	</summary>
	void OnDimTimer(wxTimerEvent & event);

	///	<summary>
	///		Start animation of the specified dimension.
	///	</summary>
	void StartAnimation(long d);

	///	<summary>
	///		Stop animation.
	///	</summary>
	void StopAnimation();

	///	<summary>
	///		Callback triggered when a dimension button is pressed.
	///	</summary>
	void OnDimButtonClicked(wxCommandEvent & event);

	///	<summary>
	///		Callback triggered when an axes button is pressed.
	///	</summary>
	void OnAxesButtonClicked(wxCommandEvent & event);

	///	<summary>
	///		Callback triggered when the colormap combo is changed.
	///	</summary>
	void OnColorMapCombo(wxCommandEvent & event);

	///	<summary>
	///		Callback triggered when the gridlines combo is changed.
	///	</summary>
	void OnGridLinesCombo(wxCommandEvent & event);

	///	<summary>
	///		Callback triggered when the overlays combo is changed.
	///	</summary>
	void OnOverlaysCombo(wxCommandEvent & event);

	///	<summary>
	///		Callback triggered when the sampler combo is changed.
	///	</summary>
	void OnSamplerCombo(wxCommandEvent & event);

private:
	///	<summary>
	///		Button for changing data range.
	///	</summary>
	wxButton * m_wxDataTransButton;

	///	<summary>
	///		Combo boxes for choosing the variable.
	///	</summary>
	wxComboBox * m_vecwxVarSelector[NcVarMaximumDimensions];

	///	<summary>
	///		Text controls for indicating displayed bounds.
	///	</summary>
	wxTextCtrl * m_vecwxImageBounds[4];

	///	<summary>
	///		Buttons for indicating active axes.
	///	</summary>
	wxButton * m_vecwxActiveAxes[NcVarMaximumDimensions][3];

	///	<summary>
	///		Sizer for the panel.
	///	</summary>
	wxBoxSizer * m_panelsizer;

	///	<summary>
	///		Sizer containing all controls.
	///	</summary>
	wxBoxSizer * m_ctrlsizer;

	///	<summary>
	///		Sizer to the right of the controls menu.
	///	</summary>
	wxBoxSizer * m_rightsizer;

	///	<summary>
	///		Sizer containing variable dimensions.
	///	</summary>
	wxFlexGridSizer * m_vardimsizer;

	///	<summary>
	///		Text controls for indicating displayed bounds.
	///	</summary>
	wxTextCtrl * m_vecwxRange[2];

	///	<summary>
	///		Text controls for indicating dimension indices.
	///	</summary>
	wxTextCtrl * m_vecwxDimIndex[NcVarMaximumDimensions];

	///	<summary>
	///		Text controls for indicating dimension values.
	///	</summary>
	wxTextCtrl * m_vecwxDimValue[NcVarMaximumDimensions];

	///	<summary>
	///		Button for animating data.
	///	</summary>
	wxButton * m_vecwxPlayButton[NcVarMaximumDimensions];

	///	<summary>
	///		Button for exporting data.
	///	</summary>
	wxButton * m_wxExportButton;

	///	<summary>
	///		Image panel used to display data.
	///	</summary>
	wxImagePanel * m_imagepanel;

	///	<summary>
	///		Options frame.
	///	</summary>
	wxNcVisExportDialog * m_wxNcVisExportDialog;

	///	<summary>
	///		Dimension timer.
	///	</summary>
	wxTimer m_wxDimTimer;

private:
	///	<summary>
	///		Flag indicating verbose output is desired.
	///	</summary>
	bool m_fVerbose;

	///	<summary>
	///		Directory containing ncvis resources.
	///	</summary>
	wxString m_wxstrNcVisResourceDir;

	///	<summary>
	///		Command-line options.
	///	</summary>
	std::map<wxString, wxString> m_mapOptions;

	///	<summary>
	///		Color map library.
	///	</summary>
	ColorMapLibrary m_colormaplib;

	///	<summary>
	///		Grid data sampler used.
	///	</summary>
	GridDataSamplerOption m_egdsoption;

	///	<summary>
	///		Shapefiles present in ncvis resource dir.
	///	</summary>
	std::vector<wxString> m_vecNcVisResourceShpFiles;

	///	<summary>
	///		Filename being displayed.
	///	</summary>
	std::vector<wxString> m_vecFilenames;

	///	<summary>
	///		NetCDF file being worked on.
	///	</summary>
	std::vector<NcFile *> m_vecpncfiles;

	///	<summary>
	///		A data structure containing dimension values and units.
	///	</summary>
	class DimDataFileIdAndCoordMap : public std::map<size_t, std::vector<double> > {
		public:
			///	<summary>
			///		Get the units for this dimension.
			///	</summary>
			const std::string & units() const {
				return m_strUnits;
			}

			///	<summary>
			///		Get the calendar for this dimension.
			///	</summary>
			const std::string & calendar() const {
				return m_strCalendar;
			}

		public:
			///	<summary>
			///		Units for this dimension.
			///	</summary>
			std::string m_strUnits;

			///	<summary>
			///		Calendar for this dimension.
			///	</summary>
			std::string m_strCalendar;
	};

	///	<summary>
	///		Dimension data, stored persistently to avoid having to reload.
	///	</summary>
	typedef std::map<std::string, DimDataFileIdAndCoordMap> DimDataMap;
	DimDataMap m_mapDimData;

	///	<summary>
	///		Unstructured index dimension name.
	///	</summary>
	std::string m_strUnstructDimName;

	///	<summary>
	///		NetCDF variable currently loaded.
	///	</summary>
	NcVar * m_varActive;

	///	<summary>
	///		Bookmarked dimensions.
	///	</summary>
	std::map<std::string, long> m_mapDimBookmarks;

	///	<summary>
	///		Flag indicating currently loaded data is unstructured.
	///	</summary>
	bool m_fIsVarActiveUnstructured;

	///	<summary>
	///		Current auxiliary dimension indices for loaded variable.
	///	</summary>
	std::vector<long> m_lVarActiveDims;

	///	<summary>
	///		Currently displayed variable dimension indices.
	///	</summary>
	long m_lDisplayedDims[2];

	///	<summary>
	///		Variable dimension currently being animated.
	///	</summary>
	long m_lAnimatedDim;

	///	<summary>
	///		Map between variables found among files and file index where they can be
	///		found.  Variables are further indexed by number of dimensions.
	///	</summary>
	std::map<std::string, std::vector<size_t> > m_mapVarNames[10];

private:
	///	<summary>
	///		ColorMap index.
	///	</summary>
	size_t m_sColorMap;

	///	<summary>
	///		Class for sampling data on the grid using a quad tree.
	///	</summary>
	GridDataSamplerUsingQuadTree m_gdsqt;

	///	<summary>
	///		Class for sampling data on the grid using a cubed-sphere rooted quad tree.
	///	</summary>
	GridDataSamplerUsingCubedSphereQuadTree m_gdscsqt;

	///	<summary>
	///		Class for sampling data on the grid using a kd tree.
	///	</summary>
	GridDataSamplerUsingKDTree m_gdskd;

	///	<summary>
	///		Data being visualized.
	///	</summary>
	std::vector<float> m_data;

	///	<summary>
	///		A flag indicating the data has missing values.
	///	</summary>
	bool m_fDataHasMissingValue;

	///	<summary>
	///		Missing value.
	///	</summary>
	float m_dMissingValueFloat;

	wxDECLARE_EVENT_TABLE();
};

////////////////////////////////////////////////////////////////////////////////


#endif // _WXNCVISFRAME_H_
