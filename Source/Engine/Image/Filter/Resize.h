//! @file     Resize.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// WeightsTable
//----------------------------------------------------------------------------

class WeightsTable
{
private:
	struct Contribution
	{
		/// Normalized weights of neighboring pixels
		_double*	Weights;
		/// Bounds of source pixels window
		unsigned	Left, Right;
	};

private:
	/// Row (or column) of contribution weights 
	Contribution *m_WeightTable;
	/// Filter window size (of affecting source pixels) 
	unsigned m_WindowSize;
	/// Length of line (no. of rows / cols) 
	unsigned m_LineLength;

public:
	/** 
	Constructor<br>
	Allocate and compute the weights table
	@param pFilter Filter used for upsampling or downsampling
	@param uDstSize Length (in pixels) of the destination line buffer
	@param uSrcSize Length (in pixels) of the source line buffer
	*/
	WeightsTable(GenericFilter *pFilter, unsigned uDstSize, unsigned uSrcSize);

	/**
	Destructor<br>
	Destroy the weights table
	*/
	~WeightsTable();

	/** Retrieve a filter weight, given source and destination positions
	@param dst_pos Pixel position in destination line buffer
	@param src_pos Pixel position in source line buffer
	@return Returns the filter weight
	*/
	double getWeight(unsigned dst_pos, unsigned src_pos) {
		return m_WeightTable[dst_pos].Weights[src_pos];
	}

	/** Retrieve left boundary of source line buffer
	@param dst_pos Pixel position in destination line buffer
	@return Returns the left boundary of source line buffer
	*/
	unsigned getLeftBoundary(unsigned dst_pos) {
		return m_WeightTable[dst_pos].Left;
	}

	/** Retrieve right boundary of source line buffer
	@param dst_pos Pixel position in destination line buffer
	@return Returns the right boundary of source line buffer
	*/
	unsigned getRightBoundary(unsigned dst_pos) {
		return m_WeightTable[dst_pos].Right;
	}
};

//----------------------------------------------------------------------------
// ResizeEngine
//----------------------------------------------------------------------------

class ResizeEngine
{
private:
	//! Pointer to the FIR / IIR filter
	GenericFilter* m_pFilter;

private:
	void horizontalFilter( _PIXEL_FORMAT pixel_format, _dword src_width, _dword src_pitch, const _byte* src_pixel, _dword height, _dword dst_width, _dword dst_pitch, _byte* dst_pixel );
	void verticalFilter( _PIXEL_FORMAT pixel_format, _dword src_height, _dword src_pitch, const _byte* src_pixel, _dword width, _dword dst_height, _dword dst_pitch, _byte* dst_pixel );

public:
	ResizeEngine(GenericFilter* filter):m_pFilter(filter) {}
	~ResizeEngine() {}

public:
	_void Scale( IImageFile* src, unsigned dst_width, unsigned dst_height, _dword dst_pitch, _byte* dst_pixel );
	_void Scale( _dword src_width, _dword src_height, _dword src_pitch, _PIXEL_FORMAT src_pixel_format, const _byte* src_pixel, unsigned dst_width, unsigned dst_height, _dword dst_pitch, _byte* dst_pixel );
};

}