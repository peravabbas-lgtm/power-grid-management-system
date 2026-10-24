# Power Grid Management System

A console-based power grid management program written in C++. The program allows a user to monitor districts, manage the available power supply, shut off or restore electricity, assign technicians, and save or load grid data from text files.

## Features

- Load district and power-grid data from a text file
- Display the current total power supply
- View each district’s:
  - Name
  - District type
  - Number of residents
  - Power usage
  - Power status
  - Assigned technicians
- Sort districts by population
- Update the grid’s available power supply
- Shut off power to a district
- Restore power to a district
- Assign technicians to districts
- Detect when active power demand exceeds the available supply
- Save updated grid information to a text file
- Load a different grid file while the program is running

## How to Run

Compile with g++:

```bash
g++ main.cpp -o power_grid
```

Run the program:

```bash
./power_grid
```

(On Windows, run `power_grid.exe` instead.)

When prompted, enter the path to a data file. Two sample grids are included:

```text
data/sample_grid_1.txt
data/sample_grid_2.txt
```

## How the Program Works

The program begins by asking the user for the name of a data file. It loads the total power supply and information about each district into an array of structures.

Districts are automatically sorted from the lowest to highest number of residents. The user can then manage the power grid using a menu-driven interface.

When the combined demand of all powered districts exceeds the available supply, the program displays a critical warning and asks the user to shut off one or more districts.

## District Information

Each district stores the following information:

- District name
- District type
- Number of residents
- Required power in megawatts
- Whether the district currently has power
- Number of assigned technicians
- Names of assigned technicians

The information is stored using a C++ `struct`.

## Main Menu

```text
Main Menu
1- Status
2- Set Power Supply
3- Shutoff Power
4- Restore Power
5- Assign Technician
6- Save
7- Load
8- Exit
```

## Data File Format

Grid files are plain text, one value per line:

```text
<total power supply in MW>
<number of districts>
<district name>
<district type>
<number of residents>
<power required in MW>
<has power: 1 or 0>
<number of technicians>
<technician name, one line each>
```

The district block repeats once per district. Example (`data/sample_grid_1.txt`):

```text
1300
2
Lower Point
COMMERCIAL
500
600
1
1
Bobby Bob
Downtown Bayside
COMMERCIAL
200
400
1
2
Anna Ann
Apple App
```

## Project Structure

```text
main.cpp                 Program source code
data/sample_grid_1.txt   Sample grid with 2 districts
data/sample_grid_2.txt   Sample grid with 3 districts
```
