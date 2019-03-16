//! @file     Resize.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

#define FI_RGBA_ALPHA	3
#define FI_RGBA_RED		2
#define FI_RGBA_GREEN	1
#define FI_RGBA_BLUE	0

// --------------------------------------------------------------------------------------------------------------
// WeightsTable Implementation
// --------------------------------------------------------------------------------------------------------------

WeightsTable::WeightsTable( GenericFilter *pFilter, unsigned uDstSize, unsigned uSrcSize)
{
	double dWidth;
	double dFScale;
	const double dFilterWidth = pFilter->GetWidth();

	// scale factor
	const double dScale = double(uDstSize) / double(uSrcSize);

	if(dScale < 1.0) {
		// minification
		dWidth = dFilterWidth / dScale; 
		dFScale = dScale; 
	} else {
		// magnification
		dWidth = dFilterWidth; 
		dFScale = 1.0; 
	}

	// allocate a new line contributions structure
	//
	// window size is the number of sampled pixels
	m_WindowSize = 2 * (int)ceil(dWidth) + 1; 
	// length of dst line (no. of rows / cols) 
	m_LineLength = uDstSize; 

	 // allocate list of contributions 
	m_WeightTable = (Contribution*)malloc(m_LineLength * sizeof(Contribution));
	for(unsigned u = 0; u < m_LineLength; u++) {
		// allocate contributions for every pixel
		m_WeightTable[u].Weights = (double*)malloc(m_WindowSize * sizeof(double));
	}

	// offset for discrete to continuous coordinate conversion
	const double dOffset = (0.5 / dScale);

	for(unsigned u = 0; u < m_LineLength; u++) {
		// scan through line of contributions

		// inverse mapping (discrete dst 'u' to continous src 'dCenter')
		const double dCenter = (double)u / dScale + dOffset;

		// find the significant edge points that affect the pixel
		const int iLeft = MAX(0, (int)(dCenter - dWidth + 0.5));
		const int iRight = MIN((int)(dCenter + dWidth + 0.5), int(uSrcSize));

		m_WeightTable[u].Left = iLeft; 
		m_WeightTable[u].Right = iRight;

		double dTotalWeight = 0;  // sum of weights (initialized to zero)
		for(int iSrc = iLeft; iSrc < iRight; iSrc++) {
			// calculate weights
			const double weight = dFScale * pFilter->Filter(dFScale * ((double)iSrc + 0.5 - dCenter));
			// assert((iSrc-iLeft) < m_WindowSize);
			m_WeightTable[u].Weights[iSrc-iLeft] = weight;
			dTotalWeight += weight;
		}
		if((dTotalWeight > 0) && (dTotalWeight != 1)) {
			// normalize weight of neighbouring points
			for(int iSrc = iLeft; iSrc < iRight; iSrc++) {
				// normalize point
				m_WeightTable[u].Weights[iSrc-iLeft] /= dTotalWeight; 
			}
		}

		// simplify the filter, discarding null weights at the right
		{			
			int iTrailing = iRight - iLeft - 1;
			while(m_WeightTable[u].Weights[iTrailing] == 0) {
				m_WeightTable[u].Right--;
				iTrailing--;
				if(m_WeightTable[u].Right == m_WeightTable[u].Left) {
					break;
				}
			}
			
		}

	} // next dst pixel
}

WeightsTable::~WeightsTable() 
{
	for(unsigned u = 0; u < m_LineLength; u++) {
		// free contributions for every pixel
		free(m_WeightTable[u].Weights);
	}
	// free list of pixels contributions
	free(m_WeightTable);
}

// --------------------------------------------------------------------------------------------------------------
// ResizeEngine Implementation
// --------------------------------------------------------------------------------------------------------------

