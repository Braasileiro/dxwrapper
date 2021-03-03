/**
* Copyright (C) 2021 Elisha Riedlinger
*
* This software is  provided 'as-is', without any express  or implied  warranty. In no event will the
* authors be held liable for any damages arising from the use of this software.
* Permission  is granted  to anyone  to use  this software  for  any  purpose,  including  commercial
* applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*   1. The origin of this software must not be misrepresented; you must not claim that you  wrote the
*      original  software. If you use this  software  in a product, an  acknowledgment in the product
*      documentation would be appreciated but is not required.
*   2. Altered source versions must  be plainly  marked as such, and  must not be  misrepresented  as
*      being the original software.
*   3. This notice may not be removed or altered from any source distribution.
*/

#define INITGUID
#define DIRECTINPUT_VERSION 0x0800

#include <d3d9.h>
#include <d3d9types.h>
#include <ddraw.h>
#include <ddrawex.h>
#include <d3d.h>
#include <d3dhal.h>
#include <dinput.h>
#include "ddraw\ddraw.h"
#include "Logging.h"

typedef enum _DIERR { } DIERR;

std::ofstream LOG;

// Get wrapper file name
void Logging::InitLog()
{
	if (!EnableLogging)
	{
		return;
	}

	static char wrappername[MAX_PATH];

	// Get module name
	HMODULE hModule = NULL;
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCTSTR)InitLog, &hModule);
	GetModuleFileName(hModule, wrappername, MAX_PATH);

	// Get process name
	char processname[MAX_PATH];
	GetModuleFileName(nullptr, processname, MAX_PATH);

	// Check if module name is the same as process name
	if (_stricmp(strrchr(wrappername, '\\') + 1, strrchr(processname, '\\') + 1) == 0)
	{
		strcpy_s(strrchr(wrappername, '\\') + 1, MAX_PATH - strlen(wrappername), "dxwrapper.dll");
	}

	// Remove extension and add dash (-)
	strcpy_s(strrchr(wrappername, '.'), MAX_PATH - strlen(wrappername), "-");

	// Add process name
	strcat_s(wrappername, MAX_PATH, strrchr(processname, '\\') + 1);

	// Change extension to .log
	strcpy_s(strrchr(wrappername, '.'), MAX_PATH - strlen(wrappername), ".log");

	// Set lower case
	for (int z = 0; z < MAX_PATH && wrappername[z] != '\0'; z++) { wrappername[z] = (char)tolower(wrappername[z]); }

	Open(wrappername);
}

std::ostream& operator<<(std::ostream& os, const D3DFORMAT& format)
{
	switch ((DWORD)format)
	{
	case 0:
		return os << "D3DFMT_UNKNOWN";
	case 20:
		return os << "D3DFMT_R8G8B8";
	case 21:
		return os << "D3DFMT_A8R8G8B8";
	case 22:
		return os << "D3DFMT_X8R8G8B8";
	case 23:
		return os << "D3DFMT_R5G6B5";
	case 24:
		return os << "D3DFMT_X1R5G5B5";
	case 25:
		return os << "D3DFMT_A1R5G5B5";
	case 26:
		return os << "D3DFMT_A4R4G4B4";
	case 27:
		return os << "D3DFMT_R3G3B2";
	case 28:
		return os << "D3DFMT_A8";
	case 29:
		return os << "D3DFMT_A8R3G3B2";
	case 30:
		return os << "D3DFMT_X4R4G4B4";
	case 31:
		return os << "D3DFMT_A2B10G10R10";
	case 32:
		return os << "D3DFMT_A8B8G8R8";
	case 33:
		return os << "D3DFMT_X8B8G8R8";
	case 34:
		return os << "D3DFMT_G16R16";
	case 35:
		return os << "D3DFMT_A2R10G10B10";
	case 36:
		return os << "D3DFMT_A16B16G16R16";
	case 40:
		return os << "D3DFMT_A8P8";
	case 41:
		return os << "D3DFMT_P8";
	case 50:
		return os << "D3DFMT_L8";
	case 51:
		return os << "D3DFMT_A8L8";
	case 52:
		return os << "D3DFMT_A4L4";
	case 60:
		return os << "D3DFMT_V8U8";
	case 61:
		return os << "D3DFMT_L6V5U5";
	case 62:
		return os << "D3DFMT_X8L8V8U8";
	case 63:
		return os << "D3DFMT_Q8W8V8U8";
	case 64:
		return os << "D3DFMT_V16U16";
	case 67:
		return os << "D3DFMT_A2W10V10U10";
	case MAKEFOURCC('U', 'Y', 'V', 'Y'):
		return os << "D3DFMT_UYVY";
	case MAKEFOURCC('R', 'G', 'B', 'G'):
		return os << "D3DFMT_R8G8_B8G8";
	case MAKEFOURCC('Y', 'U', 'Y', '2'):
		return os << "D3DFMT_YUY2";
	case MAKEFOURCC('G', 'R', 'G', 'B'):
		return os << "D3DFMT_G8R8_G8B8";
	case MAKEFOURCC('D', 'X', 'T', '1'):
		return os << "D3DFMT_DXT1";
	case MAKEFOURCC('D', 'X', 'T', '2'):
		return os << "D3DFMT_DXT2";
	case MAKEFOURCC('D', 'X', 'T', '3'):
		return os << "D3DFMT_DXT3";
	case MAKEFOURCC('D', 'X', 'T', '4'):
		return os << "D3DFMT_DXT4";
	case MAKEFOURCC('D', 'X', 'T', '5'):
		return os << "D3DFMT_DXT5";
	case 70:
		return os << "D3DFMT_D16_LOCKABLE";
	case 71:
		return os << "D3DFMT_D32";
	case 72:
		return os << "D3DFMT_S1D15";
	case 73:
		return os << "D3DFMT_D15S1";
	case 74:
		return os << "D3DFMT_S8D24";
	case 75:
		return os << "D3DFMT_D24S8";
	case 76:
		return os << "D3DFMT_X8D24";
	case 77:
		return os << "D3DFMT_D24X8";
	case 78:
		return os << "D3DFMT_X4S4D24";
	case 79:
		return os << "D3DFMT_D24X4S4";
	case 80:
		return os << "D3DFMT_D16";
	case 82:
		return os << "D3DFMT_D32F_LOCKABLE";
	case 83:
		return os << "D3DFMT_D24FS8";
	case 84:
		return os << "D3DFMT_D32_LOCKABLE";
	case 85:
		return os << "D3DFMT_S8_LOCKABLE";
	case 81:
		return os << "D3DFMT_L16";
	case 100:
		return os << "D3DFMT_VERTEXDATA";
	case 101:
		return os << "D3DFMT_INDEX16";
	case 102:
		return os << "D3DFMT_INDEX32";
	case 110:
		return os << "D3DFMT_Q16W16V16U16";
	case MAKEFOURCC('M', 'E', 'T', '1'):
		return os << "D3DFMT_MULTI2_ARGB8";
	case 111:
		return os << "D3DFMT_R16F";
	case 112:
		return os << "D3DFMT_G16R16F";
	case 113:
		return os << "D3DFMT_A16B16G16R16F";
	case 114:
		return os << "D3DFMT_R32F";
	case 115:
		return os << "D3DFMT_G32R32F";
	case 116:
		return os << "D3DFMT_A32B32G32R32F";
	case 117:
		return os << "D3DFMT_CxV8U8";
	case 118:
		return os << "D3DFMT_A1";
	case 119:
		return os << "D3DFMT_A2B10G10R10_XR_BIAS";
	case 199:
		return os << "D3DFMT_BINARYBUFFER";
	case 0x7fffffff:
		return os << "D3DFMT_FORCE_DWORD";
	default:
		if (format & 0xFF000000)
		{
			return os << (DDFOURCC)format;
		}
	}

	return os << (DWORD)format;
}

