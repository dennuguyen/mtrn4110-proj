# Phase D

## Gantt Chart

```mermaid
gantt
    title Gantt Chart for MTRN4110
    dateFormat  DD-MM-YYYY
    section Solution Comparison
    Analyse Phase A Solutions       :04-08-2021, 07-08-2021
    Analyse Phase B Solutions       :04-08-2021, 05-08-2021
    Analyse Phase C Solution        :04-08-2021, 05-08-2021

    section Solution Integration
    Phase A Integration             :07-08-2021, 4d
    Phase B Integration             :05-08-2021, 6d
    Phase C Integration             :05-08-2021, 6d

    section Phase Integration
    Phase Integrations              :08-08-2021, 2d

    section Extra Features
    Teleoperation              :12-08-2021, 6d
    Obstacle avoidance         :12-08-2021, 6d
    Bang-bang trajectory       :12-08-2021, 6d

    section Video
    Record Comparison Milestone           :09-08-2021, 3d
    Record Integration Milestones         :12-08-2021, 4d
    Record Extra Features Milestones      :16-08-2021, 4d
    Edit Video Segments                   :20-08-2021, 1d
```

## Python 3.6 Installation

Linux:
```
sudo apt-get install python3.6
```

Windows:

[Download link](https://www.python.org/ftp/python/3.6.0/python-3.6.0-amd64.exe)

## Python Requirements

Linux:
```
pip install -r requirements.txt
```

Windows:
```
py -m pip install -r requirements.txt
```

## Cython Installation

Linux:
```
pip install cython
```

## Build Instructions

`.pyx` files currently should be compiled on Ubuntu by running `cython-build-script.sh`. The option to compile on other OS has not been explored.


