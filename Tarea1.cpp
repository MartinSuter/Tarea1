#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"
#include <iostream>
#include <fstream>

using namespace std;

struct Imagen{
    unsigned char* data;
    int width, height, channels;
};

Imagen* load(const char* filename) {
    Imagen* img = new Imagen();
    img->data = stbi_load(filename, &img->width, &img->height, &img->channels, 0);
    return img;
}

void save(Imagen* img, const char* filename) {
    stbi_write_png(filename, img->width, img->height, img->channels, img->data, img->width * img->channels);
    cout << "Imagen guardada:  " << filename << "\n";
}

/*int main() {

    Imagen* img = load("Pikachu.png");

    img->data[101] = 0;
    img->data[102] = 0;
    img->data[103] = 0;
    img->data[104] = 0;
    img->data[105] = 0;
    img->data[106] = 0;

    save(img, "output.png");
} */

void espejo(Imagen* img){

    //Recorremos cada fila de la imagen hasta la mitad 
    for (int y = 0; y < img->height ; y++){
        for (int x = 0; x < (img->width)/2 ; x++){

            //Encontramos valores para cada pixel del lado izquierdo y derecho de la imagen
            int pixeles_izq = (y * img->width + x) * img->channels;
            int pixeles_der = (y * img->width + (img->width - 1 - x)) * img->channels;


            //En un for recorriendo los canales RGB de cada pixel los intercambiamos de lado usando swap izquierdo por derecho
            for (int c = 0; c < img->channels; c++){

                swap(img->data[pixeles_izq + c], img->data[pixeles_der + c]);

            }

        }
    }
        
}

void giro_horario(Imagen* img){

    int nuevo_ancho = img->height;
    int nuevo_alto = img->width;
    int nuevo_channel = img->channels;
    
    //Creamos una nueva imagen para almacenar los nuevos datos invertidos en las variables de arriba
    unsigned char* nuevosdatos = new unsigned char[nuevo_ancho * nuevo_alto * nuevo_channel];
    
    //Hacemos un for para ir aplicando la rotacion de los pixeles
    for(int y = 0; y < img->height; y++){
        for (int x = 0; x < img->width; x++){

            int imagen_original = (y * img->height + x) * img->channels;
            int nuevo_x = (img->height - 1) - y;
            int nuevo_y = x;
            int nueva_imagen = (nuevo_y * nuevo_ancho + nuevo_x) * nuevo_channel;

            //Copiamos los datos de cada pixel habiendolos rotado
            for (int c = 0; c < nuevo_channel; c++){

                nuevosdatos[nueva_imagen + c] = img->data[imagen_original + c];

            }
    
        }
    }

    //reemplazamos los valores originales de la imagen por la de el producto rotado
    delete [] img->data;

    img->data = nuevosdatos;
    img->width = nuevo_ancho;
    img->height = nuevo_alto;

}

void atenuacion(Imagen*img){

    for (int y = 0; y < img->height ; y++){
        for (int x = 0; x < img->width ; x++){

            int pixeles = (y * img->width + x) * img->channels;
            
            for (int c = 0; c < (img->channels - 1); c++){

                img->data[pixeles + c] *= 0.5;

            }
       }                  
    }   
}

void gris(Imagen*img){
    for(int y = 0; y < img->height; y++){
        for (int x = 0; x < img->width; x++){

            int pixeles = (y * img->width + x) * img->channels;
            int suma = 0;
            int promedio = 0;

            for (int c = 0; c < (img->channels - 1); c++){

                suma += img->data[pixeles + c];
                
            }

            promedio = suma / 3;

            for (int c = 0; c < (img->channels - 1); c++){

                img->data[pixeles + c] = promedio;
            }

        }
    }
}



int main(){
    Imagen* img = load("Pikachu.png");
    gris(img);
    save(img, "output.png");
    cout << img->channels << endl;
    cout << img->height << endl;
    cout << img->width << endl;
}