/*
 * This file is part of intiLED.
 *
 * intiLED is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * intiLED is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with intiLED.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * intiLED is a hardware and software platform used to control high
 * power LED strings.
 *
 *
 * USB stack derived from LUFA Generic HID Client side demo project.
 * https://github.com/abcminiuser/lufa
 *
 *
 */

#include "intiController.h"

#include <avr/wdt.h>
#include <avr/power.h>

#include "descriptors.h"
#include "AppConfig.h"

#include <LUFA/Drivers/USB/USB.h>
#include <LUFA/Platform/Platform.h>

#include <global.h>
#include <usb.h>
#include <rtc.h>
#include <settings.h>
#include <control.h>

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
    /* Disable watchdog if enabled by bootloader/fuses */
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    /* Disable clock division */
    clock_prescale_set(clock_div_1);
}

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
    SetupHardware();

    Usb      usb;
    Rtc      rtc;
    Settings settings;
    Control  control(settings.getEmitters(), rtc.now());

    for (;;)
    {
        // check for USB data
        // actual USB communications is handled by ISR
        //usb.tick();

        // one second tick
        if (rtc.tick())
        {
            DateTime now = rtc.now();
            control.tick(now);

            usb.send(control.getCurrent(now));
        }
    }
}
