#pragma once

class m_IDirectSoundCaptureFXAec8 : public IDirectSoundCaptureFXAec8, public AddressLookupTableDsoundObject
{
private:
	LPDIRECTSOUNDCAPTUREFXAEC8 ProxyInterface;

public:
	m_IDirectSoundCaptureFXAec8(LPDIRECTSOUNDCAPTUREFXAEC8 pSound8) : ProxyInterface(pSound8)
	{
		LOG_LIMIT(3, "Creating interface " << __FUNCTION__ << " (" << this << ")");

		ProxyAddressLookupTableDsound.SaveAddress(this, ProxyInterface);
	}
	~m_IDirectSoundCaptureFXAec8()
	{
		LOG_LIMIT(3, __FUNCTION__ << " (" << this << ")" << " deleting interface!");

		ProxyAddressLookupTableDsound.DeleteAddress(this);
	}

	// IUnknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID* ppvObj);
	STDMETHOD_(ULONG, AddRef)(THIS);
	STDMETHOD_(ULONG, Release)(THIS);

	// IDirectSoundCaptureFXAec methods
	STDMETHOD(SetAllParameters)(THIS_ _In_ LPCDSCFXAec pDscFxAec);
	STDMETHOD(GetAllParameters)(THIS_ _Out_ LPDSCFXAec pDscFxAec);
	STDMETHOD(GetStatus)(THIS_ _Out_ LPDWORD pdwStatus);
	STDMETHOD(Reset)(THIS);

	// Helper functions
	LPDIRECTSOUNDCAPTUREFXAEC8 GetProxyInterface() { return ProxyInterface; }
};
