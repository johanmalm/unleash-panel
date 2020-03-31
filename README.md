# unleash-panel

## Aims

- Be simple
- Be stand-alone
- Work with X11 and Wayland
- Keep feature-set small

## Architecture

- C++
- Qt5

## Dependencies

<b>Debian</b> qt5-default, libqt5x11extras5-dev

<b>Arch</b> qt5-base, qt5-x11extras

## Build

    qmake
    make

## Implementation

| File           | Purpose                                         |
|----------------|-------------------------------------------------|
| panel.cpp      | Create main window and control panel components |
| background.cpp | Draw panel background                           |
| task.cpp       | Draw taskbar tasks                              |

