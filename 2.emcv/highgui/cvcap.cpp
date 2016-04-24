////////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                 License For Embedded Computer Vision Library
//
// Copyright (c) 2012, EMCV Project,
// Copyright (c) 2000-2007, Intel Corporation,
// All rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification, 
// are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice, 
//      this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above copyright notice, 
//      this list of conditions and the following disclaimer in the documentation 
//      and/or other materials provided with the distribution.
//    * Neither the name of the copyright holders nor the names of their contributors 
//      may be used to endorse or promote products derived from this software 
//      without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
// OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
// OF SUCH DAMAGE.
//
// Contributors:
//    * Shiqi Yu (Shenzhen Institute of Advanced Technology, Chinese Academy of Sciences)


#ifndef _TMS320C6X

#include "_highgui.h"

#if _MSC_VER >= 1200
#pragma warning( disable: 4711 )
#endif

#if defined WIN64 && defined EM64T && defined _MSC_VER && !defined __ICL
#pragma optimize("",off)
#endif


/************************* Reading AVIs & Camera data **************************/

CV_IMPL void cvReleaseCapture( CvCapture** pcapture )
{
    if( pcapture && *pcapture )
    {
        delete *pcapture;
        *pcapture = 0;
    }
}

CV_IMPL IplImage* cvQueryFrame( CvCapture* capture )
{
    return capture ? capture->queryFrame() : 0;
}


CV_IMPL int cvGrabFrame( CvCapture* capture )
{
    return capture ? capture->grabFrame() : 0;
}

CV_IMPL IplImage* cvRetrieveFrame( CvCapture* capture, int idx )
{
    return capture ? capture->retrieveFrame(idx) : 0;
}

CV_IMPL double cvGetCaptureProperty( CvCapture* capture, int id )
{
    return capture ? capture->getProperty(id) : 0;
}

CV_IMPL int cvSetCaptureProperty( CvCapture* capture, int id, double value )
{
    return capture ? capture->setProperty(id, value) : 0;
}


/**
 * Camera dispatching method: index is the camera number.
 * If given an index from 0 to 99, it tries to find the first
 * API that can access a given camera index.
 * Add multiples of 100 to select an API.
 */
CV_IMPL CvCapture * cvCreateCameraCapture (int index)
{
	int  domains[] =
	{
#ifdef HAVE_VIDEOINPUT
        CV_CAP_DSHOW,
#endif
		CV_CAP_IEEE1394,   // identical to CV_CAP_DC1394
		CV_CAP_STEREO,
		CV_CAP_VFW,        // identical to CV_CAP_V4L
		CV_CAP_MIL,
		CV_CAP_QT,
		CV_CAP_UNICAP,
		-1
	};

	// interpret preferred interface (0 = autodetect)
	int pref = (index / 100) * 100;
	if (pref)
	{
		domains[0]=pref;
		index %= 100;
		domains[1]=-1;
	}

	// try every possibly installed camera API
	for (int i = 0; domains[i] >= 0; i++)
	{
        #if defined(HAVE_VIDEOINPUT) || defined(HAVE_TYZX) || defined(HAVE_VFW) || \
	    defined(HAVE_CAMV4L) || defined (HAVE_CAMV4L2) || defined(HAVE_GSTREAMER) || \
	    defined(HAVE_DC1394_2) || defined(HAVE_DC1394) || defined(HAVE_CMU1394) || \
	    defined(HAVE_GSTREAMER) || defined(HAVE_MIL) || defined(HAVE_QUICKTIME) || \
	    defined(HAVE_UNICAP)
		// local variable to memorize the captured device
		CvCapture *capture;
	#endif

		switch (domains[i])
		{
        #ifdef HAVE_VIDEOINPUT
        case CV_CAP_DSHOW:
            capture = cvCreateCameraCapture_DShow (index);
            if (capture)
                return capture;
            break;
        #endif

		#ifdef HAVE_TYZX
		case CV_CAP_STEREO:
			capture = cvCreateCameraCapture_TYZX (index);
			if (capture)
				return capture;
			break;
		#endif

		case CV_CAP_VFW:
		#ifdef HAVE_VFW
			capture = cvCreateCameraCapture_VFW (index);
			if (capture)
				return capture;
		#endif
		#if defined (HAVE_CAMV4L) || defined (HAVE_CAMV4L2)
			capture = cvCreateCameraCapture_V4L (index);
			if (capture)
				return capture;
		#endif
		#ifdef HAVE_GSTREAMER
			capture = cvCreateCapture_GStreamer(CV_CAP_GSTREAMER_V4L2, 0);
			if (capture)
				return capture;
			capture = cvCreateCapture_GStreamer(CV_CAP_GSTREAMER_V4L, 0);
			if (capture)
				return capture;
		#endif
			break;

		case CV_CAP_FIREWIRE:
		#ifdef HAVE_DC1394_2
			capture = cvCreateCameraCapture_DC1394_2 (index);
			if (capture)
				return capture;
		#endif
		#ifdef HAVE_DC1394
			capture = cvCreateCameraCapture_DC1394 (index);
			if (capture)
				return capture;
		#endif
		#ifdef HAVE_CMU1394
			capture = cvCreateCameraCapture_CMU (index);
			if (capture)
				return capture;
		#endif
		#ifdef HAVE_GSTREAMER
			capture = cvCreateCapture_GStreamer(CV_CAP_GSTREAMER_1394, 0);
			if (capture)
				return capture;
		#endif
			break;

		#ifdef HAVE_MIL
		case CV_CAP_MIL:
			capture = cvCreateCameraCapture_MIL (index);
			if (capture)
				return capture;
			break;
		#endif

		#ifdef HAVE_QUICKTIME
		case CV_CAP_QT:
			capture = cvCreateCameraCapture_QT (index);
			if (capture)
				return capture;
			break;
		#endif

		#ifdef HAVE_UNICAP
		case CV_CAP_UNICAP:
		  capture = cvCreateCameraCapture_Unicap (index);
		  if (capture)
		    return capture;
		  break;
		#endif

		}
	}

	// failed open a camera
	return 0;
}

#endif	// _TMS320C6X
