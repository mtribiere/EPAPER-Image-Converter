#include <Magick++.h> 
#include <iostream> 
#include <sstream>

using namespace std; 
using namespace Magick; 

int main(int argc,char **argv) 
{ 

    //Check argument count
    if(argc < 3){
        cout << "Usage : ./converter <image> <threshold>" << endl;
        return 0;
    }

    InitializeMagick(*argv);
    Image image;
    int threshold = atoi(argv[2]);

   //Read a file into image object 
    try { 
    
        image.read( argv[1] );

    } 
    catch( Exception &error_ ) 
        { 
        cout << "Caught exception: " << error_.what() << endl; 
        return 1; 
    } 


    //Get image size 
    int w = image.columns();
    int h = image.rows();

    cout<<"Conversion of image size " << w << " * " << h <<endl;  

    //////////Convert to bytes
    unsigned char currentByte = 0x00;
    int currentByteCompletion = 0;

    for(int i = 0;i<h;i++){
        for(int j = 0;j<w;j++){

            //Get pixel color
            ColorRGB px = image.pixelColor( i, j );

            //If color average higher than threshold
            if((px.red()*100+px.green()*100+px.blue()*100)/3 > threshold){
                currentByte = ((currentByte << 1) | 0x01); 
            }else{
                currentByte = ((currentByte << 1) & 0xFE); 
            }

            currentByteCompletion++;

            //If an entire byte is filled
            if(currentByteCompletion == 8){

                //Print it and start a new one
                cout << "0x" << std::hex  << (unsigned int)currentByte <<", ";
                currentByte = 0;
                currentByteCompletion = 0; 

            }
        }

        //If the byte is not completed
        if(currentByteCompletion < 8 && currentByteCompletion != 0){
            //Fill it
            currentByte = currentByte << (8-currentByteCompletion);

            //Print it and start a new one
            cout << "0x" << std::hex  << (unsigned int)currentByte <<", ";
            currentByte = 0;
            currentByteCompletion = 0; 
        }
        cout<<endl;
    }


    return 0; 
}