void ResizeEngine::horizontalFilter( _PIXEL_FORMAT pixel_format, _dword src_width, _dword src_pitch, const _byte* src_pixel, _dword height, _dword dst_width, _dword dst_pitch, _byte* dst_pixel )
{
	// allocate and calculate the contributions
	WeightsTable weightsTable(m_pFilter, dst_width, src_width);

	// step through rows
	switch ( pixel_format )
	{
		case _PF_R8G8B8:
		{
			// scale the 24-bit non-transparent image into a 24 bpp destination image
			for (unsigned y = 0; y < height; y++) 
			{
				// scale each row
				const _byte * const src_bits = src_pixel + y * src_pitch;
				_byte *dst_bits = dst_pixel + y * dst_pitch;

				for (unsigned x = 0; x < dst_width; x++) 
				{
					// loop through row
					const unsigned iLeft = weightsTable.getLeftBoundary(x);				// retrieve left boundary
					const unsigned iLimit = weightsTable.getRightBoundary(x) - iLeft;	// retrieve right boundary
					const _byte * pixel = src_bits + iLeft * 3;
					double r = 0, g = 0, b = 0;

					// for(i = iLeft to iRight)
					for (unsigned i = 0; i < iLimit; i++) {
						// scan between boundaries
						// accumulate weighted effect of each neighboring pixel
						const double weight = weightsTable.getWeight(x, i);
						r += (weight * (double)pixel[FI_RGBA_RED]);
						g += (weight * (double)pixel[FI_RGBA_GREEN]);
						b += (weight * (double)pixel[FI_RGBA_BLUE]);
						pixel += 3;
					}

					// clamp and place result in destination pixel
					dst_bits[FI_RGBA_RED]	= (_byte)Math::Clamp<int>((int)(r + 0.5), 0, 0xFF);
					dst_bits[FI_RGBA_GREEN]	= (_byte)Math::Clamp<int>((int)(g + 0.5), 0, 0xFF);
					dst_bits[FI_RGBA_BLUE]	= (_byte)Math::Clamp<int>((int)(b + 0.5), 0, 0xFF);
					dst_bits += 3;
				}
			}
		}
		break;

		case _PF_A8R8G8B8:
		{
			// scale the 32-bit transparent image
			// into a 32 bpp destination image
			for (unsigned y = 0; y < height; y++) {
				// scale each row
				const _byte * const src_bits = src_pixel + y * src_pitch;
				_byte *dst_bits = dst_pixel + y * dst_pitch;

				for (unsigned x = 0; x < dst_width; x++) {
					// loop through row
					const unsigned iLeft = weightsTable.getLeftBoundary(x);				// retrieve left boundary
					const unsigned iLimit = weightsTable.getRightBoundary(x) - iLeft;	// retrieve right boundary
					const _byte *pixel = src_bits + iLeft * 4;
					double r = 0, g = 0, b = 0, a = 0;

					// for(i = iLeft to iRight)
					for (unsigned i = 0; i < iLimit; i++) {
						// scan between boundaries
						// accumulate weighted effect of each neighboring pixel
						const double weight = weightsTable.getWeight(x, i);
						r += (weight * (double)pixel[FI_RGBA_RED]);
						g += (weight * (double)pixel[FI_RGBA_GREEN]);
						b += (weight * (double)pixel[FI_RGBA_BLUE]);
						a += (weight * (double)pixel[FI_RGBA_ALPHA]);
						pixel += 4;
					}

					// clamp and place result in destination pixel
					dst_bits[FI_RGBA_RED]	= (_byte)Math::Clamp<int>((int)(r + 0.5), 0, 0xFF);
					dst_bits[FI_RGBA_GREEN]	= (_byte)Math::Clamp<int>((int)(g + 0.5), 0, 0xFF);
					dst_bits[FI_RGBA_BLUE]	= (_byte)Math::Clamp<int>((int)(b + 0.5), 0, 0xFF);
					dst_bits[FI_RGBA_ALPHA]	= (_byte)Math::Clamp<int>((int)(a + 0.5), 0, 0xFF);
					dst_bits += 4;
				}
			}
		}
		break;
            
        default:
            break;
	}
}

void ResizeEngine::verticalFilter( _PIXEL_FORMAT pixel_format, _dword src_height, _dword src_pitch, const _byte* src_pixel, _dword width, _dword dst_height, _dword dst_pitch, _byte* dst_pixel )
{
	// allocate and calculate the contributions
	WeightsTable weightsTable(m_pFilter, dst_height, src_height);

	// step through columns
	_byte * const dst_base = dst_pixel;

	switch( pixel_format )
	{
		case _PF_R8G8B8:
		{
			// scale the 24-bit transparent image
			// into a 24 bpp destination image
			const _byte *const src_base = src_pixel;

			for (unsigned x = 0; x < width; x++) 
			{
				// work on column x in dst
				const unsigned index = x * 3;
				_byte *dst_bits = dst_base + index;

				// scale each column
				for (unsigned y = 0; y < dst_height; y++) {
					// loop through column
					const unsigned iLeft = weightsTable.getLeftBoundary(y);				// retrieve left boundary
					const unsigned iLimit = weightsTable.getRightBoundary(y) - iLeft;	// retrieve right boundary
					const _byte *src_bits = src_base + iLeft * src_pitch + index;
					double r = 0, g = 0, b = 0;

					for (unsigned i = 0; i < iLimit; i++) {
						// scan between boundaries
						// accumulate weighted effect of each neighboring pixel
						const double weight = weightsTable.getWeight(y, i);
						r += (weight * (double)src_bits[FI_RGBA_RED]);
						g += (weight * (double)src_bits[FI_RGBA_GREEN]);
						b += (weight * (double)src_bits[FI_RGBA_BLUE]);
						src_bits += src_pitch;
					}

					// clamp and place result in destination pixel
					dst_bits[FI_RGBA_RED]	= (_byte)Math::Clamp<int>((int) (r + 0.5), 0, 0xFF);
					dst_bits[FI_RGBA_GREEN]	= (_byte)Math::Clamp<int>((int) (g + 0.5), 0, 0xFF);
					dst_bits[FI_RGBA_BLUE]	= (_byte)Math::Clamp<int>((int) (b + 0.5), 0, 0xFF);
					dst_bits += dst_pitch;
				}
			}
		}
		break;

		case _PF_A8R8G8B8:
		{
			// scale the 32-bit transparent image
			// into a 32 bpp destination image
			const _byte *const src_base = src_pixel;

			for (unsigned x = 0; x < width; x++) 
			{
				// work on column x in dst
				const unsigned index = x * 4;
				_byte *dst_bits = dst_base + index;

				// scale each column
				for (unsigned y = 0; y < dst_height; y++) {
					// loop through column
					const unsigned iLeft = weightsTable.getLeftBoundary(y);				// retrieve left boundary
					const unsigned iLimit = weightsTable.getRightBoundary(y) - iLeft;	// retrieve right boundary
					const _byte *src_bits = src_base + iLeft * src_pitch + index;
					double r = 0, g = 0, b = 0, a = 0;

					for (unsigned i = 0; i < iLimit; i++) {
						// scan between boundaries
						// accumulate weighted effect of each neighboring pixel
						const double weight = weightsTable.getWeight(y, i);
						r += (weight * (double)src_bits[FI_RGBA_RED]);
						g += (weight * (double)src_bits[FI_RGBA_GREEN]);
						b += (weight * (double)src_bits[FI_RGBA_BLUE]);
						a += (weight * (double)src_bits[FI_RGBA_ALPHA]);
						src_bits += src_pitch;
					}

					// clamp and place result in destination pixel
					dst_bits[FI_RGBA_RED]	= (_byte)Math::Clamp<int>((int) (r + 0.5), 0, 0xFF);
					dst_bits[FI_RGBA_GREEN]	= (_byte)Math::Clamp<int>((int) (g + 0.5), 0, 0xFF);
					dst_bits[FI_RGBA_BLUE]	= (_byte)Math::Clamp<int>((int) (b + 0.5), 0, 0xFF);
					dst_bits[FI_RGBA_ALPHA]	= (_byte)Math::Clamp<int>((int) (a + 0.5), 0, 0xFF);
					dst_bits += dst_pitch;
				}
			}
		}
		break;
            
        default:
            break;
	}
}

