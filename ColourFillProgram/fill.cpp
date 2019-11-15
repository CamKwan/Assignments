/* fill.cpp
   CSC 116 - Fall 2019
   
   Color Fill program
   - Usage: ./fill <input image> <output image> <x> <y> <r> <g> <b>
        where (x, y) is starting pixel of image with respect to top left corner
        and <r, g, b> is the desired color in RGB

   Cameron Kwan - 11/14/2019
 */

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <list>
#include "image.hpp"
#include <set>


int main (int argc, const char** argv){
    
    std::vector< std::string > args{};
    for(int i = 1; i < argc; i++){
        args.push_back(argv[i]);
    }

    if(args.size() != 7){
        std::cout << "Usage: ./fill <input image> <output image> <x> <y> <r> <g> <b>" << std::endl;
        return 1;
    }
    
    std::string input_filename {args.at(0)}, output_filename {args.at(1)};
    unsigned int start_x = std::stoi(args.at(2));
    unsigned int start_y = std::stoi(args.at(3));

    unsigned char r = std::stoi(args.at(4));
    unsigned char g = std::stoi(args.at(5));
    unsigned char b = std::stoi(args.at(6));

    try{
        Image Test{input_filename};
        if ( start_x > Test.get_width() - 1 || start_y > Test.get_height() - 1 ){
            std::cout << "Error: Invalid starting pixel" << std::endl;
            return 1;
        }
        if ( (int)r < 0 || (int)r > 255 || (int)g < 0 || (int)g > 255 || (int)b < 0 || (int)b > 255 ){
            std::cout << "Error: Invalid RGB fill colour" << std::endl;
            return 1;
        }
    } catch(std::runtime_error e){
        std::cout << "Error Unable to open input image" << std::endl;
        return 1;
    }
    Image I{input_filename};
    std::list< std::pair < unsigned int, unsigned int > > Q{};
    std::set< std::pair < unsigned int, unsigned int > > check{};
    std::pair< unsigned int, unsigned int > first_pair{start_x, start_y};
    Q.push_back(first_pair);
    check.insert(first_pair);
    while(!(Q.empty())){
        auto [x, y] = *Q.begin();
        Image::Pixel& P{I.at(x, y)};

        if( (x + 1) < I.get_width()){
            if (I.at(x + 1, y) == P){
                std::pair< unsigned int, unsigned int > down{x + 1, y};
                if(check.find(down) == check.end()){
                    Q.push_back(down);
                    check.insert(down);
                }
            }
        }
        if( (x - 1) < I.get_width()){
            if (I.at(x - 1, y) == P){
                std::pair< unsigned int, unsigned int > up{x - 1, y};
                if(check.find(up) == check.end()){
                    Q.push_back(up);
                    check.insert(up);
                }
            }
        }
        if( (y + 1) < I.get_height()){
            if (I.at(x, y + 1) == P){
                std::pair< unsigned int, unsigned int > right{x, y + 1};
                if(check.find(right) == check.end()){
                    Q.push_back(right);
                    check.insert(right);
                }
            }
        }
        if( (y - 1) < I.get_height()){
            if (I.at(x, y - 1) == P){
                std::pair< unsigned int, unsigned int > left{x, y - 1};
                if(check.find(left) == check.end()){
                    Q.push_back(left);
                    check.insert(left);
                }
            }
        }
        P.r = r;
        P.g = g;
        P.b = b;
        Q.pop_front();
        
    }

    try{
        I.save(output_filename);
    } catch(std::runtime_error e){
        std::cout << "Error: Unable to write output image" << std::endl;
        return 1;
    }
    
    

    return 0;
}