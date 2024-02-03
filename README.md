## 🌻 CursedRay: Hardware-accelerated path tracer

CursedRay is a hardware-accelerated path tracer that uses the OpenCL (version: 3.0) API. Programmed in C++.

## Usage

```
--help:                  Print this help message
--version:               Print the version number
--license:               Print the license
--clear-on-exit:         Clear the terminal on exit
                         Default is '0'
--dont-suppress-banners: Don't suppress notcurses' banners
                         Default is '1'
--blitter:               Blitter to use
                         Valid values are '1x1', '2x1', '2x2', '3x2', and 'pixel'
                         Default is '1x1'
--log-level:             Log level to use
                         Valid values are 'fatal', 'error', 'panic', 'debug',
                         'info', 'warning', 'silent', 'trace', and 'verbose'
                         Default is 'silent'
--dump-logs:             Dump logs to stdout at the end
--clear-color:           Set background color
                         Default is '(0.200000, 0.200000, 0.300000, 1.000000)'
--device-type:           Type of the OpenCL device
                         Valid values are 'cpu', 'gpu',
                         'accelerator', and 'default'
                         Default is 'default'
```

## Features

- [ ] Ray-sphere intersection

## License

Copyright (C) 2024 Omar Huseynov

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
