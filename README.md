# MetRada

## Overview

**MetRada** is a Python application designed to automatically update your Windows desktop background with the latest radar image from the Hungarian Meteorological Service's website. The application fetches the radar image every 10 minutes and updates the wallpaper accordingly. It uses UTC time to ensure that the correct image is retrieved based on a predefined schedule.

## Features

- **Automatic Updates**: Fetches and sets the radar image as the desktop wallpaper every 10 minutes.
- **UTC Time Handling**: Uses UTC time to ensure the correct image is retrieved.
- **Simple File Management**: Automatically saves and overwrites the image in a dedicated folder.
- **Windows Compatibility**: Designed specifically for Windows environments.

## Getting Started

### Prerequisites

- Python 3.6 or higher
- `requests` library
- `ctypes` library (included with Python standard library)

### Installation

1. **Clone the Repository**

   ```bash
   git clone https://github.com/Kisbivaly/MetRada.git
   cd MetRada
