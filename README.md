# Google Earth Tree Calculator

This project was developed in C++ with a graphical interface built on the Qt Framework. The software calculates and visualizes a "Christmas tree" shape on Earth's surface in Google Earth, using a user-defined starting point.

<picture>
  <source
    srcset="https://github.com/kiraDegu/FoodDeliveryApp/blob/dev/README-imgs/6.png"
    media="(prefers-color-scheme: dark)"
  />
  <source
    srcset="https://github.com/kiraDegu/FoodDeliveryApp/blob/dev/README-imgs/6.png"
    media="(prefers-color-scheme: light), (prefers-color-scheme: no-preference)"
  />
  <img src="https://github-readme-stats.vercel.app/api?username=anuraghazra&show_icons=true" />
</picture>


## Project Description

The goal of this program is to calculate a sequence of points on Earth's surface, beginning from an origin point and drawing a path in the shape of a Christmas tree. The software exports the points into a `.kml` file, which can be viewed in Google Earth to display the calculated path.

### Key Features

- **User Input**: The software takes the following inputs:
  - Geographical coordinates (latitude and longitude) for the starting point
  - Angle relative to North (heading)
  - Distance between points
  - Number of points needed to draw the Christmas tree shape
 
    <picture>
  <source
    srcset="https://github.com/kiraDegu/FoodDeliveryApp/blob/dev/README-imgs/6.png"
    media="(prefers-color-scheme: dark)"
  />
  <source
    srcset="https://github.com/kiraDegu/FoodDeliveryApp/blob/dev/README-imgs/6.png"
    media="(prefers-color-scheme: light), (prefers-color-scheme: no-preference)"
  />
  <img src="https://github-readme-stats.vercel.app/api?username=anuraghazra&show_icons=true" />
</picture>

- **Earth Calculation Models**: Choose among different models to represent the Earth's surface:
  - Flat Earth model
  - Spherical Earth model
  - WGS84 model

- **Calculation Methods**:
  - **Point-to-point calculation**: Each new point is calculated based on the previous point.
  - **From-origin calculation**: Each new point is calculated relative to the initial origin point.

- **Extreme Case Handling**: The software manages specific or edge cases to ensure accurate results.

## Project Structure

The software is developed using object-oriented programming principles, with a modular architecture that efficiently handles different parameters and calculation models.

## Development Team

The project was completed over 4 days by a team consisting of:

- Chiara De Guglielmo
- Andrea Malesta
- Nicholas Mallamaci

## Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/kiraDegu/GoogleEarthTreeCalculator-Software.git
   cd GoogleEarthTreeCalculator-Software
   ```

2. **Compile**:
   Ensure you have Qt and a C++ compiler installed. Compile the project via Qt Creator or from the command line.

3. **Run**:
   After compiling, start the application and enter the required data in the graphical interface.

## Usage

1. Enter the latitude and longitude coordinates of the origin point.
2. Set the heading (angle relative to north) and the desired distance between points.
3. Choose the Earth model and preferred calculation method.
4. Click "Calculate" to generate points and save the `.kml` file.
5. Import the file into Google Earth to view the generated path.

## Technologies Used

- **Language**: C++
- **Framework**: Qt
- **Output Format**: KML (Keyhole Markup Language) for Google Earth compatibility
