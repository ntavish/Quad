#include "testApp.h"
#include "cv.h"
#include "highgui.h"

//--------------------------------------------------------------
void testApp::setup()
{
	img=cvLoadImage("data/image.bmp",CV_LOAD_IMAGE_COLOR);
	cvConvertImage(img,img, CV_CVTIMG_SWAP_RB);
	if(img==NULL)
	{
		printf("could not load image\n");
		::exit(1);
	}
	temp = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	disp = cvCreateImage(cvGetSize(img), img->depth, 3);
	cvCopyImage(img, disp);

	image.allocate(img->width, img->height);
	image=img;

	tree = new quadtree(0,0,ofGetScreenWidth(), ofGetScreenHeight());

	cvZero(temp);
}

//--------------------------------------------------------------
void testApp::update()
{
	while(!drawThis.empty())
	{
		quadtree *item;
		item=drawThis.front();
		drawThis.pop();
		CvScalar col[4];

		item->part();
		for(int i=0;i<4;i++)
		{
			cvZero(temp);
			cvRectangle(temp, cvPoint(item->child[i]->x1,item->child[i]->y1),
				cvPoint(item->child[i]->x2,item->child[i]->y2), cvScalar(255,255,255,255),
				CV_FILLED, 8, 0);

			col[i] = cvAvg(img, temp);

			cvRectangle(disp,cvPoint(item->child[i]->x1,item->child[i]->y1),
				cvPoint(item->child[i]->x2,item->child[i]->y2), col[i],
				CV_FILLED, 8, 0 );
		}
		image=disp;
	}
}

//--------------------------------------------------------------
void testApp::draw()
{
	image.draw(0,0);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key=='s')
		cvSaveImage("data/save.bmp", disp);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
drawThis.push(tree->contains(x,y));
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
	drawThis.push(tree->contains(x,y));
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
