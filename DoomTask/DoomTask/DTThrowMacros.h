#pragma once

#define GFX_EXCEPT(hr) DTGraphics::HrException( __LINE__,__FILE__,(hr),infoManager.GetMessages() )
#define GFX_THROW_FAILED(hrcall) if(FAILED(hr = (hrcall))) throw DTGraphics::HrException(__LINE__, __FILE__, hr)
#define GFX_THROW_INFO(hrcall) infoManager.Set(); if( FAILED( hr = (hrcall) ) ) throw GFX_EXCEPT(hr)
#define GFX_DEVICE_REMOVED_EXCEPT(hr) DTGraphics::DeviceRemovedException(__LINE__, __FILE__, hr)
#define GFX_THROW_NOINFO(hrcall) if( FAILED( hr = (hrcall) ) ) throw DTGraphics::HrException( __LINE__,__FILE__,hr )
#define GFX_THROW_INFO_ONLY(call) infoManager.Set(); (call); {auto v = infoManager.GetMessages(); if(!v.empty()) {throw DTGraphics::InfoException( __LINE__,__FILE__,v);}}


#define DTWND_EXCEPT( hr ) DTWindow::HrException( __LINE__,__FILE__,(hr) )
#define DTWND_LAST_EXCEPT() DTWindow::HrException( __LINE__,__FILE__,GetLastError() )
#define DTWND_NOGFX_EXCEPT() DTWindow::NoGfxException( __LINE__,__FILE__ )
