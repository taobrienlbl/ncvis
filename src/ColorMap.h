///////////////////////////////////////////////////////////////////////////////
///
///	\file    ColorMap.h
///	\author  Paul Ullrich
///	\version June 27, 2022
///

#ifndef _COLORMAP_H_
#define _COLORMAP_H_


#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "Exception.h"
#include <string>
#include <vector>
#include <cmath>

#define DEFAULT_COLORMAP "thermal"

////////////////////////////////////////////////////////////////////////////////

///	<summary>
///		A data structure specifying a colormap.
///	</summary>
class ColorMap : public std::vector< std::vector<unsigned char> > {

public:
	///	<summary>
	///		Sample the colormap.
	///	</summary>
	inline void Sample(
		float dValue,
		float dMinValue,
		float dMaxValue,
		unsigned char & cR,
		unsigned char & cG,
		unsigned char & cB
	) {
		int ixColor = static_cast<int>((dValue - dMinValue) / (dMaxValue - dMinValue) * size());

		if (ixColor < 0) {
			ixColor = 0;
		} else if (ixColor >= size()) {
			ixColor = size()-1;
		}

		cR = (*this)[ixColor][0];
		cG = (*this)[ixColor][1];
		cB = (*this)[ixColor][2];
	}

	///	<summary>
	///		Sample the colormap with a power scaling factor.
	///	</summary>
	inline void SampleWithScaling(
		float dValue,
		float dMinValue,
		float dMaxValue,
		float dScalingFactor,
		unsigned char & cR,
		unsigned char & cG,
		unsigned char & cB
	) {
		float dAlpha = (dValue - dMinValue) / (dMaxValue - dMinValue);
		if (dAlpha < 0.0) {
			dAlpha = 0.0;
		} else if (dAlpha > 1.0) {
			dAlpha = 1.0;
		}
		dAlpha = std::pow(dAlpha, dScalingFactor);

		int ixColor = static_cast<int>(dAlpha * size());

		if (ixColor < 0) {
			ixColor = 0;
		} else if (ixColor >= size()) {
			ixColor = size()-1;
		}

		cR = (*this)[ixColor][0];
		cG = (*this)[ixColor][1];
		cB = (*this)[ixColor][2];
	}

};

////////////////////////////////////////////////////////////////////////////////

class ColorMapLibrary {
public:
	///	<summary>
	///		Constructor.
	///	</summary>
	ColorMapLibrary(
		const wxString & strResourceDir
	);

	///	<summary>
	///		Get the number of colormaps in the library.
	///	</summary>
	size_t GetColorMapCount();

	///	<summary>
	///		Get colormap name from index.
	///	</summary>
	const wxString & GetColorMapName(
		size_t ix
	);

	///	<summary>
	///		Generate the specified colormap.
	///	</summary>
	void GenerateColorMap(
		const wxString & strColorMap,
		ColorMap & colormap
	) const;

private:
	///	<summary>
	///		Directory containing colormaps.
	///	</summary>
	wxString m_wxstrResourceDir;

	///	<summary>
	///		List of colormap names.
	///	</summary>
	std::vector<wxString> m_vecColorMapNames;
};

////////////////////////////////////////////////////////////////////////////////

#endif // _COLORMAP_H_
