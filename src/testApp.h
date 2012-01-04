#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "cv.h"
#include "highgui.h"
#include <queue>

class quadtree
{
	public:
		int x1;
		int y1;

		int x2;
		int y2;

		quadtree *child[4];

		quadtree()
		{
			for(int i=0; i<4;i++)
				child[i]=NULL;
		}

		quadtree(int ax1, int ay1, int ax2, int ay2)
		{
			x1=ax1;
			x2=ax2;
			y1=ay1;
			y2=ay2;
			for(int i=0; i<4;i++)
				child[i]=NULL;
		}

		void part()
		{
			int x[]={x1,(x1+x2)/2,x2};
			int y[]={y1,(y1+y2)/2,y2};
			for(int i=0;i<4;i++)
			{
				child[i]=new quadtree();
			}

			child[0]->x1=x[0];
			child[0]->y1=y[0];
			child[0]->x2=x[1];
			child[0]->y2=y[1];

			child[1]->x1=x[1]+1;
			child[1]->y1=y[0];
			child[1]->x2=x[2];
			child[1]->y2=y[1];

			child[2]->x1=x[0];
			child[2]->y1=y[1]+1;
			child[2]->x2=x[1];
			child[2]->y2=y[2];

			child[3]->x1=x[1]+1;
			child[3]->y1=y[1]+1;
			child[3]->x2=x[2];
			child[3]->y2=y[2];

		}

		//[0],[1]  ,, [1]+1,[2]
		quadtree* contains(int x, int y)
		{
			if( x<x1 || x>x2 || y<y1 || y>y2 )
			{
				return NULL;
			}
			if(child[0] == NULL)
			{
				return this;
			}

			int res[2];
			if( x <= (x1+x2)/2 )
				res[0]=0;
			else
				res[0]=1;

			if( y <= (y1+y2)/2 )
				res[1]=0;
			else
				res[1]=1;

			return child[res[1]*2+res[0]]->contains(x,y);
		}
};


class testApp : public ofBaseApp{

	public:
		//our image
		ofxCvColorImage image;
		IplImage *img;
		IplImage *temp;
		IplImage *disp;

		queue<quadtree*> drawThis;

		quadtree *tree;

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

};
