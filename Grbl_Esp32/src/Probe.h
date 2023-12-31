#pragma once

/*
  Probe.h - code pertaining to probing methods
  Part of Grbl

  Copyright (c) 2014-2016 Sungeun K. Jeon for Gnea Research LLC

	2018 -	Bart Dring This file was modifed for use on the ESP32
					CPU. Do not use this with Grbl for atMega328P

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

// Values that define the probing state machine.
enum class Probe : uint8_t {
    Off    = 0,  // Probing disabled or not in use. (Must be zero.)
    Active = 1,  // Actively watching the input pin.
};

#define PROBE_READ_LOW    0
#define PROBE_READ_HIGH   1
#define PROBE_READ()      digitalRead(PROBE_PIN)

#define PROBE_DELAY_TIME  1000 // (ms)

 typedef enum{
    PROBE_NONE,
    PROBE_GET_STATUS,   // 没有触发，并正在测量
    PROBE_IS_WRONG,     // 触发了警报
    PROBE_WAIT_WRONG,   // 等待警报解除
    PROBE_IS_OK,        // 解除报警
 }PROBE_STATUS_T;


typedef struct {
  PROBE_STATUS_T status; 
  bool is_probe_open;  
  uint32_t probe_time_start;
  uint32_t probe_time_end;
}PROBE_CTRL_T;


// Probe pin initialization routine.
void probe_init();

// setup probing direction G38.2 vs. G38.4
void set_probe_direction(bool is_away);

// Returns probe pin state. Triggered = true. Called by gcode parser and probe state monitor.
bool probe_get_state();

// Monitors probe pin state and records the system position when detected. Called by the
// stepper ISR per ISR tick.
void probe_state_monitor();

void mks_probe_init(void);
void mks_probe_check(void);
void mks_probe_check_disable();
void mks_probe_check_enable();