_void ResizeEngine::Scale( IImageFile* src, unsigned dst_width, unsigned dst_height, _dword dst_pitch, _byte* dst_pixel )
{
	_dword			src_width			= src->GetWidth( );
	_dword			src_height			= src->GetHeight( );
	_dword			src_pitch			= src->GetPitch( );
	_PIXEL_FORMAT	src_pixel_format	= src->GetPixelFormat( );
	const _byte*	src_pixel			= src->GetPixelBuffer( );

	Scale( src_width, src_height, src_pitch, src_pixel_format, src_pixel, dst_width, dst_height, dst_pitch, dst_pixel );
} 

_void ResizeEngine::Scale( _dword src_width, _dword src_height, _dword src_pitch, _PIXEL_FORMAT src_pixel_format, const _byte* src_pixel, unsigned dst_width, unsigned dst_height, _dword dst_pitch, _byte* dst_pixel )
{
	MemArrayPtr< _byte > tmp;
	_dword tmp_pitch = 0;

	if (dst_width <= src_width) 
	{
		// xy filtering
		// -------------

		if (src_width != dst_width) 
		{
			if (src_height != dst_height) 
			{
				tmp_pitch = dst_pitch;
				tmp.Create( dst_pitch * src_height );
			}
			else
			{
				tmp_pitch = dst_pitch;
				tmp.EnableAutoDelete( _false );
				tmp.SetPointer( dst_pixel );
			}

			// scale source image horizontally into temporary (or destination) image
			horizontalFilter(src_pixel_format, src_width, src_pitch, src_pixel, src_height, dst_width, dst_pitch, tmp.GetPointer( ));
		}
		else
		{
			tmp_pitch = src_pitch;
			tmp.EnableAutoDelete( _false );
			tmp.SetPointer( (_byte*)src_pixel );
		}

		if (src_height != dst_height) 
		{
			// source and destination heights are different so, scale
			// temporary (or source) image vertically into destination image
			verticalFilter(src_pixel_format, src_height, tmp_pitch, tmp.GetPointer( ), dst_width, dst_height, dst_pitch, dst_pixel);
		}
	} 
	else 
	{
		// yx filtering
		// -------------

		if (src_height != dst_height) 
		{
			if (src_width != dst_width) 
			{
				tmp_pitch = dst_pitch;
				tmp.Create( dst_pitch * dst_height );
			}
			else
			{
				tmp_pitch = dst_pitch;
				tmp.EnableAutoDelete( _false );
				tmp.SetPointer( dst_pixel );
			}

			// scale source image vertically into temporary (or destination) image
			verticalFilter(src_pixel_format, src_height, src_pitch, src_pixel, src_width, dst_height, dst_pitch, tmp.GetPointer( ));
		}
		else
		{
			tmp_pitch = src_pitch;
			tmp.EnableAutoDelete( _false );
			tmp.SetPointer( (_byte*)src_pixel );
		}

		if (src_width != dst_width) 
		{
			// source and destination heights are different so, scale
			// temporary (or source) image horizontally into destination image
			horizontalFilter(src_pixel_format, src_width, tmp_pitch, tmp.GetPointer( ), dst_height, dst_width, dst_pitch, dst_pixel);
		}
	}
}


