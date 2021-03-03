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

#include "dsound.h"

HRESULT m_IDirectSoundCaptureBuffer8::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	if ((riid == IID_IDirectSoundCaptureBuffer || riid == IID_IDirectSoundCaptureBuffer8 || riid == IID_IUnknown) && ppvObj)
	{
		AddRef();

		*ppvObj = this;

		return DS_OK;
	}

	HRESULT hr = ProxyInterface->QueryInterface(riid, ppvObj);

	if (SUCCEEDED(hr))
	{
		genericQueryInterface(riid, ppvObj);
	}

	return hr;
}

ULONG m_IDirectSoundCaptureBuffer8::AddRef()
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	return ProxyInterface->AddRef();
}

ULONG m_IDirectSoundCaptureBuffer8::Release()
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	ULONG x = ProxyInterface->Release();

	if (x == 0)
	{
		delete this;
	}

	return x;
}

// IDirectSoundCaptureBuffer methods
HRESULT m_IDirectSoundCaptureBuffer8::GetCaps(LPDSCBCAPS pDSCBCaps)
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	return ProxyInterface->GetCaps(pDSCBCaps);
}

HRESULT m_IDirectSoundCaptureBuffer8::GetCurrentPosition(LPDWORD pdwCapturePosition, LPDWORD pdwReadPosition)
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	return ProxyInterface->GetCurrentPosition(pdwCapturePosition, pdwReadPosition);
}

HRESULT m_IDirectSoundCaptureBuffer8::GetFormat(LPWAVEFORMATEX pwfxFormat, DWORD dwSizeAllocated, LPDWORD pdwSizeWritten)
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	return ProxyInterface->GetFormat(pwfxFormat, dwSizeAllocated, pdwSizeWritten);
}

HRESULT m_IDirectSoundCaptureBuffer8::GetStatus(LPDWORD pdwStatus)
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	return ProxyInterface->GetStatus(pdwStatus);
}

HRESULT m_IDirectSoundCaptureBuffer8::Initialize(LPDIRECTSOUNDCAPTURE pDirectSoundCapture, LPCDSCBUFFERDESC pcDSCBufferDesc)
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	if (pDirectSoundCapture)
	{
		pDirectSoundCapture = static_cast<m_IDirectSoundCapture8 *>(pDirectSoundCapture)->GetProxyInterface();
	}

	return ProxyInterface->Initialize(pDirectSoundCapture, pcDSCBufferDesc);
}

HRESULT m_IDirectSoundCaptureBuffer8::Lock(DWORD dwOffset, DWORD dwBytes, LPVOID *ppvAudioPtr1, LPDWORD pdwAudioBytes1, LPVOID *ppvAudioPtr2, LPDWORD pdwAudioBytes2, DWORD dwFlags)
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	return ProxyInterface->Lock(dwOffset, dwBytes, ppvAudioPtr1, pdwAudioBytes1, ppvAudioPtr2, pdwAudioBytes2, dwFlags);
}

HRESULT m_IDirectSoundCaptureBuffer8::Start(DWORD dwFlags)
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	return ProxyInterface->Start(dwFlags);
}

HRESULT m_IDirectSoundCaptureBuffer8::Stop()
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	return ProxyInterface->Stop();
}

HRESULT m_IDirectSoundCaptureBuffer8::Unlock(LPVOID pvAudioPtr1, DWORD dwAudioBytes1, LPVOID pvAudioPtr2, DWORD dwAudioBytes2)
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	return ProxyInterface->Unlock(pvAudioPtr1, dwAudioBytes1, pvAudioPtr2, dwAudioBytes2);
}

// IDirectSoundCaptureBuffer8 methods
HRESULT m_IDirectSoundCaptureBuffer8::GetObjectInPath(REFGUID rguidObject, DWORD dwIndex, REFGUID rguidInterface, LPVOID *ppObject)
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	HRESULT hr = ProxyInterface->GetObjectInPath(rguidObject, dwIndex, rguidInterface, ppObject);

	if (SUCCEEDED(hr))
	{
		genericQueryInterface(rguidInterface, ppObject);
	}

	return hr;
}

HRESULT m_IDirectSoundCaptureBuffer8::GetFXStatus(DWORD dwEffectsCount, LPDWORD pdwFXStatus)
{
	Logging::LogDebug() << __FUNCTION__ << " (" << this << ")";

	return ProxyInterface->GetFXStatus(dwEffectsCount, pdwFXStatus);
}
