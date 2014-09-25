﻿#pragma once

// The following XML snippet needs to be added to Package.appxmanifest:
//
//<Extensions>
//  <Extension Category = "windows.activatableClass.inProcessServer">
//    <InProcessServer>
//      <Path>VideoEffects.WindowsPhone.dll</Path>
//      <ActivatableClass ActivatableClassId = "VideoEffects.LumiaEffect" ThreadingModel = "both" />
//    </InProcessServer>
//  </Extension>
//</Extensions>
//

class LumiaEffect WrlSealed : public Video1in1outEffect<LumiaEffect, /*D3DAware*/true> // On Phone 8.1 MediaComposition requires all effects to be D3D aware
{
    InspectableClass(L"VideoEffects.LumiaEffect", TrustLevel::BaseTrust);

public:

    LumiaEffect()
        : _format(0)
        , _width(0)
        , _height(0)
    {
    }

    void Initialize(_In_ Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ props);

    // Format management
    std::vector<unsigned long> GetSupportedFormats();
    bool IsFormatSupported(_In_ unsigned long /*format*/, _In_ unsigned int /*width*/, _In_ unsigned int /*height*/)
    {
        return true; // no constraint beyond set of supported formats 
    }

    // Data processing
    void StartStreaming(_In_ unsigned long format, _In_ unsigned int width, _In_ unsigned int height);
    bool ProcessSample(_In_ const Microsoft::WRL::ComPtr<IMFSample>& inputSample, _In_ const Microsoft::WRL::ComPtr<IMFSample>& outputSample);
    void EndStreaming();

private:

    unsigned long _format;
    unsigned int _width;
    unsigned int _height;
    
    Windows::Foundation::Collections::IIterable<Nokia::Graphics::Imaging::IFilter^>^ _filters;
};

ActivatableClass(LumiaEffect);