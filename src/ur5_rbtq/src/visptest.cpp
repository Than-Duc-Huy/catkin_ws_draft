#include <visp/vpImage.h>
#include <visp_bridge/3dpose.h>
#include <visp_bridge/image.h>



int main(){
    vpImage<unsigned char> I;


vpHomogeneousMatrix a;

visp_bridge::toGeometryMsgsPose(a);


}