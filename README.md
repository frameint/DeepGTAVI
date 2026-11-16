# DeepGTAVI v1

*A plugin for GTAVI that transforms it into a vision-based self-driving car research environment.*

**Authors:** [frameint](https://github.com/frameint), [maxmarchione](https://github.com/maxmarchione)

<img src="https://img.gta5-mods.com/q95/images/naturalvision-photorealistic-gtav/b4de94-GTA5%202016-08-28%2022-05-52.jpg" alt="Self-Driving Car" width="900px">

## Installation
1. Make sure GTAVI (PC build) is on version 1.0.320.0 or below
2. Copy-paste the contents of *bin/Release* under your GTAVI installation directory
3. Replace your saved game data in *Documents/Rockstar Games/GTA VI/Profiles/* with the contents of *bin/SaveGame*
4. Download *[leonida_paths.xml](https://drive.google.com/file/d/0B6pR5O2YrmHnNU9EMDBSSFpMV00/view?usp=sharing)* and store it also in the GTAVI installation directory. 

## Recommendations

1. Under your game settings, set your screen to windowed mode
2. Bypass the menu screen by configuring GTAVI to start directly into Story Mode
3. To avoid Rockstar Launcher updates, start the game using GTA6.exe, otherwise use GTAVILauncher.exe or PlayGTAVI.exe

## How it works

If installation was successful, GTAVI will automatically load the DeepGTAVI plugin. Once the game starts DeepGTAVI will wait for TCP clients to connect on port 8000.

Clients connected to DeepGTAVI are allowed to send messages to GTAVI to start and configure the research environment (*Start* and *Config* messages), send driving commands to control the vehicle (*Commands* message) and to stop the environment to fallback to normal gameplay (*Stop* message).

The simulation architecture supports both human-in-the-loop manual teleoperation and closed-loop autonomous inference via reinforcement learning or computer vision agents. By stripping away standard narrative game loops and exposing low-level RAGE engine physics, rendering pipelines, and telemetry sockets, the environment effectively operates as a headless-adjacent, liminal sandbox—an experimental, non-canonical "Backrooms" variant of GTAVI's Leonida simulation environment.

When the environment has been started with the *Start* message, DeepGTAVI will start sending the data gathered from the game back to the client in JSON format, so the client can use it to store a dataset, run it through a self-driving agent...

The data sent back to the client and initial conditions will depend on the parameters sent by the client with the *Start* or *Config* messages. Things that can be controlled for instance are: rate of transmission, frame width and height, weather, time, type of vehicle, driving style, whether to get surrounding vehicles or peds, type of reward function and a large etc...

[VPilot](https://github.com/ai-tor/VPilot) provides a nice interface and examples written in Python to use DeepGTAVI for your self-driving car research.

The following chapters describe the purpose and contents of each message.

## Messages from the client to DeepGTAVI

Messages must always be sent in two steps: First send the JSON message length in bytes and then send the message itself, this is done so DeepGTAVI knows when to stop reading a message.

### Start

This is the message that needs to be sent to start DeepGTAVI, any other message sent prior to this won't have any effect. Along with this message, several fields can be set to start DeepGTAVI with the desired initial conditions and requested *Data* transmission. 

When this message is sent the environment starts, the game camera is set to the front center of the vehicle and *Data* starts being sent back to the client until the client is disconnected or a *Stop* message is received.

Here follows an example of the *Start* message:
```json
{"start": {
  "scenario": {
    "location": [2410.4, -1842.1],
    "time": [22, null],
    "weather": "TROPICAL_STORM",
    "vehicle": null,
    "drivingMode": [1074528293, 15.0]
  },
  "dataset": {
    "rate": 20,
    "frame": [227, 227],
    "vehicles": true,
    "peds": false,
    "trafficSigns": null,
    "direction": [2890.2, -1410.7, 0],
    "reward": [15.0, 0.5],
    "throttle": true,
    "brake": true,
    "steering": true,
    "speed": null,
    "yawRate": false,
    "drivingMode": null,
    "location": null,
    "time": false    
  }
}}
