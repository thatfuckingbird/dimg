/*****************************************************************
|
|   Platinum - Test Light Device
|
| Copyright (c) 2004-2010, Plutinosoft, LLC.
| All rights reserved.
| http://www.plutinosoft.com
|
| This program is free software; you can redistribute it and/or
| modify it under the terms of the GNU General Public License
| as published by the Free Software Foundation; either version 2
| of the License, or (at your option) any later version.
|
| OEMs, ISVs, VARs and other distributors that combine and
| distribute commercially licensed software with Platinum software
| and do not wish to distribute the source code for the commercially
| licensed software under version 2, or (at your option) any later
| version, of the GNU General Public License (the "GPL") must enter
| into a commercial license agreement with Plutinosoft, LLC.
| licensing@plutinosoft.com
|
| This program is distributed in the hope that it will be useful,
| but WITHOUT ANY WARRANTY; without even the implied warranty of
| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
| GNU General Public License for more details.
|
| You should have received a copy of the GNU General Public License
| along with this program; see the file LICENSE.txt. If not, write to
| the Free Software Foundation, Inc.,
| 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
| http://www.gnu.org/licenses/gpl-2.0.html
|
****************************************************************/

/*----------------------------------------------------------------------
|   includes
+---------------------------------------------------------------------*/
#include "PltUPnP.h"
#include "PltLightSample.h"

#define TEST_EMBEDDED_DEVICE 1

/*----------------------------------------------------------------------
|   main
+---------------------------------------------------------------------*/
int
main(int /* argc */, char** /* argv */)
{
    // setup Neptune logging
    NPT_LogManager::GetDefault().Configure("plist:.level=FINE;.handlers=ConsoleHandler;.ConsoleHandler.colors=off;.ConsoleHandler.filter=42");

    PLT_UPnP upnp;

    PLT_DeviceHostReference device(new PLT_LightSampleDevice("Platinum Light Bulb"));

#ifdef TEST_EMBEDDED_DEVICE
    PLT_DeviceDataReference device2(new PLT_LightSampleDevice("Platinum Light Bulb embed 1"));
    device->AddEmbeddedDevice((PLT_DeviceDataReference&)device2);

    PLT_DeviceDataReference device3(new PLT_LightSampleDevice("Platinum Light Bulb embed 2"));
    device->AddEmbeddedDevice(device3);
#endif

    upnp.AddDevice(device);
    upnp.Start();

    char buf[256];
    while (true) {
        fgets(buf, 256, stdin);
        if (*buf == 'q')
            break;
    }

    upnp.Stop();

    return 0;
}
