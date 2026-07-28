# Ready, Set, Record! — The Double Motor

**TU11_T09_430** — Alvin Park, Ethan Batiste, Hillary Sit, Yvonne Luo

An accessible, motorized GoPro mount that lets Jonathan, a participant at Pegasus
Toronto, independently frame and start/stop his own footage — no assistance from
primary counsellors required.

## The opportunity

[Pegasus Toronto](https://www.pegasustoronto.ca/) is a day program for adults
with developmental disabilities. Its participants ("Pegasus community
members") write and shoot short films for the annual **Pegasus Incredible Film
Festival (PIFF)**. Jonathan, a participant at the Matty Eckler Community Centre
location, loves filming but currently records by resting a GoPro HERO10 Black
in his lap:

- He can't hold the camera at eye level — limited arm strength means he can
  only hold ~200 g for about 15 seconds.
- Cortical Vision Impairment means he needs to be within ~20 cm of the GoPro's
  buttons to see them, and they lack the contrast/tactile feedback he needs.
- Limited wrist pronation/supination makes twisting motions (e.g. a clamp
  knob) difficult.
- As a result, a primary counsellor currently has to start/stop recording and
  set the angle for him.

Full stakeholder analysis, needs/goals/objectives, and reference-design
research are in [`rfpmark.md`](rfpmark.md), the project's Request for
Proposal.

## The design: Double Motor

A two-axis motorized GoPro mount, strapped to Jonathan's wheelchair armrest
with velcro (to avoid modifying the chair) and controlled wirelessly from an
Apple Watch:

- **Pan/tilt** — a stepper motor rotates the mount horizontally and a servo
  tilts it vertically, so Jonathan can reframe shots without touching the
  camera.
- **Rigid mount** — minimizes vibration/camera shake versus handheld footage.
- **Apple Watch interface** — familiar to Jonathan, connects over Bluetooth,
  gives haptic feedback, and requires very little force to operate
  (large color-coded tiles: record, reset, and four directional arrows).
- Meets the design objectives in the RFP: improve autonomy to start/stop
  recording, increase the range of capturable angles, minimize operating
  force, preserve footage quality, and stay intuitive enough to learn in a
  few sessions.

See [`rfpmark.md`](rfpmark.md) for the full needs/goals/objectives tree, and
the poster/one-pager images in this conversation for the visual summary
(exploded view of the mount, verification & testing table, and sustainability
notes — reduced inequalities via inclusive, adaptable design).

Measured prototype performance (from the one-pager):

| Test                        | Result |
|-----------------------------|--------|
| Force required              | < 0.6 N |
| Unique rotation planes       | 2 |
| Angle accuracy              | 0.74° |
| Vibration amplitude         | ~0 mm |

## Repository contents

This repo holds the two halves of the working prototype:

```
src/main.cpp      Arduino firmware (PlatformIO, env "uno")
platformio.ini    Board/framework/library config
.vscode/          Draft SwiftUI sources for the watch + Mac BLE prototype
```

### Firmware — `src/main.cpp`

Runs on an Arduino Uno and currently drives the mount from a **joystick**
(two analog inputs) rather than the BLE commands below:

- `Stepper` (2048 steps/rev, pins 2/4/5/7) rotates the mount horizontally when
  the joystick's X-axis is pushed past a dead zone around its calibrated
  neutral position.
- `Servo` (pin 6) tilts the mount vertically the same way, driven by the
  joystick's Y-axis.

This is the analog-joystick control path used for early bench testing of the
motors; it has not yet been merged with the Bluetooth command protocol sent
by the Swift apps below (see **Next steps**).

### Watch control prototype — `.vscode/`

These are draft SwiftUI files (exported without their Xcode project wrapper,
which is why they live under `.vscode/` — pull them into a proper Xcode
project to build them):

- **`Watch App Interface`** — the actual watchOS app UI. A Control-Center-style
  grid of six tiles (record/reset + four arrows) with haptic feedback on tap.
- **`Apple Watch MacSim - Content View`** — a macOS stand-in for the watch UI
  (drag-to-hold directional buttons, record, reset) used to test the BLE link
  from a Mac before deploying to a physical watch.
- **`AppleWatch MacSim - BLE Manager`** — `BLEManager`, a `CBCentralManager`
  wrapper that scans for a BLE peripheral named `DSD TECH` (an HM-10 clone
  module), writes to characteristic `FFE1`, and sends single-shot (`REC`,
  `RESET`) or repeated (`U`/`D`/`L`/`R`, then `S` to stop) string commands.

**Note:** the watch UI's buttons currently just log to the console and don't
yet call into `BLEManager` — only the Mac-simulator content view is wired up
end-to-end.

## Status & next steps

Per the RFP conclusion and the one-pager's "Next Steps":

- [ ] Wire the watchOS UI's button actions to `BLEManager` (currently only
      the Mac simulator sends commands).
- [ ] Update `src/main.cpp` to parse the `U`/`D`/`L`/`R`/`S`/`REC`/`RESET`
      serial commands from the HM-10 instead of (or alongside) joystick input.
- [ ] Material selection for the mount/enclosure.
- [ ] Safety testing with a high-fidelity prototype (edge radii, drop test,
      60-minute continuous attachment — see Objectives 4.3.1, 4.5.2, 4.5.3 in
      the RFP).
- [ ] Testing against relevant ISOs.
- [ ] Stakeholder validation with Jonathan and Pegasus MEC staff on a
      functional prototype.

## Background reading

- [`rfpmark.md`](rfpmark.md) — full Request for Proposal: stakeholder
  analysis, needs/goals/objectives, and reference-design evaluation.
- Project poster and one-pager (Praxis I, University of Toronto Engineering
  Science) summarize the opportunity, the Double Motor design, verification
  results, and sustainability rationale (UN SDG 10: Reduced Inequalities).
