/* image.hpp
   CSC 116 - Fall 2019 - Assignment 4

   Defines an Image class with a simplified interface to the LodePNG
   library. You are not expected to understand how to use the LodePNG library
   directly, and you don't necessarily have to understand how the Image class
   works internally, although you will have to use the Image and Image::Pixel
   classes in your code.

   B. Bird - 08/09/2019
 */

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>
#include <vector>
#include <stdexcept>

#include "lodepng.hpp"

class Image{
public:
    //The Pixel class is scoped inside of Image, so to use this class outside of the Image class,
    //you will need to refer to it as "Image::Pixel".
    class Pixel{
    public:
        unsigned char r, g, b;
        Pixel(unsigned char r, unsigned char g, unsigned char b): r {r}, g {g}, b {b} {

        }
        bool operator==(const Pixel& other) const{
            return r == other.r && g == other.g && b == other.b;
        }
        bool operator!=(const Pixel& other) const{
            return !(*this == other);
        }
    };
private:
    std::vector<Pixel> pixels;
    unsigned int width, height;
public:
    /* Constructor to load a saved PNG image into an Image object. */
    Image(std::string filename){
        std::vector<unsigned char> raw_pixels {};
        unsigned int error_code = lodepng::decode(raw_pixels, width, height, filename.c_str());
        if(error_code > 0)
            throw std::runtime_error("Error loading " + filename + ": " + lodepng_error_text(error_code));
        for(unsigned int i = 0; i < width*height; i++){
            pixels.emplace_back(raw_pixels.at(i*4), raw_pixels.at(i*4+1), raw_pixels.at(i*4+2));
        }
    }

    /* Constructor to create a blank image of a particular width and height. */
    Image(unsigned int width, unsigned int height){
        for(unsigned int i = 0; i < width*height; i++){
            pixels.emplace_back(0,0,0);
        }
    }

    /* save(filename)
       Save this image with the provided filename (which is expected to end in ".png").
       If the image cannot be saved, the function throws a std::runtime_error.
    */
    void save(std::string filename){
        std::vector<unsigned char> raw_pixels {};
        for(auto& P: pixels){
            raw_pixels.push_back(P.r);
            raw_pixels.push_back(P.g);
            raw_pixels.push_back(P.b);
            raw_pixels.push_back(255);
        }

        unsigned int error_code = lodepng::encode(filename.c_str(), raw_pixels, width, height);
        if(error_code > 0)
            throw std::runtime_error("Error saving " + filename + ": " + lodepng_error_text(error_code));
    }

    /* get_width()
       Return the width of this image.
    */
    unsigned int get_width(){
        return width;
    }

    /* get_height()
       Return the height of this image.
    */
    unsigned int get_height(){
        return height;
    }

    /* at()
       Given x and y coordinates, return the pixel at those coordinates.
       If invalid coordinates are given, this function throws a std::out_of_range
       exception.
    */
    Pixel& at(unsigned int x, unsigned int y){
        if (x >= get_width())
            throw std::out_of_range("Invalid x coordinate (x = "+std::to_string(x)+", width = "+std::to_string(get_width())+")");
        if (y > get_height())
            throw std::out_of_range("Invalid y coordinate (y = "+std::to_string(y)+", height = "+std::to_string(get_height())+")");
        return pixels.at(y*width + x);
    }

};

#endif