std::ostream& operator<<(std::ostream& os, const DDCAPS& cp)
{
	DDCAPS caps = { NULL };
	memcpy(&caps, &cp, min(sizeof(DDCAPS), cp.dwSize));
	return Logging::LogStruct(os)
		<< Logging::hex(caps.dwCaps)
		<< Logging::hex(caps.dwCaps2)
		<< Logging::hex(caps.dwCKeyCaps)
		<< Logging::hex(caps.dwFXCaps)
		<< Logging::hex(caps.dwFXAlphaCaps)
		<< Logging::hex(caps.dwPalCaps)
		<< Logging::hex(caps.dwSVCaps)
		<< caps.dwAlphaBltConstBitDepths
		<< caps.dwAlphaBltPixelBitDepths
		<< caps.dwAlphaBltSurfaceBitDepths
		<< caps.dwAlphaOverlayConstBitDepths
		<< caps.dwAlphaOverlayPixelBitDepths
		<< caps.dwAlphaOverlaySurfaceBitDepths
		<< caps.dwZBufferBitDepths
		<< caps.dwVidMemTotal
		<< caps.dwVidMemFree
		<< caps.dwMaxVisibleOverlays
		<< caps.dwCurrVisibleOverlays
		<< caps.dwNumFourCCCodes
		<< caps.dwAlignBoundarySrc
		<< caps.dwAlignSizeSrc
		<< caps.dwAlignBoundaryDest
		<< caps.dwAlignSizeDest
		<< caps.dwAlignStrideAlign
		<< "{" << caps.dwRops[0]
		<< caps.dwRops[1]
		<< caps.dwRops[2]
		<< caps.dwRops[3]
		<< caps.dwRops[4]
		<< caps.dwRops[5]
		<< caps.dwRops[6]
		<< caps.dwRops[7] << "}"
		<< caps.ddsOldCaps
		<< caps.dwMinOverlayStretch
		<< caps.dwMaxOverlayStretch
		<< caps.dwMinLiveVideoStretch
		<< caps.dwMaxLiveVideoStretch
		<< caps.dwMinHwCodecStretch
		<< caps.dwMaxHwCodecStretch
		<< caps.dwReserved1
		<< caps.dwReserved2
		<< caps.dwReserved3
		<< Logging::hex(caps.dwSVBCaps)
		<< Logging::hex(caps.dwSVBCKeyCaps)
		<< Logging::hex(caps.dwSVBFXCaps)
		<< "{" << caps.dwSVBRops[0]
		<< caps.dwSVBRops[1]
		<< caps.dwSVBRops[2]
		<< caps.dwSVBRops[3]
		<< caps.dwSVBRops[4]
		<< caps.dwSVBRops[5]
		<< caps.dwSVBRops[6]
		<< caps.dwSVBRops[7] << "}"
		<< Logging::hex(caps.dwVSBCaps)
		<< Logging::hex(caps.dwVSBCKeyCaps)
		<< Logging::hex(caps.dwVSBFXCaps)
		<< "{" << caps.dwVSBRops[0]
		<< caps.dwVSBRops[1]
		<< caps.dwVSBRops[2]
		<< caps.dwVSBRops[3]
		<< caps.dwVSBRops[4]
		<< caps.dwVSBRops[5]
		<< caps.dwVSBRops[6]
		<< caps.dwVSBRops[7] << "}"
		<< Logging::hex(caps.dwSSBCaps)
		<< Logging::hex(caps.dwSSBCKeyCaps)
		<< Logging::hex(caps.dwSSBFXCaps)
		<< "{" << caps.dwSSBRops[0]
		<< caps.dwSSBRops[1]
		<< caps.dwSSBRops[2]
		<< caps.dwSSBRops[3]
		<< caps.dwSSBRops[4]
		<< caps.dwSSBRops[5]
		<< caps.dwSSBRops[6]
		<< caps.dwSSBRops[7] << "}"
		<< caps.dwMaxVideoPorts
		<< caps.dwCurrVideoPorts
		<< Logging::hex(caps.dwSVBCaps2)
		<< Logging::hex(caps.dwNLVBCaps)
		<< Logging::hex(caps.dwNLVBCaps2)
		<< Logging::hex(caps.dwNLVBCKeyCaps)
		<< Logging::hex(caps.dwNLVBFXCaps)
		<< "{" << caps.dwNLVBRops[0]
		<< caps.dwNLVBRops[1]
		<< caps.dwNLVBRops[2]
		<< caps.dwNLVBRops[3]
		<< caps.dwNLVBRops[4]
		<< caps.dwNLVBRops[5]
		<< caps.dwNLVBRops[6]
		<< caps.dwNLVBRops[7] << "}"
		<< caps.ddsCaps;
}

std::ostream& operator<<(std::ostream& os, const DDSCAPS& dwCaps)
{
	return Logging::LogStructNull(os)
		<< ((dwCaps.dwCaps & DDSCAPS_3DDEVICE) ? " DDSCAPS_3DDEVICE " : "")
		<< ((dwCaps.dwCaps & DDSCAPS_ALLOCONLOAD) ? " DDSCAPS_ALLOCONLOAD " : "")
		<< ((dwCaps.dwCaps & DDSCAPS_ALPHA) ? " DDSCAPS_ALPHA " : "")
		<< ((dwCaps.dwCaps & DDSCAPS_BACKBUFFER) ? " DDSCAPS_BACKBUFFER " : "")
		<< ((dwCaps.dwCaps & DDSCAPS_COMPLEX) ? " DDSCAPS_COMPLEX " : "")
		<< ((dwCaps.dwCaps & DDSCAPS_FLIP) ? " DDSCAPS_FLIP " : "")
		<< ((dwCaps.dwCaps & DDSCAPS_FRONTBUFFER) ? " DDSCAPS_FRONTBUFFER " : "")
		<< ((dwCaps.dwCaps & DDSCAPS_HWCODEC) ? " DDSCAPS_HWCODEC " : "")
		<< ((dwCaps.dwCaps & DDSCAPS_LIVEVIDEO) ? " DDSCAPS_LIVEVIDEO " : "")
		<< ((dwCaps.dwCaps & DDSCAPS_LOCALVIDMEM) ? " DDSCAPS_LOCALVIDMEM " : "")
		<< ((dwCaps.dwCaps & DDSCAPS_MIPMAP) ? " DDSCAPS_MIPMAP " : "")
		<< ((dwCaps.dwCaps & DDSCAPS_MODEX) ? " DDSCAPS_MODEX " : "")
		<< ((dwCaps.dwCaps & DDSCAPS_NONLOCALVIDMEM) ? " DDSCAPS_NONLOCALVIDMEM " : "")
		<< ((dwCaps.dwCaps & DDSCAPS_OFFSCREENPLAIN) ? " DDSCAPS_OFFSCREENPLAIN " : "")
		<< ((dwCaps.dwCaps & DDSCAPS_OPTIMIZED) ? " DDSCAPS_OPTIMIZED " : "")
		<< ((dwCaps.dwCaps & DDSCAPS_OVERLAY) ? " DDSCAPS_OVERLAY " : "")
		<< ((dwCaps.dwCaps & DDSCAPS_OWNDC) ? " DDSCAPS_OWNDC " : "")
		<< ((dwCaps.dwCaps & DDSCAPS_PALETTE) ? " DDSCAPS_PALETTE " : "")
		<< ((dwCaps.dwCaps & DDSCAPS_PRIMARYSURFACE) ? " DDSCAPS_PRIMARYSURFACE " : "")
		<< ((dwCaps.dwCaps & DDSCAPS_STANDARDVGAMODE) ? " DDSCAPS_STANDARDVGAMODE " : "")
		<< ((dwCaps.dwCaps & DDSCAPS_SYSTEMMEMORY) ? " DDSCAPS_SYSTEMMEMORY " : "")
		<< ((dwCaps.dwCaps & DDSCAPS_TEXTURE) ? " DDSCAPS_TEXTURE " : "")
		<< ((dwCaps.dwCaps & DDSCAPS_VIDEOMEMORY) ? " DDSCAPS_VIDEOMEMORY " : "")
		<< ((dwCaps.dwCaps & DDSCAPS_VIDEOPORT) ? " DDSCAPS_VIDEOPORT " : "")
		<< ((dwCaps.dwCaps & DDSCAPS_VISIBLE) ? " DDSCAPS_VISIBLE " : "")
		<< ((dwCaps.dwCaps & DDSCAPS_WRITEONLY) ? " DDSCAPS_WRITEONLY " : "")
		<< ((dwCaps.dwCaps & DDSCAPS_ZBUFFER) ? " DDSCAPS_ZBUFFER " : "");
}

std::ostream& operator<<(std::ostream& os, const DDSCAPS2& caps)
{
	return Logging::LogStruct(os)
		<< *(DDSCAPS*)&caps
		<< Logging::hex(caps.dwCaps2)
		<< Logging::hex(caps.dwCaps3)
		<< Logging::hex(caps.dwCaps4);
}

std::ostream& operator<<(std::ostream& os, const DDFOURCC& dwFourCC)
{
	if (dwFourCC)
	{
		unsigned char ch0 = dwFourCC & 0xFF;
		unsigned char ch1 = (dwFourCC >> 8) & 0xFF;
		unsigned char ch2 = (dwFourCC >> 16) & 0xFF;
		unsigned char ch3 = (dwFourCC >> 24) & 0xFF;

		return os << "MAKEFOURCC('" << (char)ch0 << "', '" << (char)ch1 << "', '" << (char)ch2 << "', '" << (char)ch3 << "')";
	}

	return os << (DWORD)dwFourCC;
}

std::ostream& operator<<(std::ostream& os, const DDPIXELFORMAT& pf)
{
	return Logging::LogStruct(os)
		<< Logging::hex(pf.dwFlags)
		<< (DDFOURCC)pf.dwFourCC
		<< pf.dwRGBBitCount
		<< Logging::hex(pf.dwRBitMask)
		<< Logging::hex(pf.dwGBitMask)
		<< Logging::hex(pf.dwBBitMask)
		<< Logging::hex(pf.dwRGBAlphaBitMask);
}

std::ostream& operator<<(std::ostream& os, const DDCOLORKEY& ck)
{
	return Logging::LogStruct(os)
		<< Logging::hex(ck.dwColorSpaceLowValue)
		<< Logging::hex(ck.dwColorSpaceHighValue);
}

std::ostream& operator<<(std::ostream& os, const DDSURFACEDESC& sd)
{
	return Logging::LogStruct(os)
		<< Logging::hex(sd.dwFlags)
		<< sd.dwWidth
		<< sd.dwHeight
		<< sd.lPitch
		<< sd.dwBackBufferCount
		<< sd.dwMipMapCount
		<< sd.dwAlphaBitDepth
		<< sd.dwReserved
		<< sd.lpSurface
		<< sd.ddckCKDestOverlay
		<< sd.ddckCKDestBlt
		<< sd.ddckCKSrcOverlay
		<< sd.ddckCKSrcBlt
		<< sd.ddpfPixelFormat
		<< sd.ddsCaps;
}

