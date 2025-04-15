# RTSP Radio

RTSP Radio is a project designed to stream audio using the RTSP (Real-Time Streaming Protocol). This repository contains the necessary code and resources to set up and manage your own RTSP-based radio streaming service.

## Features

- **Real-Time Audio Streaming**: Stream audio in real-time using RTSP.
- **Customizable**: Configure the streaming settings to suit your needs.
- **Cross-Platform**: Compatible with multiple platforms and devices.

## Installation

1. Clone the repository:

```bash
git clone https://github.com/George-Madeley/RTSP-Radio.git
```

2. Navigate to the project directory:

```bash
cd RTSP-Radio
```

3. Install dependencies:

```bash
cd build
cmake ..
cmake --build .
```

## Usage

1. Start the RTSP server:

```bash
./RtspRadio.exe
```

2. Connect to the server using an RTSP client:

```bash
rtsp://<server-ip>:<port>/<stream-name>
```

## Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository.
2. Create a new branch:

```bash
git checkout -b feature-name
```

3. Commit your changes:

```bash
git commit -m "Add feature-name"
```

4. Push to your branch:

```bash
git push origin feature-name
```

5. Open a pull request.

## License

This project is licensed under the [MIT License](LICENSE).

## Contact

For questions or support, please contact [george.madeley@outlook.com].
