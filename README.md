# MetRada
Meterologyy Background Image Updater
Overview

Background Image Updater is a Python application designed to automatically update your Windows desktop background with the latest radar image from the Hungarian Meteorological Service's website. The application fetches the radar image every 10 minutes and updates the wallpaper accordingly. It uses UTC time to ensure that the correct image is retrieved based on a predefined schedule.
Features

    Automatic Updates: Fetches and sets the radar image as the desktop wallpaper every 10 minutes.
    UTC Time Handling: Uses UTC time to ensure the correct image is retrieved.
    Simple File Management: Automatically saves and overwrites the image in a dedicated folder.
    Windows Compatibility: Designed specifically for Windows environments.

Getting Started
Prerequisites

    Python 3.6 or higher
    requests library
    ctypes library (included with Python standard library)

Installation

    Clone the Repository

    bash

git clone https://github.com/yourusername/background-image-updater.git
cd background-image-updater

Install Required Packages

You need to install the required Python package if it's not already installed. You can do this using pip:

bash

    pip install requests

    Configure the Application

    Update the script to specify the URL pattern and path where images should be saved. The default configuration will save images in a képek folder relative to the script's location.

Usage

    Run the Script

    To start the background image updater, run the script:

    bash

python background_image_updater.py

The script will continuously fetch and update the desktop wallpaper with the latest radar image every 10 minutes.

Create an Executable (Optional)

If you prefer to run the application as a standalone executable, you can use PyInstaller:

bash

    pip install pyinstaller
    pyinstaller --onefile --noconsole background_image_updater.py

    This will generate an executable file in the dist directory, which you can run directly.

Code Explanation

    get_latest_image_url(): Calculates the URL for the radar image based on the current UTC time, rounded to the nearest 10 minutes.
    download_image(url, save_path): Downloads the radar image from the specified URL and saves it to the given path.
    set_background_image(image_path): Sets the downloaded image as the desktop wallpaper using Windows API calls.
    main(): Main loop that periodically downloads the latest radar image and updates the wallpaper.

Contributing

Feel free to submit issues, suggest improvements, or contribute to the project. Contributions are welcome!

    Fork the Repository
    Create a New Branch
    Commit Your Changes
    Push to the Branch
    Create a Pull Request

License

This project is licensed under the GNU General Public License (GPL) v3.0. See the LICENSE file for details.
Acknowledgements

    Python Standard Library
    PyInstaller for creating standalone executables
    Requests library for HTTP requests
    Hungarian Meteorological Service for providing radar images