std::ostream& operator<<(std::ostream& os, const DDSURFACEDESC2& sd)
{
	return Logging::LogStruct(os)
		<< Logging::hex(sd.dwFlags)
		<< sd.dwWidth
		<< sd.dwHeight
		<< sd.lPitch
		<< sd.dwBackBufferCount
		<< sd.dwMipMapCount
		<< sd.dwAlphaBitDepth
		<< sd.dwReserved
		<< sd.lpSurface
		<< sd.ddckCKDestOverlay
		<< sd.ddckCKDestBlt
		<< sd.ddckCKSrcOverlay
		<< sd.ddckCKSrcBlt
		<< sd.ddpfPixelFormat
		<< sd.dwFVF
		<< sd.ddsCaps
		<< sd.dwTextureStage;
}

std::ostream& operator<<(std::ostream& os, const D3DPRIMCAPS& dpc)
{
	return Logging::LogStruct(os)
		<< Logging::hex(dpc.dwMiscCaps)
		<< Logging::hex(dpc.dwRasterCaps)
		<< Logging::hex(dpc.dwZCmpCaps)
		<< Logging::hex(dpc.dwSrcBlendCaps)
		<< Logging::hex(dpc.dwDestBlendCaps)
		<< Logging::hex(dpc.dwAlphaCmpCaps)
		<< Logging::hex(dpc.dwShadeCaps)
		<< Logging::hex(dpc.dwTextureCaps)
		<< Logging::hex(dpc.dwTextureFilterCaps)
		<< Logging::hex(dpc.dwTextureBlendCaps)
		<< Logging::hex(dpc.dwTextureAddressCaps)
		<< dpc.dwStippleWidth
		<< dpc.dwStippleHeight;
}

std::ostream& operator<<(std::ostream& os, const D3DDEVICEDESC7& dd)
{
	return Logging::LogStruct(os)
		<< Logging::hex(dd.dwDevCaps)
		<< dd.dpcLineCaps
		<< dd.dpcTriCaps
		<< dd.dwDeviceRenderBitDepth
		<< dd.dwDeviceZBufferBitDepth
		<< dd.dwMinTextureWidth
		<< dd.dwMinTextureHeight
		<< dd.dwMaxTextureWidth
		<< dd.dwMaxTextureHeight
		<< dd.dwMaxTextureRepeat
		<< dd.dwMaxTextureAspectRatio
		<< dd.dwMaxAnisotropy
		<< dd.dvGuardBandLeft
		<< dd.dvGuardBandTop
		<< dd.dvGuardBandRight
		<< dd.dvGuardBandBottom
		<< dd.dvExtentsAdjust
		<< Logging::hex(dd.dwStencilCaps)
		<< Logging::hex(dd.dwFVFCaps)
		<< Logging::hex(dd.dwTextureOpCaps)
		<< dd.wMaxTextureBlendStages
		<< dd.wMaxSimultaneousTextures
		<< dd.dwMaxActiveLights
		<< dd.dvMaxVertexW
		<< dd.deviceGUID
		<< dd.wMaxUserClipPlanes
		<< dd.wMaxVertexBlendMatrices
		<< Logging::hex(dd.dwVertexProcessingCaps)
		<< dd.dwReserved1
		<< dd.dwReserved2
		<< dd.dwReserved3
		<< dd.dwReserved4;
}

std::ostream& operator<<(std::ostream& os, const D3DPRESENT_PARAMETERS& pp)
{
	return Logging::LogStruct(os)
		<< pp.BackBufferWidth
		<< pp.BackBufferHeight
		<< pp.BackBufferFormat
		<< pp.BackBufferCount
		<< pp.MultiSampleType
		<< pp.MultiSampleQuality
		<< pp.SwapEffect
		<< pp.hDeviceWindow
		<< pp.Windowed
		<< pp.EnableAutoDepthStencil
		<< pp.AutoDepthStencilFormat
		<< Logging::hex(pp.Flags)
		<< pp.FullScreen_RefreshRateInHz
		<< Logging::hex(pp.PresentationInterval);
}

