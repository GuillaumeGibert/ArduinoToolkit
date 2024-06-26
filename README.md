# Arduino Toolkit

## About The Project

[![Project Screen Shot][project-screenshot]]()

This repository contains a series of code for Arduino boards [Arduino](https://www.arduino.cc/) to deal with serial communication, sampling...

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Built With

* [![Arduino][arduino-shield]][arduino-url]
* [![Python][python-shield]][python-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started

To set up the project locally, you need to install (if not already the case) some dependencies.
To get a local copy up and running follow these steps.

### Prerequisites

* Arduino

Launch Arduino IDE

* Python

Install the pySerial library
  ```sh
  pip install pyserial
  ```
  
### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/GuillaumeGibert/ArduinoToolkit.git
   ```
2. Open Arduino IDE
3. Open one of the provided code
4. Compile and upload it to your Arduino board

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- USAGE EXAMPLES -->
## Usage

### Test the serial communications

1. Open Arduino IDE
2. Open the code `testSerialCommunication.ino`
3. Compile and upload it to your Arduino board
4. Open the Serial monitor
5. Set the baudrate to 115200 bauds
6. Write 
```sh
Data:200;0
```
The following message should be displayed on the Serial monitor:
```sh
(x,y)=(200,0)
```

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- LICENSE -->
## License

Distributed under the GPL License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- CONTACT -->
## Contact

Guillaume Gibert

Project Link: [https://github.com/GuillaumeGibert/Polargraph](https://github.com/GuillaumeGibert/ArduinoToolkit)

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[arduino-shield]: https://img.shields.io/badge/Arduino_IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white
[arduino-url]: https://www.arduino.cc/
[python-shield]: https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white
[python-url]: https://www.python.org/
[opencv-shield]: https://img.shields.io/badge/OpenCV-27338e?style=for-the-badge&logo=OpenCV&logoColor=white
[opencv-url]: https://opencv.org/

[project-screenshot]: images/screenshot.png

[contributors-shield]: https://img.shields.io/github/contributors/GuillaumeGibert/Polargraph.svg?style=for-the-badge
[contributors-url]: https://github.com/GuillaumeGibert/Polargraph/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/GuillaumeGibert/Polargraph.svg?style=for-the-badge
[forks-url]: https://github.com/GuillaumeGibert/Polargraph/network/members
[stars-shield]: https://img.shields.io/github/stars/GuillaumeGibert/Polargraph.svg?style=for-the-badge
[stars-url]: https://github.com/GuillaumeGibert/Polargraph/stargazers
[issues-shield]: https://img.shields.io/github/issues/GuillaumeGibert/Polargraph.svg?style=for-the-badge
[issues-url]: https://github.com/GuillaumeGibert/Polargraph/issues
[license-shield]: https://img.shields.io/github/license/GuillaumeGibert/Polargraph.svg?style=for-the-badge
[license-url]: https://github.com/GuillaumeGibert/Polargraph/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/guillaume-gibert-06502ba4
