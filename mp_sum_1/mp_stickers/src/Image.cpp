#include "Image.h"
#include <string>
Image::Image (unsigned int width, unsigned int height){
    PNG png(width, height);
}
void Image::lighten (){
    for(int i=0;i<(int)PNG::width();++i){
        for(int j=0;j<(int)PNG::height();++j){
            if(getPixel(i,j).l<=0.9){
                getPixel(i,j).l+=0.1;
            } else{
                getPixel(i,j).l=1;
            }
        }
    }
}
void Image::lighten (double amount){
    double rest=1-amount;
    for(int i=0;i<(int)PNG::width();++i){
        for(int j=0;j<(int)PNG::height();++j){
            if(getPixel(i,j).l<=rest){
                getPixel(i,j).l+=amount;
            } else{
                getPixel(i,j).l=1;
            }
        }
    }
}
void Image::darken (){
    for(int i=0;i<(int)PNG::width();++i){
        for(int j=0;j<(int)PNG::height();++j){
            if(getPixel(i,j).l<=1.1){
                getPixel(i,j).l-=0.1;
            } else{
                getPixel(i,j).l=1;
            }
        }
    }
}
void Image::darken (double amount){
    for(int i=0;i<(int)PNG::width();++i){
        for(int j=0;j<(int)PNG::height();++j){
            double rest=getPixel(i,j).l-amount;
            if(rest>0){
                getPixel(i,j).l-=amount;
            }else{
                getPixel(i,j).l=0;
            }
        }
    }
}
void Image::saturate (){
    for(int i=0;i<(int)PNG::width();++i){
        for(int j=0;j<(int)PNG::height();++j){
            if(getPixel(i,j).s<=0.9){
                getPixel(i,j).s+=0.1;
            } else{
                getPixel(i,j).s=1;
            }
        }
    }
}
void Image::saturate (double amount){
    double rest=1-amount;
    for(int i=0;i<(int)PNG::width();++i){
        for(int j=0;j<(int)PNG::height();++j){
            if(getPixel(i,j).s<=rest){
                getPixel(i,j).s+=amount;
            } else{
                getPixel(i,j).s=1;
            }
        }
    }
}
void Image::desaturate (){
    for(int i=0;i<(int)PNG::width();++i){
        for(int j=0;j<(int)PNG::height();++j){
            if(getPixel(i,j).s<=1.1){
                getPixel(i,j).s-=0.1;
            } else{
                getPixel(i,j).s=1;
            }
        }
    }
}
void Image::desaturate (double amount){
    double rest=1+amount;
    for(int i=0;i<(int)PNG::width();++i){
        for(int j=0;j<(int)PNG::height();++j){
            if(getPixel(i,j).s<=rest){
                getPixel(i,j).s-=amount;
            } else{
                getPixel(i,j).s=1;
            }
        }
    }
}
void Image::grayscale (){
    for(int i=0;i<(int)PNG::width();++i){
        for(int j=0;j<(int)PNG::height();++j){
            if(getPixel(i,j).l<=0.5){
                getPixel(i,j).l=0;
            } else{
                getPixel(i,j).l=1;
            }
        }
    }
} 
void Image::rotateColor (double degrees){
    for(int i=0;i<(int)PNG::width();++i){
        for(int j=0;j<(int)PNG::height();++j){
            int rest=((int)getPixel(i,j).h + (int)degrees + 360) % 360;
            getPixel(i,j).h=rest;
        }
    }
}
void Image::illinify (){
    for(int i=0;i<(int)PNG::width();++i){
        for(int j=0;j<(int)PNG::height();++j){
            int hue=getPixel(i,j).h;
            int toOrange=0;
            int toBlue=0;
            if (hue>=toOrange){
                if (hue<=toBlue){
                    toOrange=hue-11;
                    toBlue=216-hue;
                }
            } else{
                toBlue=hue-216;
            }
            toOrange=11-hue;
            toBlue=216-hue;
            if(toOrange<=toBlue){
                getPixel(i,j).h=11;
            } else{
                getPixel(i,j).h=216;
            }
        }
    }
}
void Image::scale (double factor){
    PNG oldPNG(*this);
    if (factor==0.5){
        PNG png((int)PNG::width()/2, (int)PNG::height()/2);
        resize((int)PNG::width()/2,(int)PNG::height()/2);
    }else if (factor==2){
        double width=(int)PNG::width()*2;
        double height=(int)PNG::height()*2;
        PNG png(width, height);
        resize(width,height);
    }
    for (int i=0; i<(int)width(); i++){
        for(int j=0; j<(int)height(); j++){
            int oldI=(int)i/factor;
            int oldJ=(int)j/factor;
            getPixel(i,j)=oldPNG.getPixel(oldI,oldJ);
        }
    }
}
void Image::scale (unsigned w, unsigned h){
    PNG oldPNG(*this);
    double width=(int)PNG::width();
    double height=(int)PNG::height();
    double ratio1=w/width;
    double ratio2=h/height;
    double ratio3=ratio1;
    if(ratio1>ratio2){
        ratio3=ratio2;
    }
    width=width*ratio3;
    height=height*ratio3;
    PNG png(width, height);
    resize(width,height);
    for (int i=0; i<width; i++){
        for(int j=0; j<height; j++){
            int oldI=(int)i/ratio3;
            int oldJ=(int)j/ratio3;
            getPixel(i,j)=oldPNG.getPixel(oldI,oldJ);
        }
    }

}