#ifndef __unknwnbase_h__
DEFINE_GUID(IID_IUnknown, 0x00000000, 0x0000, 0x0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);
DEFINE_GUID(IID_IClassFactory, 0x00000001, 0x0000, 0x0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);
#endif
#ifndef __DDRAW_INCLUDED__
DEFINE_GUID(CLSID_DirectDraw, 0xD7B70EE0, 0x4340, 0x11CF, 0xB0, 0x63, 0x00, 0x20, 0xAF, 0xC2, 0xCD, 0x35);
DEFINE_GUID(CLSID_DirectDraw7, 0x3C305196, 0x50DB, 0x11D3, 0x9C, 0xFE, 0x00, 0xC0, 0x4F, 0xD9, 0x30, 0xC5);
DEFINE_GUID(CLSID_DirectDrawClipper, 0x593817A0, 0x7DB3, 0x11CF, 0xA2, 0xDE, 0x00, 0xAA, 0x00, 0xb9, 0x33, 0x56);
DEFINE_GUID(IID_IDirectDraw, 0x6C14DB80, 0xA733, 0x11CE, 0xA5, 0x21, 0x00, 0x20, 0xAF, 0x0B, 0xE5, 0x60);
DEFINE_GUID(IID_IDirectDraw2, 0xB3A6F3E0, 0x2B43, 0x11CF, 0xA2, 0xDE, 0x00, 0xAA, 0x00, 0xB9, 0x33, 0x56);
DEFINE_GUID(IID_IDirectDraw4, 0x9c59509a, 0x39bd, 0x11d1, 0x8c, 0x4a, 0x00, 0xc0, 0x4f, 0xd9, 0x30, 0xc5);
DEFINE_GUID(IID_IDirectDraw7, 0x15e65ec0, 0x3b9c, 0x11d2, 0xb9, 0x2f, 0x00, 0x60, 0x97, 0x97, 0xea, 0x5b);
DEFINE_GUID(IID_IDirectDrawSurface, 0x6C14DB81, 0xA733, 0x11CE, 0xA5, 0x21, 0x00, 0x20, 0xAF, 0x0B, 0xE5, 0x60);
DEFINE_GUID(IID_IDirectDrawSurface2, 0x57805885, 0x6eec, 0x11cf, 0x94, 0x41, 0xa8, 0x23, 0x03, 0xc1, 0x0e, 0x27);
DEFINE_GUID(IID_IDirectDrawSurface3, 0xDA044E00, 0x69B2, 0x11D0, 0xA1, 0xD5, 0x00, 0xAA, 0x00, 0xB8, 0xDF, 0xBB);
DEFINE_GUID(IID_IDirectDrawSurface4, 0x0B2B8630, 0xAD35, 0x11D0, 0x8E, 0xA6, 0x00, 0x60, 0x97, 0x97, 0xEA, 0x5B);
DEFINE_GUID(IID_IDirectDrawSurface7, 0x06675a80, 0x3b9b, 0x11d2, 0xb9, 0x2f, 0x00, 0x60, 0x97, 0x97, 0xea, 0x5b);
DEFINE_GUID(IID_IDirectDrawPalette, 0x6C14DB84, 0xA733, 0x11CE, 0xA5, 0x21, 0x00, 0x20, 0xAF, 0x0B, 0xE5, 0x60);
DEFINE_GUID(IID_IDirectDrawClipper, 0x6C14DB85, 0xA733, 0x11CE, 0xA5, 0x21, 0x00, 0x20, 0xAF, 0x0B, 0xE5, 0x60);
DEFINE_GUID(IID_IDirectDrawColorControl, 0x4B9F0EE0, 0x0D7E, 0x11D0, 0x9B, 0x06, 0x00, 0xA0, 0xC9, 0x03, 0xA3, 0xB8);
DEFINE_GUID(IID_IDirectDrawGammaControl, 0x69C11C3E, 0xB46B, 0x11D1, 0xAD, 0x7A, 0x00, 0xC0, 0x4F, 0xC2, 0x9B, 0x4E);
#endif
#ifndef __DDRAWEXH__
DEFINE_GUID(IID_IDirectDraw3, 0x618f8ad4, 0x8b7a, 0x11d0, 0x8f, 0xcc, 0x0, 0xc0, 0x4f, 0xd9, 0x18, 0x9d);
DEFINE_GUID(CLSID_DirectDrawFactory, 0x4fd2a832, 0x86c8, 0x11d0, 0x8f, 0xca, 0x0, 0xc0, 0x4f, 0xd9, 0x18, 0x9d);
DEFINE_GUID(IID_IDirectDrawFactory, 0x4fd2a833, 0x86c8, 0x11d0, 0x8f, 0xca, 0x0, 0xc0, 0x4f, 0xd9, 0x18, 0x9d);
#endif
#ifndef _D3D_H_
DEFINE_GUID(IID_IDirect3D, 0x3BBA0080, 0x2421, 0x11CF, 0xA3, 0x1A, 0x00, 0xAA, 0x00, 0xB9, 0x33, 0x56);
DEFINE_GUID(IID_IDirect3D2, 0x6aae1ec1, 0x662a, 0x11d0, 0x88, 0x9d, 0x00, 0xaa, 0x00, 0xbb, 0xb7, 0x6a);
DEFINE_GUID(IID_IDirect3D3, 0xbb223240, 0xe72b, 0x11d0, 0xa9, 0xb4, 0x00, 0xaa, 0x00, 0xc0, 0x99, 0x3e);
DEFINE_GUID(IID_IDirect3D7, 0xf5049e77, 0x4861, 0x11d2, 0xa4, 0x7, 0x0, 0xa0, 0xc9, 0x6, 0x29, 0xa8);
DEFINE_GUID(IID_IDirect3DRampDevice, 0xF2086B20, 0x259F, 0x11CF, 0xA3, 0x1A, 0x00, 0xAA, 0x00, 0xB9, 0x33, 0x56);
DEFINE_GUID(IID_IDirect3DRGBDevice, 0xA4665C60, 0x2673, 0x11CF, 0xA3, 0x1A, 0x00, 0xAA, 0x00, 0xB9, 0x33, 0x56);
DEFINE_GUID(IID_IDirect3DHALDevice, 0x84E63dE0, 0x46AA, 0x11CF, 0x81, 0x6F, 0x00, 0x00, 0xC0, 0x20, 0x15, 0x6E);
DEFINE_GUID(IID_IDirect3DMMXDevice, 0x881949a1, 0xd6f3, 0x11d0, 0x89, 0xab, 0x00, 0xa0, 0xc9, 0x05, 0x41, 0x29);
DEFINE_GUID(IID_IDirect3DRefDevice, 0x50936643, 0x13e9, 0x11d1, 0x89, 0xaa, 0x0, 0xa0, 0xc9, 0x5, 0x41, 0x29);
DEFINE_GUID(IID_IDirect3DNullDevice, 0x8767df22, 0xbacc, 0x11d1, 0x89, 0x69, 0x0, 0xa0, 0xc9, 0x6, 0x29, 0xa8);
DEFINE_GUID(IID_IDirect3DTnLHalDevice, 0xf5049e78, 0x4861, 0x11d2, 0xa4, 0x7, 0x0, 0xa0, 0xc9, 0x6, 0x29, 0xa8);
DEFINE_GUID(IID_IDirect3DDevice, 0x64108800, 0x957d, 0X11d0, 0x89, 0xab, 0x00, 0xa0, 0xc9, 0x05, 0x41, 0x29);
DEFINE_GUID(IID_IDirect3DDevice2, 0x93281501, 0x8cf8, 0x11d0, 0x89, 0xab, 0x0, 0xa0, 0xc9, 0x5, 0x41, 0x29);
DEFINE_GUID(IID_IDirect3DDevice3, 0xb0ab3b60, 0x33d7, 0x11d1, 0xa9, 0x81, 0x0, 0xc0, 0x4f, 0xd7, 0xb1, 0x74);
DEFINE_GUID(IID_IDirect3DDevice7, 0xf5049e79, 0x4861, 0x11d2, 0xa4, 0x7, 0x0, 0xa0, 0xc9, 0x6, 0x29, 0xa8);
DEFINE_GUID(IID_IDirect3DTexture, 0x2CDCD9E0, 0x25A0, 0x11CF, 0xA3, 0x1A, 0x00, 0xAA, 0x00, 0xB9, 0x33, 0x56);
DEFINE_GUID(IID_IDirect3DTexture2, 0x93281502, 0x8cf8, 0x11d0, 0x89, 0xab, 0x0, 0xa0, 0xc9, 0x5, 0x41, 0x29);
DEFINE_GUID(IID_IDirect3DLight, 0x4417C142, 0x33AD, 0x11CF, 0x81, 0x6F, 0x00, 0x00, 0xC0, 0x20, 0x15, 0x6E);
DEFINE_GUID(IID_IDirect3DMaterial, 0x4417C144, 0x33AD, 0x11CF, 0x81, 0x6F, 0x00, 0x00, 0xC0, 0x20, 0x15, 0x6E);
DEFINE_GUID(IID_IDirect3DMaterial2, 0x93281503, 0x8cf8, 0x11d0, 0x89, 0xab, 0x0, 0xa0, 0xc9, 0x5, 0x41, 0x29);
DEFINE_GUID(IID_IDirect3DMaterial3, 0xca9c46f4, 0xd3c5, 0x11d1, 0xb7, 0x5a, 0x0, 0x60, 0x8, 0x52, 0xb3, 0x12);
DEFINE_GUID(IID_IDirect3DExecuteBuffer, 0x4417C145, 0x33AD, 0x11CF, 0x81, 0x6F, 0x00, 0x00, 0xC0, 0x20, 0x15, 0x6E);
DEFINE_GUID(IID_IDirect3DViewport, 0x4417C146, 0x33AD, 0x11CF, 0x81, 0x6F, 0x00, 0x00, 0xC0, 0x20, 0x15, 0x6E);
DEFINE_GUID(IID_IDirect3DViewport2, 0x93281500, 0x8cf8, 0x11d0, 0x89, 0xab, 0x0, 0xa0, 0xc9, 0x5, 0x41, 0x29);
DEFINE_GUID(IID_IDirect3DViewport3, 0xb0ab3b61, 0x33d7, 0x11d1, 0xa9, 0x81, 0x0, 0xc0, 0x4f, 0xd7, 0xb1, 0x74);
DEFINE_GUID(IID_IDirect3DVertexBuffer, 0x7a503555, 0x4a83, 0x11d1, 0xa5, 0xdb, 0x0, 0xa0, 0xc9, 0x3, 0x67, 0xf8);
DEFINE_GUID(IID_IDirect3DVertexBuffer7, 0xf5049e7d, 0x4861, 0x11d2, 0xa4, 0x7, 0x0, 0xa0, 0xc9, 0x6, 0x29, 0xa8);
#endif
#ifndef _D3D8_H_
DEFINE_GUID(IID_IDirect3D8, 0x1dd9e8da, 0x1c77, 0x4d40, 0xb0, 0xcf, 0x98, 0xfe, 0xfd, 0xff, 0x95, 0x12);
DEFINE_GUID(IID_IDirect3DDevice8, 0x7385e5df, 0x8fe8, 0x41d5, 0x86, 0xb6, 0xd7, 0xb4, 0x85, 0x47, 0xb6, 0xcf);
DEFINE_GUID(IID_IDirect3DResource8, 0x1b36bb7b, 0x9b7, 0x410a, 0xb4, 0x45, 0x7d, 0x14, 0x30, 0xd7, 0xb3, 0x3f);
DEFINE_GUID(IID_IDirect3DBaseTexture8, 0xb4211cfa, 0x51b9, 0x4a9f, 0xab, 0x78, 0xdb, 0x99, 0xb2, 0xbb, 0x67, 0x8e);
DEFINE_GUID(IID_IDirect3DTexture8, 0xe4cdd575, 0x2866, 0x4f01, 0xb1, 0x2e, 0x7e, 0xec, 0xe1, 0xec, 0x93, 0x58);
DEFINE_GUID(IID_IDirect3DCubeTexture8, 0x3ee5b968, 0x2aca, 0x4c34, 0x8b, 0xb5, 0x7e, 0x0c, 0x3d, 0x19, 0xb7, 0x50);
DEFINE_GUID(IID_IDirect3DVolumeTexture8, 0x4b8aaafa, 0x140f, 0x42ba, 0x91, 0x31, 0x59, 0x7e, 0xaf, 0xaa, 0x2e, 0xad);
DEFINE_GUID(IID_IDirect3DVertexBuffer8, 0x8aeeeac7, 0x05f9, 0x44d4, 0xb5, 0x91, 0x00, 0x0b, 0x0d, 0xf1, 0xcb, 0x95);
DEFINE_GUID(IID_IDirect3DIndexBuffer8, 0x0e689c9a, 0x053d, 0x44a0, 0x9d, 0x92, 0xdb, 0x0e, 0x3d, 0x75, 0x0f, 0x86);
DEFINE_GUID(IID_IDirect3DSurface8, 0xb96eebca, 0xb326, 0x4ea5, 0x88, 0x2f, 0x2f, 0xf5, 0xba, 0xe0, 0x21, 0xdd);
DEFINE_GUID(IID_IDirect3DVolume8, 0xbd7349f5, 0x14f1, 0x42e4, 0x9c, 0x79, 0x97, 0x23, 0x80, 0xdb, 0x40, 0xc0);
DEFINE_GUID(IID_IDirect3DSwapChain8, 0x928c088b, 0x76b9, 0x4c6b, 0xa5, 0x36, 0xa5, 0x90, 0x85, 0x38, 0x76, 0xcd);
#endif
#ifndef _D3D9_H_
DEFINE_GUID(IID_IDirect3D9, 0x81bdcbca, 0x64d4, 0x426d, 0xae, 0x8d, 0xad, 0x1, 0x47, 0xf4, 0x27, 0x5c);
DEFINE_GUID(IID_IDirect3DDevice9, 0xd0223b96, 0xbf7a, 0x43fd, 0x92, 0xbd, 0xa4, 0x3b, 0xd, 0x82, 0xb9, 0xeb);
DEFINE_GUID(IID_IDirect3DResource9, 0x5eec05d, 0x8f7d, 0x4362, 0xb9, 0x99, 0xd1, 0xba, 0xf3, 0x57, 0xc7, 0x4);
DEFINE_GUID(IID_IDirect3DBaseTexture9, 0x580ca87e, 0x1d3c, 0x4d54, 0x99, 0x1d, 0xb7, 0xd3, 0xe3, 0xc2, 0x98, 0xce);
DEFINE_GUID(IID_IDirect3DTexture9, 0x85c31227, 0x3de5, 0x4f00, 0x9b, 0x3a, 0xf1, 0x1a, 0xc3, 0x8c, 0x18, 0xb5);
DEFINE_GUID(IID_IDirect3DCubeTexture9, 0xfff32f81, 0xd953, 0x473a, 0x92, 0x23, 0x93, 0xd6, 0x52, 0xab, 0xa9, 0x3f);
DEFINE_GUID(IID_IDirect3DVolumeTexture9, 0x2518526c, 0xe789, 0x4111, 0xa7, 0xb9, 0x47, 0xef, 0x32, 0x8d, 0x13, 0xe6);
DEFINE_GUID(IID_IDirect3DVertexBuffer9, 0xb64bb1b5, 0xfd70, 0x4df6, 0xbf, 0x91, 0x19, 0xd0, 0xa1, 0x24, 0x55, 0xe3);
DEFINE_GUID(IID_IDirect3DIndexBuffer9, 0x7c9dd65e, 0xd3f7, 0x4529, 0xac, 0xee, 0x78, 0x58, 0x30, 0xac, 0xde, 0x35);
DEFINE_GUID(IID_IDirect3DSurface9, 0xcfbaf3a, 0x9ff6, 0x429a, 0x99, 0xb3, 0xa2, 0x79, 0x6a, 0xf8, 0xb8, 0x9b);
DEFINE_GUID(IID_IDirect3DVolume9, 0x24f416e6, 0x1f67, 0x4aa7, 0xb8, 0x8e, 0xd3, 0x3f, 0x6f, 0x31, 0x28, 0xa1);
DEFINE_GUID(IID_IDirect3DSwapChain9, 0x794950f2, 0xadfc, 0x458a, 0x90, 0x5e, 0x10, 0xa1, 0xb, 0xb, 0x50, 0x3b);
DEFINE_GUID(IID_IDirect3DVertexDeclaration9, 0xdd13c59c, 0x36fa, 0x4098, 0xa8, 0xfb, 0xc7, 0xed, 0x39, 0xdc, 0x85, 0x46);
DEFINE_GUID(IID_IDirect3DVertexShader9, 0xefc5557e, 0x6265, 0x4613, 0x8a, 0x94, 0x43, 0x85, 0x78, 0x89, 0xeb, 0x36);
DEFINE_GUID(IID_IDirect3DPixelShader9, 0x6d3bdbdc, 0x5b02, 0x4415, 0xb8, 0x52, 0xce, 0x5e, 0x8b, 0xcc, 0xb2, 0x89);
DEFINE_GUID(IID_IDirect3DStateBlock9, 0xb07c4fe5, 0x310d, 0x4ba8, 0xa2, 0x3c, 0x4f, 0xf, 0x20, 0x6f, 0x21, 0x8b);
DEFINE_GUID(IID_IDirect3DQuery9, 0xd9771460, 0xa695, 0x4f26, 0xbb, 0xd3, 0x27, 0xb8, 0x40, 0xb5, 0x41, 0xcc);
DEFINE_GUID(IID_HelperName, 0xe4a36723, 0xfdfe, 0x4b22, 0xb1, 0x46, 0x3c, 0x4, 0xc0, 0x7f, 0x4c, 0xc8);
DEFINE_GUID(IID_IDirect3D9Ex, 0x02177241, 0x69FC, 0x400C, 0x8F, 0xF1, 0x93, 0xA4, 0x4D, 0xF6, 0x86, 0x1D);
DEFINE_GUID(IID_IDirect3DDevice9Ex, 0xb18b10ce, 0x2649, 0x405a, 0x87, 0xf, 0x95, 0xf7, 0x77, 0xd4, 0x31, 0x3a);
DEFINE_GUID(IID_IDirect3DSwapChain9Ex, 0x91886caf, 0x1c3d, 0x4d2e, 0xa0, 0xab, 0x3e, 0x4c, 0x7d, 0x8d, 0x33, 0x3);
DEFINE_GUID(IID_IDirect3D9ExOverlayExtension, 0x187aeb13, 0xaaf5, 0x4c59, 0x87, 0x6d, 0xe0, 0x59, 0x8, 0x8c, 0xd, 0xf8);
DEFINE_GUID(IID_IDirect3DDevice9Video, 0x26dc4561, 0xa1ee, 0x4ae7, 0x96, 0xda, 0x11, 0x8a, 0x36, 0xc0, 0xec, 0x95);
DEFINE_GUID(IID_IDirect3DAuthenticatedChannel9, 0xff24beee, 0xda21, 0x4beb, 0x98, 0xb5, 0xd2, 0xf8, 0x99, 0xf9, 0x8a, 0xf9);
DEFINE_GUID(IID_IDirect3DCryptoSession9, 0xfa0ab799, 0x7a9c, 0x48ca, 0x8c, 0x5b, 0x23, 0x7e, 0x71, 0xa5, 0x44, 0x34);
#endif
#ifndef __DINPUT_INCLUDED__
DEFINE_GUID(CLSID_DirectInput, 0x25E609E0, 0xB259, 0x11CF, 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);
DEFINE_GUID(CLSID_DirectInputDevice, 0x25E609E1, 0xB259, 0x11CF, 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);
DEFINE_GUID(CLSID_DirectInput8, 0x25E609E4, 0xB259, 0x11CF, 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);
DEFINE_GUID(CLSID_DirectInputDevice8, 0x25E609E5, 0xB259, 0x11CF, 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);
DEFINE_GUID(IID_IDirectInputA, 0x89521360, 0xAA8A, 0x11CF, 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);
DEFINE_GUID(IID_IDirectInputW, 0x89521361, 0xAA8A, 0x11CF, 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);
DEFINE_GUID(IID_IDirectInput2A, 0x5944E662, 0xAA8A, 0x11CF, 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);
DEFINE_GUID(IID_IDirectInput2W, 0x5944E663, 0xAA8A, 0x11CF, 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);
DEFINE_GUID(IID_IDirectInput7A, 0x9A4CB684, 0x236D, 0x11D3, 0x8E, 0x9D, 0x00, 0xC0, 0x4F, 0x68, 0x44, 0xAE);
DEFINE_GUID(IID_IDirectInput7W, 0x9A4CB685, 0x236D, 0x11D3, 0x8E, 0x9D, 0x00, 0xC0, 0x4F, 0x68, 0x44, 0xAE);
DEFINE_GUID(IID_IDirectInput8A, 0xBF798030, 0x483A, 0x4DA2, 0xAA, 0x99, 0x5D, 0x64, 0xED, 0x36, 0x97, 0x00);
DEFINE_GUID(IID_IDirectInput8W, 0xBF798031, 0x483A, 0x4DA2, 0xAA, 0x99, 0x5D, 0x64, 0xED, 0x36, 0x97, 0x00);
DEFINE_GUID(IID_IDirectInputDeviceA, 0x5944E680, 0xC92E, 0x11CF, 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);
DEFINE_GUID(IID_IDirectInputDeviceW, 0x5944E681, 0xC92E, 0x11CF, 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);
DEFINE_GUID(IID_IDirectInputDevice2A, 0x5944E682, 0xC92E, 0x11CF, 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);
DEFINE_GUID(IID_IDirectInputDevice2W, 0x5944E683, 0xC92E, 0x11CF, 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);
DEFINE_GUID(IID_IDirectInputDevice7A, 0x57D7C6BC, 0x2356, 0x11D3, 0x8E, 0x9D, 0x00, 0xC0, 0x4F, 0x68, 0x44, 0xAE);
DEFINE_GUID(IID_IDirectInputDevice7W, 0x57D7C6BD, 0x2356, 0x11D3, 0x8E, 0x9D, 0x00, 0xC0, 0x4F, 0x68, 0x44, 0xAE);
DEFINE_GUID(IID_IDirectInputDevice8A, 0x54D41080, 0xDC15, 0x4833, 0xA4, 0x1B, 0x74, 0x8F, 0x73, 0xA3, 0x81, 0x79);
DEFINE_GUID(IID_IDirectInputDevice8W, 0x54D41081, 0xDC15, 0x4833, 0xA4, 0x1B, 0x74, 0x8F, 0x73, 0xA3, 0x81, 0x79);
DEFINE_GUID(IID_IDirectInputEffect, 0xE7E1F7C0, 0x88D2, 0x11D0, 0x9A, 0xD0, 0x00, 0xA0, 0xC9, 0xA0, 0x6E, 0x35);
DEFINE_GUID(GUID_XAxis,   0xA36D02E0,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_YAxis,   0xA36D02E1,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_ZAxis,   0xA36D02E2,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_RxAxis,  0xA36D02F4,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_RyAxis,  0xA36D02F5,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_RzAxis,  0xA36D02E3,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_Slider,  0xA36D02E4,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_Button,  0xA36D02F0,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_Key,     0x55728220,0xD33C,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_POV,     0xA36D02F2,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_Unknown, 0xA36D02F3,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_SysMouse,   0x6F1D2B60,0xD5A0,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_SysKeyboard,0x6F1D2B61,0xD5A0,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_Joystick   ,0x6F1D2B70,0xD5A0,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_SysMouseEm, 0x6F1D2B80,0xD5A0,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_SysMouseEm2,0x6F1D2B81,0xD5A0,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_SysKeyboardEm, 0x6F1D2B82,0xD5A0,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_SysKeyboardEm2,0x6F1D2B83,0xD5A0,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_ConstantForce, 0x13541C20,0x8E33,0x11D0,0x9A,0xD0,0x00,0xA0,0xC9,0xA0,0x6E,0x35);
DEFINE_GUID(GUID_RampForce,     0x13541C21,0x8E33,0x11D0,0x9A,0xD0,0x00,0xA0,0xC9,0xA0,0x6E,0x35);
DEFINE_GUID(GUID_Square,        0x13541C22,0x8E33,0x11D0,0x9A,0xD0,0x00,0xA0,0xC9,0xA0,0x6E,0x35);
DEFINE_GUID(GUID_Sine,          0x13541C23,0x8E33,0x11D0,0x9A,0xD0,0x00,0xA0,0xC9,0xA0,0x6E,0x35);
DEFINE_GUID(GUID_Triangle,      0x13541C24,0x8E33,0x11D0,0x9A,0xD0,0x00,0xA0,0xC9,0xA0,0x6E,0x35);
DEFINE_GUID(GUID_SawtoothUp,    0x13541C25,0x8E33,0x11D0,0x9A,0xD0,0x00,0xA0,0xC9,0xA0,0x6E,0x35);
DEFINE_GUID(GUID_SawtoothDown,  0x13541C26,0x8E33,0x11D0,0x9A,0xD0,0x00,0xA0,0xC9,0xA0,0x6E,0x35);
DEFINE_GUID(GUID_Spring,        0x13541C27,0x8E33,0x11D0,0x9A,0xD0,0x00,0xA0,0xC9,0xA0,0x6E,0x35);
DEFINE_GUID(GUID_Damper,        0x13541C28,0x8E33,0x11D0,0x9A,0xD0,0x00,0xA0,0xC9,0xA0,0x6E,0x35);
DEFINE_GUID(GUID_Inertia,       0x13541C29,0x8E33,0x11D0,0x9A,0xD0,0x00,0xA0,0xC9,0xA0,0x6E,0x35);
DEFINE_GUID(GUID_Friction,      0x13541C2A,0x8E33,0x11D0,0x9A,0xD0,0x00,0xA0,0xC9,0xA0,0x6E,0x35);
DEFINE_GUID(GUID_CustomForce,   0x13541C2B,0x8E33,0x11D0,0x9A,0xD0,0x00,0xA0,0xC9,0xA0,0x6E,0x35);
#endif
DEFINE_GUID(IID_IMediaStream, 0xb502d1bd, 0x9a57, 0x11d0, 0x8f, 0xde, 0x00, 0xc0, 0x4f, 0xd9, 0x18, 0x9d);
DEFINE_GUID(IID_IAMMediaStream, 0xbebe595d, 0x9a6f, 0x11d0, 0x8f, 0xde, 0x00, 0xc0, 0x4f, 0xd9, 0x18, 0x9d);

