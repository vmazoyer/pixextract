#pixextract
Extract pixel values according to a given mask.

## Installation
This software requires OpenCV 3.1.0

## Usage
The pixels in the source image are selected by coloring pixels of same coordinates in a mask image.
Each color present in the mask can be associated with a specific label.
The values of the source pixels are printed with their corresponding label in a CSV format.

For now, the association between colors and labels is hardcoded and a modification requires the program to be compiled again.
The mask must have the same width and height as the source image.

## Hints
* A raster graphics editor that supports layers is convenient to create the mask.
* When saving the mask, pay special attention to the file format. Especially, formats that use lossy compression (such as JPEG) may produce artifacts and impair the mask.
