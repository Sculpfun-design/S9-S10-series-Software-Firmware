# S9-S10-series-Software-Firmware

## Step.1 Download the current firmware

To download the current firmware, you can use git or download a file in. zip format. After downloading, the. zip format requires additional decompression into a separate folder.

## Step.2 Install vscode

Download address for vscode: https://code.visualstudio.com/

Download and install the corresponding version based on your platform, such as Windows/macos/Linux.

## Step.3 Installing PlatformIO plugins in vscode

Description document for platformIO: https://docs.platformio.org/

Note: This will take a considerable amount of time. If it is Linux/MacOS, it is important to note that you have your own Python version and need to use a version of Python 3.6 or higher. Some MacOS or Linux versions have Python 2.7 installed by default and do not have Python 3. Please refer to the relevant documentation for PlatformIO for details.

# If you're ready

Step.1 Open the folder of this project through vscode.

Step.2 Waiting for PlatformIO to load ready.

Step.3 After everything is ready for platformIO, you can compile it by clicking "√" below, and clicking "→" will execute the compilation and download.

Note：Before this, it is necessary to confirm the port number of the serial port after connecting to the machine, which is set in platformio.ini.

windows:

`upload_port = COM8`

linux:

`upload_port = /dev/ttyUSB0`