std::ostream& operator<<(std::ostream& os, REFIID riid)
{
#define CHECK_REFIID(riidPrefix, riidName) \
	if (riid == riidPrefix ## _ ## riidName) \
	{ \
		return os << #riidPrefix << "_" << #riidName; \
	}

	CHECK_REFIID(IID, IUnknown);
	CHECK_REFIID(IID, IClassFactory);
	// ddraw
	CHECK_REFIID(CLSID, DirectDraw);
	CHECK_REFIID(CLSID, DirectDraw7);
	CHECK_REFIID(CLSID, DirectDrawClipper);
	CHECK_REFIID(IID, IDirectDraw);
	CHECK_REFIID(IID, IDirectDraw2);
	CHECK_REFIID(IID, IDirectDraw4);
	CHECK_REFIID(IID, IDirectDraw7);
	CHECK_REFIID(IID, IDirectDrawSurface);
	CHECK_REFIID(IID, IDirectDrawSurface2);
	CHECK_REFIID(IID, IDirectDrawSurface3);
	CHECK_REFIID(IID, IDirectDrawSurface4);
	CHECK_REFIID(IID, IDirectDrawSurface7);
	CHECK_REFIID(IID, IDirectDrawPalette);
	CHECK_REFIID(IID, IDirectDrawClipper);
	CHECK_REFIID(IID, IDirectDrawColorControl);
	CHECK_REFIID(IID, IDirectDrawGammaControl);
	// ddrawex
	CHECK_REFIID(IID, IDirectDraw3);
	CHECK_REFIID(CLSID, DirectDrawFactory);
	CHECK_REFIID(IID, IDirectDrawFactory);
	// d3d
	CHECK_REFIID(IID, IDirect3D);
	CHECK_REFIID(IID, IDirect3D2);
	CHECK_REFIID(IID, IDirect3D3);
	CHECK_REFIID(IID, IDirect3D7);
	CHECK_REFIID(IID, IDirect3DRampDevice);
	CHECK_REFIID(IID, IDirect3DRGBDevice);
	CHECK_REFIID(IID, IDirect3DHALDevice);
	CHECK_REFIID(IID, IDirect3DMMXDevice);
	CHECK_REFIID(IID, IDirect3DRefDevice);
	CHECK_REFIID(IID, IDirect3DNullDevice);
	CHECK_REFIID(IID, IDirect3DTnLHalDevice);
	CHECK_REFIID(IID, IDirect3DDevice);
	CHECK_REFIID(IID, IDirect3DDevice2);
	CHECK_REFIID(IID, IDirect3DDevice3);
	CHECK_REFIID(IID, IDirect3DDevice7);
	CHECK_REFIID(IID, IDirect3DTexture);
	CHECK_REFIID(IID, IDirect3DTexture2);
	CHECK_REFIID(IID, IDirect3DLight);
	CHECK_REFIID(IID, IDirect3DMaterial);
	CHECK_REFIID(IID, IDirect3DMaterial2);
	CHECK_REFIID(IID, IDirect3DMaterial3);
	CHECK_REFIID(IID, IDirect3DExecuteBuffer);
	CHECK_REFIID(IID, IDirect3DViewport);
	CHECK_REFIID(IID, IDirect3DViewport2);
	CHECK_REFIID(IID, IDirect3DViewport3);
	CHECK_REFIID(IID, IDirect3DVertexBuffer);
	CHECK_REFIID(IID, IDirect3DVertexBuffer7);
	// d3d8
	CHECK_REFIID(IID, IDirect3D8);
	CHECK_REFIID(IID, IDirect3DDevice8);
	CHECK_REFIID(IID, IDirect3DResource8);
	CHECK_REFIID(IID, IDirect3DBaseTexture8);
	CHECK_REFIID(IID, IDirect3DTexture8);
	CHECK_REFIID(IID, IDirect3DCubeTexture8);
	CHECK_REFIID(IID, IDirect3DVolumeTexture8);
	CHECK_REFIID(IID, IDirect3DVertexBuffer8);
	CHECK_REFIID(IID, IDirect3DIndexBuffer8);
	CHECK_REFIID(IID, IDirect3DSurface8);
	CHECK_REFIID(IID, IDirect3DVolume8);
	CHECK_REFIID(IID, IDirect3DSwapChain8);
	// d3d9
	CHECK_REFIID(IID, IDirect3D9);
	CHECK_REFIID(IID, IDirect3DDevice9);
	CHECK_REFIID(IID, IDirect3DResource9);
	CHECK_REFIID(IID, IDirect3DBaseTexture9);
	CHECK_REFIID(IID, IDirect3DTexture9);
	CHECK_REFIID(IID, IDirect3DCubeTexture9);
	CHECK_REFIID(IID, IDirect3DVolumeTexture9);
	CHECK_REFIID(IID, IDirect3DVertexBuffer9);
	CHECK_REFIID(IID, IDirect3DIndexBuffer9);
	CHECK_REFIID(IID, IDirect3DSurface9);
	CHECK_REFIID(IID, IDirect3DVolume9);
	CHECK_REFIID(IID, IDirect3DSwapChain9);
	CHECK_REFIID(IID, IDirect3DVertexDeclaration9);
	CHECK_REFIID(IID, IDirect3DVertexShader9);
	CHECK_REFIID(IID, IDirect3DPixelShader9);
	CHECK_REFIID(IID, IDirect3DStateBlock9);
	CHECK_REFIID(IID, IDirect3DQuery9);
	CHECK_REFIID(IID, HelperName);
	CHECK_REFIID(IID, IDirect3D9Ex);
	CHECK_REFIID(IID, IDirect3DDevice9Ex);
	CHECK_REFIID(IID, IDirect3DSwapChain9Ex);
	CHECK_REFIID(IID, IDirect3D9ExOverlayExtension);
	CHECK_REFIID(IID, IDirect3DDevice9Video);
	CHECK_REFIID(IID, IDirect3DAuthenticatedChannel9);
	CHECK_REFIID(IID, IDirect3DCryptoSession9);
	// dinput
	CHECK_REFIID(CLSID, DirectInput);
	CHECK_REFIID(CLSID, DirectInputDevice);
	CHECK_REFIID(CLSID, DirectInput8);
	CHECK_REFIID(CLSID, DirectInputDevice8);
	CHECK_REFIID(IID, IDirectInputA);
	CHECK_REFIID(IID, IDirectInputW);
	CHECK_REFIID(IID, IDirectInput2A);
	CHECK_REFIID(IID, IDirectInput2W);
	CHECK_REFIID(IID, IDirectInput7A);
	CHECK_REFIID(IID, IDirectInput7W);
	CHECK_REFIID(IID, IDirectInput8A);
	CHECK_REFIID(IID, IDirectInput8W);
	CHECK_REFIID(IID, IDirectInputDeviceA);
	CHECK_REFIID(IID, IDirectInputDeviceW);
	CHECK_REFIID(IID, IDirectInputDevice2A);
	CHECK_REFIID(IID, IDirectInputDevice2W);
	CHECK_REFIID(IID, IDirectInputDevice7A);
	CHECK_REFIID(IID, IDirectInputDevice7W);
	CHECK_REFIID(IID, IDirectInputDevice8A);
	CHECK_REFIID(IID, IDirectInputDevice8W);
	CHECK_REFIID(IID, IDirectInputEffect);
	// Predefined object types
	CHECK_REFIID(GUID, XAxis);
	CHECK_REFIID(GUID, YAxis);
	CHECK_REFIID(GUID, ZAxis);
	CHECK_REFIID(GUID, RxAxis);
	CHECK_REFIID(GUID, RyAxis);
	CHECK_REFIID(GUID, RzAxis);
	CHECK_REFIID(GUID, Slider);
	CHECK_REFIID(GUID, Button);
	CHECK_REFIID(GUID, Key);
	CHECK_REFIID(GUID, POV);
	CHECK_REFIID(GUID, Unknown);
	// Predefined product GUIDs
	CHECK_REFIID(GUID, SysMouse);
	CHECK_REFIID(GUID, SysKeyboard);
	CHECK_REFIID(GUID, Joystick);
	CHECK_REFIID(GUID, SysMouseEm);
	CHECK_REFIID(GUID, SysMouseEm2);
	CHECK_REFIID(GUID, SysKeyboardEm);
	CHECK_REFIID(GUID, SysKeyboardEm2);
	// Predefined force feedback effects
	CHECK_REFIID(GUID, ConstantForce);
	CHECK_REFIID(GUID, RampForce);
	CHECK_REFIID(GUID, Square);
	CHECK_REFIID(GUID, Sine);
	CHECK_REFIID(GUID, Triangle);
	CHECK_REFIID(GUID, SawtoothUp);
	CHECK_REFIID(GUID, SawtoothDown);
	CHECK_REFIID(GUID, Spring);
	CHECK_REFIID(GUID, Damper);
	CHECK_REFIID(GUID, Inertia);
	CHECK_REFIID(GUID, Friction);
	CHECK_REFIID(GUID, CustomForce);
	// direct show
	CHECK_REFIID(IID, IMediaStream);
	CHECK_REFIID(IID, IAMMediaStream);
	// dxwrapper specific
	CHECK_REFIID(IID, GetRealInterface);
	CHECK_REFIID(IID, GetInterfaceX);

	UINT x = 0;
	char buffer[(sizeof(IID) * 2) + 5] = { '\0' };
	for (size_t j : {3, 2, 1, 0, 0xFF, 5, 4, 0xFF, 7, 6, 0xFF, 8, 9, 0xFF, 10, 11, 12, 13, 14, 15})
	{
		if (j == 0xFF)
		{
			buffer[x] = '-';
		}
		else
		{
			sprintf_s(buffer + x, 3, "%02X", ((byte*)&riid)[j]);
			x++;
		}
		x++;
	}

	return Logging::LogStruct(os) << buffer;
}

std::ostream& operator<<(std::ostream& os, const DDERR& ErrCode)
{
#define VISIT_DDERR_CODES(visit) \
	visit(DD_OK) \
	visit(DDERR_ALREADYINITIALIZED) \
	visit(DDERR_CANNOTATTACHSURFACE) \
	visit(DDERR_CANNOTDETACHSURFACE) \
	visit(DDERR_CURRENTLYNOTAVAIL) \
	visit(DDERR_EXCEPTION) \
	visit(DDERR_GENERIC) \
	visit(DDERR_HEIGHTALIGN) \
	visit(DDERR_INCOMPATIBLEPRIMARY) \
	visit(DDERR_INVALIDCAPS) \
	visit(DDERR_INVALIDCLIPLIST) \
	visit(DDERR_INVALIDMODE) \
	visit(DDERR_INVALIDOBJECT) \
	visit(DDERR_INVALIDPARAMS) \
	visit(DDERR_INVALIDPIXELFORMAT) \
	visit(DDERR_INVALIDRECT) \
	visit(DDERR_LOCKEDSURFACES) \
	visit(DDERR_NO3D) \
	visit(DDERR_NOALPHAHW) \
	visit(DDERR_NOSTEREOHARDWARE) \
	visit(DDERR_NOSURFACELEFT) \
	visit(DDERR_NOCLIPLIST) \
	visit(DDERR_NOCOLORCONVHW) \
	visit(DDERR_NOCOOPERATIVELEVELSET) \
	visit(DDERR_NOCOLORKEY) \
	visit(DDERR_NOCOLORKEYHW) \
	visit(DDERR_NODIRECTDRAWSUPPORT) \
	visit(DDERR_NOEXCLUSIVEMODE) \
	visit(DDERR_NOFLIPHW) \
	visit(DDERR_NOGDI) \
	visit(DDERR_NOMIRRORHW) \
	visit(DDERR_NOTFOUND) \
	visit(DDERR_NOOVERLAYHW) \
	visit(DDERR_OVERLAPPINGRECTS) \
	visit(DDERR_NORASTEROPHW) \
	visit(DDERR_NOROTATIONHW) \
	visit(DDERR_NOSTRETCHHW) \
	visit(DDERR_NOT4BITCOLOR) \
	visit(DDERR_NOT4BITCOLORINDEX) \
	visit(DDERR_NOT8BITCOLOR) \
	visit(DDERR_NOTEXTUREHW) \
	visit(DDERR_NOVSYNCHW) \
	visit(DDERR_NOZBUFFERHW) \
	visit(DDERR_NOZOVERLAYHW) \
	visit(DDERR_OUTOFCAPS) \
	visit(DDERR_OUTOFMEMORY) \
	visit(DDERR_OUTOFVIDEOMEMORY) \
	visit(DDERR_OVERLAYCANTCLIP) \
	visit(DDERR_OVERLAYCOLORKEYONLYONEACTIVE) \
	visit(DDERR_PALETTEBUSY) \
	visit(DDERR_COLORKEYNOTSET) \
	visit(DDERR_SURFACEALREADYATTACHED) \
	visit(DDERR_SURFACEALREADYDEPENDENT) \
	visit(DDERR_SURFACEBUSY) \
	visit(DDERR_CANTLOCKSURFACE) \
	visit(DDERR_SURFACEISOBSCURED) \
	visit(DDERR_SURFACELOST) \
	visit(DDERR_SURFACENOTATTACHED) \
	visit(DDERR_TOOBIGHEIGHT) \
	visit(DDERR_TOOBIGSIZE) \
	visit(DDERR_TOOBIGWIDTH) \
	visit(DDERR_UNSUPPORTED) \
	visit(DDERR_UNSUPPORTEDFORMAT) \
	visit(DDERR_UNSUPPORTEDMASK) \
	visit(DDERR_INVALIDSTREAM) \
	visit(DDERR_VERTICALBLANKINPROGRESS) \
	visit(DDERR_WASSTILLDRAWING) \
	visit(DDERR_DDSCAPSCOMPLEXREQUIRED) \
	visit(DDERR_XALIGN) \
	visit(DDERR_INVALIDDIRECTDRAWGUID) \
	visit(DDERR_DIRECTDRAWALREADYCREATED) \
	visit(DDERR_NODIRECTDRAWHW) \
	visit(DDERR_PRIMARYSURFACEALREADYEXISTS) \
	visit(DDERR_NOEMULATION) \
	visit(DDERR_REGIONTOOSMALL) \
	visit(DDERR_CLIPPERISUSINGHWND) \
	visit(DDERR_NOCLIPPERATTACHED) \
	visit(DDERR_NOHWND) \
	visit(DDERR_HWNDSUBCLASSED) \
	visit(DDERR_HWNDALREADYSET) \
	visit(DDERR_NOPALETTEATTACHED) \
	visit(DDERR_NOPALETTEHW) \
	visit(DDERR_BLTFASTCANTCLIP) \
	visit(DDERR_NOBLTHW) \
	visit(DDERR_NODDROPSHW) \
	visit(DDERR_OVERLAYNOTVISIBLE) \
	visit(DDERR_NOOVERLAYDEST) \
	visit(DDERR_INVALIDPOSITION) \
	visit(DDERR_NOTAOVERLAYSURFACE) \
	visit(DDERR_EXCLUSIVEMODEALREADYSET) \
	visit(DDERR_NOTFLIPPABLE) \
	visit(DDERR_CANTDUPLICATE) \
	visit(DDERR_NOTLOCKED) \
	visit(DDERR_CANTCREATEDC) \
	visit(DDERR_NODC) \
	visit(DDERR_WRONGMODE) \
	visit(DDERR_IMPLICITLYCREATED) \
	visit(DDERR_NOTPALETTIZED) \
	visit(DDERR_UNSUPPORTEDMODE) \
	visit(DDERR_NOMIPMAPHW) \
	visit(DDERR_INVALIDSURFACETYPE) \
	visit(DDERR_NOOPTIMIZEHW) \
	visit(DDERR_NOTLOADED) \
	visit(DDERR_NOFOCUSWINDOW) \
	visit(DDERR_NOTONMIPMAPSUBLEVEL) \
	visit(DDERR_DCALREADYCREATED) \
	visit(DDERR_NONONLOCALVIDMEM) \
	visit(DDERR_CANTPAGELOCK) \
	visit(DDERR_CANTPAGEUNLOCK) \
	visit(DDERR_NOTPAGELOCKED) \
	visit(DDERR_MOREDATA) \
	visit(DDERR_EXPIRED) \
	visit(DDERR_TESTFINISHED) \
	visit(DDERR_NEWMODE) \
	visit(DDERR_D3DNOTINITIALIZED) \
	visit(DDERR_VIDEONOTACTIVE) \
	visit(DDERR_NOMONITORINFORMATION) \
	visit(DDERR_NODRIVERSUPPORT) \
	visit(DDERR_DEVICEDOESNTOWNSURFACE) \
	visit(DDERR_NOTINITIALIZED) \
	visit(DDERR_LOADFAILED) \
	visit(DDERR_BADVERSIONINFO) \
	visit(DDERR_BADPROCADDRESS) \
	visit(DDERR_LEGACYUSAGE) \
	visit(D3D_OK) \
	visit(D3DERR_BADMAJORVERSION) \
	visit(D3DERR_BADMINORVERSION) \
	visit(D3DERR_INVALID_DEVICE) \
	visit(D3DERR_INITFAILED) \
	visit(D3DERR_DEVICEAGGREGATED) \
	visit(D3DERR_EXECUTE_CREATE_FAILED) \
	visit(D3DERR_EXECUTE_DESTROY_FAILED) \
	visit(D3DERR_EXECUTE_LOCK_FAILED) \
	visit(D3DERR_EXECUTE_UNLOCK_FAILED) \
	visit(D3DERR_EXECUTE_LOCKED) \
	visit(D3DERR_EXECUTE_NOT_LOCKED) \
	visit(D3DERR_EXECUTE_FAILED) \
	visit(D3DERR_EXECUTE_CLIPPED_FAILED) \
	visit(D3DERR_TEXTURE_NO_SUPPORT) \
	visit(D3DERR_TEXTURE_CREATE_FAILED) \
	visit(D3DERR_TEXTURE_DESTROY_FAILED) \
	visit(D3DERR_TEXTURE_LOCK_FAILED) \
	visit(D3DERR_TEXTURE_UNLOCK_FAILED) \
	visit(D3DERR_TEXTURE_LOAD_FAILED) \
	visit(D3DERR_TEXTURE_SWAP_FAILED) \
	visit(D3DERR_TEXTURE_LOCKED) \
	visit(D3DERR_TEXTURE_NOT_LOCKED) \
	visit(D3DERR_TEXTURE_GETSURF_FAILED) \
	visit(D3DERR_MATRIX_CREATE_FAILED) \
	visit(D3DERR_MATRIX_DESTROY_FAILED) \
	visit(D3DERR_MATRIX_SETDATA_FAILED) \
	visit(D3DERR_MATRIX_GETDATA_FAILED) \
	visit(D3DERR_SETVIEWPORTDATA_FAILED) \
	visit(D3DERR_INVALIDCURRENTVIEWPORT) \
	visit(D3DERR_INVALIDPRIMITIVETYPE) \
	visit(D3DERR_INVALIDVERTEXTYPE) \
	visit(D3DERR_TEXTURE_BADSIZE) \
	visit(D3DERR_INVALIDRAMPTEXTURE) \
	visit(D3DERR_MATERIAL_CREATE_FAILED) \
	visit(D3DERR_MATERIAL_DESTROY_FAILED) \
	visit(D3DERR_MATERIAL_SETDATA_FAILED) \
	visit(D3DERR_MATERIAL_GETDATA_FAILED) \
	visit(D3DERR_INVALIDPALETTE) \
	visit(D3DERR_ZBUFF_NEEDS_SYSTEMMEMORY) \
	visit(D3DERR_ZBUFF_NEEDS_VIDEOMEMORY) \
	visit(D3DERR_SURFACENOTINVIDMEM) \
	visit(D3DERR_LIGHT_SET_FAILED) \
	visit(D3DERR_LIGHTHASVIEWPORT) \
	visit(D3DERR_LIGHTNOTINTHISVIEWPORT) \
	visit(D3DERR_SCENE_IN_SCENE) \
	visit(D3DERR_SCENE_NOT_IN_SCENE) \
	visit(D3DERR_SCENE_BEGIN_FAILED) \
	visit(D3DERR_SCENE_END_FAILED) \
	visit(D3DERR_INBEGIN) \
	visit(D3DERR_NOTINBEGIN) \
	visit(D3DERR_NOVIEWPORTS) \
	visit(D3DERR_VIEWPORTDATANOTSET) \
	visit(D3DERR_VIEWPORTHASNODEVICE) \
	visit(D3DERR_NOCURRENTVIEWPORT) \
	visit(D3DERR_INVALIDVERTEXFORMAT) \
	visit(D3DERR_COLORKEYATTACHED) \
	visit(D3DERR_VERTEXBUFFEROPTIMIZED) \
	visit(D3DERR_VBUF_CREATE_FAILED) \
	visit(D3DERR_VERTEXBUFFERLOCKED) \
	visit(D3DERR_VERTEXBUFFERUNLOCKFAILED) \
	visit(D3DERR_ZBUFFER_NOTPRESENT) \
	visit(D3DERR_STENCILBUFFER_NOTPRESENT) \
	visit(D3DERR_WRONGTEXTUREFORMAT) \
	visit(D3DERR_UNSUPPORTEDCOLOROPERATION) \
	visit(D3DERR_UNSUPPORTEDCOLORARG) \
	visit(D3DERR_UNSUPPORTEDALPHAOPERATION) \
	visit(D3DERR_UNSUPPORTEDALPHAARG) \
	visit(D3DERR_TOOMANYOPERATIONS) \
	visit(D3DERR_CONFLICTINGTEXTUREFILTER) \
	visit(D3DERR_UNSUPPORTEDFACTORVALUE) \
	visit(D3DERR_CONFLICTINGRENDERSTATE) \
	visit(D3DERR_UNSUPPORTEDTEXTUREFILTER) \
	visit(D3DERR_TOOMANYPRIMITIVES) \
	visit(D3DERR_INVALIDMATRIX) \
	visit(D3DERR_TOOMANYVERTICES) \
	visit(D3DERR_CONFLICTINGTEXTUREPALETTE) \
	visit(D3DERR_CONFLICTINGTEXTUREPALETTE) \
	visit(D3DERR_INVALIDSTATEBLOCK) \
	visit(D3DERR_INBEGINSTATEBLOCK) \
	visit(D3DERR_NOTINBEGINSTATEBLOCK) \
	visit(D3DERR_COMMAND_UNPARSED) \
	visit(E_NOINTERFACE) \
	visit(E_POINTER)

#define VISIT_DDERR_RETURN(x) \
	if (ErrCode == x) \
	{ \
		return os << #x; \
	}

	VISIT_DDERR_CODES(VISIT_DDERR_RETURN);

	return os << Logging::hex((DWORD)ErrCode);
}


std::ostream& operator<<(std::ostream& os, const DIERR& ErrCode)
{
#define VISIT_DIERR_CODES(visit) \
	visit(DI_OK) \
	visit(DI_POLLEDDEVICE) \
	visit(DI_DOWNLOADSKIPPED) \
	visit(DI_EFFECTRESTARTED) \
	visit(DI_TRUNCATED) \
	visit(DI_SETTINGSNOTSAVED) \
	visit(DI_TRUNCATEDANDRESTARTED) \
	visit(DI_WRITEPROTECT) \
	visit(DIERR_OLDDIRECTINPUTVERSION) \
	visit(DIERR_BETADIRECTINPUTVERSION) \
	visit(DIERR_BADDRIVERVER) \
	visit(DIERR_DEVICENOTREG) \
	visit(DIERR_NOTFOUND) \
	visit(DIERR_OBJECTNOTFOUND) \
	visit(DIERR_INVALIDPARAM) \
	visit(DIERR_NOINTERFACE) \
	visit(DIERR_GENERIC) \
	visit(DIERR_OUTOFMEMORY) \
	visit(DIERR_UNSUPPORTED) \
	visit(DIERR_NOTINITIALIZED) \
	visit(DIERR_ALREADYINITIALIZED) \
	visit(DIERR_NOAGGREGATION) \
	visit(DIERR_OTHERAPPHASPRIO) \
	visit(DIERR_INPUTLOST) \
	visit(DIERR_ACQUIRED) \
	visit(DIERR_NOTACQUIRED) \
	visit(DIERR_READONLY) \
	visit(DIERR_HANDLEEXISTS) \
	visit(E_PENDING) \
	visit(DIERR_INSUFFICIENTPRIVS) \
	visit(DIERR_DEVICEFULL) \
	visit(DIERR_MOREDATA) \
	visit(DIERR_NOTDOWNLOADED) \
	visit(DIERR_HASEFFECTS) \
	visit(DIERR_NOTEXCLUSIVEACQUIRED) \
	visit(DIERR_INCOMPLETEEFFECT) \
	visit(DIERR_NOTBUFFERED) \
	visit(DIERR_EFFECTPLAYING) \
	visit(DIERR_UNPLUGGED) \
	visit(DIERR_REPORTFULL) \
	visit(DIERR_MAPFILEFAIL) \
	visit(E_NOINTERFACE) \
	visit(E_POINTER)

#define VISIT_DIERR_RETURN(x) \
	if (ErrCode == x) \
	{ \
		return os << #x; \
	}

	if (ErrCode == S_FALSE)
	{
		return os << "'DI_NOTATTACHED' or 'DI_BUFFEROVERFLOW' or 'DI_PROPNOEFFECT' or 'DI_NOEFFECT'";
	}

	VISIT_DIERR_CODES(VISIT_DIERR_RETURN);

	return os << Logging::hex((DWORD)ErrCode);
}
