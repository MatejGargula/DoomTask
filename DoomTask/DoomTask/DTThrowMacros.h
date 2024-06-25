#pragma once

#define GFX_THROW_FAILED(hrcall) if(FAILED(hr = (hrcall))) throw DTGraphics::HrException(__LINE__, __FILE__, hr)
#define GFX_DEVICE_REMOVED_EXCEPT(hr) DTGraphics::DeviceRemovedException(__LINE__, __FILE__, hr)
#define GFX_THROW_NOINFO(hrcall) if( FAILED( hr = (hrcall) ) ) throw DTGraphics::HrException( __LINE__,__FILE__,hr )

#define DTWND_EXCEPT( hr ) DTWindow::HrException( __LINE__,__FILE__,(hr) )
#define DTWND_LAST_EXCEPT() DTWindow::HrException( __LINE__,__FILE__,GetLastError() )
#define DTWND_NOGFX_EXCEPT() DTWindow::NoGfxException( __LINE__,__FILE__ )
