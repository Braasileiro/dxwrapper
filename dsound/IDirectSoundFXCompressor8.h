#pragma once

class m_IDirectSoundFXCompressor8 : public IDirectSoundFXCompressor8, public AddressLookupTableDsoundObject
{
private:
	LPDIRECTSOUNDFXCOMPRESSOR8 ProxyInterface;

public:
	m_IDirectSoundFXCompressor8(LPDIRECTSOUNDFXCOMPRESSOR8 pSound8) : ProxyInterface(pSound8)
	{
		LOG_LIMIT(3, "Creating interface " << __FUNCTION__ << " (" << this << ")");

		ProxyAddressLookupTableDsound.SaveAddress(this, ProxyInterface);
	}
	~m_IDirectSoundFXCompressor8()
	{
		LOG_LIMIT(3, __FUNCTION__ << " (" << this << ")" << " deleting interface!");

		ProxyAddressLookupTableDsound.DeleteAddress(this);
	}

	// IUnknown methods
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID* ppvObj);
	STDMETHOD_(ULONG, AddRef)(THIS);
	STDMETHOD_(ULONG, Release)(THIS);

	// IDirectSoundFXCompressor methods
	STDMETHOD(SetAllParameters)(THIS_ _In_ LPCDSFXCompressor pcDsFxCompressor);
	STDMETHOD(GetAllParameters)(THIS_ _Out_ LPDSFXCompressor pDsFxCompressor);

	// Helper functions
	LPDIRECTSOUNDFXCOMPRESSOR8 GetProxyInterface() { return ProxyInterface; }
};
